/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-14 18:25:35
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-15 13:34:24
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>

class Mystring
{
public:
    Mystring(const char *str = NULL)
    {
        if (str == NULL)
        {
            m_str = new char[1];
            *m_str = '\0';
        }
        else
        {
            int length = strlen(str);
            m_str = new char[length + 1];
            strcpy(m_str, str);
        }
    }

    Mystring(const Mystring &str)
    {
        int length = strlen(str.m_str);
        m_str = new char[length + 1];
        strcpy(m_str, str.m_str);
    }

    ~Mystring()
    {
        delete[] m_str;
    }

    Mystring operator=(const Mystring &str)
    {
        if (this == &str)
        { //检查自赋值
            return *this;
        }

        delete[] m_str; //释放原有内存资源

        int length = strlen(str.m_str);

        m_str = new char[length + 1];

        strcpy(m_str, str.m_str);

        return *this;
    }

    Mystring operator+(const Mystring &str) const
    {
        Mystring result = *this;
        int length = strlen(m_str) + strlen(str.m_str);
        result.m_str = new char(length + 1);
        strcpy(result.m_str, m_str);
        strcat(result.m_str, str.m_str);
        return result;
    }

    void Print_str()
    {
        printf("m_str:%s\n", m_str);
    }

private:
    char *m_str;
};

int main()
{
    Mystring str;
    Mystring str1 = str = "123";
    str1 = str + str1;

    str.Print_str();
    str1.Print_str();
}