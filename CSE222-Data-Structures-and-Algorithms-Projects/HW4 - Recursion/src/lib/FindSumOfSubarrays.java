package lib;

public class FindSumOfSubarrays 
{
    /**
     * Private constructor. It is used to prevent the class from being instantiated.
     */
    private FindSumOfSubarrays() {}

    // ----------------------------------Question3---------------------------------- //
    
    /*
        Q3-
        Suppose that you are given an unsorted integer array. Propose a recursive solution to 
        find contiguous subarray/s that the sum of its/theirs items is equal to a given integer value. 
        Hint: Consider the following approach, 
        The first element can be a part of the contiguous subarray or not. You could perform two recursive calls based on these two cases.

        Number of subarrays should be N*(N+1)/2 (N = size of array)

        Example:

        int[] unsortedArray = 5, 12, 1, 2, 5, 4
        int target = 12

        Contiguous subarrays of unsortedArray and their sums:

        Sum: 29   5 12 1 2 5 4 
        Sum: 24   12 1 2 5 4 
        Sum: 12   1 2 5 4 
        Sum: 11   2 5 4 
        Sum: 9    5 4 
        Sum: 4    4 
        Sum: 25   5 12 1 2 5 
        Sum: 20   12 1 2 5 
        Sum: 8    1 2 5 
        Sum: 7    2 5 
        Sum: 5    5 
        Sum: 20   5 12 1 2 
        Sum: 15   12 1 2 
        Sum: 3    1 2 
        Sum: 2    2 
        Sum: 18   5 12 1 
        Sum: 13   12 1 
        Sum: 1    1 
        Sum: 17   5 12 
        Sum: 12   12 
        Sum: 5    5 
        

        The target value is 12,

        Sum: 12   1 2 5 4 
        Sum: 12   12 

        will be display to the screen.

    */

    /**
     * Call private findSumOfSubarrays() method with extended parameters.
     * 
     * @param unsortedArray The array that we're searching through.
     * @param target The sum of the subarray that we're looking for.
     */
    public static void findSumOfSubarrays(int[] unsortedArray, int target)
    {
        System.out.println("Subarrays that the sum of their items equal to the target:");
        findSumOfSubarrays(unsortedArray, target, 0, unsortedArray.length - 1);
    }

   /**
    * Find all the subarrays in the given array that sum up to the given target
    * 
    * @param unsortedArray The array that we're searching through.
    * @param target The sum of the subarray that we're looking for.
    * @param start The starting index of the subarray.
    * @param end The end index of the subarray.
    */
    private static void findSumOfSubarrays(int[] unsortedArray, int target, int start, int end)
    {
        if (start <= end)
        {
            // This is a way to check if the sum of the subarray is equal to the target.
            if (findSumInRange(unsortedArray, start, end) == target)
            {
                printArray(unsortedArray, start, end, false);
            }
            // Recursive call with shifting start position.
            findSumOfSubarrays(unsortedArray, target, start + 1, end);
        }
        if (start == end)
        {
            // Recrusive call with decreasing end of the array and set start position to 0.
            findSumOfSubarrays(unsortedArray, target, 0, end - 1);
        }
    }

    /**
     * Print the array in the given range.
     * 
     * @param array the array to be printed
     * @param start The index of the first element to print.
     * @param end The index of the last element in the array.
     */
    private static void printArray(int[] array, int start, int end, boolean isBrackedSetted) 
    {
        // Print the array in given range with brackets.
        if (start > end) 
        {
            System.out.println();
        }
        else
        {
            if (!isBrackedSetted)
            {
                System.out.print("[");
            }
            if (start == end)
            {
                System.out.print(array[start]);
                System.out.print("]");
                System.out.println();
            }
            else
            {
                System.out.print(array[start] + ", ");
                printArray(array, start + 1, end, true);
            }
        }
    }
    
    /**
     * Given an array of integers, find the sum of all the integers in the array between the start and
     * end indices (inclusive).
     * 
     * @param array The array to be searched
     * @param start The starting index of the range you want to sum
     * @param end The end index of the range.
     * @return The sum of the elements in the array.
     */
    private static int findSumInRange(int[] array, int start, int end) 
    {
        if (start > end) 
        {
            return 0;
        }
        else
        {
            return array[start] + findSumInRange(array, start + 1, end);
        }
    }
}


