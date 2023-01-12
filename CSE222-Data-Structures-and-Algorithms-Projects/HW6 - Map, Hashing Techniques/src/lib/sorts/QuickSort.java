package lib.sorts;

/** Implements the revised quick sort algorithm. */ 
public class QuickSort 
{ 
    // A private constructor. It prevents the class from being instantiated.
    private QuickSort(){}
    
    /** Sort the table using the quicksort algorithm. 
     * @pre table contains Comparable objects. 
     * @post table is sorted.
     * @param table The array to be sorted
    */
    public static <T extends Comparable<T>> void sort(T[] table) 
    { 
        // Sort the whole table.
        quickSort(table, 0, table.length - 1); 
    }
    
    /** Sort a part of the table using the quicksort algorithm. 
     * @post The part of table from first through last is sorted. 
     * @param table The array to be sorted 
     * @param first The index of the low bound @param last The index of the high bound
    */
    private static <T extends Comparable<T>> void quickSort(T[] table, int first, int last) 
    {
        if (first < last) 
        { 
            // There is data to be sorted. 
            // Partition the table.
            int pivIndex = partition(table, first, last); 
            // Sort the left half.
            quickSort(table, first, pivIndex - 1); 
            // Sort the right half.
            quickSort(table, pivIndex + 1, last); 
        } 
    }
    
    /** Partition the table so that values from first to pivIndex 
     * are less than or equal to the pivot value, and values from 
     * pivIndex to last are greater than the pivot value. 
     * @param table The table to be partitioned 
     * @param first The index of the low bound 
     * @param last The index of the high bound 
     * @return The location of the pivot value
    */
    private static <T extends Comparable<T>> int partition(T[] table, int first, int last) 
    {
        /* Put the median of table[first], table[middle], 
           table[last] into table[first], and use this value as the pivot.
        */
        sort3(table, first, last); 
        // Swap first element with median. 
        swap(table, first, (first + last) / 2);

        // Select the first item as the pivot value. 
        T pivot = table[first]; 
        int up = first; 
        int down = last; 
        do 
        {
            /* Invariant: All items in table[first . . . up ‐ 1] <= pivot 
            All items in table[down + 1 . . . last] > pivot
            */
            while ((up < last) && (pivot.compareTo(table[up]) >= 0)) 
            { 
                up++;
            }
            // assert: up equals last or table[up] > pivot. 
            while (pivot.compareTo(table[down]) < 0) 
            { 
                down--;
            }
            // assert: down equals first or table[down] <= pivot. 
            if (up < down) 
            { 
                // if up is to the left of down. 
                // Exchange table[up] and table[down]. 
                swap(table, up, down);
            }
        } while (up < down); 
        // Repeat while up is left of down. 
        // Exchange table[first] and table[down] thus putting the 
        // pivot value where it belongs. 
        swap(table, first, down); 
        // Return the index of the pivot value. 
        return down;
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

    /** Sort table[first], table[middle], and table[last]. 
    @param table The table to be sorted 
    @param first Index of the first element 
    @param last Index of the last element
    */ 
    private static <T extends Comparable<T>> void sort3(T[] table, int first, int last) 
    {
        int middle = (first + last) / 2; 
        /* Sort table[first], table[middle], table[last]. */
        if (table[middle].compareTo(table[first]) < 0) 
        { 
            swap(table, first, middle);
        }
        // assert: table[first] <= table[middle] 
        if (table[last].compareTo(table[middle]) < 0) 
        { 
            swap(table, middle, last);
        }
        // assert: table[last] is the largest value of the three. 
        if (table[middle].compareTo(table[first]) < 0) 
        { 
            swap(table, first, middle);
        } 
        // assert: table[first] <= table[middle] <= table[last]. 
    }
}