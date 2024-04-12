/**
 * \file game.cpp
 * \brief This file defines the functions of Game class for "Target nine" game
 * \author Konstantinos Trimikliniotis
*/

#include "../include/game.h"
#include <cstdlib>
#include <iostream>

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

MoveResult Game::processMove(MoveType type, Move move) {
    switch (type) {
        case MoveType::play:
            play(move);
            step_forward = {};   // clears the stack
                                 // if we play new move, we generate new
                                 // branch in move history tree
            return MoveResult::success;
        case MoveType::back:
            return stepBack();    
        case MoveType::forward:
            return stepForward();
        case MoveType::show_solution:
            solved = true;
            return MoveResult::success;    
    }
    return MoveResult::fail;
}

bool Game::isSolved() const{
    return solved;
}

void Game::printGrid() const {
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

void Game::printSolution() const {
    for (auto move: solution) {
        std::cout << move.row + 1 << " " << move.col + 1 << std::endl;
    }
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

}  // target_nine
