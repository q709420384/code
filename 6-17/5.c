/*
问题 E: CONTEST5.字符统计（BY YAN）
题目描述
编写程序接收从键盘输入的n个字符串（1<n<=10），然后实现下列功能：

（1）输出字符串的长度；

（2）输出字符串所包含的单词的数量；

（3）统计该字符串包含的大写字母、小写字母、数字、空格和其他字符的数量并输出。

输入
第一行为n值，以后连续n行为待统计的字符串，每行的长度<100。

每个单词之间用一个空格隔开，或者用一个标点加一个空格隔开。

输出
输出n行，每行是7个整数，依次表示：字符串长度、单词数量、大写字母数量、小写字母数量、数字数量、空格数量、其他字符数量。每个数字以空格隔开，每行最后一个数字后面没有空格。

样例输入
3
There are 166 students in the C programming contest.
Congratulation, you receive nice scores in this test, please continue.
I am very fond of learning advanced language program design courses.
样例输出
52 9 2 38 3 8 1
70 10 1 57 0 9 3
68 11 1 56 0 10 1
*/

#include<stdio.h>
#include<string.h>
int main()
{
	int n,i;
	char str[100];
	scanf("%d",&n);
	getchar();
	while(n--)
	{
		int len,world=0,big=0,small=0,num=0,space=0,other;
		gets(str);
		len=strlen(str);
		for(i=0;i<len;i++)
		{
			if(str[i]>='A'&&str[i]<='Z')
				big++;
			if(str[i]>='a'&&str[i]<='z')
				small++;
			if(str[i]>='0'&&str[i]<='9')
				num++;
			if(str[i]==' ')
				space++;
		}
		other=len-big-small-num-space;
                world=space+1;

		printf("%d %d %d %d %d %d %d\n",len,world,big,small,num,space,other);
	}
}
