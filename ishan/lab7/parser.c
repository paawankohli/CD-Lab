#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>




// global row and col tracker
int row = 1;
int col = 0;

// keywords
char keyword[][20] = {"auto", "break", "case", "char", "const", "continue",
                      "default", "do", "double", "else", "enum", "extern",
                      "float", "for", "goto", "if", "int", "long", "register",
                      "return", "short", "signed", "sizeof", "static", "struct",
                      "switch", "typedef", "union", "unsigned", "void",
                      "volatile", "while", "printf", "scanf", "bool"
                     };

// no of keywords = 32 c keywords + printf + scanf + bool
int nok = 32 + 3;

// datatypes
char datatype[][20] = {"int", "char", "bool", "void"};

// no. of datatypes
int nod = 4;

char dbuff[20];

// when int, char, bool or void is encountered,
// an identifier is expected. Hence, expectID is set to 1
int expectID = 0;







// ::::::::::For Lexical Analysis and Symbol Table::::::::::


// struct for a token
typedef struct {
	char token_name[50];
	unsigned int row, col;
	int index;
} token;


// return a token
token create_token(char n[], int r, int c, int i) {
	token m;

	strcpy(m.token_name, n);
	m.row = r;
	m.col = c;
	m.index = i;

	return m;
}


// print a token
void print_token(token t, FILE* out) {
	fprintf(out, "<%s,%d,%d,%d>", t.token_name, t.row, t.col, t.index);
}









// struct for a row of the symbol table
typedef struct {
	int index;
	char Lex_name[50];
	char type[20];
	int size;
} tableRow;

// struct for the symbol table containing multiple rows
typedef struct {
	int entries;
	tableRow tR[50];
} table;

// store name of the current table and current table
char currTableName[20];
table currTable;

// resets the entries in table to 2
void reset_table() {
	currTable.entries = 0;
}

// print the details of the table
void print_table(FILE* out) {
	if (currTable.entries == 0) {
		return;
	}

	fprintf(out, "%s\n", currTableName);
	fprintf(out, "\tLex_Name\tType\tSize\n");

	for (int i = 0; i < currTable.entries; i++)
		fprintf(out, "%d\t%s\t\t%s\t%d\n", currTable.tR[i].index,
		        currTable.tR[i].Lex_name, currTable.tR[i].type, currTable.tR[i].size);

	fprintf(out, "\n");
}

// insert a record into table. Lexyme Name, Type, Size
void insert(char n[], char t[], int s) {
	int idx = currTable.entries;

	currTable.tR[idx].index = idx + 1;
	strcpy(currTable.tR[idx].Lex_name, n);
	strcpy(currTable.tR[idx].type, t);
	currTable.tR[idx].size = s;

	currTable.entries++;
}

// search for the record in the symbol table
int search(char* name) {
	for (int i = 0; i < currTable.entries; i++)
		if (strcmp(name, currTable.tR[i].Lex_name) == 0)
			return i + 1;

	return 0;
}








// :::::::::::Helper Functions:::::::::::::::



token ArOp(int key, int row, int col) {
	return create_token("ArOp", row, col, key);
}

token RelOp(int key, int row, int col) {
	return create_token("RelOp", row, col, key);
}

token LogOp(int key, int row, int col) {
	switch (key) {
	case 1:
		return create_token("AND", row, col, -1);
	case 2:
		return create_token("ORR", row, col, -1);
	case 3:
		return create_token("NOT", row, col, -1);
	}
}

token AssOp(int key, int row, int col) {
	switch (key) {
	case 1:
		return create_token("ASS", row, col, -1);
	case 2:
		return create_token("ADA", row, col, -1);
	case 3:
		return create_token("SBA", row, col, -1);
	case 4:
		return create_token("MLA", row, col, -1);
	case 5:
		return create_token("DVA", row, col, -1);
	case 6:
		return create_token("MDA", row, col, -1);
	}
}

token SpecChar(char n, int row, int col, int i) {
	char temp[2];
	temp[0] = n;
	temp[1] = '\0';
	return create_token(temp, row, col, i);
}

