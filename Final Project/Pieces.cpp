//Pieces.cpp
#include "Pieces.h"

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