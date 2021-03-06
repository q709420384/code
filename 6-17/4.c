/*
问题 D: CONTEST4.翻硬币（BY YAN）
题目描述
小明正在玩一个“翻硬币”的游戏，桌上放着排成一排的若干硬币。我们用 * 表示正面， 用 o 表示反面（是小写字母，不是零）。例如，可能情形是：**oo***oooo，如果同时翻转左边的两个硬币，则变为：oooo***oooo。

现在小明的问题是：如果已知了初始状态和要达到的目标状态，每次只能同时翻转相邻的两个硬币,那么对特定的局面，最少要翻动多少次呢？

我们约定：把翻动相邻的两个硬币叫做一步操作。

输入
两行等长的字符串，分别表示初始状态和要达到的目标状态，每行的长度<1000。

输出
一个整数，表示最小操作步数。

输入样例 1:
**********
o****o**** 
输出样例 1:
5
输入样例 2:
*o**o***o*** 
*o***o**o***
输出样例 2:
1
输入样例 3:
**o***oo****ooo***oo*
o**o**oo**oo***oo*oo* 
输出样例 3:
12

*/
#include<stdio.h>
#include<string.h>
void fun(char* s)
{
	if(*s=='*')
		*s='o';
	else
		*s='*';
}
int main()
{
	int i,j=0,t=0;
	char s1[1000],s2[1000];
	scanf("%s %s",s1,s2);
	for(i=0;i<strlen(s1)-1;i++)
	{
		if(s1[i]!=s2[j++])
		{
			fun(&s1[i]);
			fun(&s1[i+1]);
			t++;
		}
	}
	printf("%d",t);
}
