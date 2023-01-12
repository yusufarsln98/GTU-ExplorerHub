package srcldlinkedlist.lib;

import srcldlinkedlist.lib.buildings.*;
import java.util.Scanner;

/**
 * Street class which keeps list of buildings in two sides of street.
 */
public class StreetLD
{
    // Define logical limits according to the pixels on the screen
    public static final int LOWERLIMIT = 20;
    public static final int UPPERLIMIT = 150;

    // ----- Constructors -----
    // --- Default Constructor ---
    /**
     * Creating a street object with a length of 20.
     */
    public StreetLD() 
    {
        length = LOWERLIMIT;
    }
    
    // --- Parametrized Constructor ---
    /**
     * Creating a new street object with a in parameter.
     * @param length Lenght of street
     */
    public StreetLD(int length) 
    {
        setLength(length);
    }

    // --- Parametrized Constructor ---
    /**
     * // Creating a street with two rows of buildings.
     * @param row1 First row
     * @param row2 Second row
     * @param length Length of street
     */
    public StreetLD(LDLinkedList<Building> row1, LDLinkedList<Building> row2, int length) 
    {
        this.row1 = row1;
        this.row2 = row2;
        setLength(length);
    }

    // --- Copy Constructor --- 
    /**
     * Creating a copy of the street object.
     * @param other Object wants to clone.
     * @throws CloneNotSupportedException
     */
    protected StreetLD(StreetLD other) throws CloneNotSupportedException 
    {
        this.length = other.length;

        for (var building : other.row1)
        {
            this.addBuilding(row1, building.clone());
        }
        for (var building : other.row2)
        {
            this.addBuilding(row2, building.clone());
        }
    }
    // ----- Constructors -----


    // ----- Fields -----
    private int length;
    private LDLinkedList<Building> row1 = new LDLinkedList<>();
    private LDLinkedList<Building> row2 = new LDLinkedList<>();
    private int[] heightsInRange = new int[LOWERLIMIT];
    
    
    // ----- Setter and Getters -----
    // --- Length of street ---
    
    /**
     * Returns the length of the street
     * 
     * @return The length of the street.
     */
    public int getLength() 
    { 
        return length;
    }
    
    /** 
     * Setter of length
     * 
     * Street length should be between [20, 150]
     * @param length
     */
    protected void setLength(int length) 
    {
        // Street length should be between 20 and 150.
        // If not, throw exception.
        if (length < LOWERLIMIT || length > UPPERLIMIT)
            throw new IllegalArgumentException("Illegal length for the street! [" + LOWERLIMIT + "," + UPPERLIMIT + "]");
        
        this.length = length;
    }

    
    // --- Row 1 ---
    /**
     * Setter for first row reference
     * 
     * @param row1 Takes it and assign it to the row1
     */
    public void setRow1(LDLinkedList<Building> row1) 
    { 
        this.row1 = row1; 
    }
    
    /** 
     * Returns the reference of first row
     * 
     * @return LDLinkedList<Building>
     */
    public LDLinkedList<Building> getRow1() 
    { 
        return row1; 
    }

    
    /** 
     * Setter for second row reference
     * 
     * @param row2 Takes it and assign it to the row2
     */
    // --- Row 2 ---
    public void setRow2(LDLinkedList<Building> row2) 
    { 
        this.row2 = row2; 
    }
    
    /** 
     * Returns the reference of second row
     * 
     * @return LDLinkedList<Building>
     */
    public LDLinkedList<Building> getRow2() 
    { 
        return row2; 
    }
    
