/*
 * @Author: Jiahui Tang
 * @Date: 2022-06-24 09:43:17
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-06-24 15:11:15
 * @Description:
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
void ShowArr(int *arr, int len) //显示数组
{
	for (int i = 0; i < len; ++i)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void BubbleSort1(int *arr, int len)
{
	for (int i = 0; i < len - 1; ++i)
	{
		//一趟循环结束后，最大的数据被排到最后
		for (int j = 0; j < len - 1 - i; ++j) // len - 1 - i 每经过一趟排序，下一次就可以少比较一个数据
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

int main(int argc, char *argv[])
{
	char input[32];
	int reg_input[8] = {0};
	char device[8] = {0};
	int device_num = 4;
	int index = 0;
	printf("指定GPU:");
	scanf("%s", &input);
	int input_num = strlen(input);
	for (int i = 0; i < input_num; i++)
	{
		if (input[i] != ',')
		{
			reg_input[index] = atoi(&input[i]);
			index++;
		}
	}
	ShowArr(reg_input, index);

	return 0;
}