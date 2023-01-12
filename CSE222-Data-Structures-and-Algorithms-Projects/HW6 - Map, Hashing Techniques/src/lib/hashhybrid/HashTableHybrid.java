package lib.hashhybrid;

/**
 * This class is a map implementation with a special hashing algorithm,
 * which is:
 * Items are linked each other by coalesced hashing technique. But, instead of 
 * adding the data the end of the array, the data is linked to the next item 
 * which will be calculated by a special hashing formula.
 */
@SuppressWarnings("unchecked")
public class HashTableHybrid<V extends Comparable<V>> implements HashMap<Integer, V>
{
    private static final int INITIAL_CAPACITY = 10;
    private static final double PRIME_NUMBER_CONSTANT = 0.8;
    private Entry<V>[] table;
    private int numKeys;

    private int prevIndex;

    /**
     * This is a constructor that creates a new table with the size of the initial capacity.
     */
    public HashTableHybrid()
    {
        table = new Entry[INITIAL_CAPACITY];
        numKeys = 0;
        prevIndex = -1;
    }

    /**
     * If the key is already in the table, then the value is replaced with the new value and the old
     * value is returned
     * 
     * @param key The key to be inserted into the map.
     * @param value The value to be stored in the map.
     * @return The old value of the key.
     */
    @Override
    public V put(Integer key, V value) 
    {
        V oldValue = null;
        int hash = findHashFromKey(key);
        Entry<V> entry = new Entry<>(key, value, hash);
        if (table[hash] != null)
        {
            oldValue = table[hash].getValue();
        }
        put(entry);
        return oldValue;
    }

    /**
     * If the previous entry is not null, then set the next entry of the previous entry to the
     * current entry.
     * 
     * @param entry The entry to be added to the table.
     * @param hash the hash value of the key
     */
    private void put(Entry<V> entry) 
    {
        if (entry.getHash() > table.length)
        {
            rehash();
            entry.setHash(findHashFromKey(entry.getKey()));
            put(entry);
        }
        else if (table[entry.getHash()] == null)
        {
            table[entry.getHash()] = entry;
            if (prevIndex != -1 && table[prevIndex] != null)
            {
                table[prevIndex].setNext(entry);
            }
            numKeys++;
            if (numKeys >= table.length * PRIME_NUMBER_CONSTANT)
            {
                rehash();
            }
        }
        else
        {
            table[entry.getHash()] = entry;
        }
    }

    /**
     * The function finds the largest prime number that is smaller than the size of the hash table, and
     * then uses that prime number to calculate the hash value of the key.
     * 
     * @param key the key to be hashed
     * @return The hash value of the key.
     */
    private int findHashFromKey(Integer key) 
    {
        int primeNumber = findLargestPrimeNumber();
        int hash1 = key % table.length;
        int hash2 = primeNumber - (key % primeNumber);

        return hashMethod(hash1, hash2, key);
    }

    /**
     * The function takes in the hash values of the key, and the key itself. It then iterates through
     * the table until the a place for the key is found or the end of the table is reached
     * 
     * @param hash1 The first hash value.
     * @param hash2 The second hash value.
     * @param key The key to be hashed.
     * @return The hash value calculated with a the formula.
     */
    private int hashMethod(int hash1, int hash2, Integer key) 
    {
        int i = 1;
        int hash = (hash1 + (i * hash2)) % table.length;
        prevIndex = -1;
        boolean isPrevSettable = true;
        while (table[hash] != null && table[hash].getKey().compareTo(key) != 0)
        {
            if (isPrevSettable)
                prevIndex = hash;
            i++;
            hash = (hash1 + (i * hash2)) % table.length;

            if (table[hash] != null && table[hash].getNext() == null)
            {
                isPrevSettable = false;
            }
        }
        return hash;
    }
    
    /**
     * It finds the largest prime number that is less than 80% of the size of the hash table
     * 
     * @return The largest prime number that is less than 80% of the table length.
     */
    private int findLargestPrimeNumber() 
    {
        int number = (int) (PRIME_NUMBER_CONSTANT * table.length);
        
        if (number % 2 == 0)
            number--;

        while (!isPrimeNumber(number))
        {
            number -= 2;
        }

        return number;
    }

    /**
     * It rehashes the table.
     */
    private void rehash() 
    {
        Entry<V>[] oldTable = table;
        int size = findSmallestPrimeNumber();
        table = new Entry[size];

        for (int i = 0; i < oldTable.length; i++)
        {
            if (oldTable[i] != null)
            {
                oldTable[i].setHash(findHashFromKey(oldTable[i].getKey()));
                oldTable[i].setNext(null);
                put(oldTable[i]);
            }
        }
    }

    /**
     * It finds the smallest prime number that is greater than twice the size of the table
     * 
     * @return The smallest prime number that is greater than the size of the table.
     */
    private int findSmallestPrimeNumber() 
    {
        int number = table.length * 2 + 1;

        if (number % 2 == 0)
            number--;

        while (!isPrimeNumber(number))
        {
            number += 2;
        }
        return number;
    }

