#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int k;
	if (argc > 1) {
		k = atoi(argv[1]);
		printf("in %d\n", k);
	} else {
		return 0;
	}
	 
}
