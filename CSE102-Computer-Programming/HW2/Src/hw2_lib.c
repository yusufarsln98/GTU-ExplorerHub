/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
/* acos() for triangle function */
#include <math.h>
/* exit(1) for finish the program when user enters wrong input*/
#include <stdlib.h>

#include "hw2_lib.h"
#define INITIAL_YEAR 0

/* Stores number of days for 1 year to find total day. Starts with January (February will changes acording to year) */
int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/* Stores number of days for 1 year to control if date is available. Starts with January (February will changes acording to year) */
int arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

int find_total_day(int day, int month, int year);   /* Calculates total day from 1 - 1 - 0000 to entered date */
void is_date_exist(int day, int month, int year);   /* Controls if date is exist or not */

void is_triangle_exist (double a, double b, double c);  /* Controls if triangle can be drawn with entered values */

void print_border(char);    /* Prints borders entered as a parameter */
void print_rowLine(char);   /* Prints rows lines with - */

/*
    Fundemental of my code is;
    I calculated total days between 1-1-0000 to entered date with a function,
    -find_total_day-
    Since I know this date is correspond to saturday (There is not such date, I've calculated and determined), 
    thanks to it we can find
    which day is that entered date.

    Also with same function -find_total_day- we can calculate
    number of days between 2 date. 
    ie: from 1-1-0000 to start_date is = A
        from 1-1-0000 to end_date is = B
    difference = B - A;

*/

/* Finds day of the week */
int find_weekday_of_data(int day, int month, int year)
{
    /* https://www.timeanddate.com/calendar/?year=1&country=22 */
    
    /*  On the websites I link to, the calendar is based on the Gregorian calendar.
    Since I solve both functions with the total day function, 
    the results of week of day and count day functions are expected to be consistent. 
    Because some comparison sites accept 1.1.0000 00:00 according to the hemisphere 
    in which they are located, the results may be deviated for 1 day on other sites.
    */
    
    int total_day;      /* Keeps data of total day from 1-1-0000 to entered date*/
    int current_day;    /* Keeps data of current day */
    
    is_date_exist(day, month, year);    /* Control if date is exist */
        
	total_day = find_total_day(day, month, year);   /* Calculates number of week compare with 1/1/0000, Monday */
    
    current_day = ((total_day % 7 + 6) % 7);    /* Calculates number of week compare with 1/1/0000, Monday */
    /* Returns day of the week */
    if (current_day == 0)
    {
        return 7;
    }
    else
    {
        return current_day;  
    }
   
}

/* Calculates days between start date and end date */
int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
    /* https://ncalculators.com/time-date/date-difference-calculator.htm */

    /*  On the websites I link to, the calendar is based on the Gregorian calendar.
    Since I solve both functions with the total day function, 
    the results of week of day and count day functions are expected to be consistent. 
    Because some comparison sites accept 1.1.0000 00:00 according to the hemisphere 
    in which they are located, the results may be deviated for 1 day on other sites.
    */

    int up_to_start;    /* Keeps days between 1-1-0000 and start date */
    int up_to_end;      /* Keeps days between 1-1-0000 and end date */

    is_date_exist(start_day, start_month, start_year); /* Control if date is exist */ 
    is_date_exist(end_day, end_month, end_year);       /* Control if date is exist */    


    up_to_start = find_total_day(start_day, start_month, start_year);   /* Calculates days between 1-1-0000 and start date */
    up_to_end = find_total_day(end_day, end_month, end_year);           /* Calculates days between 1-1-0000 and end date */

    return (up_to_end - up_to_start);   /* Returns result */
                                            
}


double find_angle(double a, double b, double c)
{
    double edge1, edge2;        /* Edge of triangle which aligned to angle */
    double median1, median2;    /* Medians of main triangle */
    double cosx;                /* cos value of angle */    
    double alfa_angle;          /* Will store data of angle */

    is_triangle_exist(a, b, c); /* Controls of triangle can be drawn */

    /* 2V^2 = b^2 + c^2 - a^2/2 
       Median theorem            */
    median1 = sqrt((a * a + b * b - (c * c) / 2) / 2);
    median2 = sqrt((a * a + c * c - (b * b) / 2) / 2);

    /* Edges of triangle alfa is 2 of 3 part of median */
    edge1 = 2 * median1 / 3;
    edge2 = 2 * median2 / 3;
    
    /* Cosinus theorem: a^2 = b^2 + c^2 - 2 * b * c * cos(x) */
    cosx = (edge1 * edge1 + edge2 * edge2 - a * a) / (2 * edge1 *edge2);
    /* acos(cosx) will give us degree as radian */
    alfa_angle = acos(cosx);

    
    return alfa_angle;  /* Returns alfa_angle */
}

