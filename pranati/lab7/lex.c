#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct token
{
	char *tok;
	int row;
	int col;
}TOKEN;

TOKEN getNextToken(FILE *fp,int *r,int *c)
{
	if (fp==NULL)
	{
		TOKEN t;
		t.tok=NULL;
		t.row=NULL;
		t.col=NULL;
		return (t);
	}
	int ca=fgetc(fp);
	int cb;
	while(ca!=EOF)
	{
		
		if (ca=='#')
		{
			while(ca!='\n')
			{
				ca=fgetc(fp);
			}
		}
		else if (ca==' '||ca=='\t')
		{
	
		}
		else if (ca=='/')
		{
			cb=fgetc(fp);
			if (cb=='/')
			{
				while(ca!='\n')
					ca=fgetc(fp);
			}
			else if (cb=='*')
			{
				do
				{
					while(ca!='*')
						ca=fgetc(fp);
					ca=fgetc(fp);
				}
				while(ca!='/');
			}

		}
		else
		{
			TOKEN t;
			if (ca=='\n')
			{
				(*r)++;
				(*c)=0;
			}
			if (isalpha(ca))
			{
				char check[100];
				char arr[100][100]={"if","else","printf","while","for","do","return","exit","fopen","fclose","getc","putc","putchar"};
				int n=13;
				int colini=(*c);
				int ind=0;
				while (isalnum(ca))
				{
					
					check[ind++]=ca;
					ca=fgetc(fp);
					(*c)++;
				}
				check[ind]='\0';
				for (int i=0;i<n;i++)
			{
				if (strcmp(check,"main")==0)
				{
					t.tok="main";
					t.row=(*r);
					t.col=colini;
					return (t);
				}
				if (strcmp(check,"int")==0)
				{
					t.tok="int";
					t.row=(*r);
					t.col=colini;
					return (t);
				}
				if (strcmp(check,"char")==0)
				{
					t.tok="char";
					t.row=(*r);
					t.col=colini;
					return (t);
				}
				if (strcmp(check,arr[i])==0)
				{	
					t.tok="keyword";
					t.row=(*r);
					t.col=colini;
					return (t);
				}
			}
				t.tok="id";
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if (isdigit(ca))
			{
				int colini=(*c);
				while (isdigit(ca))
				{
					ca=fgetc(fp);
					(*c)++;
				}
				t.tok="number";
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if(ca=='\"')
			{
				int colini=(*c);
				ca=fgetc(fp);
				while (ca!='\"')
				{
					ca=fgetc(fp);
					(*c)++;
				}
				t.tok="string";
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if(ca=='>')
			{
				int colini=(*c);
				(*c)++;
				ca=fgetc(fp);
				if (ca=='=')
					t.tok="GE";
				else
					t.tok="GT";				
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if(ca=='<')
			{
				int colini=(*c);
				(*c)++;
				ca=fgetc(fp);
				if (ca=='=')
					t.tok="LE";
				else if(ca=='>')
					t.tok="NE";
				else
					t.tok="LT";
				
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if(ca=='=')
			{
				int colini=(*c);
				(*c)++;
				ca=fgetc(fp);
				if (ca=='=')
					t.tok="==";
				else
					t.tok="=";				
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if(ca=='&')
			{
				int colini=(*c);
				(*c)++;
				ca=fgetc(fp);
				if (ca=='&')
					t.tok="logicaland";
				else
					t.tok="SpecialSymbol";				
				t.row=(*r);
				t.col=colini;
				return (t);
			}
			else if(ca=='|')
			{
				int colini=(*c);
				(*c)++;
				ca=fgetc(fp);
				if (ca=='|')
					t.tok="logicalor";
				else
					t.tok="SpecialSymbol";				
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if(ca=='+')
			{
				(*c)++;
				t.tok="+";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if(ca=='-')
			{
				(*c)++;
				t.tok="-";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if(ca=='*')
			{
				(*c)++;
				t.tok="*";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if(ca=='/')
			{
				(*c)++;
				t.tok="/";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca==';')
			{
				(*c)++;
				t.tok=";";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca=='(')
			{
				(*c)++;
				t.tok="(";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca==')')
			{
				(*c)++;
				t.tok=")";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca=='{')
			{
				(*c)++;
				t.tok="{";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca=='}')
			{
				(*c)++;
				t.tok="}";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca==',')
			{
				(*c)++;
				t.tok="}";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca=='[')
			{
				(*c)++;
				t.tok="[";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
			else if (ca==']')
			{
				(*c)++;
				t.tok="]";
				t.row=(*r);
				t.col=(*c);
				return (t);
			}
		}
		ca=fgetc(fp);

	}

		TOKEN t;
		t.tok=NULL;
		t.row=NULL;
		t.col=NULL;
		return (t);

}
