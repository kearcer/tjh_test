#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 

class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        vector<int> V;
        ListNode* temp = head;
        for(int i = 0; i < n; i++)
        {
            if(i>=(m-1))
            {
                V.push_back(temp->val);
            }
            temp = temp->next;
        }

        ListNode* temp1 = head;
        int k = 0;

        reverse(V.begin(), V.end());
        for(int i = 0; i < n; i++)
        {
            if(i>=(m-1))
            {
                temp1->val = V[k];
                k++;
            }
            temp1 = temp1->next;
        }
        return head;   
    }
};

int main()
{
    // create a linked list
    ListNode* head = new ListNode(1);
    ListNode* temp = head;
    for(int i = 2; i <= 5; i++)
    {
        temp->next = new ListNode(i);
        temp = temp->next;
    }

    // print the original linked list
    cout << "Original Linked List: ";
    temp = head;
    while(temp != NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    // reverse the linked list from position 2 to 4
    Solution s;
    head = s.reverseBetween(head, 2, 4);

    // print the reversed linked list
    cout << "Reversed Linked List: ";
    temp = head;
    while(temp != NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
}