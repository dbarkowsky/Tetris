#pragma once
#include <vector>
#include "Point.h"

enum TetColor {
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE_LIGHT,
	BLUE_DARK,
	PURPLE
};

enum TetShape {
	S,
	Z,
	L,
	J,
	O,
	I,
	T
};

class Tetromino {
	friend class TestSuite;

	private:
		TetColor color;
		TetShape shape;
		std::vector<Point> blockLocs;
	public:
		Tetromino();
		TetColor getColor() const;
		TetShape getShape() const;
		void setShape(TetShape shape = TetShape::O);
		void rotateClockwise();
		void printToConsole() const;
};