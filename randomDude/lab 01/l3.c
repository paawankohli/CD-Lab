#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define MAX 1000
// List of tokens
const char *keywords[32] = {
	"auto",
	"double",
	"int",
	"struct",
	"break",
	"else",
	"long",
	"switch",
	"case",
	"enum",
	"register",
	"typedef",
	"char",
	"extern",
	"return",
	"union",
	"continue",
	"for",
	"signed",
	"void",
	"do",
	"if",
	"static",
	"while",
	"default",
	"goto",
	"sizeof",
	"volatile",
	"const",
	"float",
	"short",
	"unsigned"
};

int isKeyword (char *word) {
	int i;
	for (i = 0; i < 32; ++i) {
		if (strcmp(word, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}
void printUpperCase (char *word) {
	int l = strlen(word);
	char z;
	int i;
	for (i = 0; i < l; ++i) {
		z = word[i];
		printf("%c", z > 96 ? z - 32 : z);
	}
	printf("\n");
}


int main()
{
	FILE *input,*output;
	char ca,*tok;
	input=fopen("l2in.c","r");
	if(input==NULL){
		printf("error");
		exit(0);
	}
	output=fopen("l2out.c","w");
	char *buff[MAX];
	ca=getc(input);
	while(ca!=EOF)
	{
		fgets(buff,MAX,input);
		tok=strtok(buff," \t");
		while

	}

}