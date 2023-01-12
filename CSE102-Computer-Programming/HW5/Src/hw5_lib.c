/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include <math.h>
#include "hw5_lib.h"

/* Part1 - Polynomial. */
void pol_addition(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0);
void pol_substriction(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0);
void pol_multiplication(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0);

/* Part3 - Dhondt Method */
#define TRUE 1
#define FALSE 0

/* Part4 - Counter clockwise */
int find_location(double *p1, double *p2);
double find_precedence(double *p1, double *p2, int area);
void swap_points(double *x_1, double *y_1, double *x_2, double *y_2);

/* Makes code more readible. Not more */
#define ORIGIN 0	
#define AREA_1 1	
#define AREA_2 2	
#define AREA_3 3	
#define AREA_4 4	
#define ON_PY 5
#define ON_NY 6

/* Part5 -  */
void swap_chars(char *c1, char *c2);

/* Lib.c functions. */
void operate_polynomials(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	/* Take the operator and according to it call function by references */
	switch (op)
	{
	case '+':
		pol_addition(a3, a2, a1, a0, b3, b2, b1, b0);
		break;
	case '-':
		pol_substriction(a3, a2, a1, a0, b3, b2, b1, b0);
		break;
	case '*':
		pol_multiplication(a3, a2, a1, a0, b3, b2, b1, b0);
		break;
	}
}


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	int i;                                          /* Counter */
    double d0, d1, d2, d3, euclidian_distance = 0;  /* d0, d1..  Keeps the vector dimentions. */
    double temp0, temp1, temp2, temp3;              /* Temporarily keeps the vector dimensions. */   
    double dif0, dif1, dif2, dif3;                  /* Difference of last to entered vector. */

    i = 0;  /* Start counter from 0 */
    printf("\n************ EUCLIDAN 4D VECTOR ************\n");
    
    /* Loop till counter less then N(from main (default)) */
    while (i < N)
    {
        printf("\nEnter dimensions of %d. 4D vector <a.bc d.ef ...>\n(To stop loop enter <-1 -1 -1 -1>): ", i + 1);
        scanf("%lf %lf %lf %lf", &d0, &d1, &d2, &d3);       

        if (d0 == -1 && d1 == -1 && d2 == -1 && d3 == -1)   /* If user enter -1 -1 -1 -1, then break the loop. */
        {
            printf("\n");
            break;
        }
        if (i == 0) /* In first iteration keeps the vector in the temp variables. */
        {
            temp0 = d0;
            temp1 = d1;
            temp2 = d2;
            temp3 = d3;
        }
        else        /* In the other iterations, take the diffrence between last 2 vector and pass them into the distance function. */
        {
            dif0 = d0 - temp0;
            dif1 = d1 - temp1;
            dif2 = d2 - temp2;
            dif3 = d3 - temp3;

            distance_between_4d_points (dif0, dif1, dif2, dif3, &euclidian_distance);        
            printf("\nDifference between last two vector is: %.2f\n", euclidian_distance);

            temp0 = d0;
            temp1 = d1;
            temp2 = d2;
            temp3 = d3;
        }

        if (euclidian_distance > *longest_distance)
        {
            *longest_distance = euclidian_distance;
        }

        /* Sum of vector dimentions. */
        *mean_a0 += d0; 
        *mean_a1 += d1;
        *mean_a2 += d2;
        *mean_a3 += d3;

        i++;
    }
    /* Take the avarage of vectors. */
    *mean_a0 /= i;
    *mean_a1 /= i;
    *mean_a2 /= i;
    *mean_a3 /= i;
}


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
    *euclidian_distance = sqrt((d0 * d0 + d1 * d1 + d2 * d2 + d3 * d3)); /* Euclidian distance formula. */
}


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
    int i;
    int voteA, voteB, voteC, voteD, voteE;  /* Saves the first time entered votes. */
    int largest_vote;                       /* Keeps the largest vote. */
    int flagA, flagB, flagC, flagD, flagE;  /* Keeps the which vote is the largest during the iteration. */ 
    int seatA, seatB, seatC, seatD, seatE;  /* Number of seats. */
    int divideA, divideB, divideC, divideD, divideE;

    printf("\n************ DHONDT METHOD ************\n\n");

    /* Initial values according to the formula. */
    seatA = 0, 
    seatB = 0, 
    seatC = 0, 
    seatD = 0, 
    seatE = 0;
    
    divideA = 2,
    divideB = 2, 
    divideC = 2, 
    divideD = 2, 
    divideE = 2;

    /* Saves the first time entered votes. (According to the formula) */
    voteA = *partyA;
    voteB = *partyB;
    voteC = *partyC;
    voteD = *partyD;
    voteE = *partyE;

    /* Iteration for find largest vote and implement the formula. */
    for (i = 0; i < numberOfSeats; i++)
    {
        largest_vote = 0;
        flagA = FALSE,
        flagB = FALSE,
        flagC = FALSE,
        flagD = FALSE,
        flagE = FALSE;

        /* Find largest vote. */
        if (voteA > largest_vote)
        {
            largest_vote = voteA;
            flagA = TRUE;
        }
        if (voteB > largest_vote)
        {
            largest_vote = voteB;
            flagB = TRUE;
            flagA = FALSE;
        }
        if (voteC > largest_vote)
        {
            largest_vote = voteC;
            flagC = TRUE;
            flagA = FALSE;
            flagB = FALSE;
        }
        if (voteD > largest_vote)
        {
            largest_vote = voteD;
            flagD = TRUE;
            flagA = FALSE;
            flagB = FALSE;
            flagC = FALSE;
        }
        if (voteE > largest_vote)
        {
            largest_vote = voteE;
            flagE = TRUE;
            flagA = FALSE;
            flagB = FALSE;
            flagC = FALSE;
            flagD = FALSE;
        }

        /* Apply the Dhondt Method to the biggest vote. */
        if (flagA == TRUE)              /* If A-Party has largest vote */
        {
            voteA = *partyA / divideA;  /* Apply the formula. */  
            seatA++;                    /* Increase seats */
            divideA++;                  /* Increase divider. */
        }
        else if (flagB == TRUE)         /* If B-Party has largest vote */
        {
            voteB = *partyB / divideB;  /* Apply the formula. */ 
            seatB++;                    /* Increase seats */
            divideB++;                  /* Increase divider. */     
        }
        else if (flagC == TRUE)         /* If C-Party has largest vote */
        {
            voteC = *partyC / divideC;  /* Apply the formula. */
            seatC++;                    /* Increase seats */
            divideC++;                  /* Increase divider. */
        }
        else if (flagD == TRUE)         /* If D-Party has largest vote */
        {
            voteD = *partyD / divideD;  /* Apply the formula. */
            seatD++;                    /* Increase seats */
            divideD++;                  /* Increase divider. */
        }
        else if (flagE == TRUE)         /* If E-Party has largest vote */
        {
            voteE = *partyE / divideE;  /* Apply the formula. */
            seatE++;                    /* Increase seats */
            divideE++;                  /* Increase divider. */
        }
    }
    
    /* Return by pointer. */
    *partyA = seatA;
    *partyB = seatB;
    *partyC = seatC;
    *partyD = seatD;
    *partyE = seatE;
}


