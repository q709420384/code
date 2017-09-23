#include<iostream>
using namespace std;

#if 0
int main()
{
	const char* p1="asdfgh";
	char p2[]="asdfgh";
	cout<<sizeof(p1)<<endl;
	cout<<sizeof(p2)<<endl;
}
#endif
const int &test()
{
	int a=6;
	return a;
}
int test1()
{
	int a=7;
	return a;
}
int main()
{
	int a=test1();
	cout<<a<<endl;
}
