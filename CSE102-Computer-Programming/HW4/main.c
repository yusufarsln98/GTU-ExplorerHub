#include <stdio.h>
#include <math.h>

/* Print polynomial in pretty format. */
void print_polynomial(void);

void print_leading(double, int);    /* For leading coefficient. */
void print_middle(double ,int);     /* For coefficients in the middle. */
void print_a1(double);              /* For second to last coefficient. */
void print_a0(double);              /* For last coefficient. */

double round_n(double n);           /* Brings the decimal numbers into the requested format. */

/* Finds if entered number armstrong or palindrome number. */
void decide_armstrong_palindrome(void);

int is_armstrong(int);              /* Returns 1 if number is armstrong */
int is_palindrome(int);             /* Returns 1 if number is palindrome. */
int find_length(int);               /* Finds length of the entered number. */

/* Finds sum of prime numbers between 2 numbers. */
void sum_of_prime_numbers(void);

/* Main function of file. */
int main(void)
{
    /* Calling functions. */
    print_polynomial();
    decide_armstrong_palindrome();
    sum_of_prime_numbers();
}

/* Prints polynomial which its coefficients are taken from user. */
void print_polynomial(void)
{
    int i;                  /* Loop counter for if leading coefficient is 0 error. */
    int degree;             /* Will store current degree. */
    double coefficients;    /* Takes coefficients from user. */
    int N;                  /* Takes degree of polynomial from user. */
    double buffer;           /* For leading coefficient error. */

    printf("********* PRINT A POLYNOMIAL *********\n\n");
    printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");
    scanf("%d", &N);
    
    /* Loop for take coefficients from user and put them in a pretty format then print them. 
       There are several conditions to print polynomial in prety format. 
       1- Control the leading coefficient, because it depends on if you enter 1 or -1 or other conditions. 
       ie: 1x^3 not allowed, it should be x^3 
       2- Control the last coefficient, it is not allowed to print ie: 5x^0, it should be 5. 
       3- Control the second to last coefficient, it is not allowed to print ie: -5x^1, it should be -5.
       4- Finally control the all coefficients in the middle. It has a general formula to print. */
    
    for (degree = N; degree >= 0; degree--)
    {
        scanf("%lf", &coefficients);

        /* As we are expected to control up to 3 digits after point
           I first send the number to the function that will bring it to the desired format. 
           Ie: 0.06 -> 0.1, 2.06 -> 2.1, 1.96 -> 2, 0.056 -> 0.1, 0.055 -> 0.0 
               0.05 -> 0.0, 0.051 -> 0.1, 0.049 -> 0.0, 1.052 -> 1.1 ...
           Thanks to this, we do not have to check the 2nd and 3rd and other dgitis after the point. */
        coefficients = round_n(coefficients);   
        
        if (degree == N)    
        {
            if (coefficients == 0)
            {
                if (N == 0)
                {
                    printf("\np(x)=0\n");
                    return;
                }
                else
                {
                    printf("\nWarning! You wanted to print a polynomial with a leading coefficient of 0.\n");
                }
                
            }
            printf("\np(x)=");
            print_leading(coefficients, degree);    /* Print leading coefficient. */
        }
        else if (degree == 1)
        {
            print_a1(coefficients);                 /* Print a1 coefficient. */
        }
        else if (degree == 0)
        {
            print_a0(coefficients);                 /* Print a0 coefficient. */
        }
        else
        {
            print_middle(coefficients, degree);     /* Print other coefficients. */
        }
    }
    printf("\n");
}
/* Leading coefficient. (c is coefficient, d is degree.)*/   
void print_leading(double c, int d)     
{
    int check_decimalP;                 /* Going to start an integer to check if coefficients has floating points.*/
    check_decimalP = fabs((c * 10));    /* It checks the 1st digit after the point. */
    
    if (c == 1.0)           /* If coefficient is 1*/
    {
        if (d == 1)         /* If degree is 1 */
        {
            printf("x");
        }
        else if (d == 0)    /* If degree is 0 */
        {
            printf("1");
        }
        else                /* For other degrees */
        {
            printf("x^%d", d);
        }
    }
    else if (c == -1.0)     /* If coefficient is -1*/
    {
        if (d == 1)         /* If degree is 1 */
        {
            printf("-x");
        }
        else if (d == 0)    /* If degree is 0 */
        {
            printf("-1");
        }
        else                /* For other degrees */                
        {
            printf("-x^%d", d);
        }
    }
    else if (check_decimalP % 10 == 0)      /* Else for other integers. */
    {
        if (d == 1)         /* If degree is 1 */
        {
            printf("%.fx", c);
        }
        else if (d == 0)    /* If degree is 0 */
        {
            printf("%.f", c);
        }
        else                /* For other degrees */
        {
            printf("%.fx^%d", c, d);
        }
    }
    else if (check_decimalP % 10 != 0)      /* Else for decimal numbers. */ 
    {
        if (d == 1)         /* If degree is 1 */
        {
            printf("%.1fx", c);
        }
        else if (d == 0)    /* If degree is 0 */
        {
            printf("%.1f", c);
        }
        else                /* For other degrees */
        {
            printf("%.1fx^%d", c, d);
        }
    }     
}
/* Middle coefficients. (c is coefficient, d is degree.)*/
void print_middle(double c, int d)  
{
    int check_decimalP;             /* Going to start an integer to check if coefficients has floating points.*/

    check_decimalP = fabs(c * 10);  /* It checks the 1st digit after the point. */               
    
    if (c == 1)                     /* If coefficient is 1. */
    {
        printf("+x^%d", d);
    }
    else if (c == -1)               /* If coefficient is -1. */
    {
        printf("-x^%d", d);
    }
    else if (c != 0 && (check_decimalP % 10 == 0))      /* If coefficient is other integers. */    
    {
        printf("%+.fx^%d", c, d);
    }
    else if (c != 0 && (check_decimalP % 10 != 0))      /* If coefficient has deciamal points. */
    {
        printf("%+.1fx^%d", c, d);
    }
}
/* Coefficient a1. (c is coefficient)*/
void print_a1(double c)         
{
    int check_decimalP;             /* Going to start an integer to check if coefficients has floating points.*/

    check_decimalP = fabs(c * 10);  /* It checks the 1st digit after the point. */                 
    
    if (c == 1)                     /* If coefficient is 1. */
    {
        printf("+x");
    }
    else if (c == -1)               /* If coefficient is -1. */
    {
        printf("-x");
    }
    else if (c != 0 && (check_decimalP % 10 == 0))      /* If coefficient is other integers. */
    {
        printf("%+.fx", c);
    }
    else if (c != 0 && (check_decimalP % 10 != 0))      /* If coefficient has deciamal points. */
    {
        printf("%+.1fx", c);
    }
}
/* Coefficient a0. (c is coefficient)*/
void print_a0(double c)         
{
    int check_decimalP;             /* Going to start an integer to check if coefficients has floating points.*/

    check_decimalP = fabs(c * 10);  /* It checks the 1st digit after the point. */              

    if (c == 1)                     /* If coefficient is 1. */
    {
        printf("+1");
    }
    else if (c == -1)               /* If coefficient is -1. */
    {
        printf("-1");
    }
    else if (c != 0 && (check_decimalP % 10 == 0))      /* If coefficient is other integers. */
    {
        printf("%+.f", c);
    }
    else if (c != 0 && (check_decimalP % 10 != 0))      /* If coefficient has deciamal points. */
    {    
        printf("%+.1f", c);
    }
}
/* Round number into the requested format. */
double round_n(double n)
{
    int decimalP, floorN;       /* Decimal points and floor */
    double rounded_num;         /* Rounded number. */

    /* Here I control if 2nd and 3rd decimal point is larger then 0.050 
       If is, then I round the number and return in a.b0000 format. */

    rounded_num = fabs(n);
    floorN = floor(rounded_num);
    
    decimalP = floor(rounded_num * 1000);
    if (decimalP % 100 > 50)
    {
        rounded_num = rounded_num + 0.1;
    }
    rounded_num = (int)(rounded_num * 10) / 10.0;
    if (n < 0)
    {
        return (rounded_num * -1);
    }
    else
    {
        return rounded_num;
    }
}

