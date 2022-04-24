#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define  NUM  6  //用于指定数组大小 

typedef struct Node *  pNode;
struct Node 
{
	int  Data;
	pNode Next;//结构的递归定义  等效于注释代码 
//	struct  Node *  Next; 
};

pNode creatList(); //创建固定数值的链表 
pNode inputCreatList();//键盘输入创建链表 
int main()
{	
	pNode tmp=(pNode)malloc(sizeof(struct Node) );
	tmp=creatList();	
	tmp=inputCreatList();
	return 0;
}