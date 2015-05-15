#include <mpi.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    MPI_Init(&argc,&argv);
    int rank, comm_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    char hostname[256];
    gethostname(hostname, 255);

    printf("Rang: %d, size: %d, hostname: %s", rank, comm_size, hostname);

    MPI_Finalize();
    return 0;
}
