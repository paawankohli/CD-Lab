#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


FILE* f;
FILE* st;

int expectID = 0;

int row = 1;
int col = 0;;

int isKeyword(char buff[]) {
	char lol[][20] = {
		"for", "while", "do", "case", "break",
		"printf", "scanf", "return", "if", "else",
		"int", "char", "bool"
	};

	int n = 13;

	for (int i = 0 ; i < n ; i++)
		if (strcmp(buff, lol[i]) == 0)
			return 1;

	return 0;
}

int isDataType(char buff[]) {
	if (strcmp(buff, "int") == 0)
		return 4;

	if (strcmp(buff, "char") == 0)
		return 1;

	return 0;
}

int isSpecialSymbol(char c) {
	char lol[] = {
		'(', ')', '{', '}', ']', '[', ';', ':', ','
	};

	int n = 9;

	for (int i = 0 ; i < n ; i++)
		if (c == lol[i])
			return 1;

	return 0;
}

typedef struct token {
	char tokenName[50];
	int row;
	int col;
} token;







typedef struct tableRow {
	int index;
	char lexName[20];
	char dataType[20];
	int dataTypeSize;
} tableRow;

typedef struct table {
	char tableName[20];
	int size;
	tableRow entry[100];
} table;

table currTable;

void printTable() {

	if (currTable.size == 0)
		return;

	fprintf(st, "Table Name: %s\n", currTable.tableName);
	fprintf(st, "Index\tLex name\tdata type\tsize\n");

	for (int i = 0 ; i < currTable.size ; i++)
		fprintf(st, "%d\t\t%s\t\t%s\t\t%d\n", currTable.entry[i].index, currTable.entry[i].lexName,
		        currTable.entry[i].dataType, currTable.entry[i].dataTypeSize);
}

void newTable(char newTableName[]) {
	currTable.size = 0;
	strcpy(currTable.tableName, newTableName);
}

void insert(char lexName[], char dataType[], int s) {
	int n = currTable.size;

	currTable.entry[n].index = n + 1;
	strcpy(currTable.entry[n].lexName, lexName);
	strcpy(currTable.entry[n].dataType, dataType);

	currTable.entry[n].dataTypeSize = s;

	currTable.size++;
}

int search(char id[]) {
	for (int i = 0 ; i < currTable.size ; i++)
		if (strcmp(id, currTable.entry[i].lexName) == 0)
			return currTable.entry[i].index;

	return 0;
}

void printToken(struct token t) {
	printf("<%s, %d, %d> ", t.tokenName, t.row, t.col);
}

token createToken(char n[], int row, int col) {
	token t;

	strcpy(t.tokenName, n);
	t.row = row;
	t.col = col;

	return t;
}

