/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"


/* ====================== PART 1 ======================== */

/*
This function opens the file and sends pointers to the recursive delete_words function to read file line by line.
*/
void clean_file(char *infile, char *outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE *infid, *outfid;
	infid = fopen(infile, "r+");
	outfid = fopen(outfile, "w+");
	if (infid == NULL || outfid == NULL)
	{
		printf("File cannot be open\n");
		exit(1);
	}
	delete_words(infid, outfid, words_to_delete, number_of_words);
	fclose(infid);
	fclose(outfid);
}

/* Reads lines one by one and send them other recursive function make implementations. */
void delete_words(FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE], int number_of_words)
{
	char buffer[1025] = "\0";
	char fixed_buffer[1025] = "\0";
	if (fgets(buffer, 1024, infid) == 0)
	{
		return;
	}
	else
	{
		fix_buffer(buffer, fixed_buffer, words_to_delete, number_of_words);
		fputs(fixed_buffer, outfid);
		delete_words(infid, outfid, words_to_delete, number_of_words);
	}
}
/* Checks every line with the words in the list and remove the necesary words from lines. 
WARNING!
for example: line is "apples apple"
if we are requested to remove "apple" in the list, it will compare apples with apple once,
then since it is not exactly same word, it will pass the other words.
Therefore, "apples apple" stay same but, "apple apples" --> changes " apples"
!!
*/
void fix_buffer(char *buffer, char *fixed_buffer, char* words_to_delete[WORDSIZE], int number_of_words)
{
	int word_length, flag;
	word_length = 0;
	/* Checks every word in the list one by one, if it is finish returns. */
	if (number_of_words == 0)
	{
		return;
	}
	else
	{
		word_length = find_length(*(words_to_delete), word_length); 	/* Finds length of string recursively */
		flag = is_subset(buffer, *(words_to_delete), 0);				/* Finds where string starts to be subset */
		
		clean_buffer(buffer, fixed_buffer, flag, word_length, 0, 0);	/* Remove the words. */
		make_free(buffer);												/* Fill buffer with null's to prevent any unexpected situations. */
		string_copy(buffer, fixed_buffer);								/* Recursively copies strings */
		fix_buffer(buffer, fixed_buffer, words_to_delete + 1, number_of_words - 1);	/* Recursion part. */
	}
}

/* Checks if the line contain exactly the word we want to remove */
int is_subset(char *str, char *substr, int flag)
{
	if (str[0] == '\0')
    {
        return 0;
    }
    else
    {
		/* If it find the word as a subset, then returns the index. */
        if (compare_strings(str, substr))
        {
            return flag;
        }
        else
        {
            is_subset(str + 1, substr, flag + 1);
        }
    }
}
/* Compare strings char by char recursively */
int compare_strings(char *str, char *substr)
{
    if (*substr == '\0')
    {
        return 1;
    }
    else
    {
        if (*str != *substr)
        {
            return 0;
        }
        else
        {
            compare_strings(str + 1, substr + 1);
        }
    }
}
/* 
Main part of the implementation.
It takes 4 primary:
length: length of the word we want to remove
flag: index which buffer starts to be superset of words_to_delete
buffer: original line
fixed_buffer: removed words inside of buffer

Function copies chars from buffer to fixed buffer unless if there is word should remove.

*/
void clean_buffer(char *buffer, char *fixed_buffer, int flag, int word_length, int index, int check)
{
	/* First 2 condition for the prevent remove ie: "apples" when word is "apple" or "kart" when word is "art" */
	if ((check == 0 && (buffer[flag - 1] >= 'a' && buffer[flag - 1] <= 'z')) || (check == 0 && (buffer[flag - 1] >= 'A' && buffer[flag - 1] <= 'Z')))
	{
		printf("%s\n", &buffer[flag - 1]);
		string_copy(fixed_buffer, buffer);
		return;
	}
	else if ((check == 0 && (buffer[flag + word_length] >= 'a' && buffer[flag + word_length] <= 'z')) || 
	         (check == 0 && (buffer[flag + word_length] >= 'A' && buffer[flag + word_length] <= 'Z')))
	{
		string_copy(fixed_buffer, buffer);
		return;
	}
	/* Main recursive part to implementations. */
	else if (buffer[index] == '\0')
	{
		fixed_buffer[0] = '\0';
		return;
	}
	else
	{
		if (index >= flag && index <= (flag + word_length))
		{
			clean_buffer(buffer, fixed_buffer, flag, word_length, index + 1, check + 1);
		}
		else
		{
			fixed_buffer[0] = buffer[index];
			clean_buffer(buffer, fixed_buffer + 1, flag, word_length, index + 1, check + 1);
		}
	}
}
/* Helper recursive functions. */
void string_copy(char *buffer, char *fixed_buffer)
{
	if (fixed_buffer[0] == '\0')
	{
		buffer[0] = '\0';
	}
	else
	{
		buffer[0] = fixed_buffer[0];
		string_copy(buffer + 1, fixed_buffer + 1);
	}
}
void make_free(char *str)
{
	if (str[0] == '\0')
	{
		return;
	}
	else
	{
		str[0] = '\0';
		make_free(str + 1);
	}
}
int find_length(char *str, int len)
{
    if (*str == '\0')
    {
        return len;
    }
    else
    {
        len++;
        find_length(str + 1, len);
    }
}

