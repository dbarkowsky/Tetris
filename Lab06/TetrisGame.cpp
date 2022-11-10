#include "Gameboard.h"
#include "GridTetromino.h"
#include "TetrisGame.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <algorithm>

const int TetrisGame::BLOCK_WIDTH{32};			  // pixel width of a tetris block, init to 32
const int TetrisGame::BLOCK_HEIGHT{32};			  // pixel height of a tetris block, init to 32
const double TetrisGame::MAX_SECONDS_PER_TICK{0.75}; // the slowest "tick" rate (in seconds), init to 0.75
const double TetrisGame::MIN_SECONDS_PER_TICK{0.20}; // the fastest "tick" rate (in seconds), init to 0.20

TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset) 
	: window{ window }, blockSprite{ blockSprite }, gameboardOffset { gameboardOffset }, nextShapeOffset{ nextShapeOffset } {
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf"))
	{
		assert(false && "Missing font: RedOctober.ttf");
	};
	loadAudio();
	fillShapeSack();
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(425, 325);
	music.setLoop(true);
	music.setVolume(50);
	reset();
}

void TetrisGame::draw() const{
	drawGameboard();
	Point startLocation{ gameboardOffset.getX(), gameboardOffset.getY() };
	drawTetromino(currentShape, startLocation);
	drawTetromino(nextShape, nextShapeOffset);
	drawTetromino(ghostShape, startLocation, 50.0f);
	window.draw(scoreText);
}

void TetrisGame::onKeyPressed(sf::Event& e) {
	if (!resetOnNextTick && !shapePlacedSinceLastGameLoop) {
		switch (e.key.code)
		{
		case sf::Keyboard::Up:
			attemptRotate(currentShape);
			updateGhostShape();
			break;
		case sf::Keyboard::Left:
			attemptMove(currentShape, currentShape.getGridLoc().getX() - 1, currentShape.getGridLoc().getY());
			updateGhostShape();
			break;
		case sf::Keyboard::Right:
			attemptMove(currentShape, currentShape.getGridLoc().getX() + 1, currentShape.getGridLoc().getY());
			updateGhostShape();
			break;
		case sf::Keyboard::Down:
			if (!attemptMove(currentShape, currentShape.getGridLoc().getX(), currentShape.getGridLoc().getY() + 1)) {
				lock(currentShape);
			}
			break;
		case sf::Keyboard::Space:
			drop(currentShape);
			lock(currentShape);
			break;
		default:
			break;
		}
	}
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
	std::cout << "secondsSinceLastTick: " << secondsSinceLastTick
		<< ", secondsPerTick: " << secondsPerTick << std::endl;
	
	secondsSinceLastTick += secondsSinceLastLoop;
	// Prevent cases where elapsed time is very large, causing speed ups.
	if (secondsSinceLastTick > 1) {
		secondsSinceLastTick = secondsPerTick + 0.1; 
	}
	if (secondsSinceLastTick > secondsPerTick) {
		tick();
		secondsSinceLastTick -= secondsPerTick;
		if (resetOnNextTick) {
			resetOnNextTick = false;
			reset();
		}

		if (shapePlacedSinceLastGameLoop) {
			std::cout << "place Tick" << std::endl;
			shapePlacedSinceLastGameLoop = false;
			const int rowsToDelete = board.countCompletedRows();
			if (rowsToDelete > 0) {
				deleteOnNextTick = true;
			}
			spawnNextShape();
			pickNextShape();
		}
	}

	if (secondsSinceLastTick > secondsPerTick / 2) {
		if (deleteOnNextTick) {
			std::cout << "delete Tick" << std::endl;
			const int rowsReturned = board.removeCompletedRows();
			score += calcScore(rowsReturned);
			sfxClear.play();
			updateScoreDisplay();
			determineLevel();
			determineSecondsPerTick();
			deleteOnNextTick = false;
		}
	}
}

int TetrisGame::calcScore(const int rowsCleared) {
	switch (rowsCleared)
	{
		case 1:
			return 100 * level;
			break;
		case 2:
			return 300 * level;
			break;
		case 3:
			return 500 * level;
			break;
		case 4:
			return 800 * level;
			break;
		default:
			return 0;
			break;
	}
}

void TetrisGame::tick() {
	if (!attemptMove(currentShape, currentShape.getGridLoc().getX(), currentShape.getGridLoc().getY() + 1)) {
		lock(currentShape);
	}
}

void TetrisGame::reset() {
	secondsSinceLastTick = 0;
	deleteOnNextTick = false;
	resetOnNextTick = false;
	music.play();
	score = 0;
	updateScoreDisplay();
	determineLevel();
	determineSecondsPerTick();
	board.empty();
	pickNextShape();
	spawnNextShape();
	pickNextShape();
}

void TetrisGame::pickNextShape() {
	if (shapeSack.size() == 0) {
		fillShapeSack();
	}
	nextShape.setShape(shapeSack.back());
	shapeSack.pop_back();
}

void TetrisGame::fillShapeSack() {
	for (int i = 0; i < TetShape::COUNT; i++) {
		shapeSack.push_back(static_cast<TetShape>(i));
	}
	std::random_shuffle(shapeSack.begin(), shapeSack.end());
}

