#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;int j;
int r=1,t=0;
void expn();
void simple_expn();
void eprime();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void decision_stat();
void looping_stat();
void dprime();
void datatype();
void identifier_list();
void statement_list();
void statement();
void declarations();
void assign_stat();
void program()
{
	if(strcmp(lookahead->ln,"int")==0)
	{

		lookahead=getNextToken(fb,&r,&t);
		 
		while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
		{
			lookahead=getNextToken(fb,&r,&t);
		}
  
		if(strcmp(lookahead->ln,"main")==0)
		{
			lookahead=getNextToken(fb,&r,&t);
			while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
			{
			lookahead=getNextToken(fb,&r,&t);
			}
			if(strcmp(lookahead->ln,"(")==0)
			{
				lookahead=getNextToken(fb,&r,&t);
				if(strcmp(lookahead->ln,")")==0)
				{
					lookahead=getNextToken(fb,&r,&t);
			while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
			{
			lookahead=getNextToken(fb,&r,&t);
			}


			if(strcmp(lookahead->ln,"{")==0)
			{
				lookahead=getNextToken(fb,&r,&t);
				
				while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}
				
				declarations();
				
				while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}
				
				statement_list();
				lookahead=getNextToken(fb,&r,&t);
				
				while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}
				
				if(strcmp(lookahead->ln,"}")==0)
					return;
				else
				{
					printf("\n error }  expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
					exit(0);
				}
			}
			else
			{
				printf("\n error { expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
				exit(0);
			}
		}
	}
		}
		else
			{
				printf("\n error 'main' expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
				exit(0);
			}
	}
	else
			{
				printf("\n error 'int' expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
				exit(0);
			}
}

void declarations()
{
	if(strcmp(lookahead->ln,"int")==0||strcmp(lookahead->ln,"char")==0)
	{

		datatype();

		lookahead=getNextToken(fb,&r,&t);
		while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}
				
		identifier_list();
		lookahead=getNextToken(fb,&r,&t);
		
		if(strcmp(lookahead->ln,";")==0)
		{
			lookahead=getNextToken(fb,&r,&t);
			while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}


			declarations();
		}

	}
	else
		return;
}
void datatype()
{
	if(strcmp(lookahead->ln,"int")==0||strcmp(lookahead->ln,"char")==0)
	{

		return;
	}
	else {
		printf("\n datatype");
		printf("\n error int or char expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		exit(0);
	}
}
void identifier_list()
{
	if(lookahead->type==8)
	{


		lookahead=getNextToken(fb,&r,&t);

		if(strcmp(lookahead->ln,",")==0)
		{
			lookahead=getNextToken(fb,&r,&t);

			identifier_list();
		}
		else if(strcmp(lookahead->ln,"[")==0)
		{
			lookahead=getNextToken(fb,&r,&t);

			if(lookahead->type==6)
			{
				lookahead=getNextToken(fb,&r,&t);

				if(strcmp(lookahead->ln,"]")==0)
				{
					lookahead=getNextToken(fb,&r,&t);

					if(strcmp(lookahead->ln,",")==0)
					{
						lookahead=getNextToken(fb,&r,&t);
						identifier_list();
					}
					else
					{
						fseek(fb,-1,SEEK_CUR);
						return;
					}
				}
				else
				{
					printf("\n error ] expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
				}
			}
			else
			{
				printf("\n error number expected");exit(0);
			}
		}
		else
			{
				fseek(fb,-1,SEEK_CUR);
						return;
			}
	}
	else
	{
		printf("\n identifier expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void statement_list()
{
	while(lookahead->type==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}
				
	if(lookahead->type==8||strcmp(lookahead->ln,"if")==0||strcmp(lookahead->ln,"while")==0||strcmp(lookahead->ln,"for")==0)
		{
		
		statement();
		lookahead=getNextToken(fb,&r,&t);
		while(lookahead->type==0)
				{
				lookahead=getNextToken(fb,&r,&t);
				}

	
		statement_list();
	}
	else
	{
		
		fseek(fb,-1,SEEK_CUR);
	}
}
	

	

void statement()
{
	
	if(lookahead->type==8)
	{

		assign_stat();

		lookahead=getNextToken(fb,&r,&t);

		if(strcmp(lookahead->ln,";")==0)
			return;
		else
		{
			printf("\n ; expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
		}
	}
	else if(strcmp(lookahead->ln,"if")==0)
	{
		decision_stat();
	}
	else if(strcmp(lookahead->ln,"while")==0||strcmp(lookahead->ln,"for")==0)
	{
		looping_stat();
	}
	else
	{
		printf("\n  identifier expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		exit(0);
	}
}
void assign_stat()
{
	if(lookahead->type==8)
	{
		lookahead=getNextToken(fb,&r,&t);
		
		if(strcmp(lookahead->ln,"=")==0)
		{
			lookahead=getNextToken(fb,&r,&t);
			

			expn();

		}
		else{
			printf("\n error = expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
		}
	}
	else
	{
		printf("\n error id expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void expn()
{
	if(lookahead->type==8||lookahead->type==6)
	{
		
		simple_expn();
		lookahead=getNextToken(fb,&r,&t);

		eprime();
	}
	else{
		printf("\n error id or num expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void eprime()
{
	if(lookahead->type==2||lookahead->type==3||lookahead->type==10)
	{
		relop();
		lookahead=getNextToken(fb,&r,&t);
		simple_expn();
	}
	else
		fseek(fb,-1,SEEK_CUR);
}
void simple_expn()
{
	if(lookahead->type==8||lookahead->type==6)
	{
		term();
		lookahead=getNextToken(fb,&r,&t);
		seprime();
	}
	else{
		printf("\n error id or num expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void seprime()
{
	if(strcmp(lookahead->ln,"+")==0||strcmp(lookahead->ln,"-")==0)
	{
		addop();
		lookahead=getNextToken(fb,&r,&t);
		term();
		lookahead=getNextToken(fb,&r,&t);
		seprime();

	}
	else
		fseek(fb,-1,SEEK_CUR);
}
void term()
{
	if(lookahead->type==8||lookahead->type==6)
	{
		factor();
		lookahead=getNextToken(fb,&r,&t);

		tprime();
	}
	else
	{
		printf("\n error id or num expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void tprime()
{
	if(strcmp(lookahead->ln,"*")==0||strcmp(lookahead->ln,"/")==0||strcmp(lookahead->ln,"%")==0)
	{
		mulop();

		
		lookahead=getNextToken(fb,&r,&t);
		
		factor();
		lookahead=getNextToken(fb,&r,&t);
		tprime();

	}
	else{
		fseek(fb,-1,SEEK_CUR);

	}
}
void factor()
{
		if(lookahead->type==8||lookahead->type==6)
		return;
	else
	{
		printf("\n error id or num expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void relop()
{
	
	if(strcmp(lookahead->ln,"==")==0||strcmp(lookahead->ln,"!=")==0||strcmp(lookahead->ln,"<=")==0||strcmp(lookahead->ln,">=")==0||strcmp(lookahead->ln,"<")==0||strcmp(lookahead->ln,">")==0)
	{
		
		return;
	}
	else
	{
		printf("\n error relational op expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void addop()
{
	if(strcmp(lookahead->ln,"+")==0||strcmp(lookahead->ln,"-")==0)
	{
		return;
	}
	else
	{
		printf("\n error + or - op expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void mulop()
{
	if(strcmp(lookahead->ln,"*")==0||strcmp(lookahead->ln,"/")==0||strcmp(lookahead->ln,"%")==0)
	{
		return;
	}
	else
	{
		printf("\n error * or / or modulus op expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
	}
}
void decision_stat()
{
	
	if(strcmp(lookahead->ln,"if")==0)
	{
		 lookahead=getNextToken(fb,&r,&t);
		 
		 if(strcmp(lookahead->ln,"(")==0)
		 {
		 	
		 	lookahead=getNextToken(fb,&r,&t);
		 
		 	expn();
		 	
		 	if(strcmp(lookahead->ln,")")==0)
		 	{
		 		
		 		lookahead=getNextToken(fb,&r,&t);
		 		lookahead=getNextToken(fb,&r,&t);
		 		while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				
				}
				
				
		 		if(strcmp(lookahead->ln,"{")==0)
		 		{
		 			lookahead=getNextToken(fb,&r,&t);
		 			
		 			statement_list();
		 			
		 			
		 			lookahead=getNextToken(fb,&r,&t);
		 			while(lookahead->type==0)
					{
					lookahead=getNextToken(fb,&r,&t);
					}
					
		 			if(strcmp(lookahead->ln,"}")==0)
		 			{
		 				
		 				dprime();
		 			}
		 			else
		 			{
		 				printf("\n }  expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
		 			}
		 		}
		 		else
		 		{
		 			printf("\n {  expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 			exit(0);
		 		}
		 	}
		 	else
		 		{
		 			printf("\n ) expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 			exit(0);
		 		}
		 }
		 else
		 		{
		 			printf("\n ( expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 			exit(0);
		 		}
	}
	else
		 		{
		 			printf("\n if expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 			exit(0);
		 		}
}
void dprime()
{
	
	lookahead=getNextToken(fb,&r,&t);
	while(lookahead->type==0)
					{
					lookahead=getNextToken(fb,&r,&t);
					}
	
if(strcmp(lookahead->ln,"else")==0)
	{
		 lookahead=getNextToken(fb,&r,&t);
		 while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
		 if(strcmp(lookahead->ln,"{")==0)
		 {
		 	lookahead=getNextToken(fb,&r,&t);
		 	while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
		 	statement_list();
		 	lookahead=getNextToken(fb,&r,&t);
		 	while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
		 	if(strcmp(lookahead->ln,"}")==0)
		 		return;
		 	else
		 	{
		 		printf("\n }  expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);exit(0);
		 	}
		 }
		 else
		 {
		 	printf("\n { expected \n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 }
		}
		else
		{
			
			fseek(fb,-1,SEEK_CUR);
			return;
		}
}
void looping_stat()
{
	if(strcmp(lookahead->ln,"while")==0)
	{
		lookahead=getNextToken(fb,&r,&t);
		
		 if(strcmp(lookahead->ln,"(")==0)
		 {
		 	lookahead=getNextToken(fb,&r,&t);

		 	expn();
		 	lookahead=getNextToken(fb,&r,&t);
		 	while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
				if(strcmp(lookahead->ln,")")==0)
				{
					lookahead=getNextToken(fb,&r,&t);
		 	while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
		 	if(strcmp(lookahead->ln,"{")==0)
		 {
		 	lookahead=getNextToken(fb,&r,&t);
		 	while(lookahead->type==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
		 	statement_list();
		 	lookahead=getNextToken(fb,&r,&t);
		 	while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
				{
					lookahead=getNextToken(fb,&r,&t);
				}
		 	if(strcmp(lookahead->ln,"}")==0)
		 {
		 	return;
		 }
		 else{
		 	printf("\n } expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 	exit(0);
		 }
		 }
		 else{
		 	printf("\n {  expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 	exit(0);
		 }
		}
		else
		{
			printf("\n ) expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		}
		 }
		
		 else{
		 	printf("\n ( expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 	exit(0);
		 }
	}
	if(strcmp(lookahead->ln,"for")==0)
	{
		lookahead=getNextToken(fb,&r,&t);
		 if(strcmp(lookahead->ln,"(")==0)
		 {
		 	lookahead=getNextToken(fb,&r,&t);
		 	assign_stat();
		 	lookahead=getNextToken(fb,&r,&t);
		 	if(strcmp(lookahead->ln,";")==0)
		 	{
		 		lookahead=getNextToken(fb,&r,&t);
		 		expn();
		 		lookahead=getNextToken(fb,&r,&t);
		 		if(strcmp(lookahead->ln,";")==0)
		 		{
		 			lookahead=getNextToken(fb,&r,&t);

		 			assign_stat();
		 			lookahead=getNextToken(fb,&r,&t);
		 			if(strcmp(lookahead->ln,")")==0)
		 			{
		 				lookahead=getNextToken(fb,&r,&t);
		 				while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
						{
							lookahead=getNextToken(fb,&r,&t);
						}
		 				if(strcmp(lookahead->ln,"{")==0)
		 				{
		 					lookahead=getNextToken(fb,&r,&t);
		 					statement_list();
		 					lookahead=getNextToken(fb,&r,&t);
		 					while(strcmp(lookahead->ln,"\0")==0||strcmp(lookahead->ln,"\t")==0||strcmp(lookahead->ln,"\n")==0)
								{
									lookahead=getNextToken(fb,&r,&t);
								}
						 	if(strcmp(lookahead->ln,"}")==0)
		 					{
		 						return;
		 					}
		 					else
		 					{
		 						printf("\n } expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
		 				}
		 				else
		 					{
		 						printf("\n { expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
		 			}
		 			else
		 					{
		 						printf("\n ) expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
		 		}
		 		else
		 					{
		 						printf("\n ; expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
		 	}
		 	else
		 					{
		 						printf("\n ; expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
		 }
		 else
		 					{
		 						printf("\n ( expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
	}
	else
		 					{
		 						printf("\n while or for expected\n row:%d col:%d\n present token:%s",lookahead->row,lookahead->col,lookahead->ln);
		 						exit(0);
		 					}
}
int main()
{

    fb=fopen("loop.c","r");
    lookahead=getNextToken(fb,&r,&t);
    
    program();
   
    lookahead=getNextToken(fb,&r,&t);
    
   if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nError");


}
