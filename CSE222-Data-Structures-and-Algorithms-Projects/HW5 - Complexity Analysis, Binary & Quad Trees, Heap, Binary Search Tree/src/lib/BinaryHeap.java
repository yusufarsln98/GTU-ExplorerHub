package lib;

import java.util.NoSuchElementException;

/**
 * The BinaryHeap class is a subclass of the BinaryTree class, and it adds a size field, a parent
 * field, and a depth field to the inherited BinaryTree class
 */
public class BinaryHeap<E extends Comparable<E>> extends BinaryTree<E>
{
    // Data Fields
    /**
     * Instance of Node class. It is a reference that the item will be stored one of its children.
     */
    private Node<E> itemWillBeAdded;

    /**
     * Instance of Node class. It is a reference that its item will 
     * be replaced with the root which will be polled or removed.
     */
    private Node<E> itemWillBeReplaced;

    /**
     * Size of the heap.
     */
    private int size = 0;

    /**
     *  Defaul constructor. Creates an empty heap.
     */  
    public BinaryHeap()
    {
        super();
    }

    /**
     * Parameterized copy constructor. Creates a heap with another heap.
     * @param other The heap to be copied.
     */
    public BinaryHeap(BinaryHeap<E> other)
    {
        // A constructor that takes a BinaryHeap as parameter and insert all the elements of it to the new heap.
        insertElements(this, (BinaryHeap<E>.Node<E>) other.root);
    }

    // Methods
    /**
     * The function finds the depth of the node that item will be added, then finds the place of the node
     * that will be added, then adds the node to the heap with protecting heap structure.
     * 
     * @param item The item to be added to the heap.
     * @return The method returns true if the item is added to the heap, otherwise it returns false.
     */
    public boolean offer(E item)
    {
        int depth = findDepthOfHeap();

        // Add an item to the heap with protecting heap structure.
        if (size == 0)
        {
            root = new Node<>(item, null, 1);
        }
        else
        {
            findPlaceNodeWillBeAdded((BinaryHeap<E>.Node<E>) root, depth);
            if (itemWillBeAdded == null)
                return false;
                
            Node<E> theNewNode = new Node<>(item, itemWillBeAdded, depth + 1);
            if (itemWillBeAdded.left == null)
                itemWillBeAdded.left = theNewNode;
            else
                itemWillBeAdded.right = theNewNode;

            // Fix the heap structure.
            fixHeapOrderAfterAdd(theNewNode);
        }
        size++;
        itemWillBeAdded = null;
        return true;
    }

    /**
     * Find the depth of the node that a new node will be modified.
     * 
     * @return The depth of the node.
     */
    private int findDepthOfHeap() 
    {
        // Calculate the total number of nodes in the h-1 level and and according to result
        // return the depth of the node that item will be added.
        int perfectNodeNumber = 0;
        int depth = 0;
        int result;

        while (true)
        {
            result = (int) Math.pow(2, depth);
            if (result + perfectNodeNumber > size)
                break;
            perfectNodeNumber += result;
            depth++;
        }
        return depth;
    }

    /**
     * If the item is not in the tree, find the first node at the given depth that has a null child
     * 
     * @param localRoot The root of the tree
     * @param depth the depth of the node that will be added
     */
    private void findPlaceNodeWillBeAdded(BinaryHeap<E>.Node<E> localRoot, int depth) 
    {
        // Traverse inorder to find the first node at the given depth that has a null child.
        if (localRoot == null)
        { /* Do nothing */ }
        else if (itemWillBeAdded == null)
        {
            if (localRoot.left != null)
                findPlaceNodeWillBeAdded((BinaryHeap<E>.Node<E>) localRoot.left, depth);
            
            if (localRoot.depth == depth && (localRoot.left == null || localRoot.right == null))
            {
                itemWillBeAdded = localRoot;
                return;
            }
            
            if (localRoot.right != null)
                findPlaceNodeWillBeAdded((BinaryHeap<E>.Node<E>) localRoot.right, depth);
        }
    }
    
    /**
     * If the item is in the tree, return true. Otherwise, return false.
     * 
     * @param item the item to be searched for
     * @return The node that contains the item.
     */
    public boolean contains(E item)
    {
        return (findNode(root, item) != null);
    }

