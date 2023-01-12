#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Labeling the columns. */
int BUDGET;
int GENRE;
int NAME;
int SCORE;
int YEAR;

#define TRUE 1
#define FALSE -1

/* Movie Struct */
struct Movie
{
    double budget;
    int genre;
    char *name;
    double score;
    int year;
};

/* Char pointer array for keep the genre names and counter for number of genre */
char **genreArray;
int genreNumber;

/* ----------------------- HEADERS ----------------------- */

/* =========== FILE READING & FILL STRUCT ARRAY =========== */
struct Movie *read_file(char *infile, int *movieNumber);
char *decompose_line(struct Movie *m, char *line);
int is_movie_exist(struct Movie *m, char *str, int n);
void free_struct(struct Movie *m, int n);
void free_genre(void);
int is_genre(char *str);
int is_exist(char *str);
char *get_line(FILE *fp, int *flag);
void arrange_columns(char *str);
/* ======================================================== */

/* ======================== MENU ========================== */
void menu(struct Movie *movies, int movieNumber);
int is_valid_operator(char *operator);
char *get_string(void);
void do_operations(struct Movie *movies, int movieNumber, int operator);
void do_sorted_data(struct Movie *movies, int movieNumber, int operator);
void sort(struct Movie *movies, int movieNumber, int operator);
int number_of_unknown(struct Movie *movies, int movieNumber);
void print_list_of_genre();
int find_beginning_year(struct Movie *movies, int movieNumber);
int find_finishing_year(struct Movie *movies, int movieNumber);
void print_through_year(struct Movie *movies, int start_year, int end_year, int movieNumber);
double find_min_score(struct Movie *movies, int movieNumber);
double find_max_score(struct Movie *movies, int movieNumber);
void print_through_score(struct Movie *movies, double min_score, double max_score, int movieNumber);
int find_one_movie(struct Movie *movies, int movieNumber, char *str);
void print_imdb_average(struct Movie *movies, int movieNumber);
void frequence_of_genres(struct Movie *movies, int movieNumber);
/* ======================================================== */


/* ========================= MAIN ========================= */

/* Main function takes the struct array pointer from read_file() and send it to the menu() */
int main(void)
{
    char *infile = "shortmovies.txt";
    int movieNumber;
    struct Movie *movies;

    printf("\nFile is reading...\n\n");
    /* Reads movies from file and put them into the *movies */
    movies = read_file(infile, &movieNumber);

    printf("-------------------------------------------\n");
    printf("------------- Movie Assistant -------------\n");
    printf("-------------------------------------------");

    /* Menu of program */
    menu(movies, movieNumber);

    /* Make free 2D string array. */
    free_genre();
    /* Make free struct Movie array with it 'char *name' elements. */
    free_struct(movies, movieNumber);
    return 0;
}

/* =========== FILE READING & FILL STRUCT ARRAY =========== */

/* Goal: Reading file and put them into a struct array.
   infile: file name, movieNumber: number of movie in the list(After overwrite the same movies)*/
struct Movie * read_file(char *infile, int *movieNumber)
{
    struct Movie *moviesPointer,    /* Movie struct array */
           *temp = NULL,            /* Temp struct array */
           newMovie;                /* New movie struct */

    char *line;                     /* Char array for keep the lines dynamically */

    int flag,                       /* Flag for if EOF */
        counter,                    /* Counter for the number of movies */
        i,                          /* Loop initiliazer */
        controller;                 /* Controller for if the new movie already putted the array */

    FILE *MFP;                      /* Movie File Pointer */

    counter = 0;

    /* Open up Movie File Pointer */
    MFP = fopen(infile, "r");
    if (MFP == NULL)
    {
        printf("Can not open the file!\n");
        exit(1);
    }

    line = get_line(MFP, &flag);    /* Take first line from the file (By dynamically created get_line function) */
    arrange_columns(line);          /* Arrange columns according to the order */
    
