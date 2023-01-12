/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
This file will contain your implementation of the functions declared in the associated header file. 
The details of these functions’ behaviors are provided below.
*/


#include <stdio.h>
#include "hw1_io.h"


/* 
** Functions for prints polynomial in correct format and make code more compatible. 
**
*/
void print_leading(double, int);
void print_middle(double ,int);
void print_a1(double);
void print_a0(double);

/* Writes polynomial in an pretty format. i.e: -x^3+x^2-3.2x */
void write_polynomial3(double a0, double a1, double a2, double a3) 
{
    print_leading(a3, 3);       /* Prints leading coefficient in correct format.*/
    print_middle(a2, 2);        /* Prints middle coefficients in correct format.*/
    print_a1(a1);               /* Prints coefficient a1 in correct format.*/
    print_a0(a0);               /* Prints coefficient a0 in correct format.*/
}

/* writes polynomial in an pretty format. i.e: x^4-x^3+x^2-3.2x */
void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
    print_leading(a4, 4);       /* Prints leading coefficient in correct format.*/
    print_middle(a3, 3);        /* Prints middle coefficients in correct format.*/
    print_middle(a2, 2);        /* Prints middle coefficients in correct format.*/
    print_a1(a1);               /* Prints coefficient a1 in correct format.*/
    print_a0(a0);               /* Prints coefficient a0 in correct format.*/            

}

void print_leading(double c, int d) /* Leading coefficient. (c is coefficient, d is degree.)*/
{
    int check;              /* Going to start an integer to check if coefficients has floating points.*/
    check = c * 10;               

    if (c == 1)         /* If coefficient is 1*/
    {
        printf("x^%d", d);
    }
    else if (c == -1)   /* If coefficient is -1*/
    {
        printf("-x^%d", d);
    }
    else if (c != 1 && c != -1 && (check % 10 == 0))    /* If coefficient is neither 1 nor -1 and not floating point*/    
    {
        printf("%.fx^%d", c, d);
    }
    else if ((check % 10 != 0))                         /* If coefficient is neither 1 nor -1 but has floating point*/   
    {
        printf("%.1fx^%d", c, d);
    }    
}

void print_middle(double c, int d)  /* Middle coefficients. (c is coefficient, d is degree.)*/
{
    int check;
    check = c * 10;

    if (c == 1 && c != 0)
    {
        printf("+x^%d", d);
    }
    else if (c == -1 && c != 0)
    {
        printf("-x^%d", d);
    }
    else if ((check % 10 == 0) && (c != 1 && c != -1 && c != 0))
    {
        printf("%+.fx^%d", c, d);   /* %+f/d... is the short way to display numbers with their sign. */
    }
    else if ((check % 10 != 0) && (c != 1 && c != -1 && c != 0))
    {
        printf("%+.1fx^%d", c, d);
    }
}
void print_a1(double c)         /* Coefficient a1. (c is coefficient, d is degree.)*/
{
    int check;
    check = c * 10;

    if (c == 1 && c != 0)
    {
        printf("+x");
    }
    else if (c == -1 && c!= 0)
    {
        printf("-x");
    }
    else if ((check % 10 == 0) && c != 0)
    {
        printf("%+.fx", c);
    }
    else if ((check % 10 != 0) && c != 0)
    {
        printf("%+.1fx", c);
    }
}
void print_a0(double c)         /* Coefficient a0. (c is coefficient, d is degree.)*/
{
    int check;
    check = c * 10;  

    if ((check % 10 == 0) && c != 0)
    {
        printf("%+.f\n", c);
    }
    else if ((check % 10 != 0) && c != 0)
    {
        printf("%+.1f\n", c);
    }
}

