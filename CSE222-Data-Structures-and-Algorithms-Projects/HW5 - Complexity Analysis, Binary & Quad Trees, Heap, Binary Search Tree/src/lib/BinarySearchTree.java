package lib;

import java.util.Arrays;

// Defining an interface search tree classes.
public class BinarySearchTree<E extends Comparable<E>> implements SearchTree<E>
{
    /**
     * Default capacity of the tree.
     */
    private static final int DEFAULT_CAPACITY = 10;
    
    /**
     * The array that stores elements of the tree.
     */
    private E[] datas;

    // Constructor
    /**
     * Create a new BinarySearchTree with default capacity.
     */
    @SuppressWarnings("unchecked")
    public BinarySearchTree()
    {
        datas = (E[]) new Comparable[DEFAULT_CAPACITY];
    }

    /**
     * If the root is null, set the root to the item. Otherwise, find the correct place for the item
     * and set it there.
     * 
     * @param item The item to be added to the tree
     * @return The method returns a boolean value.
     */
    @Override
    public boolean add(E item) 
    {
        if(datas[0] == null)
        {
            datas[0] = item;
            datas[1] = null;
            datas[2] = null;
            return true;
        }

        // Find the correct place for the item to be added.
        int index = 0;
        while (datas[index] != null)
        {
            int res = datas[index].compareTo(item);
            if (res == 0)
                return false;
            if (res > 0)
            {
                index = 2 * index + 1;
            }
            else
            {
                index = 2 * index + 2;
            }
        }

        if (2 * index + 2 >= datas.length) 
            resize();
        
        datas[index] = item;
        datas[2 * index + 1] = null;
        datas[2 * index + 2] = null;
        return true;
    }

    /**
     * If the target is null, return true. Otherwise, iterate through the array and return true if the
     * target is found.
     * 
     * @param target The element to be searched for
     * @return The method returns true if the target is in the array, and false if it is not.
     */
    @Override
    public boolean contains(E target) 
    {
        return find(target) != null;
    }

    /**
     * If the target is null, return null. Otherwise, iterate through the array and return the
     * element that matches the target.
     * 
     * @param target The element to be found
     * @return The element that is being returned is the element that is being searched for.
     */
    @Override
    public E find(E target) 
    {
        if(target == null)
            return null;

        int i = 0;
        while (datas[i] != null)
        {
            int res = datas[i].compareTo(target);
            if (res == 0)
                return datas[i];
            if (res > 0)
            {
                i = 2 * i + 1;
            }
            else
            {
                i = 2 * i + 2;
            }
        }
        return null;
    }

    /**
     * If the target is not found, return null. If the target is found, remove the target and set the
     * child with the smallest value.
     * 
     * @param target The element to be deleted.
     * @return The element that was deleted.
     */
    @Override
    public E delete(E target) 
    {
        int index = findIndexOfTarget(target);
        if (index == -1)
            return null;
        
        E temp = datas[index];

        int childrenNum = getChildrenNum(index);

        switch (childrenNum) 
        {
            case 0:
                removeParentWithoutChild(index);
                break;
            case 1:
                removeParentWithOneChild(index);
                break;
            case 2:
                removeParentWithTwoChildren(index);
                break;
        }
        return temp;
    }

    /**
     * If the target is not found do nothing. If the target is found, remove the target and set the
     * child with the smallest value.
     * 
     * @param index The index that element of it will be deleted.
     */
    private void removeParentWithTwoChildren(int index) 
    {
        int smallerChildIndex = findSmallerChildIndex(index);
        int greatestRightChildIndex = findGreatestRightChildOfLeftChild(smallerChildIndex);
        datas[index] = datas[greatestRightChildIndex];
        
        if (getChildrenNum(greatestRightChildIndex) == 0)
            removeParentWithoutChild(greatestRightChildIndex);
        else
            removeParentWithOneChild(greatestRightChildIndex);
    }

    /**
     * Find the greatest right child of the left child of the smallest child of the root.
     * 
     * @param smallestChildIndex the index of the smallest child of the parent node
     * @return The greatest right child of the left child of the smallest child.
     */
    private int findGreatestRightChildOfLeftChild(int smallestChildIndex) 
    {
        // And also remove that child before return its value.
        int index = smallestChildIndex;
        while (2 * index + 2 < datas.length && datas[2 * index + 2] != null)
        {
            index = 2 * index + 2;
        }
        return index;
    }

