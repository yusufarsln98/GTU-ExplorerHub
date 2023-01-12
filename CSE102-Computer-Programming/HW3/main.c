#include <stdio.h>

/* Yusuf Arslan. 24.03.2021 CSE-102 Spring */

/* The number of terms required for difference_max_min() function.*/
#define N 5 

/* Calculates fibonacci sequences according to instructions then prints it. */
void calculate_fibonacci_sequence(void);
/* Controls perfect and harmonic numbers according to the instructions then prints if they are or not. */
void decide_perfect_harmonic_number(void);


void print_fibonacci(int);              /* Prints fibonacci sequences. */
void print_harmonic_perfect(int);       /* Prints if the input number harmonic and perfect. */
void control_number(int num, char ch);  /* Controls if input number is correct according to the instructions. */

void difference_max_min(void);  /* Finds max and min number and difference of them. Then prints. */
void bmi_calculation (void);    /* Calculates body mass index and prints. */


int main(void)
{
    /* Calling functions */
    calculate_fibonacci_sequence();
    difference_max_min();
    bmi_calculation ();
}

/* 
Instructions: 
1- '*' is switch to "decide_perfect_harmonic_number()" function 
2- Non-integer inputs are not allowed.
3- Characters except asterisk not allowed.
4- If input is a number bigger then 0, then prints fibonacci sequences.
5- Ask user to input till get correct input ('*' or a number larger then 0).
*/
void calculate_fibonacci_sequence(void)
{
    int num;    /* It will store number for print fibonacci sequence. */
    char ch;    /* Char for control if input is correct */

    printf("********* FIBONACCI NUMBER CALCULATOR *********\n\n");
    printf("Please enter term(s) number: ");

    /* Structure for ask user till get correct input. */
    while(1)
    {
        /* 
        Scanf and getchar putted here one after another. 
        Hence we can control if user correctly input a number or char.
        1- If user enter a number then press to enter scanf will take integer then getchar will take '\n'
        2- If user input a character, scanf will be passed. Then, this char going to store into the ch variable.
        */
        scanf("%d", &num);
        ch = getchar();
        /* If user enter '*' then switch to other function. (According to instructions.) */
        if (ch == '*')
        {
            decide_perfect_harmonic_number();
            break;
        }
        /* If user enter a number larger then zero, then print fibonacci sequences of this number */
        else if (ch == '\n' && num > 0)
        {
            print_fibonacci(num);
            printf("Please enter term(s) number: ");
        }
        /* Other wise, if user input not correct, go check what is this input. */
        control_number(num, ch);
    }
}

/* Print fibonacci sequence */
void print_fibonacci(int n)
{
    int t1 = 0, t2 = 1;     /* First and second element of fibonacci sequence */
    int temp, i;

    printf("\nFibonacci Sequence:\n\n");

    /* Fibonacci numbers, form a sequence, called the Fibonacci sequence, 
       such that each number is the sum of the two preceding ones, starting from 0 and 1. */
    /* In this homework in some reason it starts from 1... */
    
    for (i = 1; i <= n; i++)
    {
        printf("%d\n\n", t2);   /* Prints first term of sequence */
        temp = t1 + t2;         /* Sum of 2 term in one after other then store it temporarily*/
        t1 = t2;                /* Replace first term with its next term */
        t2 = temp;              /* Replace secont term with temporal number which keeps sum of last 2 term, then loop continues*/
    }
    printf("--------------------------------\n\n");
}

/* 
Instructions: 
1- '*' is exits the function.
2- Non-integer inputs are not allowed.
3- Characters except asterisk not allowed.
4- If input is a number bigger then 0, prints if this number perfect and harmonic number.
5- Ask user to input till get correct input ('*' or a number larger then 0).
*/
void decide_perfect_harmonic_number(void)
{
    int num;
    char ch;
    printf("\n********* PERFECT AND HARMONIC NUMBER CALCULATOR *********\n\n");
    printf("Please enter input number: ");

    /* Structure for ask user till get correct input. */
    while(1)
    {
        /* 
        Scanf and getchar putted here one after another. 
        Hence we can control if user correctly input a number or char.
        1- If user enter a number then press to enter scanf will take integer then getchar will take '\n'
        2- If user input a character, scanf will be passed. Then, this char going to store into the ch variable.
        */       
        scanf("%d", &num);
        ch = getchar();
        /* If user input '*' then break the loop and return main. (Void function) */
        if (ch == '*')
        {
            break;
        }
        /* If user enter a number larger then 0, 
           then go and control if it is perfect and harmonic number. Then print. */
        if (ch == '\n' && num > 0)
        {
            print_harmonic_perfect(num);
            printf("Please enter input number: ");
        }
        /* Other wise, if user input not correct, go check what is the reason. */
        control_number(num, ch);
    }
}

