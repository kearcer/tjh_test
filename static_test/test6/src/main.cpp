#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	int sw_start = 1;
	char front_trunk[100] = "ABC";
	char middle_trunk[100] = "ABD";
	char below_trunk[100] = "89ABC";
	int out = memcmp(front_trunk, middle_trunk, strlen(middle_trunk));
	bool out1 = (-1 != 0);
	if (sw_start == 1)
	{
		bool result = (memcmp(front_trunk, middle_trunk, strlen(middle_trunk)) != 0);
	}


	return 0;
}