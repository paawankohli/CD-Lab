// Q1 replaces blank spaces and tabs by single space

#include <stdio.h>
#include <stdlib.h>

void main() {
	char filename[30];
	printf("Enter name of file: ");
	scanf("%s", filename);

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Can't open file %s.\n", filename);
		exit(0);
	}

	FILE* out = fopen("out.c", "w");

	char c = getc(in);

	while (c != EOF) {

		if (c == '\t' || c == ' ') {
			putc(' ', out);

			while (c == ' ' || c == '\t') {
				c = getc(in);
			}
		}

		else {
			putc(c, out);
			c = getc(in);
		}
	}

	printf("File generated : out.c\n");

	fclose(in);
	fclose(out);
}