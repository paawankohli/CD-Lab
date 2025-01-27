#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int row = 1;
int col = 0;
char keyword[][20]={"main","int","if","else","while","for","char","do","bool","void","scanf","printf","return"};
int nok = 13;
char dtype[][20]={"int","char","bool","void"};
int nod = 4;
char dbuff[20];
int expectID = 0;
char currTableName[20];

typedef struct {
	char token_name[20];
	unsigned int row,col;
	int index;
}token;

typedef struct
{
	int index;
	char Lex_name[20];
	char type[20];
	int size;
}tableRow;
typedef struct
{
	int entries;
	tableRow tR[20];
}table;
table currTable;
void reset_table()
{
	currTable.entries = 0;
}
void print_table(FILE* out)
{
	if (currTable.entries == 0)
		return;
	fprintf(out,"%s\n\tLex_Name\tType\tSize\n", currTableName);
	for (int i = 0; i < currTable.entries; i++)
		fprintf(out, "%d\t%s\t\t%s\t%d\n",currTable.tR[i].index,currTable.tR[i].Lex_name,currTable.tR[i].type,currTable.tR[i].size);
	fprintf(out, "\n");
}
token create_token(char n[],int r, int c, int i)
{
	token m;
	strcpy(m.token_name,n);
	m.row = r;
	m.col = c;
	m.index = i;
	return m;
}
void insert(char n[],char t[], int s)
{
	int m = currTable.entries;
	currTable.tR[m].index = m+1;
	strcpy(currTable.tR[m].Lex_name,n);
	strcpy(currTable.tR[m].type,t);
	currTable.tR[m].size = s;
	currTable.entries++;
}
void print_token(token t,FILE* out)
{
	fprintf(out,"<%s,%d,%d,%d>",t.token_name,t.row,t.col,t.index);
}
int search(char* name)
{
	int i;
	for (i = 0; i < currTable.entries; i++)
		if (strcmp(name,currTable.tR[i].Lex_name) == 0)
			return i+1;
	return 0;
}
token ArOp(int key, int r, int c)
{
	return create_token("ArOp",r,c,key);
}
token RelOp(int key, int r, int c)
{
	return create_token("RelOp",r,c,key);
}
token LogOp(int key, int r, int c)
{
	switch(key)
	{
		case 1:
			return create_token("AND",r,c,-1);
		case 2:
			return create_token("ORR",r,c,-1);
		case 3:
			return create_token("NOT",r,c,-1);						
	}
}
token AssOp(int key, int r, int c)
{
	switch(key)
	{
		case 1:
			return create_token("ASS",r,c,-1);
		case 2:
			return create_token("ADA",r,c,-1);
		case 3:
			return create_token("SBA",r,c,-1);
		case 4:
			return create_token("MLA",r,c,-1);
		case 5:
			return create_token("DVA",r,c,-1);
		case 6:
			return create_token("MDA",r,c,-1);								
	}
}
token SpecChar(char n, int r,int c,int i)
{
	char temp[2];
	temp[0] = n;
	temp[1] = '\0';
	return create_token(temp,r,c,i);
}
token getNextToken(FILE* f,FILE* out, FILE* st)
{
	int c,cn;
	int t_index = -1;
	c = getc(f);
	col++;
	if (c == EOF)
	{
		print_table(st);
		return create_token("$",row,col,-1);
	}
	token T;
	if (c == '\n')
	{
		c=getc(f);
		row++;
		col = 1;
	}
	if (c == '/')
	{ 
		c = getc(f);
		if (c == '/')
		{
			do
			{
				c = getc(f);
			}while(c != '\n');
			row++;
			col = 0;
		}
		else if (c == '*')
		{
			do
			{
				do
				{
					c = getc(f);
				}while(c != '*');
				c = getc(f);
			}while(c != '/');
			c = getc(f);
			col--;
		}
		else
		{
			fseek(f,-2,SEEK_CUR);
			c = getc(f);
		}
	}
	if (c == '\"')
	{
		int length = 0;
		do
		{
			c = getc(f);
			length++;
		}while (c != '\"');
		T=create_token("string",row,col,-1);
		col += length;
	}
	else if (c == '#')
	{
		do
		{
			c = getc(f);
		}while(c!='\n');
		row++;
		col = 0;
		return getNextToken(f,out,st);
	}
	else if (c == '+')
	{
		c = getc(f);
		if (c == '+')
		{
			T = ArOp(6,row,col);
			col++;
		}
		else if (c == '=')
		{
			T = AssOp(2,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = ArOp(1,row,col);
		}
	}
	else if (c == '-')
	{
		c = getc(f);
		if (c == '-')
		{
			T = ArOp(7,row,col);
			col++;
		}
		else if (c == '=')
		{
			T = AssOp(3,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = ArOp(2,row,col);
		}
	}
	else if (c == '*')
	{
		c = getc(f);
		if (c == '=')
		{
			T = AssOp(4,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = ArOp(3,row,col);
		}
	}
	else if (c == '/')
	{
		c = getc(f);
		if (c == '=')
		{
			T = AssOp(5,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = ArOp(4,row,col);
		}
	}
	else if (c == '%')
	{
		c = getc(f);
		if (c == '=')
		{
			T = AssOp(6,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = ArOp(5,row,col);
		}
	}
	else if (c == '=')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(1,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = AssOp(1,row,col);
		}
	}
	else if (c == '!')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(2,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = LogOp(3,row,col);
		}
	}
	else if (c == '>')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(5,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = RelOp(3,row,col);
		}
	}
	else if (c == '<')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(6,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = RelOp(4,row,col);
		}
	}
	else if (c == '&')
	{
		c = getc(f);
		if (c == '&')
		{
			T = LogOp(1,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = SpecChar('&',row,col,-1);
		}
	}
	else if (c == '|')
	{
		c = getc(f);
		if (c == '|')
		{
			T = LogOp(2,row,col);
			col++;
		}
		else
		{
			fseek(f,-1,SEEK_CUR);
			T = SpecChar('|',row,col,-1);
		}
	}
	else if (isalpha(c))
	{
		int length = 0;
		int flag = 0;
		char buffer[20];
		do
		{
			buffer[length++] = c;
			c = getc(f);
		}while(isalpha(c));
		buffer[length]='\0';
		for (int j = 0; j < nok; j++)
			if (strcmp(keyword[j],buffer)==0)
			{
				for (int k = 0; k < nod; k++)
					if (strcmp(dtype[k],buffer) == 0)
					{
						strcpy(dbuff,buffer);
						expectID = 1;
					}
				T = create_token(buffer,row,col,t_index);
				flag++;
				break;
			}
			if (strcmp(buffer,"main") == 0)
			{
				print_table(st);
				reset_table();
				strcpy(currTableName,buffer);
				t_index = 0;
			}				
		if (flag == 0)
		{
			fseek(f,-1,SEEK_CUR);
			char d = getc(f);
			if (expectID == 1 && d == '(')
			{
				print_table(st);
				reset_table();
				strcpy(currTableName,buffer);
				t_index = 0;
			}
			else if (expectID == 1)
			{
				int t_size;
				switch(dbuff[0])
				{
					case 'i':
					{
						t_size = 4;
						break;
					}
					case 'c':
					{
						t_size = 1;
						break;
					}
					case 'v':
					{
						t_size = 4;
						break;
					}
					case 'b':
					{
						t_size = 1;
						break;
					}
					
				}
				if (d == '[')
				{
					int elements = 0;
					int extracount = 1;
					d = getc(f);
					while (d != ']')
					{
						elements *= 10;
						elements += (d-48);
						d = getc(f);
						extracount++;
					}
					fseek(f,-1*extracount,SEEK_CUR);
					t_size *= elements;
				}
				insert(buffer,dbuff,t_size);
				t_index = currTable.entries;				
			}
			else if(d == '(')
			{
				if (search(buffer) == 0)
				{
					insert(buffer,"func",-1);
					t_index = currTable.entries;
				}
				else
				{
					t_index = search(buffer);
				}
			}
			else
				t_index = search(buffer);
			length--;
			T = create_token("id",row,col,t_index);
		}
		fseek(f,-1,SEEK_CUR);
		col += length;
	}
	else if (isdigit(c) || c == '.')
	{
		int length = 0;
		do
		{
			length++;
			c = getc(f);
		}while(isdigit(c) || c == '.');
		T = create_token("num",row,col,-1);
		col += length-1;
		fseek(f,-1,SEEK_CUR);
	}
	else
		T = SpecChar(c,row,col,-1);
	if (c == ';' || c == '(' || c == '=' || c == ')')
		expectID = 0;
	if (T.token_name[0] != '\n' && T.token_name[0] != ' ' && T.token_name[0] != '\t')
	{
		print_token(T,out);
		return T;
	}
	return getNextToken(f,out,st);
}