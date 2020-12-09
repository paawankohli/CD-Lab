// Q3 uppercase all keywords

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keyword[][20] = {"int", "if", "while", "for", "char", "return"};
int nok = 6;

int main() {

	FILE* fa = fopen("prog.c", "r");

	if (fa == NULL) {
		printf("Cannot open file\n");
		return 0;
	}

	char buffer[20];
	int i = 0;

	int ca = getc(fa);

	while (ca != EOF) {
		if (ca == '\"') {
			ca = getc(fa);

			while (ca != '\"') {
				ca = getc(fa);
			}
		}

		if (isalpha(ca)) {
			buffer[i++] = ca;
		} else {
			buffer[i] = '\0';

			for (int j = 0; j < nok; j++) {

				if (strcmp(keyword[j], buffer) == 0) {

					for (int k = 0; k < i; k++) {
						printf("%c", toupper(buffer[k]));
					}

					printf("\n");
					break;
				}
			}

			i = 0;
		}

		ca = getc(fa);
	}

	fclose(fa);
	return 0;
}