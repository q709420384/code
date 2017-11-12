#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
    int i = 0;
    char buf[256];
    char* Par[] = {"Hello !","What time is it ?","Oh MyGod ! I have to go !",NULL};
    char* Chi[] = {"Hi !","It is 11 o'clock","Bye Bye !",NULL};
    char** PPar = Par;
    char** PChi = Chi;
    int PTC[2],CTP[2];
    int retP = pipe(PTC);
    int retC = pipe(CTP);
    if(retP == -1 || retC == -1)
    {
        printf("pipe error at %d \n",__LINE__);
        return 0;
    }
    pid_t pid = fork();
    if(pid == 0)
    {
        close(PTC[1]);
        close(CTP[0]);
		
        while(PChi != NULL)
        {
            read(PTC[0],buf,256);
			printf("Par: %s\n",buf);
            write(CTP[1],*PChi,strlen(*PChi)+1);
            ++PChi;
        }

        close(PTC[0]);
        close(CTP[1]);
    }
    else if(pid > 0)
    {
        close(CTP[1]);
        close(PTC[0]);

        while(PPar != NULL)
        {
            write(PTC[1],*PPar,strlen(*PPar)+1);
            ++PPar;
            read(CTP[0],buf,256);
            printf("Chi: %s\n");
        }

        close(CTP[0]);
        close(PTC[1]);
    }
    else
    {
        perror("fork error");
    }
}
