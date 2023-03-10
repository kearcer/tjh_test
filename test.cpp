/*
 * @Author: Jiahui Tang
 * @Date: 2023-03-10 15:01:34
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2023-03-10 21:07:53
 * @Description:
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

class Person
{
public:
    Person()
    {
        printf("enter the Person create function !\n");
    }
    ~Person()
    {
        printf("leave the Person create function!\n");
    }
    int m_house;
    int m_car;

    virtual int Print_money()
    {
        printf("dad have money:%d\n", m_money);
    }

protected:
    int m_money;

private:
    int child;
    int wife;
};

class Son : public Person
{
public:
    Son()
    {
        printf("enter the Son create function!\n");
    }
    ~Son()
    {
        printf("leave the Son create function!\n");
    }
    int no_money;
    int no_car;
    void set_money(int data)
    {
        m_money = data;
    }

    void PrintDadmoney()
    {
        Print_money();
    }

    virtual int Print_money()
    {
        printf("dad die so Son have the money!\n");
    }

protected:
    int few_money;

private:
    int no_child;
    int no_wife;
};

class stone
{
public:
    int one; // 4
    // int one_dot_one;          // 4
    virtual int set(int data) = 0; // 8
    virtual bool get() = 0;

    int two;          // 4
    static int three; // 0
    // char *four;
    // int five;
};

int main()
{
    Son So;
    So.set_money(100);
    Person *Per = (Person *)&So;
    Per->Print_money();
    // So.PrintDadmoney();

    printf("size of Son :%d\n", sizeof(Son));
    printf("size of Person: %d\n", sizeof(Person));

    printf("size of stone: %d\n", sizeof(stone));
    printf("size of point: %d\n", sizeof(char *));
    return 0;
}