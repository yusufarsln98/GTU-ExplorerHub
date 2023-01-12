package lib;

public class FindItemNumber 
{
    /**
     * Private constructor. It is used to prevent the class from being instantiated.
     */
    private FindItemNumber(){}

    // ----------------------------------Question2---------------------------------- //

    /*
        Q2-
        Suppose that you are given a sorted integer array. Suggest a recursive algorithm to find the 
        number of items in the array between two given integer values. 
        Hint: Consider an approach like binary search algorithm; compare given two integers with the middle element.

        case1:
            Upper bound can be smaller then smallest element of the array.
                Result will be 0.

        case2:
            Lower bound can be larger then largest element of the array.
                Result will be 0.

        case3:
            Lower or upper bound not have to be the element of the array, therefore, they should be handled separately.

    */

    /**
     * Find the number of items in the array that are between the lower and upper bounds.
     * 
     * @param sortedArray The sorted array to search
     * @param lowerBound The lower bound of the range.
     * @param upperBound The upper bound of the range.
     * @return The number of items between the lower and upper bound.
     */
    public static int findItemNumber(int[] sortedArray, int lowerBound, int upperBound)
    {
        if (upperBound < lowerBound)
            throw new IllegalArgumentException("Upper bound can't be lower than the lower bound!");
        if (sortedArray == null)
            throw new IllegalStateException("Array cannot be null!");

        // Call the recursive method.
        return findItemNumber(sortedArray, lowerBound, upperBound, 0, sortedArray.length - 1);
    }

    /**
     * Given a sorted array, find the number of items that fall within a given range
     * 
     * @param sortedArray The sorted array of integers
     * @param lowerBound The lower bound of the range
     * @param upperBound The upper bound of the range.
     * @param start The index of the first element in the array
     * @param end The index of the last element in the array.
     * @return The number of items in the array that are within the given range.
     */
    private static int findItemNumber(int[] sortedArray, int lowerBound, int upperBound, int start, int end) 
    {
        if (start > end) 
            return 0;
        int mid = (start + end) / 2;
        // If the item in the range, check right and left side of the item.
        if (sortedArray[mid] >= lowerBound && sortedArray[mid] <= upperBound)
            return 1 + findItemNumber(sortedArray, lowerBound, upperBound, start, mid - 1) + findItemNumber(sortedArray, lowerBound, upperBound, mid + 1, end);
        // If the element greater then the lower bound, we don't need to check the right side of array anymore.
        else if (sortedArray[mid] > lowerBound)
            return findItemNumber(sortedArray, lowerBound, upperBound, start, mid - 1);    
        // If the element smaller then the upper bound, we don't need to check the left side of the array anymore.
        else 
            return findItemNumber(sortedArray, lowerBound, upperBound, mid + 1, end);   
    }

}