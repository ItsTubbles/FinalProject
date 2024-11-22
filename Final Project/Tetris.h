#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <cstdlib>
#include <ctime> 
#include <unistd.h> 
#include <map>
#include <vector>
#include <functional>
#include <set>
#include <fstream>
#include "Pieces.h"

// Declare board dimensions
const int boardRows = 24;  // 20 visible rows + 4 extra rows off the top
const int boardCols = 10;

// Holds each piece on the board
struct Cell {
    char piece;
    int color;
};

// Declare global variables with extern to prevent redefinition errors
extern Cell board[boardRows][boardCols];
extern int columnStart;
extern int currentRow;
extern int tetroRows, tetroCols;
extern int colorPair;
extern char** tetromino;
extern int rotationIndex;
extern int currentScore;
extern int highScore;

// Function declarations
void loadHighScore();
void startGame(Cell (&board)[boardRows][boardCols]);
void initColors();
void drawBox();
void printTetrisTitle();
WINDOW* createNextPieceWindow();
void showNextPiece(WINDOW* nextPieceWin, char** tetromino, int rows, int cols, int colorPair);
void createScoreWindows();
void showCurrentScore();
void showHighScore();
void printBoard(Cell board[boardRows][boardCols]);
void placeTetrominoOnBoard(Cell board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col, int colorPair);
void clearTetrominoFromBoard(Cell board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col);
bool canMoveDown(Cell board[boardRows][boardCols], char** tetromino, int tetroRows, int tetroCols, int currentRow, int columnStart);
bool canPlaceTetromino(Cell board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int newRow, int newCol);
void clearCompletedRows(Cell board[boardRows][boardCols]);
void quitGame();

// Key controls
extern map<int, vector<char**>> rotations;
extern map<int, function<void()>> keyActions;

// Template to convert any Tetromino array into a pointer-to-pointer
template <size_t rows, size_t cols>
char** convertToPointer(char (&tetromino)[rows][cols]) {
    char** result = new char*[rows];
    for (size_t i = 0; i < rows; ++i) {
        result[i] = new char[cols];
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = tetromino[i][j];
        }
    }
    return result;
}

#endif // TETRIS_H
