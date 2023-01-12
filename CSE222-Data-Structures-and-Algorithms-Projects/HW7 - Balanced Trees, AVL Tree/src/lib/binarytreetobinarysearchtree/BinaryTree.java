package lib.binarytreetobinarysearchtree;

import java.io.*;
import java.util.Scanner;

/**
 * Class for a binary tree that stores type E objects
 * @author Jacob / Koffman & Wolfgang
 *
 * @param <E> The type of data to be stored
 */
@SuppressWarnings("serial")
public class BinaryTree<E extends Comparable<E>> implements Serializable {
	
	//Data Fields
	/**
	 * Class for a binary tree that stores type E objects
	 */
	protected Node<E> root;

	private static int INDEX;
	
	//Constructors
	public BinaryTree(){
		root = null;
	}
	
	// A constructor that takes a node as a parameter and sets the root of the tree to that node.
	protected BinaryTree(Node<E> root){
		this.root = root;
	}

	/**
	 * The function sorts the array, initializes the static INDEX variable to 0, 
	 * and traverses tree in order, and then, sets the element in the array to this tree.
	 * 
	 * @param array The array of elements to be added to the tree.
	 * @return The converted tree as itself.
	 */
	public BinaryTree<E> toBinarySearchTreeWithArrayElements(E[] array)
	{
		// Sort the array first.
		sort(array);

		// Initialize static INDEX variable to 0.
		INDEX = 0;
		// Travers in order and set the element in the array to the tree.
		toBinarySearchTreeWithArrayElements(root, array);
		return this;
	}

	/**
	 * The function takes a binary tree and an array of elements, and sets the elements of the array to
	 * the tree in in-order traversal.
	 * 
	 * @param localNode The node that keeps the reference of root.
	 * @param array The array that contains the elements of the binary search tree.
	 */
	private void toBinarySearchTreeWithArrayElements(Node<E> localNode, E[] array) {
		// A Binary search tree suppose to be sorted in in-order travarsal.
		// Therefor if we in order traverse the tree and set the elements of sorted array to the tree,
		// the tree will be a binary search tree with same structure that invoked by this method.
		if (localNode != null) 
		{
			toBinarySearchTreeWithArrayElements(localNode.left, array);
			// Set the element in the array to the tree and increase INDEX by one.
			localNode.data = array[INDEX++];
			toBinarySearchTreeWithArrayElements(localNode.right, array);
		}
	}
   
