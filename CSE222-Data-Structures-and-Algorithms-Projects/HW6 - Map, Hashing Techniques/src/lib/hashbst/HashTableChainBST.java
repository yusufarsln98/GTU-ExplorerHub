package lib.hashbst;

import java.util.Iterator;

import lib.hashbst.bst.BinarySearchTree;

@SuppressWarnings("unchecked")
public class HashTableChainBST<K extends Comparable<K>, V extends Comparable<V>> implements HashMap<K, V>
{
    private static final int INITIAL_CAPACITY = 11;
    private static final double LOAD_THRESHOLD = 2;
    private int numKeys;

    private BinarySearchTree<Entry<K,V>>[] table; 
    
    /**
     * Constructor
     * Creating a new table with the size of the initial capacity.
     */
    public HashTableChainBST()
    {
        table = new BinarySearchTree[INITIAL_CAPACITY];
        numKeys = 0;
    }

    // A constructor that creates a new table with the size of the capacity passed in as a parameter.
    public HashTableChainBST(int capacity)
    {
        table = new BinarySearchTree[capacity];
        numKeys = 0;
    }

    /**
     * If the key and value already exist in the BinarySearchTree object, then return the value. If the
     * key and value does not exist in the BinarySearchTree object, then add the key and value to the
     * BinarySearchTree object
     * 
     * @param key The key of the entry to be added to the map.
     * @param value The value to be associated with the specified key.
     * @return The value of the key that was added to the BinarySearchTree object.
     */
    @Override
    public V put(K key, V value) 
    {
        int index = findIndexFromKey(key);

        if (table[index] == null)
        {
            // Creating a new BinarySearchTree object and assigning it to 
            // the index of the table if current position is null.
            table[index] = new BinarySearchTree<>();
        }
        
        // Adding the key and value to the BinarySearchTree object.
        // If the key is already in the tree, the value is replaced.
        Entry<K, V> entry = table[index].find(new Entry<>(key, value));

        if (entry != null)
        {
            // If the key and value already exist in the BinarySearchTree object,
            // then return the value.
            V oldValue = entry.getValue();
            entry.setValue(value);
            return oldValue;
        } 
        else 
        {
            // If the key and value does not exist in the BinarySearchTree object,
            // then add the key and value to the BinarySearchTree object.
            table[index].add(new Entry<>(key, value));
            numKeys++;
            if (numKeys > table.length * LOAD_THRESHOLD)
            {
                // If the load factor is greater than the load threshold,
                // then increase the size of the table by the initial capacity.
                rehash();
            }
            return null;
        }
    }

    /**
     * The hashCode() method of the key object is used to find the index of the array where the
     * key-value pair should be stored.
     * 
     * @param key The key to find the index for.
     * @return The index of the key in the table.
     */
    private int findIndexFromKey(K key) 
    {
        int index = key.hashCode() % table.length;
        index = index < 0 ? index + table.length : index;
        return index;
    }

    /**
     * The function rehashes the table by creating a new table with the size of the current table plus
     * the old capacity.
     */
    private void rehash() 
    {
        // Creating a new table with the size of the current table plus the old capacity.
        BinarySearchTree<Entry<K, V>>[] oldTable = table;
        table = new BinarySearchTree[oldTable.length * 2 + 1];
        numKeys = 0;
        for (int i = 0; i < oldTable.length; i++) 
        {
            if (oldTable[i] != null) 
            {
                // Iterating through the BinarySearchTree object 
                // and adding the key and value to the new table.
                Iterator<Entry<K, V>> iterator = oldTable[i].iterator();
                while (iterator.hasNext()) 
                {
                    Entry<K, V> entry = iterator.next();
                    put(entry.getKey(), entry.getValue());
                }
            }
        }
    }

    /**
     * Find the value associated with the given key.
     * If there is no value associated with the key, return null.
     * 
     * @param key The key to search for.
     * @return The value associated with the key.
     */
    @Override
    public V get(Object key) 
    {
        if (key == null)
        {
            throw new IllegalArgumentException("Key cannot be null.");
        }
        
        int index = findIndexFromKey((K) key);
        if (table[index] == null)
        {
            return null;
        }
        else
        {
            // Find the value associated with the key. 
            // If there is no value associated with the key, return null.
            Entry<K, V> entry = table[index].find(new Entry<>((K) key, null));
            if (entry != null)
            {
                return entry.getValue();
            }
            else
            {
                return null;
            }
        }
    }

    /**
     * Remove the value associated with the key.
     * 
     * @param key The key of the entry to remove from this map.
     * @return The value of the key that is being removed.
     */
    @Override
    public V remove(Object key) 
    {
        if (key == null)
        {
            throw new IllegalArgumentException("Key cannot be null.");
        }
        int index = findIndexFromKey((K) key);
        if (table[index] == null)
        {
            return null;
        }
        else
        {
            // Removing the key and value from the BinarySearchTree object.
            Entry<K, V> entry = table[index].find(new Entry<>((K) key, null));
            if (entry != null)
            {
                V value = entry.getValue();
                table[index].remove(entry);

                // If the BinarySearchTree object is empty, then 
                // remove the BinarySearchTree object from the table.
                if ("".equals(table[index].toString()))
                {
                    table[index] = null;
                }
                numKeys--;
                return value;
            }
            else
            {
                return null;
            }
            
        }
    }

    /**
     * Returns true if the size of the list is 0, otherwise returns false.
     * 
     * @return The size of the list.
     */
    @Override
    public boolean isEmpty() 
    {
        return size() == 0;
    }

    /**
     * Returns the number of keys in the table.
     * 
     * @return The number of keys in the table.
     */
    @Override
    public int size() {
        return numKeys;
    }
    
    @Override
    public String toString() 
    {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < table.length; i++)
        {
            sb.append("index: " + i + "\n");
            if (table[i] != null)
            {
                sb.append(table[i].toString());
                sb.append("\n");
            }
            else
            {
                sb.append("null\n\n");
            }
        }
        return sb.toString();
    }

    /**
     * Entry is a class that holds a key and a value, where the value is comparable.
     */
    private static class Entry<K extends Comparable<K>, V extends Comparable<V>> implements Comparable<Entry<K, V>>
    {
        // Declaring a variable called key of type K.
        private K key;

        // Declaring a variable called key of type V.
        private V value;
        
        // A constructor for the Entry class.
        public Entry(K key, V value)
        {
            this.key = key;
            this.value = value;
        }

        /**
         * @return the key
         */
        public K getKey() {
            return key;
        }

        /**
         * It returns the value of the node
         * 
         * @return The value of the key-value pair.
         */
        public V getValue() {
            return value;
        }

        /**
         * It sets the value of the current node to the value passed in as a parameter, and returns the
         * old value
         * 
         * @param value The value of the entry.
         * @return The old value of the entry.
         */
        public V setValue(V value) {
            V oldValue = this.value;
            this.value = value;
            return oldValue;
        }
        /**
         * The compareTo() method compares the value of the current object with the value of the object
         * passed as an argument
         * 
         * @param o The object to be compared.
         * @return The value of the entry.
         */
        @Override
        public int compareTo(Entry<K, V> o) {
            return key.compareTo(o.key);
        }

        /**
         * The toString() method returns a string representation of the object
         * 
         * @return The key and value of the node as a String.
         */
        @Override
        public String toString() {
            return key + "=" + value;
        }
    }
}
