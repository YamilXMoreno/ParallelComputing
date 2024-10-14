#include <stdio.h>
#include <mpi.h>

int main(void) {
    int comm_sz, my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0) {
        // Send the rank to process 0
        MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // Process 0 receives the rank from all other processes and prints them
        printf("Process 0 is running\n");
        for (int q = 1; q < comm_sz; q++) {
            int recv_rank;
            MPI_Recv(&recv_rank, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process 0 received rank %d from process %d\n", recv_rank, q);
        }
    }

    MPI_Finalize();
    return 0;
}
