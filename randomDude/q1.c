#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;int j;
int r=1,t=0;
char first_s[][2]={"a",">","("};
char first_t[][2]={"a",">","("};
char first_t2[][2]={",","@"};
char follow_s[][2]={")","$"};
char follow_t[][2]={")"};
char follow_t2[][2]={")"};
void proc_t();
void proc_t2();
void proc_s()
{
	lookahead=getNextToken(fb,&r,&t);
	for(j=0;j<3;j++)
	{
		if(strcmp(lookahead->ln,first_s[j])==0)
		{
			break;
		}
	}
	if(j==2)
	{
		proc_t();
	}
	else if(j==0||j==1)
	{
		proc_t();
		return;
	}
	else {
		
		printf("\n error expected first of S");
		exit(0);
	}

}
void proc_t()
{
	lookahead=getNextToken(fb,&r,&t);

	for(j=0;j<3;j++)
	{
		if(strcmp(lookahead->ln,first_t[j])==0)
		{
			break;
		}
	}
	if(j<3){
		
		proc_t2();
	}
	
	else{

		return;
		
	}
}
void proc_t2()
{
	lookahead=getNextToken(fb,&r,&t);
	
	for(j=0;j<1;j++)
	{
		if(strcmp(lookahead->ln,first_t2[j])==0)
		{
			break;
		}
	}
	if(j==0)
	{
		proc_s();
		proc_t2();

	}
	else 
	{
		lookahead=getNextToken(fb,&r,&t);
		if(strcmp(lookahead->ln,follow_t2[0])==0)
		{
			lookahead=getNextToken(fb,&r,&t);
			return;
		}
		else{
			printf("\n error ')' expexted");
			exit(0);
		}
	}
	
}
int main()
{
	
    fb=fopen("test1.txt","r");
   
    proc_s();
   if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nError");

    
}
