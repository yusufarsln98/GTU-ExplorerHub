#include <stdio.h>

/* C program to draw a perpendicular triangle with *. Yusuf Arslan_200104004112 */

int main() {
	
	int i, j, n;
	char c='*';
	printf ("Enter number of rows for perpendicular triangle shape: ");
	scanf ("%d",&n);
	
	for (i=1; i<=n; i++)
	{
		for (j=1; j<=i; j++)
		{
			printf ("%c",c);
		}
		printf ("\n");
	}
	return 0;
}
