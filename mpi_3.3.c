#include <stdio.h>
#include <mpi.h>

int main(void) {
    int comm_sz, my_rank, sum_ranks = 0, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0) {
        MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Recv(&sum_ranks, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received sum of ranks: %d\n", my_rank, sum_ranks);
    } else {
        // Process 0 calculates the sum of ranks
        for (int q = 1; q < comm_sz; q++) {
            MPI_Recv(&rank, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum_ranks += rank;
        }
        sum_ranks += my_rank;  // Include rank 0

        // Send the sum to all processes
        for (int q = 1; q < comm_sz; q++) {
            MPI_Send(&sum_ranks, 1, MPI_INT, q, 0, MPI_COMM_WORLD);
        }

        printf("Process 0 calculated sum of ranks: %d\n", sum_ranks);
    }

    MPI_Finalize();
    return 0;
}
