import dayofyearset.DayOfYearSet.DayOfYear;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;

import dayofyearset.*;

/**
 * This class has a main class to test the DayOfYearSet and DayOfYearSet.DayOfYear classes.
 */
public class DayOfYearSetTest 
{
    /**
     * To use OUT instead of System.OUT
     */
    private static final PrintStream OUT = System.out;

    /**
     * Takes a DayOfYearSet reference and prints in into a file.
     * @param dayOfYearSet  DayOfYearSet reference
     */
    public static void writeSetToFile(DayOfYearSet dayOfYearSet, String setName)
    {
        try 
        {
            FileWriter myWriter = new FileWriter("sets_" + setName + ".txt");
            myWriter.write(dayOfYearSet.toString());
            myWriter.close();
        } catch (IOException e) 
        {
            System.out.println("File could not opened!");
            e.printStackTrace();
        }
    }
    /**
     * Includes tests for the DayOfYearSet and DayOfYearSet.DayOfYear classes
     * @param argv conventional.
     */
    public static void main(String[] argv)
    {
        // ------ Testing the Program ------
        
        OUT.println("\n---- Welcome to DayOfYearTest Program ---- \n");
        OUT.println("This test includes:");
        OUT.println("1- Constructors");
        OUT.println("2- All set class methods (isequal, union, intersection, complemenet).");
        OUT.println("3- add, remove, set, get methods.");
        OUT.println("4- Static variable.");
        OUT.println("5- DeMorgan Rule.\n\n");

        OUT.println("Test started... \n");

        OUT.println("TOTAL DayOfYear objects before the test starts: " + DayOfYearSet.getTotalDates() + "\n");

        // ----------- Creating object by constructors -----------
        // set1
        DayOfYearSet set1 = new DayOfYearSet(18, 5);
        set1.add(new DayOfYear(12, 7));
        set1.add(17, 5);
        set1.add(new DayOfYear(25, 8));
        OUT.println("--> set1 created with parametrized constructor and then 3 element added to it.\n");

        OUT.println("Element of set1: ");
        OUT.println("---------------- ");
        OUT.println(set1.toString() + "\n");

        // set2
        DayOfYearSet set2 = set1.clone();
        set2.remove(18, 5);
        set2.add(8, 5);
        OUT.println("--> set2 created as clone of set1.");
        OUT.println("(A deep copy has been performed.)\n");
        OUT.println("18 May removed from set2");
        OUT.println("5 May added from set2\n");

        OUT.println("Element of set1: ");
        OUT.println("---------------- ");
        OUT.println(set1.toString() + "\n");

        OUT.println("Element of set2: ");
        OUT.println("---------------- ");
        OUT.println(set2.toString() + "\n");

        // set3
        DayOfYearSet set3 = new DayOfYearSet(set2);
        OUT.println("--> set3 created with copy constructor, parameter set2.\n");
        
        OUT.println("Element of set2: ");
        OUT.println("---------------- ");
        OUT.println(set2.toString() + "\n");

        OUT.println("Element of set3: ");
        OUT.println("---------------- ");
        OUT.println(set3.toString() + "\n");

        if(set2.equals(set3))
            OUT.println("--> set2 and set3 is equal.\n");
        else
            OUT.println("--> set2 and set3 is not equal.\n");

        set3.add(23, 8);
        set3.add(23, 4);
        set3.setDate(0, 29, 10);
        
        OUT.println("23 August and 23 April added to the set3.");
        OUT.println("0th index of set (12 July) changed with 29 October.\n");
        OUT.println("Current 0th index: ");
        OUT.println("Day: " + set3.getDay(0) + " Month: " + set3.getMonth(0) + "\n");

        OUT.println("Element of set2: ");
        OUT.println("---------------- ");
        OUT.println(set2.toString() + "\n");

        OUT.println("Element of set3: ");
        OUT.println("---------------- ");
        OUT.println(set3.toString() + "\n");

        if(set2.equals(set3))
            OUT.println("--> set2 and set3 is equal.\n");
        else
            OUT.println("--> set2 and set3 is not equal.\n");
        
        
        DayOfYearSet holidays2022 = new DayOfYearSet(1, 1);
        holidays2022.add(23, 4);
        holidays2022.add(1, 5);
        holidays2022.add(2, 5);
        holidays2022.add(3, 5);
        holidays2022.add(4, 5);
        holidays2022.add(19, 5);
        holidays2022.add(9, 7);
        holidays2022.add(10, 7);
        holidays2022.add(11, 7);
        holidays2022.add(12, 7);
        holidays2022.add(30, 8);
        holidays2022.add(29, 10);
        
        OUT.println("--> holidays2022 created with parameter (1, 1) and other holidays added to the set.\n");
        OUT.println("Element of holidays2022: ");
        OUT.println("---------------- ");
        OUT.println(holidays2022.toString() + "\n");
        
        OUT.println("TOTAL DayOfYear objects after creating DayOfYearSet's: " + DayOfYearSet.getTotalDates() + "\n");
        
        
        // ----------- Set Operators -----------
        
        OUT.println("Testing continues with set operations (union, difference, intersection, complemenet)... \n");

        DayOfYearSet unionRef;
        DayOfYearSet differenceRef;
        DayOfYearSet intersectionRef;
        DayOfYearSet complementRef;

        // Union
        unionRef = set1.union(set2);

        OUT.println("--> Union of set1 and set2");
        OUT.println("--------------------------\n");

        OUT.println("Element of set1: ");
        OUT.println("---------------- ");
        OUT.println(set1.toString() + "\n");

        OUT.println("Element of set2: ");
        OUT.println("---------------- ");
        OUT.println(set2.toString() + "\n");

        OUT.println("Element of set1 union set2: ");
        OUT.println("---------------- ");
        OUT.println(unionRef.toString() + "\n");
        
        // Union
        unionRef = holidays2022.union(set3);

        OUT.println("--> Union of holidays2022 and set3");
        OUT.println("--------------------------\n");

        OUT.println("Element of holidays2022: ");
        OUT.println("---------------- ");
        OUT.println(holidays2022.toString() + "\n");

        OUT.println("Element of set3: ");
        OUT.println("---------------- ");
        OUT.println(set3.toString() + "\n");

        OUT.println("Element of holidays2022 union set3: ");
        OUT.println("---------------- ");
        OUT.println(unionRef.toString() + "\n");
        // -----------------------------------------------------

        // Difference
        differenceRef = set3.difference(set2);

        OUT.println("--> Difference of set3 and set2");
        OUT.println("--------------------------\n");

        OUT.println("Element of set3: ");
        OUT.println("---------------- ");
        OUT.println(set3.toString() + "\n");

        OUT.println("Element of set2: ");
        OUT.println("---------------- ");
        OUT.println(set2.toString() + "\n");

        OUT.println("Element of set3 difference set2: ");
        OUT.println("---------------- ");
        OUT.println(differenceRef.toString() + "\n");
        
        // Difference
        differenceRef = holidays2022.difference(set1);

        OUT.println("--> Differenece of holidays2022 and set1");
        OUT.println("--------------------------\n");

        OUT.println("Element of holidays2022: ");
        OUT.println("---------------- ");
        OUT.println(holidays2022.toString() + "\n");

        OUT.println("Element of set1: ");
        OUT.println("---------------- ");
        OUT.println(set1.toString() + "\n");

        OUT.println("Element of holidays2022 difference set1: ");
        OUT.println("---------------- ");
        OUT.println(differenceRef.toString() + "\n");
        // -----------------------------------------------------

        // Intersection
        intersectionRef = set3.intersection(set2);

        OUT.println("--> Intersection of set3 and set2");
        OUT.println("--------------------------\n");

        OUT.println("Element of set3: ");
        OUT.println("---------------- ");
        OUT.println(set3.toString() + "\n");

        OUT.println("Element of set2: ");
        OUT.println("---------------- ");
        OUT.println(set2.toString() + "\n");

        OUT.println("Element of set3 intersection set2: ");
        OUT.println("---------------- ");
        OUT.println(intersectionRef.toString() + "\n");
        
        // Intersection
        intersectionRef = holidays2022.intersection(set1);

        OUT.println("--> Intersection of holidays2022 and set1");
        OUT.println("--------------------------\n");

        OUT.println("Element of holidays2022: ");
        OUT.println("---------------- ");
        OUT.println(holidays2022.toString() + "\n");

        OUT.println("Element of set1: ");
        OUT.println("---------------- ");
        OUT.println(set1.toString() + "\n");

        OUT.println("Element of holidays2022 intersection set1: ");
        OUT.println("---------------- ");
        OUT.println(intersectionRef.toString() + "\n");
        // -----------------------------------------------------
        
        // Complement
        complementRef = set3.complement();

        OUT.println("--> Complement of set3");
        OUT.println("--------------------------\n");

        OUT.println("Element of set3: ");
        OUT.println("---------------- ");
        OUT.println(set3.toString() + "\n");

        OUT.println("Element of set3 complement: ");
        OUT.println("---------------- ");
        OUT.println(complementRef.toString() + "\n");
        
        // Complement
        complementRef = holidays2022.complement();

        OUT.println("--> Complement of holidays2022");
        OUT.println("--------------------------\n");

        OUT.println("Element of holidays2022: ");
        OUT.println("---------------- ");
        OUT.println(holidays2022.toString() + "\n");


        OUT.println("Element of holidays2022 complement: ");
        OUT.println("---------------- ");
        OUT.println(complementRef.toString() + "\n");
        // -----------------------------------------------------

        OUT.println("TOTAL DayOfYear objects after the set implementations done(complement, union...): " + DayOfYearSet.getTotalDates() + "\n");

        // --- Info ---
        if (((holidays2022.complement()).complement()).equals(holidays2022))
        {
            OUT.println("--> The complement of a set's complement is equal to itself.");
            OUT.println("((set.complement()).complement()).equals(set) is always true!\n");
        }
        else
            OUT.println("Test is failed.(You will never see here!) \n");
        // -----------------------------------------------------

        // --- DeMorgan Rule ---

        OUT.println("Testing continues with DeMorgan Rule... \n");
        OUT.println("(DeMorgan says: !(s1 + s2) == !s1 ^ !s2) \n");

        if(((set1.union(set2)).complement()).equals((set1.complement()).intersection(set2.complement())))
            OUT.println("set1 and set2 passed the DeMorgan test. \n");
        else
            OUT.println("Test is failed.(You will never see here!) \n");
        
        if(((set3.union(set2)).complement()).equals((set3.complement()).intersection(set2.complement())))
            OUT.println("set3 and set2 passed the DeMorgan test. \n");
        else
            OUT.println("Test is failed.(You will never see here!) \n");

        if(((set3.union(holidays2022)).complement()).equals((set3.complement()).intersection(holidays2022.complement())))
            OUT.println("set3 and holidays2022 passed the DeMorgan test. \n");
        else
            OUT.println("Test is failed.(You will never see here!) \n");
        
        if(((set1.union(holidays2022)).complement()).equals((set1.complement()).intersection(holidays2022.complement())))
            OUT.println("set1 and holidays2022 passed the DeMorgan test. \n");
        else
            OUT.println("Test is failed.(You will never see here!) \n");
        

        OUT.println("--> Let's continue the test with the sets whose complement, \nintersection, union, difference we have taken before. \n");

        if(((complementRef.union(intersectionRef)).complement()).equals((complementRef.complement()).intersection(intersectionRef.complement())))
            OUT.println("complementRef and intersectionRef passed the DeMorgan test. \n");
        else
            OUT.println("Test is failed.(You will never see here!) \n");
        
        if(((unionRef.union(differenceRef)).complement()).equals((unionRef.complement()).intersection(differenceRef.complement())))
            OUT.println("unionRef and differenceRef passed the DeMorgan test. \n");
        else
            OUT.println("Test is failed.(You will never see here!) \n");
        
        
        // --- Write Some Sets into the files ---
        writeSetToFile(set1, "set1");
        writeSetToFile(unionRef, "unionRef");
        writeSetToFile(holidays2022, "holidays2022");
        OUT.println("--> set1, unionRef, holidays2022 writed to the files. \n");

        OUT.println("TOTAL DayOfYear objects created after all tests are done: " + DayOfYearSet.getTotalDates() + "\n");

        OUT.println("---- TEST COMPLETED SUCCESSFULLY. HAVE A GOOD DAY! ---- \n");
    }   
}
