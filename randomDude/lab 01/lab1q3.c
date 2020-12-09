#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000

char keywords[32][20] = { "auto\0", "double\0", "int\0", "struct\0", "break\0", "else\0", "long\0", "switch\0", "case\0","enum\0", "register\0", "typedef\0", "char\0", "extern\0","return\0","union\0","const\0","float\0","short\0", "unsigned\0", "continue\0", "for\0", "signed\0", "void\0", "default\0", "goto\0", "sizeof\0", "voltile\0", "do\0", "if\0", "static\0", "while\0" };

int isKeyword( char * str ){
	for( int i = 0 ; i < 32 ; i++ ) if( strcmp( keywords[i] , str ) == 0 ) return 1;
	return 0;
}

void toUpperCase( char * str , int le ){
	for( int i = 0 ; i < le ; i++ ){
		if( str[i] >= 'a' && str[i] <= 'z' ) str[i] = str[i] - ( 'a' - 'A' );
	}
}

int main(){
	FILE * fp1 , * fp2;
	char ch , buf[MAX] = { '\0' } , * tk;
	int ln = 0 , rsofar = 0 , curr_rsofar = 0;
	fp1 = fopen( "l3in.c" , "r" );
	fp2 = fopen( "l3out.c" , "w" );
	if( !fp1 || !fp2 ){
		printf("Error accessing files.\n");
		exit(0);
	}
	//printf("Processing file...\n");
	while( !feof( fp1 ) ){
		ln++;
		curr_rsofar = 0;
		fgets( buf , MAX , fp1 );
		tk = strtok( buf , " \t" );
		while( tk ){
			if( isKeyword( tk ) ){
				toUpperCase( tk , strlen(tk) );
				fprintf( fp2 , "%s %d %d\n" , tk , ln , ( curr_rsofar + strlen(tk) ) );
			}
			curr_rsofar += ( strlen(tk) + 1 );
			tk = strtok( NULL , " \t" );
		}
		rsofar += curr_rsofar;
	}
	fclose(fp1);
	fclose(fp2);
	//printf("Operation complete.\n");
}
