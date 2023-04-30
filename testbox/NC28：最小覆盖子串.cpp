#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
#include <climits>
#include <unordered_map>
#include <vector>

using namespace std;


class Solution {
public:
    /**
     * 
     * @param S string字符串 
     * @param T string字符串 
     * @return string字符串
     */
    string minWindow(string S, string T) 
    {
        unordered_map<char, int> need;
        for(auto it:T)
        {
            need[it]++;
        }
        int left = 0;
        int right = 0;
        int count = 0;
        int minlen = INT_MAX;
        int start = -1;
        int T_size = T.size();
        int S_size = S.size();

        while(right < S_size)
        {
            char c = S[right];
            int needcnt = need.count(c);
            if(needcnt)
            {
                if(need[c]>0)
                {
                    count++;
                }
                need[c]--;
            }
            right++;
            while(count == T_size)
            {
                minlen = min(right - left, minlen);
                start = left;
                char d = S[left];
                int needcnt_d = need.count(d);
                if(needcnt_d)
                {
                    if(need[d] == 0)
                    {
                        count--;
                    }
                    need[d]++;
                }
                left++;
            }

        }
        return start == -1? "":S.substr(start, minlen);

    }
};


int main() {
  // 定义两个字符串变量S和T
    string S = "XDOYEZODEYXNZ";
    string T = "XYZ";

  // 创建一个Solution类的对象
  Solution sol;
  // 调用minWindow函数，得到返回的最小子串，并赋值给ans
  string ans = sol.minWindow(S, T);
  // 将ans输出到标准输出
  cout << ans << endl;
  return 0;
}