token getNextToken() {
	char c = fgetc(f); col++;

	if (c == EOF) {
		return createToken("EOF", row, col);
	}

	if (c == '\n') {
		printf("\n");
		row++; col = 0;
		return getNextToken();
	}


	if (c == '\t' || c == ' ')
		return getNextToken();


	// #define and #include
	if (c == '#') {
		do {
			c = fgetc(f);
		} while (c != '\n');

		row++; col = 0;

		return getNextToken();
	}

	// comments
	if (c == '/') {
		c = fgetc(f); col++;

		if (c == '/') {

			do {
				c = fgetc(f);
			} while (c != '\n');

			printf("\n");
			row++; col = 0;

			return getNextToken();

		} else if (c == '*') {

			do {
				do {
					c = fgetc(f); col++;

					if (c == '\n') {
						row++; col = 0;
					}

				} while (c != '*');

				c = fgetc(f); col++;

				if (c == '\n') {
					row++; col = 0;
				}

			} while (c != '/');

			return getNextToken();

		} else {
			col--; col--;
			fseek(f, -2, SEEK_CUR);

			c = fgetc(f); col++;
		}
	}


	// literal
	if (c == '\"') {
		int initCol = col;

		do {
			c = fgetc(f); col++;
		} while (c != '\"');

		return createToken("literal", row, initCol);
	}




	// ++   --   +   -  *   /   %   +=   -=   *=   /=   %=
	if (c == '+') {
		c = fgetc(f); col++;

		if (c == '+') {
			return createToken("++", row, col - 1);
		} else if (c == '=') {
			return createToken("+=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("+", row, col);
		}
	}

	if (c == '-') {
		c = fgetc(f); col++;

		if (c == '-') {
			return createToken("--", row, col - 1);
		} else if (c == '=') {
			return createToken("-=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("-", row, col);
		}
	}

	if (c == '/') {
		c = fgetc(f); col++;

		if (c == '=') {
			return createToken("/=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("/", row, col);
		}
	}

	if (c == '*') {
		c = fgetc(f); col++;

		if (c == '=') {
			return createToken("*=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("*", row, col);
		}
	}

	if (c == '%') {
		c = fgetc(f); col++;

		if (c == '=') {
			return createToken("%=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("%", row, col);
		}
	}





	// &   &&   |   ||
	if (c == '&') {
		c = fgetc(f); col++;
		if (c == '&') {
			return createToken("&&", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("&", row, col);
		}
	} else if (c == '|') {
		c = fgetc(f); col++;
		if (c == '|') {
			return createToken("||", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("|", row, col);
		}
	}

	// ==   =
	if (c == '=') {
		c = fgetc(f); col++;
		if (c == '=') {
			return createToken("==", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("=", row, col);
		}
	}


	// <=   <
	if (c == '<') {
		c = fgetc(f); col++;

		if (c = '=') {
			return createToken("<=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken("<", row, col);
		}
	}

	// >=   >
	if (c == '>') {
		c = fgetc(f); col++;

		if (c = '=') {
			return createToken(">=", row, col - 1);
		} else {
			col--;
			fseek(f, -1, SEEK_CUR);

			return createToken(">", row, col);
		}
	}

	// !=
	if (c == '!') {
		c = fgetc(f); col++;

		if (c = '=') {
			return createToken("!=", row, col - 1);
		} else {
			col--; col--;
			fseek(f, -2, SEEK_CUR);

			c = fgetc(f); col++;
		}
	}

	if (isSpecialSymbol(c)) {
		char temp[2]; temp[0] = c; temp[1] = '\0';
		return createToken(temp, row, col);
	}




	// keywords and identifiers
	if (isalpha(c)) {

		int initCol = col;

		char buff[50];
		int i = 0;

		do {
			buff[i++] = c;
			c = fgetc(f); col++;
		} while (isalpha(c));

		buff[i] = '\0';

		if (isKeyword(buff)) {
			fseek(f, -1, SEEK_CUR);
			col--;

			expectID = isDataType(buff);

			return createToken(buff, row, initCol);
		}






		// id hai
		while (isdigit(c) || c == '_' || isalpha(c)) {
			buff[i++] = c;
			c = fgetc(f); col++;
		}

		buff[i] = '\0';

		// buff mein id hai
		fseek(f, -1, SEEK_CUR);
		col--;


		// new id mila
		if (expectID != 0) {
			char cnext = fgetc(f);

			if (cnext == '[') {
				int digits = 0;
				int arrSize = 0;

				cnext = fgetc(f);

				while (isdigit(cnext)) {
					arrSize = arrSize * 10 + (cnext - 48);
					digits++;
					cnext = fgetc(f);
				}

				fseek(f, -(digits + 1), SEEK_CUR);


				if (expectID == 4)
					insert(buff, "int", 4 * arrSize);
				else if (expectID == 1)
					insert(buff, "char", arrSize);
			}
			else if (c == '(') {
				expectID = 0;
				printTable();
				newTable(buff);
			} else {

				if (expectID == 4)
					insert(buff, "int", 4);
				else if (expectID == 1)
					insert(buff, "char", 1);	
			
			}

			fseek(f, -1, SEEK_CUR);
		}

		return createToken("id", row, initCol);
	}

	if (c == ';' || c == '=' || c == ')' || c == '(')
		expectID = 0;

	if (isdigit(c)) {
		int initCol = col;
		char buff[20];
		int i = 0;

		do {
			buff[i++] = c;
			c = fgetc(f); col++;
		} while (isdigit(c));

		buff[i] = '\0';

		fseek(f, -1, SEEK_CUR);
		col--;

		return createToken(buff, row, initCol);
	}

	return getNextToken();
}

void main() {
	currTable.size = 0;

	f = fopen("input.c", "r");
	st = fopen("st.txt", "w");

	while (1) {
		struct token t = getNextToken();

		if (strcmp(t.tokenName, "EOF") == 0)
			break;
		else
			printToken(t);
	}

	printTable();

	printf("\n\n");
}