#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<pwd.h>
#include<errno.h>
#include<readline/history.h>
#include<readline/readline.h>

#define MAX_NAME_LEN   256
#define MAX_PATH_LEN   1024
struct passwd *pwd;
int black;

void print_prompt();
int get_input(char* buf);
int explain_input(char* buf,char* command[100]);
void do_cmd(int num, char* command[100]);
int find_command(char* command);


int main()
{
    char prompt[1024];
    char buf[256];
    char parameter[20][10];    //参数
    char* command[100];    //命令
    for(int i=0;i<100;i++)
    		command[i]=(char*)malloc(256);
    while(1)
    {	char* bla;
    	black=0;
        memset(parameter,0,sizeof(parameter));
        for(int i=0;i<100;i++)
        	memset(command[i],0,sizeof(256));
    	
    	print_prompt(prompt);
    	strcpy(buf,readline(prompt));
    	add_history(buf);
    	//int t=get_input(buf);
    	if(strcmp(buf,"exit")==0||strcmp(buf,"logout")==0)
    		break;
        if((bla=strchr(buf,'&'))!=NULL)
        {	
        	*bla=' ';
        	black=1;
        }
        int num = explain_input(buf,command);
        do_cmd(num,command);
    }
    for(int i=0;i<100;i++)
    	free(command[i]);
    exit(0);
}

void print_prompt(char* prompt)
{
	memset(prompt,0,1024);
    char hostname[MAX_NAME_LEN];
    char pathname[MAX_PATH_LEN];
    pwd=getpwuid(getuid());
    getcwd(pathname,MAX_PATH_LEN);
    if(gethostname(hostname,MAX_NAME_LEN)==0)
    {
    	int i=0;
        while(hostname[i]!='.')
        	i++;
		hostname[i]='\0';
        sprintf(prompt," %s@%s:",pwd->pw_name,hostname);
    }
    else
        sprintf(prompt," %s@%???:",pwd->pw_name);
    int length=strlen(prompt);
    if(strlen(pathname) < strlen(pwd->pw_dir) || 
            strncmp(pathname,pwd->pw_dir,strlen(pwd->pw_dir))!=0)
        sprintf(prompt+length,"%s",pathname);
    else
        sprintf(prompt+length,"~%s",pathname+strlen(pwd->pw_dir));
    length = strlen(prompt);
    if(geteuid()==0)
        sprintf(prompt+length,"#");
    else
        sprintf(prompt+length,"$");
    return;
}
int get_input(char* buf)
{
	fgets(buf,256,stdin);
	int i=0;
    while(buf[i]!='\n'&&buf[i]!='\0')
        i++;
    buf[i]='\0';
    return i;
}

int explain_input(char* buf,char* command[100])
{
    char* p=buf;
    char* q=buf;
    int number=0;
    int argcount=0;
    while(1)
    {
        if(p[0]=='\n')
            break;
    	if(p[0]=='\0')
    		break;
        if(p[0]==' ')
            p++;
        else
        {
            q=p;
            number=0;
            while(q[0]!=' '&&q[0]!='\0')
            {
                number++;
                q++;
            }
            strncpy(command[argcount],p,number+1);
            command[argcount][number]='\0';
            argcount=argcount+1;
            p=q;
        }
    }
    return argcount;

}
void do_cmd(int num, char* command[100])
{
	int out=0,in=0;
    char parameter[20][10];
    char* argv[100],*name;
    int i,j=0,k;
    int a[10]={0};
    int fd[3]={0},sdf;
    pid_t pid;
    sdf=dup(1);
    for(i=0;i<num;i++)
    {
    	argv[i]=command[i];
        if(strcmp(command[i],">")==0||strcmp(command[i],">>")==0||strcmp(command[i],"<")==0||strcmp(command[i],"|")==0)
        {

            if(i!=num-1)
            {
                strcpy(parameter[j++],command[i]);
                a[j]=i+1;
                argv[i]=NULL;
            }
            else
            {
                printf("wrong command\n");
                return;
            }
        }
    }
    argv[i]=NULL;
    if(strcmp(argv[0],"cd")==0)
    {
    	chdir(argv[1]);
    	return;
    }

    if((pid=fork())<0)
    {
    	printf("fork error\n");
    	return;
    }
    if(pid==0)
    {
        if(j==0)   //没有>,>>,<,|
        {
            if(!find_command(argv[0]))
            {
                printf("%s : command not found\n",argv[0]);
                exit(0);
            }
			//printf("\n");
            execvp(argv[0],argv);
            exit(0);
        }
        else
        {
            for(i=0;i<j;i++)
            {
            	if(argv[a[i]-1]==NULL)
            		continue;
                if(!find_command(argv[a[i]]))
                {
                    printf("%s : command not found\n",argv[a[i]]);
                    exit(0);
                }
            }
            for(i=0;i<j;i++)
            {

                if(strcmp(parameter[i],">")==0)
                {
                	out=1;
                	name=argv[a[i+1]];
                    fd[0]=open(argv[a[i+1]],O_RDWR|O_CREAT|O_TRUNC,0644);
                    dup2(fd[0],1);
                }
                if(strcmp(parameter[i],">>")==0)
		        {
		        	out=1;
           			fd[0]=open(argv[a[i+1]],O_RDWR|O_CREAT|O_APPEND,0644);
           			dup2(fd[0],1);
		        }
                if(strcmp(parameter[i],"<")==0)
		        {
		        	in=1;
           			fd[1]=open(argv[a[i+1]],O_RDONLY);
           			dup2(fd[1],0);
                }
                if(strcmp(parameter[i],"|")==0)
                {
                	fd[2]=open("/tmp/youdonotknow",O_WRONLY|O_CREAT|O_TRUNC,0644);
                	if(out==0)
                	{	
                		dup2(fd[2],1);
                	}
                }
            }
            pid_t pid2,pid3,pid4;
            
          	pid2=fork();
          	if(pid2==0)
            {
				execvp(argv[a[0]],argv);
				exit(0);
           	} 	
       	 	int status2;
       	 	if(wait(&status2)==-1)
       	 	{
       	 		printf("wait for child2 process error\n");
       	 	}
       	 	
       	 	for(i=0;i<j;i++)
       	 	{
       	 		if(strcmp(parameter[i],"|")==0)
				{	
					if(out==1)
					{
						dup2(sdf,1);
						fd[0]=open(name,O_RDONLY);
						dup2(fd[0],0);
					}
					else
					{
						dup2(sdf,1);
						fd[2]=open("/tmp/youdonotknow",O_RDONLY);
					   	dup2(fd[2],0);
				   	}
				    execvp(argv[a[i+1]],argv+a[i+1]);
					exit(0);
				}
       	 	}
    	}
    }
   	int status1;
   	if(black==1)
   	{
   		usleep(500000);
   		return;
   	}
    if(waitpid(pid,&status1,0)==-1)
    {
        printf("wait for child1 process error:%s \n",errno);
    }

}
int find_command(char* command)
{
    DIR* dp;
    struct dirent* dirp;
    char* path[]={"./","/bin","/usr/bin",NULL};

    if(strncmp(command,"./",2)==0)
    {
        command=command+2;
    }

    int i=0;
    while(path[i]!=NULL)
    {
        if((dp=opendir(path[i]))==NULL)
        {
            printf("can not open /bin \n");
        }
        while((dirp=readdir(dp))!=NULL)
        {
            if(strcmp(dirp->d_name,command)==0)
            {
                closedir(dp);
                command-=2;
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    command-=2;
    return 0;
}
