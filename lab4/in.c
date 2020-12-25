int sum(int a, int b)
{	
	// single line comment
	int s = a + b;
	return s;
}

bool search(int *arr, int key)
{

	/* multiline comment


	lol


	*/
	for (int i = 0; i < 10; i++) 
	{
		if (arr[i] == key)
			return true;
		else 
			return false;
	}
}

void main()
{
	int a[20], i, res;
	bool status;
	printf("Enter array elements:");

	for (i = 0; i < 10; ++i)
		scanf("%d", &a[i]);

	res = sum(a[0], a[4]);
	status = search(a, res);
	printf("%d", status);
}