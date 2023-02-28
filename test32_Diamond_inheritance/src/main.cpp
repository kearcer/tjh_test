/*
 * @Author: Jiahui Tang
 * @Date: 2023-02-16 17:31:03
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-02-16 22:21:36
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
class CFurniture
{

public:
    int m_Furniturevalue = 0;
    CFurniture()
    {
        printf("create CFurniture");
    }
    ~CFurniture()
    {
        printf("delete CFurniture");
    }

private:
    int m_quality = 0;
};

class CSofa : public CFurniture
{
public:
    int m_Sofavalue = 0;
    CSofa()
    {
        printf("create CSofa\n");
    }
    ~CSofa()
    {
        printf("delete CSofa\n");
    }

private:
    int m_quality = 100;
};

class CBed : public CFurniture
{
public:
    int m_Bedvalue = 0;
    CBed()
    {
        printf("create CBed\n");
    }
    ~CBed()
    {
        printf("delete CBed\n");
    }

private:
    int m_quality = 1000;
};

class CSofaBed : public CBed, public CSofa
{
public:
    CSofaBed()
    {
        printf("create CSofaBed\n");
    }
    ~CSofaBed()
    {
        printf("delete CSofaBed\n");
    }

private:
    int m_quality = 10000;
};

int main()
{
    CSofaBed sb;
    CSofa sf;
    CBed bd;
    sf.m_Furniturevalue = 1000;
    bd.m_Furniturevalue = 100;
    sb.CSofa::m_Furniturevalue = 100;
    sb.CBed::m_Furniturevalue = 200;
    return 0;
}
