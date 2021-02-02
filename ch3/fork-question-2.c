/**
 * Solution to exercise 3.2
 *
 **/

#include <stdio.h>

int main()
{
	printf("%d\n",getpid());
	fork();
	printf("%d\n",getpid());
	

	fork();
	printf("%d\n",getpid());

	fork();
	printf("%d\n",getpid());

	return 0;
}
