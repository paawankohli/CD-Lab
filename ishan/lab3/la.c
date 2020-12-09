#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int row = 1;
int col = 0;
char keyword[][20] = {"int", "if", "else", "while", "for", "char", "do"};
int nok = 7;
typedef struct
{
	char token_name[20];
	unsigned int row, col;
} token;
token create_token(char n[], int r, int c)
{
	token m;
	strcpy(m.token_name, n);
	m.row = r;
	m.col = c;
	return m;
}
void print_token(token t)
{
	printf("<%s,%d,%d>", t.token_name, t.row, t.col);
}
token ArOp(int key, int r, int c)
{
	switch (key)
	{
	case 1:
		return create_token("ADD", r, c);
	case 2:
		return create_token("SUB", r, c);
	case 3:
		return create_token("MUL", r, c);
	case 4:
		return create_token("DIV", r, c);
	case 5:
		return create_token("MOD", r, c);
	case 6:
		return create_token("INC", r, c);
	case 7:
		return create_token("DEC", r, c);
	}
}
token RelOp(int key, int r, int c)
{
	switch (key)
	{
	case 1:
		return create_token("EQ", r, c);
	case 2:
		return create_token("NE", r, c);
	case 3:
		return create_token("GT", r, c);
	case 4:
		return create_token("LT", r, c);
	case 5:
		return create_token("GE", r, c);
	case 6:
		return create_token("LE", r, c);
	}
}
token LogOp(int key, int r, int c)
{
	switch (key)
	{
	case 1:
		return create_token("AND", r, c);
	case 2:
		return create_token("ORR", r, c);
	case 3:
		return create_token("NOT", r, c);
	}
}
token AssOp(int key, int r, int c)
{
	switch (key)
	{
	case 1:
		return create_token("ASS", r, c);
	case 2:
		return create_token("ADA", r, c);
	case 3:
		return create_token("SBA", r, c);
	case 4:
		return create_token("MLA", r, c);
	case 5:
		return create_token("DVA", r, c);
	case 6:
		return create_token("MDA", r, c);
	}
}
token SpecChar(char n, int r, int c)
{
	char temp[2];
	temp[0] = n;
	temp[1] = '\0';
	return create_token(temp, r, c);
}
int getNextToken(FILE* f)
{
	int c;
	c = getc(f);
	col++;
	if (c == EOF)
		return 0;
	token T;
	if (c == '\n')
	{
		c = getc(f);
		row++;
		col = 1;
		printf("\n");
	}
	if (c == ' ')
	{
		c = getc(f);
		col++;
	}
	if (c == '\"')
	{
		int length = 0;
		do
		{
			c = getc(f);
			length++;
		} while (c != '\"');
		T = create_token("string", row, col);
		col += length;
	}
	else if (c == '+')
	{
		c = getc(f);
		if (c == '+')
		{
			T = ArOp(6, row, col);
			col++;
		}
		else if (c == '=')
		{
			T = AssOp(2, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = ArOp(1, row, col);
		}
	}
	else if (c == '-')
	{
		c = getc(f);
		if (c == '-')
		{
			T = ArOp(7, row, col);
			col++;
		}
		else if (c == '=')
		{
			T = AssOp(3, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = ArOp(2, row, col);
		}
	}
	else if (c == '*')
	{
		c = getc(f);
		if (c == '=')
		{
			T = AssOp(4, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = ArOp(3, row, col);
		}
	}
	else if (c == '/')
	{
		c = getc(f);
		if (c == '=')
		{
			T = AssOp(5, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = ArOp(4, row, col);
		}
	}
	else if (c == '%')
	{
		c = getc(f);
		if (c == '=')
		{
			T = AssOp(6, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = ArOp(5, row, col);
		}
	}
	else if (c == '=')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(1, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = AssOp(1, row, col);
		}
	}
	else if (c == '!')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(2, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = LogOp(3, row, col);
		}
	}
	else if (c == '>')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(5, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = RelOp(3, row, col);
		}
	}
	else if (c == '<')
	{
		c = getc(f);
		if (c == '=')
		{
			T = RelOp(6, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = RelOp(4, row, col);
		}
	}
	else if (c == '&')
	{
		c = getc(f);
		if (c == '&')
		{
			T = LogOp(1, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = SpecChar('&', row, col);
		}
	}
	else if (c == '|')
	{
		c = getc(f);
		if (c == '|')
		{
			T = LogOp(2, row, col);
			col++;
		}
		else
		{
			fseek(f, -1, SEEK_CUR);
			T = SpecChar('|', row, col);
		}
	}
	else if (isalpha(c))
	{
		int length = 0;
		int flag = 0;
		char buffer[20];
		do
		{
			buffer[length++] = c;
			c = getc(f);
		} while (isalpha(c));
		buffer[length] = '\0';
		for (int j = 0; j < nok; j++)
			if (strcmp(keyword[j], buffer) == 0)
			{
				T = create_token(buffer, row, col);
				flag++;
				break;
			}
		if (flag == 0)
		{
			T = create_token("id", row, col);
			fseek(f, -1, SEEK_CUR);
			length--;
		}
		col += length;
	}
	else if (isdigit(c) || c == '.')
	{
		int length = 0;
		do
		{
			length++;
			c = getc(f);
		} while (isdigit(c) || c == '.');
		T = create_token("num", row, col);
		col += length - 1;
		fseek(f, -1, SEEK_CUR);
	}
	else if (c != ' ')
		T = SpecChar(c, row, col);
	print_token(T);
	return 1;
}
int main()
{
	FILE *f, *fa, *fb;
	char ca, cprev, cb;
	fa = fopen("prog.c", "r");
	fb = fopen("temp1.c", "w");
	if (fa == NULL)
	{
		printf("Cannot open file");
		return 0;
	}
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == ' ' || ca == '\t')
		{
			putc(' ', fb);
			while (ca == ' ' || ca == '\t')
				ca = getc(fa);
		}
		putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	fa = fopen("temp1.c", "r");
	fb = fopen("temp2.c", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == '/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while (ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*')
			{
				do
				{
					while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else
			putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	fa = fopen("temp2.c", "r");
	fb = fopen("temp1.c", "w");
	ca = getc(fa);
	cprev = -1;
	while (ca != EOF)
	{
		if (ca == '#' && (cprev == -1 || cprev == '\n'))
		{
			while (cprev != '\n')
			{
				cprev = ca;
				ca = getc(fa);
			}
		}
		putc(ca, fb);
		cprev = ca;
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	f = fopen("temp1.c", "r");
	while (getNextToken(f));
	fclose(f);
	printf("\n");
	return 0;
}