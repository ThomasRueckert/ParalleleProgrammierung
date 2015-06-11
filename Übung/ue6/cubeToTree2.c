#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int nmbrsPntr = 1;

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

int rec(int nmbrs[], int father[], int cubeSize)
{
  int tmp;
  for (int i = 0; i < cubeSize; i++) {
    if (nmbrsPntr > cubeSize) {
      break;
    }
    tmp = nmbrs[i];
    for (int j = tmp-1; j > 0; j--) {
      nmbrs[nmbrsPntr] = j;
      father[nmbrsPntr] = i;
      nmbrsPntr++;
    }
  }
}

int shift(int nmbrs[], int father[], int index[], int cubeSize, int dim)
{
  int tmpFather;
  int tmpIndex;
  int tmpNmbrs;
  int mask;
  for (int i = 1; i < cubeSize; i++) 
  {
    tmpFather = father[i];
    tmpIndex = index[tmpFather];
    tmpNmbrs = nmbrs[i];
    mask = 1 << (tmpNmbrs-1);
    index[i] = (mask ^ tmpIndex);
  }
  for (int i = 0; i < cubeSize; i++) {
    printf("[%d] %d (%d) - %s\n", i, nmbrs[i], father[i], byte_to_binary(index[i], dim));
  }
}

int main(int argc, char** argv) {
  
  if (argc != 3) {
    printf("give as first arg the hypercube dimensions and second the root address as integer\n");
    return -1;
  }
  
  int dim = atoi(argv[1]);
  int root = atoi(argv[2]);
  int cubeSize = pow(2, dim);
  
  int *nmbrs = malloc(sizeof(int) * cubeSize);
  int *father = malloc(sizeof(int) * cubeSize);
  int *index = malloc(sizeof(int) * cubeSize);
  
  nmbrs[0] = dim+1;
  father[0] = -1;
  index[0] = root;
  
  rec(nmbrs, father, cubeSize);
  shift(nmbrs, father, index, cubeSize, dim);
  
  return 0;
}