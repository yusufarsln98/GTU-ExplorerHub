package dayofyearset;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * DayOfYearSet Class is a class keeps DayOfYear elements in the field array DayOfYear[] dates.
 * DayOfYear is the inner class of its.
 * It also has methods clone, equals, union, intersection, complement,
 * setter and getters and other helper functions.
 * 
 */
public class DayOfYearSet implements Cloneable
{
    // ------------ Inner Class DayOfYear Implementations ------------
    /**
     * DayOfYear class is a class keeps day and month as fields.
     */
    public static class DayOfYear
    {
        // ------------ Constructors of DayOfYear ------------
        
        /**
         * Default constructors. 
         * Assign 31 December to a DayOfYear object.
         */
        public DayOfYear() {this.day = 31; this.month = 12; }
        
        
        /**
         * Parameterized constructor.
         * Takes two parameter and creates a new DayOfYear object.
         * But here program checks exception. (1 year considered as 365 days.)
         * For example 29 February is an exception. If user enter an exception, the program will be terminated
         * after a warning message.
         * 
         * @param newDay    represent day of a month.
         * @param newMonth  represent month of a year.
         */
        public DayOfYear(int newDay, int newMonth)
        {
            // Check for exception. Be sure year and month is valid.
            try 
            {
                if (newMonth <= 0 || newMonth > 12)
                    throw new IllegalArgumentException("Illegal month entry!");
                else if (newDay <= 0 || newDay > 31)
                    throw new IllegalArgumentException("Illegal day entry!");
                else if (newDay > daysOfMonths[newMonth - 1])
                    throw new IllegalArgumentException("Illegal day entry for the month!");
            } 
            catch (Exception e) 
            {
                System.out.println(e.toString());
                System.out.println("Month: " + newMonth + " Day: " + newDay);
                System.exit(1);
            }

            this.day = newDay; this.month = newMonth; 
        }
        
        /**
         * Copy constructor.
         * Takes a DayOfYear object and invokes parametrized constructor with its day and month element.
         * @param dayOfYear represents object of DayOfYear.
         */
        public DayOfYear(DayOfYear dayOfYear) 
        {
            this(dayOfYear.getDay(), dayOfYear.getMonth()); 
        }
        
        // ------------ Setter and Getter Methods ------------

        /**
         * Takes a parameter and assign it to the day element.
         * @param newDay    represent new day.
         */
        public void setDay(int newDay) {day = newDay; }
        
        /**
         * Takes a parameter and assign it to the month element.
         * @param newMonth  represent new month.
         */
        public void setMonth(int newMonth) {month = newMonth; }
        
        /**
         * There are 2 integer fields (day and month) in DayOfYear class.
         * @return  value of day as an integer.
         */
        public int getDay() {return day; }
        /**
         * There are 2 integer fields (day and month) in DayOfYear class.
         * @return  value of month as an integer.
         */
        public int getMonth() {return month; }

        /**
         * Converts month and day integers to a string.
         * (31, 12) --> 31 December.
         */
        @Override
        public String toString()
        {
            StringBuilder strMonth = new StringBuilder();

            switch (month) {
                case 1:
                    strMonth.append("January");
                    break;
                case 2:
                    strMonth.append("February");
                    break;
                case 3:
                    strMonth.append("March");
                    break;
                case 4:
                    strMonth.append("April");
                    break;
                case 5:
                    strMonth.append("May");
                    break;
                case 6:
                    strMonth.append("Jun");
                    break;
                case 7:
                    strMonth.append("July");
                    break;
                case 8:
                    strMonth.append("August");
                    break;
                case 9:
                    strMonth.append("September");
                    break;
                case 10:
                    strMonth.append("October");
                    break;
                case 11:
                    strMonth.append("November");
                    break;
                case 12:
                    strMonth.append("December");
                    break;
                default:
                    break;
            }
            return day + " " + strMonth.toString();
        }
        
        // ------------ Private Fields ------------

        /**
         * Field int day; keep the day of a month. 
         */
        private int day;

        /**
         * Field int month; keep the month.
         */
        private int month;

        /**
         * Field static final int[] daysOfMonths; keeps the lenght of the months.
         */
        private static final int[] daysOfMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    } // Inner class DayOfYear


    // ------------ Outter Class DayOfYearSet Implementations ------------

