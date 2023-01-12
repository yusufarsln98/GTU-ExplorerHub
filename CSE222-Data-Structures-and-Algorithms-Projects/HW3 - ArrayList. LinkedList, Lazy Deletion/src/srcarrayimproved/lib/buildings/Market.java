package srcarrayimproved.lib.buildings;

/**
 * The market class is a building that has an opening time and a closing time and an owner.
 */
public class Market extends Building
{
    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * This is the default constructor. It is used to create a new object of the class.
     */
    public Market() 
    {
        super();
        openingTime = null;
        closingTime = null;
        owner = null;
    }
    // --- Parametrized Constructor ---
    /**
     * This is parameterized constructor. It creates a new instance of market with the specified parameters.
     * 
     * @param length length of market.
     * @param height height of market.
     * @param openingTime openingTime of market.
     * @param closingTime closingTime of market.
     * @param owner owner of market.
     */
    public Market(int positionleft, int length, int height, String openingTime, String closingTime, String owner) 
    {
        super(positionleft, length, height);
        setOpeningTime(openingTime);
        setClosingTime(closingTime);
        setOwner(owner);
    }
    
    // --- Copy Constructor --
    /**
     * A copy constructor. It is used to create a new object of the class.
     * 
     * @param other the market object that wants to be copied.
     */
    protected Market(Market other)
    {
        super(other);
        setOpeningTime(other.openingTime);
        setClosingTime(other.closingTime);
        setOwner(owner);
    }
    // ----- Constructors -----

    // ----- Fields -----
    private String openingTime;
    private String closingTime;
    protected String owner;
    
    
    // ----- Setter and Getters -----
    // --- Opening time ---
    /**
     * Returns the opening time of the market
     * 
     * @return The openingTime variable is being returned.
     */
    public String getOpeningTime() 
    { 
        return openingTime; 
    }
    /**
     * This function sets the opening time of the market.
     * 
     * @param openingTime the time the user wants to add to the market.
     */
    public void setOpeningTime(String openingTime) 
    {
        // This is an expression that checks if the opening time is in the correct format.
        if(!openingTime.matches("(?:[0-1][0-9]|2[0-4]):[0-5]\\d"))
            throw new IllegalArgumentException("Invalid entry for time! [hh:mm] - " + getId());

        this.openingTime = openingTime; 
    }
    // --- Closing time ---
    /**
     * Returns the closing time of the market
     * 
     * @return The closingTime of market.
     */
    public String getClosingTime() 
    { 
        return closingTime; 
    }
    /**
     * This function sets the closing time of the market
     * 
     * @param closingTime The closing time for the market.
     */
    public void setClosingTime(String closingTime) 
    { 
        // This is an expression that checks if the closing time is in the correct format.
        if(!closingTime.matches("(?:[0-1][0-9]|2[0-4]):[0-5]\\d"))
            throw new IllegalArgumentException("Invalid entry for time[hh:mm]! [hh:mm] - " + getId());
            
        this.closingTime = closingTime; 
    }

    // --- Market owner ---
    /**
     * Returns the owner of the market
     * 
     * @return The owner of the market.
     */
    public String getOwner() 
    { 
        return owner; 
    }
    /**
     * It sets the owner of the market.
     * 
     * @param owner The owner of the market.
     */
    public void setOwner(String owner) 
    { 
        this.owner = owner; 
    }
    // ----- Setter and Getters -----


    // ----- Overrides -----
    /**
     * The equals method compares the closing time, opening time and owner of the market
     * 
     * @param obj the object to compare to
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
        Market other = (Market) obj;

        // Compare closing time, opening time and owner
        if (closingTime == null) 
        {
            if (other.closingTime != null)
                return false;
        } 
        else if (!closingTime.equals(other.closingTime))
            return false;
        
        if (openingTime == null) 
        {
            if (other.openingTime != null)
                return false;
        } 
        else if (!openingTime.equals(other.openingTime))
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
     * This function overrides the toString() method in the superclass
     * 
     * @return The string representation of the object.
     */
    @Override
    public String toString() 
    {
        StringBuilder bul = new StringBuilder();

        bul.append(super.toString() + "\n"
                   + "Owner: " + owner + "\n" + "Opening Time: " + openingTime + "\n\n"
                   + "CLOSING TIME: " + closingTime);
    
        return bul.toString();
    }

    /**
     * Clones the object
     * 
     * @return The clone method returns a new object of the same class as the object that called it.
     */
    @Override
    public Market clone() throws CloneNotSupportedException 
    {
        // Invoke copy constructor
        return new Market(this);
    }
}
