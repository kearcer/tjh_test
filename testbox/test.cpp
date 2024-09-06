#include <iostream>
#include <functional>
#include <vector>

using namespace std;

void freeFunction(int a) {
    printf("I got the function name with functional: %d\n", a);
}

void freeFunction1(int a, int b) {
    printf("I got the a = %d, b = %d\n", a, b);
}

class Tester {
    public:
    void operator() (int a) const {
        printf("Tester got the value %d\n", a);
    }
};

int main() {
    std::function<void(int)> func = freeFunction;
    func(10);
    freeFunction(10);

    std::function<void(int, int)> func1 = freeFunction1;
    func1(10, 20);
    freeFunction1(10, 20);

    std::function<void(int)> func2 = [](int a) {
        std::cout << "Lambda called with " << a << std::endl;
    }

    Tester freeFunction2;
    std::function<void(int)> func2 = freeFunction2;
    func2(10);
    return 0;
}