    /**
     * Create silhouette and return it
     * 
     * @return String
     */
    public String getSilhouette() 
    {
        // Set current heights 
        setHeightsInRange();
    
        // Find max height
        int maxHeight = findMaxHeight();
        
        StringBuilder bul = new StringBuilder();
        bul.append("Skyline Silhouette of the Street\n\n\n");
    
        // Iterate two nested loop then print silhouette to the screen
        for (int i = maxHeight; i >= 0; i--)
        {
            for (int j = 0; j < this.length; j++)
            {
                // Draw the street with '#'
                if (i == 0) bul.append("#");
                else if (heightsInRange[j] == 0) bul.append(" ");
                else
                {
                    // Draw to roof with '_'
                    if (i == heightsInRange[j]) bul.append("_");
                    else
                    {
                        // Check for the first and last column to avoid out of border
                        if ((heightsInRange[j] == heightsInRange.length - 1 || j == 0) && heightsInRange[j] > i) 
                            bul.append("|");
                        else if (!(heightsInRange[j] == heightsInRange.length - 1 || j == 0))
                        {
                            // Print other walls to the screen
                            if (heightsInRange[j] > i)
                            {
                                if (heightsInRange[j] >= heightsInRange[j + 1] && heightsInRange[j + 1] <= i)
                                    bul.append("|");
                                else if (heightsInRange[j] >= heightsInRange[j - 1] && heightsInRange[j - 1] <= i)
                                    bul.append("|");
                                else 
                                    bul.append(" ");
                            }
                            else 
                                bul.append(" ");
                        }
                        else bul.append(" ");
                    }
                }
            }
            bul.append("\n");
        }

        // Add numbers to the below street
        for (int i = 0; i <= this.length; i++)
        {
            if (i < 10)
            {
                if (i % 5 == 0)
                    bul.append(i);
                else
                    bul.append(" ");
            }
            else if (i < 100)
            {
                if (i % 5 == 0)
                    bul.append(i);
                else if (i % 5 != 1)
                    bul.append(" ");
            }
            else if (i <= UPPERLIMIT)
            {
                if (i % 5 == 0)
                    bul.append(i);
                else if (i % 5 != 1 && i % 5 != 2)
                    bul.append(" ");
            }
            if (i == this.length)
            {
                bul.append(" (meter)");
            }
        }
        bul.append("\n");

        return bul.toString();
    }
    
    // --- Helper for silhouette ---
    /**
     * Setter for 'heightsInRange' field
     * Creates an array, then fills it with top border of buildings
     * It's a helper of setSilhouette
     */
    private void setHeightsInRange()
    {
        // Find all largest heights in the row and store them into 1D int array
        // Since character size is 1x for width and 2x for height then devide heights with 2

        // Add heights in row1 first
        heightsInRange = new int[this.length];
        int pleft;
        int pright;
        for (var building : row1)
        {
            pleft = building.getPositionLeft();
            pright = building.getPositionRight();
            for (int i = pleft; i <= pright; i++)
            {
                heightsInRange[i] = building.getHeight() / 2;
            }
        }

        // Add heights in row2, if height is larger then the previous one then replace it
        for (var building : row2)
        {
            pleft = building.getPositionLeft();
            pright = building.getPositionRight();
            for (int i = pleft; i <= pright; i++)
            {
                if (building.getHeight() / 2 > heightsInRange[i])
                {
                    heightsInRange[i] = building.getHeight() / 2;
                }
            }
        }
    }
    
    /**
     * Find the longest building in the street
     * It's a helper of setSilhouette
     * @return maximum height
     */
    private int findMaxHeight() 
    {
        // Find max height in the street and return the largest height
        int maxHeight = 0;

        for (int i = 0; i < heightsInRange.length; i++)
        {
            if (heightsInRange[i] > maxHeight)
                maxHeight = heightsInRange[i];
        }
        return maxHeight;
    }
    // --- Helper for silhouette ---
    // ----- Setter and Getters -----
    

    //  ----- Methods -----
   
    /**
     * It adds a building to the street.
     * 
     * @param row the row of buildings that the new building will be added to.
     * @param newBuilding The new building to be added to the street.
     * @return true.
     */
    public boolean addBuilding(LDLinkedList<Building> row, Building newBuilding)
    {
        // Check for the exceptions
        checkAddBuildingValidity(row, newBuilding);
        row.add(newBuilding);
        return true;
    }   
    
    /**
     * Remove a building from a street
     * 
     * @param row the row of buildings that the building is being removed from
     * @param building the building to be removed
     * @return true.
     */
    public boolean removeBuilding(LDLinkedList<Building> row, Building otherBuilding)
    {
        // Check for the exceptions
        checkRemoveBuildingValidity(row, otherBuilding);
        row.remove(otherBuilding);
        return true;
    }

  
    // --- Helpers for add remove ---

