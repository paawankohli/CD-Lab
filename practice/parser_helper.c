int row = 1;
int col = 0;

FILE* in;

typedef struct token {
	char name[200];
	char misc[200];
	int row, col;
} token;

token createToken(char name[], char misc[], int row, int col) {
	if (strcmp(name, "EOF") != 0)
		printf("%s - %s\n", name, misc);

	token t;

	strcpy(t.name, name);
	t.row = row;
	t.col = col;

	return t;
}

int isSplSymbol(char c) {
	char arr[] = {
		'[', ']', '{', '}', ';', ','
	};

	int n = 6;

	for (int i = 0 ; i < n ; i++)
		if (c == arr[i])
			return 1;

	return 0;
}

int isKeyword(char buff[]) {
	char arr[][20] = {
		"interface", "extends", "public", "private", "abstract",
		"static", "final", "int", "float", "boolean"
	};

	int n = 15;

	for (int i = 0 ; i < n ; i++)
		if (strcmp(arr[i], buff) == 0)
			return 1;

	return 0;
}

token getNext() {
	char c = fgetc(in); col++;

	if (c == EOF) {
		return createToken("EOF", "end of file", row, col);
	}

	if (isSplSymbol(c)) {
		char temp[2]; temp[0] = c; temp[1] = '\0';
		return createToken(temp, "Special Symbol", row, col);
	}

	if (c == '\n' || c == '\t' || c == ' ')
		return getNext();

	if (isalpha(c)) {
		char buff[100];
		int i = 0;

		int initCol = col;

		do {
			buff[i++] = c;
			c = fgetc(in); col++;
		} while (isalpha(c));

		buff[i] = '\0';

		fseek(in, -1, SEEK_CUR); col--;

		if (isKeyword(buff))
			return createToken(buff, "Keyword", row, initCol);

		c = getc(in); col++;

		while (isalpha(c) || isdigit(c) || c == '_') {
			buff[i++] = c;
			c = fgetc(in); col++;
		}

		buff[i] = '\0';

		fseek(in, -1, SEEK_CUR); col--;

		return createToken("id", buff, row, initCol);
	}

	if (isdigit(c)) {
		char buff[100];
		int i = 0;
		int initCol = col;

		do {
			buff[i++] = c;
			c = fgetc(in); col++;
		} while (isdigit(c));

		buff[i] = '\0';

		fseek(in, -1, SEEK_CUR); col--;

		return createToken("number", buff, row, initCol);
	}

	return getNext();
}
