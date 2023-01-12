#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define filename "game.txt"

#define N 4


struct game
{
	char name[20];
	char platforms[20][20];
	int platformCounter;
};

void write(struct game array[], char platform[]);


int main() 
{
	struct game games[N];
	int i, j;
	
	for (i = 0; i < N; i++)
	{
		int counter = 0;
		char control[20];
		
		printf("%d. Game\n", i + 1);
		printf ("Name: ");
		fflush(stdin);
		scanf(" %[^\n]", &games[i].name);
		
		printf ("Platforms (enter '0' to stop)\n");
		
		while (1)
		{
			scanf ("%s", &control);
			if (strcmp(control, "0") != 0)
			{
				strcpy(games[i].platforms[counter], control);
				counter++;
				games[i].platformCounter = counter;
			}
			else 
			{
				break;
			}	
		}
		
	}
	
	char platform[20];
	printf("Which platform's game do you want to write?\n");
	scanf("%s", &platform);
	
	write(games, platform);
	
						
	return 0;
}

void write(struct game array[], char platform[])
{
	FILE *fptr;
	fptr = fopen(filename, "w"); //filename (test.txt)'i "w"-write mode'da bir şeyler yazmak için aç.
	
	if (fptr == NULL) 
	{
		printf("Couldn't create text file.");
		exit(1);
	}
	
	fprintf(fptr, "%s games:\n\n", platform);
	
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < array[i].platformCounter; j++)
		{
			if (strcmp(platform, array[i].platforms[j]) == 0)
			{
				fprintf(fptr, "%s\n", array[i].name);
			}
		}
	}
	
	printf (".txt file has been written");
		
}


