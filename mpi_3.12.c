#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int comm_sz, my_rank, sum, temp_val;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Initialize your value
    temp_val = my_rank + 1; // For example

    sum = temp_val;
    for (int i = 1; i < comm_sz; i++) {
        MPI_Sendrecv_replace(&temp_val, 1, MPI_INT, (my_rank + 1) % comm_sz, 0,
                             (my_rank - 1 + comm_sz) % comm_sz, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sum += temp_val;
    }

    printf("Process %d has total sum: %d\n", my_rank, sum);
    MPI_Finalize();
    return 0;
}
