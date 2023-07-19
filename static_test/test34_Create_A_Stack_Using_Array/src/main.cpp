/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-18 16:44:50
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-18 17:12:04
 * @Description:
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
struct Node
{
    int data;
    struct Node *link;
};

Node *head = NULL;

void Push(int data)
{
    Node *temp = new Node();
    temp->data = data;
    if (head == NULL)
    {
        head = temp;
        return;
    }
    temp->link = head;
    head = temp;
    return;
}

void Pop()
{
    if (head == NULL)
    {
        printf("no element could be delete\n");
    }
    else
    {
        Node *temp = head;
        if (head->link == NULL)
        {
            free(temp);
            return;
        }
        else
        {
            head = temp->link;
            free(temp);
            return;
        }
    }
}

int Top()
{
    if (head == NULL)
        return -1;
    else
        return head->data;
}

bool IsEmpty()
{
    if (head == NULL)
        return true;
    else
        return false;
}

void Print_Stack()
{
    Node *temp = head;
    printf("Stack: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main()
{
    Push(10);
    Print_Stack();
    Push(100);
    Print_Stack();
    Push(1000);
    Print_Stack();
    int a = Top();
    printf("Top: %d\n", a);
    Pop();
    Print_Stack();
    Pop();
    Print_Stack();

    int b = Top();
    printf("Top: %d\n", b);
    bool c = IsEmpty();
    printf("Empty?: %d\n", c);
}