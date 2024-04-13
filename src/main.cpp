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
            GameOption option = static_cast<GameOption>(game_option - 1);
            if (option == GameOption::exit) {
                return 0;
            }
            game.processMove(option);  // order of enum elements                                                              // and printed options must be the same
        }
    }
    game.printGrid();
    std::cout << "Puzzle Solved!";
}