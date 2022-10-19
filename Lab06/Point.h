#pragma once
#include <iostream>

class Point {
	friend class TestSuite;

	private:
		int x;
		int y;
	public:
		Point();
		Point(int x, int y);
		int getX() const;
		int getY() const;
		void setX(int x);
		void setY(int y);
		void setXY(int x, int y);
		void swapXY();
		void multiplyX(int factor);
		void multiplyY(int factor);
		std::string toString() const;
};