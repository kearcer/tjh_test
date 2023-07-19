#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <regex>
#include <math.h>

using namespace std;
int main()
{
    string s;  //定义一个字符串s
    while (cin >> s)  //循环输入字符串
    {
        int size = s.size();  //获取字符串的长度
        //如果字符串的长度小于8，输出“NG”，并跳过本次循环
        if (size < 8)
        {
            printf("NG\n");
            continue;
        }
        int cnt[4] = {0, 0, 0, 0};  //定义一个数组，用于记录字符串中各类型字符的数量
        //遍历字符串中的每个字符
        for (int i = 0; i < size; i++)
        {
            //根据字符类型对应增加数组cnt中的计数
            if (s[i] >= 'a' && s[i] <= 'z')  //小写字母
                cnt[0] = 1;
            else if (s[i] >= 'A' && s[i] <= 'Z')  //大写字母
                cnt[1] = 1;
            else if (s[i] >= '0' && s[i] <= '9')  //数字
                cnt[2] = 1;
            else  //其他字符
                cnt[3] = 1;
        }

        //如果字符串中包含的字符类型小于3种，输出“NG”，并跳过本次循环
        if (cnt[0] + cnt[1] + cnt[2] + cnt[3] < 3)
        {
            printf("NG\n");
            continue;
        }

        //检查字符串中是否有连续出现两次的三个字符的子串
        bool flag = true;  //设定一个标志位，初始化为true
        for (int i = 0; i < size; i++)  //遍历字符串
        {
            for (int j = i + 3; j < size; j++)  //检查每一个长度为3的子串
                //如果找到相同的子串，将标志位设为false，输出“NG”，并退出当前循环
                if (s.substr(i, 3) == s.substr(j, 3))
                {
                    flag = false;
                    printf("NG\n");
                    break;
                }
            //如果标志位已经被设为false，退出外层循环
            if (flag == false)
            {
                break;
            }
        }
        //如果没有找到相同的子串，输出“OK”
        if (flag == true)
        {
            printf("OK\n");
        }
    }

    return 0;  //程序正常结束
}
