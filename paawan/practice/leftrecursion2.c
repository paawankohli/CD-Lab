1:  #include<stdio.h>  
2:  #include<string.h>  
3:  #define SIZE 10  
4:  int main () {  
5:       char non_terminal;  
6:       char beta,alpha;  
7:       int num;  
8:       char production[10][SIZE];  
9:       int index=3; /* starting of the string following "->" */  
10:       printf("Enter Number of Production : ");  
11:       scanf("%d",&num);  
12:       printf("Enter the grammar as E->E-A :\n");  
13:       for(int i=0;i<num;i++){  
14:            scanf("%s",production[i]);  
15:       }  
16:       for(int i=0;i<num;i++){  
17:            printf("\nGRAMMAR : : : %s",production[i]);  
18:            non_terminal=production[i][0];  
19:            if(non_terminal==production[i][index]) {  
20:                 alpha=production[i][index+1];  
21:                 printf(" is left recursive.\n");  
22:                 while(production[i][index]!=0 && production[i][index]!='|')  
23:                      index++;  
24:                 if(production[i][index]!=0) {  
25:                      beta=production[i][index+1];  
26:                      printf("Grammar without left recursion:\n");  
27:                      printf("%c->%c%c\'",non_terminal,beta,non_terminal);  
28:                      printf("\n%c\'->%c%c\'|E\n",non_terminal,alpha,non_terminal);  
29:                 }  
30:                 else  
31:                      printf(" can't be reduced\n");  
32:            }  
33:            else  
34:                 printf(" is not left recursive.\n");  
35:            index=3;  
36:       }  
37:  }  