#include <stdio.h>
#include <mpi.h>

int main(void) {
    int comm_sz, my_rank;
    char message[100];

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0) {
        // Create message with rank and number of processes
        sprintf(message, "Process %d of %d", my_rank, comm_sz);
        MPI_Send(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        // Process 0 prints its own message
        printf("Process 0 of %d\n", comm_sz);
        // Receive and print the messages from other processes
        for (int q = 1; q < comm_sz; q++) {
            MPI_Recv(message, 100, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", message);
        }
    }

    MPI_Finalize();
    return 0;
}