    /**
     * It checks if the building is exist in the row.
     * 
     * @param row the row that the building is in
     * @param building The building on the street that you want to remove.
     */
    private void checkRemoveBuildingValidity(LDLinkedList<Building> row, Building building) 
    {
        if (this.length == 0)
        {
            throw new IllegalStateException("Set length of the street first! [" + LOWERLIMIT + "," + UPPERLIMIT + "]");
        }
        else if (row.isEmpty())
        {
            throw new IllegalStateException("There is no element in the " + (row == row1 ? "row1!":"row2!"));
        }
        else if (!isBuildingExist(row, building))
        {
            throw new IllegalArgumentException("This building cannot remove, it does not exist in the row! - " + building.getId());
        }
    }
    
    /**
     * Check if the new building is valid to be added to the street
     * 
     * @param row the row of buildings that the new building will be added to.
     * @param newBuilding The new building that you want to add to the street.
     */
    private void checkAddBuildingValidity(LDLinkedList<Building> row, Building newBuilding) 
    {
        if (this.length == 0)
        {
            throw new IllegalStateException("Set length of the street first!");
        }
        else if (newBuilding.getLength() == 0)
        {
            throw new IllegalStateException("Set length of building first! - " + newBuilding.getId());
        }
        else if (isBuildingExist(this.row1, newBuilding) || isBuildingExist(this.row2, newBuilding))
        {
            throw new IllegalArgumentException("This building already added, make a clone or create another building! - " + newBuilding.getId());
        }
        else if (!row.isEmpty())
        {   
            // Position of new building want be settled.
            int p1 = newBuilding.getPositionLeft();
            int p2 = newBuilding.getPositionRight();
        
            for (var building : row)
            {
                if (!((p1 < building.getPositionLeft() && p2 < building.getPositionLeft()) ||
                      (p1 > building.getPositionRight() && p2 > building.getPositionRight())))
                {
                    throw new IllegalArgumentException("Invalid start position for new building! - " + newBuilding.getId());
                }
            }
            if (p2 > this.length)
                throw new IllegalArgumentException("Invalid length for new building, check borders! - " + newBuilding.getId());
        }
        else
        {
            if (newBuilding.getLength() > this.length)
                throw new IllegalArgumentException("Invalid length for new building, check borders! - " + newBuilding.getId());
            else if (newBuilding.getPositionRight() > this.length)
                throw new IllegalArgumentException("Invalid start position for new building! - " + newBuilding.getId());

        }
    }

    /**
     * Given a row of buildings, return true if the building already exists in the row
     * 
     * @param row the array of buildings on the street
     * @param otherBuilding The new building that we want to add to the street.
     * @return The method returns a boolean value.
     */
    public boolean isBuildingExist(LDLinkedList<Building> row, Building otherBuilding)
    {
        if (row.contains(otherBuilding))
        {
            return true;
        }
        return false;
    }
    // --- Helpers for add remove ---
    //  ----- Methods -----