/* Finds if entered number armstrong or palindrome number. */
void decide_armstrong_palindrome(void)
{
    int num;

    printf("\n\n********* ARMSTRONG AND PALINDROME NUMBER *********\n\n");

    printf("Please enter an integer: ");
    scanf("%d", &num);
    while (num < 0)
    {
        printf("The number cannot be negative. Please enter a new number: ");
        scanf("%d", &num);
    } 
    
    if (is_armstrong(num) == 1 && is_palindrome(num) == 1)
    {
        printf("\n\nThis number is both Armstrong and Palindrome number.\n");
    }
    else if(is_armstrong(num) == 1 && is_palindrome(num) != 1)
    {
        printf("\n\nThis number is only Armstrong number.\n");
    }
    else if (is_armstrong(num) != 1 && is_palindrome(num) == 1)
    {
        printf("\n\nThis number is only Palindrome number.\n");
    }
    else
    {
        printf("\n\nThis number neither Armstrong nor Palindrome number.\n");
    }
    
}

/* Armstrong number is a number that is equal to the sum of length power of its digits. 
   For example 0, 1, 153, 370, 371 and 407 are the Armstrong numbers. 
   ie: 153 = (1*1*1)+(5*5*5)+(3*3*3) */
int is_armstrong(int num)
{
    int i, n;
    int digit;
    int sum = 0;
    int length;

    /* since we divide the value of n by 10 step by step and collect the cube of its last digit, its value will change.
       For this reason, we record num in another variable. */  
    n = num;

    /* 0 is armstrong number. */
    if (num == 0)
    {
        return 1;
    }
    /* According to formula we should take length power of digits and sum them. */
    length = find_length(num);

    /* Loop for find digits and sum cube of them. */
    do
    {
        digit = n % 10;                 /* Last digit of number. */
        sum += pow(digit, length);      /* Sum power of length of found digits. */
        n /= 10;                        /* Reduce by one digit till this number become 0. */
        
    } while (n != 0);

    /* If sum of cube of digits are equal to num, then it is a perfect number. */
    if (sum == num)
    {
        return 1;
    }
    return 0;
}