bool TetrisGame::TetrisGame::spawnNextShape() { 
	currentShape = nextShape;
	currentShape.setGridLoc(board.getSpawnLoc());
	if (isPositionLegal(currentShape)) {
		ghostShape = currentShape;
		ghostShape.setGridLoc(currentShape.getGridLoc());
		updateGhostShape();
		return true;
	}
	else {
		music.stop();
		sfxGameOver.play();
		secondsSinceLastTick -= secondsPerTick * 5;
		resetOnNextTick = true;
		return false;
	}
}

bool TetrisGame::attemptRotate(GridTetromino& shape) { 
	GridTetromino rotatedShape = shape;
	rotatedShape.rotateClockwise();
	if (isPositionLegal(rotatedShape)) {
		shape.rotateClockwise();
		sfxRotate.play();
		return true;
	}
	return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) { 
	GridTetromino copy = shape;
	copy.setGridLoc(x, y);
	if (!isPositionLegal(copy)) {
		return false;
	}
	shape.setGridLoc(x, y);
	return true; 
}

void TetrisGame::drop(GridTetromino& shape) {
	while(attemptMove(shape, shape.getGridLoc().getX(), shape.getGridLoc().getY() + 1)) {};
	sfxDrop.play();
}

void TetrisGame::lock(GridTetromino& shape) {
	std::vector<Point> locations = shape.getBlockLocsMappedToGrid();
	board.setContent(locations, shape.getColor());
	shapePlacedSinceLastGameLoop = true;
}

// Graphics methods ==============================================

void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color, const float alpha) const{
	sf::Texture texture;
	try {
		// Load texture
		if (!texture.loadFromFile("./images/tiles.png")) {
			throw "Texture didn't load.";
		}
		texture.setSmooth(true);
		// What part of the sprite map do you need?
		blockSprite.setTextureRect(sf::IntRect(color * BLOCK_WIDTH, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
	}
	catch (std::string e) {
		// Don't panic
		std::cout << e;
		exit(1);
	}

	// Where is the block displayed?
	blockSprite.setPosition(sf::Vector2f(topLeft.getX() + (BLOCK_WIDTH * xOffset), topLeft.getY() + (BLOCK_HEIGHT * yOffset)));
	// Change transparency?
	blockSprite.setColor(sf::Color(255, 255, 255, alpha));
	window.draw(blockSprite);
}

void TetrisGame::drawGameboard() const {
	for (int i = 0; i < Gameboard::MAX_X; i++) {
		for (int j = 0; j < Gameboard::MAX_Y; j++) {
			if (board.getContent(i, j) != Gameboard::EMPTY_BLOCK) {
				drawBlock(gameboardOffset, i, j, static_cast<TetColor>(board.getContent(i, j)));
			}
		}
	}
}

void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft, const float alpha) const {
	std::vector<Point> points{ tetromino.getBlockLocsMappedToGrid() };
	for (Point block : points) {
		drawBlock(topLeft, block.getX(), block.getY(), tetromino.getColor(), alpha);
	}
}

void TetrisGame::updateGhostShape(){
	ghostShape = currentShape;
	drop(ghostShape);
}

void TetrisGame::updateScoreDisplay() {
	scoreText.setString("score: " + std::to_string(score));
}

// State & gameplay/logic methods ================================

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const { 
	if (!isWithinBorders(shape)) {
		return false;
	}
	
	if (!board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid())) {
		return false;
	}

	return true; 
}

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
	std::vector<Point> blocks = shape.getBlockLocsMappedToGrid();
	for (Point block : blocks) {
		if (block.getX() >= Gameboard::MAX_X ||
			block.getX() < 0 ||
			block.getY() >= Gameboard::MAX_Y) {
			return false;
		}
	}
	return true; 
}

void TetrisGame::determineLevel() {
	int originalLevel = level;
	if (score > 20000) {
		level = 5;
		music.setPitch(1.2);
	}
	else if (score > 12000) {
		level = 4;
		music.setPitch(1.15);
	}
	else if (score > 5000) {
		level = 3;
		music.setPitch(1.1);
	}
	else if (score > 1500) {
		level = 2;
		music.setPitch(1.05);
	}
	else {
		level = 1;
		music.setPitch(1);
	}
	if (originalLevel != level && level != 1) {
		sfxLevelUp.play();
	}
}

void TetrisGame::determineSecondsPerTick() {
	switch (level)
	{
	case 1:
		secondsPerTick = MAX_SECONDS_PER_TICK;
		break;
	case 2:
		secondsPerTick = MAX_SECONDS_PER_TICK - 0.2;
		break;
	case 3:
		secondsPerTick = MAX_SECONDS_PER_TICK - 0.3;
		break;
	case 4:
		secondsPerTick = MAX_SECONDS_PER_TICK - 0.4;
		break;
	case 5:
		secondsPerTick = MIN_SECONDS_PER_TICK;
		break;
	default:
		secondsPerTick = MAX_SECONDS_PER_TICK;
		break;
	}
}


void TetrisGame::loadAudio() {
	// Load Sound Effects
	try {
		music.openFromFile("audio/tetrisMusic.ogg");
		sfxDropBuffer.loadFromFile("audio/blockDrop.ogg");
		sfxRotateBuffer.loadFromFile("audio/blockRotate.ogg");
		sfxGameOverBuffer.loadFromFile("audio/gameOver.ogg");
		sfxLevelUpBuffer.loadFromFile("audio/levelUp.ogg");
		sfxClearBuffer.loadFromFile("audio/clear.ogg");
	}
	catch (const std::exception& exc) {
		std::cout << exc.what();
	}
}