    // ----- Modes -----
    // --- Editing Mode ---
    /**
     * It allows the user to add and remove buildings from the street.
     */
    public void editingMode()
    {
        System.out.println("--------------------------------");
        System.out.println("--------- EDITING MODE ---------");
        System.out.println("--------------------------------");
        System.out.println("\n");

        // Take the instruction from user
        Scanner scanner = new Scanner(System.in);
        int instruction;
        int index;
        Building building;
        
        while (true)
        {
            System.out.println
            ("\nEditing Mode - Menu\n\n" 
            +"1- Add building to first row\n"
            +"2- Add building to second row\n"
            +"3- Remove building from first row\n"
            +"4- Remove building from second row\n"
            +"5- Silhouette (Demo)\n"
            +"(0 to exit)\n"  
            );
            instruction = scanner.nextInt();
            
            if (instruction == 0)
                break;
            else if (instruction == 1)
            {
                // Take building from the user and insert it to the row
                building = scanBuilding();
                try 
                {
                    addBuilding(row1, building);
                    System.out.println("Building successfully added to first row!");
                } 
                catch (Exception e) 
                {
                    if (e.getMessage() != null)
                        System.out.println(e.getMessage());
                }
            }
            else if (instruction == 2)
            {
                // Take building from the user and insert it to the row
                building = scanBuilding();
                try 
                {
                    addBuilding(row2, building);
                    System.out.println("Building successfully added to second row!");
                } 
                catch (Exception e) 
                {
                    if (e.getMessage() != null)
                        System.out.println(e.getMessage());
                }
            }
            else if (instruction == 3)
            {
                // Remove building
                if (row1.isEmpty())
                {
                    System.out.println("\nThere is no building on the first row!\n");
                }
                else if (row1.size() == 1)
                {
                    removeBuilding(row1, row1.get(0));
                    System.out.println("\nOnly element has been removed!\n");
                }
                else
                {
                    for (int i = 0; i < row1.size(); i++)
                    {
                        System.out.println((i + 1) + "-\n" + row1.get(0) + "\n" + "-------------------" + "\n");
                    }

                    System.out.println("\nSelect building you want to remove!\n");
                    index = scanner.nextInt();
                    scanner.nextLine();
                    if (index > 0 && index <= row1.size())
                    {
                        removeBuilding(row1, row1.get(index - 1));
                        System.out.println("\nBuilding successfully removed!\n");
                    }
                    else
                    {
                        System.out.println("\nInvalid entry!\n");
                    }
                }
            }
            else if (instruction == 4)
            {
                // Remove building
                if (row2.isEmpty())
                {
                    System.out.println("\nThere is no building on the second row!\n");
                }
                else if (row2.size() == 1)
                {
                    removeBuilding(row2, row2.get(0));
                    System.out.println("\nOnly element has been removed!\n");
                }
                else
                {
                    for (int i = 0; i < row2.size(); i++)
                    {
                        System.out.println((i + 1) + "-\n" + row2.get(i) + "\n" + "-------------------" + "\n");
                    }

                    System.out.println("\nSelect building you want to remove!\n");
                    index = scanner.nextInt();
                    scanner.nextLine();
                    if (index > 0 && index <= row2.size())
                    {
                        removeBuilding(row2, row2.get(index - 1));
                        System.out.println("\nBuilding successfully removed!\n");
                    }
                    else
                    {
                        System.out.println("\nInvalid entry!\n");
                    }
                }
            }
            else if (instruction == 5)
            {
                System.out.println("\n\n" + getSilhouette() + "\n");
            }
            else
            {
                System.out.println("Invalid entry! [0, 5]");
            }
        }
    }
    
    // --- Helper for editing mode ---
    /**
     * It scans the building type and take the parameter of the building.
     * 
     * @return Building object
     */
    private Building scanBuilding() 
    {
        Scanner scanner = new Scanner(System.in);
        int instruction;

        // Menu
        while (true)
        {
            // Ask building type to user
            System.out.println
            ("Select the building type you want to add.\n\n" 
            +"1- House\n"
            +"2- Office\n"
            +"3- Market\n"
            +"4- Playground\n"
            +"(0 to exit)\n"  
            );
            instruction = scanner.nextInt();

            if (instruction == 0)
                return null;
            else if (instruction == 1 || instruction == 2 || instruction == 3 || instruction == 4)
                break;
            else
                System.out.println("Invalid entry! [0, 4]");
        }

        // Variables

        House house = null;
        Office office = null;
        Market market = null;
        Playground playground = null;

        int buildingLength;
        int buildingHeight;
        int roomNumber;
        int position;

        String color;
        String business;
        String openingTime;
        String closingTime;
        String owner;

        if (instruction == 1)
        {
            // Take parameter of building
            System.out.println("Enter length [4, 40] meter");
            buildingLength = scanner.nextInt();

            System.out.println("Enter height [4, 60 - even] meter");
            buildingHeight = scanner.nextInt();
            
            System.out.println("Enter room number [>0]");
            roomNumber = scanner.nextInt();
            scanner.nextLine();

            System.out.println("Enter color");
            color = scanner.nextLine();

            System.out.println("Enter owner");
            owner = scanner.nextLine();

            System.out.println("Enter position [>0]");
            position = scanner.nextInt();
            
            // Construct building, check for exceptions
            try 
            {
                house = new House(position, buildingLength, buildingHeight, roomNumber, color, owner);               
            } 
            catch (Exception e) 
            {
                System.out.println(e.getMessage());
            }
            
            return house;
        }
        else if (instruction == 2)
        {
            // Take parameter of building
            System.out.println("Enter length [4, 40] meter");
            buildingLength = scanner.nextInt();

            System.out.println("Enter height [4, 60 - even] meter");
            buildingHeight = scanner.nextInt();
            scanner.nextLine();

            System.out.println("Enter business");
            business = scanner.nextLine();

            System.out.println("Enter owner");
            owner = scanner.nextLine();

            System.out.println("Enter position [>0]");
            position = scanner.nextInt();
            
            // Construct building, check for exceptions
            try 
            {
                office = new Office(position, buildingLength, buildingHeight, business, owner); 
            } 
            catch (Exception e) 
            {
                System.out.println(e.getMessage());
            }
            
            return office;
        }
        else if (instruction == 3)
        {
            // Take parameter of building
            System.out.println("Enter length [4, 80] meter");
            buildingLength = scanner.nextInt();

            System.out.println("Enter height [4, 12 - even] meter");
            buildingHeight = scanner.nextInt();
            scanner.nextLine();

            System.out.println("Enter opening time [hh:mm]");
            openingTime = scanner.nextLine();

            System.out.println("Enter closing time [hh:mm]");
            closingTime = scanner.nextLine();

            System.out.println("Enter owner");
            owner = scanner.nextLine();

            System.out.println("Enter position [>0]");
            position = scanner.nextInt();
            
            // Construct building, check for exceptions
            try 
            {
                market = new Market(position, buildingLength, buildingHeight, openingTime, closingTime, owner); 
            } 
            catch (Exception e) 
            {
                System.out.println(e.getMessage());
            }
            
            return market;
        }
        else if (instruction == 4)
        {
            // Take parameter of building
            System.out.println("Enter length [4, 120] meter");
            buildingLength = scanner.nextInt();

            System.out.println("Enter position [>0]");
            position = scanner.nextInt();
            
            // Construct building, check for exceptions
            try 
            {
                playground = new Playground(position, buildingLength); 
            } 
            catch (Exception e) 
            {
                System.out.println(e.getMessage());
            }
            
            return playground;
        }
        
        return null;
    }
    // --- Helper for editing mode ---