token getNextToken(FILE* f, FILE* out, FILE* st) {
	int t_index = -1;
	
	char c = getc(f); col++;

	if (c == EOF) {
		print_table(st);
		return create_token("$", row, col, -1);
	}

	token T;
	
	if (c == '\n') {
		row++; col = 1;

		c = getc(f);
	}
	
	if (c == '/') {
		c = getc(f);
		
		if (c == '/') {
			
			do {
				c = getc(f);
			} while (c != '\n');

			row++; col = 0;
		} 

		else if (c == '*') {
			do {
				do {
					c = getc(f);
				} while (c != '*');
				
				c = getc(f);
			} while (c != '/');
			
			c = getc(f);
			col--;
		} 

		else {
			fseek(f, -2, SEEK_CUR);
			c = getc(f);
		}
	}


	if (c == '\"') {
		
		int length = 0;
		
		do {
			c = getc(f);
			length++;
		} while (c != '\"');
		
		T = create_token("string", row, col, -1);
		col += length;
	}

	else if (c == '#') {
		do {
			c = getc(f);
		} while (c != '\n');
		
		row++; col = 0;
		return getNextToken(f, out, st);
	}

	else if (c == '+') {
		c = getc(f);

		if (c == '+') {
			T = ArOp(6, row, col);
			col++;
		} else if (c == '=') {
			T = AssOp(2, row, col);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = ArOp(1, row, col);
		}
	}

	else if (c == '-') {
		c = getc(f);

		if (c == '-') {
			T = ArOp(7, row, col);
			col++;
		}else if (c == '=') {
			T = AssOp(3, row, col);
			col++;
		}else {
			fseek(f, -1, SEEK_CUR);
			T = ArOp(2, row, col);
		}
	}

	else if (c == '*') {
		c = getc(f);

		if (c == '=') {
			T = AssOp(4, row, col);
			col++;
		}else {
			fseek(f, -1, SEEK_CUR);
			T = ArOp(3, row, col);
		}
	}

	else if (c == '/') {
		c = getc(f);

		if (c == '=') {
			T = AssOp(5, row, col);
			col++;
		} else
		{
			fseek(f, -1, SEEK_CUR);
			T = ArOp(4, row, col);
		}
	}

	else if (c == '%') {
		c = getc(f);
		if (c == '=') {
			T = AssOp(6, row, col);
			col++;
		}else {
			fseek(f, -1, SEEK_CUR);
			T = ArOp(5, row, col);
		}
	}
	
	else if (c == '=') {
		c = getc(f);
		
		if (c == '=') {
			T = RelOp(1, row, col);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = AssOp(1, row, col);
		}
	}

	else if (c == '!') {
		c = getc(f);

		if (c == '='){
			T = RelOp(2, row, col);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = LogOp(3, row, col);
		}
	}

	else if (c == '>') {
		c = getc(f);

		if (c == '=') {
			T = RelOp(5, row, col);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = RelOp(3, row, col);
		}
	}

	else if (c == '<') {
		c = getc(f);

		if (c == '=') {
			T = RelOp(6, row, col);
			col++;
		}else{
			fseek(f, -1, SEEK_CUR);
			T = RelOp(4, row, col);
		}
	}

	else if (c == '&') {
		c = getc(f);

		if (c == '&') {
			T = LogOp(1, row, col);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = SpecChar('&', row, col, -1);
		}
	}

	else if (c == '|') {
		c = getc(f);

		if (c == '|') {
			T = LogOp(2, row, col);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = SpecChar('|', row, col, -1);
		}
	}

	else if (isalpha(c)) {
		int length = 0;
		int flag = 0;
		char buffer[20];

		do {
			buffer[length++] = c;
			c = getc(f);
		} while (isalpha(c));
		
		buffer[length] = '\0';
		
		for (int j = 0; j < nok; j++)
			if (strcmp(keyword[j], buffer) == 0) {
				
				for (int k = 0; k < nod; k++)
					if (strcmp(datatype[k], buffer) == 0) {
						strcpy(dbuff, buffer);
						expectID = 1;
					}

				T = create_token(buffer, row, col, t_index);
				flag++;
				break;
			}

		if (strcmp(buffer, "main") == 0) {
			print_table(st);
			reset_table();
			strcpy(currTableName, buffer);
			t_index = 0;
		}

		if (flag == 0) {
			fseek(f, -1, SEEK_CUR);
			char d = getc(f);

			if (expectID == 1 && d == '(') {
				print_table(st);
				reset_table();
				strcpy(currTableName, buffer);
				t_index = 0;
			}

			else if (expectID == 1) {
				int t_size;

				switch (dbuff[0])
				{
				case 'i':
					t_size = 4;
					break;
				case 'c':
					t_size = 1;
					break;
				case 'v':
					t_size = 4;
					break;
				case 'b':
					t_size = 1;
					break;
				}

				if (d == '[') {
					int elements = 0;
					int extracount = 1;
					d = getc(f);
					
					while (d != ']') {
						elements *= 10;
						elements += (d - 48);
						d = getc(f);
						extracount++;
					}

					fseek(f, -1 * extracount, SEEK_CUR);
					t_size *= elements;
				}

				insert(buffer, dbuff, t_size);
				t_index = currTable.entries;
			}

			else if (d == '(') {
				if (search(buffer) == 0) {
					insert(buffer, "func", -1);
					t_index = currTable.entries;
				} else {
					t_index = search(buffer);
				}
			}
			
			else {
				t_index = search(buffer);
			}

			length--;
			T = create_token("id", row, col, t_index);
		}
		fseek(f, -1, SEEK_CUR);
		col += length;
	}

	else if (isdigit(c) || c == '.') {
		
		int length = 0;
	
		do {
			length++;
			c = getc(f);
		} while (isdigit(c) || c == '.');
	
		T = create_token("num", row, col, -1);
		col += length - 1;
		fseek(f, -1, SEEK_CUR);
	}
	
	else {
		T = SpecChar(c, row, col, -1);
	}

	if (c == ';' || c == '(' || c == '=' || c == ')') {
		expectID = 0;
	}

	if (T.token_name[0] != '\n' && T.token_name[0] != ' ' && T.token_name[0] != '\t') {
		print_token(T, out);
		return T;
	}
	
	return getNextToken(f, out, st);
}






