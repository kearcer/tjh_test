/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-05 16:03:36
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-10 22:05:14
 * @Description:test46_Create_A_Binary_Searching_Tree
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>
#include <limits.h>

#define MAX(a, b) a > b ? a : b

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

int PrintHeight(Node *head)
{
    if (head == NULL)
    {
        // printf("tree height is 0\n");
        return -1;
    }
    else
        return MAX(PrintHeight(head->left), PrintHeight(head->right)) + 1;
}

void Hierarchical_traversal(Node *head)
{
    printf("tree: ");
    std::queue<Node *> Q;
    Node *LfetNode = NULL;
    Node *RightNode = NULL;
    if (head == NULL)
    {
        printf("end tree\n");
        return;
    }
    else
    {
        Q.push(head);
        while (Q.empty() != 1)
        {
            printf("%d ", Q.front()->data);
            LfetNode = Q.front()->left;
            RightNode = Q.front()->right;
            if (LfetNode != NULL)
            {
                Q.push(LfetNode);
            }
            if (RightNode != NULL)
            {
                Q.push(RightNode);
            }
            Q.pop();
        }
    }
    printf("\n");
    return;
}

void DLR_traversal(Node *head)
{
    if (head == NULL)
        return;
    printf("%d ", head->data);
    DLR_traversal(head->left);
    DLR_traversal(head->right);
    return;
}

void DLR_traversal_Using_Stack(Node *head)
{
    printf("DLR tree using stack: ");
    std::stack<Node *> S;
    if (head == NULL)
        return;
    else
    {
        S.push(head);
        while (S.empty() != 1)
        {
            Node *element = S.top();
            printf("%d ", element->data);
            S.pop();
            if (element->right)
                S.push(element->right);
            if (element->left)
                S.push(element->left);
        }
    }
    printf("\n");
    return;
}

void LDR_traversal(Node *head)
{
    if (head == NULL)
        return;
    DLR_traversal(head->left);
    printf("%d ", head->data);
    DLR_traversal(head->right);
    return;
}

void LDR_traversal_Using_Stack(Node *head)
{
    printf("LDR tree using stack: ");
    std::stack<Node *> S;
    if (head == NULL)
        return;
    else
    {
        while (S.empty() != 1 || head != NULL)
        {
            while (head != NULL)
            {
                S.push(head);
                head = head->left;
            }
            head = S.top();
            printf("%d ", head->data);
            S.pop();
            head = head->right;
        }
    }
    printf("\n");
    return;
}

void LRD_traversal(Node *head)
{
    if (head == NULL)
        return;
    LRD_traversal(head->left);
    LRD_traversal(head->right);
    printf("%d ", head->data);
    return;
}

void LRD_traversal_Using_Stack(Node *head)
{
    printf("RDL tree using stack: ");
    std::stack<Node *> S;
    std::stack<Node *> S_rev;
    if (head == NULL)
        return;
    else
    {
        S.push(head);
        while (S.empty() != 1)
        {
            Node *top = S.top();
            S_rev.push(top);
            S.pop();
            if (top->left != NULL)
                S.push(top->left);
            if (top->right != NULL)
                S.push(top->right);
        }
        while (S_rev.empty() != 1)
        {
            printf("%d ", S_rev.top()->data);
            S_rev.pop();
        }
    }
    printf("\n");
    return;
}

bool IsLesserthanRoot(Node *head, int root)
{
    if ((head == NULL) || ((head->data <= root) && IsLesserthanRoot(head->left, root) && IsLesserthanRoot(head->right, root)))
        return true;
    else
        return false;
}

bool IsGreaterthanRoot(Node *head, int root)
{
    if (head == NULL || ((head->data > root) && IsGreaterthanRoot(head->left, root) && IsGreaterthanRoot(head->right, root)))
        return true;
    else
        return false;
}

bool IsBSTree(Node *head, int a = INT_MAX, int b = INT_MIN)
{
    if (head == NULL)
    {
        return true;
    }
    else if (head->data > b && head->data < a &&
             IsBSTree(head->left) && IsBSTree(head->right))
    {
        return true;
    }
    else
        return false;
}

int main()
{
    Node *BSThead = NULL;
    BSThead = Add(BSThead, 8);
    BSThead = Add(BSThead, 2);
    BSThead = Add(BSThead, 4);
    BSThead = Add(BSThead, 7);
    BSThead = Add(BSThead, 10);
    BSThead = Add(BSThead, 13);
    Search(BSThead, 4);
    Search(BSThead, 5);
    FindMin(BSThead);
    Search(BSThead, 4);
    FindMax(BSThead);
    printf("height of tree %d\n", PrintHeight(BSThead));
    Hierarchical_traversal(BSThead);
    printf("DLR tree using traversal:");
    DLR_traversal(BSThead);
    printf("\n");
    DLR_traversal_Using_Stack(BSThead);

    printf("LDR tree using traversal:");
    LDR_traversal(BSThead);
    printf("\n");
    LDR_traversal_Using_Stack(BSThead);

    printf("RDL tree using traversal:");
    LRD_traversal(BSThead);
    printf("\n");
    LRD_traversal_Using_Stack(BSThead);

    bool flag = IsBSTree(BSThead);
    if (flag == false)
        printf("not a BST tree\n");
    else if (flag == true)
        printf("is a BST tree\n");

    return 0;
}
