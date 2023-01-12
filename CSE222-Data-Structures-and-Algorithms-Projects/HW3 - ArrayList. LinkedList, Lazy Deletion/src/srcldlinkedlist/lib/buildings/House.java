package srcldlinkedlist.lib.buildings;

/**
 * House class is a subclass of Building class
 * It has roomNumber field, color field and owner field.
 */
public class House extends Building
{
    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * Default constructor. Creates House object with default values.
     * It initializes roomNumber with zero, then color and owner with null.
     */
    public House()
    {
        // Default constructor
        super();
        roomNumber = 0;
        color = null;
        owner = null;
    }
    // --- Parametrized Constructor ---
    /**
     * Parametrized constructor. Creat House object with length, height, roomNumber, color and owner.
     * 
     * @param length length of the house object
     * @param height height of the house object
     * @param roomNumber room number of the house object
     * @param color color of the house object
     * @param owner owner of the house object
     */
    public House(int positionLeft, int length, int height, int roomNumber, String color, String owner) 
    {
        super(positionLeft, length, height);
        setRoomNumber(roomNumber);
        setColor(color);
        setOwner(owner);

    }
    // --- Copy Constructor --- 
    /**
     * Copy constructor. Creates House object with another house object.
     * @param other Object that is to be copied.
     */
    protected House(House other)
    {
        super(other);
        setRoomNumber(other.roomNumber);
        setColor(other.color);
        setOwner(other.owner);
    }
    // ----- Constructors -----


    // ----- Fields -----
    private int roomNumber;
    private String color;
    protected String owner;
    
    
    // ----- Setter and Getters -----
    // --- Room number ---
    /**
     * It sets the room number.
     * Throw exception if room number is less then 1.
     * 
     * @param roomNumber roomNumber of the house
     */
    public void setRoomNumber(int roomNumber) 
    { 
        if (roomNumber < 1)
            throw new IllegalArgumentException("Illegal room number! [It should be greater then 0]");
            
        this.roomNumber = roomNumber; 
    }
    /**
     * Returns the room number of house.
     * 
     * @return the room number of house.
     */
    public int getRoomNumber() 
    { 
        return roomNumber; 
    }
    
    
    /** 
     * Sets color of house.
     * 
     * @param color the color of house that wants to set.
     */
    // --- House color ---
    public void setColor(String color) 
    { 
        this.color = color; 
    }
    
    /** 
     * Returns the house color.
     * @return color of the house.
     */
    public String getColor() 
    { 
        return color; 
    }

    
    /** 
     * Returns owner of the house.
     * @return owner of house.
     */
    // --- House owner ---
    public String getOwner() 
    { 
        return owner; 
    }
    
    /** 
     * Set owner of house.
     * @param owner the owner of house
     */
    public void setOwner(String owner) 
    { 
        this.owner = owner; 
    }
    
    
    // ----- Setter and Getters -----
    // ----- Overrides -----
    /** 
     * Return true if both objects are equal.
     * @param obj the house object that is to be compared.
     * @return boolean
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
        House other = (House) obj;
        
        // Compare color, owner and room number
        if (color == null) 
        {
            if (other.color != null)
                return false;
        } 
        else if (!color.equals(other.color))
            return false;
        
        if (roomNumber != other.roomNumber)
            return false;

        return true;
    }
    
    
    /** 
     * Create a hashCode with super class hashCode.
     * @return hashCode
     */
    @Override
    public int hashCode() 
    {
        return super.hashCode();
    }

    
    /** 
     * Create illustration of house based on super class plus room number and color.
     * Emphasizes the owner.
     * @return the illustration.
     */
    @Override
    public String toString() 
    {
        StringBuilder bul = new StringBuilder();

        bul.append(super.toString() + "\n"
                   + "Room Number: " + roomNumber + "\n" + "Color: " + color + "\n\n"
                   + "OWNER: " + owner);

        return bul.toString();
    }
    
    /** 
     * Create clone of house by copy constructor, and return the new instance.
     * @return House that was created.
     * @throws CloneNotSupportedException
     */
    @Override
    public House clone() throws CloneNotSupportedException 
    {
        // Invoke copy constructor
        return new House(this);
    }
}
