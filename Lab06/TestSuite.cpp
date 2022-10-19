#include "Point.h"
#include "Tetromino.h"
#include <cassert>
#include <iostream>
#include "TestSuite.h"


bool TestSuite::runTestSuite()
{
	std::cout << "=== Running TestSuite =========================" << "\n";
	// run some sanity tests on our classes to ensure they're working as expected.
	std::cout << "uncomment the #define statements in TestSuite.h when ready to test.\n";
	testPointClass();
	testTetrominoClass();
	std::cout << "=== TestSuite complete ========================" << "\n\n";
	return true;
}

bool TestSuite::testPointClass()
{
#ifdef POINT
	std::cout << " testPointClass()...\n";

	Point p;

	// test our initial values are 0,0
	assert(p.getX() == 0 && "Point ctor - x not initialized to 0");
	assert(p.getY() == 0 && "Point ctor - y not initialized to 0");

	// test setX()
	p.setX(1);
	assert(p.getX() == 1 && "Point::setX() failed");
	p.setX(-1);
	assert(p.getX() == -1 && "Point::setX() failed");

	// test setY()
	p.setY(2);
	assert(p.getY() == 2 && "Point::setY() failed");
	p.setY(-2);
	assert(p.getY() == -2 && "Point::setY() failed");

	// test setXY()
	p.setXY(3, 4);
	assert(p.getX() == 3 && p.getY() == 4 && "Point::setXY() failed");
	p.setXY(-3, -4);
	assert(p.getX() == -3 && p.getY() == -4 && "Point::setXY() failed");

	// test constructor with 2 params
	Point q(3, 4);
	assert(q.getX() == 3 && q.getY() == 4 && "Point::ctor failed to set default params");

	// test swapXY()
	q.swapXY();
	assert(q.getX() == 4 && q.getY() == 3 && "Point::swapXY() failed");

	// test multiplyX()
	q.multiplyX(-1);
	assert(q.getX() == -4 && "Point::multiplyX() failed");

	// test multiplyY()
	q.multiplyY(-1);
	assert(q.getY() == -3 && "Point::multiplyY() failed");

	// test copy constructor
	q.setXY(1, 2);
	Point r = q;
	assert(r.getX() == q.getX() && r.getY() == q.getY() && "Point copy ctor failed");
	r.setXY(3, 4);
	assert(r.getX() == 3 && r.getY() == 4
		&& q.getX() == 1 && q.getY() == 2 && "Point::setXY() failed");

	Point s{ 5,6 };
	std::cout << "expected:\t[5,6]\n";
	std::cout << "actual: \t" << s.toString() << "\n";

	// ensure const methods are actually const
	// These lines will cause compile time errors you have methods in your Point class that
	// should be labelled as const (because the methods don't change the internal member
	// variables of yoru class).
	// The solution: make these const methods!  (see LearnCpp 13.2- const class objects and member functions)
	const Point cPoint{};
	cPoint.getX();
	cPoint.getY();
	cPoint.toString();

	std::cout << "...passed!" << "\n";
#else
	std::cout << "Point class not tested.\n";
#endif
	return true;
}



bool TestSuite::testTetrominoClass()
{
#ifdef TETROMINO
	std::cout << " testTetrominoClass...";

	Tetromino t;


	assert(t.getColor() == TetColor::RED ||
		t.getColor() == TetColor::ORANGE ||
		t.getColor() == TetColor::YELLOW ||
		t.getColor() == TetColor::GREEN ||
		t.getColor() == TetColor::BLUE_LIGHT ||
		t.getColor() == TetColor::BLUE_DARK ||
		t.getColor() == TetColor::PURPLE &&
		"default Tetromino not initialized to valid color.");

	assert(t.getShape() == TetShape::S ||
		t.getShape() == TetShape::Z ||
		t.getShape() == TetShape::L ||
		t.getShape() == TetShape::J ||
		t.getShape() == TetShape::O ||
		t.getShape() == TetShape::I ||
		t.getShape() == TetShape::T &&
		"default Tetromino not initialized to valid shape.");
	
	int blockcount = BLOCK_COUNT;

	assert(t.blockLocs.size() == blockcount &&
		"default Tetromino has no blockLocs - likely because no default set in constructor");

	t.setShape(TetShape::S);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be: 4");
	t.setShape(TetShape::Z);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::L);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::J);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::O);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::I);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");
	t.setShape(TetShape::T);
	assert(t.blockLocs.size() == blockcount && "Tetromino shape size should be 4");


	// test the rotate functionality of a single block
	t.blockLocs.clear();
	t.blockLocs.push_back(Point(1, 2));
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == 2 && t.blockLocs[0].getY() == -1 && "Tetromino::rotateClockwise() failed");
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == -1 && t.blockLocs[0].getY() == -2 && "Tetromino::rotateClockwise() failed");
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == -2 && t.blockLocs[0].getY() == 1 && "Tetromino::rotateClockwise() failed");
	t.rotateClockwise();
	assert(t.blockLocs[0].getX() == 1 && t.blockLocs[0].getY() == 2 && "Tetromino::rotateClockwise() failed");

// ensure const methods are actually const
// These lines will cause compile time errors you have methods in your Tetromino class that
// should be labelled as const (because the methods don't change the internal member
// variables of yoru class).
// (see LearnCpp 13.2- const class objects and member functions)
	const Tetromino cTetromino;
	cTetromino.printToConsole();
	cTetromino.getColor();
	cTetromino.getShape();

	// Test const 
	std::cout << "passed!" << "\n";
#else
	std::cout << "Tetromino class not tested.\n";
#endif
	return true;
}







