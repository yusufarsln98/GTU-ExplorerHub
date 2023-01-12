#include <stdio.h>
#include <math.h>

#define N 3

typedef struct matrix_struct
{
    double mtr[N][N];
}matrix;

void print_matrix(matrix initial_matrix)
{
    int i, j;
    printf("\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%f\t", initial_matrix.mtr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix)
{

}
void determinant_of_matrix(matrix* initial_matrix)
{

}

typedef struct vectors
{
    double dim[3];
}vector;

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec)
{
    double angle;
    int i;

    angle = 0;

    output_vec->dim[0] = vec_1.dim[1] * vec_2.dim[2] - vec_1.dim[2] * vec_2.dim[1];
    output_vec->dim[1] = -1 * (vec_1.dim[0] * vec_2.dim[2] - vec_1.dim[2] * vec_2.dim[0]);
    output_vec->dim[2] = (vec_1.dim[0] * vec_2.dim[1] - vec_1.dim[1] * vec_2.dim[0]);

    for (i = 0; i < N; i++)
    {
        angle += vec_1.dim[i] * vec_2.dim[i];
    }
    angle /= sqrt((vec_1.dim[0] * vec_1.dim[0] + vec_1.dim[1] * vec_1.dim[1] + vec_1.dim[2] * vec_1.dim[2]) * 
                  (vec_2.dim[0] * vec_2.dim[0] + vec_2.dim[1] * vec_2.dim[1] + vec_2.dim[2] * vec_2.dim[2]));
    angle = acos(angle);
}

typedef struct polynomials
{
    double a;
    double b;
    double c;
    double d;
}third_order_polynomial;

typedef struct poly
{
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double g;

    char h;
    double sum;
}polynomial;

polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b)
{
    polynomial result;
    double sum;

    result.a = p1.a * p2.a;
    result.b = p1.a * p2.b + p2.a * p2.b;
    result.c = p1.a * p2.c + p1.b * p2.b + p1.c * p2.a;
    result.d = p1.a * p2.d + p1.b * p2.c + p1.c * p2.b + p1.d * p2.a;
    result.e = p1.b * p2.d + p1.c * p2.c + p1.d * p2.b;
    result.f = p1.c * p2.d + p1.d * p2.c;
    result.g = p1.d * p2.d;

    result.sum = result.a * pow(b, 7) / 7.0;
    result.sum += result.b * pow(b, 6) / 6.0;
    result.sum += result.c * pow(b, 5) / 5.0;
    result.sum += result.d * pow(b, 4) / 4.0;
    result.sum += result.e * pow(b, 3) / 3.0;
    result.sum += result.f * pow(b, 2) / 2.0;
    result.sum += result.g * pow(b, 1) / 1.0;

    sum = result.a * pow(a, 7) / 7.0;
    sum += result.b * pow(a, 6) / 6.0;
    sum += result.c * pow(a, 5) / 5.0;
    sum += result.d * pow(a, 4) / 4.0;
    sum += result.e * pow(a, 3) / 3.0;
    sum += result.f * pow(a, 2) / 2.0;
    sum += result.g * pow(a, 1) / 1.0;

    result.h = 'h';

    result.sum -= sum;

    return result;

}


int main()
{
    /* PART 1 */
    int i, j;

    matrix initial_matrix, inverted_matrix;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("Enter the value of matrix <[%d][%d]>:  ", i, j);
            scanf("%lf", &initial_matrix.mtr[i][j]);
        }
    }
    print_matrix(initial_matrix);
    inverse_matrix(&initial_matrix, &inverted_matrix);


    /* PART 2 */
    double angle;

    vector vec_1, vec_2, output_vec;
    for (i = 0; i < N; i++)
    {
        printf("Enter the %d. coordinate for 1st vector:  ", i + 1);
        scanf("%lf", &vec_1.dim[i]);
    }
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf("Enter the %d. coordinate for 2st vector:  ", i + 1);
        scanf("%lf", &vec_2.dim[i]);
    }
    angle = find_orthogonal(vec_1, vec_2, &output_vec);

    for (i = 0; i < N; i++)
    {
        printf("%f\n", output_vec.dim[i]);
    }
    printf("\nAngle: %f\n\n", angle);



    /* PART 3 */
    int a, b;
    third_order_polynomial p1, p2;
    polynomial final;
    
    printf("Enter first polynomail coefficients <ax^3 + bx^2 ..>\n");
    scanf("%lf %lf %lf %lf", &p1.a, &p1.b, &p1.c, &p1.d);

    printf("Enter 2nd polynomail coefficients <ax^3 + bx^2 ..>\n");
    scanf("%lf %lf %lf %lf", &p2.a, &p2.b, &p2.c, &p2.d);

    printf("Enter intervals (first min)\n");
    scanf("%d %d", &a, &b);

    final = get_integral(p1, p2, a, b);

    printf("%f ", final.a);
    printf("%f ", final.b);
    printf("%f ", final.c);
    printf("%f ", final.d);
    printf("%f ", final.e);
    printf("%f ", final.f);
    printf("%f ", final.g);
    printf("%c\n\n", final.h);

    printf("Integral: %f\n\n", final.sum);


    return 0;
}