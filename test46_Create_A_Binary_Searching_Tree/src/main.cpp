/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-05 16:03:36
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-05 19:08:14
 * @Description:test46_Create_A_Binary_Searching_Tree
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node *GetNewBSTNode(int data)
{
    Node *temp = new Node();
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node *Add(Node *head, int data)
{
    if (head == NULL)
        return GetNewBSTNode(data);
    else if (data < head->data)
    {
        head->left = Add(head->left, data);
        return head;
    }
    else if (data > head->data)
    {
        head->right = Add(head->right, data);
        return head;
    }
}

bool Search(Node *head, int data)
{
    if (head == NULL)
    {
        printf("want find %d, not find!\n", data);
        return 0;
    }
    else if (data < head->data)
    {
        return Search(head->left, data);
    }
    else if (data > head->data)
    {
        return Search(head->right, data);
    }
    else
    {
        printf("want find %d, find!\n", data);
        return true;
    }
}

void FindMin(Node *head)
{
    if (head == NULL)
    {
        printf("empty tree no min element\n");
        return;
    }
    while (head->left != NULL)
    {
        head = head->left;
    }
    printf("find min element:%d\n", head->data);
    return;
}

void FindMax(Node *head)
{
    if (head == NULL)
    {
        printf("empty tree no min element\n");
        return;
    }
    while (head->right != NULL)
    {
        head = head->right;
    }
    printf("find miax element:%d\n", head->data);
    return;
}

int main()
{
    Node *BSThead = NULL;
    BSThead = Add(BSThead, 2);
    BSThead = Add(BSThead, 3);
    BSThead = Add(BSThead, 4);
    BSThead = Add(BSThead, 7);
    BSThead = Add(BSThead, 8);
    BSThead = Add(BSThead, 10);
    BSThead = Add(BSThead, 13);
    Search(BSThead, 4);
    Search(BSThead, 5);
    FindMin(BSThead);
    Search(BSThead, 4);
    FindMax(BSThead);
    return 0;
}
