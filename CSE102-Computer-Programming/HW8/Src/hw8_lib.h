/*
** hw8_lib.h:
**
** The header file declaring library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/
#include <string.h>
#include <stdlib.h>

/* DEFINATIONS */
#define WORDSIZE 30

#define N 8

typedef enum { 
    cell_wall, cell_free, cell_trgt, cell_ply1, cell_ply2
}cell_type;

typedef enum { 
    move_left = 1, move_right = 2, move_up = 3, move_down = 4
}move_type;

/* ====================== PART 1 ======================== */

void clean_file(char *infile, char *outfile, char* words_to_delete[WORDSIZE], int number_of_words);
void delete_words(FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE], int number_of_words);
void fix_buffer(char *buffer, char *fixed_buffer, char* words_to_delete[WORDSIZE], int number_of_words);
int compare_strings(char *str, char *substr);
int is_subset(char *str, char *substr, int flag);
int find_length(char *str, int len);
void clean_buffer(char *buffer, char *fixed_buffer, int flag, int word_length, int index, int check);
void make_free(char *str);
void string_copy(char *buffer, char *fixed_buffer);

/* ====================== PART 2 ======================== */

int maze_move(cell_type maze[][8], cell_type player, move_type move);
void display(cell_type maze[][N], int i);
void find_current(cell_type maze[][8], cell_type player, int *x, int *y);
void iterate_game(cell_type maze[][8], cell_type player, move_type move, int start);

/* ====================== PART 3 ======================== */
void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int disk_number);
void recursive_hanoi(char start_peg, char end_peg, char aux_peg, int n, int str_arr[], int end_arr[], int aux_arr[], int disk_number);
void sort_array(int array[], int n);
void place_largest(int array[], int n);
int find_num(int array[], int n, int BORDER);
void display_tower(int str_arr[], int end_arr[], int aux_arr[], int BORDER);
void print_header(int BORDER, int step);
void replace_disks(char from_peg, char dest_peg, int n, int str_arr[], int end_arr[], int aux_arr[], int BORDER);
