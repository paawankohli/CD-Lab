/*
Q4.
S -> (L)|a
L -> SL'
L' -> ,SL'|ε
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];

void S();
void L();
void Lprime();

void invalid() {
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid() {
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}



void S() {
	// S -> (L)
	if (str[curr] == '(') {
		curr++;
		L();

		if (str[curr] == ')') {
			curr++;
			return;
		}
		else {
			invalid();
		}
	}
	// S -> a
	else if (str[curr] == 'a') {
		curr++;
		return;
	}
	// invalid
	else {
		invalid();
	}
}

void L() {
	// L -> SL'
	S();
	Lprime();
}

void Lprime() {
	// L' -> ,SL'|ε
	if (str[curr] == ',') {
		curr++;
		S();
		Lprime();
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