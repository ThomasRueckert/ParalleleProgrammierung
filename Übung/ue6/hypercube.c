#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int getRightChild(int me)
{
  return (me << 1) + 1;
}

int getLeftChild(int me)
{
  return (me << 1);
}

int getParent(int me)
{
  return (me >> 1);
}

int main(int argc, char** argv) {
  int rank, size; //I am process RANK and we are a total of SIZE
  MPI_Init(&argc, &argv); 

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  ////HYPERCUBE
  
  MPI_Comm nthCube;
  int nDim=5;
  int processPerDim [5]= {2,2,2,2,2};
  int period [5]= {0,0,0,0,0};

  MPI_Cart_create(MPI_COMM_WORLD, nDim, processPerDim, period, false, &nthCube);

  int rankInDim;
  MPI_Comm_rank(nthCube, &rankInDim);
  
  ////END HYPERCUBE
  
  
  ////TREE
  
  //int lc = getLeftChild(rank);
  //int rc = getRightChild(rank);
  //int f = getParent(rank);
  //create comm with rank, lc and rc
  
  //for broadcasting
  //wait for input from f and the send it to lc and rc
  
  //for reduce first spread like broadcast and the return by reducing the answer of lc and rc and then sending it to f
  
  ////END TREE
  
  MPI_Finalize();
}

