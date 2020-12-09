#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define size 30
int flag=0;
struct Token{
char ln[100];
int row, col, type;
};
typedef struct Token* tokenptr;

struct list{
	char *name;
	struct list *next;
};
typedef struct list list;
list *Table[size]={NULL};

// void Initialize(){
// 	for(int i=0;i<30;i++){
// 		Table[i]=NULL;
// 	}
// }

int Hash(char *str)
{
	int len=strlen(str);
	int h=0;
	for(int i=0;i<len;i++)
		h=(h*31+str[i])%size;
	
	return h;
}

int Search(char *str)
{
	int pos=Hash(str);
	list *temp=Table[pos];
	int count=0;
	while(temp)
	{
		count++;
		if(strcmp(temp->name,str)==0)
		{
			
			return 1;
		}
		temp=temp->next;
	}
	return 0;

}
void insert(char *str)
{
	if(Search(str)==1)
	{
		return;
	}
	list *nd = (list*)malloc(sizeof(list));
	nd->name=str;
	nd->next=NULL;
	int pos = Hash(str);
	printf("%d",pos);
		if(Table[pos]==NULL)
		{
			Table[pos]=nd;
			//return hash[0];
			return;
		}
		else
		{
			list *temp=Table[pos];
			while(temp->next)
			{
				temp=temp->next;
			}
			temp->next=nd;
			//return hash[0];
		}
	//}
}
void Display(){
for(int i=0;i<size;i++)
	{
		list *temp=Table[i];
		while(temp->next)
		{
			printf("%s->",temp->name);
			temp=temp->next;
		}
		printf("%s\n",temp->name);
	}
}




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

if(ch == '&' || ch == '|')
{
(*c)++;
ch = getc(fa);
if(ch=='&' || ch == '|'){
a[i] = ch;
i++;
(*c)++;
a[i] = '\0';
newToken->type = 3;
strcpy(newToken->ln, a);
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
strcpy(newToken->ln, a);
for(int i=0; i<8; i++)
if(strcmp(a, keys[i])==0){
newToken->type = 5;
return newToken;
}
ch = getc(fa);
if(ch=='('){
	newToken->type=15;
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
if(ch == '('){
(*c)++;

a[i] = '\0';
newToken->type = 11;
strcpy(newToken->ln,a);
return newToken;
}
if(ch == ')'){
(*c)++;

a[i] = '\0';
newToken->type = 12;
strcpy(newToken->ln,a);
return newToken;
}
if(ch == '{'){
(*c)++;
flag=1;
a[i] = '\0';
newToken->type = 13;
strcpy(newToken->ln,a);
return newToken;
}
if(ch == '}'){
(*c)++;
flag=0;
a[i] = '\0';
newToken->type = 14;
strcpy(newToken->ln,a);
return newToken;
}
a[i]='\0';
strcpy(newToken->ln, a);
newToken->type = 4;
return newToken;
}

int main(){
FILE *fa,*fb;
char types[][20]={"NO TOKEN", "ARITHMETIC OPERATOR", "RELATIONAL OPERATOR", "LOGICAL OPERATOR", "SPECIAL SYMBOL", "KEYWORD", "NUMBER", "STRING LITERAL", "IDENTIFIER", "SHORTHAND OPERATOR", "ASSIGNMENT OPERATOR","LB","RB","LC","RC","func"};
int l=1, c=0;


fa = fopen("prime.c", "r");

if (fa == NULL){
printf("Cannot open file \n");
exit(0);
}
tokenptr temp;
char *data="null";
printf("SYMBOL TABLE\n");
do{
temp = getNextToken(fa, &l, &c);
if(temp && temp->type==5)
data=temp->ln;
char *scope;
if(flag==1)
	scope="L";
else
	scope="G";


if((temp && temp->type==8)||(temp && temp->type==15)){
	if(!Search(temp->ln)){
	insert(temp->ln);
printf(" \t%s\t%s\t\t%s        \t%s \n",data, temp->ln, types[temp->type],scope);
data="null";
}
}
//Display();
}while(temp!=NULL);

fclose(fa);
printf("\n");

fa = fopen("example.c", "r");

if (fa == NULL){
printf("Cannot open file \n");
exit(0);
}

do{
temp = getNextToken(fa, &l, &c);
if(temp && temp->type!=0)
printf("<  %s , %d , %d , %s  >\n", temp->ln, temp->row, temp->col, types[temp->type]);
}while(temp!=NULL);
fclose(fa);
return 0;
}