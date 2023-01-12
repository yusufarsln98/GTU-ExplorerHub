#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Yusuf Arslan Lab08_200104004112, 2D Array

int main() 
{
	srand(time(NULL));
	int A[10][10];
	int B[10];
	int i,j,sum = 0;
	
	for(i=0; i<10;i++)
	{
		for( j=0; j<10;j++)
		{
      		A[i][j] = rand()% 80 + 20; 
      	}
    
  	}
  	
	for(i = 0; i<10; i++)
	{
		for(j = 0; j<10;j++)
		{
			printf("%d \t",A[i][j]);
	    }
		printf("\n");
  	}
		for(j=0;j<10;j++)
	  	{
	  		for(i=0;i<10;i++)
			{
				sum = sum+ A[i][j];
		    }
		    
			B[j] = sum;
	   		sum = 0;
  		}
  
	printf ("\n");
	
	for(i=0;i<10;i++)
	{
		printf("%d\t",B[i]);
	}
	return 0;
}
