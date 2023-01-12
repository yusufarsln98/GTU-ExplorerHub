/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
This file will contain your implementation of the functions declared in the associated header file. 
The details of these functions’ behaviors are provided below.
*/

#include <stdio.h>
#include <math.h>
#include "hw1_lib.h"

double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
    int i;                          /* Initial to loop */ 
    int n;                          /* Number of steps, we assume that n is multiple of delta */
    double rt_width = delta;        /* Rectangle width */
    double rt_height;               /* Rectangle height */
    double rectangle_area = 0.0;    
    double sum = 0.0;
    
    n = (xe - xs) / delta;          /* Calculates number of steps */

    for (i = 0; i < n; i++)
    {
        rt_height = ((a3 * xs + a2) * xs + a1) * xs + a0;   /* Calculates height of rectangles for each step */
        sum = sum + rt_height;                              /* Calcuates sum of height of each rectangle */
        xs = xs + delta;                                    /* Shifts letf corner of rectangle to rigth by delta*/
    }
    return sum * delta;                                     /* Returns integral */
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
    int i;                          /* Initial to loop */    
    int n;                          /* Number of steps, we assume that n is multiple of delta */
    double rt_width = delta;        /* Rectangle width */
    double rt_height;               /* Rectangle height */
    double rectangle_area = 0.0;    
    double sum = 0.0;
    
    n = (xe - xs) / delta;          /* Calculates number of steps */

    for (i = 0; i < n; i++)
    {
        rt_height = (((a4 * xs + a3) * xs + a2) * xs + a1) * xs + a0;   /* Calculates vertical length of rectangles. */
        sum = sum + rt_height;                                          /* Calcuates sum of height of each rectangle */
        xs = xs + delta;                                                /* Shifts letf corner of rectangle to rigth by delta*/
    }
    return sum * delta;             /*Returns integral */ 
}

/* ** Newton Metodunda başlangıç değerinin olduğu noktanın türevi alınıp eğimi bulunur.
   ** Başlangıç noktası, fonksiyonun başlangıç noktasındaki değeri ve türevinin değeri(eğimi) ile bir doğru çizilir.  
   ** Bu doğrunun koordinat düzleminde x'i kestiği nokta kök(root) adayımızdır. 
   ** Bu kök adayı bir değişkene kaydedilip işlem başa alınır. Bu şekilde ilerleyerek doğrunun kökten geçmesi sağlanır.
   ** Döngü son kök adayı ile bir önceki kök adayının aynı sayı olduğu zamana kadar devam eder.
   ** Kaynak: Wikipedia, youtube.com/buders */

double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
    double xi;
    double xii;
    double fxi;
    double slope;
    double difference;

    /* ** According to Newton's Method to calculate root of an polynomial we need a initial value.
       ** Most proper initial value is lower boundary. */

    xi = xs; 

    do
    {
        fxi = ((a3 * xi + a2) * xi + a1) * xi + a0;                 /* Value of f(x initial) */
        slope = (3 * a3 * xi + 2 * a2) * xi + a1;                   /* Slope of line */
        xii = (slope * xi - fxi) / slope;                           /* Newton's Method formula */
        difference = fabs(xi - xii);                                /* Difference with last value with one before it */
        xi = xii;                                                   /* To compare initial value with changed value */

    } while (difference != 0);                                      /* Condition for break the loop and return root */
    
    return xi;
}


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{
    double xi;
    double xii;
    double fxi;
    double slope;
    double difference;

    xi = xs;

    do
    {
        fxi = (((a4 * xi + a3) * xi + a2) * xi + a1) * xi + a0;         /* Value of f(x initial) */
        slope = ((4 * a4 * xi + 3 * a3 * xi) * xi + 2 * a2) * xi + a1;  /* Slope of line */
        xii = (slope * xi - fxi) / slope;                               /* Newton's Method formula */
        difference = fabs(xi - xii);                                    /* Difference with last value with one before it */
        xi = xii;                                                       /* To compare initial value with changed value */
    
    } while (difference != 0);                                          /* Condition for break the loop and return root */
    
    return xi;
}
