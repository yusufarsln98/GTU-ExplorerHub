#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE -1

/* Create a enum type for sub-operator */
typedef enum {budget = 1, genre = 2, name = 3, score = 4, year = 5} opt_t;

/* Create 2 linked list to keep one movies informations */
typedef struct Movie_Budget
{
    int budget;
    int year;
    char *name;
    struct Movie_Budget *mbp;
} Movie_Budget;

typedef struct Movie_Name
{
    double score;
    char *genre;
    char *name;
    struct Movie_Name *mnp;
} Movie_Name;

/* Creating a Movie struct to keep component of the line temporarily */
typedef struct Movie
{
    char *budget;
    char *genre;
    char *name;
    char *score;
    char *year;
} Movie;

/* ============= HEADERS FOR READING AND CONSTRUCTING LISTS ============= */
void read_file(char *infile, Movie_Budget **Mb_ref, Movie_Name **Mn_ref, int *num_of_movies);
char *get_line(FILE *fp, int *flag);
void decompose_line(Movie *m, char *line);
Movie_Budget *create_Movie_Budget(Movie new_movie);
Movie_Name *create_Movie_Name(Movie new_movie);
int is_movie_exist(char *str, Movie_Name *Mn_head);
Movie_Budget *find_location(Movie_Budget *node, Movie_Budget *Mb_head);
Movie_Budget *find_exist_movie(char *str, Movie_Budget *Mb_head);
Movie_Name *find_place_movie(char *str, Movie_Name *Mn_head);
void insert_node(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, Movie_Budget *mb_node, Movie_Name *mn_node);
void remove_node(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, Movie new_movie);
int find_unknown_number(Movie_Budget *Mb_head);

/* ============= HEADERS FOR MENU ============= */
void menu(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, char **genre_list, int genre_num, int num_of_movies);
char **list_genre(Movie_Name *Mn_head, int *genre_num);
int is_genre_exist(char *str, char **genre_list, int genre_num);
char *get_string(void);
int is_valid_operator(char *operator);
void do_operations(int operator, Movie_Budget **Mb_ref, Movie_Name **Mn_ref, char **genre_list, int genre_num, int num_of_movies);
Movie_Budget *sortB_by_pointers(Movie_Budget *Mb_head, opt_t subOpr);
Movie_Budget *findB_location(Movie_Budget *head, Movie_Budget *node);
Movie_Budget *findB_largest(Movie_Budget *head, opt_t subOpr);
void insertB_head(Movie_Budget **head_ref, Movie_Budget *node);
Movie_Name *sortN_by_pointers(Movie_Name *Mn_head, opt_t subOpr);
Movie_Name *findN_largest(Movie_Name *head, opt_t subOpr);
Movie_Name *findN_location(Movie_Name *head, Movie_Name *node);
void insertN_head(Movie_Name **head_ref, Movie_Name *node);
void do_sorted_data(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, int num_of_movies, opt_t subOpr);
void do_through_year(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, opt_t subOpr);
void do_through_score(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, opt_t subOpr);
void print_list_of_genre(char **genre_list, int genre_num);
int find_beginning_year(Movie_Budget *Mb_head);
int find_finishing_year(Movie_Budget *Mb_head);
void print_through_year(Movie_Budget *Mb_head, Movie_Name *Mn_head, int start_year, int end_year);
double find_min_score(Movie_Name *Mn_head);
double find_max_score(Movie_Name *Mn_head);
void print_through_score(Movie_Budget *Mb_head, Movie_Name *Mn_head, double min_score, double max_score);
Movie_Budget *find_one_movie(Movie_Budget *Mb_head, char *str);
Movie_Budget *findB_node(Movie_Budget *Mb_head, int n);
Movie_Name *findN_node(Movie_Name *Mn_head, int n);
Movie_Name *findN_pair(Movie_Name *Mn_head, char *name);
Movie_Budget *findB_pair(Movie_Budget *Mb_head, char *name);
int min_budget(Movie_Budget *Mb_head);
int max_budget(Movie_Budget *Mb_head);
void print_budget(Movie_Budget *Mb_head, Movie_Name *Mn_head, int r1, int r2);
void print_year(Movie_Budget *Mb_head, Movie_Name *Mn_head, int r1, int r2);
void print_score(Movie_Budget *Mb_head, Movie_Name *Mn_head, double r1, double r2);
void print_imdb_average(Movie_Name *Mn_head, int num_of_movies);
void frequence_of_genres(Movie_Name *Mn_head, char **genre_list, int genre_num);
void free_Mn(Movie_Name *head);
void free_Mb(Movie_Budget *head);

/* ======================================================== */
/* ========================= MENU ========================= */
int main(void)
{
    Movie_Budget *Movies_b = NULL;      /* Create head pointer to each linked list */
    Movie_Name *Movies_n = NULL;        /* Create head pointer to each linked list */  
    int num_of_movies = 0;              /* Number of the movies */
    char **genre_list = NULL;           /* 2d char array to keep genre names */
    int genre_num = 0;                  /* Number of the genres in the genre_list */

    char *infile = "Movies.txt";        /* File name to read and work on it */

    /* ----- Call the functions ----- */
    read_file(infile, &Movies_b, &Movies_n, &num_of_movies);            /* Read file and return lists heads and movie number by pointers */
    genre_list = list_genre(Movies_n, &genre_num);                      /* Create string array to keep genre informations */
    menu(&Movies_b, &Movies_n, genre_list, genre_num, num_of_movies);   /* Calling the menu */

    free(genre_list);                   /* Free the pointer (strings in the array will be freed by following functions) */
    free_Mb(Movies_b);                  /* Free the Movie_Budget list */
    free_Mn(Movies_n);                  /* Free the Movie_Name list */
    return 0;
}
/* ==================== END OF THE MAIN =================== */


