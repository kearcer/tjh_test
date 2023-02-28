/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-12 14:24:24
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-14 19:45:22
 * @Description:
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct Node
{
	int data;
	struct Node *Next;
};
struct Node *head;
void Insert(int n)
{
	Node *temp = head;
	Node *temp1 = new Node();
	temp1->data = n;
	temp1->Next = NULL;
	temp1->Next = head;
	head = temp1;
	return;
}

void Print()
{
	Node *temp = head;
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->Next;
	}
	printf("\n");
}

void Delete(int n)
{
	Node *temp = head;
	if (n == 1 && temp->Next != NULL)
	{
		temp = temp->Next;
		head = temp;
	}
	else if (n >= 2)
	{
		Node *temp1 = head;
		int len = 0;
		while (temp1 != NULL)
		{
			len++;
			temp1 = temp1->Next;
		}
		if (len < n)
		{
			printf("out of range!\n");
			return;
		}

		for (int m = 0; m < n - 2; m++)
		{
			temp = temp->Next;
		}
		temp->Next = temp->Next->Next;
	}
}

void Recurencive()
{
	Node *pre = NULL;
	Node *current = head;
	Node *post = head;
	while (current != NULL)
	{
		post = current->Next;
		current->Next = pre;
		pre = current;
		current = post;
	}
	head = pre;
	// return;
}

void Recurencive_recursive(Node *p)
{
	if (p->Next == NULL)
	{
		head = p;
		return;
	}
	Recurencive_recursive(p->Next);
	Node *q = p->Next;
	q->Next = p;
	p->Next = NULL;
}

void Print_recursive(Node *p)
{
	if (p->Next == NULL)
	{
		printf("%d ", p->data);
		return;
	}
	printf("%d ", p->data);
	Print_recursive(p->Next);
}

void Print_recursive_back(Node *p)
{
	if (p->Next == NULL)
	{
		printf("%d ", p->data);
		return;
	}

	Print_recursive_back(p->Next);
	printf("%d ", p->data);
}

int main(int argc, char *argv[])
{
	Print();
	Insert(100);
	Print();
	Insert(200);
	Print();
	Insert(300);
	Print();
	// Delete(3);
	Recurencive();
	Print();
	Print_recursive(head);
	printf("\n");
	Print_recursive_back(head);
	printf("\n");
	Recurencive_recursive(head);
	Print();
}