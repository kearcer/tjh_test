/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-15 17:10:21
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-15 19:31:48
 * @Description:test48_Create_and_Get_BSTree_Sucessor
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *left;
    Node *right;
};

void TreePrint(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    TreePrint(node->left);
    printf("%d ", node->data);
    TreePrint(node->right);
}

Node *GetNewNode(int data)
{
    Node *temp = new Node();
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node *Add(Node *node, int data)
{
    if (node == NULL)
    {
        node = GetNewNode(data);
    }
    else if (node->data < data)
    {
        node->right = Add(node->right, data);
    }
    else if (node->data > data)
    {
        node->left = Add(node->left, data);
    }
    return node;
}

Node *FindMin(Node *node)
{
    if (node->left == NULL)
    {
        return node;
    }
    FindMin(node->left);
}

Node *FindData(Node *node, int data)
{
    if (node == NULL)
    {
        return NULL;
    }
    else if (node->data > data)
    {
        FindData(node->left, data);
    }
    else if (node->data < data)
    {
        FindData(node->right, data);
    }
    else
    {
        return node;
    }
}

Node *GetTheSucessor(Node *node, int data)
{
    Node *current = FindData(node, data);
    if (current == NULL)
    {
        return NULL;
    }
    else if (current->right != NULL)
    {
        Node *temp = FindMin(current->right);
        return temp;
    }
    else
    {
        Node *scessor = NULL;
        Node *acsestor = node;
        while (acsestor != current)
        {
            if (acsestor->data > current->data)
            {
                scessor = acsestor;
                acsestor = acsestor->left;
            }
            else
            {
                acsestor = acsestor->right;
            }
        }
        return scessor;
    }
}

int main()
{
    Node *head;
    head = Add(head, 5);
    head = Add(head, 1);
    head = Add(head, 2);
    head = Add(head, 7);
    head = Add(head, 9);
    head = Add(head, 6);

    printf("printf the bst tree:");
    TreePrint(head);
    printf("\n");

    Node *result = GetTheSucessor(head, 9);
    if (result != NULL)
        printf("the next node is :%d \n", result->data);
    else
        printf("ndoe is empty!\n");

    return 0;
}