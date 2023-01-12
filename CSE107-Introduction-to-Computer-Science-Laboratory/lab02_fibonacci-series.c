#include <stdio.h>
#include <stdlib.h>

/* Lab06 Yusuf Arslan */

int main() 
{
	int i, n, t1 = 0, t2 = 1, temp;
    	printf("Enter the number of terms: ");
    	scanf("%ld", &n);
    
    	printf("\n\nFibonacci Series\n");
   	printf ("--------------------\n");

    	for (i = 1; i < n; ++i) 
    	{
		printf("%ld, ", t1);
		temp = t1 + t2;
		t1 = t2;
		t2 = temp;
   	}
	printf ("%ld",t1);
	return 0;
}
