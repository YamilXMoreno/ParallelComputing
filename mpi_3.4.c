#include <stdio.h>
#include <mpi.h>

int main(void) {
    int comm_sz, my_rank, recv_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int next_rank = (my_rank + 1) % comm_sz;
    int prev_rank = (my_rank - 1 + comm_sz) % comm_sz;

    // Send to the next process and receive from the previous one
    MPI_Send(&my_rank, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_rank, 1, MPI_INT, prev_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received rank %d from process %d\n", my_rank, recv_rank, prev_rank);

    MPI_Finalize();
    return 0;
}
