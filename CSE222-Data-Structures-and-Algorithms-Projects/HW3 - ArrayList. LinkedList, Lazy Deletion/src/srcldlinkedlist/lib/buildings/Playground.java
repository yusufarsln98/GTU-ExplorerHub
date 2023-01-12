package srcldlinkedlist.lib.buildings;

/**
 * Playground class extends the Building class.
 */
public class Playground extends Building
{
    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * This is the default constructor of the Playground class.
     */
    public Playground() 
    {
        super();
    }
    // --- Parametrized Constructor ---
    /**
     * This is the parametrized constructor of the Playground class.
     * @param length length of the Playground.
     */
    public Playground(int positionleft, int length) 
    {
        super(positionleft, length, 2);
    }
    // ----- Constructors -----
    
    
    // ----- Overrides -----
    /**
     * Returns true if the object is equal to this object
     * 
     * @param obj The object to compare against.
     * @return equals of super class.
     */
    @Override
    public boolean equals(Object obj) 
    {
        return super.equals(obj);
    }
    
    /**
     * Returns a hash code value for the object
     * 
     * @return The hashCode of the superclass.
     */
    @Override
    public int hashCode() 
    {
        return super.hashCode();
    }

    /**
     * It overrides the toString() method in the Object class.
     * 
     * @return The string representation of the object.
     */
    @Override
    public String toString() 
    {
        return super.toString();
    }

    /**
     * Clone the object and return the clone.
     * 
     * @return The playground object that is being cloned.
     */
    @Override
    public Playground clone() throws CloneNotSupportedException 
    {
        // Calling the clone() method of the super class.
        return (Playground) super.clone();
    }
    // ----- Overrides -----
}
