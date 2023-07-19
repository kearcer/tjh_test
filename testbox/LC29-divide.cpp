/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-24 21:04:10
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-27 18:34:44
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
    int divide(long dividend, long divisor)
    {
        int Iso = Is_Same_operator(dividend, divisor);
        unsigned long long dividend_new = abs(dividend);
        unsigned long long divisor_new = abs(divisor);
        if (dividend_new == INT_MIN)
        {
            dividend_new = pow(2, 31);
        }
        if (divisor == INT_MIN)
        {
            divisor = pow(2, 31);
        }

        if (Iso == -1)
        {
            return 0;
        }
        else if (Iso == -2)
        {
            return -1;
        }
        else if (Iso == 1 || Iso == 0)
        {
            long long result = 0;
            while (dividend_new > 0)
            {
                dividend_new = dividend_new - divisor_new;
                if (dividend_new >= 0)
                    result++;
            }
            if (Iso == 1)
            {
                if (result == INT_MIN)
                    return result - 1;
                else
                    return result;
            }

            else if (Iso == 0)
                return (0 - result);
        }
        return 0;
    }

    int Is_Same_operator(long dividend, long divisor)
    {
        if (dividend > 0 && divisor > 0 || dividend < 0 && divisor < 0)
            return 1;
        else if (dividend > 0 && divisor < 0 || dividend < 0 && divisor > 0)
            return 0;
        else if (dividend == 0)
            return -1;
        else if (divisor == 0)
        {
            printf("the divisor cannnot be set by zero\n");
            return -2;
        }
        return 0;
    }
};

int main()
{
    Solution s;
    printf("INT_MAX:%d\n", INT_MAX);
    printf("INT_MIN:%d\n", INT_MIN);
    int dividend = -2147483648;
    int divisor = -1;
    int result = s.divide(dividend, divisor);
    std::cout << "result: " << result << std::endl;
    return 0;
}