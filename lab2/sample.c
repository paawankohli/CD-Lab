// Sample Question: Remove Spaces and Comments

#include <stdio.h>

int main() {
	FILE* fa = fopen("prog.c", "r");

	if (fa == NULL) {
		printf("Cannot open file\n");
		return 0;
	}

	FILE* fb = fopen("out.c", "w");

	int ca = getc(fa);

	while (ca != EOF) {

		if (ca == ' ') {
			putc(' ', fb);

			while (ca == ' ') {
				ca = getc(fa);
			}
		}

		if (ca == '/') {
			int cb = getc(fa);

			if (cb == '/') {

				while (ca != '\n') {
					ca = getc(fa);
				}

			} 

			else if (cb == '*') {
				do {

					while (ca != '*') {
						ca = getc(fa);
					}

					ca = getc(fa);
				} while (ca != '/');
			}
			
			else {
				putc(ca, fb);
				putc(cb, fb);
			}
		} 

		else {
			putc(ca, fb);
		}

		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);

	return 0;
}