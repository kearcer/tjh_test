/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-16 22:21:15
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-16 23:31:56
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef void(FPN_Set_Second)(struct myclock &cl, int data);
typedef void(FPN_Printdata)(struct myclock &cl);
struct myclock
{
    int n_sec = 0;
    int n_min = 0;
    int n_hour = 0;
    FPN_Set_Second *pSS;
    FPN_Printdata *pP;
};

void Set_Second(struct myclock &cl, int data)
{
    cl.n_sec = data;
}

void Printdata(struct myclock &cl)
{
    printf("sec:%d \n", cl.n_sec);
}

int main()
{
    myclock cl;
    cl.pSS = Set_Second;
    cl.pP = Printdata;
    cl.pSS(cl, 2);
    cl.pP(cl);
    return 0;
}