//Main.cpp
#include <ncurses.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed rand()
#include <unistd.h> // For usleep (to control fall speed)
#include "Tetris.h" // Utility board functions
#include "Pieces.h" // Pieces and piece function

int main() {
    initscr();             // Start ncurses mode
    noecho();              // Do not echo user input
    curs_set(0);           // Hide the cursor
    srand(time(0));        // Seed random number generator
    nodelay(stdscr, TRUE); // Make getch() non-blocking

    char board[boardRows][boardCols];

    // Initialize board with empty spaces
    for (int i = 0; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            board[i][j] = '.';
        }
    }

    // Print command instructions above the board
    mvprintw(0, 0, "             TETRIS!                  ");
    mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
    mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");
    refresh();

    // Randomly select a piece
    char** tetromino;
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

    int currentRow = 4 - tetroCols;
    int columnStart = boardCols/2 - tetroCols/2;  // Starting column position

    // Falling loop
    while (currentRow + tetroRows < boardRows) {
        clear();  // Clear the screen

        mvprintw(0, 0, "             TETRIS!                  ");
        mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
        mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");

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

        usleep(400000);  // Sleep for 200 milliseconds (controls the fall speed)

        int ch = getch();  // Check for user input
        if (ch != ERR) {   // If there's user input
            if (ch == 'W') {   // Check if Shift + W is pressed
                break;         // Exit the loop to quit the program
            }
        }
    }

    nodelay(stdscr, FALSE);  // Disable non-blocking input, return to normal blocking mode
    move(14, 3); 
    printw("Press 'shift+Set' to quit");
    refresh();
    
    int ch;
    while ((ch = getch()) != 'W') {
        // Wait for 'W' to quit
    }

    endwin();// End ncurses mode
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