#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUMKEYWORDS 7

typedef struct{
	int row;
	int col;
	int type;
	char *lexeme;
}token;

typedef struct symbol{
	char name[20];
	char type[20];
	int size;
	char scope;
	int num_arg;
	char return_type[20];
}symbol;

void readFileComplete(FILE *fa, FILE* fb);
int currState(int ch,FILE *fa,FILE *fb);
int spacehandle(char delim,FILE *fa);
int multi_comm_handle(FILE *fa);
int single_comm_handle(FILE *fa);
int newline_handle(FILE *fa);
int quotes_handle(FILE *fb,FILE *fa,char ch);
int normal_cases_handle(int ch,FILE *fa,FILE *fb);
int check_operator(int op);
int operator_handle(int ch,FILE *fa,FILE *fb);
int word_handle(int ch,FILE *fa,FILE *fb);
int SS_handle(int ch,FILE *fa,FILE *fb);
int numeric_handle(int ch,FILE *fa,FILE *fb);

int LINE = 0;
int COL = 0;
int braces_count = 0;
int table_index = 0;
symbol symbol_table[100];
char prev_type[20];
int next_param = 0;

void show_symbol_table()
{
	printf("name \t type \t size \t scope \t num_arg return_type\n");
	for(int i =0;i<table_index-1;i++)
	{
		printf("%s \t %s \t %d \t %c \t %d \t %s\n",symbol_table[i].name,symbol_table[i].type,symbol_table[i].size,symbol_table[i].scope,symbol_table[i].num_arg,symbol_table[i].return_type);
	}
}


int main(){
	braces_count = 0;
	FILE *fa,*fb;
	fa = fopen("fac.c","r");
	fb = fopen("q1out.txt","w");
	if(fa == NULL){
		printf("error opening file\n");
		exit(0);
	}
	readFileComplete(fa,fb);
	show_symbol_table();
}

int currState(int ch,FILE *fa,FILE *fb){
	//Used for ignoring quotes, comments, spaces etc.
	while(ch == ' ' || ch == '\t' || ch == '\n' || ch == '/' || ch == '"'){
		if (ch == ' '){
			ch = spacehandle(' ',fa);
		}
		else if(ch == '\t'){
			//printf("tab scanned\n");
			ch = spacehandle('\t',fa);
		}
		else if(ch == '/'){
			ch = getc(fa);
			COL++;
			if(ch == '*'){
				ch = multi_comm_handle(fa);
			}
			else if(ch == '/'){
				ch = single_comm_handle(fa);
			}
			else{
				normal_cases_handle(ch,fa,fb);
			}
		}
		else if(ch == '\n'){
			ch = newline_handle(fa);
		}
		else if(ch == '"'){
			ch = quotes_handle(fb,fa,ch);
		}
	}
	ch = normal_cases_handle(ch,fa,fb);
	return ch;
}

void readFileComplete(FILE *fa,FILE *fb){
	//Used for reading all characters till end of file
	int ch = getc(fa);
	COL++;
	while(ch != EOF){
		ch = currState(ch,fa,fb);
	}
}

int spacehandle(char delim,FILE *fa){
	//handles COL value for spaces
	int temp;
	do{
		if(temp == '\t'){
			COL = COL + 4;
		}
		else{
			COL++;
		}
		temp = getc(fa);
	}
	while(temp == delim);
	return temp;
}

int multi_comm_handle(FILE *fa){
	//handles multi line comments
	int tem;
	while(1){
		do{
			tem = getc(fa);
			COL++;
		}
		while(tem != '*');
		tem = getc(fa);
		COL++;
		if(tem == '/'){
			tem = getc(fa);
			COL++;
			return tem;
		}
	}
}

int single_comm_handle(FILE *fa){
	//handles single line comments
	int tem;
	do{
		tem = getc(fa);
		COL++;
	}
	while(tem != '\n');
	COL = 0;
	LINE++;
	tem = getc(fa);
	COL++;
	return tem;
}