void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	int P1_Area, P2_Area, P3_Area;			            /* Area of coordinate. */
	double P1_precedence, P2_precedence, P3_precedence;	/* Angle of origin to points will be enter. */

    printf("\n************ ORDER 2D POINTS ************ \n\n");
	/* Find the which location number is. */
	P1_Area = find_location(x1, y1);
	P2_Area = find_location(x2, y2);
	P3_Area = find_location(x3, y3);

    /* Find the precedences. */
    P1_precedence = find_precedence(x1, y1, P1_Area);
    P2_precedence = find_precedence(x2, y2, P2_Area);
    P3_precedence = find_precedence(x3, y3, P3_Area);

    /* According to the priority of the points swap them into the requared shape  
       My priority: (0,0) (2,0) (1,1) (2,2) (2,3) (0,2) (-1,2) (-2,2) (-3,3) (-5,-1) 
                    (-5,0) (-5,-1) (-1,-1) (-2,-2) (-1,-4) (0,-3) (1,-5) (2,-2) (4,-4) (5,-1)
        Origin > +x line > 1st Area > 2nd Area > 3rd Area > 4th Area
    */
    /* This conditions are for sort the int the same area and same sloped lines from origin to tail. */
    if (P1_precedence == P2_precedence && P1_precedence == P3_precedence)
    {
        if (*x1 * (*x1) + *y1 * (*y1) > *x2 * (*x2) + *y2 * (*y2))
        {
            swap_points(x1, y1, x2, y2);
            if (*x2 * (*x2) > *x3 * (*x3))
            {
                swap_points(x2, y2, x3, y3);
                if (*x1 * (*x1) > *x2 * (*x2))
                {
                    swap_points(x1, y1, x2, y2);
                }
            }
        }
        else
        {
            if (*x2 * (*x2) + *y2 * (*y2) > *x3 * (*x3) + *y3 * (*y3))
            {
                swap_points(x2, y2, x3, y3);
                if (*x1 * (*x1) > *x2 * (*x2))
                {
                    swap_points(x1, y1, x2, y2);
                }
            }
        }
    }
    else if (P1_precedence == P2_precedence)
    {
        if (*x1 * (*x1) + *y1 * (*y1) > *x2 * (*x2) + *y2 * (*y2))
        {
            swap_points(x1, y1, x2, y2);
        }
    }
    else if (P1_precedence == P3_precedence)
    {
        if (*x1 * (*x1) + *y1 * (*y1) > *x3 * (*x3) + *y3 * (*y3))
        {
            swap_points(x1, y1, x3, y3);
        }
    }
    else if (P2_precedence == P3_precedence)
    {
        if (*x2 * (*x2) + *y2 * (*y2) > *x3 * (*x3) + *y3 * (*y3))
        {
            swap_points(x2, y2, x3, y3);
        }
    }

	/* Final sorting the points according to counter clockwise direction. */
	if (P1_precedence < P2_precedence && P1_precedence < P3_precedence)
	{
		if (P3_precedence < P2_precedence)
		{
			swap_points(x3, y3, x2, y2);
		}
	}
	else if (P2_precedence < P1_precedence && P2_precedence < P3_precedence)
	{
        swap_points(x2, y2, x1, y1);
		if (P3_precedence < P2_precedence)
		{
			swap_points(x3, y3, x2, y2);
		}
	}
	else if (P3_precedence < P1_precedence && P3_precedence < P2_precedence)
	{
        swap_points(x3, y3, x1, y1);
		if (P3_precedence < P2_precedence)
		{
			swap_points(x3, y3, x2, y2);
		}
	}
}


