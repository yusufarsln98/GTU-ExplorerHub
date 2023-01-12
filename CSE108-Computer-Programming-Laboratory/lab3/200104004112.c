#include <stdio.h>

#define NUMBERS 5
/* Calculates the largest difference between consecutive numbers. */
int find_max_distance(int);

/* Calculates the average of odd numbers entered. */
void find_odd_average(void);

int main(void)
{
    int difference;
    /* Calling functions */
    difference = find_max_distance(NUMBERS);
    find_odd_average();
}

int find_max_distance(int nums)
{
    int i;
    /* Holds the numbers to be entered after the 2nd term. */
    int a1;
    /* Temporarily keeps the numbers from the 1st term. */
    int temp;

    /* Different amounts between 2 numbers. */
    int dif = 0;
    int temp_dif = 0;
    
    printf("Please enter %d integer:\n", nums);
    printf("1: ");
    scanf("%d", &temp);  

    /* Loop to retrieve numbers from user and find differences. */
    for (i = 0; i < (nums - 1); i++)
    {   
        printf("%d: ", (i + 2));
        scanf("%d", &a1);
        /* It keeps the difference temporarily. */
        temp_dif = (a1 - temp);
        /* If the number is negative, turn it into positive. */
        if (temp_dif < 0)
        {   
            temp_dif *= -1;
        }
        /* If the temporary difference is greater than the difference, 
           define it as the new difference. */
        if (temp_dif > dif)
        {
            dif = temp_dif;
        }
        /* Shift the numbers */
        temp = a1;
    }
    printf("Max distance between two consecutive numbers: %d\n", dif);
}

void find_odd_average(void)
{
    int n;  /* For user input numbers */
    int counter = 1;        /* Counter for where loop is */
    int count_odds = 0;     /* Counter for number of odds */
    float sum = 0;          /* Sum of odd number */

    /* Loop for find sum of odds. */
    printf("Please enter positive numbers. (end -1 to stop entering)\n");
    do
    {
        printf("%d: ", counter);
        scanf("%d", &n);
        /* If it is odd */
        if (n % 2 == 1)
        {
            sum += n;
            count_odds++;
        }
        counter++;
    } while (n != -1);

    /* Since divide 0 not possible, warn user. */
    if (count_odds == 0)
    {
        printf("You did not enter odds numbers!\n");
    }
    else
    {
        printf("Average of odd numbers: %g\n", sum / count_odds);
    }
    
}

