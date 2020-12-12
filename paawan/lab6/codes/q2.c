/*
Q2.
S -> UVW
U -> (S)|aSb|d
V -> aV| ε
W -> cW| ε
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr;
char str[100];

void S();
void U();
void V();
void W();

void invalid() {
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid() {
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}




void S() {
	// S -> UVW
	U();
	V();
	W();
}

void U() {

	// U -> (S)
	if (str[curr] == '(') {
		curr++;

		S();

		if (str[curr] == ')') {
			curr++;
			return;
		}
		else {
			invalid();
		}
	}

	// U -> aSb
	else if (str[curr] == 'a') {
		curr++;
		S();

		if (str[curr] == 'b') {
			curr++;
			return;
		}
		else {
			invalid();
		}
	}

	// U -> d
	else if (str[curr] == 'd') {
		curr++;
		return;
	}

	// none of the possibilities match - invalid
	else {
		invalid();
	}
}

void V() {
	// V -> aV| ε
	if (str[curr] == 'a') {
		curr++;
		V();
	}
}

void W() {
	// W -> cW| ε
	if (str[curr] == 'c') {
		curr++;
		W();
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