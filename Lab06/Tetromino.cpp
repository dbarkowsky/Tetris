#include "Tetromino.h"

Tetromino::Tetromino() {
	setShape();
};

TetColor Tetromino::getColor() const {
	return color;
};

TetShape Tetromino::getShape() const {
	return shape;
};

void Tetromino::setShape(TetShape shape) {
	this->shape = shape;
	blockLocs.clear(); // Just in case this Tetromino gets reassigned.
	color = static_cast<TetColor>(shape);

	switch (shape)
	{
	case S:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(-1, 0));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(1, 1));
		break;
	case Z:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(1, 0));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(-1, 1));
		break;
	case L:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(1, -1));
		break;
	case J:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(-1, -1));
		break;
	case O:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(1, 0));
		blockLocs.push_back(Point(1, 1));
		break;
	case I:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(0, 1));
		blockLocs.push_back(Point(0, 2));
		break;
	case T:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, -1));
		blockLocs.push_back(Point(-1, 0));
		blockLocs.push_back(Point(1, 0));
		break;
	default:
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 0));
		blockLocs.push_back(Point(0, 0));
		break;
	}
};

void Tetromino::rotateClockwise() {
	if (getShape() != TetShape::O) {
		for (Point& square : blockLocs) {
			int newX{ square.getY() };
			int newY{ square.getX() * -1 };

			square.setX(newX);
			square.setY(newY);
		}
	}
};

void Tetromino::printToConsole() const {
	for (int y = 3; y >= -3; y--) {
		for (int x = -3; x <= 3; x++) {
			bool match = false;
			for (Point square : blockLocs) {
				
				if (y == square.getY() && x == square.getX()) {
					match = true;
				}
			}

			if (match) {
				std::cout << 'x';
			}
			else {
				std::cout << '.';
			}
		}

		std::cout << std::endl;
	}
};

TetShape Tetromino::getRandomShape() {
	return static_cast<TetShape>(rand() % TetShape::COUNT);
}
