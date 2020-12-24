#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parser_helper.c"

token curr;

void valid() {
	printf("---------SUCCESS----------\n");
	exit(0);
}

void invalid(char buff[], int r, int c) {
	printf("Expected %s at row:%d col:%d\n", buff, r, c);
	printf("------------ERROR-------------\n");
	exit(0);
}


void interfaceDecl();
void int_mod();
void en_interfaces();
void Cprime();
void interf_body();
void int_mem_declarations();
void Bprime();
void int_mem_dec();
void const_declaration();
void constid_list();
void Aprime();
void Aprimeprime();
void constmod();
void type();
void interfacetype();








void interfaceDecl() {
	int_mod();

	if (strcmp(curr.name, "interface") == 0) {
		curr = getNext();
		if (strcmp(curr.name, "id") == 0) {
			curr = getNext();
			if (strcmp(curr.name, "extends") == 0) {
				curr = getNext();

				en_interfaces();
				interf_body();

			} else
				invalid("extends", curr.row, curr.col);
		} else
			invalid("id", curr.row, curr.col);
	} else
		invalid("interface", curr.row, curr.col);
}

void int_mod() {
	if (strcmp(curr.name, "public") == 0 ||
	        strcmp(curr.name, "private") == 0 ||
	        strcmp(curr.name, "abstract") == 0) {
		curr = getNext();
	}
}

void en_interfaces() {
	interfacetype();
	Cprime();
}

void Cprime() {
	if (strcmp(curr.name, ",") == 0) {
		curr = getNext();

		interfacetype();
		Cprime();
	}
}

void interf_body() {
	if (strcmp(curr.name, "{") == 0) {
		curr = getNext();
		int_mem_declarations();
		if (strcmp(curr.name, "}") == 0) {
			curr = getNext();
		} else
			invalid("}", curr.row, curr.col);
	} else
		invalid("{", curr.row, curr.col);
}

void int_mem_declarations() {
	int_mem_dec();
	Bprime();
}

void Bprime() {
	if (strcmp(curr.name, "public") == 0 ||
	        strcmp(curr.name, "private") == 0 ||
	        strcmp(curr.name, "final") == 0) {

		int_mem_dec();
		Bprime();
	}
}

void int_mem_dec() {
	const_declaration();
}

void const_declaration() {
	if (strcmp(curr.name, "public") == 0 || strcmp(curr.name, "private") == 0 || strcmp(curr.name, "final") == 0) {

		constmod();
		type();
		constid_list();

		if (strcmp(curr.name, ";") == 0) {
			curr = getNext();
			const_declaration();
		} 
		else invalid(";", curr.row, curr.col);
	}
}

void constid_list() {
	if (strcmp("id", curr.name) == 0) {
		curr = getNext();
		Aprime();
	} 
	else invalid("id", curr.row, curr.col);
}

void Aprime() {
	if (strcmp(curr.name, "[") == 0) {
		curr = getNext();

		if (strcmp(curr.name, "number") == 0) {
			curr = getNext();

			if (strcmp(curr.name, "]") == 0) {
				curr = getNext();

				Aprimeprime();
			} 
			else invalid("]", curr.row, curr.col);

		} else invalid("number", curr.row, curr.col);

	} 
	else if (strcmp(curr.name, ",") == 0) {
		curr = getNext();
		constid_list();
	}
}

void Aprimeprime() {
	if (strcmp(curr.name, ",") == 0) {
		curr = getNext();
		constid_list();
	}
}

void constmod() {
	if (strcmp("public", curr.name) == 0 || strcmp("final", curr.name) == 0 || strcmp("static", curr.name) == 0) {
		curr = getNext();
	}
	else invalid("public, final or static", curr.row, curr.col);
}

void type() {

	if (strcmp("int", curr.name) == 0 || strcmp("boolean", curr.name) == 0 || strcmp("float", curr.name) == 0) {
		curr = getNext();
	}
	else invalid("int, float or boolean", curr.row, curr.col);
}

void interfacetype() {
	if (strcmp("id", curr.name) == 0) {
		curr = getNext();
	} 
	else invalid("id", curr.row, curr.col);
}

void main() {
	in = fopen("in.java", "r");

	curr = getNext();
	interfaceDecl();

	if (strcmp(curr.name, "EOF") == 0)
		valid();
	else
		invalid("EOF", curr.row, curr.col);
}