    /* Loop for reading file line by line */
    while (1)
    {
        free(line);                             /* Discharge memory in every iteration */
        line = get_line(MFP, &flag);            /* Get lines from 2nd line to EOF --> MFP: File pointer, flag: To determine EOF*/
        if (flag == -1 && strlen(line) < 2)     /* If EOF detected, then break the loop */
        {
            free(line);
            break;
        }

        /* Decomposing lines to the new struct for adding array later:
           decompose_line() takes a struct as an argument then fill it with informations.
           Lastly returns a char* (string address) which created dynamically and put it newMovie.name as pointer */
        newMovie.name = decompose_line(&newMovie, line);

        /* In each new movie, counter increase one by one */
        counter++;

        /* Resize struct according to the new movie number (counter) */
        moviesPointer = calloc(counter, sizeof(struct Movie));

        for (i = 0; i < counter - 1; i++)
        {
            moviesPointer[i] = temp[i];
        }
        /* is_movie_exist() function, if movie already in the list,
           It will return the index, otherwise, it fill return FALSE.
           If controller is an index, then it will be updated.
           Else, it will add the newMovie to the end of the moviesPointer array. */

        controller = is_movie_exist(moviesPointer, newMovie.name, counter - 1);
        if (controller != FALSE)
        {
            counter--;
            moviesPointer[controller].budget = newMovie.budget;
            moviesPointer[controller].genre = newMovie.genre;
            moviesPointer[controller].score = newMovie.score;
            moviesPointer[controller].year = newMovie.year;
            free(newMovie.name);
        }
        else
        {
            moviesPointer[counter - 1] = newMovie;
        }
        /* In each iteration, temp keeps the one previous array, and free discharges memory end of the iteration. */
        if (temp != NULL)
        {
            free(temp);
        }
        /* After free() it will keep the other array to implement it in other iteration. */
        temp = moviesPointer;
    }

    /* Assign counter as movieNumber and return it as an argument */
    *movieNumber = counter;

    /* Close the file */
    fclose(MFP);

    /* Return array to the main function */
    return moviesPointer;
}

/* Goal: getting line from the file.
   fp = file pointer, flag: for detect the EOF */
char *get_line(FILE *fp, int *flag)
{
    char ch;                /* Char for reading line one char at a time */
    char *line = NULL;      /* Char pointer to take line dynamically */
    char *temp = NULL;      /* Char pointer for re-allocation of the char array (line) */
    int i, counter;         /* Initiliazers */


    /* Until the newline or EOF characters, reads line one char at a time and add them a char array dynamically */
    counter = 0;
    ch = '\0';
    while(ch != '\n' && ch != EOF)
    {
        ch = fgetc(fp);                         /* Reading char from file */
        counter++;                              /* Increase counter one by one in each reading */
        line = calloc(counter, sizeof(char));   /* Resize line in each iteration */

        for (i = 0; i < counter - 1; i++)       /* Copying previous elements to new allocated line */
        {
            line[i] = temp[i];
        }

        if (ch == '\n' || ch == EOF)    /* If ch is newline or EOF then break the rule */
        {
            if (ch == EOF)              /* Else if ch is EOF then pass flag as -1 */
            {
                *flag = -1;
                break;
            }
            line[counter - 1] = '\n';
            break;
        }
        line[counter - 1] = ch;

        /* Clean memory with previous char array */
        if (temp != NULL)
        {
            free(temp);
        }
        temp = line;
    }
    free(temp);
    /* Return address of string which created dynamically */
    return line;
}

/* Goal: Decomposing line and return the name of the movie.
   m: is a struct pointer which is address of the newMovie struct in read_file()
   line: It will be decompose and decomposed informations going to kept by m (newMovie struct) but name.
   name going to return by function and it will take by newMovie in line 134 */
