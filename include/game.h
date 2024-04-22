/**
 * \file game.h
 * \brief This file declares class Game for Target Nine game and is created as 
 *        an assignment for COMP-211(01) University of Nicosia
 * \author Konstantinos Trimikliniotis
 * \date 11 April 2024
*/

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "linked_stack.h"

namespace target_nine {

/**
 * <code>Move</code> struct which stores row and col of the move
*/
struct Move {
    int row = -1, col = -1;
};

/**
 * <code>GameOption</code> enum which describes possible types:
 * play: increasing row and column,
 * back: undo last move
 * forward: redo last move
 * show_solution: shows solution of the puzzle 
*/
enum class GameOption {
    play, back, forward, show_hint, exit
};

enum class MoveResult {
    fail, success,
};

/**
 * <code>Game</code> main class with game logic
*/
class Game {
public:
    static const int GRID_SIZE = 3;
    static const int MENU_OPTIONS = 5;

private:
    int next_hint = 0;
    int grid[GRID_SIZE][GRID_SIZE];
    bool solved = false;
    std::vector<Move> solution{};
    LinkedStack<Move> step_back;
    LinkedStack<Move> step_forward;

    /**
     * <code>generatePuzzle</code> randomly generates current grid and 
     * saves the solution
    */
    void generatePuzzle(int min_moves_to_win_);

    MoveResult stepBack();
    MoveResult stepForward();

    void play(Move move);
    void unplay(Move move);
    void checkWin();
    void playHint();
    Move readMove() const;
    
public:
    Game(int min_moves_to_win_);
    /**
     * <code>processMove</code> executes provided move
     * <BR>
     * @param type Type of the move from MoveType enum class
     * @param move Row and Column if the type is play, otherwise
     *             is not being used
     * @return Returns the result of the move as MoveResult enum class
    */
    MoveResult processMove(GameOption option);
    
    /**
     * <code>isSolved</code> checks if puzzle is solved
     * <BR>
     * @return If puzzle is solved (grid is filled with 9s) 
     *         returns true, otherwise false
    */
    bool isSolved() const;

    /**
     * <code>showBoard</code> prints the grid in terminal
    */
    void printGrid() const;
    /**
     * <code>printMenu</code> prints menu options in terminal
    */
    void printMenu() const;
};

}  // target_nine

#endif
