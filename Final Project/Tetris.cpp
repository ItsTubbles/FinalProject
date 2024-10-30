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

void printBoard(char board[boardRows][boardCols], int colorPair) {
    
    for (int i = 4; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            if (board[i][j] != '.') {  // Check if it's part of a Tetromino
                attron(COLOR_PAIR(colorPair));  // Turn on the color pair
                mvprintw(i - 3 + 4, j * 3 + 1, "%c", board[i][j]);  // Print Tetromino part
                attroff(COLOR_PAIR(colorPair)); // Turn off the color pair
            } else {
                mvprintw(i - 3 + 4, j * 3 + 1, "%c", board[i][j]);  // Print empty space
            }
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

void printTetrisTitle() {
    const char* title = "TETRIS!";
    for (int i = 0; title[i] != '\0'; ++i) {
        int colorPair = rand() % 7 + 1; // Generate a random color pair (1 to 7)
        attron(COLOR_PAIR(colorPair));
        mvprintw(0, 12 + i, "%c", title[i]); // Print each letter at a specific position
        attroff(COLOR_PAIR(colorPair));
    }
    refresh();
}

bool canMoveDown(char board[boardRows][boardCols], char** tetromino, int tetroRows, int tetroCols, int currentRow, int columnStart) {
    // Check if moving down will go out of bounds or overlap with existing pieces
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (tetromino[i][j] != '.') { // If it's part of the Tetromino
                int newRow = currentRow + i + 1;
                int newCol = columnStart + j;
                // Check if it hits the bottom or another piece
                if (newRow >= boardRows || board[newRow][newCol] != '.') {
                    return false;
                }
            }
        }
    }
    return true;
}