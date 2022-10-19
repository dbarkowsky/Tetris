#include "Point.h"
#include <string>

Point::Point() {
	setXY(0, 0);
};

Point::Point(const int x, const int y) {
	setXY(x, y);
};

int Point::getX() const {
	return x;
};

int Point::getY() const {
	return y;
};

void Point::setX(const int x) {
	this->x = x;
};

void Point::setY(const int y) {
	this->y = y;
};

void Point::setXY(const int x, int y) {
	setX(x);
	setY(y);
};

void Point::swapXY() {
	int temp{ x };
	x = y;
	y = temp;
};

void Point::multiplyX(const int factor) {
	x *= factor;
};

void Point::multiplyY(const int factor) {
	y *= factor;
};

std::string Point::toString() const {
	return "[" + std::to_string(getX()) + "," + std::to_string(getY()) + "]";
};
