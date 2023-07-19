/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-21 15:58:11
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-22 15:08:45
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    long long a = 100;
    long long *p = &a;
    printf("a:%d\n", a);
    printf("&a:%p\n", &a);
    printf("p:%p\n", p);
    printf("p+1:%p\n", p + 1);
    printf("*p:%d\n", *p);
    printf("*(p + 1):%d\n", *(p + 1));
    printf("*p + 1:%d\n", *p + 1);

    return 0;
}