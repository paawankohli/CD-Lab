/*
Q1.
S -> a | > | (T)
T -> ST'
T' -> ,ST'| ε
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr;
char str[100];

void S();
void T();
void Tprime();

void invalid() {
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid() {
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}




void S() {
	
	// S -> a
	if (str[curr] == 'a') {
		curr++;
		return;
	}

	// S -> >
	else if (str[curr] == '>') {
		curr++;
		return;
	}

	// S -> (T)
	else if (str[curr] == '(') {
		curr++;

		T();
		
		if (str[curr] == ')') {
			curr++;
			return;
		}
		else {
			invalid();
		}
	}

	// none of the possibilities match - invalid
	else {
		invalid();
	}
}

void T() {
	// T -> ST'
	S();
	Tprime();
}

void Tprime() {
	// T' -> ,ST'| ε
	if (str[curr] == ',') {
		curr++;
		S();
		Tprime();
	}
}

int main() {
	printf("Enter String: ");
	scanf("%s", str);
	curr = 0;

	// start symbol
	S();
	
	if (str[curr] == '$') {
		valid();
	} else {
		invalid();
	}
}