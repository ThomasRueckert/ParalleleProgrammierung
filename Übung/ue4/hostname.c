#include <mpi.h>
#include <unistd.h>
#include <stdio.h>

/**
 * this is a little mpi and chich how-to
 *
 * ssh chiclogin1.informatik.tu-chemnitz.de
 *
 * nur einmalig:
 * module initadd comp/gcc/422
 * module initadd mpi/openmpi/gcc422
 *
 * programm aus dem afs in die aktuelle directory kopieren
 * (/afs/tu-chemnitz.de/home/urz/[anfangsbuchstabe-vom-kürzel]/[urz-kürzel]/...)
 *
 * compilieren: mpicc programm.c -o programmname
 * anfordern von Knoten: qsub -I -l nodes=X:ppn=1,walltime=00:20:00 -q short
 * starten: mpirun -np X ./programmname
 */
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