/* Prints harmonic  */
void print_harmonic_perfect(int n)
{
    int i;
    int sum = 0;    /* Sum of divider of input number. */

    float harmonic_numerator;       /* Numerator of harmonic number formula. */
    float harmonic_denominator;     /* Denominator of harmonic number formula. */  
    float harmonic_control;         /* Result of harmonic number formula. */

    /* Counter for find number of divisor. Since we know number itself is a divisor, 
       counter start from 1, thanks of it, it will be easy to determine, with a loop, if number is perfect.  */
    float counter = 1.0;


    printf("\nNatural Number Divisors: ");
    /* Finds natural number divisors and sum of this divisors (except number itself). */
    /* n is parameter of function which number entered by user. */ 
    for (i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            printf("%d, ", i);
            sum += i;
            counter++;
        }
    }
    printf("%d\n\n", n);

    /* A number that is equal to the sum of its divisors, except for itself, is called a perfect number. 
       It is also the reason of why we starts counting from 1 and take sum of dividers except number itself. 
       Ie: 6 has 3 divisor except itself (1, 2, 3). Hence we can easily know 6 = 1 + 2 + 3 and 6 is a perfect number. */
    
    /* If sum of divisors is equal to itself then it is a perfect number. */

    if (sum == n)
    {
        printf("Is perfect number: Yes\n\n");
    }
    else
    {
        printf("Is perfect number: No\n\n");
    }

    /* Harmonic Divisor Number or Ore Number is a positive integer whose divisors have a harmonic mean that is an integer.

       ie: 6 is harmonic number. It has 4 divisor. It's formula application: 4 / ((1/1) + (1/2) + (1/3) + (1/6)) = 2 
       Since 2 is a integer, 6 is a harmonic number. 
       When we look at the formula, there are numbers such as 1/3, the result of which goes to an infinite decimal number (0.3333333...). 
       Depending on the limited memory that Float or double will allocate in RAM, there is an overflow risk here.
       For this reason, by revising the formula, bringing the sum of the divisors to the numerator, the largest divisor (the number itself) to the denominator
       eliminates the risk of overflow (Never divide a number over 1). */
    
    harmonic_numerator = sum + n;   /* Numerator of formula */
    harmonic_denominator = n;       /* Denominator of formula */

    /* Result of formula. */
    harmonic_control = counter * harmonic_denominator / harmonic_numerator;

    /* If this floating result is an integer number, then  it is a harmonic divisor number.*/
    if (harmonic_control - (int)harmonic_control == 0.0)
    {
        printf("Is Harmonic Divisor Number?: Yes\n\n");
        printf("--------------------------------\n\n");
    }
    else
    {
        printf("Is Harmonic Divisor Number?: No\n\n");
        printf("--------------------------------\n\n");
    }
}

/* Controls inputs of 1st and 2nd function */
void control_number(int num, char ch)
{
    /* If user enter a negatif number then warn him/her. */
    if (ch == '\n' && num <= 0)
    {
        printf("\nPlease enter \"positive\" term(s) number: ");
    }
    /* If user enter a char (except '*') then warn him/her */
    else if (ch != '\n' && ch != '*')
    {
        printf("\nPlease enter \"numeric\" term(s) number: ");
    }
}

/* Finds max and min number and difference of them. Then prints. */
void difference_max_min(void)
{
    int i;
    float number;   
    float max, min;             

    printf("\n********* MINIMUM AND MAXIMUM NUMBER *********\n\n");

    printf("Please enter %d numbers: ", N);

    /* Loop for find max and min number. */
    for (i = 0; i < N; i++)
    {
        scanf("%f", &number);

        /* To avoid storing garbage value inside the variables, 
           I equate max and min number to first number user entered. */
        if (i == 0)
        {
            max = min = number;
        }
        else 
        {
            if (number > max)   /* If find larger number the previous one. */
            {
                max = number;   /* Then, assign it new largest number. */
            }
            if (number < min)   /* If find smaller number the previous one. */   
            {
                min = number;   /* Then, assign it new smallest number. */
            }
        }
    }

    printf("\nMaximum number is: %g\n", max);
    printf("\nMinimum number is: %g\n", min);
    printf("\nDifference between maximum and minimum is: %g\n\n", max - min);   
}
/* Calculates body mass index and prints. */
void bmi_calculation (void)
{
    float weight, height, bmi;

    printf("\n********* BMI CALCULATOR *********\n\n");

    printf("Please enter weight(kg): ");
    scanf("%f", &weight);
    printf("\nPlease enter height(m): ");
    scanf("%f", &height);

    /* Formula of body mass index. */
    bmi = weight / (height * height);

    /* Prints in what category is user. */
    if (bmi < 16.0)
    {
        printf("\nYour category: Severely Underweight\n\n");
    }
    else if (bmi >= 16.0 && bmi < 18.5)
    {
        printf("\nYour category: Underweight\n\n");
    }
    else if (bmi >= 18.5 && bmi < 25.0)
    {
        printf("\nYour category: Normal\n\n");
    }
    else if (bmi >= 25.0 && bmi < 30.0)
    {
        printf("\nYour category: Owerweight\n\n");
    }
    else
    {
        printf("\nYour category: Obese\n\n");
    }
}