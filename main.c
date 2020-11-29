#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eval.h"
#include <mpi.h>


int main(int argc, char *argv[]) {
    int myRank, numNodes, numDone;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
    numDone = 0;

    printSolutions = argc > 1 && strcmp(argv[1], "true") == 0;

    int *board = allocate(numNodes);
    if (board == NULL) {
        return 1;
    }

    // set cells that have not been examined to -1 for easy debugging
    int i;
    for (i = 0; i < queenNum; i++) {
        board[i] = -1;
    }

    // evaluate board, outputting the obvious solution for k=1,
    if (queenNum == 1) {
        printf("There is one solution for one queen.\n");
    } else {
        // col 0 is assigned based upon a node's rank
        board[0] = myRank;
        evalColumn(board, 1);
        MPI_Send(&solutionCount, 1, MPI_INT, MASTER, TAG_DONE, MPI_COMM_WORLD);

        if (myRank == MASTER) {
            int incomingCount;
            solutionCount = 0;
            int source;
            for (source = 0; source < queenNum; source++) {
                MPI_Recv(&incomingCount, 1, MPI_INT, source, TAG_DONE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                solutionCount = solutionCount + incomingCount;
            }
            printf("There are %d solutions for %d queens.\n", solutionCount, queenNum);
            if (printSolutions && solutionCount == 0) {
                printf("none\n");
            }
        }
    }

    free(board);
    MPI_Finalize();
    return 0;
}