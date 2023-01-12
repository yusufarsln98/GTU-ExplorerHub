package srcldlinkedlist;

import java.util.ListIterator;
import java.util.Scanner;

import srcldlinkedlist.lib.*;
import srcldlinkedlist.lib.buildings.*;

/**
 * This class is used to demonstrate the StreetLD class
 */
public class Driver 
{
    private Driver() {}
    
    /**
     * This function is used to test the LDLinkedList class
     */
    public static void driverLDLinkedList() 
    {
        System.out.println("\n====== LDLinkedList driver ======\n");

        // Create a new LDLinkedList
        /* Echo */ System.out.println("1[ECHO]--- Create a new LDLinkedList with String generic.\n");
        LDLinkedList<String> ldLinkedList = new LDLinkedList<>();
        System.out.println(" --> ldLinkedList: " + ldLinkedList + "\n");        

        ldLinkedList.add("Data1");
        /* Echo */ System.out.println("\n2[ECHO]--- Data1 added to ldLinkedList.\n");
        System.out.println(" --> ldLinkedList: " + ldLinkedList + "\n");        
        

        /* Echo */ System.out.println("\n3[ECHO]--- Add more Datas to the ldLinkedList.\n");
        ldLinkedList.add("Data2");
        ldLinkedList.add("Data3");
        ldLinkedList.add("Data4");
        ldLinkedList.add("Data5");
        System.out.println(" --> ldLinkedList: " + ldLinkedList + "\n");        


        ldLinkedList.addFirst("Data0");
        /* Echo */ System.out.println("\n4[ECHO]--- Data0 added to the head of the ldLinkedList.\n");
        System.out.println(" --> ldLinkedList: " + ldLinkedList + "\n");        

        ldLinkedList.remove(3);
        /* Echo */ System.out.println("\n5[ECHO]--- Data3 removed from the ldLinkedList.\n");
        System.out.println(" --> ldLinkedList: " + ldLinkedList + "\n");        

        ldLinkedList.add(3, "DataHERE");
        /* Echo */ System.out.println("\n6[ECHO]--- DataHERE added to the 3rd index of ldLinkedList.\n");
        System.out.println(" --> ldLinkedList: " + ldLinkedList + "\n");     

        String data3 = "Data3";
        ldLinkedList.set(3, data3);
        /* Echo */ System.out.println("\n7[ECHO]--- Data3 setted to the 3rd index of ldLinkedList\n");
        System.out.println(" --> ldLinkedList: " + ldLinkedList);  
        System.out.println(" --> Get 3rd index: " + ldLinkedList.get(3)); 
        System.out.println(" --> Size: " + ldLinkedList.size()); 
        System.out.println(" --> Index of Data3: " + ldLinkedList.indexOf(data3) + "\n");
        

        /* Echo */ System.out.println("8[ECHO]--- Create a new ListIterator with String generic from ldLinkedList.\n");
        ListIterator<String> iter = ldLinkedList.listIterator();

        /* Echo */ System.out.println("9[ECHO]--- Print element with enhanced for loop.\n");
        for (var element : ldLinkedList)
        {
            System.out.println(element);
        }
        System.out.println();
        
        
        /* Echo */ System.out.println("10[ECHO]--- Move iterator one step forward.\n");
        System.out.println(" --> Last returned item: " + iter.next());
        System.out.println(" --> Next index: " + iter.nextIndex());
        System.out.println(" --> Previous index: " + iter.previousIndex() + "\n");

        /* Echo */ System.out.println("11[ECHO]--- Add DataHERE through the iterator (before the item that will be return by ListIterator.next()).\n");
        iter.add("DataHERE");
        System.out.println(" --> ldLinkedList: " + ldLinkedList);  


        /* Echo */ System.out.println("12[ECHO]--- Move iterator one step backward.\n");
        System.out.println(" --> Last returned item: " + iter.previous());
        System.out.println(" --> Next index: " + iter.nextIndex());
        System.out.println(" --> Previous index: " + iter.previousIndex() + "\n");


        /* Echo */ System.out.println("13[ECHO]--- Remove DataHERE through the iterator. (remove last item that returned by [in this condition]previous() or next())\n");
        iter.remove();
        System.out.println(" --> ldLinkedList: " + ldLinkedList);  
        System.out.println(" --> Size: " + ldLinkedList.size() + "\n\n"); 
    }

