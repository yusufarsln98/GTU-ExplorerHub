package srcarrayimproved.lib.buildings;


/**
 * This class is used to represent a building
 */
public class Building
{
    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * The default constructor. It is used to create a new object of the class.
     */
    public Building() 
    {
        // Default values
        length = 0;
        height = 0;
        positionLeft = 0;
        setPositionRight();
        counter++;
        setId();
        
    }
    // --- Parametrized Constructor ---
    /**
     * Parametrized constructor. It is used to create a new object of the class.
     * 
     * @param length length of building
     * @param height height of building
     */
    public Building(int positionLeft, int length, int height) 
    {
        setLength(length);
        setHeight(height);
        this.positionLeft = positionLeft;
        setPositionRight();
        counter++;
        setId();
    }
    // --- Copy Constructor --- 
    /**
     * Copy constructor. It is used to create a new object of the class from another object of this class.
     * 
     * @param other Building object that wants to copy
     */
    public Building(Building other)
    {
        // Copy the elements
        setLength(other.length);
        setHeight(other.height);
        this.positionLeft = other.positionLeft;
        setPositionRight();
        setId(other.getId());
    }
    // ----- Constructors -----

    // ----- Fields -----
    protected int length;
    protected int height;
    private static int counter;
    private String id;
    private int positionLeft;
    private int positionRight;

    // ----- Setter and Getters -----
    // --- Length ---
    
    /**
     * Returns the length of the building.
     * 
     * @return The length of the building.
     */
    public int getLength() 
    { 
        return length; 
    }
    /**
     * It sets the length of the building.
     * 
     * If the building is instance of House or Office
     *      check if lower limit is 4 and upper limit is 40
     * 
     * If the building is instance of Market
     *      check if lower limit is 4 and upper limit is 80
     * 
     * If the building is instance of Playground
     *      check if lower limit is 4 and upper limit is 120
     * 
     * @param length The length of the building.
     */
    public void setLength(int length) 
    {
        // Set logical limits due to scale
        int lowerLimit = 0;
        int upperLimit = 0;

        if (this instanceof House || this instanceof Office)
        {
            lowerLimit = 4;
            upperLimit = 40;            
        }
        else if (this instanceof Market)
        {
            lowerLimit = 4;
            upperLimit = 80;
        }
        else if (this instanceof Playground)
        {
            lowerLimit = 4;
            upperLimit = 120;
        }

        if (length < lowerLimit || length > upperLimit)
            throw new IllegalArgumentException("Illegal length for the building! [" + lowerLimit + "," + upperLimit + "]");

        this.length = length; 
    }

    // --- Height ---
    /**
     * Returns the height of the building
     * 
     * @return The height of the building.
     */
    public int getHeight() 
    { 
        return height; 
    }
    /**
     * Set the height of the building.
     * If height is not even then throw an exception
     * due to scaling problem, height should be even.
     * 
     * If the building is instance of House or Office
     *      check if lower limit is 4 and upper limit is 60
     * 
     * If the building is instance of Market
     *      check if lower limit is 4 and upper limit is 12
     * 
     * If the building is instance of Playground
     *      check if limit is 2
     * 
     * @param height The height of the building.
     */
    public void setHeight(int height)
    {
        // Set logical limits due to scale
        if (height % 2 != 0)
        {
            throw new IllegalArgumentException("Illegal height for the building. Height should be 'even'!");
        }

        int lowerLimit = 0;
        int upperLimit = 0;

        if (this instanceof House || this instanceof Office)
        {
            lowerLimit = 4;
            upperLimit = 60;            
        }
        else if (this instanceof Market)
        {
            lowerLimit = 4;
            upperLimit = 12;
        }
        else if (this instanceof Playground)
        {
            lowerLimit = 2;
            upperLimit = 2;
        }

        if (height < lowerLimit || height > upperLimit)
            throw new IllegalArgumentException("Illegal height for the building! [" + lowerLimit + "," + upperLimit + "]");

        this.height = height; 
    }

    // --- Building Id ---
    /**
     * It sets the id of the building.
     */
    private void setId() 
    {
        StringBuilder bul = new StringBuilder("Building " + counter + "/" + this.getClass().getSimpleName());
        id = bul.toString();
    }
    private void setId(String otherId) 
    {
        id = otherId;
    }
    /**
     * Returns the id of building
     * 
     * @return The id of the building.
     */
    public String getId() 
    { 
        return id; 
    }

    public int getPositionLeft() 
    {
        return positionLeft;
    }
    public void setPositionLeft(int positionLeft) 
    {
        this.positionLeft = positionLeft;
    }
    public void setPositionRight()
    {
        if (length == 0)
            positionRight = 0;
        else 
            positionRight = this.positionLeft + this.length - 1; 
    }
    public int getPositionRight()
    {
        return positionRight;
    }
    // ----- Setter and Getters -----

    // ----- Overrides -----
    /**
     * Compares two building and return true if they are equal.
     * 
     * @return boolean
     */
    @Override
    public boolean equals(Object obj) 
    {
        // Compare if same objects, null and classes
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        
        // Down cast the object and compare elements
        Building other = (Building) obj;
        if (id != other.getId())
            return false;
        if (height != other.height)
            return false;
        if (length != other.length)
            return false;
        if (positionLeft != other.positionLeft)
            return false;

        return true;
    }

    /**
     * Create a illustration of building and adds properties of building to the string.
     * 
     * @return String
     */
    @Override
    public String toString() 
    {
        // Create information sheet about buildings.
        // Draw the illustration of building.
        // Display informations
        StringBuilder bul = new StringBuilder();

        bul.append(this.getId() + "\n\n");
        for (int i = 0; i < (height / 2); i++)
        {
            for (int k = 0; k < 5; k++)
                bul.append(' ');
            
            for (int j = 0; j < length; j++)
            {   
                if (i == 0)
                {
                    if (j == 0)
                        bul.append('┌');
                    else if (j == length - 1)
                        bul.append('┐');
                    else
                        bul.append("─");
                }
                else if (j == 0 || j == length - 1) 
                    bul.append("│");
                else
                    bul.append(" ");
            }
            bul.append("\n");
        }
        for (int j = 0; j < length + 10; j++)
            bul.append("▀");
        
        bul.append("\n\n");
        bul.append("Length: " + length + "\n" + "Height: " + height + "\n" + "Position: " + positionLeft);
        return bul.toString();
    }

    /**
     * Create hashCode based on building.
     * @return hashCode
     */
    @Override
    public int hashCode() 
    {
        // Create hashCode from id
        return getId().hashCode();
    }
    
    /**
     * It is used to create a new object of the class.
     * 
     * @return Building object
     */
    @Override
    public Building clone() throws CloneNotSupportedException 
    {
        // Invoke copy constructor
        return new Building(this);
    }
    // ----- Overrides -----
}