int newline_handle(FILE *fa){
	//handles single or multiple newline characters
	int tem;
	do{
		tem = getc(fa);
		COL = 0;
		LINE++;
	}
	while(tem == '\n');
	return tem;
}

int quotes_handle(FILE *fb,FILE *fa,char ch){
	//used for ignoring quotes
	/*int tem;
	do{
		tem = getc(fa);
		COL++;
	}
	while(tem != '"');*/
	char str[10] = "";
	char temp[2];
	temp[1] = '\0';
	temp[0] = ch;
	do{
		strcat(str,temp);
		temp[0] = getc(fa);
		COL++;
	}while((temp[0] >= 65 && temp[0] <= 90) || (temp[0] >= 97 && temp[0] <= 122) || temp[0] == '_');
	fprintf(fb,"<%s,%d,%ld,SL>\n",str,LINE,COL-strlen(str));
	temp[0] = getc(fa);
	return temp[0];
}

int normal_cases_handle(int ch,FILE *fa,FILE *fb){
	//used for regular lexical analysis and detecting lexemes
	int rch;
	if (check_operator(ch)){
		rch = operator_handle(ch,fa,fb);
	}
	else if((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == '_'){
		rch = word_handle(ch,fa,fb);
	}
	else if(ch >= 48 && ch <= 57){
		rch = numeric_handle(ch,fa,fb);
	}
	else{
		rch = SS_handle(ch,fa,fb);
	}
	return rch;
}

int check_operator(int op){
	//checks if its and operator
	token tk;
	if(op == '<' || op == '+' || op == '>' || op == '=' || op == '*' || op == '/' || op == '&' || op == '%'){
		return 1;
	}
	return 0;
}

int numeric_handle(int ch,FILE *fa,FILE *fb){
	//handles numeric constants
	char str[10] = "";
	char temp[2];
	temp[1] = '\0';
	temp[0] = ch;
	do{
		strcat(str,temp);
		temp[0] = getc(fa);
		COL++;
	}
	while((temp[0] >= 48 && temp[0] <= 57));
	// fprintf(fb,"<%s,%d,%ld,NC>\n",str,LINE,COL-strlen(str));
	//printf("NUMBER CONST %s ROW %d COL %d\n",str,LINE,COL);
	return temp[0];
}

int operator_handle(int ch,FILE *fa,FILE *fb){
	//handles operators
	char str[5] = "";
	char temp[2];
	temp[1] = '\0';
	temp[0] = ch;
	strcat(str,temp);
	temp[0] = (char)getc(fa);
	if(check_operator(temp[0])){
		strcat(str,temp);
		temp[0] = getc(fa);
		COL++;
	}
	// fprintf(fb,"<%s,%d,%ld,OP>\n",str,LINE,COL-strlen(str));
	//printf("OPERATOR: %s ROW:%d COL:%ld\n",str,LINE,COL-strlen(str));
	return temp[0];
}

int prev_type_size()
{
	if(strcmp(prev_type,"int"))
		return sizeof(int);
	if(strcmp(prev_type,"char"))
		return sizeof(char);
	if(strcmp(prev_type,"float"))
		return sizeof(float);
	if(strcmp(prev_type,"double"))
		return sizeof(double);
	
}

char function_found(char *str, FILE *fa)
{
	strcpy(symbol_table[table_index].name,str);
	strcpy(symbol_table[table_index].type,"FUNC");
	symbol_table[table_index].scope = 'G';
	strcpy(symbol_table[table_index].return_type,prev_type);

	int check = getc(fa);
	
	while(check == ' ' || check == '\t' || check == '(')
		check = getc(fa);

	if(check == ')')
		symbol_table[table_index].num_arg = 0;
	else
	{
		symbol_table[table_index].num_arg = 1;
		next_param = 1;
	}

	return check;

}

int search_table(char *str)
{
	for(int i =0;i<table_index;i++)
	{
		if(strcmp(str,symbol_table[i].name) == 0)
			return 1;
	}
	return 0;
}


int word_handle(int ch,FILE *fa,FILE *fb){
	//handles keywords and identifiers
	char str[10] = "";
	char temp[2];
	temp[1] = '\0';
	temp[0] = ch;
	do{
		strcat(str,temp);
		temp[0] = getc(fa);
		COL++;
	}
	while((temp[0] >= 65 && temp[0] <= 90) || (temp[0] >= 97 && temp[0] <= 122) || temp[0] == '_');
	char kwds[NUMKEYWORDS][10] = {"return","if","else","for","while","break","do"};
	int i;

	for(i = 0;i < NUMKEYWORDS;i++){
		if(strcmp(kwds[i],str) == 0){

			// fprintf(fb,"<%s,%d,%ld,KW>\n",str,LINE,COL-strlen(str));
			//printf("KEYWORD %s ROW %d COL %ld\n",str,LINE,COL-strlen(str));
			return temp[0];
		}
	}
	char types_avail[4][10] = {"int","char","float","double"};
	for(i = 0;i < 4;i++){
		if(strcmp(types_avail[i],str) == 0){

			strcpy(prev_type,str);
			fprintf(fb,"<%s,%d,%ld,KW>\n",str,LINE,COL-strlen(str));
			//printf("KEYWORD %s ROW %d COL %ld\n",str,LINE,COL-strlen(str));
			return temp[0];
		}
	}

	if(search_table(str) == 1)
	{
		return temp[0];
	}


	FILE *ftemp = fa;

	int check = temp[0];
	
	while(check == ' ' || check == '\t')
		check = getc(ftemp);

	if(check != '(') //identifier
	{
		strcpy(symbol_table[table_index].name,str);
		strcpy(symbol_table[table_index].type,prev_type);

		symbol_table[table_index].size = prev_type_size();
		if(braces_count == 0 && next_param == 0)

			symbol_table[table_index].scope = 'G';
		else
		{
			symbol_table[table_index].scope = 'L';
			next_param = 0;
		}

		fprintf(fb,"<id,%d>\n",table_index);
	}
	else
	{
		temp[0] = function_found(str,fa);
		fprintf(fb,"<id,%d>\n",table_index);

	}
	table_index++;



	// for(i = 0;i < NUMKEYWORDS;i++){
	//     if(!strcmp(kwds[i],str)){
	//         fprintf(fb,"<%s,%d,%ld,KW>\n",str,LINE,COL-strlen(str));
	//         //printf("KEYWORD %s ROW %d COL %ld\n",str,LINE,COL-strlen(str));
	//         break;
	//     }
	// }
	// if(i == NUMKEYWORDS){
	//     fprintf(fb,"<%s,%d,%ld,ID>\n",str,LINE,COL-strlen(str));
	//     //printf("IDENTIFIER %s ROW %d COL %ld\n",str,LINE,COL-strlen(str));
	// }
	return temp[0];
}

int SS_handle(int ch,FILE *fa,FILE *fb){
	//handles special symbols
	char temp;
	if(ch == '#'){
		do{
			temp = getc(fa);
			COL++;
		}
		while(temp != '\n');
		LINE++;
		COL = 0;
		temp = getc(fa);
		return temp;
	}
	else if(ch == '(' || ch == ')' || ch == ',' || ch == ';' || ch == '{' || ch == '}'){
		if(ch == '{')
		{
			braces_count++;
		}
		if(ch == '}')
		{
			braces_count--;
		}
		fprintf(fb,"<%c,%d,%d,SS>\n",ch,LINE,COL);
		//printf("SPECIAL %c ROW %d COL %d\n",ch,LINE,COL);
		temp = getc(fa);
		COL++;
		return temp;
	}
}