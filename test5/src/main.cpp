#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	char front_trunk[100] = "123";
	char middle_trunk[100] = "4567";
	char below_trunk[100] = "89ABC";
	memcpy(middle_trunk+4, below_trunk, 5);
	memcpy(front_trunk+3, middle_trunk, 9);

	return 0;
}