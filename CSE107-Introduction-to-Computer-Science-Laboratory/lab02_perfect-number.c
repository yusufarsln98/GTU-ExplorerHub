#include <stdio.h>

/* yusuf arslan lab06_3 */

int main() {
	
	int i, n, mod, sum = 0;
 
    printf("Enter a Number: ");
    scanf("%d", &n);
    
    printf ("\n");
    printf ("------------------------\n\n");
    
    for (i = 1; i < n; i++)
    {
		mod = n % i;
        
		if (mod == 0)
        {
            sum = sum + i;
        }
	}
    if (sum == n)
        printf("%d is a perfect number.",n);
    else
        printf("%d is not a perfect number.",n);
	
	return 0;
}
