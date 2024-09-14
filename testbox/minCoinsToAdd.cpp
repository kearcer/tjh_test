#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCoinsToAdd(vector<int>& coins, int target) {
    sort(coins.begin(), coins.end());  // 对硬币进行排序
    long long maxReach = 0;  // 初始可覆盖的最大金额
    int coinsToAdd = 0;  // 需要添加的硬币数量
    vector<int> addedCoins; // 用来存储需要添加的硬币值
    int index = 0;  // 当前考虑的硬币索引

    while (maxReach < target) {
        // 如果当前硬币可以用来扩展覆盖范围
        if (index < coins.size() && coins[index] <= maxReach + 1) {
            maxReach += coins[index];  // 使用当前硬币扩展覆盖范围
            index++;  // 考虑下一个硬币
        } else {
            // 需要添加一个新的硬币来扩展覆盖范围
            coinsToAdd++;  // 增加需要添加的硬币数量
            int newCoin = maxReach + 1; // 计算需要添加的新硬币的值
            addedCoins.push_back(newCoin); // 将新硬币的值添加到列表中
            maxReach += newCoin;  // 更新覆盖范围
        }
    }

    // 打印需要添加的硬币的值
    cout << "Need to add the following coins: ";
    for (int coin : addedCoins) {
        cout << coin << " ";
    }
    cout << endl;

    return coinsToAdd;  // 返回需要添加的硬币数量
}

int main() {
    vector<int> coins1 = {1, 11};
    int target1 = 1111;
    cout << "Example 1: " << minCoinsToAdd(coins1, target1) << endl;

    vector<int> coins2 = {1, 10};
    int target2 = 1111;
    cout << "Example 2: " << minCoinsToAdd(coins2, target2) << endl;

    vector<int> coins3 = {1, 1, 1};
    int target3 = 20;
    cout << "Example 3: " << minCoinsToAdd(coins3, target3) << endl;

    return 0;
}
