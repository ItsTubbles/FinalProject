//Main.cpp
#include <ncurses.h>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed rand()
#include <unistd.h> // For usleep (to control fall speed)
#include "Tetris.h" // Utility board functions
#include "Pieces.h" // Pieces and piece function

void initColors() {
    start_color(); // Start color functionality

    // Define color pairs for Tetrominoes
    init_pair(1, COLOR_CYAN, COLOR_BLACK);    // Color for 'I' piece
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Color for 'O' piece
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // Color for 'T' piece
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   // Color for 'S' piece
    init_pair(5, COLOR_RED, COLOR_BLACK);     // Color for 'Z' piece
    init_pair(6, COLOR_BLUE, COLOR_BLACK);    // Color for 'J' piece
    init_pair(7, COLOR_WHITE, COLOR_BLACK);   // Color for 'L' piece
}

void quitGame() {
    endwin();  // End ncurses mode
    exit(0);   // Exit the program cleanly
}

int main() {
    initscr();             // Start ncurses mode
    noecho();              // Do not echo user input
    curs_set(0);           // Hide the cursor
    srand(time(0));        // Seed random number generator
    nodelay(stdscr, TRUE); // Make getch() non-blocking
    initColors();

    char board[boardRows][boardCols];

    // Initialize board with empty spaces
    for (int i = 0; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            board[i][j] = '.';
        }
    }

    // Print command instructions above the board
    printTetrisTitle();
    mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
    mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");
    drawBox();
    printBoard(board, 1);
    refresh();

    int ch;
    while ((ch = getch()) != 'S') {
        if(ch == 'W') quitGame();
        printTetrisTitle();
        move(14, 3);
        printw("Press 'Shift+S' to start");
        refresh();
        usleep(400000); 
    }

    // Main game loop
    while (true) {
        // Randomly select a Tetromino
        char** tetromino;
        int tetroRows, tetroCols, colorPair;

        int randomPiece = rand() % 7; // 7 possible Tetrominoes
        switch (randomPiece) {
            case 0: tetromino = convertToPointer(I_0); tetroRows = 1; tetroCols = 4; colorPair = 1; break; // I piece
            case 1: tetromino = convertToPointer(O); tetroRows = 2; tetroCols = 2; colorPair = 2; break;   // O piece
            case 2: tetromino = convertToPointer(T_0); tetroRows = 2; tetroCols = 3; colorPair = 3; break; // T piece
            case 3: tetromino = convertToPointer(S_0); tetroRows = 2; tetroCols = 3; colorPair = 4; break; // S piece
            case 4: tetromino = convertToPointer(Z_0); tetroRows = 2; tetroCols = 3; colorPair = 5; break; // Z piece
            case 5: tetromino = convertToPointer(J_0); tetroRows = 2; tetroCols = 3; colorPair = 6; break; // J piece
            case 6: tetromino = convertToPointer(L_0); tetroRows = 2; tetroCols = 3; colorPair = 7; break; // L piece
        }

        int currentRow = 0;
        int columnStart = boardCols / 2 - tetroCols / 2;

        bool gameOver = false;

        // Drop the current Tetromino
        while (!gameOver) {
            clear();  // Clear the screen
            printTetrisTitle();
            mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
            mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");

            // Draw the box around the board
            drawBox();

            // Clear the current position of the Tetromino from the board
            clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

            // Check for collision before moving Tetromino down
            if (canMoveDown(board, tetromino, tetroRows, tetroCols, currentRow, columnStart)) {
                currentRow++;  // Move down
            } else {
                // Place the Tetromino permanently on the board
                placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);
                
                // Check for game over: if Tetromino was placed in the top row
                if (currentRow == 0) {
                    gameOver = true;
                    break;
                }

                // Break to spawn a new piece
                break;
            }

            // Place the Tetromino in the new position
            placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

            // Print the updated board
            printBoard(board, colorPair);
            refresh();  // Refresh the screen to show the updated board

            usleep(400000);  // Sleep for 400 milliseconds (controls the fall speed)

            ch = getch();  // Check for user input
            if (ch != ERR) {   // If there's user input
                if (ch == 'W') {   // Check if Shift + W is pressed
                    break;
                }
            }
        }

        if (gameOver) {
            while ((ch = getch()) != 'W') {
                printTetrisTitle();
                move(13, 10);
                printw("GAME OVER!");
                move(14, 4);
                printw("Press 'Shift+W' to quit");
                refresh();
                usleep(400000); 
            }
            quitGame();  // End the game when 'W' is pressed
        }
    }
}


