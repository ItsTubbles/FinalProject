//Tetris.cpp
#include "Tetris.h"
#include "DisjointSet.h"

// Define global variables
Cell board[boardRows][boardCols]; // Game board grid
int columnStart = 0;              // Tetromino start column
int currentRow = 0;               // Current row position of tetromino
int tetroRows = 0, tetroCols = 0; // Tetromino dimensions
int colorPair = 0;                // Color pair ID for tetromino
char** tetromino = nullptr;       // Pointer to current tetromino shape
int rotationIndex = 0;            // Current rotation state of tetromino
int currentScore = 0;             // Player's current score
int highScore = 0;                // High score to beat
WINDOW* scoreWin;                 // Window for displaying current score
WINDOW* highScoreWin;             // Window for displaying high score


//Load high score 
void loadHighScore() {
    ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> highScore;
        highScoreFile.close();
    } 
    else {
        highScore = 0; 
    }
}

// Function to start the game and initialize the board
void startGame(Cell (&board)[boardRows][boardCols]) {
    initscr();             // Start ncurses mode
    noecho();              // Do not echo user input
    curs_set(0);           // Hide the cursor
    srand(time(0));        // Seed random number generator
    nodelay(stdscr, TRUE); // Make getch() non-blocking
    keypad(stdscr, TRUE);  // Enable input from stdscr
    initColors();

    // Initialize board with empty spaces and default color
    for (int i = 0; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            board[i][j].piece = '.';  // Set piece to empty
            board[i][j].color = 0;
        }
    }

    loadHighScore();       // Load high score from file
    createScoreWindows();  // Initialize score windows

    // Print command instructions above the board
    printTetrisTitle();
    mvprintw(1, 0, "q=quit    s=down     w=rotate left");
    mvprintw(2, 0, "a=left    d=right    e=rotate right");
    drawBox();
    printBoard(board);
    refresh();  // Ensure stdscr updates

    int ch;
    while ((ch = getch()) != 's') {
        if (ch == 'q') quitGame();
        printTetrisTitle();
        move(14, 7);
        printw("Press 's' to start");
        refresh();
        createScoreWindows();  // Initialize score windows

        // Show initial scores
        showCurrentScore();
        showHighScore();
        usleep(200000);
    }
}

//initializes the color mechanisms
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

//function to print the board
void printBoard(Cell board[boardRows][boardCols]) {
    for (int i = 4; i < boardRows; i++) {
        for (int j = 0; j < boardCols; j++) {
            if (board[i][j].piece != '.') { // Check if it's part of a Tetromino
                attron(COLOR_PAIR(board[i][j].color));  // Turn on the color pair
                mvprintw(i - 3 + 4, j * 3 + 1, "%c", board[i][j].piece);  // Print Tetromino part
                attroff(COLOR_PAIR(board[i][j].color)); // Turn off the color pair
            } else {
                mvprintw(i - 3 + 4, j * 3 + 1, "%c", board[i][j].piece);  // Print empty space
            }
        }
    }
}

// Function to create and initialize the "Next Piece" window
WINDOW* createNextPieceWindow() {
    int windowWidth = 8;
    int windowHeight = 6;
    int startX = boardCols * 3 + 3; // Place it to the right of the main board
    int startY = 4;

    // Create the window
    WINDOW* nextPieceWin = newwin(windowHeight, windowWidth, startY, startX);
    keypad(nextPieceWin, TRUE); // Enable input for next piece window
    box(nextPieceWin, 0, 0);    // Draw a box around the window
    mvwprintw(nextPieceWin, 0, 1, "Next"); // Label the window

    wrefresh(nextPieceWin); // Refresh the next piece window
    return nextPieceWin;
}

// Function to show the next piece in the window
void showNextPiece(WINDOW* nextPieceWin, char** tetromino, int rows, int cols, int colorPair) {
    // Clear the previous content and redraw the box
    werase(nextPieceWin);
    box(nextPieceWin, 0, 0);
    mvwprintw(nextPieceWin, 0, 1, "Next");

    // Calculate offset to center the Tetromino in the window
    int offsetY = (6 - rows) / 2;
    int offsetX = (8 - cols) / 2;

    // Display each cell of the Tetromino with the specified color
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (tetromino[i][j] != ' ') { // Only display non-empty cells
                wattron(nextPieceWin, COLOR_PAIR(colorPair)); // Turn on color
                mvwprintw(nextPieceWin, i + offsetY, j + offsetX, "%c", tetromino[i][j]);
                wattroff(nextPieceWin, COLOR_PAIR(colorPair)); // Turn off color
            }
        }
    }
    wrefresh(nextPieceWin); // Refresh the next piece window to display changes
}

// Function to create and initialize score windows
void createScoreWindows() {
    int startX = boardCols * 3 + 3;
    int startY = 4;

    // Create current score window
    scoreWin = newwin(3, 15, startY + 8, startX);
    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 0, 1, "Score");
    wrefresh(scoreWin);

    // Create high score window
    highScoreWin = newwin(3, 15, startY + 12, startX);
    box(highScoreWin, 0, 0);
    mvwprintw(highScoreWin, 0, 1, "High Score");
    wrefresh(highScoreWin);
}

