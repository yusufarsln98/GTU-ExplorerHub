#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 9
#define MAX 100

int check_palindrome(int a[], int n);

int search_element(int arr[], int input_number, int start);
void fill_array(int arr[], int n);


float find_cos(int n, float x );

int main(void)
{
    /* Part1 */
    
    int pal_array[N] = {7, 10, 4, 18, 6, 18, 4, 10, 7};
    int control;
    control = check_palindrome(pal_array, N);
    if (control == 0)
    {
        printf("\n\nThis array not palindrome!\n\n");
    }
    else if(control == 1)
    {
        printf("\n\nThis array is palindrome!\n\n");
    }

    /* Part2 */

    srand(time(NULL));

    int srh_array[20];
    int inp_number;
    int check_element;
    
    fill_array(srh_array, 20);      /* Fill array with recursion */
    inp_number = rand() % 101;      /* Give a random number to the inp_number to compare. */
    check_element = search_element(srh_array, inp_number, 0);  /* Compare number with array. */

    /*
    for (int i = 0; i < 20; i++)
    {
        printf("%d %d |", srh_array[i], inp_number);
    }
    printf("\n");
    */

    /* If array doesn't include it return 0 else return 1*/
    if (check_element == 0)                                 
    {
        printf("Array does not include the input number!\n");
    }
    else if(check_element == 1)                                     
    {       
        printf("Array include the input number!\n");
    }

    /* Part3 */
    int max;
    float x,
          cosx;

    printf("\nPlease enter n: ");
    scanf("%d", &max);

    printf("\nPlease enter x: ");
    scanf("%f", &x);
    
    cosx = find_cos(max, x);
    printf("\ncosx: %f\n", cosx);


    return 0;
}

int check_palindrome(int a[], int n)
{
    /* i start from 0 and increase 1 by 1 */
    static int i;
    
    /* There is 2 option, n should be even or odd.*/
    if (i == n - 1 || i == n)   /* If all elemenets are mathed then return 1 */
    {
        return 1;
    }
    else if (a[n - 1] != a[i])  /* If it detect difference from the numbers, returns 0 */
    {
        return 0;
    }
    else
    {
        i++;
        check_palindrome(a, n - 1); /* Recursion */
    }
}

int search_element(int arr[], int input_number, int start)
{
    if (start > 19)                         /* If input_number not matches yet, then return 0 */
    {
        return 0;
    }
    else if (arr[start] == input_number)    /* If matched then return 1 */
    {
        return 1;
    }
    else                                    /* Recursively call the function increasing by 1 */
    {
        search_element(arr, input_number, start + 1);
    } 
}
/* Fill array recursively. */
void fill_array(int arr[], int n)
{
    if (n < 0)
    {
        return;
    }
    else
    {
        arr[n - 1] = rand() % 101;
        fill_array(arr, n - 1);
    }
}

/* Find cos with recursion. */
float find_cos(int n, float x)
{
    if (n == MAX)
    {
        return 1;
    }
    else
    {
        return (1 - ((x * x) / (((2 * n) - 1) * (2 * n))) * find_cos(n + 1, x)); 
    }
}
