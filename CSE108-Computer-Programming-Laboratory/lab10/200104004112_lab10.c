#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defining struct */
typedef struct book
{
    char *title;
    char *author;
    char *subject;
    int year;

}book_t;

void resize_array(void);        /* Resizes array with adding new book. */
void get_newbook(book_t *nb);   /* Get new book from user and return it as an argument. */
char *get_string(void);         /* Get string from console */
void list_books(void);          /* Submenu */
int is_book_exist(char *str);   
int is_author_exist(char *str);
int is_subject_exist(char *str);
void sort_by_year(void);

/* Globally define array and counter */
book_t *Books;
int counter;

int main(void)
{
    /* Initiliazers */
    int opt;
    book_t newBook;
    
    /* Main menu and resizing  */
    while (1)
    {
        printf("\nMENU\n");
        printf("\t1. Add New Book\n\t2. List Books\n\t3. Exit\n");
        printf("Choose:   ");
        scanf("%d", &opt);
        getchar();

        if (!(opt == 3 || opt == 1 || opt == 2))
        {
            printf("\nInvalid Enter! Try Again.\n");
        }
        if (opt == 3)
        {
            break;
        }
        else if (opt == 1)
        {
            counter++;
            resize_array();
            get_newbook(&newBook);
            Books[counter - 1] = newBook;
        }
        else if (opt == 2)
        {
            list_books();
        }
        
    }
    /* Free chars inside then all struct array. */
    for (int i = 0; i < counter; i++)
    {
        free(Books[i].author);
        free(Books[i].title);
        free(Books[i].subject);
    }
    free(Books);
    return 0;
}

/* Resize struct array */
void resize_array(void)
{
    book_t *temp;
    temp = Books;
    Books = (book_t *)calloc(counter, sizeof(book_t));
    for (int i = 0; i < counter - 1; i++)
    {
        Books[i] = temp[i];
    }
    free(temp);
}
/* Get new book and return it as an argument */
void get_newbook(book_t *nb)
{
    printf("Please enter book title:  ");
    nb->title = get_string();
    fflush(stdin);

    printf("Please enter book author:  ");
    nb->author = get_string();
    fflush(stdin);

    printf("Please enter book subject:  ");
    nb->subject = get_string();
    fflush(stdin);

    printf("Please enter book year:  ");
    scanf("%d", &nb->year);
    getchar();
}

/* Get string from the console */
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

/* Sub menu */
void list_books(void)
{
    int subObt;
    char *buffer;
    int Check;

    if (counter == 0)
    {
        printf("\nThere is not any book in the list!\n\n");
        return;
    }

    printf("\n==================================\n\n");
    

    while (1)
    {
        printf("SUBMENU\n\n");
        printf("---------------------------------\n");
        printf("\n\t1. Get By Title\n\t2. Get By Author\n\t3. Get By Subject\n\t4. Sorted List By Year\n\t5. List All Books\n\t6. Exit SUBMENU\n\n");
        printf("Choose:   ");
        scanf("%d", &subObt);
        getchar();

        if (!(subObt == 1 || subObt == 2 || subObt == 3 || subObt == 4 || subObt == 5 || subObt == 6))
        {
            printf("\nInvalid Enter! Try Again.\n");
        }
        if (subObt == 6)
        {
            return;
        }
        else if (subObt == 1)
        {
            /* Read books title and find if it is exist. If do, print informations. */
            printf("Enter a books title:   ");
            buffer = get_string();
            fflush(stdin);
            Check = is_book_exist(buffer);
            if (Check == -1)
            {
                printf("\nThis book does not exist!\n");
                free(buffer);
            }
            else
            {
                printf("\nBook found!\n");
                printf("------------\n\n");
                printf("Title:    %s\n", Books[Check].title);
                printf("Author:   %s\n", Books[Check].author);
                printf("Subject:  %s\n", Books[Check].subject);
                printf("Year:     %d\n", Books[Check].year);
                free(buffer);
            }
        }
        else if (subObt == 2)
        {
            /* Read books author and find if it is exist. If do, print informations. */
            printf("Enter a books author:   ");
            buffer = get_string();
            fflush(stdin);
            Check = is_author_exist(buffer);
            if (Check == -1)
            {
                printf("\nThis book does not exist!\n");
                free(buffer);
            }
            else
            {
                printf("\nBook found!\n");
                printf("------------\n\n");
                printf("Title:    %s\n", Books[Check].title);
                printf("Author:   %s\n", Books[Check].author);
                printf("Subject:  %s\n", Books[Check].subject);
                printf("Year:     %d\n", Books[Check].year);
                free(buffer);
            }
        }
        else if (subObt == 3)
        {
            /* Read books subjects and find if it is exist. If do, print informations. */
            printf("Enter a books subject:   ");
            buffer = get_string();
            fflush(stdin);
            Check = is_subject_exist(buffer);
            if (Check == -1)
            {
                printf("\nThis book does not exist!\n");
                free(buffer);
            }
            else
            {
                printf("\nBook found!\n");
                printf("------------\n\n");
                printf("Title:    %s\n", Books[Check].title);
                printf("Author:   %s\n", Books[Check].author);
                printf("Subject:  %s\n", Books[Check].subject);
                printf("Year:     %d\n", Books[Check].year);
                free(buffer);
            }
        }
        else if (subObt == 4)
        {
            /* List of all books sorted by year. */
            sort_by_year();
            printf("\nList of books\n");
            printf("---------------\n\n");

            for (int i = 0; i < counter; i++)
            {
                printf("%d. Book\n", i + 1);
                printf("------------\n\n");
                printf("Title:    %s\n", Books[i].title);
                printf("Author:   %s\n", Books[i].author);
                printf("Subject:  %s\n", Books[i].subject);
                printf("Year:     %d\n", Books[i].year);
            }
        }
        else if (subObt == 5)
        {
            /* List of all entered books. */
            for (int i = 0; i < counter; i++)
            {
                printf("%d. Book\n", i + 1);
                printf("------------\n\n");
                printf("Title:    %s\n", Books[i].title);
                printf("Author:   %s\n", Books[i].author);
                printf("Subject:  %s\n", Books[i].subject);
                printf("Year:     %d\n", Books[i].year);
            }
        }
    }
}
/* Checks string with titles and return index if find the book. */
int is_book_exist(char *str)
{
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(Books[i].title, str) == 0)
        {
            return i;
        }
    }
    return -1;
}
/* Checks string with authors and return index if find the book. */
int is_author_exist(char *str)
{
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(Books[i].author, str) == 0)
        {
            return i;
        }
    }
    return -1;  
}

/* Checks string with subjects and return index if find the book. */
int is_subject_exist(char *str)
{
    for (int i = 0; i < counter; i++)
    {
        if (strcmp(Books[i].subject, str) == 0)
        {
            return i;
        }
    }
    return -1; 
}

/* Selection sorting by year. */
void sort_by_year(void)
{
    book_t temp_book;
    int i, j, max;

    for (i = 0; i < counter-1; i++)
    {
        max = i;
        for (j = i + 1; j < counter; j++)
        {
            if (Books[j].year > Books[max].year)
            {
                max = j;
            }
        }
        temp_book = Books[max];
        Books[max] = Books[i];
        Books[i] = temp_book;
    }
}