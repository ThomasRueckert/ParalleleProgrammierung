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
   
   for (int z = 0; z < m; z++) {
  
     double buff = w;
     w=0.0;
     MPI_Win_fence(0,win);
     
     MPI_Accumulate(&buff, 1, MPI_DOUBLE, left, 0, 1, MPI_DOUBLE, MPI_SUM, win);
     MPI_Accumulate(&buff, 1, MPI_DOUBLE, right, 0, 1, MPI_DOUBLE, MPI_SUM, win);
     MPI_Accumulate(&buff, 1, MPI_DOUBLE, up, 0, 1, MPI_DOUBLE, MPI_SUM, win);
     MPI_Accumulate(&buff, 1, MPI_DOUBLE, down, 0, 1, MPI_DOUBLE, MPI_SUM, win);
     
     MPI_Win_fence(0, win);
     
     w /= 4;
     
  }
   MPI_Win_free(&win);
   
   MPI_Finalize();
  
   return 0;
}