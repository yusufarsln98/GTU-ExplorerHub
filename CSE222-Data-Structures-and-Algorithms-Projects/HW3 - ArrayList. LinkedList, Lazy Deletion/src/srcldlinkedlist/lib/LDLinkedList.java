package srcldlinkedlist.lib;

import java.util.AbstractList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * This class is a linked list implementation of the List interface
 */
public class LDLinkedList<E> extends AbstractList<E> implements List<E>, Iterable<E>
{
    //  ------------------ Implementation of Node and Iterator Classes ------------------

    // Static inner node class. Keeps reference of head, tail and the data.
    /**
     * This is a private inner class that represents a LDLinkedList node, 
     * keeps reference of head and tail and a the data.
     */
    private static class Node<E>
    {
        // --- Parametrized constructor that takes the data will be kept. ---
        /**
         * It is parameterized constructor that takes the data will be kept.
         * @param data The data will be kept.
         */
        private Node(E data) 
        {
            this.data = data;
            next = null;
            previous = null;
        }

        // --- Node Data Fields ---
        private Node<E> next;
        private Node<E> previous;
        private E data;

        // --- Node Methods ---
        // Setter and Getter methods for the fields.

        /**
         * Return the next node in the list
         * 
         * @return The next node in the list.
         */
        private Node<E> getNext() 
        { 
            return next; 
        }
        /**
         * Set the next node
         * 
         * @param next The next node in the list.
         */
        private void setNext(Node<E> next) 
        { 
            this.next = next; 
        }


        /**
         * Return the previous node
         * 
         * @return The previous node.
         */
        private Node<E> getPrevious() { return previous; }
        /**
         * Set the previous node
         * 
         * @param previous The previous node in the list.
         */
        private void setPrevious(Node<E> previous) { this.previous = previous; }

        /**
         * It sets the data field of the node to the given data.
         * 
         * @param data The data to be stored in the node.
         */
        private void setData(E data){ this.data = data; }
        /**
         * Returns the data stored in the node
         * 
         * @return The data member of the node.
         */
        private E getData(){ return data; }

        @Override
        public String toString() 
        {
            return data.toString();
        }
    }
    // --- Node ---

    /**
    * This class implements the Iterator interface
    */
    private class LDIterator implements Iterator<E>
    {
        // A constructor of LDIterator class.
        // It initializes the nextItem field to the head of the list.
        public LDIterator()
        {
            nextItem = head;
            lastItemReturned = null;
        }

        // Private fields that keeps the reference of the next node and the last node returned.
        private Node <E> nextItem; 
        private Node <E> lastItemReturned; 


        /**
         * Return true if there is a next item in the iteration.
         * 
         * @return boolean.
         */
        @Override
        public boolean hasNext() 
        {
            return nextItem != null;
        }

        /**
         * Return the next item in the iteration.
         * 
         * @return The data of the next item in the list.
         */
        @Override
        public E next() 
        {
            if (!hasNext())
                throw new NoSuchElementException("Size: " + size());
            
            // Iterate the iterator and return the item that passed it.
            lastItemReturned = nextItem;
            nextItem = nextItem.getNext();

            return lastItemReturned.getData();
        }
    }
    // --- LDIterator Implementation ---

    /**
     * This class implements the ListIterator interface
     */
    private class LDListIterator implements ListIterator<E>
    {
        // Default constructor of LDListIterator class.
        // It initializes the nextItem field to the head of the list.
        public LDListIterator() 
        { 
            nextItem = head;
            lastItemReturned = null;
            index = 0;
        }

        // Parametrized constructor of LDListIterator class.
        // It initializes the nextItem field to the according to the index.
        public LDListIterator(int i) 
        { 
            // Validate i parameter. 
            if (i < 0 || i > size) 
                throw new IndexOutOfBoundsException("Size: " + size() + " Position: " + i);
            
            lastItemReturned = null;
            
            if (i == size)
            {
                index = size;
                nextItem = null;
            }
            else
            {
                nextItem = head;
                for (index = 0; index < i; index++)
                    nextItem = nextItem.getNext();
            }
        }


        // --- LDListIterator Data Fields ---
        private Node <E> nextItem; 
        private Node <E> lastItemReturned;
        private boolean isReturnedByNext = false;
        int index;

        // Overrided methods of ListIterator interface.
        
        public void add(E element) 
        {
            if (nextItem != null && lastItemReturned == null)
            {
                throw new IllegalStateException("There is no 'lastItemReturned'!");
            }
            if (nextItem == null)
            {
                addLast(element);
                index++;
            }
            else
            {
                addBefore(nextItem, element);
                index++;
            }
        }
        
