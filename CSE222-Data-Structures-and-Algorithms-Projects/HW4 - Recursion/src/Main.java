import java.util.Arrays;
import lib.*;

public class Main 
{
    /**
     * Main method. It is used to test the classes.
     */
    public static void main(String[] args) 
    {
        driverFindOccurrence();
        driverFindItemNumber();
        driverFindSumOfSubarrays();
        driverDisplayBlocks();
    }

    /**
     * Find the index of the nth occurrence of a substring in a string
     */
    private static void driverFindOccurrence() 
    {
        System.out.println("\n-------------- Problem 1 --------------\n");
     
        int position;
        String query;
        String str;
        int occurrence;
        // --------------------------------- 1st example ---------------------------------
        System.out.println("----- 1st example -----\n");
        query = "string";
        str = "Search query string in a large string, find index of 'n'th occurrence of the string.";
        occurrence = 1;
        position = FindOccurrence.findOccurrence(query, str, occurrence);

        System.out.println("str = '" + str + "'");
        System.out.println("query = '" + query + "'");
        System.out.println("occurrence = " + occurrence);
        System.out.println("position = " + position);
        System.out.println();

        // --------------------------------- 2nd example ---------------------------------
        System.out.println("----- 2nd example -----\n");
        query = "aa";
        str = "zzaaabbccaadd";
        occurrence = 2;
        position = FindOccurrence.findOccurrence(query, str, occurrence);

        System.out.println("str = '" + str + "'");
        System.out.println("query = '" + query + "'");
        System.out.println("occurrence = " + occurrence);
        System.out.println("position = " + position);
        System.out.println();
        
        // --------------------------------- 3rd example ---------------------------------
        System.out.println("----- 3rd example -----\n");
        query = "aa";
        str = "aaabbc";
        occurrence = 4;
        position = FindOccurrence.findOccurrence(query, str, occurrence);

        System.out.println("str = '" + str + "'");
        System.out.println("query = '" + query + "'");
        System.out.println("occurrence = " + occurrence);
        System.out.println("position = " + position);
        System.out.println();

    }
    
    /**
     * Given a sorted array of integers, find total number of items in the array that in the given range.
     */
    private static void driverFindItemNumber() 
    {
        System.out.println("\n-------------- Problem 2 --------------\n");

        int result;
        int[] sortedArray;
        int lowerBound;
        int upperBound;

        // --------------------------------- 1st example ---------------------------------
        System.out.println("----- 1st example -----\n");
        sortedArray = new int[]{4, 8, 15, 16, 23, 42};
        lowerBound = -5;
        upperBound = 0;
        result = FindItemNumber.findItemNumber(sortedArray, lowerBound, upperBound);

        System.out.println("sortedArray = " + Arrays.toString(sortedArray));
        System.out.println("lowerBound = " + lowerBound);
        System.out.println("upperBound = " + upperBound);
        System.out.println("result: " + result);
        System.out.println();

        // --------------------------------- 2nd example ---------------------------------
        System.out.println("----- 2nd example -----\n");
        sortedArray = new int[]{1, 3, 4, 8, 12, 16, 17, 19, 22, 24, 30};
        lowerBound = -4;
        upperBound = 32;
        result = FindItemNumber.findItemNumber(sortedArray, lowerBound, upperBound);

        System.out.println("sortedArray = " + Arrays.toString(sortedArray));
        System.out.println("lowerBound = " + lowerBound);
        System.out.println("upperBound = " + upperBound);
        System.out.println("result: " + result);
        System.out.println();

        // --------------------------------- 3rd example ---------------------------------
        System.out.println("----- 3rd example -----\n");
        sortedArray = new int[]{1, 3, 4, 8, 12, 16, 17, 19, 22, 24, 30};
        lowerBound = 9;
        upperBound = 17;
        result = FindItemNumber.findItemNumber(sortedArray, lowerBound, upperBound);

        System.out.println("sortedArray = " + Arrays.toString(sortedArray));
        System.out.println("lowerBound = " + lowerBound);
        System.out.println("upperBound = " + upperBound);
        System.out.println("result: " + result);
        System.out.println();
    }
    
    /**
     * Given an unsorted array of integers, find the sum of all the 
     * contiguous subarrays that equals to the target value.
     */
    private static void driverFindSumOfSubarrays() 
    {
        System.out.println("\n-------------- Problem 3 --------------\n");

        int[] unsortedArray;
        int target;

        // --------------------------------- 1st example ---------------------------------
        System.out.println("----- 1st example -----\n");
        unsortedArray = new int[]{5, 12, 1, 2, 5, 4, 8};
        target = 23;

        System.out.println("unsortedArray = " + Arrays.toString(unsortedArray));
        System.out.println("target = " + target);
        FindSumOfSubarrays.findSumOfSubarrays(unsortedArray, target);
        System.out.println();

        // --------------------------------- 2nd example ---------------------------------
        System.out.println("----- 2nd example -----\n");
        unsortedArray = new int[]{2, 10, 12, 3, 1, 6, 3, 5, 1, 2, 1, 5, 8, 4, 7, 1, 24};
        target = 12;

        System.out.println("unsortedArray = " + Arrays.toString(unsortedArray));
        System.out.println("target = " + target);
        FindSumOfSubarrays.findSumOfSubarrays(unsortedArray, target);
        System.out.println();

        // --------------------------------- 3rd example ---------------------------------
        System.out.println("----- 3rd example -----\n");
        unsortedArray = new int[]{1, 2, 3, 4, 3, 2, 1};
        target = 6;

        System.out.println("unsortedArray = " + Arrays.toString(unsortedArray));
        System.out.println("target = " + target);
        FindSumOfSubarrays.findSumOfSubarrays(unsortedArray, target);
        System.out.println();
    }
    
    /**
     * Display the blocks.
     */
    private static void driverDisplayBlocks()
    {
        System.out.println("\n-------------- Problem 5 --------------\n");
        DisplayBlocks.displayBlocks(8);
    }
}

