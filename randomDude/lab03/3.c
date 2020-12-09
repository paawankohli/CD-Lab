#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include<ctype.h>
#define SS_SIZE 6
#define KEY_SIZE 34
 
char special_symbols[SS_SIZE] = {
  ',',
  '(',
  ')',
  '{',
  '}'
};
char * keywords[KEY_SIZE] = {
  "auto\0",
  "break\0",
  "case\0",
  "char\0",
  "const\0",
  "continue\0",
  "default\0",
  "do\0",
  "double\0",
  "else\0",
  "enum\0",
  "extern\0",
  "float\0",
  "for\0",
  "goto\0",
  "if\0",
  "int\0",
  "long\0",
  "register\0",
  "return\0",
  "short\0",
  "signed\0",
  "sizeof\0",
  "static\0",
  "struct\0",
  "switch\0",
  "typedef\0",
  "union\0",
  "unsigned\0",
  "void\0",
  "volatile\0",
  "while\0",
  "true\0",
  "false\0"
};
 
typedef struct token {
  char lexemename[100];
  unsigned int row, col;
  char type[100];
}
TOKEN;
 
typedef struct table_entry {
  int idx;
  char name[100];
  char type[100];
  int size;
  char scope;
  int num_args;
  TOKEN arguments[100];
  char return_type[100];
  struct table_entry * next;
}
TABLE_ENTRY;
 
// typedef struct table {
//   int count;
// }
// TABLE;
struct Token1{
  char ln[100];
  int row, col, type;
};
typedef struct Token1* tokenptr;