	/**
	 * Selection Sort:
	 * Sort the array by comparing each element to the next element and swapping them if the first
	 * element is greater than the second element.
	 * 
	 * @param array The array to be sorted.
	 */
	private static <E extends Comparable<E>> void sort(E[] array)
    {
        for (int i = 0; i < array.length; i++) {
            for (int j = i + 1; j < array.length; j++) {
                if (array[i].compareTo(array[j]) > 0) {
                    E temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }


	/**
	 * Constructs a new binary tree with data in its root, leftTree as its left subtree, 
	 * and rightTree as its right subtree.
	 * 
	 * @param data The data of the root node
	 * @param leftTree The left subtree
	 * @param rightTree The right subtree
	 */
	public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree){
		root = new Node<E>(data);
		if(leftTree != null){
			root.left = leftTree.root;
		} else {
			root.left = null;
		}
		if(rightTree != null){
			root.right = rightTree.root;
		} else {
			root.right = null;
		}
	}
	
	//Methods

	// Add a new data with the left tree weigth
	public boolean add(E item){
		root = add(root, item);
		return true;
	}

	/**
	 * Recursive add method
	 * post: The data field addReturn is set to true if the item is added to the tree, 
	 * false if the item is already in the tree
	 * @param localRoot The local root of the subtree
	 * @param item The object to be inserted
	 * @return The new local root that now contains the inserted item
	 */
	private Node<E> add(Node<E> localRoot, E item){
		if(localRoot == null){
			//item is not in the tree - insert it
			return new Node<>(item);
		} 
		else 
		{
			int random = (int) (Math.random() * 2) + 1;

			if (random % 2 == 0)
			{
				//item is less than localRoot.data
				localRoot.left = add(localRoot.left, item);
				return localRoot;
			} 
			else 
			{
				//item is greater than localRoot.data
				localRoot.right = add(localRoot.right, item);
				return localRoot;
			}
		}
	}

	/**
	 * Return the left subtree
	 * @return The left subtree or null if either the root or the left subtree is null
	 */
	public BinaryTree<E> getLeftSubtree(){
		if(root != null && root.left != null){
			return new BinaryTree<E>(root.left);
		} else {
			return new BinaryTree<E> (null);
		}
	}
	
	/**
	 * Return the right subtree
	 * @return The right subtree or null if either the root or the right subtree is null
	 */
	public BinaryTree<E> getRightSubtree(){
		if(root != null && root.right != null){
			return new BinaryTree<E>(root.right);
		} else {
			return new BinaryTree<E> (null);
		}
	}

	/**
	 * Determine whether this tree is a leaf
	 * @return true if the root has no children
	 */
	public boolean isLeaf(){
		return root == null || (root.left == null && root.right == null);
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		preOrderTraverse(root, 1, sb);
		return sb.toString();
	}
	
	/**
	 * Perform a preorder traversal
	 * @param node The local root
	 * @param depth The depth
	 * @param sb The string buffer to save the output
	 */
	private void preOrderTraverse(Node<E> node, int depth, StringBuilder sb){
		for(int i = 1; i < depth; i++){
			sb.append("  ");
		}
		if(node == null){
			sb.append("null\n");
		} else {
			sb.append(node.toString());
			sb.append("\n");
			preOrderTraverse(node.left, depth + 1, sb);
			preOrderTraverse(node.right, depth + 1, sb);
		}
	}
	
	public String oneLinePreorder(){
		StringBuilder sb = new StringBuilder();
		preOrderTraverseOneLine(root, sb);
		return sb.toString();
	}
	
	/**
	 * Perform a preorder traversal, returning the tree as one line
	 * @param node The local root
	 * @param sb The string bufer to save the output
	 */
	private void preOrderTraverseOneLine(Node<E> node, StringBuilder sb){
		if(node == null){
			//do nothing
		} else {
			sb.append(node.toString());
			sb.append(" ");
			preOrderTraverseOneLine(node.left, sb);
			preOrderTraverseOneLine(node.right, sb);
		}
	}
	
	public String oneLinePostorder(){
		StringBuilder sb = new StringBuilder();
		postOrderTraverse(root, sb);
		return sb.toString();
	}
	
	/**
	 * Perform a postorder traversal, returning the tree as one line
	 * @param node The local root
	 * @param sb The string bufer to save the output
	 */
	private void postOrderTraverse(Node<E> node, StringBuilder sb){
		if(node == null){
			//do nothing
		} else {
			preOrderTraverseOneLine(node.left, sb);
			preOrderTraverseOneLine(node.right, sb);
			sb.append(node.toString());
			sb.append(" ");
		}
	}
	
	public String oneLineInorder(){
		StringBuilder sb = new StringBuilder();
		inOrderTraverse(root, sb);
		return sb.toString();
	}
	
	/**
	 * Perform an inorder traversal, returning the tree as one line (with parentheses)
	 * @param node The local root
	 * @param sb The string bufer to save the output
	 */
	private void inOrderTraverse(Node<E> node, StringBuilder sb){
		if(node == null){
			//do nothing
		} else {
			sb.append("(");
			inOrderTraverse(node.left, sb);
			sb.append(" ");
			sb.append(node.toString());
			sb.append(" ");
			inOrderTraverse(node.right, sb);
			sb.append(")");
		}
	}
	
	/**
	 * Method to read a binary treee
	 *   pre: The input consists of a preorder traversal of the binary tree.
	 *        The line "null" indicates a null tree.
	 * @param scan the Scanner attached to the input file
	 * @return The binary tree
	 */
	public static BinaryTree<String> readBinaryTree(Scanner scan){
		//Read a line and trim leading and trailing spaces
		String data = scan.next();
		if(data.equals("null")){
			return null;
		} else {
			BinaryTree<String> leftTree = readBinaryTree(scan);
			BinaryTree<String> rightTree = readBinaryTree(scan);
			return new BinaryTree<String>(data, leftTree, rightTree);
		}
	}

	protected Node<E> getRoot() {
		return root;
	}
	
	/**
	 * Class to encapsulate a tree node
	 * @author Jacob / Koffman & Wolfgang
	 *
	 * @param <E> The type of data stored
	 */
	protected static class Node<E> implements Serializable {
		
		//Data Fields
		/**
		 * The information stored in this node
		 */
		protected E data;
		/**
		 * Reference to the left child
		 */
		protected Node<E> left;
		/**
		 * Reference to the right child
		 */
		protected Node<E> right;
		
		//Constructors
		/**
		 * Construct a node with given data and no children
		 * @param data The data to store in this node
		 */
		public Node(E data){
			this.data = data;
			left = null;
			right = null;
		}
		
		public Node()
		{
			this.data = null;
			left = null;
			right = null;
		}

		public void setData(E data) {
			this.data = data;
		}

		public E getData() {
			return data;
		}

		public Node<E> getLeft() {
			return left;
		}

		public Node<E> getRight() {
			return right;
		}
		
		//Methods
		/**
		 * Return a string representation of the node
		 * @return A string representation of the data fields
		 */
		public String toString(){
			return data.toString();
		}
	}
}

