#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"
void program();
void declarations();
void datatype();
void idlist();
void idlistprime();
void assign_stat();
void assign_statprime();
struct token tkn;
FILE *f1;
int r=0; int c=0;
int * rptr=&r;
int * cptr=&c;

int isdtype(char * s)
{
	if (((strcmp(s,"int"))==0)|((strcmp(s,"char"))==0))
		return 1;
}
int main()
{
    int ca, cb;
    f1 = fopen("input.c", "r");
    if (f1 == NULL){
        printf("Cannot open file \n");
        exit(0);
    }
	tkn=getNextToken(f1,rptr,cptr);
	printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
	while(tkn.tok!=NULL)
	{
		if(strcmp(tkn.tok,"main")==0)
		{
			program();
			break;
		}
	}
}
void program()
{


	if(strcmp(tkn.tok,"main")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		if(strcmp(tkn.tok,"(")==0)
		{
			tkn=getNextToken(f1,rptr,cptr);
			printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
			if(strcmp(tkn.tok,")")==0)
			{
				tkn=getNextToken(f1,rptr,cptr);
				printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
				if(strcmp(tkn.tok,"{")==0)
				{
					tkn=getNextToken(f1,rptr,cptr);
					printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
					declarations();
					assign_stat();
					if (tkn.tok==NULL)
					{
						printf("} missing at the end of the file\n");
						exit(1);
					}
					if(strcmp(tkn.tok,"}")==0)
					{
						printf("Compiled successfully");
						return;
					}
				}
				else
				{	
					printf("{ missing at row=%d col=%d",tkn.row,tkn.col);
					exit(1);
				}
			}
			else
			{
				printf(") missing at row=%d col=%d",tkn.row,tkn.col);
				exit(1);
			}
		}
		else
		{
			printf("( missing at row=%d col=%d",tkn.row,tkn.col);
			exit(1);
		}
	}
}

void declarations()
{
	if(isdtype(tkn.tok)==0)
	{
		return;
	}
	datatype();
	idlist();
	if(strcmp(tkn.tok,";")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		declarations();
	}
	else
	{
		printf("; missing at row=%d col=%d",tkn.row,tkn.col);
		exit(1);
	}
}

void datatype()
{
	if(strcmp(tkn.tok,"int")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		return;
	}
	else if(strcmp(tkn.tok,"char")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		return;
	}
	else
	{
		printf("%s Missing datatype at row=%d col=%d",tkn.tok, tkn.row,tkn.col);
		exit(1);
	}
}
void idlist()
{
	if(strcmp(tkn.tok,"id")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		idlistprime();
	}
	else
	{
		printf("Missing id at row=%d col=%d",tkn.row,tkn.col);
	}
}
void idlistprime()
{
	if(strcmp(tkn.tok,",")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		idlist();
	}
	
}
void assign_stat()
{
	if(strcmp(tkn.tok,"id")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		if(strcmp(tkn.tok,"=")==0)
		{
			tkn=getNextToken(f1,rptr,cptr);
			printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
			assign_statprime();
		}
		else
		{
			printf("= missing at row=%d col=%d",tkn.row,tkn.col);
			exit(1);
		}
	}
	else
	{
		printf("Missing id at row=%d col=%d",tkn.row,tkn.col);
		exit(1);
	}
}

void assign_statprime()
{
	if (strcmp(tkn.tok,"id")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		if (strcmp(tkn.tok,";")==0)
		{
			tkn=getNextToken(f1,rptr,cptr);
			printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
			return;
		}
		else
		{
			printf("missing ; at row=%d col=%d",tkn.row,tkn.col);
			exit(1);
		}
	}
	else if (strcmp(tkn.tok,"number")==0)
	{
		tkn=getNextToken(f1,rptr,cptr);
		printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
		if (strcmp(tkn.tok,";")==0)
		{
			tkn=getNextToken(f1,rptr,cptr);
			printf("<%s , %d , %d > \t",tkn.tok,tkn.row,tkn.col);
			return;
		}
		else
		{
			printf("missing ; at row=%d col=%d",tkn.row,tkn.col);
			exit(1);
		}
	}
	else
	{
			printf("id or number expected at row= %d col = %d\n",tkn.row,tkn.col);
			exit(1);
	}


}