/* =========== READING FILE & CREATE LINKED LISTS =========== */
/* ---------- Reading all movies and creating linked lists ---------- */
void read_file(char *infile, Movie_Budget **Mb_ref, Movie_Name **Mn_ref, int *num_of_movies)
{
    /* Variables */
    FILE *fp;
    char *line;
    int EOFflag = 0,
        controller;

    /* Create a buffer struct for composing the line */
    Movie new_movie;

    /* Nodes */
    Movie_Budget *mb_node;
    Movie_Name *mn_node;

    /* ------ Open the File ------ */
    fp = fopen(infile, "r");
    if (fp == NULL)
    {
        printf("ERROR! File cannot be open.\n\n");
        exit(1);
    }

    line = get_line(fp, &EOFflag);
    free(line);
    /* ------ Reading File line by line ------ */
    while(EOFflag != TRUE)
    {
        line = get_line(fp, &EOFflag);      /* Get line from file and put its address to the char *line */

        if (strlen(line) < 2)               /* If there is not any line end of the file then break the loop  */
        {                                   /* ie:   ....   .....................................            */
            free(line);                     /*       6791   unknown,comedy,straight talk,5.7,1992            */
            break;                          /*       6792                                                    */
        }                                   /*       6793                                                    */

        /* ------ Decomposing line ------ */
        /* A buffer sturct sent as an argument, line will be decomposed and strings going to keep by buffer struct */
        decompose_line(&new_movie, line);

        /* ------ Creating linked list according to the instructions ------ */
        /* is_movie_exist() return TRUE when a movie exist, or FALSE if does not exist */
        controller = is_movie_exist(new_movie.name, (*Mn_ref));

        if (controller == FALSE)            /* -------- IF MOVIE DOES NOT EXIST -------- */
        {
            /* ---- Add new nodes to the lists ---- */
            mb_node = create_Movie_Budget(new_movie);   /* ---- Create nodes ---- */
            mn_node = create_Movie_Name(new_movie);     /* ---- Create nodes ---- */

            insert_node(Mb_ref, Mn_ref, mb_node, mn_node);
            free(new_movie.budget); free(new_movie.score); free(new_movie.year);
            (*num_of_movies)++;
        }
        else if (controller == TRUE)        /* -------- IF MOVIE EXIST -------- */
        {
            /* ---- Remove previous movie to update lists ---- */
            remove_node(Mb_ref, Mn_ref, new_movie);

            /* ---- Add new nodes to the lists ---- */
            mb_node = create_Movie_Budget(new_movie);   /* ---- Create nodes ---- */
            mn_node = create_Movie_Name(new_movie);

            insert_node(Mb_ref, Mn_ref, mb_node, mn_node);
            free(new_movie.budget); free(new_movie.score); free(new_movie.year);
        }
        free(line); /* Make free for memory corrupted for line */
    }
    fclose(fp);     /* Close the file */
}
/* ---------- Remove nodes from lists ---------- */
void remove_node(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, Movie new_movie)
{
    /* Cursors for determine location */
    Movie_Budget *cursor = NULL;
    Movie_Name *place = NULL;

    /* Temporary pointer for make free previous movies */
    Movie_Budget *temp_b;
    Movie_Name *temp_n;

    cursor = find_exist_movie(new_movie.name, *Mb_ref);     /* Find one previous nodes which are going to remove */
    place = find_place_movie(new_movie.name, *Mn_ref);      /* Find one previous nodes which are going to remove */

    /* There is 2 condition for each list
       We know that, a node should be remove --> (from upper function)
       So;
       1- If cursor is NULL (since we are looking for one step forward) it means that node is in the head of the list
       Then change the head and make free previous node.
       2- Else -cursor is not NULL- (for example: 'a' )then change the pointer from a --> b --> c to a --> c then remove b */

    if (cursor == NULL)                 /* If node in the head */
    {
        cursor = (*Mb_ref);             /* Change the head */
        (*Mb_ref) = (*Mb_ref)->mbp;
        free(cursor);                   /* Free previous pointer */
    }
    else                                /* If node not in the head */
    {
        temp_b = cursor->mbp;           /* Then change  a --> b --> c to a --> c */
        cursor->mbp = cursor->mbp->mbp;
        free(temp_b);
    }
    if (place == NULL)                  /* If node in the head */
    {
        place = (*Mn_ref);              /* Change the head */
        (*Mn_ref) = (*Mn_ref)->mnp;
        free(place->genre);             /* Free previous pointer and strings */
        free(place->name);
        free(place);
    }
    else                                /* If node not in the head */
    {
        temp_n = place->mnp;            /* Then change  a --> b --> c to a --> c */
        place->mnp = place->mnp->mnp;
        free(temp_n->genre);            /* Free previous pointer and strings */
        free(temp_n->name);
        free(temp_n);
    }
}
/* ---------- Insert nodes to the lists ---------- */
void insert_node(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, Movie_Budget *mb_node, Movie_Name *mn_node)
{
    Movie_Budget *cursor = NULL;    /* Initiliaze cursor for lists */

    if ((*Mb_ref) == NULL)          /* If lists are empty, then start lists with first nodes */
    {
        (*Mb_ref) = mb_node;
        (*Mn_ref) = mn_node;
    }
    else                            /* If lists are already initiliazed: */
    {
        /* ---- Adding new Movie_Name to the head node without sorting ---- */
        mn_node->mnp = (*Mn_ref);
        (*Mn_ref) = mn_node;

        /* ---- Adding new Movie_Budget node with sorting insertion ---- */
        cursor = find_location(mb_node, (*Mb_ref));

        if (cursor == NULL)                 /* If cursor is NULL (mean: Could not find any appropriate location) */
        {
            mb_node->mbp = (*Mb_ref);       /* Then push new node to the head */
            (*Mb_ref) = mb_node;
        }
        else                                /* Else -if find a suitable location- */
        {
            mb_node->mbp = cursor->mbp;     /* Then interpose the new node */
            cursor->mbp = mb_node;
        }
    }
    /* Make free unnecessary components */
}
/* ---------- Decompose line and keep the parts into a buffer struct ---------- */
void decompose_line(Movie *m, char *line)
{
    int i = 0, FLAG = 1, length = 0; /* Variables */
    char ch = ' ';                          /* Variables */

    /* ------ Controlling entire line ------ */
    /* Check the line until '\0' and if find '\0' or ',' then copy the parts into the structs */
    while (ch != '\0')
    {
        ch = line[i];

        /* Take char from the line, then if ch not equal ',' or '\0' increase length
           If find the keys then create memory for each places and copy tokens into the right Movie struct
           FLAG increase by one in each circle */
        if (ch == ',' || ch == '\0')
        {
            if (FLAG == budget)     /* Copy budget part into the m->budget */
            {
                m->budget = malloc((length + 1) * sizeof(char));
                strncpy(m->budget, &line[i - length], length);
                m->budget[length] = '\0';
            }
            if (FLAG == genre)      /* Copy genre part into the m->genre */
            {
                m->genre = malloc((length + 1) * sizeof(char));
                strncpy(m->genre, &line[i - length], length);
                m->genre[length] = '\0';
            }
            if (FLAG == name)       /* Copy name part into the m->name */
            {
                m->name = malloc((length + 1) * sizeof(char));
                strncpy(m->name, &line[i - length], length);
                m->name[length] = '\0';
            }
            if (FLAG == score)      /* Copy score part into the m->score */
            {
                m->score = malloc((length + 1) * sizeof(char));
                strncpy(m->score, &line[i - length], length);
                m->score[length] = '\0';
            }
            if (FLAG == year)       /* Copy year part into the m->year */
            {
                m->year = malloc((length + 1) * sizeof(char));
                strncpy(m->year, &line[i - length], length);
                m->year[length] = '\0';
            }
            /* To count the length, make it 0 again and increase FLAG by one */
            length = 0;
            FLAG++;
        }
        else
        {
            length++;
        }
        i++;
    }
}
/* ---------- Read line from file ---------- */
char *get_line(FILE *fp, int *flag)
{
    char ch = '\0';               /* Variables */
    int i, counter = 0;

    char *line,             /* Char* for keeping line */
         *temp = NULL;      /* Temp char* for reading file by calloc() */

    /* -------------- Reading file one char at a time  -------------- */

    while (ch != '\n' && ch != '\r' && ch != EOF)                   /* If ch equal to newline or CR or EOF chars then break the loop */
    {
        ch = fgetc(fp);                     /* Read chars from file */
        counter++;                          /* Increase counter in each reading */
        if (ch == EOF)                      /* If find the EOF then give the EOFflag to TRUE */
        {
            *flag = TRUE;
        }
        line = calloc(counter, sizeof(char));                   /* Allocate memory for line */
        for (i = 0; i < counter - 1; i++) line[i] = temp[i];    /* Take previous indexes to the new   */
        line[counter - 1] = ch;                                 /* Put the last char to the tail */

        if (temp != NULL) free(temp);       /* Make free temp memory */
        temp = line;                        /* Change temp with the new line */

    }
    if (line[counter - 1] == '\r') ch = fgetc(fp);
    line[counter - 1] = '\0';

    /* ------------------- End of reading line  ------------------- */

    return line;    /* Return address of the string allocated for line */
}

