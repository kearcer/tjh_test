/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-11 20:48:50
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-12 11:43:13
 * @Description: test47_Inorder_traversal_check_BS_Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

Node *GetNode(int data)
{
    Node *tree = new Node();
    tree->data = data;
    tree->left = nullptr;
    tree->right = nullptr;
    return tree;
}

Node *Add(Node *tree, int data)
{
    if (tree == nullptr)
    {
        tree = GetNode(data);
        return tree;
    }
    else if (tree->data < data)
    {
        tree->right = Add(tree->right, data);
    }
    else if (tree->data > data)
    {
        tree->left = Add(tree->left, data);
    }
}

void LDR_Reversual_Print(Node *Tree)
{
    if (Tree == nullptr)
        return;
    LDR_Reversual_Print(Tree->left);
    printf("%d ", Tree->data);
    LDR_Reversual_Print(Tree->right);
}

template <typename T>
void LDR_Reversual_Vector(Node *Tree, std::vector<T> &V)
{
    if (Tree == nullptr)
        return;
    LDR_Reversual_Vector(Tree->left, V);
    V.push_back(Tree->data);
    LDR_Reversual_Vector(Tree->right, V);
}

template <typename T>
bool IsBSTree_Using_Vector(std::vector<T> V)
{
    for (int i = 0; i < V.size() - 1; i++)
    {
        if (V[i] > V[i + 1])
            return false;
    }
    return true;
}

int main()
{
    std::vector<int> vec;
    Node *Tree = nullptr;
    Tree = Add(Tree, 2);
    Tree = Add(Tree, 1);
    Tree = Add(Tree, 3);
    Tree = Add(Tree, 5);
    printf("reversal the tree\n");
    LDR_Reversual_Print(Tree);
    printf("\n");
    LDR_Reversual_Vector(Tree, vec);
    for (auto i : vec)
    {
        printf("%d ", i);
    }
    printf("Tree is BST:%d\n", IsBSTree_Using_Vector(vec));
    return 0;
}