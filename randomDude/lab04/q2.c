#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;int j;
int r=1,t=0;
char first_E[][2]={"(","id"};
char first_Ed[][2]={"+","@"};
char first_T[][2]={"(","id"};
char first_Td[][2]={"*","@"};
char first_F[][2]={"(","id"};
char follow_E[][2]={")","$"};
char follow_Ed[][2]={")","$"};
char follow_T[][2]={")","+","$"};
char follow_Td[][2]={"+",")","$"};
char follow_F[][2]={"*","+",")","$"};
void proc_T();
void proc_Td();
void proc_F();
void proc_Ed();
void proc_E()
{
	lookahead=getNextToken(fb,&r,&t);
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_E[j])==0)
		{
			break;
		}
	}
	if(j<2)
	{
		proc_Ed();
	}
	else {
		return;
		
		printf("\n error ");
		exit(0);
	}

}

void proc_Ed()
{
	lookahead=getNextToken(fb,&r,&t);
	
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_Ed[j])==0)
		{
			break;
		}
	}
	if(j==1)
	{
		proc_T();
		proc_Ed();

	}
	else 
	{
		for(j=0;j<2;j++)
		{
		if(strcmp(lookahead->ln,follow_Ed[j])==0)
		{
			
			return;
		}
		}
			printf("\n error ");
			exit(0);
		
	}
	
}
void proc_T()
{
	lookahead=getNextToken(fb,&r,&t);
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_T[j])==0)
		{
			break;
		}
	}
	if(j<2)
	{
		proc_Td();
	}
	else {
		
		printf("\n error ");
		exit(0);
	}

}
void proc_Td()
{
	lookahead=getNextToken(fb,&r,&t);
	
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_Td[j])==0)
		{
			break;
		}
	}
	if(j==1)
	{
		proc_F();
		proc_Td();

	}
	else 
	{
		for(j=0;j<3;j++)
		{
		if(strcmp(lookahead->ln,follow_Td[j])==0)
		{
			
			return;
		}
	}
	
			printf("\n error ");
			exit(0);
		
	}
	
}
void proc_F()
{
	lookahead=getNextToken(fb,&r,&t);
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_F[j])==0)
		{
			break;
		}
	}
	if(j==0)
	{
		proc_E();
	}
	else if(j==1)
	{
		return;
	}
	else {
		
		printf("\n error ");
		exit(0);
	}

}
int main()
{
	
    fb=fopen("ex3.txt","r");
   
    proc_E();
   if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nsuccess");

    
}
