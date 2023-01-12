/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

/* Initialization part and declerations. */

/* 
WARNING!
number_of_words correspond the number of the words in *words_to_delete[]
*/

void test_clean_file(void) 
{
	char infile[15], outfile[15];
	int number_of_words;

	char *words_to_delete[WORDSIZE] = {"word1", "word2"};
	number_of_words = 2;

	strcpy(infile, "infile.txt");
	strcpy(outfile, "outfile.txt");
	printf("\n\nPlease enter any char to start reading file...\n");
	getchar();
    clean_file(infile, outfile, words_to_delete, number_of_words);
}


void test_maze_move ()
{
	int i, j;
	int check_maze;
	cell_type player;
	move_type move; 
	cell_type maze[N][N] = 
	{
		{cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall}, 
		{cell_wall, cell_trgt, cell_free, cell_free, cell_free, cell_free, cell_free, cell_wall}, 
		{cell_wall, cell_free, cell_wall, cell_wall, cell_wall, cell_wall, cell_free, cell_wall}, 
		{cell_wall, cell_free, cell_wall, cell_wall, cell_ply2, cell_wall, cell_free, cell_wall}, 
		{cell_wall, cell_free, cell_wall, cell_free, cell_free, cell_wall, cell_free, cell_wall}, 
		{cell_wall, cell_free, cell_wall, cell_free, cell_wall, cell_wall, cell_free, cell_wall}, 
		{cell_wall, cell_free, cell_free, cell_free, cell_wall, cell_ply1, cell_free, cell_wall}, 
		{cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall}
	};
	printf("\n****   MAZE GAME   ****\n");

	/* Start game. */
    printf("\nEnter priority for first or second player. (1 or 2):  ");
    scanf("%u", &player);
    printf("\n\n");
    iterate_game(maze, player, move, player);
}


void test_towers_of_hanoi(void)
{
	char start_peg, end_peg, aux_peg;
    int disk_number;
    printf("\n\n********** TOWER OF HANOI **********\n\n");
    start_peg = 'S';
    end_peg = 'E';
    aux_peg = 'A';
    printf("\nEnter number of disks:  ");
    scanf("%d", &disk_number);
    towers_of_hanoi(start_peg, end_peg, aux_peg, disk_number);
}

/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
