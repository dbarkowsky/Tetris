#include "Point.h"
#include "Gameboard.h"
#include <cassert>
#include <iomanip>
#include <vector>

Gameboard::Gameboard() {
	empty();
}

void Gameboard::empty() {
	for (int x = 0; x < MAX_X; x++) {
		for (int y = 0; y < MAX_Y; y++) {
			grid[y][x] = EMPTY_BLOCK;
		}
	}
}

void Gameboard::printToConsole() const {
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			std::cout << std::setw(2);
			if (grid[y][x] == EMPTY_BLOCK) {
				std::cout << ".";
			}
			else {
				std::cout << grid[y][x];
			}
		}
		std::cout << std::endl;
	}
}

int Gameboard::getContent(Point block) const{
	assert(isValidPoint(block));
	return grid[block.getY()][block.getX()];
}

int Gameboard::getContent(int x, int y) const{
	assert(isValidPoint(x, y));
	return grid[y][x];
}

void Gameboard::setContent(Point block, int content){
	if (isValidPoint(block.getX(), block.getY()))
		grid[block.getY()][block.getX()] = content;
}

void Gameboard::setContent(int x, int y, int content){
	if(isValidPoint(x, y))
		grid[y][x] = content;
}

void Gameboard::setContent(std::vector<Point>& points, const int content) {
	for (Point& point : points) {
		grid[point.getY()][point.getX()] = content;
	}
}

bool Gameboard::areAllLocsEmpty(const std::vector<Point>& points) const {
	for (const Point& point : points) {
		if (isValidPoint(point)) {
			if (grid[point.getY()][point.getX()] != EMPTY_BLOCK) {
				return false;
			}
		}
		
	}
	return true;
}

int Gameboard::countCompletedRows() {
	std::vector<int> toRemove{ getCompletedRowIndices() };
	int size = toRemove.size();
	return size;
}

int Gameboard::removeCompletedRows(){
	std::vector<int> toRemove{ getCompletedRowIndices() };
	int size = toRemove.size();
	removeRows(toRemove);
	return size;
}

Point Gameboard::getSpawnLoc() const{
	return spawnLoc;
}

bool Gameboard::isValidPoint(const Point& block) const{
	if ((block.getX() >= 0 && block.getX() <= MAX_X) &&
		(block.getY() >= 0 && block.getY() <= MAX_Y)) {
		return true;
	}
	return false;
}

bool Gameboard::isValidPoint(const int x, const int y) const{
	if ((x >= 0 && x <= MAX_X) &&
		(y >= 0 && y <= MAX_Y)) {
		return true;
	}
	return false;
}

bool Gameboard::isRowCompleted(const int index) const{
	assert(index >= 0 && index <= MAX_Y && "row out of index");
	for (int coordinate : grid[index]) {
		if (coordinate == EMPTY_BLOCK) {
			return false;
		}
	}
	return true;
}

void Gameboard::fillRow(const int index, const int content) {
	for (int& coordinate : grid[index]) {
		coordinate = content;
	}
}

std::vector<int> Gameboard::getCompletedRowIndices() const{
	std::vector<int> completedRows;
	for (int i = 0; i < MAX_Y; i++) {
		if (isRowCompleted(i)) {
			completedRows.push_back(i);
		}
	}
	return completedRows;
}

void Gameboard::copyRowIntoRow (const int sourceIndex, const int targetIndex){
	for (int i = 0; i < MAX_X; i++) {
		grid[targetIndex][i] = grid[sourceIndex][i];
	}
}

void Gameboard::removeRow(const int rowIndex){
	assert(rowIndex >= 0 && rowIndex <= MAX_Y);
	for (int y = rowIndex; y > 0; y--) {
		copyRowIntoRow(y - 1, y);
	}
	fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(const std::vector<int>& rowIndexes){
	for (int i = 0; i < rowIndexes.size(); i++) {
		removeRow(rowIndexes[i]);
	}
}