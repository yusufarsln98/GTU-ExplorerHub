package lib.hashbst.bst;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.Stack;

/**
 * Implementation of a Binary Search Tree
 * @author Jacob / Koffman & Wolfgang
 *
 * @param <E> The type of data in the tree. Must be a Comparable object.
 */
public class BinarySearchTree<E extends Comparable<E>> extends BinaryTree<E> implements SearchTree<E>, Iterable<E> {
	//Data Fields
	/**
	 * Return value from the public add method
	 */
	protected boolean addReturn;
	/** 
	 * Return value from the public delete method 
	 */
	protected E deleteReturn;

	private int size;

	//Constructors
	/**
	 * Constructs an empty binary search tree.
	 */
	public BinarySearchTree() {
		super();
		size = 0;
	}
	
	//Methods
	/**
	 * The toString() function returns the preOrder() function
	 * 
	 * @return The preOrder() method is being returned.
	 */
	@Override
	public String toString(){
		
		return preOrder();
	}
	
	/**
	 * It returns a string representation of the tree in preorder traversal.
	 * 
	 * @return A string representation of the tree.
	 */
	public String preOrder(){
		StringBuilder sb = new StringBuilder();
		preOrderTraverse(root, sb);
		return sb.toString();
	}
	
	/**
	 * Perform an inorder traversal, returning the tree in ascending order (new lines separate characters)
	 * @param node The local root
	 * @param sb The string bufer to save the output
	 */
	private void preOrderTraverse(Node<E> node, StringBuilder sb){
		if(node == null){
			//do nothing
		} else {
			sb.append(node.toString() + "\n");
			preOrderTraverse(node.left, sb);
			preOrderTraverse(node.right, sb);
		}
	}
	
	/**
	 * Starter method add
	 * pre: The object to be inserted must implement the Comparable interface
	 * @param item The item being inserted
	 * @return true if the object is inserted, false if the object already exists in the tree
	 */
	public boolean add(E item) {
		root = add(root, item);
		return addReturn;
	}

	/**
	 * Recursive add method
	 * post: The data field addReturn is set to true if the item is added to the tree, false if the item is already in the tree
	 * @param localRoot The local root of the subtree
	 * @param item The object to be inserted
	 * @return The new local root that now contains the inserted item
	 */
	private Node<E> add(Node<E> localRoot, E item){
		if(localRoot == null){
			//item is not in the tree - insert it
			addReturn = true;
			return new Node<E>(item);
		} else {
			int compare = item.compareTo(localRoot.data);
			if (compare == 0){
				//item is equal to localRoot.data
				addReturn = false;
				return localRoot;
			} else if (compare < 0){
				//item is less than localRoot.data
				localRoot.left = add(localRoot.left, item);
				return localRoot;
			} else {
				//item is greater than localRoot.data
				localRoot.right = add(localRoot.right, item);
				return localRoot;
			}
		}
	}
	
	public boolean contains(E target) {
		E result = find(target);
		return result == target;
	}

	/**
	 * Starter method find.
	 * pre: The target object must implement the Comparable interface.
	 * @param target The Comparable object being sought
	 * @return The object if found, otherwise null
	 */
	public E find(E target) {
		return find(root, target);
	}
	
	/**
	 * Recursive find method
	 * @param localRoot The local subtree's root
	 * @param target The object being sought
	 * @return The object, if found, otherwise null
	 */
	private E find(Node<E> localRoot, E target){
		if(localRoot == null)
			return null;
		//Compare target with the data field at the root
		int compResult = target.compareTo(localRoot.data);
		if(compResult == 0)
			return localRoot.data;
		else if (compResult < 0)
			return find(localRoot.left, target);
		else
			return find(localRoot.right, target);
	}

	/**
	 * Starter method delete
	 * post: The object is not in the tree
	 * @param target The object to be deleted
	 * @return The object deleted from the tree or null if the object was not in the tree
	 * @throws ClassCast Exception if target does not implement Comparable
	 */
	public E delete(E target){
		root = delete(root, target);
		return deleteReturn;
	}
	
