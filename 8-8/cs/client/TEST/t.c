#include<stdio.h>
#include<assert.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	mkdir("te/qwe",S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	FILE* fp=fopen("te/qwe/709420384","w");
	fclose(fp);
}
