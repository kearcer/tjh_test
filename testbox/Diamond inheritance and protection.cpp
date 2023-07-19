/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-14 15:49:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-14 17:19:35
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

class Furniture
{
public:
    int raw_material = 0;
    void Print_Value()
    {
        printf("raw value : %d\n ", raw_material);
    }
};

class Sofa : virtual public Furniture
{
public:
    Sofa()
    {
        raw_material = 1;
    }
    bool sit = 0;

protected:
    int protect_value = 0;
};

class Bed : virtual public Furniture
{
public:
    Bed()
    {
        raw_material = 2;
    }
    bool sleep = 0;
};

class Sofabed : public Sofa,
                public Bed
{
public:
    bool sleepAndsit = 0;
    void Set_Protect_value()
    {
        protect_value = 10;
    }
};

int main()
{
    Furniture Furniture;
    Sofa sofa;
    Bed bed;
    Sofabed sb;
    // sb.raw_material = 0;
    sb.Print_Value();

    return 0;
}