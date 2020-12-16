// Sample: Identification of arithmetic and relational operators from the given input file

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
	FILE *fp = fopen("in.c", "r");

	if (fp == NULL) {
		printf("Cannot open file \n");
		exit(0);
	}

	char c = fgetc(fp);
	char buf[30];

	while (c != EOF) {
		int i = 0;
		buf[0] = '\0';

		if (c == '=') {
			buf[i++] = c;
			c = fgetc(fp);

			if (c == '=') {
				buf[i++] = c;
				buf[i] = '\0';
				printf("\n Relational operator : %s", buf);
			} else {
				buf[i] = '\0';
				printf("\n Assignment operator: %s", buf);
			}

		} else {
			if (c == '<' || c == '>' || c == '!') {
				buf[i++] = c;
				c = fgetc(fp);

				if (c == '=') {
					buf[i++] = c;
				}

				buf[i] = '\0';
				printf("\n Relational operator : %s", buf);
			} else {
				buf[i] = '\0';
			}
		}

		c = fgetc(fp);
	}
	printf("\n");
}