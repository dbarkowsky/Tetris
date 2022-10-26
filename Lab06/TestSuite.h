#ifndef TESTSUITE_H
#define TESTSUITE_H

// This class runs some automated testing for the Gameboard class
// Two steps are required to activate it:
// 1) Call TestSuite::runTestSuite() from main()
// 2) Uncomment the #define statements directly below:
//-----------------------------------------------------------------------
#define GAMEBOARD
#include "Gameboard.h"

class TestSuite {

private:	
	static void testGameboardClass();	// tests for the Gameboard class
	static bool isGameboardEmpty(const Gameboard& g);

public:
	// This will run a series of tests on the Point and Tetromino classes
	// when the #define statements at the top of this file are active.
	static void runTestSuite();
};


#endif /* TESTSUITE_H */