    /**
     * If the item not in the heap, return null, otherwise return the node.
     * 
     * @param root The root of the tree to search
     * @param item the item to be found
     * @return The node that contains the item.
     */
    protected Node<E> findNode(lib.BinaryTree.Node<E> root, E target) 
    {
        if (root == null)
            return null;
        if (root.data.compareTo(target) == 0)
            return (BinaryHeap<E>.Node<E>) root;
        Node<E> left = findNode(root.left, target);
        if (left != null)
            return left;
        return findNode(root.right, target);
    }

    /**
     * If the node is not the root, and the node's data is less than its parent's data, swap the node
     * with its parent, and recursively call fixHeapOrderAfterAdd on the parent.
     * 
     * @param node the node that we are fixing the heap order for
     */
    private void fixHeapOrderAfterAdd(BinaryHeap<E>.Node<E> node) 
    {
        // If the node is not the root, and the node's data is less than its parent's data, swap the node.
        if(node.parent != null)
        {
            int comp = node.data.compareTo(node.parent.data);
            if (comp < 0)
            {
                swap(node, node.parent);
                fixHeapOrderAfterAdd(node.parent);
            }
        }
    }

    /**
     * Swap the data of the node with the data of its parent.
     * 
     * @param node the node that is being swapped
     * @param left The parent node of the node we're swapping with.
     */
    private void swap(BinaryHeap<E>.Node<E> parent, BinaryHeap<E>.Node<E> child) 
    {
        E temp = parent.data;
        parent.data = child.data;
        child.data = temp;
    }

    /**
     * We find the furthest node from the root, then we replace the root with the furthest node, then
     * we fix the heap order.
     * 
     * @return The root of the heap.
     */
    public E poll()
    {
        if(isEmpty())
            return null;

        E removedItem = root.data;

        if(size == 1)
        {
            root = null;
            size--;
            return removedItem;
        }
        itemWillBeReplaced = (BinaryHeap<E>.Node<E>) root;
        findFurthestNode((BinaryHeap<E>.Node<E>) root);

        // Remove the furthest node from the heap.
        if(itemWillBeReplaced.parent.left == itemWillBeReplaced)
            itemWillBeReplaced.parent.left = null;
        else
            itemWillBeReplaced.parent.right = null;

        root.data = itemWillBeReplaced.data;
        fixHeapOrderAfterRemove();
        
        size--;
        return removedItem;
    }

    /**
     * It fixes the heap order after a remove operation.
     */
    private void fixHeapOrderAfterRemove() 
    {
        // If the head is larger than its any child, swap the head with the smallest child.
        // Iteration continues until the head is smaller than its children or no element left.
        BinaryHeap<E>.Node<E> head = (BinaryHeap<E>.Node<E>) root;
        while(head.left != null)
        {
            if (head.right == null && head.data.compareTo(head.left.data) > 0)
            {
                swap(head, (BinaryHeap<E>.Node<E>) head.left);
                head = (BinaryHeap<E>.Node<E>) head.left;
            }
            else if (head.right != null)
            {
                if(head.left.data.compareTo(head.right.data) < 0)
                {
                    swap(head, (BinaryHeap<E>.Node<E>) head.left);
                    head = (BinaryHeap<E>.Node<E>) head.left;
                }
                else
                {
                    swap(head, (BinaryHeap<E>.Node<E>) head.right);
                    head = (BinaryHeap<E>.Node<E>) head.right;
                }
            }
            else
                break;
        }
    }
    
    /**
     * If the node is a leaf, check if it's depth is greater than the current furthest node. If it
     * is, set it as the furthest node. If it's not a leaf, recursively call the function on the left
     * and right nodes
     * 
     * @param localNode The node that is being checked.
     */
    private void findFurthestNode(BinaryHeap<E>.Node<E> localNode) 
    {
        if(localNode == null)
        { /* Do nothing */ }
        else if(localNode.left == null && localNode.right == null)
        {
            if (localNode.depth >= itemWillBeReplaced.depth)
                itemWillBeReplaced = localNode;
        }
        else
        {
            findFurthestNode((BinaryHeap<E>.Node<E>) localNode.left);
            findFurthestNode((BinaryHeap<E>.Node<E>) localNode.right);
        }
    }

