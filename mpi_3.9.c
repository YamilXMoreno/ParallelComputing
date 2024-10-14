#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void Read_vector(double* vector, int n);

int main(int argc, char* argv[]) {
    int comm_sz, my_rank, n;
    double scalar, *vector = NULL, local_dot = 0.0, global_dot = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        printf("Enter the size of the vector: ");
        scanf("%d", &n);
        printf("Enter the scalar: ");
        scanf("%lf", &scalar);
        vector = malloc(n * sizeof(double));
        Read_vector(vector, n);
    }

    // Broadcast the scalar and vector size
    MPI_Bcast(&scalar, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Allocate memory for local vector
    double* local_vector = malloc(n / comm_sz * sizeof(double));

    // Scatter the vector to all processes
    MPI_Scatter(vector, n / comm_sz, MPI_DOUBLE, local_vector, n / comm_sz, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Compute local dot product and scalar multiplication
    for (int i = 0; i < n / comm_sz; i++) {
        local_vector[i] *= scalar;
        local_dot += local_vector[i]; // Calculate dot product
    }

    // Reduce to get the global dot product
    MPI_Reduce(&local_dot, &global_dot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 prints the results
    if (my_rank == 0) {
        printf("Global dot product: %lf\n", global_dot);
        printf("Scalar multiplied vector:\n");
        for (int i = 0; i < n; i++) {
            printf("%lf ", vector[i] * scalar);
        }
        printf("\n");
        free(vector);
    }

    free(local_vector);
    MPI_Finalize();
    return 0;
}

void Read_vector(double* vector, int n) {
    printf("Enter the vector elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vector[i]);
    }
}
