#include<stdio.h>
#define maxline 20
char getch()
{
        char c;
        system("stty -echo");
        system("stty -icanon");
        c=getchar();
        system("stty icanon");
        system("stty echo");
        return c;
}

void get__pwd(char *buffer)    //get  pass word,putchar '*',replace of every char user input
{ 
    int i=0; 
    char letter; 
    char ch=getchar(); 
    while(( i < maxline ) && (letter != '\r' )) 
    { 
        letter = getch(); 
        if(letter==127)    //when backspace 
        {     
            if(i>0) 
            { 
                buffer[i--]='\0'; 
              //      putchar(BACKSPACE);
                putchar('\b');
                putchar(' ');
               //     putchar(BACKSPACE);
                putchar('\b'); 
                continue; 
            } 
            else putchar(7);    //alarm 
        } 
        else if( letter != '\r') 
        { 
            buffer[i++]=letter; 
               putchar('*'); 
        } 
    } 
    buffer[i]='\0';
}
int main()
{
	char passwd[20];
	get__pwd(passwd);
	printf("%s",passwd);
}
