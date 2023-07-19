/*
 * @Author: Jiahui Tang
 * @Date: 2022-08-13 09:00:04
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-09-07 19:09:01
 * @Description:
 */
// Test11.cpp:定义控制台的应用程序的入口点
//

#include <iostream>
#include <type_traits>
#include <memory>
#include <stdio.h>
#include <stack>
#include <string>
#include <cstring>
#include <math.h>
using namespace std;

/*priority
1)Parentness (){}[]
2)exponents *
3)mulitiplication and division
4)addition and subtraction
*/

bool Ismatch(string s)
{
}

int main()
{
	unsigned char m_Tenccet_contentid[255];
	memset(m_Tenccet_contentid, 0, 255);
	int m_Tencent_gap = 0;
	char *m_Tcent_prefix = "";
	char *m_Tcent_postfix = "";
	char *sCID = "123";
	int temp[16] = {0};
	int temp_usrid, count = 0;
	m_Tencent_gap = m_Tencent_gap + 1;
	int m_Tencent_contentlen = strlen(m_Tcent_prefix) + strlen(m_Tcent_postfix) + 16;
	// VMF_Memset(m_Tenccet_contentid, '0', 255);
	int m_Tencent_userID = atoi(sCID);
	temp_usrid = m_Tencent_userID;

	while (temp_usrid)
	{
		if (temp_usrid % 2)
			temp[count] = '1';
		else
			temp[count] = '0';
		count++;
		temp_usrid /= 2;
	}

	for (unsigned int i = 0; i < strlen(m_Tcent_prefix); i++)
	{
		m_Tenccet_contentid[i] = m_Tcent_prefix[i];
	}

	for (int i = count - 1; i >= 0; i--)
	{
		m_Tenccet_contentid[15 + strlen(m_Tcent_prefix) - i] = temp[i];
	}

	for (unsigned int i = 0; i < strlen(m_Tcent_postfix); i++)
	{
		m_Tenccet_contentid[strlen(m_Tcent_prefix) + 16 + i] = m_Tcent_postfix[i];
	}

	for (int i = 0; i < m_Tencent_contentlen; i++)
	{
		printf("%c ", m_Tenccet_contentid[i]);
	}
	printf("\n");

	return 0;
}