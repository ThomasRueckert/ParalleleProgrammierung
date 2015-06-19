 #include <mpi.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <time.h>

void heartbeat_master() {
  long *timestamps;
  MPI_Alloc_mem(sizeof(long)*(MPI_Comm_size()-1), MPI_INFO_NULL, &timestamps);
  for (int i = 0; i < MPI_Comm_size()-1; i++) {
    timestamps[i] = 0;
  }
  MPI_Win win;
  MPI_Win_create(timestamps, sizeof(long)*(MPI_Comm_size()-1), sizeof(long), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  int workers_alive;
  
  while(true) {
    sleep(1);
    time_t current_time = time();
    
    for (int k=0; k < 100; k++) {
      int flag;
      MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, MPI_STATUS_IGNORE);
    }
    
    workers_alive = 0;
    //MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0,0, win);
    for (int i = 0; i < MPI_Comm_size()-1; i++) {
      if (current_time - timestamps[i] <= 3) {
	workers_alive++;
      } else {
	printf("worker %d died\n", i+1);
      }      
    }
    //MPI_Win_unlock(0, win);
    if (workers_alive <= 0) {
      break;
    }
  }
  
  MPI_Win_free(&win);
  
}
 
void heartbeat_worker() {
  MPI_Win win;
  MPI_Win_create(NULL,0,1,MPI_INFO_NULL,MPI_COMM_WORLD,&win);
  while (1) {
    time_t current_time; time(&current_time);
    long t = current_time;
    MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, win);
    MPI_Put(&t, 1, MPI_LONG, 0, rank-1, 1, MPI_LONG, win);
    MPI_Win_unlock(0, win);
    sleep(1);
  }
  MPI_Win_free(&win);
}
 
int main (int argc, char** argv)
 {
  
   int my_rank, num_tasks;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_tasks); 
 
   int window[];
   time_t start = time();
   
   if (num_tasks > 1) {
  
     
      if (my_rank == 0) {
	
	  heartbeat_master();
	
      } else {
	
	  heartbeat_worker();
	
      }
      
     
   }
   
   MPI_Finalize();

   return 0;
 }