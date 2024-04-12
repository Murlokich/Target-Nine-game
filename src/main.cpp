/**
 * \file main.cpp
 * \brief This file contains main function and runs game loop for "Target nine" game
 * \author Konstantinos Trimikliniotis
*/

#include "../include/game.h"
#include <iostream>
#include <time.h>

using namespace target_nine;

const int GRID_SIZE = 3;

int main() {
    srand(time(0)); 

    int difficulty = 0;
    while (difficulty <= 0 || difficulty > 9) {
        std::cout << "Enter level of difficulty (from 1 to 9) for Target Nine puzzle: ";
        std::cin >> difficulty;
    }
    Game game(difficulty);
    while (!game.isSolved()) {
        int row = -1, col = -1;
        while (row >= GRID_SIZE || row < 0 || col >= GRID_SIZE || col < 0) {
            game.printGrid();
            std::cout << "Enter the row for move: ";
            std::cin >> row;
            std::cout << "Enter the column for move: ";
            std::cin >> col;
            row--, col--;
            if (row >= GRID_SIZE || row < 0 || col >= GRID_SIZE || col < 0) {
                std::cout << "Row and column must be in range from 1 to 3." 
                          << "Please, try enter values again";
            }
        }
        game.processMove(MoveType::play, {row, col});
    }
    game.printGrid();
    std::cout << "Puzzle Solved!";
}