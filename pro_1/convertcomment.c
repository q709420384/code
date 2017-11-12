#include<stdio.h>
#include "convertcomment.h"

//定义状态
typedef enum
{
    no_comment_state,
    c_comment_state,
    cpp_comment_state,
    quo_state,
    end_state
}enum_state;

//定义状态机
typedef struct
{
    FILE *input;
    FILE *output;
    enum_state ulstate;
}state_machine;

//定义全局状态机
state_machine g_state;

int convertcomment(FILE *inputfile, FILE *outputfile)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("invalid arugment inputfile or outputfile.\n");
        return -1;
    }

    //初始化状态机
    g_state.input = inputfile;
    g_state.output = outputfile;
    g_state.ulstate = no_comment_state;

    char ch;
    while(g_state.ulstate != end_state)
    {
        ch = fgetc(g_state.input);
        eventpro(ch);
    }

    return 0;
}

void eventpro(char ch)
{
    switch(g_state.ulstate)
    {
    case no_comment_state:
        eventpro_no(ch);
        break;
    case c_comment_state:
    	eventpro_c(ch);
        break;
    case cpp_comment_state:
        eventpro_cpp(ch);
        break;
    case quo_state:
    	eventpro_quo(ch);
    	break;
    }
}

void eventpro_no(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
        nextch = fgetc(g_state.input);
        if(nextch == '/')   //C++
        {
            fputc('/', g_state.output);
            fputc('*', g_state.output);
            g_state.ulstate = cpp_comment_state;
        }
        else if(nextch=='*')
        {
        	fputc('/', g_state.output);
            fputc('*', g_state.output);
            g_state.ulstate = c_comment_state;
        }
        else
        {
        	fputc(ch, g_state.output);
        	fputc(nextch, g_state.output);
        }
        break;
     case '"':
     	fputc('"', g_state.output);
        g_state.ulstate = quo_state;
        break;
     case EOF:
        g_state.ulstate = end_state;
        break;
     default:
     	fputc(ch, g_state.output);
        break;
    }
}
void eventpro_c(char ch)
{
	char nextch;
	switch(ch)
	{
	case '/':
		nextch = fgetc(g_state.input);
		if(nextch=='/')
		{
			fputc(' ', g_state.output);
        	fputc(' ', g_state.output);
		}
		else
		{
			fputc(ch, g_state.output);
        	fputc(nextch, g_state.output);
		}
		break;
	case '*':
		nextch = fgetc(g_state.input);
		if(nextch=='/')
		{
			fputc(ch, g_state.output);
        	fputc(nextch, g_state.output);
        	g_state.ulstate = no_comment_state;
		}
		else if(nextch=='*')
		{
			fputc(ch, g_state.output);
			fseek(g_state.input,-1L,SEEK_CUR);
		}
		else
		{
			fputc(ch, g_state.output);
        	fputc(nextch, g_state.output);
		}
		break;
	case EOF:
        g_state.ulstate = end_state;
        break;
	default:
        fputc(ch, g_state.output);
        break;
	}
}
void eventpro_cpp(char ch)
{
	char nextch;
    switch(ch)
    {
    case EOF:
        fputc('*', g_state.output);
        fputc('/', g_state.output);
        g_state.ulstate = end_state;
        break;
    case '/':
    	nextch=fgetc(g_state.input);
    	if(nextch=='/'||nextch=='*')
    	{
    		fputc(' ', g_state.output);
        	fputc(' ', g_state.output);
    	}
    	else if(nextch=='\n')
    	{
    		fputc(ch, g_state.output);
    		fputc('*', g_state.output);
        	fputc('/', g_state.output);
    		fputc('\n', g_state.output);
    		g_state.ulstate = no_comment_state;
    	}
    	else
    	{
    		fputc(ch, g_state.output);
        	fputc(nextch, g_state.output);
    	}
    	break;
    case '*':
    	nextch=fgetc(g_state.input);
    	if(nextch=='/')
    	{
    		fputc(' ', g_state.output);
        	fputc(' ', g_state.output);
    	}
    	else
    	{
    		fputc(ch, g_state.output);
        	fputc(nextch, g_state.output);
    	}
    	break;
    case '\n':
    	fputc('*', g_state.output);
        fputc('/', g_state.output);
        fputc('\n', g_state.output);
        g_state.ulstate = no_comment_state;
        break;
    default:
        fputc(ch, g_state.output);
        break;
    }
}

void eventpro_quo(char ch)
{
	char nextch;
	switch(ch)
	{
	case '\n':
	case '"':
		fputc(ch, g_state.output);
        g_state.ulstate = no_comment_state;
        break;
    case EOF:
        g_state.ulstate = end_state;
        break;
	default:
        fputc(ch, g_state.output);
        break;
	}
}

























