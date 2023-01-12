import lib.*;

/**
 * Main class.
 */
public class Main 
{
    /**
     * The main function that runs the program.
     */
    public static void main(String[] args) 
    {
        binaryHeapDriver();
        binarySearchTreeDriver();
    }

    /**
     * The above function is a driver function for the BinaryHeap class. It creates two BinaryHeap objects
     * and insert some elements to them. Then it merges the two heaps and poll elements from the merged
     * heap.
     */
    private static void binaryHeapDriver() 
    {
        // ------------------ Test the BinaryHeap class ------------------
        System.out.println("\n========= BinaryHeap class driver (No user interaction) =========\n");

        // Add some elements to the heap
        /* Echo */ System.out.println("1[ECHO]--- Create a empty heap -heap1- and insert 3 random element to this heap.\n");
        BinaryHeap<Integer> heap1 = new BinaryHeap<>();
        heap1.offer(8);
        heap1.offer(12);
        heap1.offer(3);
        System.out.println(heap1);

        // Add a smaller element to the heap and see how to handle heap order and heap structure
        /* Echo */ System.out.println("2[ECHO]--- Offer a small element to the heap and see how to cover heap order and structure.\n");
        heap1.offer(1);
        System.out.println(heap1);

        // Add more element to the heap
        /* Echo */ System.out.println("3[ECHO]--- Add more element to the heap and see every sub-tree is also a heap.\n");
        heap1.offer(5);
        heap1.offer(0);
        heap1.offer(4);
        heap1.offer(19);
        System.out.println(heap1);

        /* Echo */ System.out.println("4[ECHO]--- Poll the root element and see how to cover heap order and structure.\n");
        System.out.println("Polled Element: " + heap1.poll() + "\n");
        System.out.println(heap1);

        // Create another heap object
        /* Echo */ System.out.println("5[ECHO]--- Create another heap -heap2- and offer some random element to this heap.\n");
        BinaryHeap<Integer> heap2 = new BinaryHeap<>();
        heap2.offer(23);
        heap2.offer(12);
        heap2.offer(31);
        heap2.offer(1);
        heap2.offer(7);
        heap2.offer(8);
        heap2.offer(13);
        System.out.println(heap2);

        // Increase key of 8 to the 32
        /* Echo */ System.out.println("6[ECHO]--- Increase the key of 8 to 32 and see how to cover heap order and structure.\n");
        heap2.increaseKey(8, 32);
        System.out.println(heap2);

        // Merge heap1 and heap2
        BinaryHeap<Integer> merged = heap1.merge(heap2);
        /* Echo */ System.out.println("7[ECHO]--- Merge heap1 and heap2 and assign result to the 'merged'.\n");
        System.out.println(merged);

        // Poll elements from the merged heap.
        /* Echo */ System.out.println("8[ECHO]--- Poll elements from the merged heap and see how to cover heap order and structure.\n");
        System.out.println("Polled Element: " + merged.poll() + "\n");
        System.out.println(merged);

        /* Echo */ System.out.println("9[ECHO]--- Keep polling.\n");
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll() + "\n");
        System.out.println(merged);

        /* Echo */ System.out.println("10[ECHO]--- Keep polling.\n");
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll() + "\n");
        System.out.println(merged);
        
        /* Echo */ System.out.println("11[ECHO]--- Keep polling.\n");
        System.out.println("Polled Element: " + merged.poll());
        System.out.println("Polled Element: " + merged.poll() + "\n");

        System.out.println("There is no enough element to poll in the 'merged' heap.\n");

        
        System.out.println("\n==========================End Of The Test========================\n");

    }

    /**
     * The above function is a driver function for the BinarySearchTree class. It creates a tree and
     * adds some elements to the tree. Then it tests contains method. After that it finds a target.
     * Then it tests remove method. After that it removes the root until no element left in the tree.
     */
    private static void binarySearchTreeDriver() 
    {
        // ------------------ Test the BinarySearchTree class ------------------
        System.out.println("\n====== BinarySearchTree class driver (No user interaction) ======\n");

        // Create a tree and add some elements to the tree.
        /* Echo */ System.out.println("1[ECHO]--- Create a empty tree -tree1- and insert 3 random element to this tree.\n");
        BinarySearchTree<Integer> tree1 = new BinarySearchTree<>();
        System.out.println("Is addition performed: " + tree1.add(100));
        System.out.println("Is addition performed: " + tree1.add(50));
        System.out.println("Is addition performed: " + tree1.add(150) + "\n");
        System.out.println(tree1);

        // Try to add same element to the tree
        /* Echo */ System.out.println("2[ECHO]--- Try to add same element to the tree.\n");
        System.out.println("Is addition performed: " + tree1.add(150) + "\n");

        // Add more elements to the tree
        /* Echo */ System.out.println("3[ECHO]--- Add more element to the tree.\n");
        tree1.add(0);
        tree1.add(90);
        tree1.add(80);
        tree1.add(70);
        tree1.add(85);
        tree1.add(95);
        tree1.add(92);
        tree1.add(97);
        System.out.println(tree1);

        // Test contains method
        /* Echo */ System.out.println("4[ECHO]--- Test contains method.\n");
        System.out.println("Is 100 in the tree: " + tree1.contains(100));
        System.out.println("Is 333 in the tree: " + tree1.contains(333) + "\n");

        // Find a target
        /* Echo */ System.out.println("5[ECHO]--- Test find method.\n");
        System.out.println("Find 100: " + tree1.find(100));
        System.out.println("Find 333: " + tree1.find(333) + "\n");

        // Test remove method
        /* Echo */ System.out.println("6[ECHO]--- Remove an element with no child.\n");
        System.out.println("Deleted Number: " + tree1.delete(150) + "\n");
        System.out.println(tree1);

        /* Echo */ System.out.println("7[ECHO]--- Remove an element with two child.\n");
        System.out.println("Deleted Number: " + tree1.delete(90) + "\n");
        System.out.println(tree1);

        /* Echo */ System.out.println("8[ECHO]--- Delete an element with one child.\n");
        System.out.println("Deleted Number: " + tree1.delete(50) + "\n");
        System.out.println(tree1);

        /* Echo */ System.out.println("9[ECHO]--- Remove the root.\n");
        System.out.println("Deleted Number: " + tree1.delete(100) + "\n");
        System.out.println(tree1);

        //Remove the root until no element left in the tree.
        /* Echo */ System.out.println("10[ECHO]--- Remove the root until no element left in the tree.\n");
        while (tree1.getRoot() != null)
        {
            System.out.println("Is removal performed for " + tree1.getRoot() + " " + tree1.remove(tree1.getRoot()) + "\n");
            System.out.println(tree1);
        }
        

        System.out.println("\n==========================End Of The Test========================\n");
    }
}
