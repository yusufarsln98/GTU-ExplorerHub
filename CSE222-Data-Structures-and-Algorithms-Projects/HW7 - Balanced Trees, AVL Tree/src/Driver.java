import java.util.Arrays;

import lib.binarytreetobinarysearchtree.BinaryTree;
import lib.binarysearchtreetoavltree.TreePrinter;
import lib.binarysearchtreetoavltree.BinarySearchTreeWithRotate;

public final class Driver {
    
    private Driver() {}

    public static void main(String[] args) {
        
        toBinarySearchTreeWithArrayElementsDriver();
        toAVLTreeDriver();
    }

    /**
     * The function takes an array of integers and converts binary tree to binary search tree with the 
     * same elements as the array.
     */
    private static void toBinarySearchTreeWithArrayElementsDriver() 
    {
        // You can increase or decrease the size of the array/tree to test this code.
        int TREE_SIZE = 10;

        System.out.println("\n\n ---------------------- To Binary Search Tree With Array Elements Driver ----------------------" + "\n");
        BinaryTree<Integer> tree = new BinaryTree<>();
        // Add tree random numbers between 1 and 100
        for (int i = 0; i < TREE_SIZE; i++) {
            tree.add((int) (Math.random() * 100) + 1);
        }

        System.out.println();
        System.out.println("----- Binary Tree -----");
        System.out.println(tree.toString());
        System.out.println("Binary Tree (one-line inorder): " + "\n" + tree.oneLineInorder() + "\n");
        Integer[] array = new Integer[TREE_SIZE];
        
        // Add array 7 unique random numbers between 1 and 100
        for (int i = 0; i < TREE_SIZE; i++) {
            int num = (int) (Math.random() * 50) + 1;
            if (Arrays.asList(array).contains(num)) {
                i--;
            } else {
                array[i] = num;
            }
        }
        // print the array
        System.out.println();
        System.out.print("-- The array: ");
        System.out.println(Arrays.toString(array) + " --" + "\n");

        BinaryTree<Integer> bst = tree.toBinarySearchTreeWithArrayElements(array);
        System.out.println("----- Binary Search Tree -----");            
        System.out.println(bst.toString());
        System.out.println("Binary Search Tree (one-line inorder): " + "\n" + bst.oneLineInorder() + "\n");
    }

    
    /**
     * This function creates a binary search tree with some random numbers between 1 and 100, prints the
     * tree, converts the tree to an AVL tree, and prints the AVL tree.
     */
    private static void toAVLTreeDriver() 
    {
        // You can increase or decrease the size of the array/tree to test this code.
        // But, TreePrinter.print method will not work if the tree is too big.
        int TREE_SIZE = 15;
        System.out.println("\n\n ---------------------- To AVL Tree Driver ----------------------" + "\n");

        BinarySearchTreeWithRotate<Integer> bst = new BinarySearchTreeWithRotate<>();

        // Add TREE_SIZE random unique numbers between 1 and 100 to the tree
        for (int i = 0; i < TREE_SIZE; i++) {
            int random = (int) (Math.random() * 100) + 1; 
            if (bst.contains(random)) {
                i--;
            } 
            else {
                bst.add(random);
            }
        }
  
        // Print the tree
        System.out.println("------ Binary Search Tree ------" + "\n");
        System.out.println("one-line in order: " + bst.oneLineInorder() + "\n");
        System.out.println("pre order:" + "\n" + bst.toString());
        
        // Convert to AVL tree
        System.out.println("\n------ AVL Tree ------" + "\n");
        BinarySearchTreeWithRotate<Integer> avlTree = bst.toAVLTree();
        TreePrinter.print(avlTree.getRoot());
        System.out.println();        
        System.out.println("one-line in order: " + avlTree.oneLineInorder() + "\n");
        System.out.println("pre order:" + '\n' + avlTree.toString());
    }
}