/* ====================== END OF THE PART 1 ======================== */



/* ====================== PART 2 ======================== */

/* Recursively iterates game. */
void iterate_game(cell_type maze[][8], cell_type player, move_type move, int start)
{
    int check_maze;
	/* Print the maze. */
	display(maze, 0);

	/* Depend on start condition plays game in order */
    if (start % 2 == 1)
    {
		player = cell_ply1;
		printf("\n1. Player");
		printf("\nEnter the direction you want to go:\n(Left: 1, Right: 2, Up: 3, Down: 4)  \n");
		scanf("%uud\n", &move);

		/* Check if movement is possible. */
        check_maze = maze_move(maze, player, move);
        if (check_maze == 0)
        {
            printf("\n!! You cannot move this direction!\nYou lost your turn.\n\n");
        }
        else if (check_maze == -1)
        {
            printf("\nMovement is successful!\n");
        }
        else if (check_maze == 1)
        {
	        display(maze, 0);
            printf("\n\n1. player has won!\n\n");
            return;
        }
        start++;
		/* Recursive part */
        iterate_game(maze, player, move, start);
    }
    else
    {
		player = cell_ply2;
		printf("\n2. Player");
		printf("\nEnter the direction you want to go:\n(Left: 1, Right: 2, Up: 3, Down: 4)  \n");
		scanf("%uud\n", &move);

		/* Check if movement is possible. */
        check_maze = maze_move(maze, player, move);
        if (check_maze == 0)
        {
            printf("\n!! You cannot move this direction!\nYou lost your turn.\n\n");
        }
        else if (check_maze == -1)
        {
            printf("\nMovement is successful!\n");
        }
        else if (check_maze == 1)
        {
	        display(maze, 0);
            printf("\n\n2. player has won!\n\n");
            return;
        }
        start++;
		/* Recursive part */
        iterate_game(maze, player, move, start);
    }
}

/*  
Checks the move then return logical values according to the possibility of the movement.
first checks the direction, 

if there is wall, returns 0 and warns the players.

If user reach the target, returns 1 and declare winner.

If the path is empty, then moves the player and return -1

*/
int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
	int x, y;
    x = 0;
    y = 0;
	find_current(maze, player, &x, &y);
	switch (move)
	{
	case move_left:
		if (maze[x][y - 1] == cell_trgt)
		{
			maze[x][y - 1] = player;
            maze[x][y] = cell_free;
            return 1;
		}
		else if (maze[x][y - 1] == cell_free)
		{
			maze[x][y - 1] = player;
            maze[x][y] = cell_free;
            return -1; 
		} 
		else
		{
            return 0;
		}
		break;

	case move_right:
		if (maze[x][y + 1] == cell_trgt)
		{
			maze[x][y + 1] = player;
            maze[x][y] = cell_free;
            return 1;
		}
		else if (maze[x][y + 1] == cell_free)
		{
			maze[x][y + 1] = player;
            maze[x][y] = cell_free;
            return -1; 
		} 
		else
		{
            return 0;
		}
		break;

	case move_up:
		if (maze[x - 1][y] == cell_trgt)
		{
			maze[x - 1][y] = player;
            maze[x][y] = cell_free;
            return 1;
		}
		else if (maze[x - 1][y] == cell_free)
		{
			maze[x - 1][y] = player;
            maze[x][y] = cell_free;
            return -1; 
		} 
		else
		{
            return 0;
		}
		break;

	case move_down:
		if (maze[x + 1][y] == cell_trgt)
		{
			maze[x + 1][y] = player;
            maze[x][y] = cell_free;
            return 1;
		}
		else if (maze[x + 1][y] == cell_free)
		{
			maze[x + 1][y] = player;
            maze[x][y] = cell_free;
            return -1; 
		} 
		else
		{
            return 0;
		}
		break;
	}
}

