package lib;

public class FindOccurrence 
{
    /**
     * Private constructor. It is used to prevent the class from being instantiated.
     */
    private FindOccurrence() {}

    // ----------------------------------Question1---------------------------------- //

    /* 
        Q1-
        Write a recursive function to search a given string in another given bigger string. 
        The function should return the index of the ith occurrence of the query string and return -1 
        when the query string doesn’t occur in the big string or the number of occurences is less than i.


        str = "Search query string in a large string, find index of 'i'th occurrence of the string."
        

        case1:
            query = "string"
            i = 5
            return -1, because number of occurrences are less than i.
        
        case2:
            query = "string"
            i = 1
            return 13, number of occurrences are greater and equals to i,
                       therefor, return index of '1'st occurrence.
        
        case3:
            query = "notexist"
            Regardless of the value of i, -1 will be returned as query is not in the large string.
    */
    
    /**
     * Find the index of the any occurrence of a substring in a string.
     * 
     * @param query The string to search for.
     * @param str The string to search in.
     * @param i Occurence number that we are searching for.
     * @return The index of the 'i'th occurrence of the query string in the string.
     */
    public static int findOccurrence(String query, String str, int n)
    {
        if (query == null || str == null)
            throw new IllegalArgumentException("Query or string must not be null!");
        return findOccurrence(query, str, n, 0);
    }

    /**
     * Given a query string and a string, find the occurrence of the query string in the larger string.
     * 
     * @param query the string to search for
     * @param str The string to search
     * @param i The number of occurrences of the query string that we're looking for.
     * @param start The start index of the string to search.
     * @return The index of the first occurrence of the query string in the string.
     */
    private static int findOccurrence(String query, String str, int n, int position)
    {
        if (n < 0 || (str.length() - query.length() + 1) <= position)
        {
            // This is a base case. If the number of occurrences is less than i, or the start index is
            // greater than the length of the string, then we return -1.
            return -1;
        }
        else if (searchQuery(query, str, position, query.length()))
        { 
            // If the query string is the substring, then check number of occurrence is correct.
            if (n == 1)
                return position;
            // Otherwise check for other, instances of substring.
            else
                return findOccurrence(query, str, n - 1, position + 1);
        }
        else
        {
            // Recursively call function and shift larger string one character at a time.
            return findOccurrence(query, str, n, position + 1);
        }
    }

    /**
     * Given a query string and a string, return true if the query string is a substring of the string
     * 
     * @param query The string we're searching for.
     * @param str The string to search.
     * @param index The index of the current character in the string.
     * @param length The length of the query string.
     * @return The boolean value of the searchQuery function.
     */
    private static boolean searchQuery(String query, String str, int index, int length)
    {
        // This is a base case. If the last index of the query string is less than 0, then we return true.
        if (length - 1 < 0)
            return true;
        // Check the character, if they are different return false.
        else if (str.charAt(index + length - 1) != query.charAt(length - 1))
            return false;
        // Recursivly call the method, decrease the length to compare other characters.
        else
            return searchQuery(query, str, index, length - 1);
    }

}