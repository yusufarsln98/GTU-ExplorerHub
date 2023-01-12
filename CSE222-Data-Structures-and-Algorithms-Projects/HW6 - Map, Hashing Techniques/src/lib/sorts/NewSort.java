package lib.sorts;

/**
 * The `NewSort` class contains a private constructor
 * public static method `sort` that takes an array of comparable objects and
 * sorts it.
 */
public class NewSort 
{
    // A private constructor. It prevents the class from being instantiated.
    private NewSort(){}

    /** Sort the table using the quicksort algorithm. 
     * @pre table contains Comparable objects. 
     * @post table is sorted.
     * @param table The array to be sorted
    */
    public static <T extends Comparable<T>> void sort(T[] table) 
    {
        int[] minMax = new int[2];
        // Sort the whole table.
        newSort(table, 0, table.length - 1, minMax); 
    }
    
    /**
     * If the head is less than the tail, set the min and max, swap the head and min, swap the tail and
     * max, and call the function again
     * 
     * @param table the array to be sorted
     * @param head the index of the first element in the array
     * @param tail the last index of the array
     */
    private static <T extends Comparable<T>> void newSort(T[] table, int head, int tail, int[] minMax) 
    {
       if (head < tail)
       {
            minMax[0] = tail;
            minMax[1] = tail;   
            minMaxFinder(table, head, tail, minMax);
            swap(table, head, minMax[0]);
            swap(table, tail, minMax[1]);
            newSort(table, head + 1, tail - 1, minMax);
       }
    }

    /**
     * It takes an array of comparable objects, and returns the indices of the minimum and maximum
     * elements in the array
     * 
     * @param table the array to be sorted
     * @param head the index of the first element in the array
     * @param tail the last index of the array
     * @param minMax an array of two integers, the first one is the index of the minimum element in the
     * array, the second one is the index of the maximum element in the array.
     */
    private static <T extends Comparable<T>> void minMaxFinder(T[] table, int head, int tail, int[] minMax) 
    {
        if (head < tail)
        {
            int middle = (head + tail) / 2;
            if (table[middle].compareTo(table[minMax[0]]) < 0)
            {
                minMax[0] = middle;
            }
            if (table[middle].compareTo(table[minMax[1]]) > 0)
            {
                minMax[1] = middle;
            }
            minMaxFinder(table, head, middle, minMax);
            minMaxFinder(table, middle + 1, tail, minMax);
        }
    }

    /** Swap the values at two indices in the table. 
     * @param table The table containing the values to be swapped 
     * @param index1 The index of the first value to be swapped 
     * @param index2 The index of the second value to be swapped 
    */
    private static <T extends Comparable<T>> void swap(T[] table, int index1, int index2) 
    {
        T temp = table[index1]; 
        table[index1] = table[index2]; 
        table[index2] = temp; 
    }
}
