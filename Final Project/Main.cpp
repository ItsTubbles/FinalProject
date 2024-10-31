//Main.cpp
#include "Tetris.h" // Utility board functions
#include "Pieces.h" // Pieces and piece function

int main() {
    char ch;

    // Timing constants for delays
    const int dropDelay = 750000;    // Delay for fall speed in microseconds
    const int moveDelay = 50000;     // Delay for side-to-side movement
    const int titleDelay = 200000;   // Delay for title update
    const int setDelayThreshold = 15; // Ticks to delay before setting piece

    // Counters for timing
    int fallCounter = 0;           // Tracks fall timing
    int setDelayCounter = 0;       // Tracks delay before setting the piece
    int titleCounter = 0;          // Counter for title update timing

    // Initialize game and create the "Next Piece" window
    startGame(board);
    WINDOW* nextPieceWin = createNextPieceWindow();

    // Choose the initial "next" Tetromino
    char** nextTetromino;
    int nextRows, nextCols, nextColorPair;
    int randomPiece = rand() % 7;
    switch (randomPiece) {
        case 0: nextTetromino = convertToPointer(I_0); nextRows = 1; nextCols = 4; nextColorPair = 1; break;
        case 1: nextTetromino = convertToPointer(O); nextRows = 2; nextCols = 2; nextColorPair = 2; break;
        case 2: nextTetromino = convertToPointer(T_0); nextRows = 2; nextCols = 3; nextColorPair = 3; break;
        case 3: nextTetromino = convertToPointer(S_0); nextRows = 2; nextCols = 3; nextColorPair = 4; break;
        case 4: nextTetromino = convertToPointer(Z_0); nextRows = 2; nextCols = 3; nextColorPair = 5; break;
        case 5: nextTetromino = convertToPointer(J_0); nextRows = 2; nextCols = 3; nextColorPair = 6; break;
        case 6: nextTetromino = convertToPointer(L_0); nextRows = 2; nextCols = 3; nextColorPair = 7; break;
    }

    clear();
    // Main game loop
    while (true) {
        showNextPiece(nextPieceWin, nextTetromino, nextRows, nextCols, nextColorPair);

        // Set the current Tetromino to the next piece
        tetromino = nextTetromino;
        tetroRows = nextRows;
        tetroCols = nextCols;
        colorPair = nextColorPair;

        // Generate a new "next" Tetromino
        randomPiece = rand() % 7;
        switch (randomPiece) {
            case 0: nextTetromino = convertToPointer(I_0); nextRows = 1; nextCols = 4; nextColorPair = 1; break;
            case 1: nextTetromino = convertToPointer(O); nextRows = 2; nextCols = 2; nextColorPair = 2; break;
            case 2: nextTetromino = convertToPointer(T_0); nextRows = 2; nextCols = 3; nextColorPair = 3; break;
            case 3: nextTetromino = convertToPointer(S_0); nextRows = 2; nextCols = 3; nextColorPair = 4; break;
            case 4: nextTetromino = convertToPointer(Z_0); nextRows = 2; nextCols = 3; nextColorPair = 5; break;
            case 5: nextTetromino = convertToPointer(J_0); nextRows = 2; nextCols = 3; nextColorPair = 6; break;
            case 6: nextTetromino = convertToPointer(L_0); nextRows = 2; nextCols = 3; nextColorPair = 7; break;
        }

        currentRow = 0;
        columnStart = boardCols / 2 - tetroCols / 2;
        bool gameOver = false;
        setDelayCounter = 0;  // Reset the delay counter for each new piece

        // Drop the current Tetromino
        while (!gameOver) {

            // Update the title consistently based on titleCounter
            if (titleCounter >= titleDelay) {
                printTetrisTitle();
                titleCounter = 0;  // Reset the counter after updating the title
            }
            titleCounter += moveDelay;  // Accumulate title counter with each loop iteration

            mvprintw(1, 0, "w=set      s=down    Shift+a=rotate left");
            mvprintw(2, 0, "a=left    d=right    Shift+D=rotate right");
            showNextPiece(nextPieceWin, nextTetromino, nextRows, nextCols, nextColorPair);

            // Draw the box around the board
            drawBox();

            // Clear the current position of the Tetromino from the board
            clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);

            // Check if Tetromino can move down
            if (canMoveDown(board, tetromino, tetroRows, tetroCols, currentRow, columnStart)) {
                if (fallCounter >= dropDelay) {
                    currentRow++;  // Move down based on fall speed
                    fallCounter = 0; // Reset fall counter
                    setDelayCounter = 0;  // Reset delay counter if it can still move down
                }
            } 
            else {
                // Increment the delay counter if the piece cannot move down
                setDelayCounter++;

                // Check if delay threshold is reached before setting the piece
                if (setDelayCounter >= setDelayThreshold) {
                    placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart, colorPair);

                    // Check for game-over condition at the top row
                    if (currentRow == 0) {
                        gameOver = true;
                    }
                    break;  // Break to spawn a new piece
                }
            }

            // Place the Tetromino in the new position
            placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart, colorPair);

            // Print the updated board
            printBoard(board);
            refresh();          // Refresh stdscr to update main board
            wrefresh(nextPieceWin);  // Refresh the next piece window

            usleep(moveDelay);  // Apply appropriate delay for movements

            fallCounter += moveDelay;  // Accumulate fall counter

            ch = getch();
            flushinp();  // Clear input buffer to prevent lag from queued inputs
            if (ch != ERR) {
                if (keyActions.find(ch) != keyActions.end()) {
                    clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);
                    keyActions[ch]();  // Execute the corresponding action
                }
                if (ch == 'W') { // Quit game if 'W' is pressed
                    gameOver = true;
                }
            }
        }

        if (gameOver) {
            while ((ch = getch()) != 'W') {
                printTetrisTitle();
                showNextPiece(nextPieceWin, nextTetromino, nextRows, nextCols, nextColorPair);
                move(13, 10);
                printw("GAME OVER!");
                move(14, 4);
                printw("Press 'Shift+W' to quit");
                refresh();
                usleep(400000);
            }
            quitGame();  // End the game when 'W' is pressed
            delwin(nextPieceWin); // Delete the next piece window before quitting
        }
    }
}
