#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>

// Declare board dimensions
const int boardRows = 24;  // 20 visible rows + 4 extra rows off the top
const int boardCols = 10;

// Function declarations
void drawBox();
void printBoard(char board[boardRows][boardCols]);
void placeTetrominoOnBoard(char board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col);
void clearTetrominoFromBoard(char board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col);

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
