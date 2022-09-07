#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include<stdio.h>
#include<string>
using namespace std;

// 抽象基类(接口)
class Animal
{
public:
    Animal(){}
    virtual ~Animal(){}

    virtual void Sleep() = 0;
    virtual void Walk() = 0;

};

class Cat:public Animal
{
public:
    Cat(){}
    virtual ~Cat(){}

    virtual void Sleep()
    {
        printf("Cat Sleep\n");
    }
    virtual void Walk()
    {
        printf("Cat Walk\n");
    }

};

class Dog:public Animal
{
public:
    Dog(){}
    virtual ~Dog(){}

    virtual void Sleep()
    {
        printf("Dog Sleep\n");
    }
    virtual void Walk()
    {
        printf("Dog Walk\n");
    }

};

void TestAnimal(Animal *animal)
{
    animal->Sleep();
    animal->Walk();
}

int main(int argc,char *argv[])
{
    Animal *animal;
    Dog dog;
    Cat cat;
    animal=&dog;
    TestAnimal(animal);
    animal=&cat;
    TestAnimal(animal);

    return 0;
}
