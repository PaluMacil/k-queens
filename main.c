#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("number of queens must be specified (1 - 16)\n");
        return 1;
    }
    printSolutions = argc > 2 && strcmp(argv[2], "true") == 0;

    int *board = allocate(atoi(argv[1]));
    if (board == NULL) {
        return 1;
    }

    // set cells that have not been examined to -1 for easy debugging
    int i;
    for (i = 0; i < queenNum; i++) {
        board[i] = -1;
    }

    if (printSolutions) {
        printf("Solutions:\n");
    }
    // evaluate board, starting with column 0
    evalColumn(board, 0);

    if (printSolutions && solutionCount == 0) {
        printf("none\n");
    }
    const char * singularPhrase = "There is one solutions for one queen.\n";
    const char * pluralPhrase = "There are %d solutions for %d queens.\n";
    printf(solutionCount == 1 ? singularPhrase : pluralPhrase,
           solutionCount,
           queenNum);

    free(board);
    return 0;
}