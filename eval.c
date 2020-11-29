#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int checkPosition(const int *board, int col, int row) {
    // this is the first column, so there are no other queens to attack
    if (col == 0) return 1;
    int i;
    for (i = col - 1; i >= 0; i--) {
        // same row
        if (board[i] == row) return 0;

        int deltaX = i - col;
        int deltaY = board[i] - row;
        // back diagonal
        if (deltaX - deltaY == 0) return 0;
        // forward diagonal
        if (deltaX + deltaY == 0) return 0;
    }

    return 1;
}

void evalColumn(int *board, int col) {
    int row;

    for (row = 0; row < queenNum; row++) {
        board[col] = row;
        int valid = checkPosition(board, col, row);
        int lastCol = col == queenNum - 1;
        if (valid) {
            // if last column, increment solution count and print if necessary
            if (lastCol) {
                solutionCount += 1;
                if (printSolutions) {
                    printf("\t");
                    int i;
                    for (i = 0; i < queenNum; i++) {
                        // adjust row position by adding one
                        // (typically Chess positions start at 1, not 0)
                        printf("%d ", board[i] + 1);
                    }
                    printf("\n");
                }
            } else {
                evalColumn(board, col + 1);
            }
        }
    }
}

// make space for storing data and return an array to represent the board
int *allocate(int queens) {
    solutionCount = 0;

    queenNum = queens;
    if (queenNum < MIN_QUEENS || queenNum > MAX_QUEENS) {
        printf("You requested %d, but the number of queens must be between %d and %d.",
               queenNum, MIN_QUEENS, MAX_QUEENS);

        return NULL;
    }

    // represent board as an array of columns
    // each column holds an int representing the row of the queen
    // add debug watch with: *board@queenNum
    int *board;
    board = (int *) calloc(queenNum, sizeof(int));

    return board;
}