void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';

    printf("\n************ NUMBER ENCRYPT ************ \n\n");

	/* Call the functions. */
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	/* To seperate number into the bits, we take the modulo two of the number and divide it into two in the continuation. 
	   We repeat this by the number of bits (8). */

	*b7 = number % 2;
	number /= 2;

	*b6 = number % 2;
	number /= 2;

	*b5 = number % 2;
	number /= 2;

	*b4 = number % 2;
	number /= 2;

	*b3 = number % 2;
	number /= 2;

	*b2 = number % 2;
	number /= 2;

	*b1 = number % 2;
	number /= 2;

	*b0 = number % 2;
	number /= 2;
}

void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	/* Swap chars according to the instructions. */
	swap_chars(&b7, &b2);
	swap_chars(&b6, &b3);
	swap_chars(&b5, &b0);
	swap_chars(&b4, &b1);

	/* Reconstruct the numbers with sum of the power 2 of the bits. */
	*number = 128 * b2;
	*number += 64 * b3;
	*number += 32 * b4;
	*number += 16 * b5;
	*number += 8 * b6;
	*number += 4 * b7;
	*number += 2 * b0;
	*number += 1 * b1;
}

/* Part1 - Polynomial */
void pol_addition(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	/* Addition operation. */
	*a3 += *b3;
	*a2 += *b2;
	*a1 += *b1;
	*a0 += *b0;

	/* Sort them tail to head. */
	*b1 = *a0;
	*b2 = *a1;
	*b3 = *a2;
	*a0 = *a3;

	*a1 = 0;
	*a2 = 0;
	*a3 = 0;
}
void pol_substriction(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	/* Substriction operation. */
	*a3 -= *b3;
	*a2 -= *b2;
	*a1 -= *b1;
	*a0 -= *b0;

	/* Sort them tail to head. */
	*b1 = *a0;
	*b2 = *a1;
	*b3 = *a2;
	*a0 = *a3;

	*a1 = 0;
	*a2 = 0;
	*a3 = 0;
}
void pol_multiplication(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	double c6, c5, c4, c3, c2, c1, c0;	/* Coefficients for up to 6 degree polinomial. */
	
	/* Multiplication operation. */
	c6 = (*a3) * (*b3);
    c5 = (*a3) * (*b2) + (*a2) * (*b3);
    c4 = (*a3) * (*b1) + (*a2) * (*b2) + (*a1) * (*b3);
    c3 = (*a3) * (*b0) + (*a2) * (*b1) + (*a1) * (*b2) + (*a0) * (*b3);
    c2 = (*a2) * (*b0) + (*a1) * (*b1) + (*a0) * (*b2);
    c1 = (*a1) * (*b0) + (*a0) * (*b1);
    c0 = (*a0) * (*b0);

	/* Sort them tail to head. */
    *a3 = c6;
    *a2 = c5;
    *a1 = c4;
    *a0 = c3;
    *b3 = c2;
    *b2 = c1;
    *b1 = c0;
}

