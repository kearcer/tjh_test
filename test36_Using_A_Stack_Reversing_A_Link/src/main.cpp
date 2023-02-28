/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-23 18:02:34
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-23 18:42:53
 * @Description:Change_The_midsniff_To_Presniff
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

struct Node
{
    int data;
    struct Node *link;
};
Node *head = NULL;

void AddNode(int data)
{
    Node *temp = head;
    Node *nodenew = new Node();
    nodenew->data = data;
    nodenew->link = NULL;
    if (head == NULL)
    {
        head = nodenew;
    }
    else
    {
        nodenew->link = head;
        head = nodenew;
    }
    return;
}

void PrintNode()
{
    Node *temp = head;
    printf("当前的链表：");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
    return;
}

void ReversingUseStack()
{
    std::stack<Node *> S;
    Node *temp = head;
    while (temp != NULL)
    {
        S.push(temp);
        temp = temp->link;
    }

    head = S.top();
    temp = head;

    while (S.top() != NULL)
    {
        S.pop();
        if (S.empty() == 1)
        {
            temp->link = NULL;
            return;
        }

        temp->link = S.top();
        temp = S.top();
    }
    return;
}

int main()
{
    AddNode(6);
    PrintNode();
    AddNode(4);
    PrintNode();
    AddNode(2);
    PrintNode();
    AddNode(1);
    PrintNode();
    ReversingUseStack();
    PrintNode();
}