char *decompose_line(struct Movie *m, char *line)
{
    int i, index, length, flag;  /* Initiliazer */

    /* Initiliazer for decomposing line into the parts */
    char *buffer;
    char *name;

    i = 0; length = 0; flag = 0;


    /* Flags from 7 to 11th (BUDGET, GENRE, NAME...) are arranged with by calling arrange_columns() in 118th line */
    while (1)
    {
        /* According to the last characters, flag increase one by one to make comparision with BUDGET, GENRE... */
        if (line[i] == ',' || line[i] == '\0' || line[i] == '\n' || line[i] == EOF)
        {
            flag++;

            /* If flag equal to BUDGET, then allocate memory for buffer and
               if budget is unknown put -1 into the struct
               else put the budget into the struct by changing string to double -->atof() */
            if (flag == BUDGET)
            {
                buffer = malloc(length + 1);
                strncpy(buffer, &line[i - length], length);
                buffer[length] = '\0';
                if (strcmp(buffer, "unknown") == 0)
                {
                    m->budget = -1;
                }
                else
                {
                    m->budget = atof(buffer);
                }
                free(buffer);
            }
            /* If flag is GENRE, allocates memory for buffer and copy this part into it.
               After all, it calls is_genre to find detect if current genre is already exist or not.
               If not it increase the size of pointer array (line 27) and put new genre to it. */
            else if (flag == GENRE)
            {
                buffer = malloc(length + 1);
                strncpy(buffer, &line[i - length], length);
                buffer[length] = '\0';

                index = is_genre(buffer);
                m->genre = index;

                free(buffer);
            }
            /* If flag is NAME, then put the string into char *name to return end of the decomposing */
            else if (flag == NAME)
            {
                name = malloc(length + 1);
                strncpy(name, &line[i - length], length);
                name[length] = '\0';
            }
            /* If flag is SCORE, then change string to doube with atof() and keep it into the m->score */
            else if (flag == SCORE)
            {
                buffer = malloc(length + 1);
                strncpy(buffer, &line[i - length], length);
                buffer[length] = '\0';

                m->score = atof(buffer);
                free(buffer);
            }
            /* If flag is YEAR, then change string to int with atoi() and keep it into the m->year */
            else if (flag == YEAR)
            {
                buffer = malloc(length + 1);
                strncpy(buffer, &line[i - length], length);
                buffer[length] = '\0';

                m->year = atoi(buffer);
                free(buffer);
            }
            length = 0;
        }
        else
        {
            length++;
        }

        /* If find newline or null then break the loop */
        if (line[i] == '\0' || line[i] == '\n')
        {
            break;
        }
        i++;
    }
    return name;
}
/* Goal: take string, compare it with char **genreArray, if it doesn't exist, return last index of char **, otherwise return index */
int is_genre(char *str)
{
    /* Initiliazers */
    int i, index;
    char **temp = NULL;

    /* Check if genre is exist */
    index = is_exist(str);

    /* If exist, then return the index where genre is in the array */
    if (index != FALSE)
    {
        return index;
    }
    /* Otherwise add genre to the char **genreArray and increase number of genres */
    else
    {
        genreNumber++;
        temp = genreArray;
        genreArray = calloc(genreNumber, sizeof(char *));
        for (i = 0; i < genreNumber - 1; i++)
        {
            genreArray[i] = temp[i];
        }
        genreArray[genreNumber - 1] = malloc(strlen(str) + 1);
        strcpy(genreArray[genreNumber - 1], str);

        if (temp != NULL)
        {
            free(temp);
        }
    }
    return genreNumber - 1;
}
/* --------- HELPER FUNCTIONS TO READ FILE AND STORE THEM INTO THE STRUCT ARRAY --------- */

/* If genre exist then returns the index, otherwise return FALSE */
int is_exist(char *str)
{
    int i;
    for (i = 0; i < genreNumber; i++)
    {
        if (strcmp(genreArray[i], str) == 0)
        {
            return i;
        }
    }
    return FALSE;
}

/* Checks if the movie exist, if it is, then return index, otherwise return FALSE */
int is_movie_exist(struct Movie *m, char *str, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(m[i].name, str) == 0)
        {
            return i;
        }
    }
    return FALSE;
}

/* Ordering the columns according to the first line.
   Looks for ',' or '\n' or '\0' and if finds it increase flag then equals it with the global integers from 7 to 11th line */
