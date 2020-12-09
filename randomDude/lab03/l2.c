#include <stdio.h>
int main()
{
	FILE *fa,*fb;
	int ca,cb;
	fa=fopen("prime1.c","r");
	if(fa==NULL){
		printf("error");
		exit(0);
	}
	fb=fopen("prime.c","w");
	ca=getc(fa);
	while(ca!=EOF){
		if(ca=='\n')
		{
			printf("%c",ca);
			ca=getc(fa);
			// while(ca==' ')
			// 	ca=getc(fa);
			if(ca=='#')
			{
				printf("%c",ca);
				while(ca!='\n')
					ca=getc(fa);
			}
			else
			{
				printf("%c",ca);
				while(ca!='\n')
				{
					//printf("%c",ca);
					putc(ca,fb);
					ca=getc(fa);

				}
			}
		}
		else
		{
			printf("%c",ca);
			if(ca=='#')
			{
				while(ca!='\n')
					ca=getc(fa);
			}
			else
			{
				while(ca!='\n')
				{
					printf("%c",ca);
					putc(ca,fb);
					ca=getc(fa);

				}
			}
		}
	}


fclose(fa);
fclose(fb);
	return 0;
}