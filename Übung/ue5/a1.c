
 #include <mpi.h>
 #include <stdio.h>

 #define false 0
 #define true  1

 #define SIZE  24
 #define DIM   3
 #define DIM_0 2
 #define DIM_1 3
 #define DIM_2 4

 int main (int argc, char** argv)
 {
    int num_tasks;

    char hostname[80];

    int dims[DIM];
    dims[0] = DIM_0;
    dims[1] = DIM_1;
    dims[2] = DIM_2;

    int periods[DIM] = {false, false, false};
    int reorder = true;
    int my_rank;

    int coords[DIM];

    MPI_Comm cartcomm, y_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);

    if (num_tasks != SIZE) {
        if (my_rank == 0) {
            printf("We need %d proccesses, %d given. Exiting.\n", SIZE, num_tasks);
        }
        
        MPI_Finalize();

		return 0;
        
    }         
    
    gethostname(hostname, 79);
	MPI_Cart_create(MPI_COMM_WORLD, DIM, dims, periods, reorder, &cartcomm);
	MPI_Cart_coords(cartcomm, my_rank, DIM, coords);
	printf("%-15.12s: MPI_COMM_WORLD rank %2d: (%d, %d, %d)\n", hostname, my_rank, coords[0], coords[1], coords[2]);
	
	//neighbors
	int src, dest;
	for (int i = 0; i < 3; i++) {
		MPI_Cart_shift(cartcomm, i, +1, src, dest);
		printf("i am %d and my right neighbor in %d is %d", dest, i, src);
		MPI_Cart_shift(cartcomm, i, -1, src, dest);	
		printf("i am %d and my left neighbor in %d is %d", dest, i, src);
	}
	
	
	int keep_dims[1];
	keep_dims[0] = 1;
	MPI_Cart_sub(cartcomm, keep_dims, &y_comm);
	printf("%d: my y rank is %d", my_rank, coords[1]);

    MPI_Finalize();

    return 0;
 }