tokenptr getNextToken1(FILE *fa, int *l, int *c){
  char a[100], ch, temp, i=0, keys[][20]= {"int", "char", "if", "else", "while", "void", "for", "return"};
  tokenptr newToken=(tokenptr)malloc(sizeof(struct Token1));
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
    strcpy(newToken->ln, a);
    for(int i=0; i<8; i++)
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
 
int get_size(char type[]) {
  if (strcmp(type, "int\0")) {
    return sizeof(int);
  }
  if (strcmp(type, "float\0")) {
    return sizeof(float);
  }
  if (strcmp(type, "char\0")) {
  return sizeof(char);
  }
  return 0;
}
 
int is_paranthesis(char c) {
  for (int i = 0; i < SS_SIZE; ++i) {
    if (c == special_symbols[i]) {
      return 1;
    }
  }
  return 0;
}
 
int is_digit(char c) {
  for (int i = '0'; i <= '9'; ++i) {
    if (c == i) {
      return 1;
    }
  }
  return 0;
}
 
int is_alpha(char c) {
  if (c == '_') {
    return 1;
  }
 
  for (int i = 'a'; i <= 'z'; ++i) {
    if (c == i) {
      return 1;
    }
  }
 
  for (int i = 'A'; i <= 'Z'; ++i) {
    if (c == i) {
      return 1;
    }
  }
 
  return 0;
}
 
int is_keyword(char buffer[]) {
  for (int i = 0; i < KEY_SIZE; ++i) {
    if (strcmp(buffer, keywords[i]) == 0) {
      return 1;
    }
  }
  return 0;
}
 
TOKEN getNextToken(int * ca, FILE * input, int * row, int * col) {
  int i = 0;
  int read = 1;
  char buffer[100];
  TOKEN cur_token;
 
  if ( * ca == '#') {
    while ( * ca != '\n') {
      * ca = getc(input);
      * row = * row + 1;
      if ( * ca == '\n') {
        * col = * col + 1;
        * row = 0;
      }
    }
    * ca = getc(input);
    * row = * row + 1;
    if ( * ca == '\n') {
      * col = * col + 1;
      * row = 0;
    }
  }
 
  if ( * ca == '"') {
    cur_token.row = * row;
    cur_token.col = * col;
    i = 0;
    buffer[i++] = * ca;
    * ca = getc(input);
    * row = * row + 1;
    if ( * ca == '\n') {
      * col = * col + 1;
      * row = 0;
    }
    while ( * ca != '"') {
      buffer[i++] = * ca;
      * ca = getc(input);
      * row = * row + 1;
      if ( * ca == '\n') {
        * col = * col + 1;
        * row = 0;
      }
    }
    buffer[i++] = '"';
    buffer[i++] = '\0';
    strcpy(cur_token.lexemename, buffer);
    strcpy(cur_token.type, "Literal\0");
  } else if (is_paranthesis( * ca)) {
    cur_token.row = * row;
    cur_token.col = * col;
    cur_token.lexemename[0] = * ca;
    cur_token.lexemename[1] = '\0';
    cur_token.type[0] = * ca;
    cur_token.type[1] = '\0';
  } else if ( * ca == '/') {
    int cb = getc(input);
    * row = * row + 1;
    if (cb == '\n') {
      * col = * col + 1;
      * row = 0;
    }
    if (cb == '/') {
      while (cb != '\n') {
        cb = getc(input);
        * row = * row + 1;
        if (cb == '\n') {
          * col = * col + 1;
          * row = 0;
        }
      }
      * ca = getc(input);
      * row = * row + 1;
      if ( * ca == '\n') {
        * col = * col + 1;
        * row = 0;
      }
    } else if (cb == '*') {
      do {
        while (cb != '*') {
          cb = getc(input);
          * row = * row + 1;
          if (cb == '\n') {
            * col = * col + 1;
            * row = 0;
          }
        }
        cb = getc(input);
        * row = * row + 1;
        if (cb == '\n') {
          * col = * col + 1;
          * row = 0;
        }
      } while (cb != '/');
      * ca = getc(input);
      * row = * row + 1;
      if ( * ca == '\n') {
        * col = * col + 1;
        * row = 0;
      }
    }
    return getNextToken(ca, input, row, col);
  } else if (is_alpha( * ca)) {
    cur_token.row = * row;
    cur_token.col = * col;
    i = 0;
    buffer[i++] = * ca;
    * ca = getc(input);
    * row = * row + 1;
    if ( * ca == '\n') {
      * col = * col + 1;
      * row = 0;
    }
    while (is_alpha( * ca) || is_digit( * ca)) {
      buffer[i++] = * ca;
      * ca = getc(input);
      * row = * row + 1;
      if ( * ca == '\n') {
        * col = * col + 1;
        * row = 0;
      }
    }
    buffer[i++] = '\0';
    if (is_keyword(buffer)) {
      strcpy(cur_token.lexemename, buffer);
      strcpy(cur_token.type, "Keyword\0");
    } else {
      strcpy(cur_token.lexemename, buffer);
      strcpy(cur_token.type, "Identifier\0");
    }
    read = 0;
  } else {
    * ca = getc(input);
    * row = * row + 1;
    if ( * ca == '\n') {
      * col = * col + 1;
      * row = 0;
    }
    return getNextToken(ca, input, row, col);
  }
  if (read) {
    * ca = getc(input);
    * row = * row + 1;
    if ( * ca == '\n') {
      * col = * col + 1;
      * row = 0;
    }
  }
  return cur_token;
}
 
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
 
int hash_func(char * s) {
unsigned h = FIRSTH;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h % 30;
}
 
int search(TABLE_ENTRY ** table_entry, char * str) {
  int hash = hash_func(str);
  TABLE_ENTRY * cur = table_entry[hash];
  while (cur != NULL) {
    if (strcmp(cur->name, str) == 0) {
      return hash;
    }
    cur = cur->next;
  }
  return -1;
}
 
 
char * display_token(TABLE_ENTRY ** table, TOKEN token[], int count) {
  char * str = (char * ) calloc(100, sizeof(char));
  int idx = 0;
  for (int i = 0; i < count; ++i) {
    str[idx++] = '<';
    strcpy( & str[idx], "id, ");
    idx += 4;
    int j = search(table, token[i].lexemename);
    str[idx++] = j + '0';
    // printf("%s %d\n", token[i].lexemename, j);
    strcpy( & str[idx++], ">");
  }
  return str;
}
 
void display(TABLE_ENTRY ** table, int count) {
  printf("----------SYMBOL TABLE-----------------------\n");
  printf("Index \t Name \t Type \t Size \t Scope \t Num arg \t Arguments \t Return Type\n");
  for (int i = 0; i < 100; ++i) {
    TABLE_ENTRY * cur = table[i];
    cur = cur->next;
    while (cur != NULL) {
      TABLE_ENTRY * entry = cur;
      if (strcmp(entry->type, "FUNC\0") == 0) {
        printf("%d \t %s \t %s \t null \t null \t %d \t\t %s \t %s\n",
          entry->idx, entry->name, entry->type, entry->num_args, display_token(table, entry->arguments, entry->num_args), entry->return_type);
      } else {
        printf("%d \t %s \t %s \t %d \t %c \t null \t\t null \t null\n",
          entry->idx, entry->name, entry->type, entry->size, entry->scope, entry->num_args, display_token(table, entry->arguments, entry->num_args), entry->return_type);
      }
      cur = cur->next;
    }
  }
}
 
void insert(TABLE_ENTRY ** table, TABLE_ENTRY table_entry, int count) {
  if (search(table, table_entry.name) > -1) {
    return;
  }
  int i = hash_func(table_entry.name);
  table_entry.idx = i;
  TABLE_ENTRY * cur = table[i];
  while (cur->next != NULL) {
    cur = cur->next;
  }
  TABLE_ENTRY * entry = (TABLE_ENTRY*)malloc(sizeof(TABLE_ENTRY));
  *entry = table_entry;
  cur->next = entry;
  cur->next->next = NULL;
}
 
int main(int argc, char * argv[]) {
  FILE *input = fopen("prime.c","r");
  if (input == NULL) {
    printf("Cannot open file\n");
    exit(-1);
  }
  int ca = getc(input);
  int row = 0, col = 0;
  TOKEN prev_token;
  TABLE_ENTRY ** table = (TABLE_ENTRY**) calloc(100, sizeof(TABLE_ENTRY*));
  for (int i = 0; i < 100; ++i) {
    table[i] = (TABLE_ENTRY *) malloc(sizeof(TABLE_ENTRY));
    table[i]->next;
  }
  int count = 0;
  int global_scope = 0;
  while (ca != EOF) {
    TOKEN cur_token = getNextToken( & ca, input, & row, & col);
    if (strcmp(cur_token.type, "{\0") == 0) {
      global_scope++;
    } else if (strcmp(cur_token.type, "}\0") == 0) {
      global_scope--;
    }
    if (strcmp(cur_token.type, "Identifier\0") == 0) {
      TOKEN next_token = getNextToken( & ca, input, & row, & col);
      TABLE_ENTRY table_entry;
      strcpy(table_entry.name, cur_token.lexemename);
      if (strcmp(next_token.type, "(\0") == 0) {
        strcpy(table_entry.type, "FUNC\0");
        int num_args = 0;
        cur_token = getNextToken( & ca, input, & row, & col);
        while (strcmp(cur_token.type, ")\0") != 0) {
          if (strcmp(cur_token.type, "Identifier\0") == 0) {
            TABLE_ENTRY table_entry2;
            strcpy(table_entry2.name, cur_token.lexemename);
            strcpy(table_entry2.type, prev_token.lexemename);
            table_entry2.size = get_size(table_entry2.type);
            insert(table, table_entry2, count++);
 
            table_entry.arguments[num_args] = cur_token;
            num_args++;
          }
          if (strcmp(cur_token.type, "Keyword") == 0) {
          prev_token = cur_token;
          }
          cur_token = getNextToken( & ca, input, & row, & col);
        }
        table_entry.num_args = num_args;
        strcpy(table_entry.return_type, prev_token.lexemename);
        table_entry.scope = 'G';
      } else {
        strcpy(table_entry.type, prev_token.lexemename);
        table_entry.size = get_size(table_entry.type);
        if (global_scope == 0) {
          table_entry.scope = 'G';
        } else {
          table_entry.scope = 'L';
        }
      }
      insert(table, table_entry, count);
      count++;
    }
    if (strcmp(cur_token.type, "Keyword") == 0) {
      prev_token = cur_token;
    }
  }
  //display(table, count);
  char types[][20]={"No_Token", "Arithmetic_Operator", "Relational_Operator", "Logical_Operator", "Special_Symbol", "Keyword", "Number_Constant", "String_Literal", "Identifier", "Shorthand_Operator", "Assignment_Operator"};
  int l=1, c=0;
  FILE* fa=fopen("prime.c","r");
  printf("\nTokens:\n\n");
  tokenptr temp;
  do{
    temp = getNextToken1(fa, &l, &c);
    if(temp && temp->type!=0)
    {
      if(search(table,temp->ln)==-1)
      printf("<  '%s' , %d , %d , %s  >\n", temp->ln, temp->row, temp->col, types[temp->type]);
    else
       printf("<  'id,%d' , %d , %d , %s  >\n", search(table,temp->ln), temp->row, temp->col, types[temp->type]);    
  
      
    }
  }while(temp!=NULL);
  display(table, count);
}
 
