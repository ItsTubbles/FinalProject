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

// Define the rotations map explicitly
map<int, vector<char**>> rotations = {
    {1, {convertToPointer(I_0), convertToPointer(I_90)}},
    {3, {convertToPointer(T_0), convertToPointer(T_90), convertToPointer(T_180), convertToPointer(T_270)}},
    {4, {convertToPointer(S_0), convertToPointer(S_90)}},
    {5, {convertToPointer(Z_0), convertToPointer(Z_90)}},
    {6, {convertToPointer(J_0), convertToPointer(J_90), convertToPointer(J_180), convertToPointer(J_270)}},
    {7, {convertToPointer(L_0), convertToPointer(L_90), convertToPointer(L_180), convertToPointer(L_270)}}
};

// Define movement and rotation actions using lambda functions with explicit types
function<void()> moveLeft = [&]() {
    if (columnStart > 0) columnStart--;
};

function<void()> moveRight = [&]() {
    if (columnStart + tetroCols < boardCols) columnStart++;
};

function<void()> moveDown = [&]() {
    if (canMoveDown(board, tetromino, tetroRows, tetroCols, currentRow, columnStart)) currentRow++;
};

function<void()> rotateRight = [&]() {
    if (rotations[colorPair].size() > 1) {  // Rotate only if multiple rotations are defined
        rotationIndex = (rotationIndex + 1) % rotations[colorPair].size();
        tetromino = rotations[colorPair][rotationIndex];

        // Set tetroRows and tetroCols based on the rotation and piece type
        switch (colorPair) {
            case 1: // 'I' piece
                tetroRows = (rotationIndex % 2 == 0) ? 1 : 4;
                tetroCols = (rotationIndex % 2 == 0) ? 4 : 1;
                break;
            case 2: // 'O' piece (no rotation)
                tetroRows = 2;
                tetroCols = 2;
                break;
            case 3: // 'T' piece
                tetroRows = (rotationIndex % 2 == 0) ? 2 : 3;
                tetroCols = (rotationIndex % 2 == 0) ? 3 : 2;
                break;
            case 4: // 'S' piece
            case 5: // 'Z' piece
                tetroRows = (rotationIndex % 2 == 0) ? 2 : 3;
                tetroCols = (rotationIndex % 2 == 0) ? 3 : 2;
                break;
            case 6: // 'J' piece
            case 7: // 'L' piece
                tetroRows = (rotationIndex % 2 == 0) ? 2 : 3;
                tetroCols = (rotationIndex % 2 == 0) ? 3 : 2;
                break;
        }
    }
};

function<void()> rotateLeft = [&]() {
    if (rotations[colorPair].size() > 1) {  // Rotate only if multiple rotations are defined
        rotationIndex = (rotationIndex - 1 + rotations[colorPair].size()) % rotations[colorPair].size();
        tetromino = rotations[colorPair][rotationIndex];

        // Set tetroRows and tetroCols based on the rotation and piece type
        switch (colorPair) {
            case 1: // 'I' piece
                tetroRows = (rotationIndex % 2 == 0) ? 1 : 4;
                tetroCols = (rotationIndex % 2 == 0) ? 4 : 1;
                break;
            case 2: // 'O' piece (no rotation)
                tetroRows = 2;
                tetroCols = 2;
                break;
            case 3: // 'T' piece
                tetroRows = (rotationIndex % 2 == 0) ? 2 : 3;
                tetroCols = (rotationIndex % 2 == 0) ? 3 : 2;
                break;
            case 4: // 'S' piece
            case 5: // 'Z' piece
                tetroRows = (rotationIndex % 2 == 0) ? 2 : 3;
                tetroCols = (rotationIndex % 2 == 0) ? 3 : 2;
                break;
            case 6: // 'J' piece
            case 7: // 'L' piece
                tetroRows = (rotationIndex % 2 == 0) ? 2 : 3;
                tetroCols = (rotationIndex % 2 == 0) ? 3 : 2;
                break;
        }
    }
};



// Map of key inputs to corresponding movement functions
map<int, function<void()>> keyActions = {
    {'a', moveLeft},
    {'d', moveRight},
    {'s', moveDown},
    {'A', rotateLeft}, // Shift + a for left rotation
    {'D', rotateRight} // Shift + d for right rotation
};
