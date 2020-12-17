#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int row = 1;
int col = 0;

char keyword[][20] = { "scalar", "foreach" };
int nok = 2;

char currTableName[20];

typedef struct {
	char token_name[20];
	unsigned int row, col;
	int index;
} token;

typedef struct {
	int index;
	char Lex_name[20];
	char type[20];
	int size;
} tableRow;

typedef struct {
	int entries;
	tableRow tR[20];
} table;

table currTable;

void print_table(FILE* out) {
	if (currTable.entries == 0)
		return;

	fprintf(out, "%s\n\tLex_Name\tType\tSize\n", currTableName);

	for (int i = 0; i < currTable.entries; i++)
		fprintf(out, "%d\t%s\t\t%s\t%d\n", currTable.tR[i].index, currTable.tR[i].Lex_name, currTable.tR[i].type, currTable.tR[i].size);

	fprintf(out, "\n");
}

token create_token(char n[], int r, int c, int i) {
	token m;
	strcpy(m.token_name, n);
	m.row = r;
	m.col = c;
	m.index = i;
	return m;
}

void insert(char n[], char t[], int s) {
	int m = currTable.entries;
	currTable.tR[m].index = m + 1;
	strcpy(currTable.tR[m].Lex_name, n);
	strcpy(currTable.tR[m].type, t);
	currTable.tR[m].size = s;
	currTable.entries++;
}

void print_token(token t, FILE* out) {
	printf("<%s,%d,%d,%d>", t.token_name, t.row, t.col, t.index);
	fprintf(out, "<%s,%d,%d,%d>", t.token_name, t.row, t.col, t.index);
}

int search(char* name) {
	for (int i = 0; i < currTable.entries; i++)
		if (strcmp(name, currTable.tR[i].Lex_name) == 0)
			return i + 1;
	
	return 0;
}

token SpecChar(char n, int r, int c, int i) {
	char temp[2]; temp[0] = n; temp[1] = '\0';
	return create_token(temp, r, c, i);
}

token getNextToken(FILE* f, FILE* out, FILE* st) {
	int c, cn;
	int t_index = -1;
	c = getc(f);
	col++;

	if (c == EOF) {
		print_table(st);
		return create_token("eof", row, col, -1);
	}

	token T;

	if (c == '#') {
		do {
			c = getc(f);
		} while (c != '\n');
	}

	if (c == '\n') {
		row++;
		col = 0;
		T = SpecChar('\n', row, col, -1);
	}

	else if (c == '+') {
		c = getc(f);

		if (c == '=') {
			T = create_token("+=", row, col, -1);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = create_token("+", row, col, -1);
		}
	}

	else if (c == '@') {
		c = getc(f);

		if (c == '_') {
			T = create_token("@_", row, col, -1);
			col++;
		} else {
			fseek(f, -1, SEEK_CUR);
			T = SpecChar('@', row, col, -1);
		}
	}

	else if (c == '=') {
		T = create_token("=", row, col, -1);
	}

	else if (isalpha(c)) {
		int length = 0;
		int flag = 0;
		char buffer[20];
		buffer[length++] = c;
		c = getc(f);

		while (isalpha(c)) {
			buffer[length++] = c;
			c = getc(f);
		}

		buffer[length] = '\0';
		T = create_token(buffer, row, col, t_index);
		fseek(f, -1, SEEK_CUR);
		col += length;
	}

	else if (c == '$') {
		int length = 1;
		int flag = 0;
		char buffer[20];
		buffer[0] = '$';
		c = getc(f);
		while (isalpha(c)) {
			buffer[length++] = c;
			c = getc(f);
		}

		buffer[length] = '\0';

		if (length == 1) {
			T = SpecChar('$', row, col, -1);
		} else {
			if (search(buffer) == 0) {
				insert(buffer, "int", 4);
				t_index = currTable.entries;
			} else {
				t_index = search(buffer);
			}

			length--;
			T = create_token("id", row, col, t_index);
		}

		fseek(f, -1, SEEK_CUR);
		col += length - 1;
	}

	else if (isdigit(c)) {
		int length = 0;
		do {
			length++;
			c = getc(f);
		} while (isdigit(c));

		T = create_token("num", row, col, -1);
		col += length - 1;
		fseek(f, -1, SEEK_CUR);
	}

	else {
		T = SpecChar(c, row, col, -1);
	}

	if (T.token_name[0] != '\n' && T.token_name[0] != ' ' && T.token_name[0] != '\t') {
		print_token(T, out);
		return T;
	}

	return getNextToken(f, out, st);
}

int main() {
	FILE *f, *lex, *st;
	currTable.entries = 0;
	strcpy(currTableName, "Sample Output");

	f = fopen("prog", "r");
	lex = fopen("lex.txt", "w");
	st = fopen("st.txt", "w");

	while (strcmp(getNextToken(f, lex, st).token_name, "eof") != 0);

	fclose(f);
	fclose(lex);
	fclose(st);

	return 0;
}