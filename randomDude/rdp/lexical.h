#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Token{
	char ln[100];
	int row, col, type;
};
typedef struct Token* tokenptr;

tokenptr getNextToken(FILE *fa, int *l, int *c){
	char a[100], ch, temp, i=0, keys[][20]= {"int", "char", "if", "else", "while", "void", "for", "return"};
	tokenptr newToken=(tokenptr)malloc(sizeof(struct Token));
	ch = getc(fa);
	if(ch==EOF){
		newToken = NULL;
		return newToken;
	}
	a[i]=ch;
	i++;
	newToken->row = *l;
	newToken->col = *c;

	if(ch == '\n'){
		*c=0;
		(*l)++;
		newToken->type = 0;
		return newToken;
	}

	if(ch == '#'){
		ch = getc(fa);
		while(ch!='\n')
			ch = getc(fa);
		(*l)++;
		newToken->type = 0;
		return newToken;
	}

	temp=ch;
	if(temp=='/'){
		temp = getc(fa);
		if(temp == '*'){
			*c+=2;
			while(1){
				temp = getc(fa);
				(*c)++;
				if(temp == '\n'){
					*c = 0;
					(*l)++;
				}
				if(temp == '*'){
					char t = getc(fa);
					if(t == '/'){
						(*c)++;
						newToken->type = 0;
						return newToken;
					}
					fseek(fa, -1, SEEK_CUR);
				}
			}
		}
		else if(temp == '/'){
			*c+=2;
			while(1){
				temp = getc(fa);
				(*c)++;
				if(temp == '\n'){
					*c = 0;
					(*l)++;
					newToken->type = 0;
					return newToken;
				}
			}
		}
	}

	if(ch == '"'){
		(*c)++;
		ch = getc(fa);
		while(ch!='"'){
			(*c)++;
			a[i]=ch;
			i++;
			ch = getc(fa);
		}
		a[i]=ch;
		a[i+1]='\0';
		strcpy(newToken->ln, a);
		newToken->type = 7;
		return newToken;
	}

	if(ch == ' ' || ch =='\t'){
		(*c)++;
		newToken->type = 0;
		return newToken;
	}

	if(ch=='+'||ch=='-'||ch=='/'||ch=='*'||ch=='%'){
		(*c)++;
		ch=getc(fa);
		if(ch=='='){
			a[i] = ch;
			i++;
			(*c)++;
			a[i] = '\0';
			newToken->type = 9;
			strcpy(newToken->ln, a);
			return newToken;
		}
		else{
			a[i]='\0';
			newToken->type = 1;
			strcpy(newToken->ln, a);
			fseek(fa, -1, SEEK_CUR);
			return newToken;
		}
	}

	if(ch == '<' || ch == '>' || ch == '!' || ch == '='){
		(*c)++;
		ch = getc(fa);
		if(ch=='='){
			a[i] = ch;
			i++;
			(*c)++;
			a[i] = '\0';
			newToken->type = 2;
			strcpy(newToken->ln, a);
			return newToken;
		}
		else{
			a[i]='\0';
			if(a[0]=='!')
				newToken->type = 3;
			else if(a[0]=='=')
				newToken->type = 10;
			else
				newToken->type = 2;
			strcpy(newToken->ln, a);
			fseek(fa, -1, SEEK_CUR);
			return newToken;
		}
	}

	if(isalpha(ch)||ch=='_'){
		(*c)++;
		ch = getc(fa);
		while(isalpha(ch)||ch=='_'||(ch>='0'&&ch<='9')){
			a[i]=ch;
			i++;
			(*c)++;
			ch = getc(fa);
		}
		a[i]='\0';
		fseek(fa, -1, SEEK_CUR);
		strcpy(newToken->ln, a);int i;
		for( i=0; i<8; i++)
			if(strcmp(a, keys[i])==0){
				newToken->type = 5;
				return newToken;
			}
		newToken->type = 8;
		return newToken;
	}

	if(isdigit(ch)){
		(*c)++;
		ch = getc(fa);
		while(isdigit(ch)||ch=='.'){
			a[i]=ch;
			i++;
			(*c)++;
			ch = getc(fa);
		}
		a[i]='\0';
		fseek(fa, -1, SEEK_CUR);
		strcpy(newToken->ln, a);
		newToken->type = 6;
		return newToken;
	}

	a[i]='\0';
	strcpy(newToken->ln, a);
	newToken->type = 4;
	return newToken;
}