/* -------------- Helper functions for Reading and Construction Part -------------- */
/* Creating new Movie_Budget node */
Movie_Budget *create_Movie_Budget(Movie new_movie)
{
    Movie_Budget *New_Mb = malloc(sizeof(Movie_Budget));        /* Memory allocation for new node */

    New_Mb->budget = atof(new_movie.budget);                    /* ------------------------------------------------------------  */
    New_Mb->year = atoi(new_movie.year);                        /* Fill new node information coming from buffer new_movie struct */
    New_Mb->name = new_movie.name;                              /* Fill new node information coming from buffer new_movie struct */
    New_Mb->mbp = NULL;                                         /* ------------------------------------------------------------  */

    return New_Mb;                                              /* RETURN new Movie_Budget node */
}
/* Creating new Movie_Name node */
Movie_Name *create_Movie_Name(Movie new_movie)
{
    Movie_Name *New_Mn = malloc(sizeof(Movie_Name));            /* Memory allocation for new node */

    New_Mn->genre = new_movie.genre;                            /* ------------------------------------------------------------  */
    New_Mn->name = new_movie.name;                              /* Fill new node information coming from buffer new_movie struct */
    New_Mn->score = atof(new_movie.score);                      /* Fill new node information coming from buffer new_movie struct */
    New_Mn->mnp = NULL;                                         /* ------------------------------------------------------------  */

    return New_Mn;                                              /* RETURN new Movie_Name node */
}
/* Find if movie exist */
int is_movie_exist(char *str, Movie_Name *Mn_head)
{
    while (Mn_head != NULL)                                     /* Scan entire list */
    {
        if (strcmp(str, Mn_head->name) == 0)                    /* If there is same movie */
        {
            return TRUE;                                        /* Then return TRUE */
        }
        Mn_head = Mn_head->mnp;                                 /* Go one step forward */
    }

    return FALSE;                                               /* If movie cannot found then return FALSE */
}
/* Find location for new Movie_Budget node */
Movie_Budget *find_location(Movie_Budget *node, Movie_Budget *Mb_head)
{
    Movie_Budget *cursor = NULL;                                /* Create a cursor to define location */

    while (Mb_head != NULL)                                     /* Check end of the list */
    {
        /* If new node has smaller year then any node in the list
           or equal year but smaller budget then any node, Then assign to the cursor its location */
        if ((node->year < Mb_head->year) || ((node->year == Mb_head->year) && node->budget < Mb_head->budget))
        {
            cursor = Mb_head;                                   /* Assigning the cursor */
        }
        Mb_head = Mb_head->mbp;                                 /* Go one step forward */
    }

    return cursor;                                              /* Return Location */
}
/* Make memory free from leaks for Movie_Name list */
void free_Mn(Movie_Name *head)
{
    Movie_Name *tmp;                                            /* Temporary pointer */
    while (head != NULL)                                        /* Check entire list */
    {
        tmp = head;                                             /* Take the head of the list */
        head = head->mnp;                                       /* Then go to one step forward */
        if (tmp != NULL)                                        /* If tmp is not the end of the list (NULL) */
        {
            free(tmp->genre);                                   /* Make free index first */
            free(tmp->name);                                    /* Make free index first */
            free(tmp);                                          /* Then make free its pointer */
        }
    }
}
/* Make memory free from leaks for Movie_Budget list */
void free_Mb(Movie_Budget *head)
{
    Movie_Budget *tmp;                                          /* Temporary pointer */
    while (head != NULL)                                        /* Check entire list */
    {
        tmp = head;                                             /* Take the head of the list */
        head = head->mbp;                                       /* Then go to one step forward */
        if (tmp != NULL)                                        /* If tmp is not the end of the list (NULL) */
        {
            free(tmp);                                          /* Since 'name' is already free, it is enough to make free the pointer */
        }
    }
}
/* Find place for the remove node from Movie_Name list */
Movie_Name *find_place_movie(char *str, Movie_Name *Mn_head)
{
    Movie_Name *place = NULL;                           /* Initiliaze */

    while (Mn_head->mnp != NULL)                        /* Check end of the list */
    {
        if (strcmp(str, Mn_head->mnp->name) == 0)       /* If one step further node in the list is should remove */
        {
            place = Mn_head;                            /* Then place it */
        }
        Mn_head = Mn_head->mnp;                         /* Go one step forward in each iteration */
    }
    return place;                                       /* Return found place */
}
/* Find place of node should remove from Movie_Budget list */
Movie_Budget *find_exist_movie(char *str, Movie_Budget *Mb_head)
{
    Movie_Budget *cursor = NULL;                        /* Initiliaze */

    while (Mb_head->mbp != NULL)                        /* Check end of the list */
    {
        if (strcmp(str, Mb_head->mbp->name) == 0)       /* If one step further node in the list is should remove */
        {
            cursor = Mb_head;                           /* Then mark it */
        }
        Mb_head = Mb_head->mbp;                         /* Go one step forward in each iteration */
    }
    return cursor;                                      /* Return found mark */
}

/* =========== END OF READING FILE & CREATE LINKED LISTS =========== */

