#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int recursive(int i)
{
	int sum = 0;
	if (0 == i)
		return (1);
	else
		sum = i * recursive(i-1);
	return sum;
}

int main(int argc, char *argv[]) 
{
	int result = recursive(10);
	return 0;
}