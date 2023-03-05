/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-01 16:46:22
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-01 19:18:42
 * @Description:test44_Create_A_Queue_Using_LinkList
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

struct Node
{
    int data;
    struct Node *link;
};

class Queue
{
private:
    Node *m_head;
    Node *m_front;
    Node *m_rear;

public:
    Queue()
    {
        m_head = NULL;
        m_front = NULL;
        m_rear = NULL;
    }
    bool isEmpty()
    {
        if (m_front == NULL && m_rear == NULL)
            return true;
        else
            return false;
    }

    int enQueue(int data)
    {
        Node *guild = m_front;
        Node *temp = new Node();
        temp->data = data;
        temp->link = NULL;
        if (isEmpty())
        {
            m_front = m_rear = temp;
        }
        else
        {
            m_rear->link = temp;
            m_rear = temp;
        }

        return 0;
    }

    void deQueue()
    {
        if (isEmpty())
        {
            printf("There is no element to pop!\n");
            return;
        }
        else if (m_front = m_rear)
        {
            delete (m_front);
            m_rear = m_front = NULL;
        }
        else
        {
            Node *temp = m_front;
            m_front = m_front->link;
            delete (temp);
            temp = NULL;
        }
        return;
    }

    void PrintQueue()
    {
        if (m_front == NULL)
        {
            printf("no element to be print\n");
            return;
        }

        printf("Queue: ");
        Node *temp = m_front;
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
};

int main()
{
    Queue Q;
    Q.enQueue(1);
    Q.PrintQueue();
    Q.enQueue(2);
    Q.PrintQueue();
    Q.enQueue(3);
    Q.PrintQueue();
    Q.enQueue(4);
    Q.PrintQueue();
    Q.deQueue();
    Q.PrintQueue();
    Q.deQueue();
    Q.PrintQueue();
    Q.deQueue();
    Q.PrintQueue();
    printf("is empty: %d\n", Q.isEmpty());
    Q.deQueue();
    Q.PrintQueue();
    printf("is empty: %d\n", Q.isEmpty());
    Q.deQueue();
    Q.PrintQueue();
    printf("is empty: %d\n", Q.isEmpty());

    return 0;
}