void arrange_columns(char *str)
{
    int i, j, counter, flag;
    char *row_name = NULL;
    char *temp = NULL;

    i = 0; counter = 0; flag = 0;

    while (1)
    {
        /* If find ',' or '\n' or '\0' or '\r' then initiliaze counter from 0*/
        if (str[i] == ',' || str[i] == '\n' || str[i] == '\0' || str[i] == '\r')
        {
            counter = 0;
            /* Finally, arrange the rows according to the row_name. Store them into the global int's.
               Go to: 7th line */
            if (strncmp(row_name, "budget", 6) == 0)
            {
                flag++;
                BUDGET = flag;
                free(row_name);
                row_name = NULL;
            }
            else if (strncmp(row_name, "genre", 5) == 0)
            {
                flag++;
                GENRE = flag;
                free(row_name);
                row_name = NULL;
            }
            else if (strncmp(row_name, "name", 4) == 0)
            {
                flag++;
                NAME = flag;
                free(row_name);
                row_name = NULL;
            }
            else if (strncmp(row_name, "score", 5) == 0)
            {
                flag++;
                SCORE = flag;
                free(row_name);
                row_name = NULL;
            }
            else if (strncmp(row_name, "year", 4) == 0)
            {
                flag++;
                YEAR = flag;
                free(row_name);
                row_name = NULL;
            }
        }
        /* Otherwise, check the line char by char then put them into char *row_name dynamically */
        else
        {
            counter++;
            temp = row_name;
            row_name = calloc(counter, sizeof(char));
            for (j = 0; j < counter - 1; j++)
            {
                row_name[j] = temp[j];
            }
            row_name[counter - 1] = str[i];

            if (temp != NULL)
            {
                free(temp);
            }
        }
        if (str[i] == '\n' || str[i] == '\0' || str[i] == '\r')
        {
            break;
        }
        i++;
    }
}
/* Makes free first strings then all pointer array */
void free_genre(void)
{
    int i;
    for (i = 0; i < genreNumber; i++)
    {
        free(genreArray[i]);
    }
    free(genreArray);
}

/* Make free first name inside the struct then all struct array */
void free_struct(struct Movie *m, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(m[i].name);
    }
    free(m);
}


/* ========================= MENU ========================= */

/* menu() takes the struct array address and number of movies from main.
   Goal: Take first operators from user and according to the validity send operator
   to the do_operations() for taking sub operations from user. */
