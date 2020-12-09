#include<stdio.h>
#include<string.h>

struct token
{
	char lexeme[100];
};
typedef struct token token;
int isdelimiter(char ch)
{
	return(ch==','||ch=='$'||ch=='%'||ch=='"'||ch==' '||ch=='\n'||ch=='\t'||ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='='||ch==';'||ch=='('||ch==')'||ch=='}'||ch=='{'||ch=='<'||ch=='>'||ch=='|'||ch=='&'||ch=='['||ch==']');

}

int iskeyword(char *str)
{
	return (!strcmp(str,"int")||!strcmp(str,"char")||!strcmp(str,"if")||!strcmp(str,"for")||!strcmp(str,"while"));
}

int isIdentifier(char *str)
{
	if((str[0]>='0' && str[0]<='9') || isdelimiter(str[0]))
		return 0;
	else
	{
		for(int i=1;str[i]!='\0';i++)
		{
			if(isdelimiter(str[i]))
				return 0;
		}
	}
	return 1;
}
int isDigit(char *str)
{
	for(int i=0;i<strlen(str);i++)
	if(!(str[i]>='0' && str[i]<='9'))
		return 0;
	return 1;
}
int isoperator(char ch)
{
	return (ch=='+'||ch=='/'||ch=='*'||ch=='-'||ch=='%');
}
int relop(char ch)
{
	return(ch=='<'||ch=='>'||ch=='=');
}

token getNextToken(FILE *file)
{
	//FILE *file=fopen("t1.c","r");
	char ch;
	token tok;
	while((ch=fgetc(file))!=EOF)
	{
		if(!isdelimiter(ch))
		{
			int i=0;
			char str[50];
			while(isdelimiter(ch)==0)
			{
				str[i++]=ch;
				ch=fgetc(file);
			}
			str[i]='\0';
			fseek(file,-1,SEEK_CUR);
			//printf("here %s\n",str);
			if(iskeyword(str))
			{
				//strcpy(tok.lexeme,str);
				strcpy(tok.lexeme,str);
				return tok;
			}
			else if(isIdentifier(str))
			{
				strcpy(tok.lexeme,str);
				//printf("%s\n",tok.lexeme);
				return tok;
			}
			else if(isDigit(str))
			{
				strcpy(tok.lexeme,str);
				return tok;
			}
		}
		else
		{
			char x;
			if(ch=='=')
			{
				if((x=fgetc(file))=='=')
				{
					tok.lexeme[0]=ch;
					tok.lexeme[1]=x;
					tok.lexeme[2]='\0';
					return tok;
				}
				else
				{
					fseek(file,-1,SEEK_CUR);
					tok.lexeme[0]=ch;
					tok.lexeme[1]='\0';
					return tok;
				}
			}
			else if(ch=='>')
			{
				if((x=fgetc(file))=='=')
				{
					tok.lexeme[0]=ch;
					tok.lexeme[1]=x;
					tok.lexeme[2]='\0';
					return tok;
				}
				else
				{
					fseek(file,-1,SEEK_CUR);
					tok.lexeme[0]=ch;
					tok.lexeme[1]='\0';
					return tok;
				}
			}
			else if(ch=='>')
			{
				if((x=fgetc(file))=='=')
				{
					tok.lexeme[0]=ch;
					tok.lexeme[1]=x;
					tok.lexeme[2]='\0';
					return tok;
				}
				else
				{
					fseek(file,-1,SEEK_CUR);
					tok.lexeme[0]=ch;
					tok.lexeme[1]='\0';
					return tok;
				}
			}
			else if(ch=='!')
			{
				if((x=fgetc(file))=='=')
				{
					tok.lexeme[0]=ch;
					tok.lexeme[1]=x;
					tok.lexeme[2]='\0';
					return tok;
				}
			}
			else if(ch!='\n' && ch!=' ' && ch!='\t')
			{
				//printf("here %c",ch);
				tok.lexeme[0]=ch;
				tok.lexeme[1]='\0';
				return tok;
			}

		}
	}
	fclose(file);
}
// int main()
// {
// 	getNextToken();
// }
