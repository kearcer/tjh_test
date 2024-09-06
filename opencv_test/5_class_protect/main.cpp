#include <iostream>

class BaseClass {
protected:
    int protectedValue;

    void protectedMethod() {
        std::cout << "Accessing protected method. Value is " << protectedValue << std::endl;
    }

public:
    BaseClass() : protectedValue(100) {}  // 初始化 protected 成员变量
    virtual ~BaseClass() {}
};

class DerivedClass : public BaseClass {
public:
    void accessProtected() {
        protectedValue = 200; 
        protectedMethod(); 
    }
};

int main() {
    DerivedClass derivedObj;
    derivedObj.accessProtected();  // 访问并修改 protected 成员
    return 0;
}


