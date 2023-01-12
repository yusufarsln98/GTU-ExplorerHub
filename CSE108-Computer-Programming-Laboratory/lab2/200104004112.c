#include <stdio.h>
#include <math.h>


/* 1st */
void number_type(void);

void calcuation_type_int(void);
void int_addition(void);
void int_multiplication(void);

void calcuation_type_comp(void);
void comp_addition(void);
void comp_multiplication(void);

/*-----------------------*/

/* 2nd */
void shape_type(void);

void rectangle(void);
void triangle(void);
void circle(void);

/*-----------------------*/

/* 3rd */
void temp_type(void);

void fah_to_kelv(void); 
void kelv_to_fah(void);


/*-----------------------*/

int main(void)
{
    
    int choice;
    
    printf("Enter the calculation type:\n");
    printf(" 1. Standart Calcuator\n 2. Area&Perimeter Calculator\n 3. Temperature Calculator\n");
    printf("----------------------\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        number_type();
        break;
    case 2:
        shape_type();
        break;
    case 3:
        temp_type();
        break;
    default:
        printf("Invalid Enter. (Enter 1 or 2 or 3)\n");
        break;
    }

    
    
}
void number_type(void)
{
    int choice;
    printf("Enter the number type:\n");
    printf(" 1. Integer\n 2. Complex\n");
    printf("----------------------\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        calcuation_type_int();
        break;
    case 2:
        calcuation_type_comp();
        break;
    default:
        printf("Invalid Enter. (Enter 1 or 2)\n");
        break;
    }

}
void calcuation_type_int(void)
{
    int choice;
    printf("Enter the calculation type:\n");
    printf(" 1. Addition\n 2. Multiplication\n");
    printf("----------------------\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        int_addition();
        break;
    case 2:
        int_multiplication();
        break;
    default:
        printf("Invalid Enter. (Enter 1 or 2)\n");
        break;
    }   
}
void calcuation_type_comp(void)
{
    int choice;
    printf("Enter the calculation type:\n");
    printf(" 1. Addition\n 2. Multiplication\n");
    printf("----------------------\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        comp_addition();
        break;
    case 2:
        comp_multiplication();
        break;
    default:
        printf("Invalid Enter. (Enter 1 or 2)\n");
        break;
    }    
}
void int_addition(void)
{
    int n1, n2;
    printf("Please first integer:\n");
    scanf("%d", &n1);
    printf("Please second integer:\n");
    scanf("%d", &n2);

    printf("Addition of the numbers: %d\n", n1 + n2);

}
void int_multiplication(void)
{
    int n1, n2;
    printf("Please enter the first integer:\n");
    scanf("%d", &n1);
    printf("Please enter the second integer:\n");
    scanf("%d", &n2);

    printf("Multiplication of the numbers: %d\n", n1 * n2);

}
void comp_addition(void)
{
    int n1, n2;
    int a1, a2;
    printf("Please enter the first complex number (Real part first):\n");
    scanf("%d", &n1);
    scanf("%d", &a1);
    printf("Please enter the second complex number (Real part first):\n");
    scanf("%d", &n2);
    scanf("%d", &a2);
    printf("Addition of numbers: %d + (%di)\n", n1 + n2, a1 + a2);
}
void comp_multiplication(void)
{
    int n1, n2;
    int a1, a2;
    int m1, m2;

    printf("Please enter the first complex number (Real part first):\n");
    scanf("%d", &n1);
    scanf("%d", &a2);
    printf("Please enter the second complex number (Real part first):\n");
    scanf("%d", &n2);
    scanf("%d", &a2);
    
    m1 = n1 * n2 - a1 * a2;
    m2 = n1 * a2 + n2 * a1;

    printf("Multiplication of numbers: %d + (%di)\n", m1, m2);
}

void shape_type(void)
{
    int choice;
    printf("Enter the shape type:\n");
    printf(" 1. Rectangle\n 2. Triangle\n 3. Circle\n");
    printf("----------------------\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        rectangle();
        break;
    case 2:
        triangle();
        break;
    case 3:
        circle();
        break;
    default:
        printf("Invalid Enter. (Enter 1 or 2)\n");
        break;
    }     
}
void rectangle(void)
{
    float n1, n2;
    printf("Please enter 1st edge:\n");
    scanf("%f", &n1);
    printf("Please enter 2nd edge:\n");
    scanf("%f", &n2);

    printf("Perimeter of rectangle: %.2f\n\n", (2 * (n1 + n2)));
    printf("Area of rectangle: %.2f\n", n1 * n2);    
}
void triangle(void)
{
    float n1, n2, n3;
    float s;
    float area;
    float p;

    printf("Please enter 1st edge:\n");
    scanf("%f", &n1);
    printf("Please enter 2nd edge:\n");
    scanf("%f", &n2);
    printf("Please enter 3rd edge:\n");
    scanf("%f", &n3);

    p = n1 + n2 + n3;
    s = p / 2;
    area = sqrt(s * (s - n1) * (s - n2) * (s - n3));
    

    printf("Perimeter of triangle: %f\n\n", p);
    printf("Area of triangle: %f\n", area); 

}
void circle(void)
{
    float radius;
    float perimeter, area;
    float pi = 3.1415926;

    printf("Please enter the radius:\n");
    scanf("%f", &radius);

    printf("Perimeter of circle: %.2f\n\n", (2 * pi * radius));
    printf("Area of circle: %.2f\n", (pi * radius * radius)); 

}

void temp_type(void)
{
    int choice;
    printf("Enter the calculation type:\n");
    printf(" 1. Fahrenheit to Kelvin\n 2. Kelvin to Fahrenheit\n");
    printf("----------------------\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        fah_to_kelv();
        break;
    case 2:
        kelv_to_fah();
        break;
    default:
        printf("Invalid Enter. (Enter 1 or 2)\n");
        break;
    } 
}

void fah_to_kelv(void)
{
    float f, k;
    printf("Please enter the temperature in Fahrenheit:\n");
    scanf("%f", &f);

    k = ((5 * (f - 32)) / 9) + 273.15;
    printf("Result: %f\n", k);

}
void kelv_to_fah(void)
{
    float f, k;
    printf("Please enter the temperature in Fahrenheit:\n");
    scanf("%f", &k);

    f = ((5 * (k - 273.15)) / 9 + 32);
    printf("Result: %f\n", k);
}