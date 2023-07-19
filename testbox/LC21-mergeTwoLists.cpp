/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-19 15:18:26
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-19 16:13:09
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>

struct ListNode
{
    int val;
    struct ListNode *next;
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *list3 = nullptr;
        ListNode *temp1 = list1;
        ListNode *temp2 = list2;

        if (list1 == nullptr)
            return list2;
        else if (list2 == nullptr)
            return list1;
        else
        {
            while (list1 != nullptr && list2 != nullptr)
            {
                if (list1->val == list2->val)
                {
                    list3 = Add(list3, list1->val);
                    list3 = Add(list3, list2->val);
                    list1 = list1->next;
                    list2 = list2->next;
                }
                else if (list1->val > list2->val)
                {
                    while (list2 != nullptr && list1->val >= list2->val)
                    {
                        list3 = Add(list3, list2->val);
                        list2 = list2->next;
                    }
                    list3 = Add(list3, list1->val);
                    list1 = list1->next;
                }
                else if (list1->val < list2->val)
                {
                    while (list1 != nullptr && list1->val <= list2->val)
                    {
                        list3 = Add(list3, list1->val);
                        list1 = list1->next;
                    }
                    list3 = Add(list3, list2->val);
                    list2 = list2->next;
                }
            }

            while (list1 != nullptr)
            {
                list3 = Add(list3, list1->val);
                list1 = list1->next;
            }
            while (list2 != nullptr)
            {
                list3 = Add(list3, list2->val);
                list2 = list2->next;
            }
        }
        return list3;
    }

    ListNode *Add(ListNode *list, int value)
    {
        ListNode *temp = list;
        if (temp == nullptr)
        {
            temp = GetNewNode(value);
            return temp;
        }
        else
        {
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = GetNewNode(value);
        }
        return list;
    }
    ListNode *GetNewNode(int value)
    {
        ListNode *Node = new ListNode();
        Node->val = value;
        Node->next = nullptr;
        return Node;
    }
};

int main()
{
    ListNode *Node1 = nullptr;
    ListNode *Node2 = nullptr;
    ListNode *Node3 = nullptr;
    // 创建一个解决方案对象
    Solution sol;
    // Node1 = sol.Add(Node1, 1);
    Node1 = sol.Add(Node1, 1);
    // Node1 = sol.Add(Node1, 4);

    Node2 = sol.Add(Node2, 2);
    // Node2 = sol.Add(Node2, 3);
    // Node2 = sol.Add(Node2, 4);

    Node3 = sol.mergeTwoLists(Node1, Node2);

    return 0;
}