// int main() {
//     initscr();             // Start ncurses mode
//     noecho();              // Do not echo user input
//     curs_set(0);           // Hide the cursor
//     srand(time(0));        // Seed random number generator
//     nodelay(stdscr, TRUE); // Make getch() non-blocking
//     initColors();

//     char board[boardRows][boardCols];

//     // Initialize board with empty spaces
//     for (int i = 0; i < boardRows; i++) {
//         for (int j = 0; j < boardCols; j++) {
//             board[i][j] = '.';
//         }
//     }

//     // Print command instructions above the board
//     printTetrisTitle();
//     mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
//     mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");
//     drawBox();
//     printBoard(board, 1);
//     refresh();

//     int ch;
//     while ((ch = getch()) != 'S') {
//         if(ch == 'W') quitGame();
//         printTetrisTitle();
//         move(14, 3);
//         printw("Press 'Shift+S' to start");
//         refresh();
//         usleep(400000); 
//     }

//     // Randomly select a pieceS
//     char** tetromino;
//     int tetroRows, tetroCols, colorPair;

//     int randomPiece = rand() % 7; // 7 possible Tetrominoes
//     switch (randomPiece) {
//         case 0: tetromino = convertToPointer(I_0); tetroRows = 1; tetroCols = 4; colorPair = 1; break; // I piece
//         case 1: tetromino = convertToPointer(O); tetroRows = 2; tetroCols = 2; colorPair = 2; break;   // O piece
//         case 2: tetromino = convertToPointer(T_0); tetroRows = 2; tetroCols = 3; colorPair = 3; break; // T piece
//         case 3: tetromino = convertToPointer(S_0); tetroRows = 2; tetroCols = 3; colorPair = 4; break; // S piece
//         case 4: tetromino = convertToPointer(Z_0); tetroRows = 2; tetroCols = 3; colorPair = 5; break; // Z piece
//         case 5: tetromino = convertToPointer(J_0); tetroRows = 2; tetroCols = 3; colorPair = 6; break; // J piece
//         case 6: tetromino = convertToPointer(L_0); tetroRows = 2; tetroCols = 3; colorPair = 7; break; // L piece
//     }

//     int currentRow = 4 - tetroCols;
//     int columnStart = boardCols/2 - tetroCols/2;  // Starting column position

//     // Falling loop
//     while (currentRow + tetroRows < boardRows) {
//         clear();  // Clear the screen

//         printTetrisTitle();
//         mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
//         mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");

//         // Draw the box around the board
//         drawBox();

//         // Clear the current position of the Tetromino from the board
//         clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

//         // Move Tetromino one row down
//         currentRow++;

//         // Place the Tetromino in the new position
//         placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

//         // Print the updated board
//         printBoard(board, colorPair);
//         refresh();  // Refresh the screen to show the updated board

//         usleep(400000);  // Sleep for 400 milliseconds (controls the fall speed)

//         int ch = getch();  // Check for user input
//         if (ch != ERR) {   // If there's user input
//             if (ch == 'W') {   // Check if Shift + W is pressed
//                 break;         // Exit the loop to quit the program
//             }
//         }
//     }

//     while ((ch = getch()) != 'W') {
//         printTetrisTitle();
//         move(13, 10);
//         printw("GAME OVER!");
//         move(14, 4);
//         printw("Press 'Shift+w' to quit");
//         refresh();
//         usleep(400000); 
//     }

//     quitGame();
// }

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