#!/usr/bin/env python
# coding: utf-8

# In[ ]:


from random import shuffle
from random import randint

# --------------------- Question 1 ---------------------

def find_longest_path(longest_path, the_path, the_map, i, j, n, m):
    # Add the current cell to the path
    the_path.append(the_map[i][j])
    # If we have reached the end of the map
    if (i == n and j == m):
        # Add the path to the list of all paths
        if (sum(the_path) > sum(longest_path[0])):
            longest_path.insert(0, the_path.copy())
        # Create a new path
        the_path = []

    # If we have not reached the end of the map, then move to the next cell (i+1,j) or (i,j+1)
    if (i + 1 <= n and j <= m):
        find_longest_path(longest_path, the_path.copy(), the_map, i + 1, j, n, m)

    if (i <= n and j + 1 <= m):
        find_longest_path(longest_path, the_path.copy(), the_map, i, j + 1, n, m)

    # Return the list of all paths
    return longest_path[0]

def driverQ1():
    print("\nQuestion 1: Find the highest sum of the path from (0,0) to (n,m)\n")

    # Create random map sizes
    row = randint(3, 6)
    col = randint(3, 6)

    # Create a random map
    the_map = [[randint(1, 30) for i in range(col)] for j in range(row)]
    
    # Print the map
    print("Randomly Generated Map is:")
    for i in range(row):
        for j in range(col):
            print(the_map[i][j], end = "\t")
        print()
    
    longest_path = []   # The list of longest path (it is list of list to pass by reference)
    the_path = []       # The current path
    i = 0       # i is the row index
    j = 0       # j is the column index

    longest_path.append(the_map[0])

    # Find all the possible paths from (0,0) to (n,m) by moving to the next cell (i+1,j) or (i,j+1)
    the_path = find_longest_path(longest_path, the_path, the_map, i, j, row - 1, col - 1)
    
    # Find the highest sum of the path
    highest_sum = sum(the_path)

    # Print the range of the highest the_sum
    print("\nThe highest sum of the path from (0,0) to (" + str(row - 1) + "," + str(col - 1) + ") is: " + str(highest_sum))

    # Print the highest sum of the path, format 1 -> 2, 2 -> 3, 3 -> 4, 4 -> 5
    print("The path is: ", end = "")
    for i in range(len(the_path) - 1):
        if i != len(the_path) - 2:
            print(str(the_path[i]) + " -> " + str(the_path[i + 1]), end = ", ")
        else:
            print(str(the_path[i]) + " -> " + str(the_path[i + 1]))
    print()

    print("--------------------------------------------\n")

driverQ1()
# --------------------- Question 1 - END ---------------------


# --------------------- Question 2 ---------------------
# Quick Select Algorithm - Inspired in lecture and internet resources
def quickselect(array, k):
  # Choose pivot element
  pivot = array[0]
  
  # Partition array around pivot
  left, right = [], []
  for element in array:
    if element < pivot:
      left.append(element)
    elif element > pivot:
      right.append(element)
  
  # If pivot is kth smallest element, return it
  if k == len(left):
    return pivot
  
  # If kth smallest element is in left subarray, recursively apply algorithm to left subarray
  elif k < len(left):
    return quickselect(left, k)
  
  # If kth smallest element is in right subarray, recursively apply algorithm to right subarray
  else:
    return quickselect(right, k - len(left) - 1)

# Driver function to test the algorithm
def driverQ2():
    array = []
        # Create random array of size n
    n = randint(5, 15)
    for i in range(n):
        array.append(randint(1, 100))
    
    print("Question 2: Find the median of an array\n")
    print(f"Randomly generated array: {array}")
    # Find median of shuffled array
    shuffle(array)
    if len(array) % 2 == 0:
        # If array has even length, return average of two middle elements
        median = (quickselect(array, len(array) // 2) + quickselect(array, len(array) // 2 - 1)) / 2
    else:
        # If array has odd length, return middle element
        median = quickselect(array, len(array) // 2)
    print(f"Median of random array: {median}\n")
    
    # Find median of sorted array
    array.sort()
    print(f"Sorted array: {array}")
    if len(array) % 2 == 0:
        # If array has even length, return average of two middle elements
        median = (quickselect(array, len(array) // 2) + quickselect(array, len(array) // 2 - 1)) / 2
    else:
        # If array has odd length, return middle element
        median = quickselect(array, len(array) // 2)
    print(f"Median of sorted array: {median}\n")
    
    print("--------------------------------------------\n")

driverQ2()
# --------------------- Question 2 - END ---------------------



# --------------------- Question 3 ---------------------
# --------------------- Question 3.a ---------------------
class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

def create_circular_linked_list(start, end):
    head = Node(start)
    current = head
    for i in range(start + 1, end + 1):
        current.next = Node(i)
        current = current.next

    # Set the last node's next to the head, creating a circular linked list
    current.next = head 
    return head

def find_winner(n: int) -> int: 
    head = create_circular_linked_list(1, n)  # Create a circular linked list with n nodes
    pointer = head  # Set the pointer to the head of the list

    while pointer.next != pointer:          # While there is more than one node in the list
        pointer.next = pointer.next.next    # Eliminate the node pointed to by the pointer
        pointer = pointer.next              # Move the pointer to the next node

    return pointer.value    # Return the value of the node pointed to by the pointer (the winner)

def driverQ3a():
    # Test the functions
    print("Question 3.a Find winner of game by using circular linked list. O(n) \n")
    for i in range(1, 6):
        n = randint(5, 15)
        print("Number of players: " + str(n))
        print("Winner: " + str(find_winner(n)) + "\n")

driverQ3a()

# --------------------- Question 3.b ---------------------
def find_winner(players: list) -> int:

    # If there is only one player, then it is the winner
    if len(players) == 1:
        return players[0]

    # If there are more than one player, then eliminate the second players
    # There are 2 cases:
        #  1. If there are odd number of players, then the last player will be add as the first player and
        #     all even index players will be eliminated

        #  2. If there are even number of players, then all even index players will be eliminated

    winners = []
    if len(players) % 2 == 0:
        for i in range(0, len(players), 2):
            winners.append(players[i])
    else:
        winners.append(players[-1])
        for i in range(0, len(players) - 1, 2):
            winners.append(players[i])

    # Call the function recursively
    return find_winner(winners)

def driver3b():
    # Test the function
    print("\n\nQuestion 3.b Find winner of game by decrease-and-conquer algorithm. O(logn) \n")
    for i in range(1, 6):
        n = randint(5, 15)
        players = [i for i in range(1, n + 1)]
        print("Number of players: " + str(n))
        print("Winner: " + str(find_winner(players)) + "\n")
    print("\n--------------------------------------------\n")

driver3b()
# --------------------- Question 3 - END ---------------------

