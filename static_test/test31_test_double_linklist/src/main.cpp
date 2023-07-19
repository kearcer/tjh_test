/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-15 15:50:34
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-15 22:35:44
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *preNode;
	struct Node *postNode;
};

Node *GetNewNode(int data)
{
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->data = data;
	temp->preNode = NULL;
	temp->postNode = NULL;
	return temp;
}

void AddfrontNode(Node *&p, int data)
{
	Node *temp = GetNewNode(data);
	if (p == NULL)
	{
		p = temp;
	}
	else
	{
		temp->postNode = p;
		p->preNode = temp;
		p = temp;
	}
}

void Printdoublelink(Node *p, bool direct)
{
	Node *temp = p;
	if (direct == 0)
	{
		printf("正向打印：");
		while (temp != NULL)
		{
			printf("%d ", temp->data);
			temp = temp->postNode;
		}
		printf("\n");
	}
	else
	{
		printf("反向打印：");
		{
			while (temp->postNode != NULL)
			{
				temp = temp->postNode;
			}
			while (temp != NULL)
			{
				printf("%d ", temp->data);
				temp = temp->preNode;
			}
		}
		printf("\n");
	}
}

int main()
{
	Node *head;
	AddfrontNode(head, 2);
	Printdoublelink(head, 0);
	Printdoublelink(head, 1);
	AddfrontNode(head, 3);
	Printdoublelink(head, 0);
	Printdoublelink(head, 1);
	AddfrontNode(head, 4);
	Printdoublelink(head, 0);
	Printdoublelink(head, 1);
}