void menu(struct Movie *movies, int movieNumber)
{
    int operator;       /* Valid operator */
    char *op;           /* Operator takes string first and check if it is valid */
    do
    {
        /* Ask user operations */
        printf("\n\nEnter the operator  \n");
        printf("--------------------\n");
        printf("  1.    List of sorted data\n  2.    List of genres\n  3.    List of the movies through the years\n");
        printf("  4.    List of the movie through the IMDb scores\n  5.    All information of a single movie\n");
        printf("  6.    Average of the IMDb scores\n  7.    Frequence of the genres\n  8.    Exit\n\n  ");

        /* Take operator as a string and check for validity */
        op = get_string();
        fflush(stdin);
        /* Ask user until a valid operation */
        while (is_valid_operator(op) == FALSE)
        {
            printf("Please Enter a Valid operator!\n");
            op = get_string();
            fflush(stdin);
        }

        /* If operation between 1 and 8 then change it int to string */
        operator = atoi(op);
        free(op);

        /* Send it to to the do_operations for sub operations */
        do_operations(movies, movieNumber, operator);

    } while (operator != 8);
    printf("\nHave a good day!\n");
}
void do_operations(struct Movie *movies, int movieNumber, int operator)
{
    int subOpr,                 /* sub operation */
        year, year_flag,        /* year & until (0) from (1) operation */
        start_year, end_year,   /* Start and end years */
        score_flag,             /* until (0) from (1) operation */
        controller;             /* TRUE if movie exist, else FALSE */

    double score,                   /* Keep score */
           min_score, max_score;    /* Max and min score from text file */

    char *movieName;                /* For taking movie name from user */

    /* According to the first operators, takes SUB OPERATORS from user */
    switch (operator)
    {
        case 1:
        {
            /* If operator is List of sorted data, ask for sub opt */
            printf("\n  1. List of sorted data\n");
            printf("  ------------------------\n");
            printf("    1.    Budget\n");
            printf("    2.    Genre\n");
            printf("    3.    Name\n");
            printf("    4.    Score\n");
            printf("    5.    Year\n\n    ");
            scanf("%d", &subOpr);
            getchar();

            /* Check for validity, and if valid, send sub operator to do_sorted_data() to make operations */
            if (subOpr >= 1 && subOpr <= 5)
            {
                do_sorted_data(movies, movieNumber, subOpr);
            }
            else
            {
                printf("\n    You enter an invalid operation!\n");
            }
            break;
        }
        /* If operator is List of genres then print list of genres by print_list_of_genre() */
        case 2:
        {
            printf("\n  2. List of genres\n");
            printf("  -------------------\n");
            print_list_of_genre();
            break;
        }
        /* If operator is List of movies through the years, then ask for range */
        case 3:
        {
            printf("\n  3. List of movies through the years\n");
            printf("  -------------------------------------\n");
            sort(movies, movieNumber, YEAR);
            start_year = find_beginning_year(movies, movieNumber);
            end_year = find_finishing_year(movies, movieNumber);

            /* Check for validity of operations and year by comparing them with start and end year */
            do
            {
                printf("\n  --> Enter a year\n  ");
                scanf("%d", &year);
                printf("\n  --> until %d (0)  or  from %d (1)\n  ", year, year);
                scanf("%d", &year_flag);
                getchar();

                /* If user enter an invalid year then warn he/she */
                if (year_flag == 0 && (year <= start_year))
                {
                    printf("\n  You enter an invalid year!\n  Movies start from %d.\n", start_year);
                }
                else if (year_flag == 1 && (year >= end_year))
                {
                    printf("\n  You enter an invalid year!\n  Movies end in %d.\n", end_year);
                }

            } while (((year_flag == 0) && (year <= start_year)) || ((year_flag == 1) && (year >= end_year)));

            /* According to the operations print the movies in the range */
            if (year_flag == 0)
            {
                print_through_year(movies, start_year, year, movieNumber);
            }
            else if (year_flag == 1)
            {
                print_through_year(movies, year, end_year, movieNumber);
            }
            break;
        }
        /* If operator is List of movies through the scores, then ask for range */
        case 4:
        {
            printf("\n  4. List of movies through the scores\n");
            printf("  -------------------------------------\n");
            sort(movies, movieNumber, SCORE);
            min_score = find_min_score(movies, movieNumber);
            max_score = find_max_score(movies, movieNumber);
            /* Check for validity of operations and year by comparing them with min and max score */
            do
            {
                printf("\n  --> Enter a score\n  ");
                scanf("%lf", &score);
                printf("\n  --> until %.1f (0)  or  from %.1f (1)\n  ", score, score);
                scanf("%d", &score_flag);
                getchar();
                /* If user enter an invalid year then warn he/she */
                if (score_flag == 0 && (score <= min_score))
                {
                    printf("\n  You enter an invalid score!\n  Minimum score is %.1f.\n", min_score);
                }
                else if (score_flag == 1 && (score >= max_score))
                {
                    printf("\n  You enter an invalid score!\n  Maximum score is %.1f.\n", max_score);
                }

            } while (((score_flag == 0) && (score <= min_score)) || ((score_flag == 1) && (score >= max_score)));

            /* According to the operations print the movies in the range */
            if (score_flag == 0)
            {
                print_through_score(movies, min_score, score, movieNumber);
            }
            else if (score_flag == 1)
            {
                print_through_score(movies, score, max_score, movieNumber);
            }
            break;
        }
        /* If operator is All information of a single movie, then ask for range */
        case 5:
        {
            printf("\n  5. All information of a single movie\n");
            printf("  --------------------------------------\n");
            printf("    Please enter the name of the movie:\n    ");
            movieName = get_string();
            fflush(stdin);
            /* Get string name from user and check if it is exist */
            controller = find_one_movie(movies, movieNumber, movieName);

            /* If exist, then print all informations */
            if (controller != FALSE)
            {
                printf("\n    Budget:  ");
                if (movies[controller].budget == -1)
                {
                    printf("unknown\n");
                }
                else
                {
                    printf("%.1f\n", movies[controller].budget);
                }
                printf("    Genre:   %s\n", genreArray[movies[controller].genre]);
                printf("    Name:    %s\n", movies[controller].name);
                printf("    Score:   %.1f\n", movies[controller].score);
                printf("    Year:    %d\n", movies[controller].year);
            }
            /* If does not exist then warn user */
            else
            {
                printf("\n   You enter an invalid movie name\n");
                printf("  ----------------------------------\n");
            }
            break;
        }
        /* If operator is Average of the IMDb scores, print average by print_imdb_average() */
        case 6:
        {
            printf("\n  6. Average of the IMDb scores\n");
            printf("  -------------------------------\n");
            print_imdb_average(movies, movieNumber);
            break;
        }
        /* If operator is Frequence of the genres, print freqeunce by freqeunce_of_genres */
        case 7:
        {
            printf("\n  7. Frequence of the genres\n");
            printf("  ----------------------------\n\n");
            frequence_of_genres(movies, movieNumber);
            break;
        }
    }
}

