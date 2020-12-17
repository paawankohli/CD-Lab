#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct token {
	char name[30];
	int row;
	int col;
} token;

token createToken(char name[], int row, int col) {
	token t;
	strcpy(t.name, name);
	t.row = row;
	t.col = col;
	return t;
}

int row = 1;
int col = 0;

int isKeyword(char buffer[]) {
	char keywords[][20] = {
		"main", "printf", "scanf", "int", "char",
		"bool", "void", "return", "if", "else",
		"for", "while", "do"
	};

	int nok = 13;

	for (int i = 0 ; i < nok ; i++)
		if (strcmp(buffer, keywords[i]) == 0)
			return 1;

	return 0;
}

int isDataType(char buffer[]) {
	char dt[][20] = { "int", "char", "bool", "void"};
	int nodt = 4;

	for (int i = 0 ; i < nodt ; i++)
		if (strcmp(buffer, dt[i]) == 0)
			return 1;

	return 0;
}

int isSplChar(char c) {
	char arr[] = {'{', '[', '(', ')', ']', '}', ';', ',', ':'};

	for (int i = 0 ; i < sizeof(arr) ; i++)
		if (arr[i] == c)
			return 1;

	return 0;
}

token getNextToken(FILE* fd) {
	char c = getc(fd); col++;

	if (c == EOF) {
		return createToken("$", -1, -1);
	}

	// handle newline
	if (c == '\n') {
		row++; col = 0;
		printf("\n");
		return getNextToken(fd);
	}

	// handle comments
	if (c == '/') {
		char cnext = getc(fd); col++;

		if (cnext == '/') {
			do {
				c = getc(fd); col++;
			} while (c != '\n');

			row++; col = 0;

		} else if (cnext == '*') {

			do {
				do {
					c = getc(fd); col++;

					if (c == '\n') {
						row++; col = 0;
					}

				} while (c != '*');
				c = getc(fd); col++;
			} while (c != '/');

			return getNextToken(fd);

		} else {
			fseek(fd, -2, SEEK_CUR);
			col -= 2;
		}
	}

	// handle #define and #include
	if (c == '#') {
		do {
			c = getc(fd); col++;
		} while (c != '\n');
		row++; col = 0;
	}

	// handle strings
	if (c == '\"') {
		int initCol = col;
		do {
			c = getc(fd); col++;
		} while (c != '\"');

		return createToken("string", row, initCol);
	}

	if (isSplChar(c)) {
		char temp[2]; temp[0] = c; temp[1] = '\0';
		return createToken(temp, row, col);
	}


	// ++ += +
	if (c == '+') {
		char cnext = getc(fd); col++;

		if (cnext == '+') {
			return createToken("++", row, col - 1);
		} else if (cnext == '=') {
			return createToken("+=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("+", row, col);
		}
	}

	// -- -= -
	if (c == '-') {
		char cnext = getc(fd); col++;

		if (cnext == '-') {
			return createToken("--", row, col - 1);
		} else if (cnext == '=') {
			return createToken("-=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("-", row, col);
		}
	}

	// *= *
	if (c == '*') {
		char cnext = getc(fd); col++;

		if (cnext == '=') {
			return createToken("*=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("*", row, col);
		}
	}

	// /= =
	if (c == '/') {
		char cnext = getc(fd); col++;

		if (cnext == '=') {
			return createToken("/=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("/", row, col);
		}
	}

	// != !
	if (c == '!') {
		char cnext = getc(fd); col++;

		if (cnext == '=') {
			return createToken("/=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("!", row, col);
		}
	}

	// == =
	if (c == '=') {
		char cnext = getc(fd); col++;

		if (cnext == '=') {
			return createToken("==", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("=", row, col);
		}
	}

	// <= <
	if (c == '<') {
		char cnext = getc(fd); col++;

		if (cnext == '=') {
			return createToken("<=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("<", row, col);
		}
	}

	// >= >
	if (c == '>') {
		char cnext = getc(fd); col++;

		if (cnext == '=') {
			return createToken(">=", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken(">", row, col);
		}
	}

	if (c == '&') {
		char cnext = getc(fd); col++;

		if (cnext == '&') {
			return createToken("&&", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("&", row, col);
		}
	}


	if (c == '|') {
		char cnext = getc(fd); col++;

		if (cnext == '|') {
			return createToken("||", row, col - 1);
		} else {
			fseek(fd, -1, SEEK_CUR); col--;
			return createToken("|", row, col);
		}
	}

	if (isalpha(c)) {
		int initCol = col;

		int i = 0;
		char buffer[20];

		do {
			buffer[i++] = c;
			c = getc(fd); col++;
		} while (isalpha(c));

		fseek(fd, -1, SEEK_CUR); col--;
		buffer[i] = '\0';

		if (isKeyword(buffer))
			return createToken(buffer, row, initCol);


		// if not keyword then id
		c = getc(fd); col++;

		while (isalpha(c) || isdigit(c) || c == '_') {
			buffer[i++] = c;
			c = getc(fd); col++;
		}

		fseek(fd, -1, SEEK_CUR); col--;
		buffer[i] = '\0';

		return createToken("id", row, initCol);
	}

	if (isdigit(c)) {
		int initCol = col;

		int i = 0;
		char buffer[20];

		do {
			buffer[i++] = c;
			c = getc(fd); col++;
		} while (isdigit(c) || c == '.');

		fseek(fd, -1, SEEK_CUR); col--;
		buffer[i] = '\0';

		return createToken(buffer, row, initCol);
	}

	return getNextToken(fd);
}



void main() {
	char name[20];
	printf("Enter name of file: ");
	scanf("%s", name);

	FILE* fd = fopen(name, "r");

	if (fd == NULL) {
		printf("File opening error\n");
		exit(0);
	}


	while (1) {
		token t = getNextToken(fd);

		if (strcmp(t.name, "$") == 0) {
			break;
		}

		printf("<%s,%d,%d>", t.name, t.row, t.col);
	}

	printf("\n\nDone\n\n");
}