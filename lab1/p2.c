// Q2 reverse the file contents and store in another file.
// display the size of file using file handling function.

#include <stdio.h>

int main() {

	printf("Enter filename to open for reading: ");
	char filename[100];
	scanf("%s", filename);

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Cannot open file %s \n", filename);
		return 0;
	}
	
	printf("Enter resultant filename to open for writing: ");
	scanf("%s", filename);

	FILE* out = fopen(filename, "w");
	
	fseek(in, 0, SEEK_END);
	long int count = ftell(in);
	char c;

	for (long int i = 0; i < count - 1; i++) {
		fseek(in, -2, SEEK_CUR);
		c = fgetc(in);
		fputc(c, out);
	}

	printf("Size of file = %ld bytes\n", count);

	fclose(in);
	fclose(out);

	return 0;
}