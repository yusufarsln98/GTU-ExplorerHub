package lib;

// ----- Container Class -----
public class BuildingOnStreet
{
    public static final int STREETUPPERLIMIT = 150;

    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * This is the default constructor. It is used to create a new object of the class.
     */
    public BuildingOnStreet() 
    {
        building = null;
        positionLeft = 0;
        setPositionRight();
    }
    // --- Parametrized Constructor ---
    /**
     * The parametrized constructor. It is used to create a new object of the class.
     * 
     * @param building Building wants to add to the BuildingOnStreet
     * @param positionLeft Position wants to add to the street
     */
    public BuildingOnStreet(Building building, int positionLeft) 
    {
        setBuilding(building);
        setPositionLeft(positionLeft);
        setPositionRight();
    }
    // --- Copy Constructor --- 
    /**
     * A copy constructor. It is used to create a new object of the class.
     * @param bOnStreet Object want to copy
     * @throws CloneNotSupportedException
     */
    protected BuildingOnStreet(BuildingOnStreet bOnStreet) throws CloneNotSupportedException 
    {
        setBuilding(bOnStreet.building.clone());
        setPositionLeft(bOnStreet.positionLeft);
        setPositionRight();
    }
    // ----- Constructors -----

    // ----- Fields -----
    Building building;
    int positionLeft;
    int positionRight;

    // ----- Setter and Getters -----
    // --- Bulding ---
    /**
     * It sets the building of street to the building passed in.
     * 
     * @param building The building that the player is currently in.
     */
    public void setBuilding(Building building) 
    { 
        this.building = building; 
    }

    /**
     * Returns the building.
     * 
     * @return The building object.
     */
    public Building getBuilding() 
    { 
        return building; 
    }

    // --- Positions ---
    /**
     * Returns the position of the left
     * 
     * @return The positionLeft variable is being returned.
     */
    public int getPositionLeft() 
    { 
        return positionLeft; 
    }

    /**
     * It sets the positionLeft variable to the value passed in.
     * 
     * @param positionLeft The left position of the object.
     */
    public void setPositionLeft(int positionLeft) 
    {
        this.positionLeft = positionLeft; 
    }


    /**
     * Returns the right position of street
     * 
     * @return The right position
     */
    public int getPositionRight() 
    { 
        return positionRight; 
    }

    /**
     * It sets the positionRight variable to the positionLeft variable plus the length of the building
     * minus 1.
     */
    public void setPositionRight() 
    {
        if (building == null)
            positionRight = 0;
        else 
            positionRight = this.positionLeft + this.getLength() - 1; 
    }

    // --- Lenght and Height ---
    /**
     * Returns the length of the building
     * 
     * @return The length of the building.
     */
    public int getLength() 
    { 
        return building.getLength(); 
    }

    /**
     * Set the length of the building
     * 
     * @param length The length of the building.
     */
    protected void setLength(int length) 
    { 
        building.setLength(length); 
    }

    /**
     * Returns the height of the building
     * 
     * @return The height of the building.
     */
    public int getHeight() 
    { 
        return building.getHeight(); 
    }

    /**
     * Set the height of the building
     * 
     * @param height The height of the building.
     */
    protected void setHeight(int height) 
    { 
        building.setHeight(height); 
    }
    // ----- Setter and Getters -----

    // ----- Overrides -----
    /**
     * The hashCode method returns the hash code of the building and the positionLeft
     * 
     * @return The hashcode of the building and the positionLeft.
     */
    @Override
    public int hashCode() 
    {
        return building.hashCode() + positionLeft;
    }

    /**
     * Returns true if the object is equal to this object, false otherwise
     * 
     * @param obj the object to compare to
     * @return The boolean value of the equals method.
     */
    @Override
    public boolean equals(Object obj) 
    {
        // Check basic parametres then the object itself
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        BuildingOnStreet other = (BuildingOnStreet) obj;
        if (building == null) 
        {
            if (other.building != null)
                return false;
        } 
        else if (!building.equals(other.building))
            return false;
        if (positionLeft != other.positionLeft)
            return false;
        return true;
    }
    

    /**
     * Clones the object
     * 
     * @return New BuildingOnStreet object with copy constructor.
     */
    @Override
    public BuildingOnStreet clone() throws CloneNotSupportedException 
    {
        // Invoke copy constructor
        return new BuildingOnStreet(this);
    }
    
    /**
     * This function returns a string representation of the building
     * 
     * @return The string representation of the building and the position of the building.
     */
    @Override
    public String toString() 
    {
        // Add position to building string
        return building.toString() + "\n\n" + "Position: " + positionLeft;
    }
    // ----- Overrides -----
}
    
