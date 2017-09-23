#ifndef _MY_RECV_H
#define _MY_RECV_H
	#define BUFSIZE 1024
	char* myrecv(int clifd,char* buf,int len);
	void my_err(const char* err_string,int line);
	char* s_gets(char* st,int n);
	void gettime(char* timenow);
#endif
