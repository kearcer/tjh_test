/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-28 14:37:39
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-28 16:20:42
 * @Description:Create_A_Queue_Using_Array
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MAXSIZE 10
int front = -1;
int rear = -1;
int Arr[MAXSIZE];

bool Isempty()
{
    if (front == -1 && rear == -1)
        return true;
    else
        return false;
    return 0;
}

int EnQueue(int data)
{
    if (Isempty())
    {
        Arr[0] = data;
        front = rear = 0;
    }
    else if ((rear + 1) % MAXSIZE == front)
    {
        printf("the queue is full! no element can be sent in\n");
    }
    else
    {
        rear++;
        Arr[rear % 10] = data;
    }
    return 0;
}

int DeQueue()
{
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % 10;
    }
    return 0;
}

int ShowQueue()
{
    printf("queue:");
    if (Isempty())
    {
        printf("Empty queue,no element to show!");
    }
    else
    {
        for (int i = front; i <= rear; i++)
            printf("%d ", Arr[i]);
    }
    printf("\n");
    return 0;
}

int main()
{
    EnQueue(0);
    ShowQueue();
    EnQueue(1);
    ShowQueue();
    EnQueue(2);
    ShowQueue();
    EnQueue(3);
    ShowQueue();
    EnQueue(4);
    ShowQueue();
    EnQueue(5);
    ShowQueue();
    EnQueue(6);
    ShowQueue();
    EnQueue(7);
    ShowQueue();
    EnQueue(8);
    ShowQueue();
    EnQueue(9);
    ShowQueue();
    DeQueue();
    EnQueue(10);
    ShowQueue();
    EnQueue(11);

    return 0;
}