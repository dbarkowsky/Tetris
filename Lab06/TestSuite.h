#ifndef TESTSUITE_H
#define TESTSUITE_H

// This class runs some automated testing for Point and Tetromino classes
// Two steps are required to activate it:
// 1) Call TestSuite::runTestSuite() from main()
// 2) Uncomment the #define statements directly below:
//-----------------------------------------------------------------------
#define POINT
#define TETROMINO

class TestSuite {

private:
	static const int BLOCK_COUNT{ 4 };	// # of blocks in a Tetromino
	static bool testPointClass();		// tests for the Point class
	static bool testTetrominoClass();	// tests for the Tetromino class

public:
	// This will run a series of tests on the Point and Tetromino classes
	// when the #define statements at the top of this file are active.
	static bool runTestSuite();
};


#endif // !TESTSUITE_H