    /**
     * If the left child is smaller than the right child, return the index of the left child.
     * Otherwise, return the index of the right child.
     * 
     * @param index the index of the parent node
     * @return The index of the smaller child.
     */
    private int findSmallerChildIndex(int index) 
    {
        int smallestChildIndex = 2 * index + 2;
        if (datas[index] != datas[2 * index + 1] && datas[2 * index + 2].compareTo(datas[2 * index + 1]) > 0)
            smallestChildIndex = 2 * index + 1;
        return smallestChildIndex;
    }

    /**
     * Return the number of child of the parent in given index.
     * 
     * @param index the index of the node in the array
     * @return The number of children of the node at the given index.
     */
    private int getChildrenNum(int index) 
    {
        int childrenNum = 0;
        if (datas[2 * index + 1] != null)
            childrenNum++;
        if (datas[2 * index + 2] != null)
            childrenNum++;
        return childrenNum;
    }

    /**
     * If the parent has one child, then the parent is replaced by its child, and the child is removed.
     * It continues, until no element left.
     * 
     * @param index The index of the parent node.
     */
    private void removeParentWithOneChild(int index) 
    {
        if (2 * index + 1 < datas.length)
        {
            int leftChildIndex = 2 * index + 1;
            int rightChildIndex = 2 * index + 2;

            if (datas[leftChildIndex] != null)
            {
                datas[rightChildIndex] = datas[index];
                removeParentWithTwoChildren(index);
                datas[rightChildIndex] = null;
            }
            else if (datas[rightChildIndex] != null)
            {
                System.out.println("herere");
                datas[leftChildIndex] = datas[index];
                removeParentWithTwoChildren(index);
                datas[leftChildIndex] = null;
            }
        }
    }

    /**
    * If the parent has no child, then the parent is removed.
    * 
    * @param index The index of the parent node.
    */
    private void removeParentWithoutChild(int index) 
    {
        datas[index] = null;
    }

    /**
     * If the target is less than the current node, go left. If the target is greater than the current
     * node, go right. If the target is equal to the current node, stop.
     * 
     * @param target The element we are looking for.
     * @return The index of the target.
     */
    private int findIndexOfTarget(E target) 
    {
        int index = 0;
        while (datas[index] != null)
        {
            int res = datas[index].compareTo(target);

            if (res == 0)
                return index;
            
            if(2 * index + 1 > datas.length - 1)
                resize();

            if (res > 0)
            {
                index = 2 * index + 1;
            }
            else
            {
                index = 2 * index + 2;
            }
        }
        return -1;
    }

    /**
     * If the target is found, remove it and return true. Otherwise, return false.
     * 
     * @param target The element to be removed
     * @return The method returns a boolean value.
     */
    @Override
    public boolean remove(E target) 
    {
        return delete(target) != null;
    }

    // Helper methods.
    /**
     * If the array is full, create a new array that is twice the size of the old array, copy the old
     * array into the new array, and then set the old array to the new array.
     */
    private void resize()
    {
        E[] temp = Arrays.copyOf(datas, datas.length * 2);
        datas = temp;
    }

    /**
     * The function preOrderTraverse() is called with the 0th index of array, the current depth, and a
     * StringBuilder object. 
     * 
     * @return The string representation of the tree.
     */
    @Override
    public String toString() 
    {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(0, 0, sb);
        return sb.toString();
    }

    /**
     * Return the root element of the heap.
     * 
     * @return The root of the tree.
     */
    public E getRoot()
    {
        return datas[0];
    }

    /**
     * If the index is less than the length of the array, then print the data at the index, then
     * recursively call the function on the left child and then the right child.
     * 
     * @param index the index of the current node in the array
     * @param counter This is the number of spaces to be printed before the data.
     * @param sb StringBuilder object that will be used to build the string
     */
    private void preOrderTraverse(int index, int counter, StringBuilder sb) 
    {
        if (index < datas.length)
        {
            for (int i = 0; i < counter; i++)
                sb.append("  ");

            sb.append(datas[index] + "\n");
            if(datas[index] != null)
                preOrderTraverse(2 * index + 1, counter + 1, sb);
            if(datas[index] != null)
                preOrderTraverse(2 * index + 2, counter + 1, sb);
        }
    }
}
