
int prime(int n)
{
	int i;
	for(i=0x2;i<sqrt(n);i++)
		if(n%i==0&&i<=n)
			return 0;
		return 1;
}

int main()
{
	int n,i;
	int x[]={1,2,13,7};
	printf("enetr a number");
	scanf("%d",&n);
	/* call and display 
	whether prime or not*/
	for(i=0;i<n;i++)
		if(prime(x[i]))
			printf("is prime\n");
		else
			printf("not a prime\n");
		return 0;
}