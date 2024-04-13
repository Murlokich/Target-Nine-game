/**
 * \file main.cpp
 * \brief This file contains main function and runs game loop for "Target nine" game
 * \author Konstantinos Trimikliniotis
*/

#include "../include/game.h"
#include <iostream>
#include <time.h>

using namespace target_nine;


int main() {
    srand(time(0)); 

    int difficulty = 0;
    while (difficulty <= 0 || difficulty > 9) {
        std::cout << "Enter level of difficulty (from 1 to 9) for Target Nine puzzle: ";
        std::cin >> difficulty;
    }
    Game game(difficulty);
    while (!game.isSolved()) {
        int game_option = -1;
        while (game_option < 1 || game_option > Game::MENU_OPTIONS) {
            game.printGrid();
            game.printMenu();
            std::cin >> game_option;
            if (game_option < 1 || game_option > Game::MENU_OPTIONS) {
                continue;
            }

            GameOption option = static_cast<GameOption>(game_option - 1); // order of enum elements
                                                                          // and printed options must be the same
            if (option == GameOption::exit) {
                return 0;
            }
            MoveResult res = game.processMove(option);
            if (res == MoveResult::fail) {
                if (option == GameOption::back) {
                    std::cout << "No moves to undo!" << std::endl;
                }
                else if (option == GameOption::forward) {
                    std::cout << "No moves to redo!" << std::endl;
                }
                else {
                    std::cout << "Fatal error!" << std::endl;
                    return 1;
                }
            }                                                               
        }
    }
    game.printGrid();
    std::cout << "Puzzle Solved!";
}