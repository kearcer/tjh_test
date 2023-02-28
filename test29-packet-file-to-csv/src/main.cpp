/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-11-08 10:54:40
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <type_traits>
#include <memory>
#include <stdio.h>
#include <stack>
#include <string>
#include <queue>
#include <cstring>
#include <math.h>
#include <mutex>
#include <thread>
using namespace std;

void writeExcel()
{
	char chy[4] = {'x', 'a', 'h', 'w'};
	float data[4] = {0.1, 0.3, 0.6, 0.9};
	int i;

	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			static char file_output[128];
			memset(file_output, 0, 128);
			sprintf(file_output, "./obj/output%d%dthread%d.csv", 1920, 1080, 1);
			FILE *fp = NULL;
			fp = fopen(file_output, "w");
			fprintf(fp, "%c\t%0.3f\n", chy[i], data[i]);
			fclose(fp);
		}
		else
		{
			static char file_output[128];
			memset(file_output, 0, 128);
			sprintf(file_output, "./obj/output%d%dthread%d.csv", 1920, 1080, 1);
			FILE *fp = NULL;
			fp = fopen(file_output, "a");
			fprintf(fp, "%c\t%0.3f\n", chy[i], data[i]);
			fclose(fp);
		}
	}
}
int main()
{
	writeExcel();
	return 0;
}