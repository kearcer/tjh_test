#include <iostream>
using namespace std;

#define SIZE 10

class Queue
{
private:
    int items[SIZE], front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isFull()
    {
        if (front == 0 && rear == SIZE - 1)
        {
            return true;
        }
        if (front == rear + 1)
        {
            return true;
        }
        return false;
    }

    bool isEmpty()
    {
        if (front == -1)
            return true;
        else
            return false;
    }

    void enQueue(int element)
    {
        if (isFull())
        {
            cout << "Queue is full";
        }
        else
        {
            if (front == -1)
                front = 0;
            rear = (rear + 1) % SIZE;
            items[rear] = element;
            cout << endl
                 << "Inserted " << element << endl;
        }
    }

    int deQueue()
    {
        int element;
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return (-1);
        }
        else
        {
            element = items[front];
            if (front == rear)
            {
                front = -1;
                rear = -1;
            } /* Q has only one element, so we reset the queue after deleting it. */
            else
            {
                front = (front + 1) % SIZE;
            }
            cout << endl
                 << "Deleted -> " << element << endl;
            return (element);
        }
    }
    void showQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Elements in Circular Queue are: ";
        if (rear >= front)
        {
            for (int i = front; i <= rear; i++)
            {
                cout << items[i] << " ";
            }
        }
        else
        {
            for (int i = front; i < SIZE; i++)
            {
                cout << items[i] << " ";
            }
            for (int i = 0; i <= rear; i++)
            {
                cout << items[i] << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    Queue q;

    // Fails because front = -1
    q.deQueue();

    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);
    q.enQueue(40);
    q.enQueue(50);

    // Fails to enqueue because front == 0 && rear == SIZE - 1
    q.enQueue(60);

    q.deQueue();
    q.showQueue();

    return 0;
}