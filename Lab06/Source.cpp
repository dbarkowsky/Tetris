
#include <iostream>
#include "TestSuite.h"
#include "Tetromino.h"
#include "Gameboard.h"
#include <vector>
#include <SFML/Graphics.hpp>

void testGameboard() {
    Gameboard board;
    
    Point pt1{ 3, 5 };
    board.setContent(pt1, 3);
    board.printToConsole();
}

void manualTesting() {
    // Manual shape testing
    Tetromino shape = Tetromino();
    char input{};;

    do {
        std::cout << std::endl;
        std::cout << "Valid shapes: S, Z, L, J, O, I, T " << std::endl;
        std::cout << "Rotate: r" << std::endl;
        std::cout << "Exit: x" << std::endl;
        std::cout << "Enter a command: ";

        std::cin >> input;
        std::cout << std::endl;

        switch (input) {
        case 'S':
            shape.setShape(TetShape::S);
            break;
        case 'Z':
            shape.setShape(TetShape::Z);
            break;
        case 'L':
            shape.setShape(TetShape::L);
            break;
        case 'J':
            shape.setShape(TetShape::J);
            break;
        case 'O':
            shape.setShape(TetShape::O);
            break;
        case 'I':
            shape.setShape(TetShape::I);
            break;
        case 'T':
            shape.setShape(TetShape::T);
            break;
        case 'r':
            shape.rotateClockwise();
            break;
        case 'x':
            exit(0);
            break;
        default:
            std::cout << "Invalid input. Try again." << std::endl;
            break;
        }
        shape.printToConsole();
    } while (input != 'x');
}

int main()
{
    testGameboard();
    TestSuite::runTestSuite();
    manualTesting();

    
}
