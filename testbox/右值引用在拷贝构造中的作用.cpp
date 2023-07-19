#include<iostream>
#include<utility>

class MyClass {
public:
    MyClass(int val): val_(val) {
        std::cout << "Constructor called for val: " << val_ << std::endl;
    }

    MyClass(const MyClass &obj) {
        std::cout << "Copy constructor called" << std::endl;
        val_ = obj.val_;
    }

    MyClass(MyClass &&obj) {
        std::cout << "Move constructor called" << std::endl;
        val_ = obj.val_;
        obj.val_ = 0;
    }

    int getVal() const {
        return val_;
    }

private:
    int val_;
};

MyClass createObject(int val) {
    return MyClass(val);
}

int main() {
    MyClass obj1(5);
    // 使用std::move强制产生一个右值
    MyClass &&a = std::move(obj1);
    std::cout << "Value of a: " << a.getVal() << std::endl;

    MyClass obj2(6);
    MyClass b = obj2;
    std::cout << "Value of b: " << b.getVal() << std::endl;

    return 0;
}

