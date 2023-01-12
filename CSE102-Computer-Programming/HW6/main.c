#include <stdio.h>
#include <stdlib.h>

#define N 4     /* Define size of N x N matrix. */

/* Enumerated types. */
typedef enum {squeeze, left, right, up, down, stop} directiont;   
typedef enum {FALSE, TRUE} booleant;

void fill_array(int arr[][N]);  
void print_maze(int arr[][N]);

booleant is_number_exist(int arr[][N], int r);  /* Controls repeated numbers. */
booleant is_sorted(int arr[][N]);               /* Controls if maze sorted. */

/* arr --> array, x and y --> coordinates, dir --> direction */
directiont can_shift(int arr[][N], int x, int y, directiont dir);   /* Controls if move is possible. */

void shift_left(int arr[][N], int x, int y);            /* Shift left */
void shift_right(int arr[][N], int x, int y);           /* Shift right */
void shift_up(int arr[][N], int x, int y);              /* Shift up */
void shift_down(int arr[][N], int x, int y);            /* Shift down */

void find_zero(int arr[][N], int *x_zero, int *y_zero); /* Finds where is the blank */

int main(void)
{

    int maze[N][N];             /* Decleare N x N matrix. */
    directiont direction;       /* Direction */
    directiont flag = squeeze;  /* Flag for return direction */
    int x, y;                   /* Coordinates */

    fill_array(maze);   /* Fill maze */
    print_maze(maze);   /* Print maze */

    while (is_sorted(maze) == FALSE)    /* Continue the loop until maze will be sorted */
    {

        printf("\nEnter direction: \n(Left: 1, Right: 2, Up: 3, Down: 4 (To Finish: 5)) -->  ");
        scanf("%uud", &direction);
        printf("\n");

        if (direction == stop)
        {
            printf("You quit the game.\n\n");
            break;
        }

        printf("Enter coordinate \nFirst number <0 0>, Last number <3 3> -->  ");
        scanf("%d %d", &x, &y);
        
        flag = can_shift(maze, x, y, direction);    /* Keeps the direction user want to shift */

        switch (flag)
        {
        case left:
            shift_left(maze, x, y);
            break;
        case right:
            shift_right(maze, x, y);
            break;
        case up:
            shift_up(maze, x, y);
            break;
        case down:
            shift_down(maze, x, y);
            break;
        case squeeze:
            printf("\n!! You cannot move in this direction !!\n");
            break;
        }
        print_maze(maze);
    }
    if (is_sorted(maze) == TRUE)
    {
        printf("You won the game.\n\n");
    }
    
}

void fill_array(int arr[][N])
{
    int randNumber;     /* Keeps random number */   
    booleant INE;       /* Is number exist */
	int i, j;           /* Loop initializer */
	
    /* Fill the array with the -1 as initial values. */
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            arr[i][j] = -1;
        }
    }

    /* Fill the array with random numbers. 
       !! WARNING - IN 4 x 4 array blank can be locate in right bottom corner but it is totally random.
       You can check with changing the defined N (size)*/
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            while (i != N || j != N)
            {
                randNumber = rand() % (N * N);          /* Randomly fill the number from 1 to N * N */
                INE = is_number_exist(arr, randNumber); /* Check if the current number is being used before. */
                if (INE == FALSE)                       /* If did not, Then fill the array with this number. */
                {
                    arr[i][j] = randNumber;
                    break;
                }
            } 
        }
    }
}

/* returns a booleant enum, arr --> maze, r --> random number */
booleant is_number_exist(int arr[][N], int r)
{
    int i, j;
    
    /* This loop controls if the r is being used before. */
	for (i = 0; i < N; i++)     
    {
        for (j = 0; j < N; j++)
        {
            if (arr[i][j] == r) /* If used, then return TRUE */
            {
                return TRUE;
            }
        }
    }
    return FALSE;               /* If did not used, then return FALSE */
}

/* returns a booleant enum if GAME OVER. */
booleant is_sorted(int arr[][N])
{
    int flag = 0;
    int n = 1;
	int i, j;
	
    /* Controls if maze sorted from 1 to (N * N - 1) and finally blank */
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == N - 1 && j == N - 1)
            {
                break;
            }
            if (arr[i][j] == n)
            {
                flag++;
            }
            n++;
        }
    }
    if (flag == N * N - 1)  /* If sorted, then return TRUE.*/
    {
        return TRUE;
    }
    else                    /* Else, return FALSE */
    {
        return FALSE;
    }
}

/* Controls row and columns then decide if moving is possible. */
directiont can_shift(int arr[][N], int x, int y, directiont dir)
{
    int flag = 0;

    if (arr[x][y] == 0)         /* If coordinates indicates blank, then return SQUEEZE */
    {
        return squeeze;
    }
    else if (dir == left)       /* If user want to move left */
    {
        while (y >= 0)          /* Control the row */
        {
            if (arr[x][y] == 0) 
            {
                flag++;
            }
            y--;
        }
        if (flag == 0)          /* If there is not blank */
        {
            return squeeze;     /* Return SQUEEZE */
        }       
        else                    /* Else if, there is blank */
        {   
            return left;        /* Return LEFT */
        }
    }
    else if (dir == right)      /* If user want to move right */
    {
        while (y < N)           /* Control the row */
        {
            if (arr[x][y] == 0)
            {
                flag++;
            }
            y++;
        }
        if (flag == 0)          /* If there is not blank */
        {
            return squeeze;     /* Return SQUEEZE */
        }
        else                    /* Else if, there is blank */
        {   
            return right;       /* Return RIGHT */
        }
    }
    else if (dir == up)         /* If user want to move up */
    {
        while (x >= 0)          /* Control the column */
        {
            if (arr[x][y] == 0) 
            {
                flag++;
            }
            x--;
        }
        if (flag == 0)          /* If there is not blank */
        {
            return squeeze;     /* Return SQUEEZE */
        }
        else                    /* Else if, there is blank */
        {
            return up;          /* Return UP */
        }
    }
    else if (dir == down)       /* If user want to move down */
    {
        while (x < N)           /* Control the column */
        {
            if (arr[x][y] == 0) 
            {
                flag++;
            }
            x++;
        }
        if (flag == 0)          /* If there is not blank */  
        {
            return squeeze;     /* Return SQUEEZE */
        }
        else                    /* Else if, there is blank */
        {
            return down;        /* Return DOWN */
        }       
    }
}

