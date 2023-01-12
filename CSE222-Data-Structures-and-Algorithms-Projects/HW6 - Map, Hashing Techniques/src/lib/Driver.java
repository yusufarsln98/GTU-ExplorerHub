package lib;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

import lib.hashbst.HashTableChainBST;
import lib.hashhybrid.HashTableHybrid;
import lib.sorts.MergeSort;
import lib.sorts.QuickSort;
import lib.sorts.NewSort;

/**
 * It tests the sorting algorithms and the bst chain hash table and the hybrid hash table
 */
public class Driver 
{
    private Driver(){}
    

    /**
     * This function tests the three sorting algorithms on three different sized arrays.
     * Sorting algorithms:
     * 1. QuickSort
     * 2. MergeSort
     * 3. NewSort
     */
    public static void testSorts()
    {
        // Variables for the test sorting algorithms
        int NUM_ARRAYS = 100;
        int SMALL = 100;
        int MEDIUM = 1000;
        int LARGE = 10000;
        int SORT_NUM = 3;

        // Test for 100 arrays of size 100
        Random ran = new Random();
        // Create 2D array of random integers size 100.
        Integer[][] randomInts2D;
        Integer[][] ints2D;

        long[] mergeResults = new long[SORT_NUM];
        long[] quickResults = new long[SORT_NUM];
        long[] newResults = new long[SORT_NUM];

        long startTime;
        long endTime;

        randomInts2D = new Integer[NUM_ARRAYS][SMALL];
        ints2D = new Integer[NUM_ARRAYS][SMALL];
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < SMALL; j++)
            {
                randomInts2D[i][j] = (int) ran.nextInt(SMALL);
            }
        }

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            MergeSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        mergeResults[0] = endTime - startTime;
        

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            QuickSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        quickResults[0] = endTime - startTime;

        resetInts2d(ints2D, randomInts2D);
        
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            NewSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        newResults[0] = endTime - startTime;

        // Test for 100 arrays of size 1000
        randomInts2D = new Integer[NUM_ARRAYS][MEDIUM];
        ints2D = new Integer[NUM_ARRAYS][SMALL];
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < MEDIUM; j++)
            {
                randomInts2D[i][j] = (int) ran.nextInt(MEDIUM);
            }
        }

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            MergeSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        mergeResults[1] = endTime - startTime;

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            QuickSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        quickResults[1] = endTime - startTime;
        
        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            NewSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        newResults[1] = endTime - startTime;

        // Test for 100 arrays of size 10000
        randomInts2D = new Integer[NUM_ARRAYS][LARGE];
        ints2D = new Integer[NUM_ARRAYS][SMALL];
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < LARGE; j++)
            {
                randomInts2D[i][j] = (int) ran.nextInt(LARGE);
            }
        }

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            MergeSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        mergeResults[2] = endTime - startTime;

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            QuickSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        quickResults[2] = endTime - startTime;

        resetInts2d(ints2D, randomInts2D);
        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            NewSort.sort(ints2D[i]);
        }
        endTime = System.currentTimeMillis();
        newResults[2] = endTime - startTime;

        for (int i = 0; i < SORT_NUM; i++)
        {
            System.out.print("\n\nArray size: \t" + NUM_ARRAYS + "x");
            if (i == 0)
                System.out.println(SMALL);
            else if (i == 1)
                System.out.println(MEDIUM);
            else
                System.out.println(LARGE);
            
            System.out.println("-------------------------");
            System.out.println("Merge Sort: \t" + mergeResults[i] / (double) NUM_ARRAYS + "ms");
            System.out.println("Quick Sort: \t" + quickResults[i] / (double) NUM_ARRAYS + "ms");
            System.out.println("New Sort: \t" + newResults[i] / (double) NUM_ARRAYS + "ms");
        }
        System.out.println("\n");

        System.out.println("Merge Sort\t" + "Quick Sort\t" + "New Sort");
        System.out.println("----------\t" + "----------\t" + "--------");
        for (int i = 0; i < SORT_NUM; i++)
        {
            System.out.print(mergeResults[i] / (double) NUM_ARRAYS + "ms" + "\t\t");
            System.out.print(quickResults[i] / (double) NUM_ARRAYS + "ms" + "\t\t");
            System.out.println(newResults[i] / (double) NUM_ARRAYS + "ms");
        }
        System.out.println("\n");
    }

    /**
     * Resets the 2D array to the original values
     */
    private static void resetInts2d(Integer[][] ints2d, Integer[][] randomInts2D) 
    {
        for (int i = 0; i < 100; i++)
        {
            ints2d[i] = Arrays.copyOf(randomInts2D[i], randomInts2D[i].length);
        }
    }

    /**
     * It creates a new hash table, adds some key-value pairs to it, and then prints the result of tests
     */
    public static void testHybrid()
    {
        System.out.println("\n ===================== Test HashTableHybrid ===================== \n");
        System.out.println("--Echo[1] Put element to the empty place and colliding place.\n");
        HashTableHybrid<String> hashTable = new HashTableHybrid<>();
        hashTable.put(3, "three");
        hashTable.put(12, "twelve");
        hashTable.put(13, "thirteen");
        hashTable.put(25, "twenty-five");
        hashTable.put(23, "twenty-three");
        hashTable.put(51, "fifty-one");
        System.out.println(hashTable);

        System.out.println("--Echo[2] Remove existent element and try to remove non-existent element.\n");
        System.out.println("Remove element with key 25 (Head of a link)): " + hashTable.remove(25));
        System.out.println("Remove element with key 12 (Middle of a link): " + hashTable.remove(13));
        System.out.println("Remove element with key 100 (Non-existent): " + hashTable.remove(100) + "\n");
        System.out.println(hashTable);

        System.out.println("--Echo[3] Get an existent element and try to get a non-existent element.\n");
        System.out.println("Get element with key 23 (existent - after break a link): " + hashTable.get(23));
        System.out.println("Get element with key 100 (Non-existent): " + hashTable.get(13) + "\n");
    }

    /**
     * It creates a new hash table, adds some key-value pairs to it, and then prints the result of tests
     */
    public static void testChain()
    {
        System.out.println("\n ===================== Test HashTableChainBST ===================== \n");
        HashTableChainBST<Integer, String> ht = new HashTableChainBST<Integer, String>();
        System.out.println("--Echo[1] Put element to the empty place and colliding place.\n");
        ht.put(2, "banana");
        ht.put(3, "orange");  
        ht.put(6, "peach");
        ht.put(7, "plum");
        ht.put(17, "apple");
        ht.put(28, "kiwi");
        ht.put(39, "pear");
        ht.put(14, "peach");
        System.out.println(ht);

        System.out.println("--Echo[2] Remove existent element and try to remove non-existent element.\n");
        System.out.println("Remove element: " + ht.remove(2));
        System.out.println("Try to remove non-existent element: " + ht.remove(2) + "\n");
        System.out.println(ht);

        System.out.println("--Echo[3] Get existent element and try to get non-existent element.\n");
        System.out.println("Get element: " + ht.get(17));
        System.out.println("Try to get non-existent element: " + ht.get(32) + "\n");
    }

    public static void testChainTime()
    {
        System.out.println("\n ===================== Test HashTableChainBST ===================== \n");
        
        int NUM_ARRAYS = 100;
        int SMALL = 100;
        int MEDIUM = 1000;
        int LARGE = 10000;
        long[] results = new long[3];
        long startTime;
        long endTime;
        Integer[] randomInts;
        ArrayList<HashTableChainBST<Integer, Integer>> ints;
        Random ran = new Random();

        
        ints = new ArrayList(NUM_ARRAYS);
        // Push 100 random item to every HashTableChainBST
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            ints.add(new HashTableChainBST<>());
            for (int j = 0; j < SMALL; j++)
            {
                ints.get(i).put(ran.nextInt(SMALL), ran.nextInt(SMALL));
            }
        }
        // Generate 1 dimension 100 size random arrays

        randomInts = new Integer[SMALL];
        for (int i = 0; i < SMALL; i++)
        {
            randomInts[i] = ran.nextInt(SMALL);
        }
        
        // Try to remove 100 element in each HashTableChainBST

        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < SMALL; j++)
            {
                ints.get(i).remove(randomInts[i]);
            }
        }
        endTime = System.currentTimeMillis();
        results[0] = endTime - startTime;

        // 1000 element

        ints = new ArrayList(NUM_ARRAYS);
        // Push 100 random item to every HashTableChainBST
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            ints.add(new HashTableChainBST<>());
            for (int j = 0; j < MEDIUM; j++)
            {
                ints.get(i).put(ran.nextInt(MEDIUM), ran.nextInt(MEDIUM));
            }
        }
        // Generate 1 dimension 100 size random arrays

        randomInts = new Integer[MEDIUM];
        for (int i = 0; i < MEDIUM; i++)
        {
            randomInts[i] = ran.nextInt(MEDIUM);
        }
        
        // Try to remove 100 element in each HashTableChainBST

        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < MEDIUM; j++)
            {
                ints.get(i).remove(randomInts[i]);
            }
        }
        endTime = System.currentTimeMillis();
        results[1] = endTime - startTime;

        // 10000 element

        ints = new ArrayList(NUM_ARRAYS);
        // Push 100 random item to every HashTableChainBST
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            ints.add(new HashTableChainBST<>());
            for (int j = 0; j < LARGE; j++)
            {
                ints.get(i).put(ran.nextInt(LARGE), ran.nextInt(LARGE));
            }
        }
        // Generate 1 dimension 100 size random arrays

        randomInts = new Integer[LARGE];
        for (int i = 0; i < LARGE; i++)
        {
            randomInts[i] = ran.nextInt(LARGE);
        }
        
        // Try to remove 100 element in each HashTableChainBST

        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < LARGE; j++)
            {
                ints.get(i).remove(randomInts[i]);
            }
        }
        endTime = System.currentTimeMillis();
        results[2] = endTime - startTime;

        System.out.println("\nRemove for 100, 1000, 10000 elements (Average)");
        System.out.println("----------------------------------------------\n");
        for (int i = 0; i < results.length; i++)
        {
            System.out.print("100x");
            if (i == 0)
                System.out.print(SMALL);
            else if (i == 1)
                System.out.print(MEDIUM);
            else
                System.out.print(LARGE);
            
            System.out.println(" Elements: \t" + results[i] / (double) NUM_ARRAYS + " ms\n");
        }

        ints = new ArrayList(NUM_ARRAYS);
        // Push 100 random item to every HashTableChainBST
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            ints.add(new HashTableChainBST<>());
            for (int j = 0; j < SMALL; j++)
            {
                ints.get(i).put(ran.nextInt(SMALL), ran.nextInt(SMALL));
            }
        }
        // Generate 1 dimension 100 size random arrays

        randomInts = new Integer[SMALL];
        for (int i = 0; i < SMALL; i++)
        {
            randomInts[i] = ran.nextInt(SMALL);
        }

        // Try to get 100 element in each HashTableChainBST

        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < SMALL; j++)
            {
                ints.get(i).get(randomInts[i]);
            }
        }
        endTime = System.currentTimeMillis();
        results[0] = endTime - startTime;

        // 1000 element

        ints = new ArrayList(NUM_ARRAYS);
        // Push 100 random item to every HashTableChainBST
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            ints.add(new HashTableChainBST<>());
            for (int j = 0; j < MEDIUM; j++)
            {
                ints.get(i).put(ran.nextInt(MEDIUM), ran.nextInt(MEDIUM));
            }
        }
        // Generate 1 dimension 100 size random arrays

        randomInts = new Integer[MEDIUM];
        for (int i = 0; i < MEDIUM; i++)
        {
            randomInts[i] = ran.nextInt(MEDIUM);
        }

        // Try to get 100 element in each HashTableChainBST

        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < MEDIUM; j++)
            {
                ints.get(i).get(randomInts[i]);
            }
        }
        endTime = System.currentTimeMillis();
        results[1] = endTime - startTime;

        // 10000 element

        ints = new ArrayList(NUM_ARRAYS);
        // Push 100 random item to every HashTableChainBST
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            ints.add(new HashTableChainBST<>());
            for (int j = 0; j < LARGE; j++)
            {
                ints.get(i).put(ran.nextInt(LARGE), ran.nextInt(LARGE));
            }
        }
        // Generate 1 dimension 100 size random arrays

        randomInts = new Integer[LARGE];
        for (int i = 0; i < LARGE; i++)
        {
            randomInts[i] = ran.nextInt(LARGE);
        }

        // Try to get 100 element in each HashTableChainBST

        startTime = System.currentTimeMillis();
        for (int i = 0; i < NUM_ARRAYS; i++)
        {
            for (int j = 0; j < LARGE; j++)
            {
                ints.get(i).get(randomInts[i]);
            }
        }
        endTime = System.currentTimeMillis();
        results[2] = endTime - startTime;

        System.out.println("\nget for 100, 1000, 10000 elements (Average)");
        System.out.println("----------------------------------------------\n");
        for (int i = 0; i < results.length; i++)
        {
            System.out.print("100x");
            if (i == 0)
                System.out.print(SMALL);
            else if (i == 1)
                System.out.print(MEDIUM);
            else
                System.out.print(LARGE);
            
            System.out.println(" Elements: \t" + results[i] / (double) NUM_ARRAYS + " ms\n");
        }

    }
    
    public static void testHybridTime()
    {
        // Yetismedi...
    }
}
