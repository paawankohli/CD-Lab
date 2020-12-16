// Q2 discard preprocessor directives

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void main() {
	char filename[30];
	printf("Enter name of file: ");
	scanf("%s", filename);

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Can't open file %s.\n", filename);
		exit(0);
	}

	char buffer[100];
	int bufferIndex = 0;
	buffer[bufferIndex] = '\0';

	char c = getc(in);

	while (c != EOF) {

		if (c == '#') {
			buffer[bufferIndex++] = c;
			c = getc(in);

			while (isalpha(c)) {
				buffer[bufferIndex++] = c;
				c = getc(in);
			}

			buffer[bufferIndex] = '\0';

			if (strcmp(buffer, "#define") == 0 || strcmp(buffer, "#include") == 0) {
				while (c != '\n') {
					c = getc(in);
				}
			} else {
				printf("%s", buffer);
				printf("%c", c);
			}

			bufferIndex = 0;
			buffer[bufferIndex] = '\0';
		}

		else {
			printf("%c", c);
		}

		c = getc(in);
	}

	printf("\n");

	fclose(in);
}