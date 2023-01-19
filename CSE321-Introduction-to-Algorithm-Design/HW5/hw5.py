#!/usr/bin/env python
# coding: utf-8

# In[ ]:


# Random class
from random import randint

# Question 1
print("Question 1: Find the longest common prefix of a list of words\n")
def longest_common_prefix(strings):
    if len(strings) == 1:
        return strings[0]

    mid = len(strings) // 2
    # Find the longest common prefix of the left and right halves
    left = longest_common_prefix(strings[:mid])
    right = longest_common_prefix(strings[mid:])

    i = 0
    while i < len(left) and i < len(right) and left[i] == right[i]:
        i += 1

    return left[:i]

def Q1():
    strings = ["programmable", "programming", "programmer", "programmatic", "programmability"]
    lcp = longest_common_prefix(strings)
    print(strings)
    print(f"Longest common prefix: {lcp}")
    
    strings = ["compute", "compatible", "computer", "compare", "compactness"]
    lcp = longest_common_prefix(strings)
    print(strings)
    print(f"Longest common prefix: {lcp}")
    
    # User input
    strings = input("Enter words: ").split()
    lcp = longest_common_prefix(strings)
    print(f"Longest common prefix: {lcp}")

Q1()
print("--------------------------------------------\n\n")


# Question 3
print("Question 3: Find the longest increasing subarray of an array\n")
def longest_increasing_subarray(arr):
    # Initialize the table with the first element of the input array
    table = [1]
    # Iterate through the input array, starting from the second element
    for i in range(1, len(arr)):
        # If the current element is greater than the previous element
        if arr[i] > arr[i-1]:
            # Set the value at the current index in the table to be one more than the value at the previous index
            table.append(table[i-1] + 1)
        else:
            # Set the value at the current index to 1
            table.append(1)
    # Return the maximum value
    return max(table)

def Q3():
    arr1 = [1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7]
    arr2 = [1, 2, 3, 4, 1, 2, 3, 5, 2, 3, 4]

    print(arr1)
    print(longest_increasing_subarray(arr1)) # should print 5

    print(arr2)
    print(longest_increasing_subarray(arr2)) # should print 4

    # User input
    arr = input("Enter numbers: ").split()
    arr = [int(x) for x in arr]
    print(longest_increasing_subarray(arr))

Q3()
print("--------------------------------------------\n\n")


# Question 4
print("Question 4: Find the longest path in a the_map\n")
print("Using dynamic programming\n")
def longest_path_dp(the_map):
    # Create a the_map to store the results of subproblems
    longest_paths = [[0 for j in range(len(the_map[0]))] for i in range(len(the_map))]
    # Create a the_map to store the direction of the path (0 = from left, 1 = from top)
    directions = [[0 for j in range(len(the_map[0]))] for i in range(len(the_map))]
    
    # Initialize the first element to be the starting point
    longest_paths[0][0] = the_map[0][0]
    
    # Initialize the first column of the the_map to be the sum of the previous value and the current value
    for i in range(1, len(the_map)):
        longest_paths[i][0] = longest_paths[i-1][0] + the_map[i][0]
        directions[i][0] = 1  # Mark the direction as coming from the top
    
    # Initialize the first row of the the_map to be the sum of the previous value and the current value
    for j in range(1, len(the_map[0])):
        longest_paths[0][j] = longest_paths[0][j-1] + the_map[0][j]
        directions[0][j] = 0  # Mark the direction as coming from the left
    
    # Fill in the rest of the the_map using dynamic programming
    for i in range(1, len(the_map)):
        for j in range(1, len(the_map[0])):
            # The longest path to the current position is the maximum of the path from the top and the path from the left
            if longest_paths[i-1][j] > longest_paths[i][j-1]:
                longest_paths[i][j] = longest_paths[i-1][j] + the_map[i][j]
                directions[i][j] = 1  # Mark the direction as coming from the top
            else:
                longest_paths[i][j] = longest_paths[i][j-1] + the_map[i][j]
                directions[i][j] = 0  # Mark the direction as coming from the left
    
    # Initialize the path with the last element in the the_map
    path = [(len(the_map)-1, len(the_map[0])-1)]
    
    # Follow the directions the_map backwards to find the path
    i = len(the_map)-1
    j = len(the_map[0])-1
    while i > 0 or j > 0:
        if directions[i][j] == 1:
            i -= 1
        else:
            j -= 1
        path.append((i, j))
    
    # Reverse the path so it starts at the beginning
    path = path[::-1]
    
    return path

def Q3dp():
    # Test the function
    the_map = [[25, 30, 25], [45, 15, 11], [1, 88, 15], [9, 4, 23]]
    
    print("The map:")
    for row in the_map:
        print(row)

    print("Longest path:")
    print(longest_path_dp(the_map))

    print("Sum of the path:")
    print(sum([the_map[i][j] for i, j in longest_path_dp(the_map)]))

    # User input
    the_map = []
    while True:
        row = input("Enter row:").split()
        if row == []:
            break
        row = [int(x) for x in row]
        the_map.append(row)

    print("The map:")
    for row in the_map:
        print(row)

    print("Longest path:")
    print(longest_path_dp(the_map))

    print("Sum of the path:")
    print(sum([the_map[i][j] for i, j in longest_path_dp(the_map)]))

Q3dp()
print("--------------------------------------------\n\n")

print("Using greedy algorithm\n")
def longest_path_greedy(the_map):
    # Initialize the path with the starting point
    path = [(0, 0)]
    
    # Initialize the current position
    i = 0
    j = 0
    
    # Keep looping until the end of the the_map is reached
    while i < len(the_map)-1 or j < len(the_map[0])-1:
        # If we can move down and it leads to a longer path, move down
        if i < len(the_map)-1 and (j == len(the_map[0])-1 or the_map[i+1][j] > the_map[i][j+1]):
            i += 1
        # Otherwise, move right
        else:
            j += 1
        
        # Add the new position to the path
        path.append((i, j))
    
    return path

def Q3greedy():
    # Test the function
    the_map = [[25, 30, 25], [45, 15, 11], [1, 88, 15], [9, 4, 23]]
    print("The map:")
    for row in the_map:
        print(row)
    print("Longest path:")
    print(longest_path_greedy(the_map))  # Output: [(0, 0), (1, 0), (1, 1), (2, 1), (2, 2), (3, 2)] 
    print("Sum of the path:")
    print(sum([the_map[i][j] for i, j in longest_path_greedy(the_map)]))
    
    # User input
    the_map = []
    while True:
        row = input("Enter row:").split()
        if row == []:
            break
        row = [int(x) for x in row]
        the_map.append(row)
    print("Longest path:")
    print(longest_path_dp(the_map))

    print("Sum of the path:")
    print(sum([the_map[i][j] for i, j in longest_path_dp(the_map)]))

Q3greedy()
print("--------------------------------------------\n\n")



