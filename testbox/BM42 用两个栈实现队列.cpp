#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    void push(int node) {
        stack1.push(node);
        
    }

    int pop() {
        if(stack2.empty())
        {
            while(!stack1.empty())
            {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        if(stack2.empty())
            return -1;
        
        int head = stack2.top();
        stack2.pop();
        return head;
        
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};

int main() {
    Solution q;
    q.push(1);
    q.push(2);
    cout << q.pop() << endl; // 1
    cout << q.pop() << endl; // 2
    cout << q.pop() << endl; // -1
    return 0;
}