// :::::::Parser::::::::::

token cT;
FILE *f, *lex, *st;


void invalid(char* exp, int r, int c) {
	printf("expected '%s' at row %d col %d\n", exp, r, c);
	exit(0);
}

void valid() {
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}

void Program();
void declarations();
void data_type();
void identifier_list();
void ilprime();
void ilpprime();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

token getNext() {
	return getNextToken(f, lex, st);
}

void Program() {
	cT = getNext();

	if (strcmp(cT.token_name, "main") == 0) {

		cT = getNext();

		if (strcmp(cT.token_name, "(") == 0) {

			cT = getNext();

			if (strcmp(cT.token_name, ")") == 0) {

				cT = getNext();

				if (strcmp(cT.token_name, "{") == 0) {

					cT = getNext();
					declarations();
					statement_list();

					if (strcmp(cT.token_name, "}") == 0) {
						cT = getNext();
						return;
					}
					else {
						invalid("}", cT.row, cT.col);
					}
				}
				else {
					invalid("{", cT.row, cT.col);
				}
			}
			else {
				invalid(")", cT.row, cT.col);
			}
		}
		else {
			invalid("(", cT.row, cT.col);
		}
	}
	else {
		invalid("main", cT.row, cT.col);
	}
}

void declarations() {
	char firstofdata_type[20][20] = {"int", "char"};
	int nof = 2;
	int flag = 0;
	
	for (int i = 0; i < nof; i++) 
		if ((strcmp(cT.token_name, firstofdata_type[i])) == 0)
			flag++;
	
	if (flag) {
		data_type();
		identifier_list();

		if (strcmp(cT.token_name, ";") == 0) {
			cT = getNext();
			declarations();
		}
		else {
			invalid(";", cT.row, cT.col);
		}
	}
}

void data_type() {
	if (strcmp(cT.token_name, "int") == 0) {
		cT = getNext();
		return;
	} else if (strcmp(cT.token_name, "char") == 0) {
		cT = getNext();
		return;
	} else {
		invalid("int or char", cT.row, cT.col);
	}
}