void do_sorted_data(struct Movie *movies, int movieNumber, int operator)
{
    int i,          /* Index */
        selection,  /* Selection type (multiple/single) */
        value,      /* For single selection, ask for index */
        r1, r2,     /* For multiple selection ask for range */
        unknownNum; /* Number of unknown budgets */

    /* Firstly, sort move list according to the sub operator comes from do_operations(); */
    sort(movies, movieNumber, operator);

    /* Take a valid operator from user */
    printf("\n  Please select an selection type\n\n  1. Single Selection\n  2. Multiple Selection\n  ");
    scanf("%d", &selection);
    getchar();

    while (1)
    {
        if (selection == 1 || selection == 2)
        {
            break;
        }
        else
        {
            printf("\n  You enter an invalid operation\n  Try Again\n  ");
            scanf("%d", &selection);
            getchar();
        }
    }
    /* If selection is single */
    if (selection == 1)
    {
        /* Take a valid value (index) from user */
        printf("    Enter the value\n    ");
        scanf("%d", &value);
        getchar();
        while (1)
        {
            if (value >= 1 && value <= movieNumber)
            {
                break;
            }
            else
            {
                printf("\n  You enter an invalid value \n  Try Again (1 to %d)\n  ", movieNumber);
                scanf("%d", &value);
                getchar();
            }
        }
        /* Create index from value user enter */
        i = value - 1;

        /* Since there is unknown budgets, do not include them to the sorting
           After create an index then print the sorting type  */
        if (operator == BUDGET)
        {
            unknownNum = number_of_unknown(movies, movieNumber);
            i += unknownNum;
            if (i > movieNumber - 1)
            {
                printf("\nWARNING! Because of unknown budget films, The most expensive film has been written!\n");
                i = movieNumber - 1;
            }
            printf("\n  %d. Movie, sorted by budget\n", value);
        }
        else if (operator == GENRE)
        {
            printf("\n  %d. Movie, sorted by genre\n", value);
        }
        else if (operator == SCORE)
        {
            printf("\n  %d. Movie, sorted by score\n", value);
        }
        else if (operator == YEAR)
        {
            printf("\n  %d. Movie, sorted by year\n", value);
        }

        /* Finally, print the movie informations */
        printf("\n\t%-12s%-20s %-80s %-8s %-8s\n", "Budget", "Genre", "Name", "Score", "Year");
        if (movies[i].budget == -1)
        {
            printf("\n\t%-12s%-20s %-80s %-8.1f %-8d\n", "unknown", genreArray[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
        }
        else
        {
            printf("\n\t%-12.0f%-20s %-80s %-8.1f %-8d\n", movies[i].budget, genreArray[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
        }
        printf("\t--------------------------------------------------------------------------\n");
    }
    /* If user ask for multiple selection */
    else if (selection == 2)
    {
        /* Ask for first range and take it if it is valid */
        printf("    Enter the start value    ");
        scanf("%d", &r1);
        getchar();
        while(1)
        {
            if (r1 >= 1 && r1 < movieNumber - 1)
            {
                break;
            }
            if (r1 < 1)
            {
                printf("    Movie list starts from 1\n     Enter a bigger number\n    ");
                scanf("%d", &r1);
                getchar();
            }
            else if (r1 >= movieNumber - 1)
            {
                printf("    Movie list ends in %d\n     Enter a smaller number\n    ", movieNumber - 1);
                scanf("%d", &r1);
                getchar();
            }
        }
        /* Ask for second range and take it if it is valid */
        printf("    Enter the end value    ");
        scanf("%d", &r2);
        getchar();
        while(1)
        {
            if (r2 >= r1 && r2 <= movieNumber)
            {
                break;
            }
            if (r2 < r1)
            {
                printf("    List has to start from %d \n     Enter a number bigger than start number\n    ", r1);
                scanf("%d", &r2);
                getchar();
            }
            else if (r2 >= movieNumber)
            {
                printf("    Movie list ends in %d\n     Enter a smaller number\n    ", movieNumber);
                scanf("%d", &r2);
                getchar();
            }
        }
        /* If operator is budget then modify range according to the number of unknown budget film
           And print which kind of sorting we do */
        if (operator == BUDGET)
        {
            printf("\n  Movies between %d and %d, sorted by budget\n", r1, r2);
            unknownNum = number_of_unknown(movies, movieNumber);
            r1 += unknownNum;
            r2 += unknownNum;

            /* If range is become out of the movie number by adding number of the unknown budgets,
               then print movies according to the most expensive one. */
            if (r1 > movieNumber - 1)
            {
                r1 = movieNumber;
            }
            if (r2 > movieNumber - 1)
            {
                printf("\n    Unknown budgets does not include the list! \n    Printed according to most expensive movie!\n");
                r2 = movieNumber;
            }
        }
        else if (operator == GENRE)
        {
            printf("\n  Movies between %d and %d, sorted by genre\n", r1, r2);
        }
        else if (operator == SCORE)
        {
            printf("\n  Movies between %d and %d, sorted by score\n", r1, r2);
        }
        else if (operator == YEAR)
        {
            printf("\n  Movies between %d and %d, sorted by year\n", r1, r2);
        }
        /* Print informations for the movies in the range */
        printf("\n\t%-12s%-20s %-80s %-8s %-8s\n\n", "Budget", "Genre", "Name", "Score", "Year");
        for (i = r1 - 1; i < r2; i++)
        {
            if (movies[i].budget == -1)
            {
                printf("\t%-12s%-20s %-80s %-8.1f %-8d\n", "unknown", genreArray[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
            }
            else
            {
                printf("\t%-12.0f%-20s %-80s %-8.1f %-8d\n", movies[i].budget, genreArray[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
            }
        }
        printf("\t--------------------------------------------------------------------------\n");
    }
}

/* Selection sorting of the list */
void sort(struct Movie *movies, int movieNumber, int operator)
{
    int i, j, min_index;        /* Loop initiliazers and index */
    struct Movie temp_movie;    /* Temporarily struct array */

    /* Takes index from first to one less the end of the indexes and compare them
       with entire list, and sort them increasing order */
    for (i = 0; i < movieNumber - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < movieNumber; j++)
        {
            /* According to the Operator compare indexes and find min, then sort the list */
            if (operator == BUDGET)
            {
                if (movies[j].budget < movies[min_index].budget)
                {
                    min_index = j;
                }
            }
            else if (operator == GENRE)
            {
                if (strcmp(genreArray[movies[j].genre], genreArray[movies[min_index].genre]) < 0)
                {
                    min_index = j;
                }
            }
            /* But name, it comparing by string */
            else if (operator == NAME)
            {
                if (strcmp(movies[j].name, movies[min_index].name) < 0)
                {
                    min_index = j;
                }
            }
            else if (operator == SCORE)
            {
                if (movies[j].score < movies[min_index].score)
                {
                    min_index = j;
                }
            }
            else if (operator == YEAR)
            {
                if (movies[j].year < movies[min_index].year)
                {
                    min_index = j;
                }
            }

        }
        /* Replace struct array indexes */
        temp_movie = movies[min_index];
        movies[min_index] = movies[i];
        movies[i] = temp_movie;
    }
}
/* Print list of genre */
void print_list_of_genre()
{
    int i;
    for (i = 0; i < genreNumber; i++)
    {
        printf("  %s\n", genreArray[i]);
    }
}
/* Find smallest year in the list */
int find_beginning_year(struct Movie *movies, int movieNumber)
{
    int begin, i;
    begin = movies[0].year;
    for (i = 1; i < movieNumber; i++)
    {
        if (movies[i].year < begin)
        {
            begin = movies[i].year;
        }
    }
    return begin;
}
/* Find largest year in the list */
int find_finishing_year(struct Movie *movies, int movieNumber)
{
    int end, i;
    end = movies[0].year;
    for (i = 1; i < movieNumber; i++)
    {
        if (movies[i].year > end)
        {
            end = movies[i].year;
        }
    }
    return end;
}

/* Find min score in the list */
double find_min_score(struct Movie *movies, int movieNumber)
{
    double min;
    int i;
    min = movies[0].score;

    for (i = 1; i < movieNumber; i++)
    {
        if (movies[i].score < min)
        {
            min = movies[i].score;
        }
    }
    return min;
}
/* Find max score in the list */
double find_max_score(struct Movie *movies, int movieNumber)
{
    double max;
    int i;
    max = movies[0].score;

    for (i = 1; i < movieNumber; i++)
    {
        if (movies[i].score > max)
        {
            max = movies[i].score;
        }
    }
    return max;
}
/* Take start and end year and print movies (including year) */
void print_through_year(struct Movie *movies, int start_year, int end_year, int movieNumber)
{
    int i;
    for (i = 0; movies[i].year <= end_year && i < movieNumber; i++)
    {
        if (movies[i].year >= start_year && strlen(movies[i].name) > 1)
        {
            printf("\t%d\t%s\n", movies[i].year, movies[i].name);
        }
    }
}
/* Take min and max score and print movies (including min and max score) */
void print_through_score(struct Movie *movies, double min_score, double max_score, int movieNumber)
{
    int i;
    for (i = 0; movies[i].score <= max_score && i < movieNumber; i++)
    {
        if (movies[i].score >= min_score && strlen(movies[i].name) > 1)
        {
            printf("\t%.1f\t%s\n", movies[i].score, movies[i].name);
        }
    }

}
/* Find movie if it is exist, if it is, then return index */
int find_one_movie(struct Movie *movies, int movieNumber, char *str)
{
    int i;
    for (i = 0; i < movieNumber; i++)
    {
        if (strcmp(movies[i].name, str) == 0)
        {
            return i;
        }
    }
    return FALSE;
}
/* Print IMDb average */
void print_imdb_average(struct Movie *movies, int movieNumber)
{
    double average;
    int i;
    average = 0;
    for (i = 0; i < movieNumber; i++)
    {
        average += movies[i].score;
    }
    average /= movieNumber;
    printf("\n  Average of scores is: %f\n", average);
}

/* Print genres frequence */
void frequence_of_genres(struct Movie *movies, int movieNumber)
{
    int i, j;
    int *genreCounter;

    genreCounter = calloc(genreNumber, sizeof(int));
    for (i = 0; i < genreNumber; i++)
    {
        for (j = 0; j < movieNumber; j++)
        {
            if (movies[j].genre == i)
            {
                genreCounter[i]++;
            }
        }
    }
    for (i = 0; i < genreNumber; i++)
    {
        printf("     %s\t\t%d\n", genreArray[i], genreCounter[i]);
    }
    free(genreCounter);
}

/* --------- HELPER FUNCTIONS FOR MENU --------- */

/* Get string dynamically from console
   Takes char one by one and increase size of the char array (char*) then return address of it */
char *get_string(void)
{
    char *opr;
    char *temp = NULL;
    char ch;
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
/* Returns TRUE if first operator is valid, else return FALSE */
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
/* Returns number of unknown budget movies */
int number_of_unknown(struct Movie *movies, int movieNumber)
{
    int i;
    int counter;

    for (i = 0, counter = 0; i < movieNumber; i++)
    {
        if (movies[i].budget == -1)
        {
            counter++;
        }
    }
    return counter;
}