void shift_left(int arr[][N], int x, int y)
{
    int x_zero, y_zero; /* Address of 0 (blank) */
    int temp, num, i;   /* Variabless */
    int KVS[N];         /* Keeps the Values */

    temp = y;           /* go to --> row 267 */           
	
    find_zero(arr, &x_zero, &y_zero);   /* Find the address of blanks */
    num = y - y_zero;

    /* Keep the values from coordinates to 0 */
    for (i = 0; i < num; i++)
    {
        KVS[i] = arr[x][y];
        y--;
    }

    /* Then replace the blank with the coordinate. */
    arr[x][temp] = 0;

    /* Then shift the blanks */
    for (i = 0; i < num; i++)
    {
        arr[x][temp - 1] = KVS[i];
        temp--;
    }
}
void shift_right(int arr[][N], int x, int y)
{
    int x_zero, y_zero; /* Address of 0 (blank) */
    int temp, num, i;   /* Variabless */
    int KVS[N];         /* Keeps the Values */

    temp = y;           /* go to --> row 296 */ 
	
    find_zero(arr, &x_zero, &y_zero);   /* Find the address of blanks */
    num = y_zero - y;

    /* Keep the values from coordinates to 0 */
    for (i = 0; i < num; i++)
    {
        KVS[i] = arr[x][y];
        y++;
    }

    /* Then replace the blank with the coordinate. */
    arr[x][temp] = 0;

    /* Then shift the blanks */
    for (i = 0; i < num; i++)
    {
        arr[x][temp + 1] = KVS[i];
        temp++;
    }
}
void shift_up(int arr[][N], int x, int y)
{
    int x_zero, y_zero; /* Address of 0 (blank) */
    int temp, num, i;   /* Variabless */
    int KVS[N];         /* Keeps the Values */

    temp = x;           /* go to --> row 324 */ 
	
    find_zero(arr, &x_zero, &y_zero);   /* Find the address of blanks */
    num = x - x_zero;

    /* Keep the values from coordinates to 0 */
    for (i = 0; i < num; i++)
    {
        KVS[i] = arr[x][y];
        x--;
    }

    /* Then replace the blank with the coordinate. */
    arr[temp][y] = 0;

    /* Then shift the blanks */
    for (i = 0; i < num; i++)
    {
        arr[temp - 1][y] = KVS[i];
        temp--;
    }
}
void shift_down(int arr[][N], int x, int y)
{
    int x_zero, y_zero; /* Address of 0 (blank) */
    int temp, num, i;   /* Variabless */
    int KVS[N];         /* Keeps the Values */

    temp = x;           /* go to --> row 352 */
	
    find_zero(arr, &x_zero, &y_zero);   /* Find the address of blanks */
    num = x_zero - x;

    /* Keep the values from coordinates to 0 */
    for (i = 0; i < num; i++)
    {
        KVS[i] = arr[x][y];
        x++;
    }

    /* Then replace the blank with the coordinate. */
    arr[temp][y] = 0;

    /* Then shift the blanks */
    for (i = 0; i < num; i++)
    {
        arr[temp + 1][y] = KVS[i];
        temp++;
    }
}

/* Find the location of zero then pass the dereference of coordinate variables x and y */
void find_zero(int arr[][N], int *x_zero, int *y_zero)
{
    int i, j;   /* Loop initializers */
    
    /* Loop for finding the coordinate of 0(blank) */
	for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (arr[i][j] == 0)
            {
                *x_zero = i;
                *y_zero = j;
                return;
            }
        }
    }
}

/* Print current maze */
void print_maze(int arr[][N])
{
    int i, j,       /* Loop initializer */ 
        row, clm;   /* Row and column of maze */
    char ast = '*';
    char bln = ' ';

    row = 0, clm = 0;

    printf("\n");
    for (i = 0; i < 4 * N + 1; i++)             /* There are 4 * N + 1 rows in the table */
    {
        for (j = 0; j < 5 * N + 1; j++)         /* There is 5 * N + 1 columns in the table */
        {
            if (i % 4 == 0)                     /* Print outer and inner lines with *'s */
            {
                printf("%c", ast);
            }
            else if (i % 4 == 1 || i % 4 == 3)  /* Print outer and inner lines with *'s or blanks in condition */
            {
                if (j % 5 == 0)                 
                {
                    printf("%c", ast);
                }
                else
                {
                    printf("%c", bln);
                }
            }
            else if (i % 4 == 2)                /* Print outer and inner lines with *'s or number or blanks in condition */
            {
                if (j % 5 == 0)
                {
                    printf("%c", ast);
                }
                else if (j % 5 == 1 || j % 5 == 4)
                {
                    printf("%c", bln);
                } 
                else if(j % 5 == 2)
                {
                    if (arr[row][clm] != 0)
                    {
                        printf("%-2d", arr[row][clm]);
                    }
                    else
                    {
                        printf("%2c", bln);
                    }
                    clm++;
                }
            }
        }
        if (i % 4 == 2)
        {
            row++;
        }
        clm = 0;
        printf("\n");
    }
}
