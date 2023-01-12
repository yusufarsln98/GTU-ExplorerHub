#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 20
#define OUTFILE "outfile.txt"

/* Struct Definations */
typedef struct country_t
{
    char country[N];
    char capital[N];
    int population;
    bool driving_side;

} country_t;

typedef struct country_l
{
    char country[N];
    char capital[N];
    int population;
    bool driving_side;
    struct country_l *next;
} country_l;

int main()
{
    country_t *countries = NULL;                        /* Array */
    country_l *countries_l = NULL, *new_node, *head;    /* Linked list and new node */
    int opt, temp;                                      /* Initiliaze */
    int country_number = 0, i;
    char buffer[20];
    FILE *infile, *outfile;

    do
    {
        /* Ask for operations */
        printf("1-\tEnter new record\n");
        printf("2-\tWrite to the file\n");
        printf("3-\tRead from file\n");
        printf("4-\tPrint linked list\n");
        printf("5-\tExit\n");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1: 
        {
            /* Increase country_number one by one in each new record */
            printf("Your choce is 1\n");
            country_number++;
            /* Reallocate struct array */
            countries = realloc(countries, country_number * sizeof(country_t));

            /* Take the informations */
            printf("Country name: ");
            scanf("%s",countries[country_number - 1].country);
            printf("Capital: ");
            scanf("%s",countries[country_number - 1].capital);
            printf("Population of %s: ", countries[country_number - 1].country);
            scanf("%d", &countries[country_number - 1].population);
            printf("Do people on %s drive on the right side? (yes = 1, no = 0): ", countries[country_number - 1].country);
            scanf("%d", &temp);
            countries[country_number - 1].driving_side = temp;
            break;
        }
        case 2:
        {
            /* Create a file with array elements */
            printf("Your choce is 2\n");
            outfile = fopen(OUTFILE, "w");
            if (outfile == NULL)
            {
                exit(1);
            }

            /* print informatin in the array to a outfile */
            for (i = 0; i < country_number; i++)
            {
                fprintf(outfile, "%s ", countries[i].country);
                fprintf(outfile, "%s ", countries[i].capital);
                fprintf(outfile, "%d ", countries[i].population);
                if (countries[i].driving_side == 1)
                {
                    fprintf(outfile, "%s\n", "Right");
                }
                else
                {
                    fprintf(outfile, "%s\n", "Left");
                }
            }
            fclose(outfile);
            break;
        }
        case 3:
        {
            /* Read created file in previous step */
            printf("Your choce is 3\n");
            infile = fopen(OUTFILE, "r");
            if (infile == NULL)
            {
                exit(1);
            }
            /* Create new nodes and add them to the a linked list */
            for (i = 0; i < country_number; i++)
            {
                new_node = malloc(sizeof(country_l));
                fscanf(infile, "%s", new_node->country);
                fscanf(infile, "%s", new_node->capital);
                fscanf(infile, "%d", &new_node->population);
                fscanf(infile, "%s", buffer);
                if (strcmp(buffer, "Right") == 0)
                {
                    new_node->driving_side = 1;
                }
                else
                {
                    new_node->driving_side = 0;
                }
                new_node->next = NULL;
                if (countries_l == NULL)
                {
                    countries_l = new_node;
                }
                else
                {
                    new_node->next = countries_l;
                    countries_l = new_node;
                }
            }
            country_number = 0;
            fclose(infile);
            break;
        }
        case 4:
        {
            /* Print information in linked list */
            printf("Your choce is 4\n");
            head = countries_l;

            /* Until the end of the list, print information to the terminal */
            while (head != NULL)
            {
                printf("Country: %20s    Capital: %20s    Population: %-20d", head->country, head->capital, head->population);
                if (head->driving_side == 1)
                {
                    printf("Driving side: Right\n");
                }
                else
                {
                    printf("Driving side: Left\n");
                }
                head = head->next;
            }
            break;
        }
        case 5:
            printf("Program has been terminated! Have a good day\n");
            break;
        default:
            printf("Try Again\n");
        }

    } while (opt != 5);
    return 0;
}