/* Part4 - Counter Clockwise */
int find_location(double *p1, double *p2)
{
	/* Find the location of point. */
	if (*p1 == 0.0 && *p2 == 0.0)
	{
		return ORIGIN;
	}
	else if (*p1 > 0.0 && *p2 >= 0.0)
	{
		return AREA_1;
	}
    else if (*p1 == 0 && *p2 > 0)
    {
        return ON_PY;
    }
	else if (*p1 < 0.0 && *p2 > 0.0)
	{
		return AREA_2;
	}
	else if (*p1 < 0.0 && *p2 <= 0.0)
	{
		return AREA_3;
	}
    else if (*p1 == 0 && *p2 < 0)
    {
        return ON_NY;
    }
	else
	{
		return AREA_4;
	}
}

double find_precedence(double *p1, double *p2, int area)
{

	/* Find the angle according to the sin of the triangle occures. 
       (Not exactly angle but to compare it returns logical numbers. */

    /* Sin is directly proportioanal with the angle between 0 to 90 degree. 
       So, I took the absolute value of points and pretend like they are in the first area.
       Then with math (add 1, 2 or 3), I returned logical priorities to compare and write them. */
    
	if (area == ORIGIN)
	{
		return -1;
	}
	else if (area == AREA_1)
	{
		return (*p2 / sqrt(*p1 * (*p1) + *p2 * (*p2)));
	}
    else if (area == ON_PY)
    {
        return 1;
    }
	else if (area == AREA_2)
	{
		return 1 + (1 - (*p2 / sqrt(*p1 * (*p1) + *p2 * (*p2))));
	}
	else if (area == AREA_3)
	{
		return 2 + (-1 * (*p2) / sqrt(*p1 * (*p1) + *p2 * (*p2)));
	}
    else if (area == ON_NY)
    {
        return 3;
    }
	else if (area == AREA_4)
	{
		return 3 + (1 - (-1 * (*p2) / sqrt(*p1 * (*p1) + *p2 * (*p2))));
	}
}

void swap_points(double *x_1, double *y_1, double *x_2, double *y_2)
{
	/* Swap the points. */
	double x_Temp, y_Temp;

	x_Temp = *x_1;
	y_Temp = *y_1;

	*x_1 = *x_2;
	*y_1 = *y_2;

	*x_2 = x_Temp;
	*y_2 = y_Temp;
}

/* Part5 - Encrypt */
void swap_chars(char *c1, char *c2)
{
	char temp;

	/* Swap the chars. */
	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}