        /**
         * If the last item returned is the head, then set the head to the next node and set the
         * previous node to null. If the last item returned is the tail, then set the tail to the
         * previous node and set the next node to null. If the last item returned is in the middle of
         * the list, then change the next and previous references.
         */
        @Override
        public void remove() 
        {
            // Check for the validity.
            if (lastItemReturned == null) 
            {
                throw new IllegalStateException("There is no 'lastItemReturned'!");
            }
            else
            {
                // If there is only one element in the list, then remove it.
                if (size == 1)
                {
                    head = null;
                    tail = null;
                    index = 0;
                }
                // Checking if the last item returned is the head. If it is, it sets the head to the
                // next node and sets the previous node to null.
                else if (lastItemReturned == head)  
                {
                    head = head.getNext();
                    head.setPrevious(null);
                    index = 0;
                }
                // Checking to see if the item returned is the last item in the list. If it is, it sets
                // the tail to the previous item in the list.
                else if (lastItemReturned == tail)
                {
                    
                    tail = tail.getPrevious();
                    tail.setNext(null);
                    if (isReturnedByNext)
                        index--;
                } 
                // If an element that middle of the list wants to be remove,
                // Change the next and previous references.
                else
                {
                    lastItemReturned.getNext().setPrevious(lastItemReturned.getPrevious());
                    lastItemReturned.getPrevious().setNext(lastItemReturned.getNext());
                    if (isReturnedByNext) 
                        index--;
                }
                lastItemReturned.next = null;
                lastItemReturned.previous = null;
                lazyList.add(lastItemReturned);
                lastItemReturned = null;

                if (!isReturnedByNext)
                    nextItem = nextItem.getNext();
                
                size--;
            }
        }

        /**
         * Returns true if there is another item in the iteration.
         * 
         * @return boolean.
         */
        @Override
        public boolean hasNext() 
        {
            return nextItem != null;
        }

        /**
         * The next method returns the next item in the list
         * and move forward through the list once.
         * 
         * @return The data of the item that was returned last.
         */
        @Override
        public E next() 
        {
            if (!hasNext())
                throw new NoSuchElementException();
            
            // Iterate the iterator and return the item that passed it.
            lastItemReturned = nextItem;
            nextItem = nextItem.getNext();
            isReturnedByNext = true;
            index++;
            
            return lastItemReturned.getData();
        }

        /**
         * Returns true if there is a previous item in the list.
         * 
         * @return boolean.
         */
        @Override
        public boolean hasPrevious() 
        {
            return ((nextItem == null && size != 0) || (size != 0 && nextItem.getPrevious() != null));
        }

        /**
         * Returns data of the previous element in the list.
         * and move backwards through the list once.
         * 
         * @return The data of the item that was returned last.
         */
        @Override
        public E previous() 
        {
            if (!hasPrevious()) 
                throw new NoSuchElementException("You are at the head!");
            
            // If the iterator points to the null, which means that
            // it is pointing to one after the tail.
            if (nextItem == null) 
                nextItem = tail;
            else 
                nextItem = nextItem.getPrevious(); 
            
            lastItemReturned = nextItem;
            isReturnedByNext = false;
            index--; 

            return lastItemReturned.data;
        }
        
        /**
         * Returns the index of the next element in the iteration.
         * 
         * @return The index of the next element.
         */
        @Override
        public int nextIndex() 
        {
            return index;
        }

        /**
         * Return the index of the previous element in the iteration.
         * 
         * @return The index of the previous element.
         */
        @Override
        public int previousIndex() 
        {
            return index - 1;
        }

        /**
         * The set method sets the data of the last item returned by the iterator.
         * 
         * @param element The element to be set.
         */
        @Override
        public void set(E element) 
        {
            lastItemReturned.setData(element);
        }
    }
    // --- LDListIterator Implementation ---
    //  ------------------ Implementation of Node and Iterator Classes ------------------


    // ------- Implementation of IndelibleLinkedList class --------

    /**
     * This class is a very simple list class that includes nodes, 
     * which want to be removed from the LDLinkedList.
     */
    private class LazyLinkedList
    {
        // Creating a new instance of the LazyLinkedList class.
        /**
         * Default constructor of the LazyLinkedList.
         */
        protected LazyLinkedList()
        {
            lazyList = new LinkedList<>();
            size = 0;
        }

        private LinkedList<Node<E>> lazyList;
        private int size;

        /**
         * Add a node to the LazyLinkedList.
         * 
         * @param node The node to be added to the LazyLinkedList.
         */
        protected void add(Node<E> node)
        {
            lazyList.add(node);
            size++;
        }
        
        /**
         * Remove the element at the specified index from the LazyLinkedList.
         * 
         * @param index The index of the node to be removed.
         * @return The node at the given index.
         */
        protected Node<E> steal()
        {
            size--;
            return lazyList.removeFirst();
        }

