#!/usr/bin/env python
# coding: utf-8

# In[ ]:


79
import numpy as np

#q2 calculate power with O(logn) complexity ( n = z+ so it is higher than zero)
def power(a,n):
    temp = 0
    if( n == 0):
        return 1

    temp = power(a , int(n/2))

    if n % 2 == 0:
        return temp * temp
    else:
        return a * temp * temp

def run_power():
    a = int( input("please enter base (a in a^n) = ") )
    n = int( input("please enter power (n in a^n) = ") )
    print("result: ",power(a,n))

#q3 solve puzzle
def puzzle(a):
    for i in range(9):
        for j in range(9):
            print(a[i][j],end = " ")
        print()


def solve(grid, row, col, num):
    for x in range(9):
        if grid[row][x] == num:
            return False
             
    for x in range(9):
        if grid[x][col] == num:
            return False
 
    startRow = row - row % 3
    startCol = col - col % 3
    for i in range(3):
        for j in range(3):
            if grid[i + startRow][j + startCol] == num:
                return False
    return True



def Suduko(grid, row, col):
 
    if (row == 9 - 1 and col == 9):
        return True
    if col == 9:
        row += 1
        col = 0
    if grid[row][col] > 0:
        return Suduko(grid, row, col + 1)
    for num in range(1, 9 + 1, 1): 
     
        if solve(grid, row, col, num):
         
            grid[row][col] = num
            if Suduko(grid, row, col + 1):
                return True
        grid[row][col] = 0
    return False


#driver function for sudoku
def run_sudoku(grid): 
    print("Q3 - sudoku")
    print("input:\n")
    puzzle(grid)
   
    print("output:\n")
    if (Suduko(grid, 0, 0)):
        puzzle(grid)
    else:
        print("Solution does not exist:(")



if __name__ == "__main__":
    
    print("q2:")
    run_power()

    
    print("\nq3:")
    # i dont add input to grid since it took too much time to take it
    grid = [[2, 5, 0, 0, 3, 0, 9, 0, 1],
        [0, 1, 0, 0, 0, 4, 0, 0, 0],
        [4, 0, 7, 0, 0, 0, 2, 0, 8],
        [0, 0, 5, 2, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 9, 8, 1, 0, 0],
        [0, 4, 0, 0, 0, 3, 0, 0, 0],
        [0, 0, 0, 3, 6, 0, 0, 7, 2],
        [0, 7, 0, 0, 0, 0, 0, 0, 3],
        [9, 0, 3, 0, 0, 0, 6, 0, 4]]
    run_sudoku(grid)


 