    // ------------ Constructors of DayOfYearSet ------------

    /**
     * Default constructor.
     * Assign dates (Array of DayOfYear) to the null.
     */
    public DayOfYearSet(){this.dates = null; }
    
    /**
     * Parametrized constructor.
     * Takes 2 parameter. Creates a new DayOfYear object and
     * add it to the dates.
     * @param newDay    represents day
     * @param newMonth  represents month
     */
    public DayOfYearSet(int newDay, int newMonth){add(new DayOfYear(newDay, newMonth)); }
    
    /**
     * Parametrized constructor.
     * Takes an ArrayList of DayOfYear
     * Then adds elements of ArrayList to the dates and creating new object with it.
     * @param dayOfYears    represents ArrayList of DayOfYear objects.
     */
    public DayOfYearSet(ArrayList<DayOfYear> dayOfYears)
    {
        this();
        if(!dayOfYears.isEmpty())
        {
            for (var dayOfYear : dayOfYears) 
                add(dayOfYear);
        }
    }
    /**
     * Copy constructor.
     * Takes a DayOfYearSet object and copies it.
     * @param rSet  DayOfYearSet object for copying set
     */
    public DayOfYearSet(DayOfYearSet rSet)
    {
        this();
        if (rSet.dates != null)
        {
            for (var date : rSet.dates) 
                add(date);
        }
    }

    // ------------ Methods of DayOfYearSet ------------

    /**
     * clone method (Overrided).
     * Makes a clone of current object.
     * Instead shallow makes a deep copy.
     */
    @Override
    public DayOfYearSet clone()
    {

        DayOfYearSet clone = null;
        try
        {
            clone = (DayOfYearSet) super.clone();
            clone.dates = null;
            
            // Make deep copy of current object. 
            if (this.dates != null)
            {
                for (var date : dates) clone.add(date);
            }
        }
        catch(CloneNotSupportedException cns)
        {
            System.out.println(cns.toString());
            System.exit(1);
        }

        return clone;
    }

    /**
     * size method.
     * @return the size of dates.
     */
    public int size()
    {
        if (dates == null) return 0;
        else               return dates.length;
    }
    
    /**
     * add method.
     * Takes two parameter (newDay, newMonth) and add them
     * into the dates (array of DayOfYear).
     * At the end invoke the increaseDateNum method to increase
     * number of created DayOfYear objects.
     * 
     * @param newDay    represent new day.
     * @param newMonth  represent new month
     */
    public void add(int newDay, int newMonth)
    {
        // Add an element to the set.
        // Check if element is already exist. Duplicate not allowed.
        if(isExist(newDay, newMonth)) return;
        
        DayOfYear[] temp = dates;
        dates = new DayOfYear[size() + 1];
        
        if (temp != null)
            dates = Arrays.copyOf(temp, size());
        
        dates[size() - 1] = new DayOfYear(newDay, newMonth);
        increaseDateNum();
    }

    /**
     * add method by DayOfYear object.
     * Takes DayOfYear object.
     * Calls add(int, int) with this objects fields.
     * @param dayOfYear  Represent the object of DayOfYear class.
     */
    public void add(DayOfYear dayOfYear)
    {
        // Add an element to the set by DayOfYear object parameter.
        add(dayOfYear.getDay(), dayOfYear.getMonth());
    }

    /**
     * remove method.
     * Takes two parameter day and month and 
     * if this day and move is exist in the set,
     * then removes it.
     * Otherwise returns only.
     * At the end invoke the decreaseDateNum method to decrease
     * number of created DayOfYear objects.
     * 
     * @param day       the day to be deleted.
     * @param month     the month to be deleted.
     */
    public void remove(int day, int month)
    {
        // Check if element is already exist. If not then there is nothing to remove.
        if(!isExist(day, month)) return;
        
        if (size() == 1) dates = null;
        else
        {
            DayOfYear[] temp = dates;
            dates = new DayOfYear[size() - 1];
            int j = 0;
            for(int i = 0; i < size() + 1; i++)
            {
                if(!(day == temp[i].getDay() && month == temp[i].getMonth()))
                {
                    dates[j] = temp[i];
                    j++;
                }
            }
        }
        decreaseDateNum();
    }
    
