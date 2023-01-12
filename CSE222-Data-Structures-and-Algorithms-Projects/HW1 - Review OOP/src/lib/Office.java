package lib;

/**
 * The Office class is a subclass of the Building class. It has a business field and an owner field.
 */
public class Office extends Building
{
    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * The default constructor. It is used to create an object of the class Office.
     */
    public Office() 
    {
        super();
        business = null;
        owner = null;
    }
    // --- Parametrized Constructor ---
    /**
     * The parametrized constructor. It used to create an object of the class Office with the properties of
     * length, height, business and owner.
     * 
     * @param length length of building
     * @param height height of building
     * @param business job type if office
     * @param owner owner of office
     */
    public Office(int length, int height, String business, String owner) 
    {
        super(length, height);
        setBusiness(business);
        setOwner(owner);
    }
    // --- Copy Constructor ---
    /**
     * A copy constructor. It is used to create an object of the class Office with the properties of
     * length, height, business and owner.
     * @param other the object wants to be copied.
     */
    protected Office(Office other)
    {
        super(other);
        setBusiness(other.business);
        setHeight(other.height);
        setOwner(other.owner);
    }
    // ----- Constructors -----
    
    // ----- Fields -----
    private String business;
    protected String owner;

    
    // ----- Setter and Getters -----
    // --- Jop type ---
    /**
     * It sets the business field of the object to the value of the business parameter.
     * 
     * @param business The name of the business.
     */
    public void setBusiness(String business) 
    { 
        this.business = business; 
    }
    /**
     * It returns the business name.
     * 
     * @return The business field of the Office object.
     */
    public String getBusiness() 
    { 
        return business; 
    }

    // --- Office owner ---
    /**
     * Returns the owner of the office
     * 
     * @return The owner of the office.
     */
    public String getOwner() 
    { 
        return owner; 
    }
    /**
     * It sets the owner of the office.
     * 
     * @param owner The owner of the office wants to be updated.
     */
    public void setOwner(String owner) 
    { 
        this.owner = owner; 
    }

    // ----- Overrides -----
    /**
     * The equals method compares the office field of the current object to the office field of the
     * object passed in as a parameter. 
     * 
     * @param obj The object to compare to.
     * @return The boolean value of the equals method.
     */
    @Override
    public boolean equals(Object obj) 
    {
        // Compare if same objects, null, supers and classes
        if (this == obj)
            return true;
        if (!super.equals(obj))
            return false;
        if (getClass() != obj.getClass())
            return false;

        // Down cast the object
        Office other = (Office) obj;

        // Compare bussines, owner
        if (business == null) 
        {
            if (other.business != null)
                return false;
        } 
        else if (!business.equals(other.business))
            return false;
        
        return true;
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
     * The function returns a string that contains the information from the super class.
     * 
     * @return The toString method is overridden to return a string that contains the owner, business,
     * and the superclass toString method.
     */
    @Override
    public String toString() 
    {
        StringBuilder bul = new StringBuilder();

        bul.append(super.toString() + "\n"
                   + "Owner: " + owner + "\n\n"
                   + "BUSINESS: " + business);

        return bul.toString();
    }

    /**
     * Clone an object by invoking the copy constructor
     * 
     * @return Nothing.
     */
    @Override
    public Office clone() throws CloneNotSupportedException 
    {
        // Invoke copy constructor
        return new Office(this);
    }
}
