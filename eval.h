#ifndef EVAL_H
#define EVAL_H

#define MIN_QUEENS 1
#define MAX_QUEENS 26
#define MASTER 0
#define TAG_DONE 0

int queenNum;
int printSolutions;
int solutionCount;

int* allocate(int queens);

int checkPosition(const int* board, int col, int row);

void evalColumn(int* board, int col);

#endif