    // --- Viewing Mode ---
    /**
     * This function is used to display the total remaining length of lands, list of buildings, number
     * and ratio of playgrounds, total length of street occupied by the markets, houses or offices, and
     * the silhouette of the city.
     */
    public void viewingMode()
    {
        System.out.println("--------------------------------");
        System.out.println("--------- VIEWING MODE ---------");
        System.out.println("--------------------------------");
        System.out.println("\n");

        // Take the instruction from user
        Scanner scanner = new Scanner(System.in);
        int instruction;

        while (true)
        {
            // Take user request
            System.out.println
            ("\nViewing Mode - Menu\n\n" 
            +"1- Display total remaining length of lands\n"
            +"2- Display list of buildings\n"
            +"3- Display the number and ratio of length of playgrounds\n"
            +"4- Display total length of street occupied by the markets, houses or offices.\n"
            +"5- Display silhouette\n"
            +"(0 to exit)\n"  
            );
            instruction = scanner.nextInt();
            
            if (instruction == 0)
                break;
            else if (instruction == 1)
            {
                System.out.println("Total remaining land (meter): " + findTotalRemainingLand());
            }
            else if (instruction == 2)
            {
                System.out.println(toString());
            }
            else if (instruction == 3)
            {
                System.out.println("Number of playgrounds: " + findNumberOfPlaygrounds() + "\n" +
                                   "Ratio of playgrounds: " + findRatioOfPlaygrounds());    
            }
            else if (instruction == 4)
            {
                System.out.println("Occupied land by markets: " + findTotalOccupiedLandBy("Market") + "\n" +
                                   "Occupied land by houses: " + findTotalOccupiedLandBy("House") + "\n" +
                                   "Occupied land by offices: " + findTotalOccupiedLandBy("Office") + "\n");
            }
            else if (instruction == 5)
            {
                System.out.println("\n\n" + getSilhouette() + "\n");
            }
            else
            {
                System.out.println("Invalid entry! [0, 5]");
            }
        }
    }
    
    // --- Helper for viewing mode ---

    /**
     * Find the total length of all buildings of a certain type
     * 
     * @param className the name of the class you want to find the total number of.
     * @return The total number of occupied lands.
     */
    public int findTotalOccupiedLandBy(String className) 
    {
        // Find total occupied lands from class names
        int result = 0;
        for (var building : row1)
        {
            if (building.getClass().getSimpleName().equals(className))
            {
                result += building.getLength();
            }
        }
        for (var building : row2)
        {
            if (building.getClass().getSimpleName().equals(className))
            {
                result += building.getLength();
            }
        }
        return result;
    }
    
