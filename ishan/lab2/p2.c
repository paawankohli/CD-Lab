// Q2 discard preprocessor directives

#include <stdio.h>

int main() {

	FILE* fa = fopen("in.c", "r");

	if (fa == NULL) {
		printf("Cannot open file\n");
		return 0;
	}

	FILE* fb = fopen("out.c", "w");

	int ca, cprev;

	ca = getc(fa);
	cprev = -1;

	while (ca != EOF) {
		if (ca == '#' && (cprev == -1 || cprev == '\n')) {

			while (cprev != '\n') {
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

	return 0;
}