#include <stdio.h>

void main()
{
	float array[15];
	for (int i = 0; i < 15; i++)
	{
		printf("Enter price for Row %i:", i+1);
		fflush(stdout);
		scanf("%f", &array[i]);
	}

	char seats[15][30];
	for (int i = 0; i < 15; i ++)
	{
		printf("Row %i\t seats",i);
	}
}


