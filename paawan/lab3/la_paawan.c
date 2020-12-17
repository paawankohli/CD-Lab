// Design a lexical analyzer which contains getNextToken() for a simple C program 
// to create a structure of token each time and return, which includes row number, 
// column number and token type. The tokens to be identified are arithmetic operators, 
// relational operators, logical operators, special symbols, keywords, numerical constants, 
// string literals and identifiers. 

// Also, getNextToken() should ignore all the tokens when encountered inside single line 
// or multiline comment or inside string literal. Preprocessor directive should also be stripped.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// structure of token
struct token {
	char name[30];
	int row, col;
};

// prints a token
void printToken(char *tokenName, int row, int col) {
	printf("<%s,%d,%d>", tokenName, row, col);
}

// check is char is a spl character
int isSplChar(char c) {
	char splChars[] = {':', ';', '(', ')', '{', '}', ',', '.', '?', '[' , ']'};

	for (int i = 0 ; i < sizeof(splChars) ; i++)
		if (c == splChars[i])
			return 1;

	return 0;
}

// check is string is a keyword
int isKeyword(char *buffer) {
	char keywords[][20] = {"auto", "break", "case", "char", "const", "continue",
	                       "default", "do", "double", "else", "enum", "extern",
	                       "float", "for", "goto", "if", "int", "long", "register",
	                       "return", "short", "signed", "sizeof", "static", "struct",
	                       "switch", "typedef", "union", "unsigned", "void",
	                       "volatile", "while", "printf", "scanf", "bool"
	                      };

	// no of keywords = 32 c keywords + printf + scanf + bool
	int nok = 32 + 2 + 1;

	for (int i = 0 ; i < nok ; i++)
		if (strcmp(buffer, keywords[i]) == 0)
			return 1;

	return 0;
}


// global FILE*
FILE* in;

// global row and col tracker
int row = 1;
int col = 0;

// return 1 unless EOF. prints lexymes
int getNextToken() {
	char c = getc(in); col++;

	// base condition
	if (c == EOF) {
		printf("\n");
		return 0;
	}

	// handle newline
	if (c == '\n') {
		row++; col = 0;
		printf("\n");
	}

	// ignore spaces and tabs
	if (c == ' ' || c == '\t') {
		do {
			c = getc(in); col++;
		} while (c == ' ' || c == '\t');

		fseek(in, -1, SEEK_CUR); col--;
	}

	// handle comments
	if (c == '/') {
		c = getc(in); col++;

		if (c == '/') {

			// keep scanning and ignore till newline
			do {
				c = getc(in);
			} while (c != '\n');

			// update row and col accordingly
			row++; col = 0;

		} else if (c == '*') {

			do {

				do {
					c = getc(in); col++;

					if (c == '\n') {
						row++; col = 0;
					}

				} while (c != '*');

				c = getc(in); col++;

				if (c == '\n') {
					row++; col = 0;
				}

			} while (c != '/');
		}
	}

	// handle string literals
	if (c == '\"') {

		int stringIndex = col;

		do {
			c = getc(in); col++;
		} while (c != '\"');

		printToken("string", row, stringIndex);
		return 1;
	}

	// handle pre processor directives
	if (c == '#') {
		do {
			c = getc(in); col++;
		} while (c != '\n');

		row++; col = 0;
	}

	// handle ++, += and +
	if (c == '+') {
		char c = getc(in); col++;

		if (c == '+') {
			printToken("++", row, col - 1);
			return 1;
		}
		else if (c == '=') {
			printToken("+=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("+", row, col - 1);
			return 1;
		}
	}

	// handle --, -+ and -
	if (c == '-') {
		char c = getc(in); col++;

		if (c == '-') {
			printToken("--", row, col - 1);
			return 1;
		}
		else if (c == '=') {
			printToken("-=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("-", row, col - 1);
			return 1;
		}
	}

	// handle *= and *
	if (c == '*') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken("*=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("*", row, col - 1);
			return 1;
		}
	}

	// handle /= and /
	if (c == '/') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken("/=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("/", row, col - 1);
			return 1;
		}
	}

	// handle %= and %
	if (c == '%') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken("%=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("%", row, col - 1);
			return 1;
		}
	}

	// handle == and =
	if (c == '=') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken("==", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("=", row, col - 1);
			return 1;
		}
	}

	// handle != and !
	if (c == '!') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken("!=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("!", row, col - 1);
			return 1;
		}
	}

	// handle >= and >
	if (c == '>') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken(">=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken(">", row, col - 1);
			return 1;
		}
	}

	// handle <= and <
	if (c == '<') {
		char c = getc(in); col++;

		if (c == '=') {
			printToken("<=", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("<", row, col - 1);
			return 1;
		}
	}

	// handle && and &
	if (c == '&') {
		char c = getc(in); col++;

		if (c == '&') {
			printToken("&&", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("&", row, col - 1);
			return 1;
		}
	}

	// handle || and |
	if (c == '|') {
		char c = getc(in); col++;

		if (c == '|') {
			printToken("||", row, col - 1);
			return 1;
		} else {
			fseek(in, -1, SEEK_CUR); col--;

			printToken("|", row, col - 1);
			return 1;
		}
	}

	// handle ^
	if (c == '^') {
		printToken("^", row, col);
		return 1;
	}

	//handle special symbols
	if (isSplChar(c) == 1) {
		char temp[2]; temp[0] = c; temp[1] = '\0';

		printToken(temp, row, col);
		return 1;
	}

	// handle keywords and identifiers
	if (isalpha(c)) {
		int initialCol = col;

		char buffer[20];
		int bufferIndex = 0;

		do {
			buffer[bufferIndex++] = c;
			c = getc(in); col++;
		} while (isalpha(c));

		buffer[bufferIndex] = '\0';
		fseek(in, -1, SEEK_CUR); col--;

		if (isKeyword(buffer)) {
			printToken(buffer, row, initialCol);
			return 1;
		}

		// if not a keyword, it would be an identifier. It can include _ and digits
		c = getc(in);
		while (isalpha(c) || isdigit(c) || c == '_') {
			buffer[bufferIndex++] = c;
			c = getc(in); col++;
		}

		fseek(in, -1, SEEK_CUR); col--;

		printToken("id", row, initialCol);
		return 1;
	}

	// handle numerics
	if (isdigit(c)) {
		int initialCol = col;

		char buffer[20];
		int bufferIndex = 0;

		do {
			buffer[bufferIndex++] = c;
			c = getc(in); col++;
		} while (isdigit(c));

		buffer[bufferIndex] = '\0';

		fseek(in, -1, SEEK_CUR); col--;

		printToken(buffer, row, initialCol);
		return 1;
	}

	return 1;
}


void main() {

	char file[50];
	printf("Enter name of input .c file: ");
	scanf("%s", file);

	if ((in = fopen(file, "r")) == NULL) {
		printf("Couldn't open the file\n");
		exit(1);
	}

	while (getNextToken());

	fclose(in);
}