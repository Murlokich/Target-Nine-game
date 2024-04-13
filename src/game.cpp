/**
 * \file game.cpp
 * \brief This file defines the functions of Game class for "Target nine" game
 * \author Konstantinos Trimikliniotis
*/

#include "../include/game.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>

namespace target_nine {

Game::Game(int min_moves_to_win_) {
    generatePuzzle(min_moves_to_win_);    
}

void Game::generatePuzzle(int min_moves_to_win_) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            grid[row][col] = 9;
        }
    }
    solution.resize(min_moves_to_win_);
    for (int i = 0; i < min_moves_to_win_; i++) {
        int row = std::rand() % 3;
        int col = std::rand() % 3;
        solution[i] = {row, col};
        unplay(solution[i]);
    }
}

MoveResult Game::stepBack() {
    if (step_back.empty()) {
        return MoveResult::fail;
    }
    unplay(step_back.top());
    step_forward.push(step_back.top());
    step_back.pop();
    return MoveResult::success;
}

MoveResult Game::stepForward() {
    if (step_forward.empty()) {
        return MoveResult::fail;
    }
    play(step_forward.top());
    step_back.push(step_forward.top());
    step_forward.pop();
    return MoveResult::success;
}

// doesn't update stack, this responsibility is upon process move
void Game::play(Move move) {
    grid[move.row][move.col]--;  // in both loops move cell was incremented
    for (int row = 0; row < GRID_SIZE; row++) {
        grid[row][move.col]++;
        grid[row][move.col] %= 10;  // if cell is 10 reassign it to 0
    }
    for (int col = 0; col < GRID_SIZE; col++) {
        grid[move.row][col]++;
        grid[move.row][col] %= 10;  //if cell is 10 reassign it to 0
    }
    checkWin();
}

// doesn't update move_forward stack, this responsibility is upon process move
void Game::unplay(Move move) {
    grid[move.row][move.col]++;  // in both loops move cell was decremented
    for (int row = 0; row < GRID_SIZE; row++) {
        grid[row][move.col] += 10 - 1;  // first decreases value by one, 
                                        // than adds 10 to make the result of modulo consistent
                                        // without adding 10 compile dependant (-1 % 10 case)
        grid[row][move.col] %= 10;  // cuts off overflow for values [0, 8] 
    }
    for (int col = 0; col < GRID_SIZE; col++) {
        grid[move.row][col] += 10 - 1;  // first decreases value by one, 
                                        // than adds 10 to make the result of modulo consistent
                                        // without adding 10 compile dependant (-1 % 10 case)
        grid[move.row][col] %= 10;  // cuts off overflow for values [0, 8] 
    }
}

Move Game::readMove() const {
    int row = -1, col = -1;
    while (row >= Game::GRID_SIZE || row < 0 || col >= Game::GRID_SIZE || col < 0) {
        std::cout << "Enter the row for move: ";
        std::cin >> row;
        std::cout << "Enter the column for move: ";
        std::cin >> col;
        row--, col--;
        if (row >= Game::GRID_SIZE || row < 0 || col >= Game::GRID_SIZE || col < 0) {
            std::cout << "Row and column must be in range from 1 to 3." 
                    << "Please, try enter values again";
        }
    }
    return {row, col};
}

MoveResult Game::processMove(GameOption option) {
    switch (option) {
        case GameOption::play:
            play(readMove());
            step_forward = {};   // clears the stack
                                 // if we play new move, we generate new
                                 // branch in move history tree
            return MoveResult::success;
        case GameOption::back:
            return stepBack();    
        case GameOption::forward:
            return stepForward();
        case GameOption::show_hint:
            solved = true;
            return MoveResult::success; 
        default:
            assert(true);

    }
    assert(true);
}

bool Game::isSolved() const{
    return solved;
}

void Game::printGrid() const {
    std::cout << std::endl;
    std::cout << "  ";
    for (int col = 1; col <= GRID_SIZE; col++) {
        std::cout << " " << col;
    }
    std::cout << std::endl << std::endl;
    for (int row = 0; row < GRID_SIZE; row++) {
        std::cout << row + 1 << "  ";
        for (int col = 0; col < GRID_SIZE; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Game::checkWin() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] != 9) {
                solved = false;
                return;
            }
        }
    }
    solved = true;
}

void Game::playHint() {
    std::cout << std::endl;
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            grid[row][col] = 9;
        }
    }
    for (int i = solution.size() - 1; i > next_hint; i--) {
        unplay(solution[i]);
    }
    if (next_hint == solution.size() - 1) {
        solved = true;
    }
    std::cout << "Hint: row = " << solution[next_hint].row + 1 
              << ", col = " << solution[next_hint].col + 1
              << std::endl << std::endl;  
    next_hint++;
    step_back = {};
    step_forward = {};
}

void Game::printMenu() const {
    static const std::string options[Game::MENU_OPTIONS] = {
        "Play move", "Go to previous position",
        "Go to next position", "Show hint", "Exit",
    };
    std::cout << std::endl << "Choose an option: " << std::endl;
    for (int i = 1; i <= Game::MENU_OPTIONS; i++) {
        std::cout << i << ") " << options[i - 1] << std::endl;
    }
    std::cout << std::endl;
}

}  // target_nine
