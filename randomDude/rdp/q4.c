#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;int j;
int r=1,t=0;
char first_lexp[][2]={"n","i","("};
char first_aterm[][2]={"n","i"};
char first_list[][2]={"("};
char first_lexps[][2]={"n","i","("};
char first_a[][2]={"n","i","(","@"};

char follow_lexp[][2]={"$",")","n","i","("};
char follow_aterm[][2]={"$",")","n","i","("};
char follow_list[][2]={"$",")","n","i","("};
char follow_lexps[][2]={")"};
char follow_a[][2]={")"};

void proc_lexps();
void proc_aterm();
void proc_list();
void proc_a();
void proc_lexp()
{
    if(lookahead->type==6||lookahead->type==8)
    {
        proc_aterm();
    }
    else if(strcmp(lookahead->ln,first_lexp[2])==0)
        proc_list();
    else{
        printf("\n error number,identifier or ( expected");
        exit(0);
    }

}
void proc_aterm()
{
     if(lookahead->type==6||lookahead->type==8)
        return;
     else{
        printf("\n error number or identifier expected");
        exit(0);
     }
}
void proc_list()
{
        if(strcmp(lookahead->ln,first_list[0])==0)
        {
             lookahead=getNextToken(fb,&r,&t);
             proc_lexps();
        }
        else{
            printf("\n ( expected");
            exit(0);
        }
}
void proc_lexps()
{
     if(lookahead->type==6||lookahead->type==8||strcmp(lookahead->ln,first_lexps[2])==0)
        {
            proc_lexp();
             lookahead=getNextToken(fb,&r,&t);
             proc_a();
        }
        else{
            printf("\n error number , identifier or ( expected");
            exit(0);
        }
}
void proc_a()
{
         if(lookahead->type==6||lookahead->type==8||strcmp(lookahead->ln,first_a[2])==0)
            {
                 proc_lexp();
             lookahead=getNextToken(fb,&r,&t);
             proc_a();
            }
            else if(strcmp(lookahead->ln,follow_a[0])==0)
                    {
                        return;

                    }
                    else{
                        printf("\n error number,identifier,( or ) expected");
                        exit(0);
                    }
}
int main()
{

    fb=fopen("text4.txt","r");
   lookahead=getNextToken(fb,&r,&t);

    proc_lexp();
 lookahead=getNextToken(fb,&r,&t);

   if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nError");


}
