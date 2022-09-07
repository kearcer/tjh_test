#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	int sw_start = 1;
	char front_trunk[] = {0};
	char middle_trunk[100] = "ABD";
	char below_trunk[100] = "89ABC";
	memcpy(front_trunk, middle_trunk, strlen(middle_trunk));
	return 0;
}