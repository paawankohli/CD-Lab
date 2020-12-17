// Q3 uppercase all keywords

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keyword[32][20] = {
						"auto", "break", "case", "char", "const", "continue",
                        "default", "do", "double", "else", "enum", "extern",
                        "float", "for", "goto", "if", "int", "long", "register",
                        "return", "short", "signed", "sizeof", "static", "struct",
                        "switch", "typedef", "union", "unsigned", "void",
                        "volatile", "while"
                       };


void main() {
	char filename[30];
	printf("Enter name of file: ");
	scanf("%s", filename);

	printf("\n");

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Can't open file %s.\n", filename);
		exit(0);
	}

	char buffer[100] = "";
	int bufferIndex = 0;

	char c = getc(in);

	while (c != EOF) {

		if (c == '\"') {
			// string enclosed in double quotes
			while (c != '\"') {
				printf("%c", c);
				c = getc(in);
			}

			printf("%c", c);
		}

		else if (isalpha(c)) {
			buffer[bufferIndex++] = c;
		}

		else {
			buffer[bufferIndex] = '\0';

			// print uppercase if buffer has a keyword
			for (int i = 0; i < 32 ; i++) {
				if (strcmp(buffer, keyword[i]) == 0) {

					for (int k = 0 ; k < bufferIndex ; k++) {
						printf("%c", toupper(buffer[k]));
					}

					bufferIndex = 0;
					buffer[bufferIndex] = '\0';

					break;
				}
			}

			if (bufferIndex != 0) {
				// buffer didn't have a keyword
				printf("%s", buffer);
				bufferIndex = 0;
				buffer[bufferIndex] = '\0';
			}

			// print pending non alpha character
			printf("%c", c);
		}

		c = getc(in);
	}

	printf("\n");
	fclose(in);
}