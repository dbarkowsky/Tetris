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
	protected:
		std::vector<Point> blockLocs; // Array of points that make up the tetromino
	public:
		/// <summary>
		///		Constructor class
		/// </summary>
		Tetromino();

		/// <summary>
		///		Getter for Color
		/// </summary>
		/// <returns>
		///		TetColor: colour of tetromino
		/// </returns>
		TetColor getColor() const;

		/// <summary>
		///		Getter for shape
		/// </summary>
		/// <returns>
		///		TetShape: shape of tetromino
		/// </returns>
		TetShape getShape() const;

		/// <summary>
		///		Sets which shape tetromino is
		/// </summary>
		/// <param name="shape">
		///		TetShape: desired shape
		/// </param>
		void setShape(TetShape shape = TetShape::O);

		/// <summary>
		///		Rotates the tetromino 90 degress clockwise
		/// </summary>
		void rotateClockwise();

		/// <summary>
		///		Prints a grid of dots with x's representing the tetromino
		/// </summary>
		void printToConsole() const;
};