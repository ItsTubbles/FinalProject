//Main.cpp
#include <ncurses.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed rand()
#include <unistd.h> // For usleep (to control fall speed)
#include "Pieces.h" // Include your pieces header file

const int boardRows = 20;
const int boardCols = 10;

void drawBox() {
    // Draw the top of the box
    mvprintw(0, 0, "+");
    for (int i = 0; i < boardCols; i++) {
        printw("---");
    }
    printw("+");

    // Draw the sides of the box
    for (int i = 1; i <= boardRows; ++i) {
        mvprintw(i, 0, "|");                   // Left side
        mvprintw(i, boardCols * 3 + 1, "|");   // Right side (adjusting for 3 spaces per column)
    }

    // Draw the bottom of the box
    mvprintw(boardRows + 1, 0, "+");
    for (int i = 0; i < boardCols; i++) {
        printw("---");
    }
    printw("+");
}

void printBoard(char board[boardRows][boardCols]) {
    for (int i = 0; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            mvprintw(i + 1, j * 3 + 1, "%c", board[i][j]);  // Adjust for space between columns
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

int main() {
    initscr();             // Start ncurses mode
    noecho();              // Do not echo user input
    curs_set(0);           // Hide the cursor
    srand(time(0));        // Seed random number generator

    char board[boardRows][boardCols];

    // Initialize board with empty spaces
    for (int i = 0; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            board[i][j] = '.';
        }
    }

    // Randomly select a piece
    char **tetromino;
    int tetroRows, tetroCols;

    int randomPiece = rand() % 7; // 7 possible Tetrominoes
    switch (randomPiece) {
        case 0: tetromino = convertToPointer(I_0); tetroRows = 1; tetroCols = 4; break;
        case 1: tetromino = convertToPointer(O); tetroRows = 2; tetroCols = 2; break;
        case 2: tetromino = convertToPointer(T_0); tetroRows = 2; tetroCols = 3; break;
        case 3: tetromino = convertToPointer(S_0); tetroRows = 2; tetroCols = 3; break;
        case 4: tetromino = convertToPointer(Z_0); tetroRows = 2; tetroCols = 3; break;
        case 5: tetromino = convertToPointer(J_0); tetroRows = 2; tetroCols = 3; break;
        case 6: tetromino = convertToPointer(L_0); tetroRows = 2; tetroCols = 3; break;
    }

    int currentRow = 0;
    int columnStart = 3;  // Starting column position

    // Falling loop
    while (currentRow + tetroRows < boardRows) {
        clear();  // Clear the screen

        // Draw the box around the board
        drawBox();

        // Clear the current position of the Tetromino from the board
        clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

        // Move Tetromino one row down
        currentRow++;

        // Place the Tetromino in the new position
        placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

        // Print the updated board
        printBoard(board);
        refresh();  // Refresh the screen to show the updated board

        usleep(200000);  // Sleep for 200 milliseconds (controls the fall speed)
    }

    // Keep the final board displayed
    getch(); // Wait for user input before exiting

    endwin();              // End ncurses mode
    return 0;
}

// #include <ncurses.h>

// int main() {
//     initscr();             //Starts ncurses mode
//     printw("Press 'a' for a message, 'q' to quit.");
//     refresh();             //Refreshes the screen to show message

//     int ch;
//     while ((ch = getch()) != 'q') {  //Loop until 'q' is pressed
//         clear();                     //Clears the screen
        
//         if (ch == 'a') {
//             printw("You pressed 'a'! Great choice.");
//         } else {
//             printw("Press 'a' for a message or 'q' to quit.");
//         }

//         refresh();                   
//     }

//     endwin(); //Ends ncurses mode
//     return 0;
// }