/* Finds the current location of players recursively. */
void find_current(cell_type maze[][8], cell_type player, int *x, int *y)
{
    if (maze[*x][*y] == player)
    {
        return;
    }
    else
    {
        if (*y == 7)
        {
            (*x)++;
            *y = -1;
        }
        (*y)++;
        find_current(maze, player, x, y);
    }
}
/* Display the maze recursively */
void display(cell_type maze[][N], int i)
{
    if (i == N * N)
    {
        return;
    }
    else
    {
        if (maze[0][i] == cell_wall)
        {
            printf("# ");
        }
        else if (maze[0][i] == cell_trgt)
        {
            printf("P ");
        }
        else if (maze[0][i] == cell_free)
        {
            printf("  ");
        }
        else if (maze[0][i] == cell_ply1)
        {
            printf("1 ");
        }
        else if (maze[0][i] == cell_ply2)
        {
            printf("2 ");
        }
        i++;
        if (i % 8 == 0)
        {
            printf("\n");
        }
        display(maze, i);
    }
}

/* ====================== PART 3 ======================== */
/* It takes 3 argument as specify the movement of disks */
void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int disk_number)
{
    int i;

	/* Keeps the disks for each iteration. */
    int str_arr[7];
    int end_arr[7];
    int aux_arr[7];

	/* Initially starts the first array. */
    for (i = 0; i < disk_number; i++)
    {
        str_arr[i] = i + 1;
        end_arr[i] = 0;
        aux_arr[i] = 0;
    }

	/* Display the tower. */
    display_tower(str_arr, end_arr, aux_arr, disk_number);

	/* Sends parameters to a recursive function. */
    recursive_hanoi(start_peg, end_peg, aux_peg, disk_number, str_arr, end_arr, aux_arr, disk_number);

	/* Print basement for last tower */
    for (i = 0; i < (6 * disk_number + 27); i++) printf("-");
    printf("\n\n");
}

/* tower of hanoi algorithm */
void recursive_hanoi(char start_peg, char end_peg, char aux_peg, int n, int str_arr[], int end_arr[], int aux_arr[], int disk_number)
{
    if (n == 1)
    {
		/* Replace last disk from S or A to E */
        replace_disks(start_peg, end_peg, n, str_arr, end_arr, aux_arr, disk_number);

		/* Display the tower. */
        display_tower(str_arr, end_arr, aux_arr, disk_number);
    }
    else
    {
		/* 1st Recursive part */
        recursive_hanoi(start_peg, aux_peg, end_peg, (n - 1), str_arr, end_arr, aux_arr, disk_number);

		/* Replace disks in appropriate conditions. then display the towers */
        replace_disks(start_peg, end_peg, n, str_arr, end_arr, aux_arr, disk_number);
        display_tower(str_arr, end_arr, aux_arr, disk_number);

		/* 1st Recursive part */
        recursive_hanoi(aux_peg, end_peg, start_peg, (n - 1), str_arr, end_arr, aux_arr, disk_number);
    }
}