    /**
     * If the heap is empty, throw an exception. Otherwise, return the value of the first element in
     * the heap and remove it from the heap.
     * 
     * @return The first element in the heap.
     */
    public E remove()
    {
        if (isEmpty())
        {
            throw new NoSuchElementException();
        }
        return poll();
    }
    
    /**
     * If the heap is empty, return null, otherwise return the root's data.
     * 
     * @return The data of the root node.
     */
    public E peek()
    {
        if (isEmpty())
            return null;
        return root.data;
    }
    
    /**
     * If the heap is empty, throw an exception. Otherwise, return the smallest element in the heap.
     * 
     * @return The smallest element in the heap.
     */
    public E element()
    {
        E result = peek();
        
        if (result == null)
            throw new NoSuchElementException();
        return result;
    }

    /**
     * Returns the number of elements in this heap.
     * 
     * @return The size of the heap.
     */
    public int size()
    {
        return size;
    }
    
    /**
     * Returns true if the heap is empty, false otherwise.
     * 
     * @return The size of the heap.
     */
    public boolean isEmpty()
    {
        return size == 0;
    }

    /**
     * Merge two binary heaps into a new binary heap.
     * 
     * @param other The other heap to merge with this one.
     * @return A new BinaryHeap object that contains all the elements of the two BinaryHeap objects
     * that were merged.
     */
    public BinaryHeap<E> merge(BinaryHeap<E> other)
    {
        BinaryHeap<E> result = new BinaryHeap<>();
        
        insertElements(result, (BinaryHeap<E>.Node<E>) this.root);
        insertElements(result, (BinaryHeap<E>.Node<E>) other.root);

        return result;
    }

    /**
     * Take a root as parameter and insert all the elements of the tree into the new heap.
     * 
     * @param result the BinaryHeap that we are inserting the elements into
     * @param localRoot the root of the tree
     */
    private void insertElements(BinaryHeap<E> heap, BinaryHeap<E>.Node<E> localRoot) 
    {
        if (localRoot == null)
            return;
        else
        {
            insertElements(heap, (BinaryHeap<E>.Node<E>) localRoot.left);
            heap.offer(localRoot.data);
            insertElements(heap, (BinaryHeap<E>.Node<E>) localRoot.right);
        }
    }

    /**
     * If the new value is greater than the current value, then replace the current value with the new
     * value and fix the heap order.
     * 
     * @param current The current value of the node that you want to change.
     * @param newValue The new value to be assigned to the node.
     */
    public void increaseKey(E current, E newValue)
    {
        if (current == null || newValue == null || newValue.compareTo(current) < 0)
            throw new IllegalArgumentException();
        
        
        BinaryHeap<E>.Node<E> node = findNode(root, current);
        
        if (node == null)
            throw new NoSuchElementException();
        
        node.data = newValue;
        fixHeapOrderAfterIncreaseKey(node);
    }

    /**
     * Fixes the heap order after an increaseKey operation.
     * 
     * @param node The node that we want to fix the heap order for.
     */
    private void fixHeapOrderAfterIncreaseKey(BinaryHeap<E>.Node<E> node) 
    {
        // Check for the left node, if the left node smaller than the parent, swap them.
        // If not, check for the right node, if the right node smaller than the parent, swap them.
        // If both are larger than the parent, break the loop.
        while (true)
        {
            if (node.left != null && node.data.compareTo(node.left.data) > 0 && node.left.data.compareTo(node.right.data) < 0)
            {
                swap(node, (BinaryHeap<E>.Node<E>) node.left);
                node = (BinaryHeap<E>.Node<E>) node.left;
            }
            else if (node.right != null && node.data.compareTo(node.right.data) > 0)
            {
                swap(node, (BinaryHeap<E>.Node<E>) node.right);
                node = (BinaryHeap<E>.Node<E>) node.right;
            }
            else
                break;
        }
    }

    /**
     * The Node class is a subclass of the BinaryTree.Node class, and it adds a parent and depth field
     * to the inherited BinaryTree.Node class
     */
    protected class Node<E> extends BinaryTree.Node<E>
    {
        // Add the parent and depth information to the inherited Node class.
        protected Node(E data)
        {
            super(data);
            parent = null;
            depth = 0;
        }
        protected Node(E data, Node<E> parent, int depth)
        {
            super(data);
            this.parent = parent;
            this.depth = depth;
        }
        protected Node<E> parent;
        protected int depth;
    }

}