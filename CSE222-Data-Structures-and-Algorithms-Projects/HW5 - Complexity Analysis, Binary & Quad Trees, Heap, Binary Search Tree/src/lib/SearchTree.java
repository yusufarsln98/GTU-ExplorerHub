package lib;

/**
 * Interface of search tree classes.
 */
public interface SearchTree<E>
{
    boolean add(E item);
    boolean contains(E item);
    E find(E target);
    E delete(E target);
    boolean remove(E target);
}

