#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keyword[32][20] = {"auto", "break", "case", "char", "const", "continue",
                        "default", "do", "double", "else", "enum", "extern",
                        "float", "for", "goto", "if", "int", "long", "register",
                        "return", "short", "signed", "sizeof", "static", "struct",
                        "switch", "typedef", "union", "unsigned", "void",
                        "volatile", "while"
                       };

void main() {
	
	char filename[30] = "in.c";
	// printf("Enter name of file: ");
	// scanf("%s", filename);
	printf("\n");

	FILE* in = fopen(filename, "r");

	if (in == NULL) {
		printf("Can't open file %s.\n", filename);
		exit(0);
	}

	char buffer[100] = "";
	int bufferIndex = 0;

	char c = getc(in);
}