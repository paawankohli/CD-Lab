#include<stdio.h>
#include "la.c"
#include<string.h>
#include<stdlib.h>

FILE *file;
void program();
void declarations();
void data_type();
void statement_list();
void statement();
void term();
void expn();
void simple_expn();
void factor();
void assign_stat();
void addop();
void seprime();
void tprime();
void mulop();
void identifier_list();
void decision_stat();
void dprime();
void looping_stat();
void relopp();
void eprime();
void program()
{
	token t =getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"main")==0)
	{
		t=getNextToken(file);
		printf("%s\n",t.lexeme);
		if(strcmp(t.lexeme,"(")==0)
		{
			t=getNextToken(file);
			printf("%s\n",t.lexeme);
			if(strcmp(t.lexeme,")")==0)
			{
				t=getNextToken(file);
				printf("%s\n",t.lexeme);
				if(strcmp(t.lexeme,"{")==0)
				{
					declarations();
					statement_list();
					t=getNextToken(file);
					printf("%s\n",t.lexeme);
					if(strcmp("}",t.lexeme)==0)
						return;
				}
				else
				{
					printf("program type error\n");
					exit(0);
				}
			}
			else
			{
				printf("program type error\n");
				exit(0);
			}
		}
		else
		{
			printf("program type error\n");
			exit(0);
		}
	}
	else
	{
		printf("program error\n");
		exit(0);
	}
}
void declarations()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(iskeyword(t.lexeme))
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		data_type();
		t=getNextToken(file);
		printf("%s\n",t.lexeme);
		if(isIdentifier(t.lexeme))
		{
			fseek(file,-strlen(t.lexeme),SEEK_CUR);
			identifier_list();
			t=getNextToken(file);
			printf("%s\n",t.lexeme);
			if(t.lexeme[0]==';')
			{
				declarations();
			}
		}
		else
		{
			printf("data type error\n");
			exit(0);
		}
	}
	else
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		return;
	}
}
void identifier_list()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(isIdentifier(t.lexeme))
	{
		t=getNextToken(file);
		printf("2 %s\n",t.lexeme);
		if(strcmp(t.lexeme,"[")==0)
		{
			t=getNextToken(file);
			printf("%s\n",t.lexeme);
			if(isDigit(t.lexeme))
			{
				t=getNextToken(file);
				if(strcmp(t.lexeme,"]")==0)
				{
					t=getNextToken(file);
					if(strcmp(t.lexeme,",")==0)
					{
						identifier_list();
					}
					else
					{
						fseek(file,-strlen(t.lexeme),SEEK_CUR);
						return;
					}
				}
			}
		}
		else if(strcmp(t.lexeme,",")==0)
			identifier_list();
		else
		{
			fseek(file,-strlen(t.lexeme),SEEK_CUR);
			return;
		}
	}
}
void data_type()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(iskeyword(t.lexeme))
	{
		if((strcmp(t.lexeme,"int")==0) || (strcmp(t.lexeme,"char")==0))
			return;
	}
	else
	{
		printf("data type error\n");
		exit(0);
	}
}
void statement_list()
{
	token t=getNextToken(file);
	printf("4 %s\n",t.lexeme);
	if(isIdentifier(t.lexeme))
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		statement();
		statement_list();
	}
	else
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		return;
	}
}
void statement()
{
	token t=getNextToken(file);
	printf("%s statement \n",t.lexeme);
	if(iskeyword(t.lexeme))
	{
		printf("%s key of",t.lexeme);
		if(strcmp(t.lexeme,"if")==0)
		{
			fseek(file,-strlen(t.lexeme),SEEK_CUR);
			decision_stat();
		}
		else if(strcmp(t.lexeme,"for")==0){
			fseek(file,-strlen(t.lexeme),SEEK_CUR);
			looping_stat();
		}
		else{
			printf("error\n");
			exit(0);
		}
	}
	else if(isIdentifier(t.lexeme))
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		assign_stat();
		t=getNextToken(file);
		printf("5 %s\n",t.lexeme);
		if(strcmp(t.lexeme,";")==0)
			return;
		else
		{
			printf("data type error\n");
			exit(0);
		}
	}
	else
	{
		printf("error");
		exit(0);
	}
	
}
void assign_stat()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(isIdentifier(t.lexeme))
	{
		t=getNextToken(file);
		printf("%s\n",t.lexeme);
		if(strcmp(t.lexeme,"=")==0)
		{
			expn();
		}
		else
		{
			printf("assign error\n");
			exit(0);
		}
	}
	else 
	{
		printf("error\n");
		exit(0);
	}
}
void expn()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(isIdentifier(t.lexeme) || isDigit(t.lexeme))
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		simple_expn();
		eprime();
	}
	else
	{
		printf("error\n");
		exit(0);
	}
}
void simple_expn()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(isIdentifier(t.lexeme) || isDigit(t.lexeme))
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		term();
		seprime();
	}
	else
	{
		printf("error\n");
		exit(0);
	}
}
void term()
{
	token t=getNextToken(file);
	printf("2 %s\n",t.lexeme);
	if(isIdentifier(t.lexeme) || isDigit(t.lexeme))
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		factor();
		tprime();
	}
	else
	{
		printf("error\n");
		exit(0);
	}
}
void factor()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(isIdentifier(t.lexeme) || isDigit(t.lexeme))
	{
		//printf("herr\n");
		return;
	}
	else
	{
		printf("error\n");
		exit(0);
	}
}
void seprime()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"+")==0 || strcmp(t.lexeme,"-")==0)
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		addop();
		term();
		seprime();
	}
	else
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		return;
	}
}
void looping_stat()
{
	token t=getNextToken(file);
	if(strcmp(t.lexeme,"while")==0)
	{
		t=getNextToken(file);
		if(strcmp(t.lexeme,"(")==0)
		{
			expn();
			t=getNextToken(file);
			if(strcmp(t.lexeme,")")==0)
			{
				t=getNextToken(file);
				if(strcmp(t.lexeme,"{")==0)
				{
					statement_list();
					t=getNextToken(file);
					if(strcmp(t.lexeme,"}")==0)
					return;
				}
			}
		}
	}
	if(strcmp(t.lexeme,"for")==0)
	{
		t=getNextToken(file);
		if(strcmp(t.lexeme,"(")==0)
		{
			assign_stat();

			t=getNextToken(file);
			if(strcmp(t.lexeme,";")==0)
			{
				expn();
				t=getNextToken(file);
				if(strcmp(t.lexeme,";")==0)
				{
					assign_stat();
					t=getNextToken(file);
					if(strcmp(t.lexeme,")")==0){
						t=getNextToken(file);
				if(strcmp(t.lexeme,"{")==0)
				{
					statement_list();
					t=getNextToken(file);
					if(strcmp(t.lexeme,"}")==0)
					return;
				}
					}
					
				}
			}
		}
	}
}
void decision_stat()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"if")==0)
	{
		t=getNextToken(file);
		printf("%s of decision_stat\n",t.lexeme);
		if(strcmp(t.lexeme,"(")==0)
		{
			expn();
			t=getNextToken(file);
			if(strcmp(t.lexeme,")")==0)
			{
				t=getNextToken(file);
				if(strcmp(t.lexeme,"{")==0)
				{
					statement_list();
					t=getNextToken(file);
					if(strcmp(t.lexeme,"}")==0)
					{
						printf("decision_stat closing %s",t.lexeme);
						dprime();
					}
				}
			}
		}
	}
}
void dprime()
{
	token t=getNextToken(file);
	printf("%s",t.lexeme);
	if(strcmp(t.lexeme,"else")==0)
	{
		t=getNextToken(file);
		if(strcmp(t.lexeme,"{")==0)
		{
			statement_list();
			t=getNextToken(file);
			if(strcmp(t.lexeme,"}")==0)
			return;
		}
	}
	else
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		return;
	}
}
void addop()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"+")==0 || strcmp(t.lexeme,"-")==0)
	{
		return;
	}
	else
	{
		printf("error\n");
		exit(0);
	}
}
void tprime()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"*")==0 || strcmp(t.lexeme,"/")==0 || strcmp(t.lexeme,"%")==0)
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		mulop();
		factor();
		tprime();
	}
	else
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		return;
	}
}
void mulop()
{
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"*")==0 || strcmp(t.lexeme,"/")==0 || strcmp(t.lexeme,"%")==0)
	{
		return;
	}
	else
	{
		printf("error\n");
		exit(0);
	}
}
void eprime(){
	token t=getNextToken(file);
	printf("%s\n",t.lexeme);
	if(strcmp(t.lexeme,"==")==0||strcmp(t.lexeme,"!=")==0||strcmp(t.lexeme,"<=")==0||strcmp(t.lexeme,">=")==0||strcmp(t.lexeme,"<")==0||strcmp(t.lexeme,">")==0)
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		relopp();
		simple_expn();
	}
	else
	{
		fseek(file,-strlen(t.lexeme),SEEK_CUR);
		return;
	}
}
void relopp()
{
	token t=getNextToken(file);
	printf("relopp %s",t.lexeme);
	if(strcmp(t.lexeme,"==")==0||strcmp(t.lexeme,"!=")==0||strcmp(t.lexeme,"<=")==0||strcmp(t.lexeme,">=")==0||strcmp(t.lexeme,"<")==0||strcmp(t.lexeme,">")==0)
	{
		return;
	}
	else
	{
		printf("\n error relational op expected");exit(0);
	}
}
int main()
{
	file=fopen("t1.c","r");
	program();
	token t=getNextToken(file);
	if(strcmp(t.lexeme,"$")==0)
		printf("success\n");
	else
		printf("Error \n");
}