        /**
         * Return the number of elements in the list
         * 
         * @return The size of the list.
         */
        protected int size()
        {
            return size;
        }

        /**
         * This function returns a string representation of the LazyLinkedList.
         * 
         * @return The toString method returns a String representation of the LazyLinkedList.
         */
        @Override
        public String toString() 
        {
            StringBuilder bul = new StringBuilder();
            ListIterator<Node<E>> iter = lazyList.listIterator();
            
            bul.append("[");
            for (int i = 0; i < lazyList.size(); i++)
            {
                if (i == lazyList.size() - 1)
                {
                    bul.append(iter.next());
                }
                else
                    bul.append(iter.next() + ", ");
                
            }
            bul.append("]");        

            return bul.toString();
        }
    }


    //  ------------------ Implementation of LDLinkedList ------------------

    // The default constructor of LDLinkedList.
    /**
     * Default constructor of LDLinkedList.
     * Initializes head and tail with nulla and size with 0.
     */
    public LDLinkedList()
    {
        head = null;
        tail = null;
        size = 0;
        lazyList = new LazyLinkedList();
    }

    // Data Fields
    private Node<E> head;
    private Node<E> tail;
    private int size;
    private LazyLinkedList lazyList;

    // ------ Override Methods of List interface and AbstractList abstract class ---------
    /**
     * Add an element to the end of the list
     * 
     * @param element The element to be added to the list.
     * @return true.
     */
    @Override
    public boolean add(E element) 
    {
        addLast(element);
        return true;
    }
    
    /**
     * Go to the index and add element before the index.
     * 
     * @param index The index of the element that we want to add before.
     * @param element The element to be added.
     */
    @Override
    public void add(int index, E element) 
    {
        // Check the if index is valid.
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("Size: " + size + " Index: " + index);

        if (index == 0)
            addFirst(element);
        else if (index == size - 1)
            addLast(element);
        else
        {
            // Create a temp reference and assign it to the head.
            // Go the node that we want to add element before it and
            // invoke addBefore with this node and element.
            Node<E> temp = head;

            for (int i = 0; i < index; i++)
            {
                temp = temp.getNext();
            }
            addBefore(temp, element);
        }
        
    }

    @Override
    public E remove(int index) 
    {
        // Check the if index is valid.
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("Size: " + size + " Index: " + index);
        
        ListIterator<E> iterator = listIterator(index);
        E removedItem = iterator.next();
        iterator.remove();

        return removedItem;
    }

    /**
     * Returns true if the specified element removed successfully, false otherwise
     * 
     * @param o The object to be removed.
     * @return The boolean value of the remove method.
     */
    @Override
    public boolean remove(Object o)
    {
        ListIterator<E> iterator = listIterator();
        while (iterator.hasNext())
        {
            if(o.equals(iterator.next()))
            {
                iterator.remove();
                return true;
            }    

        }
        return false;
    }
    
    /**
     * Given a list iterator positioned at the specified index, 
     * replace the element at that index with the specified element. 
     * 
     * The list iterator is returned to the original element.
     * 
     * @param index The index of the element to be replaced.
     * @param element The element to be inserted into the list.
     * @return The overwritten item.
     */
    @Override
    public E set(int index, E element) 
    {
        E overwrittenItem;

        ListIterator<E> iterator = listIterator(index);
        overwrittenItem = iterator.next();
        iterator.set(element);
        
        return overwrittenItem;
    }

    @Override
    public E get(int index) 
    {
        return listIterator(index).next();
    }

    /**
     * Return the first element in the list
     * 
     * @return The data of the first node in the list.
     */
    public E getFirst()
    {
        if (size == 0)
            throw new IllegalStateException("Size: 0");
        
        return head.getData();
    }

    /**
     * Return the last element in the list
     * 
     * @return The data of the last node in the list.
     */
    public E getLast()
    {
        if (size == 0)
            throw new IllegalStateException("Size: 0");
        
        return tail.getData();
    }

    /**
     * Return the number of elements in the list
     * 
     * @return The size of the list.
     */
    @Override
    public int size() 
    {
        return size;
    }

    /**
     * If the other object is the head or tail, return 0 or size - 1, respectively. Otherwise, iterate
     * through the list until the other object is found or the end of the list is reached. If the other
     * object is found, return the index of the object. Otherwise, return -1.
     * 
     * @param oth the object to be searched for.
     * @return The index of the object in the list.
     */
    @Override
    public int indexOf(Object oth) 
    {
        int index = -1;
        for (var element : this)
        {
            if (element.equals(oth))
            {
                return ++index;
            }
            index++;
        }
        return index;
    }
    

    // --- Method that returns Iterators ---
    /**
     * Create a new Iterator and return it
     * 
     * @return An iterator.
     */
    @Override
    public Iterator<E> iterator() 
    {
        // Create a new LDIterator and return it.
        return new LDIterator();
    }
    