    /**
     * This function is used to test the StreetLD class
     */
    public static void driver()
    {
        System.out.println("\n====== StreetLD class driver (No user interaction) ======\n");

        // Creating a new street with a length of 100.
        /* Echo */ System.out.println("1[ECHO]--- Create new street with length of 80.\n\n");
        StreetLD street = new StreetLD(80);

        // Silhouette of street we already created.
        /* Echo */ System.out.println("2[ECHO]--- Display silhouette of street.\n\n");
        System.out.println(street.getSilhouette() + "\n");

        // Create house1
        House house1 = new House(2, 5, 20, 12, "green", "Barney Stinson");
        /* Echo */ System.out.println("3[ECHO]--- house1 created.\n\n");
        
        /* Echo */ System.out.println("4[ECHO]--- Display house1 properties.\n\n");
        System.out.println(house1 + "\n");

        // Add house1 to the BuildingOnStreet container class and then
        // add it to the first row of street in 2 position.
        street.addBuilding(street.getRow1(), house1);
        /* Echo */ System.out.println("5[ECHO]--- Add house1 to the 1st row of the street in 2 position.\n\n");

        // Create office1
        Office office1 = new Office(12, 5, 20, "News Center", "Robin Scherbatsky");
        /* Echo */ System.out.println("6[ECHO]--- office1 created.\n\n");

        /* Echo */ System.out.println("7[ECHO]--- Display office1 properties.\n\n");
        System.out.println(office1 + "\n");

        // Add office1 to the BuildingOnStreet container class and then
        // add it to the first row of street in 12 position.
        street.addBuilding(street.getRow1(), office1);
        /* Echo */ System.out.println("8[ECHO]--- Add office1 to the 1st row of the street in 12 position.\n\n");

        // Create market1
        Market market1 = new Market(20, 10, 10, "10:00", "21:00", "Lilly Aldrin");
        /* Echo */ System.out.println("9[ECHO]--- market1 created.\n\n");

        /* Echo */ System.out.println("10[ECHO]--- Display market1 properties.\n\n");
        System.out.println(market1 + "\n");

        // Add market1 to the BuildingOnStreet container class and then
        // add it to the first row of street in 20 position.
        street.addBuilding(street.getRow1(), market1);
        /* Echo */ System.out.println("11[ECHO]--- Add market1 to the 1st row of the street in 20 position.\n\n");

        // Create house2
        House house2 = new House(35, 15, 40, 18, "Red", "Marshall Eriksen");
        /* Echo */ System.out.println("12[ECHO]--- house2 created.\n\n");

        /* Echo */ System.out.println("13[ECHO]--- Display house2 properties.\n\n");
        System.out.println(house2 + "\n");

        // Add house2 to the BuildingOnStreet container class and then
        // add it to the first row of street in 35 position.
        street.addBuilding(street.getRow1(),house2);
        /* Echo */ System.out.println("14[ECHO]--- Add house2 to the 1st row of the street in 35 position.\n\n");

        // Create playground1
        Playground playground1 = new Playground(52, 26);
        /* Echo */ System.out.println("15[ECHO]--- playground1 created.\n\n");

        /* Echo */ System.out.println("16[ECHO]--- Display playground1 properties.\n\n");
        System.out.println(playground1 + "\n");

        // Add playground1 to the BuildingOnStreet container class and then
        // add it to the first row of street in 52 position.
        street.addBuilding(street.getRow1(), playground1);
        /* Echo */ System.out.println("17[ECHO]--- Add playground1 to the 1st row of the street in 52 position.\n\n");


        // Silhouette of street after we add building to the first row.
        /* Echo */ System.out.println("18[ECHO]--- Display silhouette of street after add buildings to the first row.\n\n");
        System.out.println(street.getSilhouette() + "\n");

        // Create office2
        Office office2 = new Office(2, 15, 40, "Architectural Office", "Ted Mosby");
        /* Echo */ System.out.println("19[ECHO]--- office2 created.\n\n");

        /* Echo */ System.out.println("20[ECHO]--- Display office2 properties.\n\n");
        System.out.println(office2 + "\n");

        // Add office2 to the BuildingOnStreet container class and then
        // add it to the second row of street in 2 position.
        street.addBuilding(street.getRow2(), office2);
        /* Echo */ System.out.println("21[ECHO]--- Add office2 to the 2nd row of the street in 2 position.\n\n");

        // Create house3
        House house3 = new House(17, 10, 50, 8, "Lilac", "Tracy McConnell");
        /* Echo */ System.out.println("22[ECHO]--- house3 created.\n\n");

        /* Echo */ System.out.println("23[ECHO]--- Display house3 properties.\n\n");
        System.out.println(house3 + "\n");

        // Add house3 to the BuildingOnStreet container class and then
        // add it to the second row of street in 17 position.
        street.addBuilding(street.getRow2(), house3);
        /* Echo */ System.out.println("24[ECHO]--- Add house3 to the 2nd row of the street in 17 position.\n\n");

        // Create office3
        Office office3 = new Office(28, 15, 20, "Taxi Driver", "Ranjit");
        /* Echo */ System.out.println("25[ECHO]--- office3 created.\n\n");

        /* Echo */ System.out.println("26[ECHO]--- Display office3 properties.\n\n");
        System.out.println(office3 + "\n");

        // Add office3 to the BuildingOnStreet container class and then
        // add it to the second row of street in 28 position.
        street.addBuilding(street.getRow2(), office3);
        /* Echo */ System.out.println("27[ECHO]--- Add office3 to the 2nd row of the street in 28 position.\n\n");

        // Create market2
        Market market2 = new Market(45, 25, 12, "14:00", "02:00", "Maclaren's Irish Pub");
        /* Echo */ System.out.println("28[ECHO]--- market2 created.\n\n");

        /* Echo */ System.out.println("29[ECHO]--- Display market2 properties.\n\n");
        System.out.println(market2 + "\n");

        // Add market2 to the BuildingOnStreet container class and then
        // add it to the second row of street in 45 position.
        street.addBuilding(street.getRow2(), market2);
        /* Echo */ System.out.println("30[ECHO]--- Add market2 to the 2nd row of the street in 45 position.\n\n");

        // Silhouette of street after we add building to the first row.
        /* Echo */ System.out.println("31[ECHO]--- Display silhouette of street after add buildings to the second row.\n\n");
        System.out.println(street.getSilhouette() + "\n");


        // List of buildings on the street
        /* Echo */ System.out.println("32[ECHO]--- Display list of buildings on the street.\n\n");
        System.out.println(street + "\n");

        
        // Remove first building from the second row.
        Building ref = street.getRow2().get(0);
        street.removeBuilding(street.getRow2(), ref);
        /* Echo */ System.out.println("33[ECHO]--- Remove first building in second row.\n\n");

        // Try to remove same building again.
        try 
        {
            /* Echo */ System.out.println("34[ECHO]--- Try to remove same building twice.");
            street.removeBuilding(street.getRow2(), ref);    
        } 
        catch (Exception e) 
        {
            System.out.println(e.getMessage() + "\n\n");
        }

        // Silhouette of street after we add building to the first row.
        /* Echo */ System.out.println("35[ECHO]--- Display silhouette of street after removing a building from the second row.\n\n");
        System.out.println(street.getSilhouette() + "\n");

        // Print first building in first row
        /* Echo */ System.out.println("36[ECHO]--- Display first building in first row: \n");
        System.out.println(street.getRow1().get(0) + "\n\n");

        // Test clone method of a building.
        Building buildingReference;
        try 
        {
            // Clone first building in first row.
            /* Echo */ System.out.println("37[ECHO]--- Make a clone of first building in first row.\n\n");
            buildingReference = street.getRow1().get(0).clone();
            
            // Print cloned building
            /* Echo */ System.out.println("38[ECHO]--- Display clone of first building in first row: \n\n");
            System.out.println(buildingReference + "\n");
            
            // Test equality of cloned and original building
            /* Echo */ System.out.println("39[ECHO]--- Compare clone and original building:");
            if (buildingReference.equals(street.getRow1().get(0)))
            {
                System.out.println("They are equal!" + "\n");
                System.out.println("Hash code of original: " + street.getRow1().get(0).hashCode());
                System.out.println("Hash code of clone: " + buildingReference.hashCode() + "\n\n");
            }
        } 
        catch (CloneNotSupportedException e) 
        {
            e.printStackTrace();
        }

        // Print viewing mode properties to the screen finally.
        /* Echo */ System.out.println("40[ECHO]--- Display analytics of the street.\n");
        
        System.out.println("Total remaining land (meter): " + street.findTotalRemainingLand());
        System.out.println("Number of playgrounds: " + street.findNumberOfPlaygrounds() + "\n" +
                                   "Ratio of playgrounds: " + street.findRatioOfPlaygrounds());  
        System.out.println("Occupied land by markets: " + street.findTotalOccupiedLandBy("Market") + "\n" +
                           "Occupied land by houses: " + street.findTotalOccupiedLandBy("House") + "\n" +
                           "Occupied land by offices: " + street.findTotalOccupiedLandBy("Office") + "\n");
    }

