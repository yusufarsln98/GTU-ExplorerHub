/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
Contains the main function. You are not expected to modify this file in your submission. 
You may modify it for your own testing and debugging needs.
*/

#include <stdio.h>

#include "hw1_lib.h"
#include "hw1_io.h"


/*
** Testing root finding..
**
*/
void test_root_finder3() 
{
	double root_known = 1.0;
	double root_found;
	root_found = root3(1.2, 1.0, -1.0, -1.2, root_known-0.1, root_known+0.1);
	printf("Ground truth root: %f vs found root: %f\n", root_known, root_found);
}

/*
** Testing other functions..
** */

void test_root_finder4()
{
	double root_known = 1.027776;
	double root_found;
	root_found = root4(-27, 15, 11, 1.2, -1.2, root_known-0.1, root_known+0.1);
	printf("Ground truth root: %f vs found root: %f\n", root_known, root_found);
}

void test_integral3()
{
	double integral_found = integral3(-12, -0.5, -1.2, 1, 0, 10, 1);
	printf("Integral is = %f\n", integral_found);
}

void test_integral4()
{
	double integral_found = integral4(-12, -0.5, -1.2, 1, -3.1, 0, 10, 1);
	printf("Integral is = %f\n", integral_found);
}

/*
** main function for testing the functions...
**
*/
int main(void) {


	/*
	** Testing Functions..
	*/
	test_root_finder3();
	test_root_finder4();
	test_integral3();
	test_integral4();
	write_polynomial3(-1.2, 5, -4.7, 4.1);
	write_polynomial4(-1.2, 5.1, 0, 4, 222);
	write_polynomial4(1, 2, 3, 1, -1);
	
	return (0);
	
} /* end main */
