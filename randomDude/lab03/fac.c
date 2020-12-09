// C program to find factorial of given number 
#include<stdio.h> 

// function to find factorial of given number 
int factorial(int n) 
{ 
	if (n == 0) 
	return 1; 
	return n * factorial(n - 1); 
} 

int main() 
{ 
	int num = 5; 
	printf("Factorial of %d is %d", num, factorial(num)); 
	return 0; 
} 
