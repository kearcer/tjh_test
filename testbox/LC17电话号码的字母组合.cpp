/*
 * @Author: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @Date: 2024-08-15 10:42:39
 * @LastEditors: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @LastEditTime: 2024-08-15 11:28:34
 * @FilePath: \tjh_test\testbox\LC17电话号码的字母组合.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <functional>
#include <vector>

void freeFunction(int a) {
    std::cout << "Free function called with " << a << std::endl;
}

class Functor {
public:
    void operator()(int a) const {
        std::cout << "Functor called with " << a << std::endl;
    }
};

int main() {
    // 使用std::function存储普通函数
    std::function<void(int)> func1 = freeFunction;
    func1(10);

    // 使用std::function存储lambda表达式
    std::function<void(int)> func2 = [](int a) {
        std::cout << "Lambda called with " << a << std::endl;
    };
    func2(20);

    // 使用std::function存储仿函数
    Functor functor;
    std::function<void(int)> func3 = functor;
    func3(30);

    return 0;
}
