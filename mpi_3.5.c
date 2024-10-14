#include <stdio.h>
#include <mpi.h>

int main(void) {
    int comm_sz, my_rank;
    char message[100] = "Hello from process 0";

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        MPI_Send(message, 100, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(message, 100, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (my_rank < comm_sz - 1) {
            MPI_Send(message, 100, MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    printf("Process %d received message: %s\n", my_rank, message);

    MPI_Finalize();
    return 0;
}
