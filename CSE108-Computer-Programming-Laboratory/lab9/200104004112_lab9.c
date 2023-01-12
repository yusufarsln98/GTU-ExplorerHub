#include <stdio.h>
#include <string.h>

/* line type struct */
typedef struct
{
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double m;

}line_t;

void part1(void)
{
    /* PART 1 find slope and then y3 */
    line_t line;

    /* Read informations */
    printf("\nPART 1\n");
    printf("\nPlease enter x1 and y1 <x1 y1>:  ");
    scanf("%lf %lf", &line.x1, &line.y1);
    printf("Please enter x2 and y2 <x2 y2>:  ");
    scanf("%lf %lf", &line.x2, &line.y2);
    printf("Please enter x3 <x3>:  ");
    scanf("%lf", &line.x3);

    line.m = (line.y2 - line.y1) / (line. x2 - line.x1);
    line.y3 = line.m * (line.x3 - line.x1) + line.y1;

    printf("m:   %f\n", line.m);
    printf("y3:  %f\n", line.y3);
}

/* Grade and student type structs */
typedef struct grade
{
    float midterm, final, homework;
}grades_t;

typedef struct student
{
    char name[30];
    unsigned int id;
    grades_t grades;
}student_t;

/* Is student exist */
int is_exist(student_t *s, unsigned int ID, int STN);


void part2(void)
{
    int index, i, STN;
    unsigned int ID;

    float favg, mavg, havg;

    printf("\nPART 2\n");
    printf("\nEnter the student number:  ");
    scanf("%d", &STN);

    student_t students[STN];

    /* Read informations */
    for (i = 0; i < STN; i++)
    {
        printf("\n\n%d. Student\n", i + 1);
        printf("-----------\n");

        printf("Name:  ");
        scanf("%s", students[i].name);
        getchar();
        
        printf("ID:  ");
        scanf("%u", &students[i].id);
        getchar();
        printf("Midterm:  ");
        scanf("%f", &students[i].grades.midterm);
        printf("Final:  ");
        scanf("%f", &students[i].grades.final);
        printf("Homework:  ");
        scanf("%f", &students[i].grades.homework);
    }

    /* Find grade averages. */
    mavg = 0; favg = 0; havg = 0;
    for (i = 0; i < STN; i++)
    {
        mavg += students[i].grades.midterm;
        favg += students[i].grades.final;
        havg += students[i].grades.homework;

    }
    printf("Midterm average:   %f\n", mavg / (double)(STN));
    printf("Final average:     %f\n", favg / (double)(STN));
    printf("Homework average:  %f\n", havg / (double)(STN));

    printf("\nEnter an ID number  ");
    scanf("%u", &ID);

    /* Find if student exist */
    index = is_exist(students, ID, STN);

    if (index == -1)
    {
        printf("\nThis student does not exist!\n");
    }
    else
    {
        printf("ID:  %u  ", ID);
        printf("Name:  %s\n", students[index].name);
    }

}

/* is student exist */
int is_exist(student_t *s, unsigned int ID, int STN)
{
    int i;
    for (i = 0; i < STN; i++)
    {
        if (ID == s[i].id)
        {
            return i;
        }
    }
    return -1;
}

/* PART 3 Definations */
#define N 10

typedef struct game
{
    char name[30];
    char platform[N][30];
    float score;

}game_t;
/* if platform does not exist then add */
int is_platform_exist(char p[N][30], char *str, int pn);

void part3(void)
{
    int GMN;
    int PLN;
    int check = 0;

    float avg;
    char platforms[N][30] = {"\0"};
    int pn = 0;

    printf("\nPART 3\n");
    printf("\nEnter the number of the game:  ");
    scanf("%d", &GMN);
    
    game_t games[GMN];

    /* Read informations */
    for (int i = 0; i < GMN; i++)
    {
        printf("%d. Game\n", i + 1);
        printf("---------\n\n");

        printf("Enter the name of the game:   ");
        scanf("%s", games[i].name);

        printf("Enter the number of the platform:  ");
        scanf("%d", &PLN);
        
        for (int j = 0; j < PLN; j++)
        {
            printf("\tEnter %d. platform:  ", j + 1);
            scanf("%s", games[i].platform[j]);

            /* add new platforms to the string array */
            check = is_platform_exist(platforms, games[i].platform[j], pn);
            if (check != -1)
            {
                strcpy(platforms[check], games[i].platform[j]);
                pn++;
            }
        }
        printf("Enter the score:  ");
        scanf("%f", &games[i].score);
    }
    avg = 0;
    for (int i = 0; i < GMN; i++)
    {
        avg += games[i].score;
    }
    printf("\n\nScore Average is %f\n", avg / (double)GMN);

    /* find platforms */
    for (int i = 0; i < pn; i++)
    {
        for (int j = 0; j < GMN; j++)
        {
            printf("%s games:  ", platforms[i]);
            for (int k = 0; k < N; k++)
            {
                if (strcmp(platforms[i], games[j].platform[k]) == 0)
                printf("%s,  ", games[j].name);
            }
            printf("\n");
        }
    }
}

/* Checks if the platform already exist or not */
int is_platform_exist(char p[N][30], char *str, int pn)
{
    for (int i = 0; i < pn; i++)
    {
        if (strcmp(p[i], str) == 0)
        {
            return -1;
        }
    }
    return pn;
}

int main()
{
    //part1();
    //part2();
    part3();
    return 0;
}