    /**
     * Find the number of playgrounds in the street
     * 
     * @return The number of playgrounds in the street.
     */
    public int findNumberOfPlaygrounds() 
    {
        // Find number of playgrounds in the street
        int playgroundsNumber = 0;
        for (var building : row1)
        {
            if (building instanceof Playground)
            {
                playgroundsNumber++;
            }
        }
        for (var building : row2)
        {
            if (building instanceof Playground)
            {
                playgroundsNumber++;
            }
        }

        return playgroundsNumber;
    }
    
    /**
     * Find the total length of all playgrounds in the city and divide it by the total length of the
     * city.
     * 
     * @return The ratio of playgrounds' length to the total length of the city.
     */
    public double findRatioOfPlaygrounds() 
    {
        // Ratio of playgrounds' length
        double totalPlaygroundsLength = 0.0;

        for (var building : row1)
        {
            if (building instanceof Playground)
            {
                totalPlaygroundsLength += building.getLength();
            }
        }
        for (var building : row2)
        {
            if (building instanceof Playground)
            {
                totalPlaygroundsLength += building.getLength();
            }
        }
        return totalPlaygroundsLength / (2 * this.length);
    }

    
    /**
     * Find the total length of all buildings in the row and subtract it from the total length of the
     * row.
     * 
     * @return The total remaining land.
     */
    public int findTotalRemainingLand() 
    {
        // Find total occupied land and remove it from total land
        int totalLength = 0;
        for (var building : row1)
        {
            totalLength += building.getLength();
        }
        for (var building : row2)
        {
            totalLength += building.getLength();
        }
        return 2 * length - totalLength;
    }
    // --- Helper for viewing mode ---
    // ----- Modes -----

    // ----- Overrides -----
    /**
     * The hashCode method returns a hash code for the object
     * 
     * @return The hash code of the two rows.
     */
    @Override
    public int hashCode() 
    {
        int result = 0;
        for (var building : row1)
        {
            result += building.hashCode();
        }
        for (var building : row2)
        {
            result += building.hashCode();
        }
        return result;
    }

    /**
     * It compares the current object with the other object.
     * 
     * @param obj The object to compare to.
     * @return The boolean value of the equals method.
     */
    @Override
    public boolean equals(Object obj) 
    {
        // Compare priority features
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;

        // Compare current object with other object
        StreetLD other = (StreetLD) obj;
        if (length != other.length)
            return false;
        if (row1.size() != other.row1.size())
            return false;
        if (row2.size() != other.row2.size())
            return false;

        // Check building elements in the rows
        for (var building : row1)
        {
            if (!isBuildingExist(row2, building))
                return false;
        }
        for (var building : row2)
        {
            if (!isBuildingExist(row1, building))
                return false;
        }
        
        return true;
    }
    
    /**
     * Clones the object
     * 
     * @return new object from copy constructor.
     */
    @Override
    public StreetLD clone() throws CloneNotSupportedException 
    {
        return new StreetLD(this);
    }
    
    /**
     * Create a string with the buildings on the first row, second row and the length of the street
     * 
     * @return The toString method is returning a string that contains the information about the
     * street.
     */
    @Override
    public String toString() 
    {
        // Create toString with elements of rows and length.
        StringBuilder bul = new StringBuilder();
        bul.append("List of building on the street\n");
        bul.append("------------------------------\n\n");

        bul.append("Length of street: " + length + "\n\n");

        bul.append("Buildings on first row:\n");
        bul.append("-----------------------\n\n");
        if (!row1.isEmpty())
        {
            for (var building : row1)
            {
                bul.append(building + "\n");
            }
        }
        else
            bul.append("-- there is no building --\n");
        
        bul.append("\nBuildings on second row:\n");
        bul.append("------------------------\n\n");
        if (!row2.isEmpty())
        {
            for (var building : row2)
            {
                bul.append(building + "\n");
            }
        }
        else
            bul.append("-- there is no building --\n");

        
        return bul.toString();
    }
    // ----- Overrides -----
}
