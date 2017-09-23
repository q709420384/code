#include<stdio.h>
#include<string.h>

#define bool int
#define false 0
#define true  1
enum Status{kValid=0,kInvalid};
int g_nStatus=kValid;

int StrToInt_1(const char *str)
{
	int number=0;
	while(*str!=0)
	{
		number=number*10+*str-'0';
		++str;
	}
	return number;
}

int StrToInt_2(const char *str)
{
	if(str==NULL)
		return 0;
	int number=0;
	while(*str!=0)
	{
		number=number*10+*str-'0';
		++str;
	}
	return number;
}

int StrToInt_3(const char *str)
{
	g_nStatus=kInvalid;
	int num=0;
	if(str!=NULL)
	{
		const char* digit=str;
		bool minus=false;
		if(*digit=='+')
			digit++;
		else if(*digit=='-')
		{
			digit++;
			minus=true;
		}
		while(*digit!='\0')
		{
			if(*digit>='0'&&*digit<='9')
			{
				num=num*10+(*digit-'0');
				digit++;
			}
			else
			{
				num=0;
				break;
			}
		}
		if(*digit=='\0')
		{
			g_nStatus=kValid;
			if(minus)
				num=0-num;
		}
		
	}
	return num;
}

long long StrToIntCore(const char* digit,bool minus)
{
	long long num=0;
	while(*digit!='\0')
	{
		if(*digit>='\0'&&*digit<='9')
		{
			int flag=minus?-1:1;
			num=num*10+flag*(*digit-'0');
			if(!minus&&num>0x7fffffff||(minus&&num<0x80000000))
			{
				num=0;
				break;
			}
			digit++;
		}
		else
		{
			num=0;
			break;
		}
	}
	if(*digit=='\0')
		g_nStatus=kValid;
	return num;
}

int StrToInt_4(const char *str)
{
	g_nStatus=kInvalid;
	long long num=0;
	if(str!=NULL&&*str!='\0')
	{
		bool minus=false;
		if(*str=='+')
			str++;
		else if(*str=='-')
		{
			str++;
			minus=true;
		}
		if(*str!='\0')
			num=StrToIntCore(str,minus);
	}
	return num;
}

void main()
{
	char *p=NULL;
	int l=StrToInt_1(p);
	printf("l=%d\n",l);
}
