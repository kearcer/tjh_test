#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<functional>
 
using namespace std;
using namespace placeholders;
// class bind_something;

class bind_something
{
    public:
        bind_something();
        ~bind_something();

    private:
        int a = 5;
        std::function<void(bind_something*, int, int)> f1 = bind(&alter, this, a, _1);

};

void alter(bind_something &bs,int &a, int b) {
    a = b;
}

 
int main() {
 
    return 0;
}
 