/* According to the tower of hanoi algorithm it replace disks in arrays. */
void replace_disks(char from_peg, char dest_peg, int n, int str_arr[], int end_arr[], int aux_arr[], int BORDER)
{
    int temp, index;

	/* if from S to E, then replace disk from start array to end array. 
	   Same for other conditions. */
    if (from_peg == 'S' && dest_peg == 'E')
    {
        index = find_num(str_arr, n, BORDER);
        end_arr[0] = str_arr[index];
        str_arr[index] = 0;
    }
    else if (from_peg == 'S' && dest_peg == 'A')
    {
        index = find_num(str_arr, n, BORDER);
        aux_arr[0] = str_arr[index];
        str_arr[index] = 0;
    }
    else if (from_peg == 'A' && dest_peg == 'S')
    {
        index = find_num(aux_arr, n, BORDER);
        str_arr[0] = aux_arr[index];
        aux_arr[index] = 0;
    }
    else if (from_peg == 'A' && dest_peg == 'E')
    {
        index = find_num(aux_arr, n, BORDER);
        end_arr[0] = aux_arr[index];
        aux_arr[index] = 0;       
    }    
    else if (from_peg == 'E' && dest_peg == 'S')
    {
        index = find_num(end_arr, n, BORDER);
        str_arr[0] = end_arr[index];
        end_arr[index] = 0;
    }
    else if (from_peg == 'E' && dest_peg == 'A')
    {
        index = find_num(end_arr, n, BORDER);
        aux_arr[0] = end_arr[index];
        end_arr[index] = 0;
    }
	/* Finally sorts the array from 0 to BORDER to make arrays printble. */
    sort_array(str_arr, BORDER); 
    sort_array(aux_arr, BORDER); 
    sort_array(end_arr, BORDER); 
}
/* Recursive sorting algorithm. */
void sort_array(int array[], int n)
{
    if (n > 1)
    {
        place_largest(array, n);
        sort_array(array, n - 1);
    }
}
/* Finds largest element and put it to the last address */
void place_largest(int array[], int n)
{
    int largest, index, temp;
	int i;

    largest = array[0];
    index = 0;

    for (i = 1; i < n; i++)
    {
        if (array[i] > largest)
        {
            largest = array[i];
            index = i;
        }
    }
    temp = array[n - 1];
    array[index] = temp;
    array[n - 1] = largest;
}
/* Finds the index of disk which going to be replace */
int find_num(int array[], int n, int BORDER)
{
    int i;
    for (i = 0; i < BORDER; i++)
    {
        if (array[i] != 0)
        {
            return i;
        }
    }
}

/* DISPLAY THE TOWER */
/* 

Instead of the tell about codes, I will show the math:

  ---------------------------------------------------------------------
  =                               STEP 1                              =
  ---------------------------------------------------------------------
             S                      A                      E
                                                                           
           *****                  *****                  *****             
           * 1 *                  * 1 *                  * 1 *             
          *******                *******                *******            
          *  2  *                *  2  *                *  2  *            
         *********              *********              *********           
         *   3   *              *   3   *              *   3   *           
        ***********            ***********            ***********          
        *    4    *            *    4    *            *    4    *          
       *************          *************          *************         
       *     5     *          *     5     *          *     5     *         
      ***************        ***************        ***************    
      *      6      *        *      6      *        *      6      *        
     *****************      *****************      *****************       
     *       7       *      *       7       *      *       7       *       
     *****************      *****************      *****************  

  <-----------------        (6 * BORDER + 27)   	----------------->
	    FIRST TOWER			  SECOND TOWER            THIRD TOWER

  |	THERE IS 3 PART:    |	THERE IS 3 PART:	| 	THERE IS 3 PART:   |
  | 1st: left blanks.	|	1st: left blanks.	|	1st: left blanks.  |		                                     
  |	2nd: Starts & nums. |	2nd: Starts & nums.	|	2nd: Starts & nums.|                                    
  |	3rd: right blanks   |	3rd: right blanks 	|	3rd: right blanks  |	                                      	
  |	Each part has:		|	Each part has:		|  	Each part has:	   |                                  
  | 2 * n + 9 digit.    |   2 * n + 9 digit.	|	2 * n + 9 digit.   |

  Each part divided according to the stars.
  For example:
  
  If the number is 1, (n = 2 * "1" + 3);
  It has 2 * n(5) + 9 digit for total.
  There is (2 * 5 + 9 - 5) / 2 blank for each side of tower and 5 digit for the star.

*/


