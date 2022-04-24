#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <stdio.h>
using namespace std;
int hanoi(int n,int p1,int p2,int p3, int all)
{	
	if(1==n)
	{
		cout<<"盘子从"<<p1<<"移到"<<p3<<"的第"<< all++ <<"步"<<endl;
	}	
	else
	{

		hanoi(n-1,p1,p3,p2,all);
		cout<<"盘子从"<<p1<<"移到"<<p3<<"的第"<< all++ <<"步"<<endl;
		hanoi(n-1,p2,p1,p3,all);
	}
}

int main(int argc, char *argv[]) 
{
	int n = 3;
	int p1 = 1;
	int p2 = 2;
	int p3 = 3;
	int result = 0;
	hanoi(n, p1, p2, p3, result);
	printf("finished!!!");
	return 0;

}