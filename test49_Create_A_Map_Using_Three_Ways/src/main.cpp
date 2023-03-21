/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-20 18:34:30
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-20 19:37:48
 * @Description:test49_Create_A_Map_Using_Three_Ways
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#define MAXSIZE 7

class MyMap
{
public:
    MyMap();
    MyMap(int edge[][2], int EdgeNum);
    ~MyMap();
    void PrintMap();

private:
    int m_map[MAXSIZE][MAXSIZE];
};

MyMap::MyMap()
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        for (int j = 0; j < MAXSIZE; j++)
        {
            m_map[i][j] = 0;
        }
    }
}

MyMap::MyMap(int edge[][2], int EdgeNum) : MyMap() //委托构造
{
    for (int i = 0; i < EdgeNum; i++)
    {
        m_map[edge[i][0]][edge[i][1]] = 1;
        m_map[edge[i][1]][edge[i][0]] = 1;
    }
}
MyMap::~MyMap()
{
}

void MyMap::PrintMap()
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        for (int j = 0; j < MAXSIZE; j++)
        {
            printf("%d ", m_map[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int edge[][2] = {{1, 2},
                     {2, 3},
                     {4, 5},
                     {2, 6},
                     {0, 4}};
    int edgenum = sizeof(edge) / sizeof(edge[0]);
    MyMap mmp(edge, edgenum);

    mmp.PrintMap();

    return 1;
}
