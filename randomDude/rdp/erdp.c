#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
FILE *fb;
int r=1,t=0;
void proc_t()
{
    lookahead=getNextToken(fb,&r,&t);
    if(strcmp(lookahead->ln,"*")==0)
    {
        lookahead=getNextToken(fb,&r,&t);
         if(lookahead->type==6)
    {
        lookahead=getNextToken(fb,&r,&t);
        return;
    }
    else{
        printf("\n Error");
        exit(0);
    }
    }
    else
    {
        if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
        exit(0);
    }


}
void proc_e()
{
    lookahead=getNextToken(fb,&r,&t);
    if(lookahead->type==6)
    {

        proc_t();
    }
    else

    {
          printf("\n Error");
          exit(0);
    }

}

int main()
{
    fb=fopen("test.txt","r");

    proc_e();
    if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nError");
}
