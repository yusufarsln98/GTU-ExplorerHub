/* 

The variable names that used in this file have no relation with the ones in the pdf file. 

<?> in the functions means something other than void, you should find the correct type for these functions.

*/

#include <stdio.h>

/* Trigonometry function*/
void trigonometry_calculation(int a, int b, int c)
{
    printf("sinx = %f\n", (double)a/c);             /* sinx */
    printf("cosx = %f\n", (double)b/c);             /* cosx */
    printf("tanx = %f\n", (double)a/b);             /* tanx */
}



/* Age function*/
void age_calculation(int x)
{

    if (x <= 100 && x >= 0)
    {
        printf("You are %ld seconds\n", (long)x * 365 * 24 * 3600); /* How second old you are */
    }
    else
    {
        printf("Age should be between 0 and 100\n");                /* Should be 0 to 100 years old */   
    }   
    
}


int main()
{
    int a, b, c;        /* variable for trigonometry */
    int age_of;         /* for age calculation */
    
    printf("a: ");
    scanf("%d", &a);
    
    printf("b: ");
    scanf("%d", &b);
    
    printf("c: ");
    scanf("%d", &c);      
    
    trigonometry_calculation(a, b, c);

    printf("Your age: ");
    scanf("%d", &age_of);
    
    age_calculation(age_of);


    
    return 0;
}
