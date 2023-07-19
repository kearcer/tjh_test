/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-17 21:37:00
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-17 21:58:15
 * @Description:
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_ARR_LEN 10
int arr[MAX_ARR_LEN];
int top = -1;

void Push(int n)
{
    arr[++top] = n;
    return;
}

void Pop()
{
    if (top == -1)
    {
        printf("no element could be pop!\n");
    }
    else
    {
        --top;
    }
}

int Top()
{
    return top;
}

bool Isempty()
{
    if (top == -1)
        return true;
    else
        return false;
}

void Print_Arr()
{
    if (top > -1)
    {
        printf("array: ");
        for (int i = 0; i <= top; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
}

int main()
{
    bool is_emp = false;
    Push(1);
    Print_Arr();
    Push(10);
    Print_Arr();
    Push(100);
    Print_Arr();
    Push(1000);
    Print_Arr();
    Pop();
    Print_Arr();
    Pop();
    Print_Arr();
    is_emp = Isempty();

    return 0;
}