// Q1 replaces blank spaces and tabs by single space

#include <stdio.h>

int main() {
	FILE* fa = fopen("in.c", "r");

	if (fa == NULL) {
		printf("Cannot open file\n");
		return 0;
	}

	FILE* fb = fopen("out.c", "w");

	int ca = getc(fa);

	while (ca != EOF) {

		if (ca == ' ' || ca == '\t') {
			putc(' ', fb);

			while (ca == ' ' || ca == '\t') {
				ca = getc(fa);
			}
		}

		putc(ca, fb);
		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
}