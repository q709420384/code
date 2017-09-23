#include <iostream>
using namespace std;

#include <string.h>

#if 0
void main()
{
	int i = 5;
	int j = 0;
	++i = j;
//	i++ = j;
	cout<<i<<endl;
//	int *p;
//	*p = 5; //error
	char *q = "asdfasd";
	char str[10] = "asdfasd";
//	*q = 6; //error
	str[0] = 6;

	char str1[20] = "abc\012bac";
	char str2[20] = "abc\0abcad";
	cout<<sizeof(str1)<<endl;
	cout<<sizeof(str2)<<endl;
	cout<<strlen(str1)<<endl;
	cout<<strlen(str2)<<endl;
}
#endif

#if 0
const int &test()
{
	int a = 6;
	return a;
}

int test1()
{
	int b = 7;
	return b;
}
void main()
{
	//int b = test();
	//test() = 8;

	int a = 5;
	int &b = a;
	b++;
	cout<<a<<endl;

	//const int &c = 12;
	

	test() = 8;
}

#endif


/*
引用和指针的区别
*/

#if 0
void test(int (&a)[10])
{
	cout<<sizeof(a)<<endl;

}
void swap1(int a,int b)
{
	int t = a;
	a = b;
	b = t;
}
void swap2(int *a,int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
void swap3(int *a,int *b)
{
	int *t = a;
	a = b;
	b = t;
}
void swap4(int &a,int &b)
{
	int t = a;
	a = b;
	b = t;
}
void main()
{
//	int a[10] = {1,2,3,4,5,6,7,8,9,0};
//	test(a);
	int a = 6,b = 8;
	swap1(a,b);
	cout<<a<<b<<endl;
	swap2(&a,&b);
	cout<<a<<b<<endl;
	swap3(&a,&b);
	cout<<a<<b<<endl;
	swap4(a,b);
	cout<<a<<b<<endl;
}

#endif

#if 0

class Clock
{
public:
	void set(){}
	void show()
	{
		cout<<m_hour<<m_minute<<m_second<<endl;
	}
private:
	int m_hour;
	int m_minute;
	int m_second;
};

class Desk
{
public:
	//void set(){}
	Desk()
	{
		m_length = 20;
		m_weight = 20;
		m_high = 20;
		cout<<"Desk"<<endl;
	}
	Desk(int l,int w,int h)
	{
		m_length = l;
		m_weight = w;
		m_high = h;
	}
	void print()
	{
		cout<<m_length<<m_weight<<m_high<<endl;
	}
	~Desk()
	{
		cout<<"~Desk"<<endl;
	}
private:
	int m_length;
	int m_weight;
	int m_high;
};
void main()
{
	//Clock c;
	//c.show();
	//c.set();

	Desk d;
	Desk c(40,60,80);
	d.print();
	c.print();
	cout<<"main"<<endl;
}

#endif

#if 0
class A
{
public:
	A(){cout<<"A"<<endl;}
};
A a;
void main()
{
	cout<<"main"<<endl;
}

#endif


/*
面向过程，面向对象
流程图，类图，用例图
*/


/*
构造函数调用过程：遇到对象要去调用本类的构造函数
1.传参-调用匹配的构造函数
2.根据数据成员在类里面的声明顺序，并用冒号语法后面的值根据声明顺序进行初始化
3.数据成员初始化完之后进入本类的构造函数函数体执行其他操作

*/
#if 0
class CPU
{
public:
	CPU(int i = 0):m_i(i)
	{
		cout<<"CPU"<<m_i<<endl;
	}
private:
	int m_i;
};

class Computer
{
public:
	Computer(int i):a(i) 
	{
		//a = i;
		cout<<"Computer"<<endl;
	}
private:
	CPU a;
};

void main()
{
	Computer b(6);
}
#endif
#if 0

class A
{
public:
	A(int i = 0,int j = 0):m_j(j),m_i(m_j)
	{
		cout<<m_i<<" "<<m_j<<endl;
	} 
private:
	int m_j;
	int m_i;

};
void main()
{
	A a(6,9);
}
#endif

#if 0

class A
{
public:
	 A(int i = 0):m_i(i)
	 {
		 cout<<"A"<<endl;
	 }  //explicit
	 A(const A &s) 
	 {
		 m_i = s.m_i;
		 m_j = s.m_j;
		 cout<<"A(A)"<<endl;
	 }
	void print(){cout<<m_i<<endl;}
private:
	int m_i;
	int m_j;
};

void test(A s)
{
	s.print();
	cout<<"test"<<endl;
}
A fn()
{
	cout<<"fn "<<endl;
	A t(6);
	return t;
}
void main()
{
	//A a = 5;
	A a(5);
	A b(a); //A b = a;
	b.print();
	test(b);
	b = fn();
	cout<<"main end"<<endl;
}

#endif



class Str
{
public:
	Str(char *str = "")
	{
	//	m_str  = str;
		m_str = new char[strlen(str)+1];
		strcpy(m_str,str);
		cout<<"Str"<<endl;
	}
	/*Str(Str &s)   //浅复制（浅拷贝）
	{
		m_str = s.m_str;
		cout<<"Str(Str)"<<endl;
	}
	*/
	Str(Str &s)
	{
		m_str = new char[strlen(s.m_str)+1];
		strcpy(m_str,s.m_str);
	}
	~Str()
	{
		delete[] m_str;
	}
	void print()
	{
		cout<<m_str<<endl;
	}
private:
	char *m_str;
};

void main()
{
	Str s("12345678");
	s.print();
	Str t = s;
	t.print();
}
