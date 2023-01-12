package lib;
import java.util.Arrays;

// -------------------------- !!!!! Not totally completed !!!!! --------------------------

public class DisplayBlocks 
{
    /**
     * Private constructor. It is used to prevent the class from being instantiated.
     */
    private DisplayBlocks() {}
    
    // Array of blocks
    private static char[] blocks;
    
    /**
     * Display the blocks in the array.
     * 
     * @param size The size of the blocks array.
     */
    public static void displayBlocks(int size) 
    {
        // This is the wrapper method of the recursive displayBlocks method.
        blocks = new char[size];
        clearBlocks(0, size);
        printBlocks();
        displayBlocks(size, 0, 3);
        System.out.println();
    }
    
    /**
     * Display the set of blocks which are shifting and increasing.
     * 
     * @param size The size of the array.
     * @param start The starting index of the block.
     * @param blockSize The size of the block to be filled.
     */
    private static void displayBlocks(int size, int start, int blockSize) 
    {
        // This is the recursive method of the displayBlocks method.

        // Base case of the recursive method. If the block size is less than the size of
        // the array, then the block size is increased by 1 and the method is called again.
        if (start + blockSize > size)
        {
            if (blockSize <= size)
            {
                displayBlocks(size, 0, blockSize + 1);
            }
        }
        // Recursive case of the displayBlocks method. If the block size is less than the
        // size of the array, then the block size is increased by 1 and the method is called again.
        else
        {
            fillBlocks(start, blockSize);
            printBlocks();
            clearBlocks(0, size);
            displayBlocks(size, start + 1, blockSize);
        }
    }
    
    /**
     * Prints the blocks array
     */
    private static void printBlocks() 
    {
        System.out.println(blocks);
    }
    
    /**
     * Fill the array with the '#'
     * 
     * @param start The starting index of the block.
     * @param blockSize The number of bytes to copy at a time.
     */
    private static void fillBlocks(int start, int blockSize)
    {
        Arrays.fill(blocks, start, start + blockSize, '#');
    }
    
    /**
     * Clear the blocks between start and end
     * 
     * @param start The index of the first block to be cleared.
     * @param end The index of the last block to be cleared.
     */
    private static void clearBlocks(int start, int end)
    {
        Arrays.fill(blocks, start, end, '-');
    }

}