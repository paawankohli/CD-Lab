// Q3 merges lines alternatively from 2 files and stores it in a resultant file

#include <stdio.h>

int main() {
	char filename[100];

	printf("Enter first filename to open for reading: \t");
	scanf("%s", filename);
	FILE* in1 = fopen(filename, "r");

	if (in1 == NULL) {
		printf("Cannot open file %s \n", filename);
		return 0;
	}

	printf("Enter second filename to open for reading: \t");
	scanf("%s", filename);
	FILE* in2 = fopen(filename, "r");

	if (in2 == NULL) {
		printf("Cannot open file %s \n", filename);
		return 0;
	}

	printf("Enter resultant filename to open for writing: \t");
	scanf("%s", filename);
	FILE* out = fopen(filename, "w");

	int context = 1, flag = 1;
	char c1, c2;

	while (flag) {
		if (context == 1) {
			
			while ((c1 = fgetc(in1)) != EOF) {
				fputc(c1, out);
				if (c1 == '\n') {
					context = 2;
					break;
				}
			}

			if (c1 == EOF) {
				flag = 0;
			}

		} else {

			while ((c2 = fgetc(in2)) != EOF) {
				fputc(c2, out);
				if (c2 == '\n') {
					context = 1;
					break;
				}
			}

			if (c2 == EOF) {
				flagc = 0;
			}
		}
	}

	while ((c1 = fgetc(in1)) != EOF) {
		fputc(c1, out);
	}

	while ((c2 = fgetc(in2)) != EOF) {
		fputc(c2, out);
	}

	fclose(in1);
	fclose(in2);
	fclose(out);

	return 0;
}