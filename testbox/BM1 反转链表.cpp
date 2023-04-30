#include <stdlib.h>
#include <stdio.h>
#include <iostream>


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
		ListNode* pre = NULL;
        ListNode* current = pHead;
        ListNode* post = pHead;

        while(current != NULL)
        {
            post = current->next;
            current->next = pre;
            pre = current;
            current = post;
        }
        pHead = pre;
        return pHead;
    }
};

int main()
{
    printf("hello world!\n");
    return 0;
}