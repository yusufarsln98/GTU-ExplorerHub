/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	double p1_3 = 0, p1_2 = 0, p1_1 = 0, p1_0 = 0, p2_3 = 0, p2_2 = 0, p2_1 = 0, p2_0 = 0;
	char op;
	int i;

	int bufferN;
	double bufferF;

	printf("\n************ POLYNOMIAL CALCULATOR ************\n\n");

	/* Get 1st polynomial coefficients. WARNING! WATCH OUT THE BLANKS AND PUNCTIATIONS */

    printf("Enter 1st polynomial <(3, a), (2, b), (1, c), (0, d)> : ");
	/* It enable to take polynomial in any order. E.g. (0, 11.2), (2, 1.2), (1, -1.2), (3, 1.2) */
    for (i = 0; i <= 30; i++)
    {
        if (i % 8 == 1)
        {
            scanf("%d", &bufferN);
        }
        else if (i % 8 == 4)   
        {
            scanf("%lf", &bufferF);
            if (bufferN == 3)
            {
                p1_3 = bufferF;
            }
            else if (bufferN == 2)
            {
                p1_2 = bufferF;
            }
            else if (bufferN == 1)
            {
                p1_1 = bufferF;
            }
            else if (bufferN == 0)
            {
                p1_0 = bufferF;
            }
        }
        else
        {
            getchar();
        }
    }

	/* Get 1st polynomial coefficients. WARNING! WATCH OUT THE BLANKS AND PUNCTIATIONS */
	printf("\nEnter 2nd polynomial <(3, a), (2, b), (1, c), (0, d)> : ");

	/* It enable to take polynomial in any order. E.g. (0, 11.2), (2, 1.2), (1, -1.2), (3, 1.2) */
    for (i = 0; i <= 30; i++)
    {
        if (i % 8 == 1)
        {
            scanf("%d", &bufferN);
        }
        else if (i % 8 == 4)   
        {
            scanf("%lf", &bufferF);
            if (bufferN == 3)
            {
                p2_3 = bufferF;
            }
            else if (bufferN == 2)
            {
                p2_2 = bufferF;
            }
            else if (bufferN == 1)
            {
                p2_1 = bufferF;
            }
            else if (bufferN == 0)
            {
                p2_0 = bufferF;
            }
        }
        else
        {
            getchar();
        }
    }

	printf("\n");

	/* Ask user to which operation he/she wants to do. */
    printf("Operation ( + or - or * ): ");
	scanf(" %c", &op);

	/* Be sure the correct answer. */
	while ((op != '+') && (op != '-') && (op != '*'))
	{
		printf("Make sure you have entered the correct operator: ");
		scanf(" %c", &op);
	}

	printf("\n");

	/* Pass the address of the variables to the functions. (To return by reference) */
	operate_polynomials(&p1_3, &p1_2, &p1_1, &p1_0, &p2_3, &p2_2, &p2_1, &p2_0, op);

	printf("\n");
	
	if (p1_3 == 0 && p1_2 == 0 && p1_1 == 0 && p1_0 == 0 && p2_3 == 0 && p2_2 == 0)	/* Print if polynomial is 0 degree. */
	{
		printf("0 degree polynomial coefficient: \n\n");
		printf("a0: %.2f\n", p2_1);
	}
	else if (p1_3 == 0 && p1_2 == 0 && p1_1 == 0 && p1_0 == 0 && p2_3 == 0)			/* Print if polynomial is 1 degree. */
	{
		printf("1 degree polynomial coefficients: \n\n");
		printf("a1: %.2f	a0: %.2f\n", p2_2, p2_1);
	}
	else if (p1_3 == 0 && p1_2 == 0 && p1_1 == 0 && p1_0 == 0)						/* Print if polynomial is 2 degree. */
	{
		printf("2 degree polynomial coefficients: \n\n");
		printf("a2: %.2f	a1: %.2f	a0: %.2f\n", p2_3, p2_2, p2_1);	
	}
	else if (p1_3 == 0 && p1_2 == 0 && p1_1 == 0)									/* Print if polynomial is 3 degree. */
	{
		printf("3 degree polynomial coefficients: \n\n");
		printf("a3: %.2f	a2: %.2f	a1: %.2f	a0: %.2f\n", p1_0, p2_3, p2_2, p2_1);		
	}
	else if (p1_3 == 0 && p1_2 == 0)												/* Print if polynomial is 4 degree. */
	{
		printf("4 degree polynomial coefficients: \n\n");
		printf("a4: %.2f	a3: %.2f	a2: %.2f	a1: %.2f	a0: %.2f\n", p1_1, p1_0, p2_3, p2_2, p2_1);
	}
	else if (p1_3 == 0)																/* Print if polynomial is 5 degree. */
	{
		printf("5 degree polynomial coefficients: \n\n");
		printf("a5: %.2f	a4: %.2f	a3: %.2f	a2: %.2f	a1: %.2f	a0: %.2f\n", p1_2, p1_1, p1_0, p2_3, p2_2, p2_1);
	}
	else 																			/* Print if polynomial is 6 degree. */
	{
		printf("6 degree polynomial coefficients: \n\n");
		printf("a6: %.2f	a5: %.2f	a4: %.2f	a3: %.2f	a2: %.2f	a1: %.2f	a0: %.2f\n", p1_3, p1_2, p1_1, p1_0, p2_3, p2_2, p2_1);
	}
	printf("\n\n");
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number = 0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}

/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
