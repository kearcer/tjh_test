/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-21 18:29:47
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-21 19:29:26
 * @Description:Using a stack to reverse a array
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stack>

int Reverse_Using_Stack(int *arr, int len)
{
    std::stack<int> S;
    int *temp = arr;
    for (int i = 0; i < 10; i++)
    {
        S.push(arr[i]);
    }
    for (int i = 0; i < 10; i++)
    {
        arr[i] = S.top();
        S.pop();
    }
    return 0;
}

int Print_Arrar(int *arr)
{
    printf("当前数组: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Print_Arrar(array);
    Reverse_Using_Stack(array, 10);
    Print_Arrar(array);
}