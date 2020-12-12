/*
Q3.
S -> aAcBe
A -> bA'
A' -> bA'|ε
B -> d
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[100];
int curr;

void S();
void A();
void Aprime();
void B();

void invalid() {
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid() {
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}


void S() {
	// S -> aAcBe
	if (str[curr] == 'a') {
		curr++;
		A();

		if (str[curr] == 'c') {
			curr++;
			B();

			if (str[curr] == 'e') {
				curr++;
				return;
			} else {
				invalid();
			}
		} else {
			invalid();
		}
	} else {
		invalid();
	}
}

void A() {
	// A -> bA'
	if (str[curr] == 'b') {
		curr++;
		Aprime();
	} else {
		invalid();
	}
}

void Aprime() {
	// A' -> bA'|ε
	if (str[curr] == 'b') {
		curr++;
		Aprime();
	}
}

void B() {
	// B -> d
	if (str[curr] == 'd') {
		curr++;
		return;
	} else {
		invalid();
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