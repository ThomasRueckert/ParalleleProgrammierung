#include <mpi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    MPI_Init(&argc,&argv);
    int rank, comm_size;
    char hostname[256];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    char* hostnames;
    if(rank == 0) {
        hostnames = (char*) malloc(256*comm_size);
    }

    MPI_Gather(hostname, 256, MPI_CHAR, hostnames, 256, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int i;
        for (i = 0; i < comm_size; i++) {
            printf("process %d: host %s\n", i, &hostnames[i*256]);
        }
    }

    MPI_Finalize();
    return 0;
}