/* 
   Fundemental of my code:
   I give areas to variables bounded by spaces (ie: %-7c%-5d%-3c). 
   Then I make this variables move as indicated areas (%-5d).
   In this example, my integer variable has 5 digits which able to
   locate and move inside of. (According to instructions).
   But there is different instructions, it caused a lot of condition.
*/

/* Epic of Gilgamesh */
void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{

    char vrtEdge = '|';     /* Vertical bounder character */
    char blank = ' ';       /* It stores blank to place it where needed. */
    char h1[8] = "Row 101", h2[12] = "Row ABCDEFG", h3[11] = "Row XYZ123";

    /* Upper border */
    printf("\n");
    printf("┌");
    print_border(border);   /* Prints border according to user input (*, -) */
    printf("┐");

    /* 1st Row */
    printf("\n");
    printf("%c", vrtEdge);
    printf("%11s%4c|%13s%2c|%13s", h1, blank, h2, blank, h3);
    printf("%4c", vrtEdge);
    
    print_rowLine(border);    /* Draw a line between rows */

    /* 2nd Row */
    printf("\n");
    printf("%c", vrtEdge);  
    
    /* First conditions for digits number of unsiged integers*/
    if (r11 >= 1 && r11 <= 9)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r12 * 100) % 10 != 0)
        {
            printf("%-7c%-5d%-3c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r12 * 10) % 10 != 0)
            {
                printf("%-7c%-5d%-3c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
            }
            else
            {
                printf("%-7c%-5d%-3c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
            }
        } 
    }
    /* First conditions for digits number of unsiged integers*/
    else if (r11 >= 10 && r11 <= 999)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r12 * 100) % 10 != 0)
        {
            printf("%-6c%-5d%-4c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r12 * 10) % 10 != 0)
            {
                printf("%-6c%-5d%-4c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
            }
            else
            {
                printf("%-6c%-5d%-4c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
            }
        }

    }
    /* First conditions for digits number of unsiged integers*/
    else if (r11 >= 1000 && r11 <= 99999)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r12 * 100) % 10 != 0)
        {
            printf("%-5c%-5d%-5c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r12 * 10) % 10 != 0)
            {
                printf("%-5c%-5d%-5c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
            }
            else
            {
                printf("%-5c%-5d%-5c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r11, blank, vrtEdge, blank, r12, blank, vrtEdge, blank, r13, blank);
            }
        }
    }
    printf("%c", vrtEdge);

    print_rowLine(border);    /* Draw a line between rows */

    /* 3rd Row */
    printf("\n");
    printf("%c", vrtEdge);

    /* First conditions for digits number of unsiged integers*/
    if (r21 >= 1 && r21 <= 9)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r22 * 100) % 10 != 0)
        {
            printf("%-7c%-5d%-3c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r22 * 10) % 10 != 0)
            {
                printf("%-7c%-5d%-3c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
            }
            else
            {
                printf("%-7c%-5d%-3c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
            }
        }    
    }

    /* First conditions for digits number of unsiged integers*/
    else if (r21 >= 10 && r21 <= 999)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r22 * 100) % 10 != 0)
        {
            printf("%-6c%-5d%-4c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
        }
        else
        {
           /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
           if ((int)(r22 * 10) % 10 != 0)
           {
               printf("%-6c%-5d%-4c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank); 
           }
           else
           {
               printf("%-6c%-5d%-4c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank); 
           }
        }
    }
    /* First conditions for digits number of unsiged integers*/
    else if (r21 >= 1000 && r21 <= 99999)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r22 * 100) % 10 != 0)
        {
            printf("%-5c%-5d%-5c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r22 * 10) % 10 != 0)
            {
                printf("%-5c%-5d%-5c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
            }
            else
            {
                printf("%-5c%-5d%-5c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r21, blank, vrtEdge, blank, r22, blank, vrtEdge, blank, r23, blank);
            }
        }
    }    
    printf("%c", vrtEdge);

    print_rowLine(border);    /* Draw a line between rows */
    
    /* 4th Row */
    printf("\n");
    printf("%c", vrtEdge);
    
    /* First conditions for digits number of unsiged integers*/
    if (r31 >= 1 && r31 <= 9)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r32 * 100) % 10 != 0)
        {
            printf("%-7c%-5d%-3c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r32 * 10) % 10 != 0)
            {
                printf("%-7c%-5d%-3c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
            }
            else
            {
                printf("%-7c%-5d%-3c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
            }
        }
        
    }
    /* First conditions for digits number of unsiged integers*/
    else if (r31 >= 10 && r31 <= 999)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r32 * 100) % 10 != 0)
        {
            printf("%-6c%-5d%-4c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r32 * 10) % 10 != 0)
            {
                printf("%-6c%-5d%-4c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
            }
            else
            {
                printf("%-6c%-5d%-4c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
            }
        }
    }
    /* First conditions for digits number of unsiged integers*/
    else if (r31 >= 1000 && r31 <= 99999)
    {
        /* 2nd conditions for doubles. Controls if its 2nd decimal digits has 0 or not */
        if ((int)(r32 * 100) % 10 != 0)
        {
            printf("%-5c%-5d%-5c%-c%-2c%-11.2f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
        }
        else
        {
            /* 3rd conditions for doubles. Control if its 1st and 2nd decimal digits are 0 or not */
            if ((int)(r32 * 100) % 10 != 0)
            {
                printf("%-5c%-5d%-5c%-c%-2c%-11.1f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
            }
            else
            {
                printf("%-5c%-5d%-5c%-c%-2c%-11.0f%-2c%-c%-3c%-+7d%-6c", blank, r31, blank, vrtEdge, blank, r32, blank, vrtEdge, blank, r33, blank);
            }

        }
    }  
    printf("%c", vrtEdge);
    
    /* Lower border */
    printf("\n");
    printf("└");
    print_border(border);   /* Prints border according to user input (*, -) */
	printf("┘\n\n");
    
}

/* Returns number of total day between 1-1-0000 to given date */
int find_total_day(int day, int month, int year)
{
    int i;
    int total_day = 0;
    int month_day = 0;

    /* It calculates approximately how many days have passed until the year entered. 
       Leap years going to add later. */
    total_day = (year - INITIAL_YEAR) * 365 + (day - 1);
	
    /* It collects the days to come from the months. */
    for(i = 0; i < (month - 1); i++)
    {
        month_day = month_day + months[i];
    }
    /* Adds this days as total day. */
    total_day = total_day + month_day;

    /* Leap days are added. Missing days in 100 years are removed, exceptions in 400 years are added. */
    total_day = total_day + (year / 4) + 1 - ((year - 1) / 100) + ((year - 1) / 400);

    /* In the years divided by 4, an extra day is added to this total. 
       Condition to remove this extra day in the months before March. */
    if ((year % 4) == 0 && month < 3)
    {
        /* Returns number of total day between 1-1-0000 to given date */
        return (total_day - 1);
    }
	else 
	{
		/* Returns number of total day between 1-1-0000 to given date */
        return total_day;
	}
}

/* Controls according to calander if there is such a date */
void is_date_exist(int day, int month, int year)
{
    /* Change days of months to with correct ones. */
    if (year % 4 == 0)
    {
        arr[1] = 29;
    }
    if (year % 100 == 0)
    {
        arr[1] = 28;
    }
    if (year % 400 == 0)
    {
        arr[1] = 29;
    }

    /* If there is not such a date, then exit the program */ 
    if (day < 0 || (day > arr[month - 1]))
    {
        printf("\nERROR! Enter a correct date!!!\n\n");
        exit(1);
    }
    else if (month < 1 || month > 12)
    {
        printf("\nERROR! Enter a correct date!!!\n\n");
        exit(1);
    }
    else if (year < 0)
    {
        printf("\nERROR! Enter a correct date!!!\n\n");
        exit(1);
    }
}

/* Controls if triangle can be drawn by given paramters */
void is_triangle_exist(double a, double b, double c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        printf("\nERROR! Edges can not be neither negative nor zero.\n");
        exit(1);
    }
    
    if ((a >= b + c) || (b >= a + c) || (c >= a + b))
    {
        printf("\nERROR! Length of an edge should be shorter then sum of other 2 edge.\n\n");
        exit(1);
    }
}

/* Prints borders according to given parameter */
void print_border(char border)
{
    int i;
    for (i = 0; i < 48; i++)
    {
    	printf("%c", border);
	}
}

/* Prints rows with '-'. Also puts lines */
void print_rowLine(char border)
{   
    int i;
    char vrtEdge = '|';
    printf("\n");
    printf("%c", vrtEdge);

    for (i = 0; i < 48; i++)
    {
        if (i == 15 || i == 31)
        {
        	printf("|");
        }
        else
        {
            printf("%c", border);
        }
    }
    printf("%c", vrtEdge);
}