void display_tower(int str_arr[], int end_arr[], int aux_arr[], int BORDER)
{
    static int step;
    int i, j, k, l, m;
    k = 0;
    l = 0;
    m = BORDER - 1;

    step++;  
    print_header(BORDER, step);

    for (i = 0; i < (2 * BORDER + 1); i++)
    {
        if (i == (2 * BORDER))
        {
            if (str_arr[m] == 0 && aux_arr[m] == 0 && end_arr[m] == 0)
                for (j = 0; j < (6 * BORDER + 27); j++) printf(" ");
            else if (str_arr[m] == 0 && aux_arr[m] == 0 && end_arr[m] != 0)
            {
                for (j = 0; j < 2 * (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[m] + 3); j++) printf("*");
            }
            else if (str_arr[m] == 0 && aux_arr[m] != 0 && end_arr[m] == 0)
            {
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[m] + 3); j++) printf("*");
            }
            else if (str_arr[m] != 0 && aux_arr[m] == 0 && end_arr[m] == 0)
            {                
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[m] + 3); j++) printf("*");
            }
            else if (str_arr[m] == 0 && aux_arr[m] != 0 && end_arr[m] != 0)
            {
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[m] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[m] + 3); j++) printf("*");
            }
            else if (str_arr[m] != 0 && aux_arr[m] == 0 && end_arr[m] != 0)
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[m] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[m] + 3); j++) printf("*");
            }
            else if (str_arr[m] != 0 && aux_arr[m] != 0 && end_arr[m] == 0)
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[m] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[m] + 3); j++) printf("*");
            }
            else
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[m] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[m] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[m] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[m] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[m] + 3)) / 2); j++) printf(" ");
            }
        }       
        else if (i % 2 == 0)
        {
            if (str_arr[k] == 0 && aux_arr[k] == 0 && end_arr[k] == 0)
                for (j = 0; j < (6 * BORDER + 27); j++) printf(" ");
            else if (str_arr[k] == 0 && aux_arr[k] == 0 && end_arr[k] != 0)
            {
                for (j = 0; j < 2 * (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[k] + 3); j++) printf("*");
            }
            else if (str_arr[k] == 0 && aux_arr[k] != 0 && end_arr[k] == 0)
            {
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[k] + 3); j++) printf("*");
            }
            else if (str_arr[k] != 0 && aux_arr[k] == 0 && end_arr[k] == 0)
            {                
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[k] + 3); j++) printf("*");
            }
            else if (str_arr[k] == 0 && aux_arr[k] != 0 && end_arr[k] != 0)
            {
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[k] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[k] + 3); j++) printf("*");
            }
            else if (str_arr[k] != 0 && aux_arr[k] == 0 && end_arr[k] != 0)
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[k] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[k] + 3); j++) printf("*");
            }
            else if (str_arr[k] != 0 && aux_arr[k] != 0 && end_arr[k] == 0)
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[k] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[k] + 3); j++) printf("*");
            }
            else
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[k] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[k] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[k] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[k] + 3); j++) printf("*");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[k] + 3)) / 2); j++) printf(" ");
            }
            k++;
        }
        else
        {
            if (str_arr[l] == 0 && aux_arr[l] == 0 && end_arr[l] == 0)
                for (j = 0; j < (6 * BORDER + 27); j++) printf(" ");
            else if (str_arr[l] == 0 && aux_arr[l] == 0 && end_arr[l] != 0)
            {
                for (j = 0; j < 2 * (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * end_arr[l] + 2)) printf("*");
                    else if (j == ((2 * end_arr[l] + 2) / 2)) printf("%d", end_arr[l]);
                    else printf(" ");
                }
            }
            else if (str_arr[l] == 0 && aux_arr[l] != 0 && end_arr[l] == 0)
            {
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * aux_arr[l] + 2)) printf("*");
                    else if (j == ((2 * aux_arr[l] + 2) / 2)) printf("%d", aux_arr[l]);
                    else printf(" ");
                }
            }
            else if (str_arr[l] != 0 && aux_arr[l] == 0 && end_arr[l] == 0)
            {                
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                    
                for (j = 0; j < (2 * str_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * str_arr[l] + 2)) printf("*");
                    else if (j == ((2 * str_arr[l] + 2) / 2)) printf("%d", str_arr[l]);
                    else printf(" ");
                }
            }
            else if (str_arr[l] == 0 && aux_arr[l] != 0 && end_arr[l] != 0)
            {
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * aux_arr[l] + 2)) printf("*");
                    else if (j == ((2 * aux_arr[l] + 2) / 2)) printf("%d", aux_arr[l]);
                    else printf(" ");
                } 
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * end_arr[l] + 2)) printf("*");
                    else if (j == ((2 * end_arr[l] + 2) / 2)) printf("%d", end_arr[l]);
                    else printf(" ");
                }
            }
            else if (str_arr[l] != 0 && aux_arr[l] == 0 && end_arr[l] != 0)
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                    
                for (j = 0; j < (2 * str_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * str_arr[l] + 2)) printf("*");
                        
                    else if (j == ((2 * str_arr[l] + 2) / 2)) printf("%d", str_arr[l]);
                        
                    else printf(" ");
                        
                }
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * BORDER + 9); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * end_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * end_arr[l] + 2)) printf("*");
                    else if (j == ((2 * end_arr[l] + 2) / 2)) printf("%d", end_arr[l]);
                    else printf(" ");
                }
            }
            else if (str_arr[l] != 0 && aux_arr[l] != 0 && end_arr[l] == 0)
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * str_arr[l] + 2)) printf("*");
                    else if (j == ((2 * str_arr[l] + 2) / 2)) printf("%d", str_arr[l]);
                    else printf(" ");
                } 
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * aux_arr[l] + 2)) printf("*");
                    else if (j == ((2 * aux_arr[l] + 2) / 2)) printf("%d", aux_arr[l]);
                    else printf(" ");
                }  
            }
            else
            {
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * str_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * str_arr[l] + 2)) printf("*");
                    else if (j == ((2 * str_arr[l] + 2) / 2)) printf("%d", str_arr[l]);
                    else printf(" ");
                } 
                for (j = 0; j < (((2 * BORDER + 9) - (2 * str_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[l] + 3)) / 2); j++) printf(" ");
                for (j = 0; j < (2 * aux_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * aux_arr[l] + 2)) printf("*");
                    else if (j == ((2 * aux_arr[l] + 2) / 2)) printf("%d", aux_arr[l]);
                    else printf(" ");
                }  
                for (j = 0; j < (((2 * BORDER + 9) - (2 * aux_arr[l] + 3)) / 2); j++) printf(" ");
                    
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[l] + 3)) / 2); j++) printf(" ");
                   
                for (j = 0; j < (2 * end_arr[l] + 3); j++)
                {
                    if (j == 0 || j == (2 * end_arr[l] + 2)) printf("*");
                    else if (j == ((2 * end_arr[l] + 2) / 2)) printf("%d", end_arr[l]);
                    else printf(" ");
                } 
                for (j = 0; j < (((2 * BORDER + 9) - (2 * end_arr[l] + 3)) / 2); j++) printf(" ");
            }
            l++;
        }
        printf("\n");
    }
    
}

void print_header(int BORDER, int step)
{
    int i;
    
    for (i = 0; i < (6 * BORDER + 27); i++) printf("-");
    printf("\n=");
    for (i = 0; i < (3 * BORDER + 10); i++) printf(" ");
    printf("STEP %d", step);
    for (i = 0; i < (3 * BORDER + 9); i++) printf(" ");
    printf("=\n");
    for (i = 0; i < (6 * BORDER + 27); i++) printf("-");
    printf("\n");
    for (i = 0; i < ((((6 * BORDER + 27) / 3) - 1) / 2); i++) printf(" ");
    printf("S");
    for (i = 0; i < ((((6 * BORDER + 27) / 3) - 1)); i++) printf(" ");
    printf("A");
    for (i = 0; i < ((((6 * BORDER + 27) / 3) - 1)); i++) printf(" ");
    printf("E");
    printf("\n\n\n\n\n");
}
