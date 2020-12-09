// Design a lexical analyzer which contains getNextToken( ) for a simple C program to create a structure of token each time and return, which includes row number, column number and token type. The tokens to be identified are arithmetic operators, relational operators, logical operators, special symbols, keywords, numerical constants, string literals and identifiers. Also, getNextToken() should ignore all the tokens when encountered inside single line or multiline comment or inside string literal. Preprocessor directive should also be stripped.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct token {
	char name[30];
	int row, col;
};

char splChars[] = {':', ';', '(', ')', '{', '}', ',', '.', '?'};
char aritChars[] = {'+', '-', '*', '/'};

char keywords[][20] = {"auto", "break", "case", "char", "const", "continue",
                       "default", "do", "double", "else", "enum", "extern",
                       "float", "for", "goto", "if", "int", "long", "register",
                       "return", "short", "signed", "sizeof", "static", "struct",
                       "switch", "typedef", "union", "unsigned", "void",
                       "volatile", "while"
                      };

int row = 1, col = 0, ca, cb;

struct token getNextToken(FILE *in) {
	char buffer[50];

	while (ca != EOF) {

		// handle preprocessors
		if (ca == '#') {
			while (ca != '\n') {
				col++;
				ca = getc(in);
			}
		}

		// handle comments
		if (ca == '/') {
			col++;
			cb = getc(in);
			if (cb == '/') {
				while (ca != '\n') {
					col++;
					ca = getc(in);
				}
			} else if (cb == '*') {
				do {
					while (ca != '*') {
						col++;

						if (ca == '\n') {
							col = 1;
							row++;
						}

						ca = getc(in);
					}

					ca = getc(in);
				} while (ca != '/');
				ca = getc(in);

			}
		}

		// Literal
		if (ca == '"') {

			int i = 0;
			ca = getc(in);
			col++;

			while (ca != '"') {
				buffer[i++] = ca;
				ca = getc(in);
			}

			buffer[i] = '\0';
			struct token t;
			int j = 0;

			while (buffer[j] != '\0') {
				t.name[j] = buffer[j];
				j++;
			}

			t.name[j] = '\0';
			t.row = row;
			t.col = col;
			col = col + strlen(buffer);
			ca = getc(in);

			return t;
		}

		//blank space
		if (ca == ' ') {
			col++;
			ca = getc(in);
		}

		// handle new line char
		if (ca == '\n') {
			row++;
			col = 1;
			ca = getc(in);
			printf("\n");
		}

		// handle spl char
		for (int i = 0; i < 9; i++) {
			if (ca == splChars[i]) {
				struct token t;
				t.name[0] = ca;
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col++;
				return t;
			}
		}

		// handle arithmatic operators
		for (int i = 0; i < 4; i++) {
			if (ca == aritChars[i]) {
				struct token t;
				t.name[0] = ca;
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col++;
				return t;
			}
		}

		// handle assignment or equals operator
		if (ca == '=') {
			ca = getc(in);
			if (ca == '=') {
				struct token t;
				t.name[0] = '=';
				t.name[1] = '=';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col += 2;
				return t;
			} else {
				struct token t;
				t.name[0] = '=';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}

		// handle logical ops
		if (ca == '|') {
			ca = getc(in);
			if (ca == '|') {
				struct token t;
				t.name[0] = '|';
				t.name[1] = '|';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col += 2;
				return t;
			} else {
				struct token t;
				t.name[0] = '|';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		} else if (ca == '&') {
			ca = getc(in);
			if (ca == '&') {
				struct token t;
				t.name[0] = '&';
				t.name[1] = '&';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col += 2;
				return t;
			} else {
				struct token t;
				t.name[0] = '&';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		} else if (ca == '^') {
			struct token t;
			t.name[0] = '^';
			t.name[1] = '\0';
			t.row = row;
			t.col = col;
			col++;
			return t;
		}

		// handle relational operators
		if (ca == '<') {
			ca = getc(in);
			if (ca == '=') {
				struct token t;
				t.name[0] = '<';
				t.name[1] = '=';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col += 2;
				return t;
			} else {
				struct token t;
				t.name[0] = '<';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		} else if (ca == '>') {
			ca = getc(in);
			if (ca == '=')
			{
				struct token t;
				t.name[0] = '>';
				t.name[1] = '=';
				t.name[2] = '\0';
				t.row = row;
				t.col = col;
				ca = getc(in);
				col += 2;
				return t;
			}
			else {
				struct token t;
				t.name[0] = '>';
				t.name[1] = '\0';
				t.row = row;
				t.col = col;
				col++;
				return t;
			}
		}

		// handle numerics
		int i = 0;
		if (isdigit(ca)) {

			while (isdigit(ca)) {
				buffer[i++] = ca;
				ca = getc(in);
			}

			buffer[i] = '\0';
			struct token t;
			strcpy(t.name, buffer);
			t.row = row;
			t.col = col;
			col += strlen(buffer);
			return t;
		}

		// handle keywords
		i = 0;
		while (isalpha(ca)) {
			buffer[i++] = ca;
			ca = getc(in);
		}

		buffer[i] = '\0';

		for (int j = 0; j < 13; j++) {
			if (strcmp(buffer, keywords[j]) == 0) {
				struct token t;
				strcpy(t.name, buffer);
				t.row = row;
				t.col = col;
				col = col + strlen(buffer);
				return t;
			}
		}

		if (buffer[0] != '\0') {
			struct token t;
			strcpy(t.name, buffer);
			t.row = row;
			t.col = col;
			col += strlen(buffer);
			return t;
		}

		ca = getc(in);
		col++;
	}

	struct token t;
	t.row = -1;
}

void main() {
	FILE* in = fopen("in.c", "r");

	if (in == NULL) {
		printf("Cannot open file \n");
		exit(0);
	}

	ca = getc(in);
	col = 1;

	while (ca != EOF) {
		struct token t = getNextToken(in);

		if (t.row == -1) {
			break;
		}

		printf("<%s,%d,%d>", t.name, t.row, t.col );
	}

	printf("\n");
}