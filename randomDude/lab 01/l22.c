#include <stdio.h>
int main()
{
	FILE *input,*output;
	int ch;
	input=fopen("l2in.c","r");
	if(input==NULL){
		printf("error");
		exit(0);
	}
	output=fopen("l2out.c","w");
	
do {
		ch = getc(input); // Get character from input file.
		if (ch == '#') { // If a #if found, loop till you find the next '\n'
			while (ch != '\n') { 
				ch = getc(input);
			}
			// ch = getc(input); // If you want to delete the line too
		}
		putc(ch, output);
	} while (ch != EOF);
	fclose(input);
	fclose(output);

	return 0;

}

