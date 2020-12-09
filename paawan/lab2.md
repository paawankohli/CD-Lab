# CD Lab 1
##### Name: Paawan Kohli
##### Reg No: 180905416

### Sample Question: Remove Spaces and Comments

```c
#include <stdio.h>

int main() {
	char filename[30];
	printf("Enter name of a .c file: ");
	scanf("%s", filename);

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Cannot open file\n");
		return 0;
	}

	FILE* out = fopen("out.c", "w");

	int c = getc(in);

	while (c != EOF) {

		if (c == ' ') {
			putc(' ', out);

			while (c == ' ') {
				c = getc(in);
			}
		}

		if (c == '/') {
			int cnext = getc(in);

			if (cnext == '/') {

				while (c != '\n') {
					c = getc(in);
				}

			}

			else if (cnext == '*') {
				do {

					while (c != '*') {
						c = getc(in);
					}

					c = getc(in);
				} while (c != '/');
			}

			else {
				putc(c, out);
				putc(cnext, out);
			}
		}

		else {
			putc(c, out);
		}

		c = getc(in);
	}

	fclose(in);
	fclose(out);

	printf("Output file generated: out.c\n");

	return 0;
}
```

##### Input file:
![samplea](./lab2/screenshot/samplea.png)


##### Terminal:
![sampleb](./lab2/screenshot/sampleb.png)


##### Output file:
![samplec](./lab2/screenshot/samplec.png)