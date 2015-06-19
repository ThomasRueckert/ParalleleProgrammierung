 #include <mpi.h>
 #include <stdio.h>
 
/*
 * vorher: 
 * MPI_GET auf dem master Prozess ausgeführt
 * dieser muss stets von allen 4 anderen empfangen
 * 
 * jetzt:
 * MPI_PUT durch die slaves durchgeführt
 * master liest nur aus dem Speicher die Werte aus
 */
 
 
int main (int argc, char** argv)
{
  
   int my_rank, num_tasks;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_tasks); 

   //...
   double w = rank;
   int m;
   int left, right, up, down; //neighbours
   //...
   
   MPI_Win win;
   MPI_Win_create(&w, sizeof(double), sizeof(double), MPI_INFO_NULL, Comm_2d, &win);
   MPI_Win_fence(MPI_MODE_NOPRECEDE, win);
   
   for (int z = 0; z < m; z++) {
  
     double buff[4];
     MPI_Get(&buff[0], 1, MPI_DOUBLE, left, 0, 1, MPI_DOUBLE, win);
     MPI_Get(&buff[1], 1, MPI_DOUBLE, right, 0, 1, MPI_DOUBLE, win);
     MPI_Get(&buff[2], 1, MPI_DOUBLE, up, 0, 1, MPI_DOUBLE, win);
     MPI_Get(&buff[3], 1, MPI_DOUBLE, down, 0, 1, MPI_DOUBLE, win);
     
     MPI_Win_fence(0, win);
     
     w = 0.0;
     for (int i = 0; i < 4; i++) {
       w += buff[i];
    }
     w /= 4;
     
  }
   MPI_Win_free(&win);
   
   MPI_Finalize();
  
   return 0;
}