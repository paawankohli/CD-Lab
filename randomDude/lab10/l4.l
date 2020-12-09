/* Lex program to search a word in a file */

%{ 
/* Definition section */
#include<string.h> 
void check(char *); 
%} 

/* Rule Section */
%% 
[a-zA-Z]+ check(yytext); 
%% 

// driver code 
int main() 
{ 
	// The function that starts the analysis 
	yylex(); 
	return 0; 
} 
void check(char *str) 
{ 
	/* fp as pointer 
	of File type */
	FILE *fp; 
	char temp[30]; 
	
	
	/* fp points to the file input.txt 
	and opens it in read mode */
	fp=fopen("input.txt", "r"); 
	while((fscanf(fp, "%s", temp))!=EOF) 
	{ 
		if(!(strcmp(temp, str))) 
		{ 
			printf("FOUND\n"); 
			return; 
		} 
		
	} 
	printf("NOT FOUND\n"); 
		return; 
} 
