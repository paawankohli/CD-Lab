#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;int j;
 char ip[][20]={"a","b","b","b","c","d","e","$"};
int r=1,t=0;int k=0;
char first_s[][2]={"a"};
char first_a2[][2]={"b","@"};
char first_a[][2]={"b"};
char first_b[][2]={"d"};
char follow_s[][2]={"$"};
char follow_a[][2]={"c"};
char follow_a2[][2]={"e"};
char follow_b[][2]={"c"};

void proc_a2();
void proc_b();
void proc_a();
void proc_s()
{



	for(j=0;j<1;j++)
	{
		if(strcmp(ip[k],first_s[j])==0)
		{
			break;
		}
	}
	if(j==0)
    {
        k++;
        proc_a();
       k++;
        if(strcmp(ip[k],"c")==0)
        {
             k++;
             proc_b();
             k++;
              if(strcmp(ip[k],"e")==0)
                return;

        }
        else
        {
            printf("\n c expected ");
            exit(0);
        }
    }
    else
    {
        printf("\n a expected");exit(0);
    }
}
void proc_a()
{
     if(strcmp(ip[k],"b")==0)
        {
            k++;
             proc_a2();

        }
        else{
            printf("\n b expected ");
            exit(0);
        }
}
void proc_a2()
{
    if(strcmp(ip[k],"b")==0)
        {
             k++;
             proc_a2();

        }
    else if(strcmp(ip[k],"c")==0)
    {
        k--;
        return;
    }
    else
    {
        printf("b or c expected");exit(0);
    }
}
void proc_b()
{
    if(strcmp(ip[k],"d")==0)
        {
            return;
        }
        else{
            printf("\n d expected");
            exit(0);
        }
}
int main()
{


  proc_s();

k++;
   if(strcmp(ip[k],"$")==0)
        printf("Successfull");
    else
        printf("\nError");


}