    /**
     * If the number is divisible by any number between 3 and the square root of the number, then it is
     * not a prime number.
     * 
     * @param number The number to be checked for primality.
     * @return The method is returning a boolean value.
     */
    private static boolean isPrimeNumber(int number) 
    {
        for (int i = 3; i <= Math.sqrt(number); i += 2)
        {
            if (number % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    
    /**
     * The function then iterates through the links at the first hash
     * value until it finds the key.
     * 
     * @param key The key to be searched for.
     * @return The value of the key.
     */
    @Override
    public V get(Integer key) 
    {
        int primeNumber = findLargestPrimeNumber();

        int hash1 = key % table.length;
        int hash2 = primeNumber - (key % primeNumber);
        int hash = (hash1 + (1 * hash2)) % table.length;

        Entry<V> current = table[hash];
        while (current != null && current.getKey().compareTo(key) != 0)
        {
            current = current.getNext();
        }
        if (current != null)
            return current.getValue();
        return null;
    }

    /**
     * It removes the value associated with the key.
     * 
     * @param key The key of the element to remove.
     * @return deleted element if found, null otherwise.
     */
    @Override
    public V remove(Integer key) 
    {
        int primeNumber = findLargestPrimeNumber();
        int hash1 = key % table.length;
        int hash2 = primeNumber - (key % primeNumber);
        int hash = (hash1 + (1 * hash2)) % table.length;

        if (table[hash] == null)
            return null;

        V value;
        
        if (table[hash].getKey().compareTo(key) == 0 && table[hash].getNext() == null)
        {
            value = table[hash].getValue();
            table[hash] = null;
        }
        else if (table[hash].getKey().compareTo(key) == 0 && table[hash].getNext() != null)
        {
            // Go to the last element and set it to the as first element.
            Entry<V> current = table[hash];
            value = current.getValue();

            while (current.getNext().getNext() != null)
            {
                current = current.getNext();
            }
            table[hash].setValue(current.getNext().getValue());
            table[hash].setKey(current.getNext().getKey());
            
            int removedHash = current.getNext().getHash();
            current.setNext(null);
            table[removedHash] = null;
        }
        else
        {
            Entry<V> current = table[hash];
            while (current.getNext() != null && current.getNext().getKey().compareTo(key) != 0)
            {
                current = current.getNext();
            }
            if (current.getNext() == null)
                return null;
            
            value = current.getNext().getValue();
            int removedHash = current.getNext().getHash();
            current.setNext(current.getNext().getNext());
            table[removedHash] = null;
        }
        numKeys--;
        return value;
    }

    /**
     * Returns true if the size of the list is 0, false otherwise.
     * 
     * @return The size of the list.
     */
    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    /**
     * Returns the number of keys in the map.
     * 
     * @return The number of keys in the map.
     */
    @Override
    public int size() {
        return numKeys;
    }

    /**
     * The function iterates through the hash table and prints out the index of each element, the
     * element itself, and a new line
     * 
     * @return A string representation of the hash table.
     */
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
                sb.append("\n\n");
            }
            else
            {
                sb.append("null\n\n");
            }
        }
        return sb.toString();
    }

    /**
     * A class that represents a entry of a map.
     * It contains a key and a value, hash number and a reference to the next entry.
     * 
     * @param <V> The type of data in the map. 
     */
    private static class Entry<V> implements Comparable<Entry<V>>
    {
        // Declaring a variable called key of type K.
        private Integer key;
        // Declaring a variable called key of type V.
        private V value;
        // Used to store the hash value of the key.
        private int hash;
        // A pointer to the next entry.
        private Entry<V> next;

        // A constructor for the Entry class.
        public Entry(Integer key, V value, int hash)
        {
            this.key = key;
            this.value = value;
            this.hash = hash;
            next = null;
        }

        /**
         * @return the key
         */
        public Integer getKey() {
            return key;
        }

        /**
         * This function sets the key of the node to the key passed in as a parameter
         * 
         * @param key The key of the item to be changed.
         */
        public void setKey(Integer key) {
            this.key = key;
        }

        /**
         * It returns the value of the entry
         * 
         * @return The value of the key-value pair.
         */
        public V getValue() {
            return value;
        }

        /**
         * It sets the value of the current entry to the value passed in as a parameter, and returns the
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
         * This function returns the hash value of the object.
         * 
         * @return The hash value of the object.
         */
        public int getHash() {
            return hash;
        }

        /**
         * This function sets the hash value of the object to the value of the parameter.
         * 
         * @param hash The hash of the block
         */
        public void setHash(int hash) {
            this.hash = hash;
        }

        /**
         * This function returns the next entry of a bucket
         * 
         * @return The next entry of a bucket
         */
        public Entry<V> getNext() {
            return next;
        }
        
        /**
         * This function sets the next entry of a bucket
         * 
         * @param next The next entry of a bucket
         */
        public void setNext(Entry<V> next) {
            this.next = next;
        }

        /**
         * The compareTo() method compares the value of the current object with the value of the object
         * passed as an argument
         * 
         * @param o The object to be compared.
         * @return The value of the entry.
         */
        @Override
        public int compareTo(Entry<V> o) {
            return key.compareTo(o.key);
        }

        /**
         * The toString() method returns a string representation of the object
         * 
         * @return The key and value of the entry as a String.
         */
        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append(key + "=" + value);
            Entry<V> local = next;
            
            while (local != null)
            {
                sb.append(" --> " + local.getKey() + "=" + local.getValue());
                local = local.getNext();
            }
            return sb.toString();
        }
    }
}
