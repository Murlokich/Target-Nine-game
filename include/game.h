/**
 * \file game.h
 * \brief This file declares the Main Game class for "Target nine" game
 *        and some additional structs/enums
 * \author Konstantinos Trimikliniotis
*/

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <stack>

namespace target_nine {

/**
 * <code>Move</code> struct which stores row and col of the move
*/
struct Move {
    int row = -1, col = -1;
};

/**
 * <code>MoveType</code> enum which describes possible types:
 * play: increasing row and column,
 * back: undo last move
 * forward: redo last move
 * show_solution: shows solution of the puzzle 
*/
enum class MoveType {
    play, back, forward, show_solution, 
};

enum class MoveResult {
    fail, success,
};

/**
 * <code>Game</code> main class with game logic
*/
class Game {
    static const int GRID_SIZE = 3;
    int grid[GRID_SIZE][GRID_SIZE];
    bool solved = false;
    std::vector<Move> solution{};
    std::stack<Move> step_back;
    std::stack<Move> step_forward;

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
    MoveResult processMove(MoveType type, Move move = {});
    
    /**
     * <code>isSolved</code> checks if puzzle is solved
     * <BR>
     * @return If puzzle is solved (grid is filled with 9s) 
     *         returns true, otherwise false
    */
    [[nodiscard]] bool isSolved() const;

    /**
     * <code>showBoard</code> prints the grid in terminal
    */
    void printGrid() const;
    void printSolution() const;
};

}  // target_nine

#endif