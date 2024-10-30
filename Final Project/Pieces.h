//Pieces.h
#ifndef PIECES_H
#define PIECES_H

#include <iostream>
using namespace std;

// Tetromino 'I'
char I_0[1][4] = {
    {'X', 'X', 'X', 'X'}
};

char I_90[4][1] = {
    {'X'},
    {'X'},
    {'X'},
    {'X'}
};

// Tetromino 'O' (no rotation needed)
char O[2][2] = {
    {'X', 'X'},
    {'X', 'X'}
};

// Tetromino 'T'
char T_0[2][3] = {
    {'X', 'X', 'X'},
    {' ', 'X', ' '}
};

char T_90[3][2] = {
    {'X', ' '},
    {'X', 'X'},
    {'X', ' '}
};

char T_180[2][3] = {
    {' ', 'X', ' '},
    {'X', 'X', 'X'}
};

char T_270[3][2] = {
    {' ', 'X'},
    {'X', 'X'},
    {' ', 'X'}
};

// Tetromino 'S'
char S_0[2][3] = {
    {' ', 'X', 'X'},
    {'X', 'X', ' '}
};

char S_90[3][2] = {
    {'X', ' '},
    {'X', 'X'},
    {' ', 'X'}
};

// Tetromino 'Z'
char Z_0[2][3] = {
    {'X', 'X', ' '},
    {' ', 'X', 'X'}
};

char Z_90[3][2] = {
    {' ', 'X'},
    {'X', 'X'},
    {'X', ' '}
};

// Tetromino 'J'
char J_0[2][3] = {
    {'X', ' ', ' '},
    {'X', 'X', 'X'}
};

char J_90[3][2] = {
    {'X', 'X'},
    {'X', ' '},
    {'X', ' '}
};

char J_180[2][3] = {
    {'X', 'X', 'X'},
    {' ', ' ', 'X'}
};

char J_270[3][2] = {
    {' ', 'X'},
    {' ', 'X'},
    {'X', 'X'}
};

// Tetromino 'L'
char L_0[2][3] = {
    {' ', ' ', 'X'},
    {'X', 'X', 'X'}
};

char L_90[3][2] = {
    {'X', ' '},
    {'X', ' '},
    {'X', 'X'}
};

char L_180[2][3] = {
    {'X', 'X', 'X'},
    {'X', ' ', ' '}
};

char L_270[3][2] = {
    {'X', 'X'},
    {' ', 'X'},
    {' ', 'X'}
};

#endif // TETROMINO_H

// template<size_t rows, size_t cols>
// void printTetromino(char (&tetromino)[rows][cols]) {
//     for (size_t i = 0; i < rows; i++) {
//         for (size_t j = 0; j < cols; j++) {
//             printf("%c ", tetromino[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

//// Printing the Tetrominoes and their rotations (for copying)

//// Print I
// printTetromino(I_0);
// printTetromino(I_90);

//// Print O
// printTetromino(O);

//// Print T
// printTetromino(T_0);
// printTetromino(T_90);
// printTetromino(T_180);
// printTetromino(T_270);

//// Print S
// printTetromino(S_0);
// printTetromino(S_90);

//// Print Z
// printTetromino(Z_0);
// printTetromino(Z_90);

//// Print J
// printTetromino(J_0);
// printTetromino(J_90);
// printTetromino(J_180);
// printTetromino(J_270);

//// Print L
// printTetromino(L_0);
// printTetromino(L_90);
// printTetromino(L_180);
// printTetromino(L_270);