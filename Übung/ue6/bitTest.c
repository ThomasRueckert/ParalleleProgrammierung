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
    int a = 4;
    printf("shift left %d and shift right %d\n", (a << 1), (a >> 1));
    printf("father %d, left c %d and right c %d\n", getParent(a), getLeftChild(a), getRightChild(a));
}
