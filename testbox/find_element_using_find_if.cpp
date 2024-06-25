#include <iostream>
#include <algorithm>
#include <vector>

bool isEven(int num) {
    return num % 2 == 0;
}

int main() {
    std::vector<int> numbers = {1, 3, 5, 2, 4, 6};

    // 使用std::find_if查找第一个偶数
    auto it = std::find_if(numbers.begin(), numbers.end(), isEven);

    if (it != numbers.end()) {
        std::cout << "the first even number is" << *it << std::endl;
    } else {
        std::cout << "can not find the even number?" << std::endl;
    }

    return 0;
}
