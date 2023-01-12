#include <stdio.h>

int main() {
	
   int i, n, m = 0;
   
    printf("Enter a number: ");
    scanf("%d", &n);

    for (i = 2; i < n; ++i) 
    {
	    // situation for if it is prime or not
	    if (n % i == 0)
	    {
		m = 1;
		break;
	    }
    }

    if (n == 1) 
    {
        printf("1 is not a prime number");
    }
    else 
    {
	    if (m == 0)
	    {
            	printf("%d is a prime number.", n);
            }
            else
	    {
        	printf("%d is not a prime number.", n);
	    }
    }
	return 0;
}