	/**
	 * Recursive delete method
	 * post: The item is not in the tree;
	 * 		 deleteReturn is equal to the deleted item
	 * 		 as it was stored in the tree or null
	 *		 if the item was not found
	 * @param localRoot The root of the current subtree
	 * @param item The item to be deleted
	 * @return The modified local root that does not contain the item
	 */
	private Node<E> delete(Node<E> localRoot, E item){
		if(localRoot == null){
			//item is not in the tree
			deleteReturn = null;
			return localRoot;
		}
		//search for the item to delete
		int compResult = item.compareTo(localRoot.data);
		if(compResult < 0){
			//item is smaller than localRoot.data
			localRoot.left = delete(localRoot.left, item);
			return localRoot;
		} else if (compResult > 0){
			//item is larger than localRoot.data
			localRoot.right = delete(localRoot.right, item);
			return localRoot;
		} else {
			
			//item is at local root
			deleteReturn = localRoot.data;
			if(localRoot.left == null){
				//if there is no left child, return right child which can also be null
				return localRoot.right;
			} else if (localRoot.right == null){
				//if there is no right child, return left child
				return localRoot.left;
			} else {
				//Node being deleted has 2 children, replace the data with inorder predecessor
				if(localRoot.left.right == null){
					//the left child has no right child. Replace the data with the data in the left child
					localRoot.data = localRoot.left.data;
					localRoot.left = localRoot.left.left; // replace the left child with its left child
					return localRoot;	
				} else {
					//Search for the inorder predecessor and replace deleted node's data with it
					localRoot.data = findLargestChild(localRoot.left);
					return localRoot;
				}
			}
		}
	}
	
	/**
	 * Find the node that is the inorder predecessor and replace it with its left child (if any)
	 * post: the inorder predecessor is removed from the tree
	 * warning: only call on nodes with known right children
	 * @param parent The parent of possible inorder predecessor
	 * @return The data in the inorder predecessor
	 */
	private E findLargestChild(Node<E> parent){
		//if the right child has no right child, it is the inorder predecessor
		if(parent.right.right == null){
			E returnValue = parent.right.data;
			parent.right = parent.right.left;
			return returnValue;
		} else {
			return findLargestChild(parent.right);
		}
	}
	
	public boolean remove(E target) {
		delete(target);
		return deleteReturn == target;
	}

	/**
	 * The iterator() function returns an iterator that iterates over the elements in the tree in the
	 * order specified by the traversal method.
	 * 
	 * @return An iterator that iterates through the tree in order.
	 */
	@Override
	public Iterator<E> iterator() 
	{
		return new BinaryTreeIterator<>(root);
	}

	/**
	 * The BinaryTreeIterator class is a class that implements the Iterator interface. It has a stack that
	 * is filled with an inorder traversal of the tree. The hasNext() method returns true if the stack is
	 * not empty, and the next() method returns the data of the top element of the stack
	 */
	private static class BinaryTreeIterator<E> implements Iterator<E>
	{
		private Stack<Node<E>> stack = new Stack<>();
		
		// Filling the stack with an inorder traversal of the tree rooted at localRoot.
		public BinaryTreeIterator(Node<E> localRoot)
		{
			fillStack(localRoot);
		}
		
		/**
		 * Fill the stack with an inorder traversal of the tree rooted at localRoot
		 * 
		 * @param localRoot The root of the tree.
		 */
		private void fillStack(Node<E> localRoot) 
		{
			if (localRoot != null)
			{
				stack.push(localRoot);
				fillStack(localRoot.left);
				fillStack(localRoot.right);
			}
		}

		/**
		 * If the stack is empty, return false, otherwise return true.
		 * 
		 * @return The next element in the tree.
		 */
		@Override
		public boolean hasNext()
		{
			return !stack.isEmpty();
		}

		/**
		 * If there is no next element, throw an exception. Otherwise, return the data of the top element of
		 * the stack
		 * 
		 * @return The data of the node that is being popped off the stack.
		 */
		@Override
		public E next()
		{
			if (!hasNext())
			{
				throw new NoSuchElementException();
			}
			return stack.pop().data;
		}

		/**
		 * This function throws an exception.
		 */
		@Override
		public void remove()
		{
			throw new UnsupportedOperationException();
		}
	}
}
