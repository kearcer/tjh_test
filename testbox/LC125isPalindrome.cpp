
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

class Solution
{
public:
    bool isPalindrome(std::string s)
    {
        if (s.empty())
            return true;
        int left = 0;
        int right = s.size() - 1;
        while (left < right)
        {
            if (s[left] < '0' || (s[left] > '9' && s[left] < 'A') || (s[left] > 'Z' && s[left] < 'a') || s[left] > 'z')
            {
                left++;
                continue;
            }

            if (s[right] < '0' || (s[right] > '9' && s[right] < 'A') || (s[right] > 'Z' && s[right] < 'a') || s[right] > 'z')
            {
                right--;
                continue;
            }

            if ((s[left] >= '0' && s[left] <= '9') && ((s[right] >= 'A' && s[right] <= 'Z') || (s[right] >= 'a' && s[right] <= 'z')))
            {
                return false;
            }
            if ((s[right] >= '0' && s[right] <= '9') && ((s[left] >= 'A' && s[left] <= 'Z') || (s[left] >= 'a' && s[left] <= 'z')))
            {
                return false;
            }

            if ((s[left] - s[right]) != 0 && (s[left] - s[right]) != 'A' - 'a' && (s[left] - s[right]) != 'a' - 'A')
            {
                return false;
            }
            else
            {
                left++;
                right--;
            }
        }
        return true;
    }
};

int main()
{
    Solution S;
    std::string s = "Marge, let's \"[went].\" I await {news} telegram.";
    std::cout << S.isPalindrome(s) << std::endl;
    return 0;
}