    /**
     * equals method (Overrided).
     * Takes an object and compares with current object.
     * If both sets are equal (regardless of keeping order)
     * returns true.
     * Otherwise returns false.
     */
    @Override
    public boolean equals(Object rSet)
    {
        // If both sets are same then return true.
        // Else create a instance of 
        if (this == rSet) return true;
        else if (rSet instanceof DayOfYearSet temp)
        {
            if (dates == null && temp.dates == null) return true;
            else if (dates != null && temp.dates != null)
            {
                if (dates.length != temp.dates.length) return false;
                
                for (int i = 0; i < dates.length; i++)
                {
                    if(!isExist(temp.dates[i].getDay(), temp.dates[i].getMonth()))
                        return false;
                }
                return true;
            }
        }
        return false;
    }
    
    /**
     * union method.
     * Takes a set of DayOfYear (rSet) - DayOfYearSet object.
     * Creates a ArrayList of DayOfYear.
     * Fills with a combination of DayOfYear objects with current set and rSet.
     * Does not allow the duplication.
     * 
     * @param rSet  DayOfYearSet object keeps the dates.
     * @return      Creates a DayOfYearSet object with that ArrayList
     */
    public DayOfYearSet union(DayOfYearSet rSet)
    {
        ArrayList<DayOfYear> tempList =  new ArrayList<>();
        
        if (dates != null)
        {
            for (var date : dates)
                tempList.add(new DayOfYear(date));
        }
        if (rSet.dates != null)
        {
            for (var date : rSet.dates)
                tempList.add(new DayOfYear(date));
        }
        return new DayOfYearSet(tempList);
    }

    /**
     * difference method.
     * Takes a set of DayOfYear (rSet) - DayOfYearSet object.
     * Creates a ArrayList of DayOfYear.
     * Fills with difference of DayOfYear objects with current set and rSet.
     * 
     * @param rSet    DayOfYearSet object keeps the dates.  
     * @return        Creates a DayOfYearSet object with that ArrayList  
     */
    public DayOfYearSet difference(DayOfYearSet rSet)
    {
        if (dates == null) return new DayOfYearSet();
        else if (rSet.dates == null) return new DayOfYearSet(this);

        ArrayList<DayOfYear> tempList =  new ArrayList<>();
        
        for (DayOfYear date : dates) 
        {
            if(!rSet.isExist(date.getDay(), date.getMonth()))
                tempList.add(new DayOfYear(date));
        }
       
        return new DayOfYearSet(tempList);
    }

    /**
     * intersection method.
     * Takes a set of DayOfYear (rSet) - DayOfYearSet object.
     * Creates a ArrayList of DayOfYear.
     * Fills with intersections of DayOfYear objects with current set and rSet.
     * 
     * @param rSet    DayOfYearSet object keeps the dates.  
     * @return        Creates a DayOfYearSet object with that ArrayList  
     */
    public DayOfYearSet intersection(DayOfYearSet rSet)
    {
        if (dates == null || rSet.dates == null) return new DayOfYearSet();
        
        ArrayList<DayOfYear> tempList =  new ArrayList<>();

        for (DayOfYear date : rSet.dates) 
        {
            if(isExist(date.getDay(), date.getMonth()))
                tempList.add(new DayOfYear(date));
        }
        return new DayOfYearSet(tempList);
    }
    
    /**
     * complemenet method.
     * Creates a ArrayList of DayOfYear.
     * Fills with complemenets of DayOfYear objects in current set.
     
     * @return Creates a DayOfYearSet object with that ArrayList  
     */
    public DayOfYearSet complement()
    {
        ArrayList<DayOfYear> tempList =  new ArrayList<>();
        
        for (int month = 1; month <= DayOfYear.daysOfMonths.length; month++)
        {
            for (int day = 1; day <= DayOfYear.daysOfMonths[month - 1]; day++)
            {
                if(!isExist(day, month))
                {
                    tempList.add(new DayOfYear(day, month));
                }
            }
        }
        return new DayOfYearSet(tempList);
    }

    /**
     * isExist method.
     * Takes to element (day, month).
     * Checks if the element is exist.
     * If it is then returns true.
     * Otherwise return false.
     * @param day       day for comparision.
     * @param month     month for comparision.
     * @return          return the result.
     */
    public boolean isExist(int day, int month)
    {
        if (dates != null)
        {
            for (var date : dates)
            {
                if (day == date.getDay() && month == date.getMonth()) return true;
            }
        }
        return false;
    }
    
