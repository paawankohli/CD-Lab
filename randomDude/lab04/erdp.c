#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexical.h"

tokenptr lookahead;
int i=0;
FILE*fa;
int l=1,c=0;
void proc_t();
void proc_e()
{
    lookahead=getNextToken(fa,&l,&c);
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
void proc_t()
{
    lookahead=getNextToken(fa,&l,&c);
    if(strcmp(lookahead->ln,"*")==0)
    {
        lookahead=getNextToken(fa,&l,&c);
         if(lookahead->type==6)
    {
        lookahead=getNextToken(fa,&l,&c);
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
int main()
{
    fa=fopen("ex1.txt","r");

    proc_e();
    if(strcmp(lookahead->ln,"$")==0)
        printf("Successfull");
    else
        printf("\nError");
}