/* ==================== CREATING MENU AND IMPLEMENT OPERATORS =================== */
/* ------- Menu Implementations ------- */
void menu(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, char **genre_list, int genre_num, int num_of_movies)
{
    int operator;                                   /* Operator type */
    char *op;                                       /* String operator */

    /* ------- Take the first operator ------- */
    do
    {
        printf("\n\nEnter the operator  \n");
        printf("---------------------\n");
        printf("1.\tList of sorted data\n2.\tList of genres\n3.\tList of the movies through the years\n");
        printf("4.\tList of the movie through the IMDb scores\n5.\tAll information of a single movie\n");
        printf("6.\tAverage of the IMDb scores\n7.\tFrequence of the genres\n8.\tExit\n\n");

        op = get_string();                          /* Get string with get_string() function which is dynamically created */
        fflush(stdin);                              /* Clear the terminal */
        while (is_valid_operator(op) == FALSE)      /* Check validity and ask until get a valid operator */
        {
            printf("Please Enter a Valid operator!\n");     
            op = get_string();
            fflush(stdin);
        }
        operator = atoi(op);                        /* Turn string to int */

        /* Call the do_operations() function to manage menu by operator */
        do_operations(operator, Mb_ref, Mn_ref, genre_list, genre_num, num_of_movies);

        free(op);                                   /* Free string operator */
    } while (operator != 8);                        
}
/* ------- Managing operations takes from user in the previous function: menu() ------- */
void do_operations(int operator, Movie_Budget **Mb_ref, Movie_Name **Mn_ref, char **genre_list, int genre_num, int num_of_movies)
{
    Movie_Budget *controller;                           /* Initiliazer */
    Movie_Name *pair;                                   /* Initiliazer */
    opt_t subOpr = 0;                                   /* Initiliazer */
    char *movieName;                                    /* Initiliazer */

    /* ----- Share out operations ---- */
    switch (operator)
    {
        case 1:                                                             /* In case 1 */
        {
            printf("\n1. List of sorted data\n");                           /* Ask a sub-operator */
            printf("------------------------\n");
            printf("1.\tBudget\n");
            printf("2.\tGenre\n");
            printf("3.\tName\n");
            printf("4.\tScore\n");
            printf("5.\tYear\n\n");

            scanf("%u", &subOpr);
            getchar();
            while (!(subOpr >= 1 && subOpr <= 5))                           /* Check validity until get correct sub-operator */
            {
                printf("\nYou enter an invalid operation!\n");              
                printf("Please enter a number between 1 and 5:  ");
                scanf("%u", &subOpr);
                getchar();
            }
            do_sorted_data(Mb_ref, Mn_ref, num_of_movies, subOpr);          /* Direct it to the do_sorted_data() function */
            break;
        }
        case 2:                                                             /* In case 2 */
        {
            printf("\n2. List of genres\n");
            printf("-------------------\n");
            print_list_of_genre(genre_list, genre_num);                     /* To print list direct list and number to the print_list_of_genre() */
            break;
        }
        case 3:                                                             /* In case 3 */
        {
            printf("\n3. List of movies through the years\n");
            printf("-------------------------------------\n");
            do_through_year(Mb_ref, Mn_ref, subOpr);                        /* To print years through the years then call the function */
            break;
        }
        case 4:                                                             /* In case 4 */
        {
            printf("\n4. List of movies through the scores\n");
            printf("-------------------------------------\n");
            do_through_score(Mb_ref, Mn_ref, subOpr);
            break;
        }
        case 5:                                                             /* In case 5 */
        {
            printf("\n5. All information of a single movie\n");             
            printf("--------------------------------------\n");
            printf("Please enter the name of the movie:\n");                /* Ask movie name and take it */
            movieName = get_string();
            fflush(stdin);
            controller = find_one_movie(*Mb_ref, movieName);                /* Then check if movie is exist */
            if (controller != NULL)                                         /* If it is exist, then it will return the node */
            {
                pair = findN_pair(*Mn_ref, controller->name);               /* Find pair of the movie */
                printf("\nAll information about %s\n", movieName);          /* Print informations */
                printf("------------------------------------\n");

                if (controller->budget == 0)
                {
                    printf("Budget: Unknown\n");
                }
                else
                {
                    printf("Budget: %d\n", controller->budget);
                }
                printf("Genre: %s\n", pair->genre);
                printf("Name: %s\n", pair->name);
                printf("Score: %.1f\n", pair->score);
                printf("Year: %d\n", controller->year);

            }
            else                                                            /* If movie does not exist then warn the user then go back to menu */
            {
                printf("\nYou enter an invalid movie name\n");
            }
            break;
        }
        case 6:                                                             /* In case 6 */
        {
            printf("\n6. Average of the IMDb scores\n");
            print_imdb_average(*Mn_ref, num_of_movies);                     /* Direct head of the list and num. of movies to the function */
            break;
        }
        case 7:                                                             /* In case 7 */
        {
            printf("\n7. Frequence of the genres\n");               
            printf("----------------------------\n\n");                     /* Direct head of the list and array and counter to calculate frequence */
            frequence_of_genres(*Mn_ref, genre_list, genre_num);
            break;
        }
    }
}
/* ------- Sorting lists and take instructions from user ------- */
void do_sorted_data(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, int num_of_movies, opt_t subOpr)
{
    int i, unkn, r1, r2, value, sel;                                    /* Variables */
    int max, min;                                                       /* Variables */   
    double max_, min_, rs1, rs2;                                        /* Variables */
    Movie_Budget *singleB_node, *headB;                                 /* Variables */
    Movie_Name *singleN_node, *headN;                                   /* Variables */

    /* ----- According to the sub-operator sort only one list ----- */
    switch (subOpr)
    {
    case budget: *Mb_ref = sortB_by_pointers(*Mb_ref, subOpr);
        break;
    case genre: *Mn_ref = sortN_by_pointers(*Mn_ref, subOpr);
        break;
    case name: *Mb_ref = sortB_by_pointers(*Mb_ref, subOpr);
        break;
    case score: *Mn_ref = sortN_by_pointers(*Mn_ref, subOpr);
        break;
    case year: *Mb_ref = sortB_by_pointers(*Mb_ref, subOpr);
        break;
    }

    /* Mentality:  
       According to the sub-operator, one list has been sorted.
       Then depend on the instructions, all operations should be manage differently,
       For example for budget: There are unknown-budget movies in the list, I don't include them to the list
       for score and year: Asking for the range in score or year. For example: Prints from 1997 to 2005 
       for name and genre: It will ask the user to the range by number. For example from 7 to 1000 
       
       Displaying Part: I've sorted only one list according to the sub-operator. (for budget Movie_Budget, for genre Movie_name list) 
       There for after the find the correct range to print, I am calling a function to find PAIRs then I'm printing all informations */

    if (subOpr == budget)                                                   /* If sub-operator is Budget */            
    {
        unkn = find_unknown_number(*Mb_ref);                                /* Find number of unknown-budget movies */
        
        /* Take a correct operator */
        printf("\n\nPlease select a selection type.\n    1- Single Selection\n    2- Multiple Selection\n    ");
        scanf("%d", &sel);
        getchar();
        while (!(sel == 1 || sel == 2))
        {
            printf("\nYou enter an invalid operation\nTry Again    ");
            scanf("%d", &sel);
            getchar();
        }
        if (sel == 1)                                   /* If selection is 1 (single) */
        {
            /* Take the valid value from user */
            printf("\nEnter the value\n");              
            scanf("%d", &value);
            getchar();
            while (!(value > 0 && value <= (num_of_movies - unkn)))
            {
                printf("\nYou enter an invalid value.\nEnter a value between 1 and %d\nTry Again    ", (num_of_movies - unkn));
                scanf("%d", &value);
                getchar();
            }

            /* Find Pairs */
            singleB_node = findB_node(*Mb_ref, (value + unkn - 1));
            singleN_node = findN_pair(*Mn_ref, singleB_node->name);

            /* Print informations */
            printf("\nInformations of %d. Movie, sorted by Budget\n", value);
            printf("\n%-12s%-20s %-85s %-8s %-8s\n", "Budget", "Genre", "Name", "Score", "Year");
            if (singleB_node->budget == 0)
            {
                printf("\n%-12s%-20s %-85s %-8.1f %-8d\n", "unknown", singleN_node->genre, singleB_node->name, singleN_node->score, singleB_node->year);
            }
            else
            {
                printf("\n%-12d%-20s %-85s %-8.1f %-8d\n", singleB_node->budget, singleN_node->genre, singleB_node->name, singleN_node->score, singleB_node->year);
            }
        }
        else if (sel == 2)                              /* If selection is 2 (multiple) */
        {
            /* Find max and min budget */
            min = min_budget(*Mb_ref);
            max = max_budget(*Mb_ref);

            /* Take valid first range */
            printf("\nEnter minimum value\n");
            scanf("%d", &r1);
            getchar();
            while (!(r1 >= min && r1 <= max))
            {
                printf("\nYou enter an invalid value.\nMin Budget: %d    Max Budget: %d\nTry Again    ", min, max);
                scanf("%d", &r1);
                getchar();
            }
            /* Take valid second range */
            printf("\nEnter maximum value\n");
            scanf("%d", &r2);
            getchar();
            while (!(r2 >= r1 && r2 <= max))
            {
                printf("\nYou enter an invalid value.\nSelected min value: %d    Max Budget: %d\nTry Again    ", r1, max);
                scanf("%d", &r2);
                getchar();
            }

            /* Print movies by print_budget(function) */
            printf("\nMovies with budgets from %d USD to %d USD\n", r1, r2);
            printf("\n%-12s%-20s %-85s %-8s %-8s\n", "Budget", "Genre", "Name", "Score", "Year");

            print_budget(*Mb_ref, *Mn_ref, r1, r2);
        }
    }
    else                                                                    /* If sub-operator is not Budget */  
    {
        /* Take a valid selection type and then share it out with according to the sub-operators */
        printf("\n\nPlease select a selection type.\n    1- Single Selection\n    2- Multiple Selection\n    ");
        scanf("%d", &sel);
        getchar();
        while (!(sel == 1 || sel == 2))
        {
            printf("\nYou enter an invalid operation\nTry Again    ");
            scanf("%d", &sel);
            getchar();
        }
        if (sel == 1)                                   /* If selection type is 1 (single) */
        {
            /* Take the valid value from the 1 and Number of movies */
            printf("\nEnter the value\n");
            scanf("%d", &value);
            getchar();
            while (!(value > 0 && value <= num_of_movies))
            {
                printf("\nYou enter an invalid value.\nEnter a value between 1 and %d\nTry Again    ", num_of_movies);
                scanf("%d", &value);
                getchar();
            }

            /* Print informations according to the sub-operator */
            printf("\nInformations of %d. Movie, sorted by ", value);
            if (subOpr == genre) printf("Genre\n");
            else if (subOpr == score) printf("Score\n");
            else if (subOpr == name) printf("Name\n");
            else if (subOpr == year) printf("Year\n");

            printf("\n%-12s%-20s %-85s %-8s %-8s\n", "Budget", "Genre", "Name", "Score", "Year");
            if (subOpr == genre || subOpr == score)                     /* If sub-operator is genre or score */
            {
                /* Take the informations from Movie_Name list first then find pair of it in Movie_Budget list */
                singleN_node = findN_node(*Mn_ref, value - 1);
                singleB_node = findB_pair(*Mb_ref, singleN_node->name);
                if (singleB_node->budget == 0)
                {
                    printf("\n%-12s%-20s %-85s %-8.1f %-8d\n", "unknown", singleN_node->genre, singleB_node->name, singleN_node->score, singleB_node->year);
                }
                else
                {
                    printf("\n%-12d%-20s %-85s %-8.1f %-8d\n", singleB_node->budget, singleN_node->genre, singleB_node->name, singleN_node->score, singleB_node->year);
                }
            }
            else if (subOpr == name || subOpr == year)
            {
                /* Take the informations from Movie_Budget list first then find pair of it in Movie_Name list */
                singleB_node = findB_node(*Mb_ref, value - 1);
                singleN_node = findN_pair(*Mn_ref, singleB_node->name);
                if (singleB_node->budget == 0)
                {
                    printf("\n%-12s%-20s %-85s %-8.1f %-8d\n", "unknown", singleN_node->genre, singleB_node->name, singleN_node->score, singleB_node->year);
                }
                else
                {
                    printf("\n%-12d%-20s %-85s %-8.1f %-8d\n", singleB_node->budget, singleN_node->genre, singleB_node->name, singleN_node->score, singleB_node->year);
                }
            }
        }
        else if (sel == 2)                              /* If selection type is 2 (Multiple) */
        {
            if (subOpr == genre || subOpr == name)      /* If sub-operator is genre or name it will take numbers n to m */
            {
                min = 1;                                /* User can select from 1 to movie number */
                max = num_of_movies;
                printf("\nEnter minimum value\n");      /* Ask for the valid first range */
                scanf("%d", &r1);
                getchar();
                while (!(r1 >= min && r1 <= max))
                {
                    printf("\nYou enter an invalid value.\nMin Budget: %d    Max Budget: %d\nTry Again    ", min, max);
                    scanf("%d", &r1);
                    getchar();
                }
                printf("\nEnter maximum value\n");      /* Ask for the valid second range */
                scanf("%d", &r2);
                getchar();
                while (!(r2 >= r1 && r2 <= max))        
                {
                    printf("\nYou enter an invalid value.\nSelected min value: %d    Max Budget: %d\nTry Again    ", r1, max);
                    scanf("%d", &r2);
                    getchar();
                }

                if (subOpr == genre)                /* If sub-operator is genre */
                {
                    i = 1;
                    headN = *Mn_ref;                    /* Copy the head reference of Movie_name list */

                    printf("\nList of movies from %d to %d, sorted by Genre\n", r1, r2);
                    printf("\n%s\t%-12s%-20s %-85s %-8s %-8s\n", "Number", "Budget", "Genre", "Name", "Score", "Year");

                    while (i <= r2 && headN != NULL)    /* Until the end of the list */
                    {
                        if (i >= r1)                        /* Print Informations in the range*/
                        {
                            printf("\n%d.\t", i);
                            singleB_node = findB_pair(*Mb_ref, headN->name);
                            if (singleB_node->budget == 0)  
                            {
                                printf("%-12s%-20s %-85s %-8.1f %-8d", "unknown", headN->genre,
                                       singleB_node->name, headN->score, singleB_node->year);
                            }
                            else
                            {
                                printf("%-12d%-20s %-85s %-8.1f %-8d", singleB_node->budget, headN->genre,
                                       singleB_node->name, headN->score, singleB_node->year);
                            }
                        }
                        headN = headN->mnp;
                        i++;
                    }
                }
                else if (subOpr == name)            /* If sub-operator is name */
                {
                    i = 1;
                    headB = *Mb_ref;                    /* Copy the head reference of Movie_Budget list */

                    printf("\nList of movies from %d to %d, sorted by Name\n", r1, r2);
                    printf("\n%s\t%-12s%-20s %-85s %-8s %-8s\n", "Number", "Budget", "Genre", "Name", "Score", "Year");

                    while (i <= r2 && headB != NULL)    /* Check for the end of the list */
                    {
                        if (i >= r1)                        /* Print informations according to the range */
                        {
                            printf("\n%d.\t", i);
                            singleN_node = findN_pair(*Mn_ref, headB->name);
                            if (headB->budget == 0)
                            {
                                printf("%-12s%-20s %-85s %-8.1f %-8d", "unknown", singleN_node->genre,
                                       headB->name, singleN_node->score, headB->year);
                            }
                            else
                            {
                                printf("%-12d%-20s %-85s %-8.1f %-8d", headB->budget, singleN_node->genre,
                                       headB->name, singleN_node->score, headB->year);
                            }
                        }
                        headB = headB->mbp;
                        i++;
                    }
                }
            }
            else if (subOpr == year)                    /* If sub-operator is year */
            {
                min = find_beginning_year(*Mb_ref);     /* Find min and max year */
                max = find_finishing_year(*Mb_ref);

                printf("\nEnter start year\n");         /* Take the valid year range from user */
                scanf("%d", &r1);
                getchar();
                while (!(r1 >= min && r1 <= max))
                {
                    printf("\nYou enter an invalid value.\nStart year: %d    End year: %d\nTry Again    ", min, max);
                    scanf("%d", &r1);
                    getchar();
                }
                printf("\nEnter end year\n");
                scanf("%d", &r2);
                getchar();
                while (!(r2 >= r1 && r2 <= max))
                {
                    printf("\nYou enter an invalid value.\nSelected from year: %d    End year: %d\nTry Again    ", r1, max);
                    scanf("%d", &r2);
                    getchar();
                }
                printf("\nMovie list from %d to %d, sorted by year\n", r1, r2);
                printf("\n%-12s%-20s %-85s %-8s %-8s\n", "Budget", "Genre", "Name", "Score", "Year");

                /* Print informations by range with print_year() function */
                print_year(*Mb_ref, *Mn_ref, r1, r2);
            }
            else if (subOpr == score)                   /* If sub-operator is year */ 
            {
                min_ = find_min_score(*Mn_ref);         /* Find min and max score */
                max_ = find_max_score(*Mn_ref);

                printf("\nEnter minimum score\n");      /* Take the valid score range from user */
                scanf("%lf", &rs1);
                getchar();
                while (!(rs1 >= min_ && rs1 <= max_))
                {
                    printf("\nYou enter an invalid value.\nMin score: %.1f    Max score: %.1f\nTry Again    ", min_, max_);
                    scanf("%lf", &rs1);
                    getchar();
                }
                printf("\nEnter maximum score\n");
                scanf("%lf", &rs2);
                getchar();
                while (!(rs2 >= rs1 && rs2 <= max_))
                {
                    printf("\nYou enter an invalid value.\nSelected score: %.1f    Max score: %.1f\nTry Again    ", rs1, max_);
                    scanf("%lf", &rs2);
                    getchar();
                }
                printf("\nMovie list from %.1f to %.1f, sorted by score\n", rs1, rs2);
                printf("\n%-12s%-20s %-85s %-8s %-8s\n", "Budget", "Genre", "Name", "Score", "Year");
                /* Print informations by range with print_score() function */ 
                print_score(*Mb_ref, *Mn_ref, rs1, rs2);
            }
        }
    }
}
/* ------- Operations of 3rd operator ------- */
void do_through_year(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, opt_t subOpr)
{
    int start, end, sel, years;                         /* Variables */    

    subOpr = year;                                      /* Sort by year */
    *Mb_ref = sortB_by_pointers(*Mb_ref, subOpr);       /* Sort by year */

    start = find_beginning_year(*Mb_ref);               /* Find start and end year */
    end = find_finishing_year(*Mb_ref);


    printf("\nEnter a year\n");                         /* Ask for the year */
    scanf("%d", &years);
    getchar();
    printf("Until (0) or Since (1) %d\n", years);       /* Ask for the flag type */
    scanf("%d", &sel);
    getchar();
    while (!(sel == 0 || sel == 1))                     /* Check validity for flag type */
    {
        printf("Warning! Enter 0 for Less and 1 for Greater\n");
        scanf("%d", &sel);
        getchar();
    }

    /* ------ According to the start and end year and operator takes valid year if it is not valid ------ */
    /* For example if the smallest year is 1986, user cannot ask print movies until 1986 */
   
    if (sel == 0)                                                           /* If selection is until (0) */
    {
        /* Take a valid year for until */
        while (!(years != start && years <= end + 1 && years >= start))
        {
            if (years == start)
            {
                printf("\nWarning! List starts from %d. You cannot print movies until %d.\nTry Again    ", start, start);
            }
            else
            {
                printf("\nWarning!List start in %d and end in %d\nYou can choose min: %d max: %d\nTry Again    ", start, end, start + 1, end + 1);
            }
            scanf("%d", &years);
            getchar();
        }
    }
    else if (sel == 1)                                                      /* If selection is until (0) */
    {
        /* Take a valid year for since */
        while (!(years >= start && years <= end))
        {
            printf("\nWarning!List start in %d and end in %d\nTry Again    ", start, end);
            scanf("%d", &years);
            getchar();
        }
    }
    
    if (sel == 0)           /* If selection is 0 then print years by print_through_year() with range start and years - 1 */
    {
        printf("\n\n-->Movie names until %d, sorted by score\n", years);
        printf("--------------------------------------\n");
        print_through_year(*Mb_ref, *Mn_ref, start, years - 1);
    }
    else if (sel == 1)      /* If selection is 1 then print years by print_through_year() with range years and end */
    {
        printf("\n\n-->Movie names until %d, sorted by score\n", years);
        printf("--------------------------------------\n");
        print_through_year(*Mb_ref, *Mn_ref, years, end);
    }
}
/* ------- Operations of 4th operator ------- */
void do_through_score(Movie_Budget **Mb_ref, Movie_Name **Mn_ref, opt_t subOpr)
{
    double min, max, scor;                              /* Variables */
    int sel;

    subOpr = score;                                     /* Sort by score */
    *Mn_ref = sortN_by_pointers(*Mn_ref, subOpr);       /* Sort by score */

    min = find_min_score(*Mn_ref);                      /* Find min and max score */
    max = find_max_score(*Mn_ref);

    printf("\nEnter a score\n");                                /* Ask a score */       
    scanf("%lf", &scor);
    getchar();
    printf("Less then (0) or Greater then (1) %.1f\n", scor);   /* Ask the selection type */
    scanf("%d", &sel);
    getchar();
    
    /* Take the valid selection type if it is not valid */
    while (!(sel == 0 || sel == 1))
    {
        printf("Warning! Enter 0 for Less and 1 for Greater\n");
        scanf("%d", &sel);
        getchar();
    }

    /* ------ According to the selection type, change score if it is not valid ----- */
    /* For example if the min score is 5.1, user cannot ask print movies less then 5.1 */
    
    if (sel == 0)                           /* If selection is less(0) */
    {
        /* Ask a valid score */
        while (!(scor != min && scor <= max + 0.1 && scor >= min))
        {
            if (scor == min)
            {
                printf("\nWarning! List starts from %.1f. You cannot print movies less then %.1f.\nTry Again    ", min, min);
            }
            else
            {
                printf("\nWarning!List start in %.1f and end in %.1f\nYou can choose min: %.1f max: %.1f\nTry Again    ", min, max, min + 0.1, max + 0.1);
            }
            scanf("%lf", &scor);
            getchar();
        }
    }
    else if (sel == 1)                      /* If selection is greater(1) */
    {
        /* Ask a valid score */
        while (!(scor != max && scor < max && scor >= min - 0.1))
        {
            if (scor == max)
            {
                printf("\nWarning! List ends from %.1f. You cannot print movies greater then %.1f.\nTry Again    ", max, max);
            }
            else
            {
                printf("\nWarning!List start in %.1f and end in %.1f\nYou can choose min: %.1f max: %.1f\nTry Again    ", min, max, min - 0.1, max - 0.1);
            }
            scanf("%lf", &scor);
            getchar();
        }
    }
    
    if (sel == 0)           /* If selection is less (0) print list by print_through_score() with range of min and scor - 0.1 */
    {
        printf("\nMovie names less then %.1f, sorted by score\n", scor);
        printf("-----------------------------------------\n");
        print_through_score(*Mb_ref, *Mn_ref, min, scor - 0.01);
    }
    else if (sel == 1)      /* If selection is greater (1) print list by print_through_score() with range of scor + 0.1 and max */
    {
        printf("\nMovie names greater then %.1f, sorted by score\n", scor);
        printf("-----------------------------------------------\n");
        print_through_score(*Mb_ref, *Mn_ref, scor + 0.01, max);
    }
}
/* ------- Print score by range ------- */
void print_score(Movie_Budget *Mb_head, Movie_Name *Mn_head, double r1, double r2)
{
    Movie_Budget *singleB_node;                         /* To keep pair of the movie */
    while (Mn_head != NULL && Mn_head->score <= r2)     /* Check for the end of the list */
    {
        if (Mn_head->score >= r1)                           /* If score in the range print it */
        {
            singleB_node = findB_pair(Mb_head, Mn_head->name);  /* Take pair of the list */
            if (singleB_node->budget == 0)
            {
                printf("\n%-12s%-20s %-85s %-8.1f %-8d", "unknown", Mn_head->genre, singleB_node->name, Mn_head->score, singleB_node->year);
            }
            else
            {
                printf("\n%-12d%-20s %-85s %-8.1f %-8d", singleB_node->budget, Mn_head->genre, singleB_node->name, Mn_head->score, singleB_node->year);
            }

        }
        Mn_head = Mn_head->mnp;                             /* Go one step further */
    }
}
/* ------- Print score by budget ------- */
void print_budget(Movie_Budget *Mb_head, Movie_Name *Mn_head, int r1, int r2)
{
    Movie_Name *singleN_node;                           /* To keep pair of the node */
    while (Mb_head != NULL && Mb_head->budget <= r2)    /* Check end of the list */
    {
        if (Mb_head->budget != 0 && Mb_head->budget >= r1)  /* Check the if range is valid then print informations */
        {
            singleN_node = findN_pair(Mn_head, Mb_head->name);  /* Take the pair of the node */
            printf("\n%-12d%-20s %-85s %-8.1f %-8d", Mb_head->budget, singleN_node->genre, Mb_head->name, singleN_node->score, Mb_head->year);
        }

        Mb_head = Mb_head->mbp;                             /* Go one step further */
    }
}
/* ------- Print score by year ------- */
void print_year(Movie_Budget *Mb_head, Movie_Name *Mn_head, int r1, int r2)
{
    Movie_Name *singleN_node;                       /* To keep pair of the node */
    while (Mb_head != NULL && Mb_head->year <= r2)  /* Check for the end of the list */
    {
        if (Mb_head->year >= r1)
        {
            singleN_node = findN_pair(Mn_head, Mb_head->name);  /* Take the pair of the node */
            if (Mb_head->budget == 0)
            {
                printf("\n%-12s%-20s %-85s %-8.1f %-8d", "unknown", singleN_node->genre, Mb_head->name, singleN_node->score, Mb_head->year);
            }
            else
            {
                printf("\n%-12d%-20s %-85s %-8.1f %-8d", Mb_head->budget, singleN_node->genre, Mb_head->name, singleN_node->score, Mb_head->year);
            }

        }
        Mb_head = Mb_head->mbp;
    }
}
/* ----- Sorted Movie_Budget list by manipulating pointers instead copying the indexes ----- */
Movie_Budget *sortB_by_pointers(Movie_Budget *Mb_head, opt_t subOpr)
{
    Movie_Budget *sortedList = NULL,        /* Pointer to indicate head of the new list */
                 *larg,                     /* Pointer to largest node */
                 *cursor;                   /* One node before largest node */

    /* ------- Creating sorted list ------- */
    /*  We want to create a ascending order list. So, instead of find smallest node
        and put it to the tail, I will find largest and put it to the head */

    /*  My sorting algorithm is based on a simple mentality:
        with findB_largest() function I am searching the largest element in the original list.
        for example:
        list A:  6 <-- 3 <-- 5 <-- 2 <-- 7 <-- 1 is the original list.

        larg going to find '7' by findB_largest() function which is largest number,
        cursor is going to point '2' which is indicate '7', by findB_location().
        The it will create sortedList by 7 and shrink original list from 7.

        List A: 6 <-- 3 <-- 5 <-- 2 <-- 1
        sortedList: 7

        In second iteration larg going to find 6, but since 6 is in the head,
        cursor going to point --> NULL.

        If cursor is NULL, original list will shrink from head,
        then the largest number going to put from head.

        In this step lists are going to be:

        List A: 3 <-- 5 <-- 2 <-- 1
        sortedList: 6 <-- 7

        Iteration keep continue until the all elements moved from original list to sorted list */

    while (Mb_head != NULL)                         /* Check end of the list */
    {
        larg = findB_largest(Mb_head, subOpr);              /* Find largest node in current list */
        cursor = findB_location(Mb_head, larg);     /* Find one step before the largest node */
        if (cursor == NULL)                         /* If there is nothing before the largest, it mean it is in the head */
        {
            Mb_head = Mb_head->mbp;                 /* Then shrink list from the head */
        }
        else                                        /* If there is a node before the largest node, */
        {
            cursor->mbp = cursor->mbp->mbp;         /* Then change its link to the one step further node */
        }
        larg->mbp = NULL;                           /* Break link of the largest node */
        insertB_head(&sortedList, larg);            /* Then put it to the head of the new list */
    }
    return sortedList;                              /* Return the sorted list */
}
/* ----- Finding the largest node in the current list ----- */
Movie_Budget *findB_largest(Movie_Budget *head, opt_t subOpr)
{
    Movie_Budget *cursor = head;                                            /* Assume the largest node is in the head */

    while (head != NULL)                                                    /* Check the end of the list */
    {
        if (subOpr == budget && cursor->budget < head->budget)              /* According to the sub-operator(global) check the largest nodes */
        {
            cursor = head;
        }
        else if (subOpr == year && cursor->year < head->year)
        {
            cursor = head;
        }
        else if (subOpr == name && strcmp(cursor->name, head->name) < 0)
        {
            cursor = head;
        }
        head = head->mbp;                                                   /* Go one step further */
    }
    return cursor;                                                          /* Return the largest node address */
}
/* ----- Finding the one before node from largest node in the current list ----- */
Movie_Budget *findB_location(Movie_Budget *head, Movie_Budget *node)
{
    Movie_Budget *cursor = NULL;        /* Point it to the NULL as initial */
    while (head->mbp != NULL)           /* Check if one node further is NULL */
    {
        if (head->mbp == node)          /* Find one before node from largest node */
        {
            cursor = head;              /* Point it */
        }
        head = head->mbp;               /* Go one step further */
    }
    return cursor;                      /* If largest node is in the head returns NULL, other wise return an address */
}
/* ----- Insert unlinked node to the new sorted list ----- */
void insertB_head(Movie_Budget **head_ref, Movie_Budget *node)
{
    if (*head_ref == NULL)          /* If it is the first element */
    {
        *head_ref = node;           /* Then point its address */
    }
    else                            /* If it is not the first element */
    {
        node->mbp = *head_ref;      /* Then change the reference of the head with new node */
        *head_ref = node;
    }
}
/* ----- Sorted Movie_Budget list by manipulating pointers instead copying the indexes ----- */
Movie_Name *sortN_by_pointers(Movie_Name *Mn_head, opt_t subOpr)
{
    Movie_Name *sortedList = NULL,          /* Pointer to indicate head of the new list */
                 *larg,                     /* Pointer to largest node */
                 *cursor;                   /* One node before largest node */

    /* ------- Creating sorted list ------- */
    while (Mn_head != NULL)                         /* Check end of the list */
    {
        larg = findN_largest(Mn_head, subOpr);              /* Find largest node in current list */
        cursor = findN_location(Mn_head, larg);     /* Find one step before the largest node */
        if (cursor == NULL)                         /* If there is nothing before the largest, it mean it is in the head */
        {
            Mn_head = Mn_head->mnp;                 /* Then shrink list from the head */
        }
        else                                        /* If there is a node before the largest node, */
        {
            cursor->mnp = cursor->mnp->mnp;         /* Then change its link to the one step further node */
        }
        larg->mnp = NULL;                           /* Break link of the largest node */
        insertN_head(&sortedList, larg);            /* Then put it to the head of the new list */
    }
    return sortedList;                              /* Return the sorted list */
}
/* ----- Finding the largest node in the current list ----- */
Movie_Name *findN_largest(Movie_Name *head, opt_t subOpr)
{
    Movie_Name *cursor = head;                                              /* Assume the largest node is in the head */

    while (head != NULL)                                                    /* Check the end of the list */
    {
        if (subOpr == score && cursor->score < head->score)                 /* According to the sub-operator(global) check the largest nodes */
        {
            cursor = head;
        }
        else if (subOpr == genre && strcmp(cursor->genre, head->genre) < 0)
        {
            cursor = head;
        }
        head = head->mnp;                                                   /* Go one step further */
    }
    return cursor;                                                          /* Return the largest node address */
}
/* ----- Finding the one before node from largest node in the current list ----- */
Movie_Name *findN_location(Movie_Name *head, Movie_Name *node)
{
    Movie_Name *cursor = NULL;          /* Point it to the NULL as initial */
    while (head->mnp != NULL)           /* Check if one node further is NULL */
    {
        if (head->mnp == node)          /* Find one before node from largest node */
        {
            cursor = head;              /* Point it */
        }
        head = head->mnp;               /* Go one step further */
    }
    return cursor;                      /* If largest node is in the head returns NULL, other wise return an address */
}
/* ----- Insert unlinked node to the new sorted list ----- */
void insertN_head(Movie_Name **head_ref, Movie_Name *node)
{
    if (*head_ref == NULL)          /* If it is the first element */
    {
        *head_ref = node;           /* Then point its address */
    }
    else                            /* If it is not the first element */
    {
        node->mnp = *head_ref;      /* Then change the reference of the head with new node */
        *head_ref = node;
    }
}

