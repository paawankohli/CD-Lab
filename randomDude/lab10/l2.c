%{
	int words=0;
	int chars=0;
	int line=0;
	int blank=0;
%}
%%
[a-zA-Z]+ {words++; chars+=strlen(yytext);}
\n line++;
" " blank++;
. {chars++;}
%%

int yywrap(){
	return 1;
}
int main() 
{ 
	
	yylex(); 
	printf("Number of words  are: %d\n", words); 
	printf("Number of characters  are: %d\n", chars); 
	printf("Number of spaces are: %d\n", blank); 
	printf("Number of lines  are: %d\n", line); 
	return 0; 
} 
