package lib.hashhybrid;


/**
 * HashMap interface
 * @author Jacob / Koffman & Wolfgang
 *
 * @param <K> The type of key value.
 * @param <V> The type of data in the map. Must be a Comparable object.
 */
public interface HashMap<K, V extends Comparable<V>>
{
    /**
     * Returns the value to which the specified key is mapped, or null if this map contains no mapping
     * for the key.
     * 
     * @param key The key of the element to return.
     * @return The value associated with the key.
     */
    V get(K key);

    /**
     * Returns true if this map contains no key-value mappings.
     * 
     * @return True if this map contains no key-value mappings.
     */
    boolean isEmpty();

    /**
     * Associates the specified value with the specified key in this map.
     * If the map previously contained a mapping for the key, the old value is replaced.
     * 
     * @param key The key with which the specified value is to be associated.
     * @param value The value to be associated with the specified key.
     * @return The value previously associated with key, or null if there was no mapping for key.
     */
    V put(K key, V value);

    /**
     * Removes the mapping for a key from this map if it is present.
     * 
     * @param key The key whose mapping is to be removed from the map.
     * @return The previous value associated with key, or null if there was no mapping for key.
     */
    V remove(K key);

    /**
     * Returns the number of key-value mappings in this map.
     * 
     * @return The number of key-value mappings in this map.
     */
    int size();
}