/* Palindrome number is a number that is same after reverse. 
   For example 121, 34543, 343, 131, 48984 are the palindrome numbers. */
int is_palindrome(int num)
{
    int first_digit, last_digit;    
    int num2;
    int length, len;
    int counter = 0;

    first_digit = last_digit = num; /* A precaution in case it's single digits. */

    num2 = num;                     /* Since we reduce the number step by step, we need to copy. */
    length = find_length(num);      /* Length of input number */
    len = length;                   /* One will be the number of repetitions of the loop. */

    /* By examining the number from the left and right, check if these numbers are the same. */
    while (num != 0)
    {
        last_digit = num % 10;          /* Starting from the right with Modulo, the digits are controlled. */
        
        /* By dividing the number by a multiple of 10, the digits on the right are controlled. */
        first_digit = (int)(num2 / (pow(10, len - 1))) % 10; 
        
        if (last_digit == first_digit)  /* If these numbers match, increase the counter. */
        {
            counter++;
        }
        len--;
        num /= 10;
    }

    /* If the length is equal to the number of matching digits, that number is palindrome. */
    if (length == counter)
    {
        return 1;
    }
    return 0;
}

/* Find length of number. */
int find_length(int n)
{
    int length = 0;
    while (n != 0)
    {
        length++;
        n /= 10;
    }
    return length;
}

/* This function will read 2 integers from the command prompt, 
   find the prime numbers between these integers (exclusive) and print their sum on the screen. */
void sum_of_prime_numbers(void)
{
    int i;                  /* Foor counting loop. */
    int n1, num1, num2;     /* Integers gotten from user. */
    int temp;               /* Temporarily keeps the integer to sort numbers taken from user. */
    int sum;                /* Sum of prime numbers. */
    int difference;         /* Keeps number of numbers between taken number from user. */
    int counter;            /* Counts number of divisors. */
    
    /* Initial Values */
    counter = 0;            
    sum = 0;

    printf("\n\n********* SUM OF PRIME NUMBERS *********\n\n");

    printf("Please enter first integer number: ");
    scanf("%d", &num1);
    while (num1 <= 0)
    {
        printf("The number should be positive. Please enter a new number: ");    
        scanf("%d", &num1);
    }
    
    printf("\nPlease enter second integer number: ");
    scanf("%d", &num2);
    while (num2 <= 0)
    {
        printf("The number should be positive. Please enter a new number: ");    
        scanf("%d", &num2);
    }

    /* Sorting numbers */
    if (num1 > num2)
    {
        temp = num2;
        num2 = num1;
        num1 = temp;
    }

    /* Copies lower limit to another integer. Since it's exlusive, then increase by 1. */
    n1 = num1 + 1;

    /* Number of steps, also number of number between 2 number. Since it's exlusive, then decrease by 1. */
    difference = (num2 - num1 - 1);

    if (difference <= 0)
    {
        printf("\nThere is no prime number between %d and %d.\n", num1, num2);
        return;
    }
    
    /* Loop for find prime numbers and find sum of them. */
    while (difference != 0)
    {
        for (i = 1; i <= (n1 / 2); i++)    /* Finds dividers.  */
        {
            if (n1 % i == 0)    /* If number has a divider in the range. */
            {
                counter++;      /* Then increase the counter. */
            }
        }
        if (counter == 1)   /* If number has any divider except 1 */
        {
            sum += n1;      /* Then sum this prime numbers. */
        }
        counter = 0;        /* Count from the beginning for each loop. */
        n1++;               /* From the lower limit, increase one by one. */
        difference--;       /* Decrease steps of loop one by one. */
    }
    printf("\n\nSum of prime numbers between %d and %d: %d\n", num1, num2, sum);
}


