#pragma once
#include <iostream>

class Point {
	friend class TestSuite;

	private:
		int x;
		int y;
	public:
		/// <summary>
		///		Default constructor
		/// </summary>
		Point();

		/// <summary>
		///		Constructor that creates a point with x and y coordinates
		/// </summary>
		/// <param name="x">
		///		X coordinate
		///	</param>
		/// <param name="y">
		///		Y coordinate
		/// </param>
		Point(int x, int y);

		/// <summary>
		///		Getter for X
		/// </summary>
		/// <returns>
		///		int: x coordinate
		/// </returns>
		int getX() const;

		/// <summary>
		///		Getter for Y
		/// </summary>
		/// <returns>
		///		int: y coordinate
		/// </returns>
		int getY() const;

		/// <summary>
		///		Setter for X
		/// </summary>
		/// <param name="x">
		///		int: x coordinate
		/// </param>
		void setX(int x);

		/// <summary>
		///		Setter for Y
		/// </summary>
		/// <param name="y">
		///		int: y coordinate
		/// </param>
		void setY(int y);

		/// <summary>
		///		Setter for both X and Y
		/// </summary>
		/// <param name="x">
		///		int: x coordinate
		/// </param>
		/// <param name="y">
		///		int: y coordinate
		/// </param>
		void setXY(int x, int y);

		/// <summary>
		///		Swaps the x and y coordinates
		/// </summary>
		void swapXY();

		/// <summary>
		///		Multiplies X by the factor
		/// </summary>
		/// <param name="factor">
		///		int: multiplication factor
		/// </param>
		void multiplyX(int factor);

		/// <summary>
		///		Multiplies Y by the factor
		/// </summary>
		/// <param name="factor">
		///		int: multiplication factor
		/// </param>
		void multiplyY(int factor);

		/// <summary>
		///		Prints the point to a string
		/// </summary>
		/// <returns>
		///		std::string: "x y"
		/// </returns>
		std::string toString() const;
};