    /**
     * toString method (Overrided).
     * Creates a StringBuild object with elements of dates.
     * Then returns that built string.
     */
    @Override
    public String toString()
    {
        if (dates == null)
            return "This set is the empty set.";
        else
        {
            var bld = new StringBuilder();
            int i = 0;
            for (; i < dates.length - 1; i++)
            {
                bld.append(dates[i].toString() + "\n");
            }
            bld.append(dates[i].toString());
            
            return bld.toString();
        }
    }

    // ---- Setter and Getters ----

    /**
     * setDate method.
     * Takes an index and day and month.
     * If index not out of boundry
     * then sets the day and the month.
     * Also checks for if there is already such element.
     * If there is, gives a warning to user and does not add anything.
     * 
     * @param index     index wants to change.
     * @param newDay    new day of the month.
     * @param newMonth  new month of the year.
     */
    public void setDate(int index, int newDay, int newMonth)
    {
        // Check if this day of year exist. If exist then warn the user and return.
        if(isExist(newDay, newMonth)) 
        {
            System.out.println((new DayOfYear(newDay, newMonth)).toString() + " is already exist in your class!");
            System.out.println();
            return;
        }

        // Dates can be null and index can be out of boundry. Check for the exceptions.
        // If every thing okey then set the value with the newDay and newMonth.
        try 
        {
            if (dates == null)
                throw new NullPointerException();
            else if (index < 0 || index >= dates.length)
                throw new IndexOutOfBoundsException();
        } 
        catch (Exception e) 
        {
            System.out.println(e.toString());
            if (dates == null)
                System.out.println("Size of total dates: 0");
            else
            {
                System.out.println("Size of total dates: " + dates.length);
                System.out.printf("(Max index: %d) \n", dates.length);
            }
            System.exit(1);
        }
        
        DayOfYear temp = new DayOfYear(newDay, newMonth);
        dates[index] = temp;
    }
    
    /**
     * getDay method.
     * Takes an index and if the index is valid,
     * returns the day in that index.
     * 
     * @param index     index wants to get its day.
     * @return          return the value of day.
     */
    public int getDay(int index)
    {
        // Check for null and out of bound exception.
        try 
        {
            if (dates == null)
                throw new NullPointerException();
            else if (index < 0 || index >= dates.length)
                throw new IndexOutOfBoundsException();

        } 
        catch (Exception e) 
        {
            System.out.println(e.toString());
            if (dates == null)
                System.out.println("Size of total dates: 0");
            else
            {
                System.out.println("Size of total dates: " + dates.length);
                System.out.printf("(Max index: %d) \n", dates.length);
            }
            System.exit(1);
        }
        
        // If index is valid then get the day.
        return dates[index].getDay();
    }

    /**
     * getMonth method.
     * Takes an index and if the index is valid,
     * returns the month in that index.
     * 
     * @param index     index wants to get its month.
     * @return          return the value of month.
     */
    public int getMonth(int index)
    {
        // Check for null and out of bound exception.
        try 
        {
            if (dates == null)
                throw new NullPointerException();
            else if (index < 0 || index >= dates.length)
                throw new IndexOutOfBoundsException();

        } 
        catch (Exception e) 
        {
            System.out.println(e.toString());
            if (dates == null)
                System.out.println("Size of total dates: 0");
            else
            {
                System.out.println("Size of total dates: " + dates.length);
                System.out.printf("(Max index: %d) \n", dates.length);
            }
            System.exit(1);
        }

        // If index is valid then get the month.
        return dates[index].getMonth();
    }

    /**
     * getTotalDates method.
     * @return the totalDates field.
     */
    public static int getTotalDates() {return totalDates; }

    // ---- Private Methods ----
    /**
     * increaseDateNum method.
     * Increase the totalDates.
     */
    private static void increaseDateNum(){totalDates++; }
    /**
     * decreaseDateNum method.
     * Decrease the totalDates.
     */
    private static void decreaseDateNum(){totalDates--; }

    // ---- Private Fields ----
    
    /**
     * dates is an array of DayOfYear.
     */
    private DayOfYear[] dates;

    /**
     * totalDates keeps the number of alive DayOfYear object.
     */
    private static int totalDates;
}
