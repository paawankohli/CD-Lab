#include <stdio.h>
int main()
{
	FILE *fa,*fb;
	int ca,cb;
	fa=fopen("l1in.c","r");
	if(fa==NULL){
		printf("error");
		exit(0);
	}
	fb=fopen("l1out.c","w");
	ca=getc(fa);
	while(ca!=EOF){
		if(ca==' ')
		{
			//printf("%c 1\n",ca);
			putc(ca,fb);
			while(ca==' '){
				ca=getc(fa);
			}
			putc(ca,fb);
		}
		else if(ca=='\n')
		{
			putc(' ',fb);
		}
		else if(ca=='\t')
		{
			putc(' ',fb);
		}
		else
		{
			//printf("%c 2\n",ca);
			putc(ca,fb);
		}
		ca=getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
	}