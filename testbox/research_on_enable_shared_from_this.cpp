/*
 * @Author: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @Date: 2023-12-11 09:47:47
 * @LastEditors: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @LastEditTime: 2023-12-25 10:44:35
 * @FilePath: \tjh_test\testbox\test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <memory>

class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    std::shared_ptr<MyClass> getShared() {
        return shared_from_this(); // 返回指向自身的shared_ptr
    }
    void print() {
        std::cout << "m_i value " << m_i << std::endl;
    }
    void set(int i) { m_i = i; }

private:
    int m_i = 0; // 私有成员变量
};

int main() {
    std::shared_ptr<MyClass> obj1 = std::make_shared<MyClass>(); // 创建一个shared_ptr指向MyClass对象
    std::shared_ptr<MyClass> obj2 = obj1->getShared(); // 通过getShared()获取指向obj1的shared_ptr
    std::shared_ptr<MyClass> obj3 = obj1;

    obj1->set(10); // 修改obj1的值
    obj1->print(); // 输出Some Message
    obj2->print(); 
    obj2->print();

    std::cout << "obj1 use count: " << obj1.use_count() << std::endl; // 输出obj1的引用计数
    std::cout << "obj2 use count: " << obj2.use_count() << std::endl; // 输出obj2的引用计数
    std::cout << "obj3 use count: " << obj3.use_count() << std::endl;

    return 0;
}