    /**
     * Return a list iterator that will traverse the elements in this list in proper sequence
     * 
     * @return A new LDListIterator object.
     */
    @Override
    public ListIterator<E> listIterator() 
    {
        // Create a default LDListIterator object and return it.
        return new LDListIterator();
    }

    /**
     * Create a new LDListIterator object with the given index and return it
     * 
     * @param index The index of the element that the iterator should point to.
     * @return A ListIterator object.
     */
    @Override
    public ListIterator<E> listIterator(int index) 
    {
        // Create LDListIterator object with index and return it.
        return new LDListIterator(index);
    }
        
    /**
     * This function checks if the two lists are equal.
     * 
     * @param obj the object to compare to.
     * @return The boolean value of the equals method.
     */
    @SuppressWarnings("unchecked")
    @Override
    public boolean equals(Object obj) 
    {
        // Check if the object is of the same class.
        if (this == obj)
            return true;
        if (!super.equals(obj))
            return false;
        if (getClass() != obj.getClass())
            return false;

        // Checking if the two lists are equal.
        LDLinkedList<E> other = (LDLinkedList<E>) obj;
        if (head == null) 
        {
            if (other.head != null)
                return false;
        } 
        else if (!head.equals(other.head))
            return false;
        if (lazyList == null) 
        {
            if (other.lazyList != null)
                return false;
        } 
        else if (!lazyList.equals(other.lazyList))
            return false;
        if (size != other.size)
            return false;
        if (tail == null) 
        {
            if (other.tail != null)
                return false;
        } 
        else if (!tail.equals(other.tail))
            return false;
        return true;
    }
    
    /**
     * The hashCode method is implemented by calling the hashCode method of the head and tail nodes, 
     * and adding the size of the list
     * 
     * @return The hash code of the head of the list.
     */
    @Override
    public int hashCode() {
        final int prime = 31;
        int result = super.hashCode();
        result = prime * result + ((head == null) ? 0 : head.hashCode());
        result = prime * result + ((lazyList == null) ? 0 : lazyList.hashCode());
        result = prime * result + size;
        result = prime * result + ((tail == null) ? 0 : tail.hashCode());
        return result;
    }
    
    /**
     * This method returns a string representation of the LDLinkedList.
     * 
     * @return The string representation of the list.
     */
    @Override
    public String toString() 
    {
        StringBuilder bul = new StringBuilder();
        bul.append("[");
        Node<E> temp = head;
        while (temp != null) 
        {
            if (temp.getNext() != null)
                bul.append(temp.getData() + ", ");
            else
                bul.append(temp.getData());

            temp = temp.getNext();
        }

        bul.append("]");

        return bul.toString();
    }
    // ------- Implementations of Object class -------


    // ------------ Helper Methods ------------
    /**
     * Add a new node to the beginning of the list and change the head of the list.
     * 
     * @param element The element to be added to the list.
     */
    public void addFirst(E element)
    {
        Node<E> temp = createNode(element);

        if (size == 0)
        {
            // Creating a new node and setting the head and tail to that node.
            head = temp;
            tail = head;
            size++;
        }
        else
        {   
            // Add a new node to the beginning of the list and change the head of the list.
            temp.setNext(head);
            head.setPrevious(temp);
            head = temp;
            size++;
        }
    }

    /**
     * If the list is empty, add the element to the head of the list. Otherwise, add the element to the
     * end of the list and change the tail to the new node.
     * 
     * @param element The element to be added to the list.
     */
    public void addLast(E element)
    {
        if (size == 0)
        {
            // If size equals 0, then add element to the head of the list.
            addFirst(element);
        }
        else
        {
            // Otherwise, add element to the and of the list and change tail with the new node.
            Node<E> temp = createNode(element);
            temp.setPrevious(tail);
            tail.setNext(temp);
            tail = temp;
            size++;
        }
    }

    /**
     * Add an element before the node that wants to be added before it.
     * 
     * @param node The node that we want to add before.
     * @param element The element to be added.
     */
    private void addBefore(Node<E> node, E element)
    {
        // Add element before the node.
        Node<E> temp = createNode(element);

        node.getPrevious().setNext(temp);
        temp.setPrevious(node.getPrevious());
        temp.setNext(node);
        node.setPrevious(temp);

        size++;
    }

    /**
     * Creates a new node and adds it to the end of the list.
     * 
     * @param data The data to be stored in the node.
     * @return The node that was created.
     */
    private Node<E> createNode(E data)
    {
        Node<E> node;

        if (lazyList.size() == 0)
            node = new Node<>(data);
        else
        {
            node = lazyList.steal();
            node.setData(data);
            node.setNext(null);
            node.setPrevious(null);
        }

        return node;
    }

}