    /**
     * Ask a valid number for the length of the street, and then create a street object with that
     * length. Then, until the user terminates the program, ask which mode that he/she wants to use. If
     * the mode is 1, then enter editing mode, and if the mode is 2, then enter viewing mode.
     */
    public static void userInteraction() 
    {
        System.out.println("\n====== StreetLD Demonstration (User interaction) ======\n");

        Scanner scanner = new Scanner(System.in);
        int streetLength;

        // Ask a valid number for the length
        while (true)
        {
            // Ask length of street.
            System.out.println("Enter street length [20, 150]");
            streetLength = scanner.nextInt();
            scanner.nextLine();
            if (streetLength >= 20 && streetLength <= 150)
                break;
            else
                System.out.println("Invalid street length: " + streetLength + "\n");
        }
        
        StreetLD street = new StreetLD(streetLength);
        int mode;

        // Until user terminates the program, ask which mode that he/she wants to use.
        while (true)
        {
            System.out.println("\nEnter which mode do you want to use:");
            System.out.println("1- Editing mode");
            System.out.println("2- Viewing mode");
            System.out.println("(0 to exit)");
            mode = scanner.nextInt();
            scanner.nextLine();
            if (mode == 0)
                break;
            else if (mode == 1)
                street.editingMode();
            else if (mode == 2)
                street.viewingMode();
            else
                System.out.println("Invalid mode: " + mode + "\n");
        }
    }
}