/* -------------- Helper functions for Reading and Construction Part -------------- */
/* Find largest budget */
int max_budget(Movie_Budget *Mb_head)
{
    int max = 0;
    while (Mb_head != NULL)
    {
        if (max < Mb_head->budget) max = Mb_head->budget;
        Mb_head = Mb_head->mbp;
    }
    return max;
}
/* Find smallest budget */
int min_budget(Movie_Budget *Mb_head)
{
    int min = 999999999;
    while (Mb_head != NULL)
    {
        if (min > Mb_head->budget && Mb_head->budget != 0) min = Mb_head->budget;
        Mb_head = Mb_head->mbp;
    }
    return min;
}
/* Find pair of the struct  */
Movie_Name *findN_pair(Movie_Name *Mn_head, char *name)
{
    while (Mn_head != NULL)
    {
        if (strcmp(Mn_head->name, name) == 0)
        {
            return Mn_head;
        }
        Mn_head = Mn_head->mnp;
    }
    return NULL;
}
/* Find pair of the struct */
Movie_Budget *findB_pair(Movie_Budget *Mb_head, char *name)
{
    while (Mb_head != NULL)
    {
        if (strcmp(Mb_head->name, name) == 0)
        {
            return Mb_head;
        }
        Mb_head = Mb_head->mbp;
    }
    return NULL;
}
/* Finds Nth node */
Movie_Budget *findB_node(Movie_Budget *Mb_head, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        Mb_head = Mb_head->mbp;
    }
    return Mb_head;
}
/* Finds Nth node */
Movie_Name *findN_node(Movie_Name *Mn_head, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        Mn_head = Mn_head->mnp;
    }
    return Mn_head;
}
/* Finds number of the unknown-budget movies */
int find_unknown_number(Movie_Budget *Mb_head)
{
    int sum = 0;
    while (Mb_head != NULL)
    {
        if (Mb_head->budget == 0)
        {
            sum++;
        }
        Mb_head = Mb_head->mbp;
    }
    return sum;
}
/* Displaying list of the genres */
void print_list_of_genre(char **genre_list, int genre_num)
{
    int i;
    for (i = 0; i < genre_num; i++)
    {
        printf("-> %s\n", genre_list[i]);
    }
}
/* Find smallest year */
int find_beginning_year(Movie_Budget *Mb_head)
{
    int beg = Mb_head->year;
    while (Mb_head != NULL)
    {
        if (Mb_head->year < beg)
        {
            beg = Mb_head->year;
        }
        Mb_head = Mb_head->mbp;
    }
    return beg;
}
/* Find largest year */
int find_finishing_year(Movie_Budget *Mb_head)
{
    int fin = Mb_head->year;
    while (Mb_head != NULL)
    {
        if (Mb_head->year > fin)
        {
            fin = Mb_head->year;
        }
        Mb_head = Mb_head->mbp;
    }
    return fin;
}
/* Print list through start and end year */
void print_through_year(Movie_Budget *Mb_head, Movie_Name *Mn_head, int start_year, int end_year)
{
    while (Mb_head != NULL)
    {
        if (Mb_head->year >= start_year && Mb_head->year <= end_year)
        {
            printf("\n%s  (%d)", Mb_head->name, Mb_head->year);
        }
        Mb_head = Mb_head->mbp;
    }
}
/* Find min score */
double find_min_score(Movie_Name *Mn_head)
{
    double min = Mn_head->score;
    while (Mn_head != NULL)
    {
        if (Mn_head->score < min)
        {
            min = Mn_head->score;
        }
        Mn_head = Mn_head->mnp;
    }
    return min;
}
/* Find max score */
double find_max_score(Movie_Name *Mn_head)
{
    double max = Mn_head->score;
    while (Mn_head != NULL)
    {
        if (Mn_head->score > max)
        {
            max = Mn_head->score;
        }
        Mn_head = Mn_head->mnp;
    }
    return max;
}
/* Print list through min and max score */
void print_through_score(Movie_Budget *Mb_head, Movie_Name *Mn_head, double min_score, double max_score)
{
    while (Mn_head != NULL)
    {
        if (Mn_head->score >= min_score && Mn_head->score <= max_score)
        {
            printf("\n%s  (%.1f)", Mn_head->name, Mn_head->score);
        }
        Mn_head = Mn_head->mnp;
    }
}
/* Find movie from its name */
Movie_Budget *find_one_movie(Movie_Budget *Mb_head, char *str)
{
    Movie_Budget *cursor = NULL;
    while (Mb_head != NULL)
    {
        if (strcmp(Mb_head->name, str) == 0)
        {
            cursor = Mb_head;
        }
        Mb_head = Mb_head->mbp;
    }
    return cursor;
}
/* Print IMDb score by scanning all list and divide by num_of_movies */
void print_imdb_average(Movie_Name *Mn_head, int num_of_movies)
{
    double sum = 0;
    while (Mn_head != NULL)
    {
        sum += Mn_head->score;
        Mn_head = Mn_head->mnp;
    }
    printf("\nAverage of scores: %f\n", sum / (double)num_of_movies);
    printf("---------------------------\n");
}
/* Create a genre list */
char **list_genre(Movie_Name *Mn_head, int *genre_num)
{
    char **genre_list, **temp = NULL;                       /* Variables */
    int i;

    while (Mn_head != NULL)                                 /* Check end of the list */
    {
        if (is_genre_exist(Mn_head->genre, genre_list, *genre_num) == FALSE)    /* Check if movie already exist */
        {
            (*genre_num)++;                                                     /* Increase genre_num by one */
            genre_list = calloc((*genre_num), sizeof(char *));                  /* Allocate memory for genre array */
            for (i = 0; i < (*genre_num) - 1; i++) genre_list[i] = temp[i];     /* Fill genre_list with previous list */
            genre_list[(*genre_num) - 1] = Mn_head->genre;                      /* Fill the last index */
            if (temp != NULL) free(temp);                                       /* Make free previous list */
            temp = genre_list;                                                  /* Change temp with new list */
        }
        Mn_head = Mn_head->mnp;                             /* Go end of the list */
    }
    return genre_list;                                      /* Return that created genre array */
}
/* Find frequence of genres and print it */
void frequence_of_genres(Movie_Name *Mn_head, char **genre_list, int genre_num)
{
    int i;                                                      /* Variables */
    int *freq_genre;                                            /* Variables */ 

    freq_genre = calloc(genre_num, sizeof(int));                       /* Create a int array */
    /* ------ Check end of the list and compare all genres in the list with array ------ */
    while (Mn_head != NULL)
    {
        for (i = 0; i < genre_num; i++)                         /* Check all genres with genre_list[] array */
        {
            if (strcmp(Mn_head->genre, genre_list[i]) == 0)
            {
                freq_genre[i]++;                                /* Increase by one */
            }
        }
        Mn_head = Mn_head->mnp;                                 /* Go one step further */
    }
    for (i = 0; i < genre_num; i++)                             /* Print frequence */
    {
        printf("%-12s:\t\t%d\n", genre_list[i], freq_genre[i]);
    }
    free(freq_genre);
}
/* Check if genre is already exist in the genre_list array */
int is_genre_exist(char *str, char **genre_list, int genre_num)
{
    int i;
    for (i = 0; i < genre_num; i++)
    {
        if (strcmp(genre_list[i], str) == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
/* Take chars from console by getchar and create a string dynamically */
char *get_string(void)
{
    char *opr;
    char *temp = NULL;
    char ch = '\0';
    int i, counter;
    counter = 0;
    while (ch != '\n')
    {
        ch = getchar();
        counter++;
        opr = calloc(counter, sizeof(char));
        for (i = 0; i < counter - 1; i++)
        {
            opr[i] = temp[i];
        }
        if (ch == '\n')
        {
            opr[counter - 1] = '\0';
        }
        else
        {
            opr[counter - 1] = ch;
        }
        if (temp != NULL)
        {
            free(temp);
        }
        temp = opr;
    }
    return opr;
}
/* Check the if first operator is valid */
int is_valid_operator(char *op)
{
    if (strlen(op) == 1 && (op[0] >= '1' && op[0] <= '8'))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/* ==================== END OF THE MENU IMPLEMENTATIONS =================== */