void identifier_list() {
	if (strcmp(cT.token_name, "id") == 0) {
		cT = getNext();
		ilprime();
	}
	else {
		invalid("identifier", cT.row, cT.col);
	}
}

void ilprime() {
	if (strcmp(cT.token_name, ",") == 0) {
		cT = getNext();
		identifier_list();
	}
	else if (strcmp(cT.token_name, "[") == 0) {
		cT = getNext();
		
		if (strcmp(cT.token_name, "num") == 0) {
		
			cT = getNext();
		
			if (strcmp(cT.token_name, "]") == 0) {
				cT = getNext();
				ilpprime();
			}
			else {
				invalid("]", cT.row, cT.col);
			}
		}
		else {
			invalid("number", cT.row, cT.col);
		}
	}
}

void ilpprime() {
	if (strcmp(cT.token_name, ",") == 0) {
		cT = getNext();
		identifier_list();
	}
}

void statement_list() {
	char firstofstatement[20][20] = {"id"};
	int nof = 1;
	int flag = 0;

	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name, firstofstatement[i])) == 0)
			flag++;

	if (flag) {
		statement();
		statement_list();
	}
}

void statement() {
	assign_stat();

	if (strcmp(cT.token_name, ";") == 0) {
		cT = getNext();
		return;
	} else {
		invalid(";", cT.row, cT.col);
	}
}

void assign_stat() {
	if (strcmp(cT.token_name, "id") == 0) {
		cT = getNext();

		if (strcmp(cT.token_name, "ASS") == 0) {
			cT = getNext();
			expn();
		}
		else {
			invalid("=", cT.row, cT.col);
		}
	}
	else {
		invalid("identifier", cT.row, cT.col);
	}
}

void expn() {
	simple_expn();
	eprime();
}

void eprime() {
	char firstofrelop[20][20] = {"RelOp"};
	int nof = 1;
	int flag = 0;

	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name, firstofrelop[i])) == 0)
			flag++;
	
	if (flag) {
		relop();
		simple_expn();
	}
}

void simple_expn() {
	term();
	seprime();
}

void seprime() {
	char firstofaddop[20][20] = {"ArOp"};
	int nof = 1;
	int flag = 0;
	
	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name, firstofaddop[i])) == 0 && cT.index < 3)
			flag++;
	
	if (flag) {
		addop();
		term();
		seprime();
	}
}

void term() {
	factor();
	tprime();
}

void tprime() {
	char firstofmulop[20][20] = {"ArOp"};
	int nof = 1;
	int flag = 0;

	for (int i = 0; i < nof; i++)
		if ((strcmp(cT.token_name, firstofmulop[i])) == 0 && cT.index > 2)
			flag++;
	
	if (flag) {
		mulop();
		factor();
		tprime();
	}
}

void factor() {
	if (strcmp(cT.token_name, "id") == 0) {
		cT = getNext();
		return;
	} else if (strcmp(cT.token_name, "num") == 0) {
		cT = getNext();
		return;
	} else {
		invalid("identifier or number", cT.row, cT.col);
	}
}

void relop() {
	if (strcmp(cT.token_name, "RelOp") == 0) {
		cT = getNext();
		return;
	}
	else {
		invalid("relational operator", cT.row, cT.col);
	}
}

void addop() {
	if (strcmp(cT.token_name, "ArOp") == 0 && cT.index < 3) {
		cT = getNext();
		return;
	}
	else {
		invalid("addition or subtraction operator", cT.row, cT.col);
	}
}

void mulop() {
	if (strcmp(cT.token_name, "ArOp") == 0 && cT.index > 2) {
		cT = getNext();
		return;
	} else {
		invalid("multiplication, division or modulus operator", cT.row, cT.col);
	}
}

void main() {
	currTable.entries = 0;

	f = fopen("in.c", "r");
	lex = fopen("lex.txt", "w");
	st = fopen("st.txt", "w");

	Program();

	if (strcmp(cT.token_name, "$") == 0) {
		valid();
	} else {
		invalid("EOF", cT.row, cT.col);
	}

	fclose(f);
	fclose(lex);
	fclose(st);
}