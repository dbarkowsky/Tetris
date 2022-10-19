#include "Point.h"

Point::Point() {
	setXY(0, 0);
};

Point::Point(int x, int y) {
	setXY(x, y);
};

int Point::getX() const {
	return x;
};

int Point::getY() const {
	return y;
};

void Point::setX(int x) {
	this->x = x;
};

void Point::setY(int y) {
	this->y = y;
};

void Point::setXY(int x, int y) {
	setX(x);
	setY(y);
};

void Point::swapXY() {
	int temp{ x };
	x = y;
	y = temp;
};

void Point::multiplyX(int factor) {
	x *= factor;
};

void Point::multiplyY(int factor) {
	y *= factor;
};

std::string Point::toString() const {
	return x + " " + y;
};
