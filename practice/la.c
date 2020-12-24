#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* f;
int row;
int col;

int isKeyword(char buff[]) {
	char lol[][20] = {
		"for", "while", "do", "case", "break",
		"printf", "scanf", "return", "if", "else",
		"int", "char", "bool", "main"
	};

	int n = 14;

	for (int i = 0 ; i < n ; i++)
		if (strcmp(buff, lol[i]) == 0)
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

struct token {
	char tokenName[50];
	int row;
	int col;
	int index;
};

void printToken(struct token t) {
	// printf("<%s> ", t.tokenName);
	printf("<%s, %d, %d> ", t.tokenName, t.row, t.col);
}

struct token createToken(char n[], int row, int col) {
	struct token t;

	strcpy(t.tokenName, n);
	t.row = row;
	t.col = col;

	return t;
}

struct token getNextToken() {
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
	}

	if (c == '|') {
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

			return createToken(buff, row, initCol);
		}

		while (isdigit(c) || c == '_' || isalpha(c)) {
			buff[i++] = c;
			c = fgetc(f); col++;
		}

		buff[i] = '\0';

		fseek(f, -1, SEEK_CUR);
		col--;

		return createToken("id", row, initCol);
	}

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
	row = 1;
	col = 0;

	f = fopen("input.c", "r");


	while (1) {
		struct token t = getNextToken();

		if (strcmp(t.tokenName, "EOF") == 0)
			break;
		else
			printToken(t);
	}

	printf("\n\n");
}