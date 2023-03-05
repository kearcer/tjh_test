/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-02 14:37:07
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-02 15:00:12
 * @Description:
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory> // 引入智能指针头文件
struct Node
{
    int data;
    std::shared_ptr<Node> link; // 使用shared_ptr代替原始指针
};
class Queue
{
private:
    std::shared_ptr<Node> m_head;
    std::shared_ptr<Node> m_front;
    std::shared_ptr<Node> m_rear;

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
        std::shared_ptr<Node> temp = std::make_shared<Node>(); // 使用make_shared创建新节点
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
        else if (m_front == m_rear)
        {
            // 不需要手动delete，智能指针会自动释放内存
            m_rear = m_front = NULL;
        }
        else
        {
            std::shared_ptr<Node> temp = m_front;
            // 不需要手动delete，智能指针会自动释放内存
            // 当temp离开作用域时，它会减少m_front所指向对象的引用计数
            // 如果引用计数变为0，则对象会被销毁
            m_front = m_front->link;
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
        std::shared_ptr<Node> temp = m_front;
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