// Function to update the current score display
void showCurrentScore() {
    werase(scoreWin);
    box(scoreWin, 0, 0);
    mvwprintw(scoreWin, 0, 1, "Score");
    mvwprintw(scoreWin, 1, 1, "%d", currentScore);
    wrefresh(scoreWin);
}

// Function to update the high score display
void showHighScore() {
    werase(highScoreWin);
    box(highScoreWin, 0, 0);
    mvwprintw(highScoreWin, 0, 1, "High Score");
    mvwprintw(highScoreWin, 1, 1, "%d", highScore);
    wrefresh(highScoreWin);
}

//Places the piece on the board
void placeTetrominoOnBoard(Cell board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col, int colorPair) {
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (tetromino[i][j] != ' ') {
                board[row + i][col + j].piece = tetromino[i][j];
                board[row + i][col + j].color = colorPair; // Set the color
            }
        }
    }
}

//clears the piece off the board
void clearTetrominoFromBoard(Cell board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int row, int col) {
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (row + i < boardRows && col + j < boardCols && tetromino[i][j] != ' ') {
                board[row + i][col + j].piece = '.';
            }
        }
    }
}

//prints the tetris title with cool colors
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

//Checks to see if a piece can move down
bool canMoveDown(Cell board[boardRows][boardCols], char** tetromino, int tetroRows, int tetroCols, int currentRow, int columnStart) {
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (tetromino[i][j] != ' ') { // Only check Tetromino cells
                int newRow = currentRow + i + 1;
                int newCol = columnStart + j;

                // Check bounds and if the new position collides with existing board pieces
                if (newRow >= boardRows || board[newRow][newCol].piece != '.') {
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to check if the tetromino can be placed at a new position
bool canPlaceTetromino(Cell board[boardRows][boardCols], char **tetromino, int tetroRows, int tetroCols, int newRow, int newCol) {
    for (int i = 0; i < tetroRows; i++) {
        for (int j = 0; j < tetroCols; j++) {
            if (tetromino[i][j] != ' ' && (newRow + i >= boardRows || newCol + j < 0 || newCol + j >= boardCols || board[newRow + i][newCol + j].piece != '.')) {
                return false;  // Out of bounds or collision detected
            }
        }
    }
    return true;
}

//Scores filled rows
void clearCompletedRows(Cell board[boardRows][boardCols]) {
    int completedCount = 0;
    for (int row = boardRows - 1; row >= 0; --row) {
        DisjointSet ds(boardCols);
        bool rowComplete = true;
        bool rowEmpty = true;

        for (int col = 0; col < boardCols; ++col) {
            if (board[row][col].piece == 'X') {
                rowEmpty = false;  // Mark as not empty if any cell is filled
                if (col > 0 && board[row][col - 1].piece == 'X') {
                    ds.unite(col, col - 1);  // Union adjacent filled cells
                }
            } 
            else {
                rowComplete = false;  // Mark as incomplete if any cell is empty
            }
        }

        // Stop checking further if row is entirely empty
        if (rowEmpty) break;

        // If row is complete, clear it and shift all rows above down
        if (rowComplete && ds.getSize(0) == boardCols) {
            // Clear the row
            for (int col = 0; col < boardCols; ++col) {
                board[row][col].piece = '.';
            }

            // Shift rows above down by one
            for (int r = row; r > 0; --r) {
                for (int c = 0; c < boardCols; ++c) {
                    board[r][c] = board[r - 1][c];
                }
            }

            // Reset the top row to empty after shifting
            for (int col = 0; col < boardCols; ++col) {
                board[0][col].piece = '.';
            }

            // Re-check the current row after shifting
            row++;  // Increment row to re-check this position after shift
            completedCount++;
        }
    }
    currentScore += completedCount * completedCount * 10;
    if (currentScore > highScore){
        highScore = currentScore;

        // Overwrite high score with current score to highscore.txt
        ofstream highScoreFile("highscore.txt");
        if (highScoreFile.is_open()) {
            highScoreFile << highScore;
            highScoreFile.close();
        }
    }
}

//Quit the game
void quitGame() {
    endwin();  // End ncurses mode
    exit(0);   // Exit the program cleanly
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
//function to move left
function<void()> moveLeft = [&]() {
    if (canPlaceTetromino(board, tetromino, tetroRows, tetroCols, currentRow, columnStart - 1)) {
        clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);
        columnStart--;
        placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart, colorPair);
    }
};

//function to move right
function<void()> moveRight = [&]() {
    if (canPlaceTetromino(board, tetromino, tetroRows, tetroCols, currentRow, columnStart + 1)) {
        clearTetrominoFromBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart);
        columnStart++;
        placeTetrominoOnBoard(board, tetromino, tetroRows, tetroCols, currentRow, columnStart, colorPair);
    }
};

//function to speed up the fall
function<void()> moveDown = [&]() {
    if (canMoveDown(board, tetromino, tetroRows, tetroCols, currentRow, columnStart)) currentRow++;
};

//function to rotate the piece to the right
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

//function to rotate the piece to the left
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
    {'w', rotateLeft}, 
    {'e', rotateRight} 
};