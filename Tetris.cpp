//Tetris.cpp
#include "Tetris.h"

// Function implementations
void drawBox() {
    mvprintw(4, 0, "+");
    for (int i = 0; i < boardCols; i++) {
        printw("---");
    }
    printw("+");

    for (int i = 5; i <= boardRows; ++i) {
        mvprintw(i, 0, "|");
        mvprintw(i, boardCols * 3 + 1, "|");
    }

    mvprintw(boardRows + 1, 0, "+");
    for (int i = 0; i < boardCols; i++) {
        printw("---");
    }
    printw("+");
}

void printBoard(char board[boardRows][boardCols]) {
    // Shift the board content down by 4 rows so it fits inside the box
    for (int i = 4; i < boardRows; i++) {  // Start from row 4 (first visible row)
        for (int j = 0; j < boardCols; j++) {
            mvprintw(i - 3 + 4, j * 3 + 1, "%c", board[i][j]);  // Shift down by 4 rows
        }
    }
}

void placeTetrominoOnBoard(char board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col) {
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (tetromino[i][j] != ' ') {
                board[row + i][col + j] = tetromino[i][j];
            }
        }
    }
}

void clearTetrominoFromBoard(char board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col) {
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (tetromino[i][j] != ' ') {
                board[row + i][col + j] = '.';
            }
        }
    }
}