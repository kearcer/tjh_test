#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>
#include <math.h>
#include <string.h>
using namespace std;

int main()
{
    std::string a;
    while (cin >> a)
    {
        int size = a.size();
        int ans = 0;
        for (int i = 2; i < size; i++)
        {
            if (a[i] >= '0' && a[i] <= '9')
                ans += std::pow(16, size - i - 1) * (a[i] - '0');
            else if (a[i] >= 'A' && a[i] <= 'F')
                ans += std::pow(16, size - i - 1) * (a[i] - 'A' + 10);
        }
        printf("%d\n", ans);
    }
}
// 64