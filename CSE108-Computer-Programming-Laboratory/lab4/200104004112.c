#include <stdio.h>

/* Russian multiplication method */
void russian_multiplication(unsigned int* multiplicand, unsigned int* multiplier);

/* Multiplication of 2 3rd degree polinomials. */
void multiply_polynomials(double* a3, double* a2, double* a1, double* a0, 
                          double* b3, double* b2, double* b1, double b0);


int main(void)
{
    int n1, n2;                 /* Will keep 2 number to multiple. */

    double a3, a2, a1, a0;      /* 1st polinomial coefficients. */
    double b3, b2, b1, b0;      /* 2nd polinomial coefficients. */

    /*1st Part*/
    printf("\nPlese enter 2 positive number: ");
    scanf("%d%d", &n1, &n2);
    russian_multiplication(&n1, &n2);
    printf("Current Multiplicant: %d\nCurrent Multiplier: %d\n\n", n1, n2);
    printf("--------------------------------------\n\n");

    /*2nd Part*/
    printf("Enter first 3rd degree polinomial: ");
    scanf("%lf%lf%lf%lf", &a3, &a2, &a1, &a0);
    printf("Enter 2nd 3rd degree polinomial: ");
    scanf("%lf%lf%lf%lf", &b3, &b2, &b1, &b0);
    
    multiply_polynomials(&a3, &a2, &a1, &a0, &b3, &b2, &b1, b0);

    printf("\np(x)=%+gx^6%+gx^5%+gx^4%+.gx^3%+gx^2%+gx%+g\n", a3, a2, a1, a0, b3, b2, b1);

}

/* Russian multiplication method */
void russian_multiplication(unsigned int* multiplicand, unsigned int* multiplier)
{
    int sum = 0;        /* This is going to add up the multiplicands while the multiplier is odd. */ 

    while(1)
    {
        
        if (*multiplier % 2 != 0)   /* If multiplier not even */
        {
            sum += *multiplicand;   /* Then add it multiplicand to sum */
        }
        if (*multiplier == 1)       /* If multiplier equal to 1 */
        {
            *multiplicand = sum;    /* Then replace multiplicand with sum.(According to instructions.) */
            break;
        }
        *multiplicand = *multiplicand * 2;  /* Multiple multiplicand by 2*/
        *multiplier = *multiplier / 2;      /* Divide multiplier over 2 */
    }
}

/* Multiplication of 2 3rd degree polinomials. */
void multiply_polynomials(double* a3, double* a2, double* a1, double* a0, 
                          double* b3, double* b2, double* b1, double b0)
{
    double c6, c5, c4, c3, c2, c1, c0; /* Coefficients for 6 degree polinomial. */

    /* Polinomial multiplication. */
    c6 = (*a3) * (*b3);
    c5 = (*a3) * (*b2) + (*a2) * (*b3);
    c4 = (*a3) * (*b1) + (*a2) * (*b2) + (*a1) * (*b3);
    c3 = (*a3) * (b0) + (*a2) * (*b1) + (*a1) * (*b2) + (*a0) * (*b3);
    c2 = (*a2) * (b0) + (*a1) * (*b1) + (*a0) * (*b2);
    c1 = (*a1) * (b0) + (*a0) * (*b1);
    c0 = (*a0) * (b0);

    /* Replace the first and second polinomial coefficints with theirs new values. 
       (6th degree polinomial coefficients) */
       
    *a3 = c6;
    *a2 = c5;
    *a1 = c4;
    *a0 = c3;
    *b3 = c2;
    *b2 = c1;
    *b1 = c0;

}
