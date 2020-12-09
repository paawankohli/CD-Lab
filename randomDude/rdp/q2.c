#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;int j;
int r=1,t=0;
char first_e[][2]={"i","("};
char first_e2[][2]={"+","@"};
char first_t[][2]={"i","("};
char first_t2[][2]={"*","@"};
char first_f[][2]={"i","("};
char follow_e[][2]={"$",")"};
char follow_e2[][2]={"$",")"};
char follow_t[][2]={"$",")","+"};
char follow_t2[][2]={"$",")","+"};
char follow_f[][2]={"*",")","+","$"};

void proc_e2();
void proc_t2();
void proc_t();
void proc_f();
void proc_e()
{
    printf("\n e called");

    printf("\n %s",lookahead->ln);
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_e[j])==0)
		{
			break;
		}
	}
	if(j<2){

		proc_t();

        lookahead=getNextToken(fb,&r,&t);

		proc_e2();
    lookahead=getNextToken(fb,&r,&t);



	}
	else{
		printf("\n error -first of e expected");
		exit(0);
	}
}
void proc_t()
{
printf("\n t called");
printf("\n %s",lookahead->ln);
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_t[j])==0)
		{
			break;
		}
	}
	if(j<2){

		proc_f();

		lookahead=getNextToken(fb,&r,&t);

		proc_t2();

	}
	else{
		printf("\n error -first of t expected");
		exit(0);
	}
}
void proc_f()
{
printf("\n f called");
printf("\n %s",lookahead->ln);

	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_f[j])==0)
		{
			break;
		}
	}
	if(j==1){
     lookahead=getNextToken(fb,&r,&t);
		proc_e();


	}
	else if(j==0)
	{

		return;
	}
	else{
		printf("\n error -first of f expected");
		exit(0);
	}
}
void proc_e2()
{
printf("\n e2 called");
printf("\n %s",lookahead->ln);
	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_e2[j])==0)
		{
			break;
		}
	}
	if(strcmp(lookahead->ln,"$")==0)
    {
                fseek(fb, -1, SEEK_CUR);
        printf("\n%s",lookahead->ln);

		return;
    }
	 if(j==0){

            lookahead=getNextToken(fb,&r,&t);

		proc_t();

		lookahead=getNextToken(fb,&r,&t);
		proc_e2();

	}
	else if(strcmp(lookahead->ln,follow_e2[1])==0)
	{
                fseek(fb, -1, SEEK_CUR);

		return;
	}
	else{
		printf("\n error -first of e2 expected");
		exit(0);
	}
}
void proc_t2()
{printf("\n t2 called");
printf("\n %s",lookahead->ln);

	for(j=0;j<2;j++)
	{
		if(strcmp(lookahead->ln,first_t2[j])==0)
		{
			break;
		}
	}
	if(j==0){

            lookahead=getNextToken(fb,&r,&t);
		proc_f();

		lookahead=getNextToken(fb,&r,&t);
		proc_t2();

	}
	else if(strcmp(lookahead->ln,"$")==0)
    {
                fseek(fb, -1, SEEK_CUR);
		return;
    }
	else if(j==2)
	{
		for(j=0;j<3;j++)
	{
		if(strcmp(lookahead->ln,follow_t2[j])==0)

		{


            fseek(fb, -1, SEEK_CUR);
			return;
		}
	}

	}
	else{
		printf("\n error -first of t2 expected");
		exit(0);
	}
}
int main()
{

    fb=fopen("test2.txt","r");
   lookahead=getNextToken(fb,&r,&t);
    proc_e();

    printf("\n %s",lookahead->ln);
   if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nError");


}

