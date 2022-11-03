#include "GridTetromino.h"

GridTetromino::GridTetromino() : Tetromino{}, gridLoc{ 0, 0 } {}

Point GridTetromino::getGridLoc() const {
	return gridLoc;
}

void GridTetromino::setGridLoc(int x, int y) {
	setGridLoc(Point(x, y));
}

void GridTetromino::setGridLoc(const Point& newGridLoc) {
	gridLoc = newGridLoc;
}

void GridTetromino::move(int xOffset, int yOffset) {
	gridLoc.setXY(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const {
	std::vector<Point> mapped{};
	for (Point block : blockLocs) {
		mapped.push_back(Point{ block.getX() + gridLoc.getX(), block.getY() + gridLoc.getY()});
	}
	return mapped;
}
