/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-27 18:36:17
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-28 23:29:55
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        long a = labs(dividend), b = labs(divisor), res = 0;
        int sign = (dividend > 0) ^ (divisor > 0) ? -1 : 1;
        while (a >= b)
        {
            long t = b, p = 1;
            while (a >= (t << 1))
            {
                t <<= 1;
                p <<= 1;
            }
            res += p;
            a -= t;
        }
        return sign * res;
    }
};

int main()
{
    Solution s;
    printf("INT_MAX:%d\n", INT_MAX);
    printf("INT_MIN:%d\n", INT_MIN);
    int dividend = 10;
    int divisor = 3;
    int result = s.divide(dividend, divisor);
    std::cout << "result: " << result << std::endl;
    return 0;
}