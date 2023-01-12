#include <stdio.h>
#include <stdlib.h>

void expression0 (int x, int *result);
void expression1 (int x, int *result);
void expression2 (int x, int *result);
void addition (void (*func)(int, int *), int *sum, int n);
void calculation (int *sumArray, int n);

void createArray(int (*array)[10]);

#define ROW 10
#define CLM 10

int main(void)
{
    int sum_of_exp[3] = {0, 0, 0};
    int n;

    do
    {
        printf("Please enter the upper limit: "); 
        scanf("%d", &n);
        if (n < 0)
        {
            printf("Error! Enter a positive number.\n");
        }
    }while(n < 0);

    calculation(&sum_of_exp[0], n);

    printf("Sum of expression0: %d\n", sum_of_exp[0]);
    printf("Sum of expression1: %d\n", sum_of_exp[1]);
    printf("Sum of expression2: %d\n", sum_of_exp[2]);

    /* ------------------------------------------------------ */

    int myArray[ROW][CLM];
    createArray(myArray);
    int r, c;

    printf("Matrix:\n\n");
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < CLM; j++)
        {
            printf("%d ", myArray[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    do
    {
        printf("Which element do you want to reach?\n");
        printf("i:  ");
        scanf("%d", &r);
        printf("j:  ");
        scanf("%d", &c);
        if (r >= 0 && r <= 8 && c >= 0 && c <= 8)
        {
            printf("%d. row %d. column of the matrix is %d\n\n", r, c, myArray[r][c]);
        }
        else
        {
            printf("Invalid input. Terminating...\n");
            break;
        }
        
    } while (r >= 0 && r <= 8 && c >= 0 && c <= 8);
    
}
void expression0 (int x, int *result)
{
    *result = x * x + 5;
}
void expression1 (int x, int *result)
{
    *result = 2 * x + 1;
}
void expression2 (int x, int *result)
{
    *result = x * x;
}
void addition (void (*func)(int , int *), int *sum, int n)
{
    int i, result;
    for (i = 0; i <= n; i++)
    {
        func(i, &result);
        *sum += result;
    }
}
void calculation (int *sumArray, int n)
{
    addition((&expression0), &sumArray[0], n);
    addition((&expression1), &sumArray[1], n);
    addition((&expression2), &sumArray[2], n);
}

/* ---------------------------------------------------- */

void createArray(int (*array)[10])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < CLM; j++)
        {
            array[i][j] = rand () %90 + 10;
        }
    }
}




