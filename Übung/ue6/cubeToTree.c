#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

const char *byte_to_binary(int x, int dim)
{
    static char b[12];
    b[0] = '\0';

    int z;
    for (z = pow(2, dim-1); z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

extern int pntr = 0;
extern int maxDepth = 0;
extern int dPntr = 0;

void printfAllKids(int root, int count, int dim, int connected[], int depth, int deptharr[])
{
  connected[pntr] = root; pntr++;
  if (maxDepth < depth) maxDepth=depth;
  int *childs = malloc(sizeof(int)*dim);
  int locCount = 0;
  for (int i = count-1; i >= 0; i--) {
    int mask = 1 << i;
    int newRoot = (mask ^ root);
    int exists = false;
    for (int j = 0; j < pow(2, dim); j++) {
      if (newRoot == connected[j]) {
	exists = true;
      }
    }
    if (!exists) {
      childs[locCount++] = newRoot;
    }
  }
  for (int i = 0; i < locCount; i++) {
     //printf("%s, ", byte_to_binary(childs[i], dim));
  }
    deptharr[dPntr++]=locCount;
//     printf("\n");
  for (int i = 0; i < locCount; i++) {

      printfAllKids(childs[i], count-i-1, dim, connected, (depth+1), deptharr);


  }
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("give as first arg the hypercube dimensions and second the root address as integer\n");
    return -1;
  }
  int dim = atoi(argv[1]);
  int cubeSize = pow(2, dim);
  if (dim > 11) {
    printf("size too big\n");
    return -1;
  }
  int root = atoi(argv[2]);
  if (cubeSize <= root || 0 > root) {
    printf("root out of size\n");
    return -1;
  } 
  printf("dim is %d and root is %d\n", dim, root);
  //create tree
   //printf("%s\n", byte_to_binary(root, dim));
  int *connected = malloc(sizeof(int)*cubeSize);
  int *depth = malloc(sizeof(int)*cubeSize);
  int *brCount = malloc(sizeof(int)*cubeSize);
  pntr = 0;
  int depthC = 1;
  //printf("--->%d\n", ( void * )pntr);
  depth[dPntr++]=1;
  printfAllKids(root, dim, dim, connected, depthC, depth);
  //printf("%d\n",pntr);
  for (int i = 0; i < cubeSize; i++) {
    //printf("%d, %s\n", depth[i], byte_to_binary(connected[i], dim));
  }
  for (int i = 1; i < cubeSize; i++) {
      printf("%s, ", byte_to_binary(connected[i], dim));
    if (depth[i] == i) {
      printf("\n");
    }
  }

  
  return 0;
}