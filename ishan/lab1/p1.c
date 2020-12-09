// Q1 count the number of lines and characters in a file

#include <stdio.h>

int main() {

	printf("Enter filename to open for reading: \t");
	char filename[100];
	scanf("%s", filename);

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Cannot open file %s \n", filename);
		return 0;
	}

	int count = 0, line = 0;
	char c;

	while ((c = fgetc(in)) != EOF) {
		count++;

		if (c == '\n') {
			line++;
		}
	}

	printf("Number of characters = %d\n Number of lines = %d\n", count, line);
	fclose(in);

	return 0;
}