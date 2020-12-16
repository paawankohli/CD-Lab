#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "la.c"

token cT;
FILE *f,*lex,*st;
void invalid(char* exp,int r, int c)
{
	printf("expected '%s' at row %d col %d\n",exp,r,c);
	exit(0);
}
void valid()
{
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}
void Program();
void declarations();
void data_type();
void identifier_list();
void ilprime();
void ilpprime();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
token getNext()
{
	return getNextToken(f,lex,st);
}
void Program()
{
	cT = getNext();
	if (strcmp(cT.token_name,"main") == 0)
	{
		cT = getNext();
		if (strcmp(cT.token_name,"(") == 0)
		{
			cT = getNext();
			if (strcmp(cT.token_name,")") == 0)
			{
				cT = getNext();
				if (strcmp(cT.token_name,"{") == 0)
				{
					cT = getNext();
					declarations();
					statement_list();
					if (strcmp(cT.token_name,"}") == 0)
					{
						cT = getNext();
						return;
					}
					else
						invalid("}",cT.row,cT.col);
				}
				else
					invalid("{",cT.row,cT.col);
			}
			else
				invalid(")",cT.row,cT.col);
		}
		else
			invalid("(",cT.row,cT.col);
	}
	else
		invalid("main",cT.row,cT.col);
}
void declarations()
{
	char firstofdata_type[20][20] = {"int", "char"};
	int nof = 2;
	int flag = 0;
	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name,firstofdata_type[i])) == 0)
			flag++;
	if (flag)
	{
		data_type();
		identifier_list();
		if (strcmp(cT.token_name,";") == 0)
		{
			cT = getNext();
			declarations();
		}
		else
			invalid(";",cT.row,cT.col);
	}
}
void data_type()
{
	if (strcmp(cT.token_name,"int") == 0)
	{
		cT = getNext();
		return;
	}
	else if (strcmp(cT.token_name,"char") == 0)
	{
		cT = getNext();
		return;
	}
	else
	invalid("int or char",cT.row,cT.col);
}
void identifier_list()
{
	if (strcmp(cT.token_name,"id") == 0)
	{
		cT = getNext();
		ilprime();
	}
	else
		invalid("identifier",cT.row,cT.col);
}
void ilprime()
{
	if (strcmp(cT.token_name,",") == 0)
	{
		cT = getNext();
		identifier_list();
	}
	else if (strcmp(cT.token_name,"[") == 0)
	{
		cT = getNext();
		if (strcmp(cT.token_name,"num") == 0)
		{
			cT = getNext();
			if (strcmp(cT.token_name,"]") == 0)
			{
				cT = getNext();
				ilpprime();
			}
			else
				invalid("]",cT.row,cT.col);
		}
		else
			invalid("number",cT.row,cT.col);
	}
}
void ilpprime()
{
	if (strcmp(cT.token_name,",") == 0)
	{
		cT = getNext();
		identifier_list();
	}
}
void statement_list()
{
	char firstofstatement[20][20] = {"id"};
	int nof = 1;
	int flag = 0;
	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name,firstofstatement[i])) == 0)
			flag++;
	if (flag)
	{
		statement();
		statement_list();
	}
}
void statement()
{
	assign_stat();
	if (strcmp(cT.token_name,";") == 0)
	{
		cT = getNext();
		return;
	}
	else
		invalid(";",cT.row,cT.col);
}
void assign_stat()
{
	if (strcmp(cT.token_name,"id") == 0)
	{
		cT = getNext();
		if (strcmp(cT.token_name,"ASS") == 0)
		{
			cT = getNext();
			expn();
		}
		else
			invalid("=",cT.row,cT.col);
	}
	else
	invalid("identifier",cT.row,cT.col);
}
void expn()
{
	simple_expn();
	eprime();
}
void eprime()
{
	char firstofrelop[20][20] = {"RelOp"};
	int nof = 1;
	int flag = 0;
	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name,firstofrelop[i])) == 0)
			flag++;
	if (flag)
	{
		relop();
		simple_expn();
	}
}
void simple_expn()
{
	term();
	seprime();
}
void seprime()
{
	char firstofaddop[20][20] = {"ArOp"};
	int nof = 1;
	int flag = 0;
	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name,firstofaddop[i])) == 0 && cT.index < 3)
			flag++;
	if (flag)
	{
		addop();
		term();
		seprime();
	}
}
void term()
{
	factor();
	tprime();
}
void tprime()
{
	char firstofmulop[20][20] = {"ArOp"};
	int nof = 1;
	int flag = 0;
	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name,firstofmulop[i])) == 0 && cT.index > 2)
			flag++;
	if (flag)
	{
		mulop();
		factor();
		tprime();
	}
}
void factor()
{
	if (strcmp(cT.token_name,"id") == 0)
	{
		cT = getNext();
		return;
	}
	else if (strcmp(cT.token_name,"num") == 0)
	{
		cT = getNext();
		return;
	}
	else
	invalid("identifier or number",cT.row,cT.col);
}
void relop()
{
	if (strcmp(cT.token_name,"RelOp") == 0)
	{
		cT = getNext();
		return;
	}
	else
		invalid("relational operator",cT.row,cT.col);
}
void addop()
{
	if (strcmp(cT.token_name,"ArOp") == 0 && cT.index < 3)
	{
		cT = getNext();
		return;
	}
	else
		invalid("addition or subtraction operator",cT.row,cT.col);
}
void mulop()
{
	if (strcmp(cT.token_name,"ArOp") == 0 && cT.index > 2)
	{
		cT = getNext();
		return;
	}
	else
		invalid("multiplication, division or modulus operator",cT.row,cT.col);
}	
int main()
{
	currTable.entries = 0;
	f = fopen("in.c","r");
	lex = fopen("lex.txt","w");
	st = fopen("st.txt","w");
	Program();
	if (strcmp(cT.token_name,"$") == 0)
		valid();
	else
		invalid("EOF",cT.row,cT.col);
	fclose(f);
	fclose(lex);
	fclose(st);
	return 0;
}
