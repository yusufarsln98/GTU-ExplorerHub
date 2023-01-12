/*
   GEBZE TECHNICAL UNIVERSITY
   Object Orianted Programing - CSE241
   Homework 6
   Writing your own vector, set, array classes with iterators. 
   Yusuf Arslan

   main.cpp
*/

#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <string>
#include <algorithm>    // std::find, std::for_each and std::sort
#include <memory>       
#include <cstddef>
#include <iterator> 

// Insert header files
#include "gtuvector.h"
#include "gtuarray.h"
#include "gtuset.h"

// Using namespaces
using YusufArslanGTU_Containers::GTUVector;
using YusufArslanGTU_Containers::GTUArray;
using YusufArslanGTU_Containers::GTUSet;
using YusufArslanGTU_Containers::Iterator;

using std::cout;
using std::endl;
using std::string;
using std::find;
using std::for_each;
using std::sort;


// To display for each.

void test_print_str(string val)
{
   cout << val << endl;
}

void test_print_int(int val)
{
   cout << val << endl;
}

void test_print_chr(char val)
{
   cout << val << endl;
}


// ------------------ TESTS ------------------

void vector_demo()
{
   cout << "__________Vector Demo__________" << endl << endl;
   

   GTUVector<string> v1, v2(3);
   cout << "--> 2 GTUVector<string> has been created. (1 presized)" << endl << endl;
   
   
   v1.push_back("Chandler");
   v1.push_back("Monica");
   v1.push_back("Phoebe");
   v1.push_back("Joey");
   v1.push_back("Rachel");
   v1.push_back("Ross");
   cout << "--> 6 item pushed back to 1st vector." << endl << endl; 
   

   cout << "Items of 1st vector. (display with range based loop)" << endl;
   cout << "---------------------------------------" << endl;
   for (auto i : v1)
      cout << i << endl;
   cout << endl << endl;
   

   v2[0] = "Micheal";
   v2[1] = "Dwight";
   v2[2] = "Jim";
   cout << "--> 3 item assigned to index of 2nd vector. (vector[0] = item)" << endl << endl;
   

   cout << "Items of 2nd vector. (display with range based loop)" << endl;
   cout << "---------------------------------------" << endl;
   for (auto i : v2)
      cout << i << endl;
   cout << endl << endl;
   
   
   v2.pop_back();
   cout << "--> Last element of 2nd vector popped." << endl << endl;
   

   v2.push_back("Pam");
   v2.push_back("Andy");
   cout << "--> 2 other element pushed back to the 2nd vector." << endl << endl;
   

   cout << "Final items of 2nd vector. (display with range based loop)" << endl;
   cout << "---------------------------------------" << endl;
   for (auto i : v2)
      cout << i << endl;
   cout << endl << endl;
   

   GTUVector<string> nv1(move(v1));
   GTUVector<string> nv2 = v2;
   cout << "--> 2 new GTUVector<string> has been created. " << endl ;
   cout << "1st vector moved to New Vector 1. (Move Constructor)" << endl;
   cout << "2nd vector assigned to the New Vector 2. (Coppy Assigment)" << endl << endl;
   if(v1.empty())
      cout << "1st vector current size: " << v1.size() << endl << endl;
   

   nv1.erase(nv1.cbegin() + 1);
   cout << "---> 2nd element of New Vector 1 erased." << endl;
   cout << "Items of New Vector 1. (display with range based loop)" << endl;
   cout << "---------------------------------------" << endl;
   for (auto i : nv1)
      cout << i << endl;
   cout << endl << endl;
   

   v2 = move(nv2);
   cout << "--> Items of New Vector 2 moved to old Vector 2. (move assigment)" << endl;
   if(nv2.empty())
      cout << "New Vector 2 current size: " << v1.size() << endl << endl;
   


   cout << "Current items of old Vector 2. (normal loop with iterator incrementing)" << endl;
   cout << "-------------------------------------------------------------------" << endl;
   GTUVector<string>::GTUIterator itr = v2.begin();
   for (; itr != v2.end(); itr++)
      cout << *itr << endl;
   cout << endl << endl;
   

   itr = v2.end() - 1;
   *itr = "Meredith";
   cout << "Changing last element accesing by dereferencing iterator. (*itr)" << endl << endl;
   

   v2.at(2) = "Andy";
   cout << "Accessing and modifying element by at() function." << endl << endl;
   

   auto found = find(nv1.begin(), nv1.end(), "Chandler");
   if (found != nv1.end())
      cout << "--> Chandler is found in New Array 1." << endl << endl;
   else
      cout << "Could not find." << endl << endl;
   

   cout << "Element of Vector 2" << endl;
   cout << "-------------------" << endl;
   for_each(v2.begin(), v2.end(), test_print_str);
   

   sort(nv1.begin(), nv1.end());
   cout << "New Vector 1 sorted." << endl << endl;
   

   cout << "Final states of vectors: " << endl;
   cout << "New Vector 1: " << endl;
   cout << "---------------" << endl;
   for (auto i : nv1)
      cout << i << endl;
   cout << endl << endl;

   cout << "Old Vector 2: " << endl;
   cout << "---------------" << endl;
   for (auto i : v2)
      cout << i << endl;
   cout << endl << endl;
   

   v2.clear();
   nv1.clear();
   cout << "Last two vector cleared." << endl;
   if (v2.empty() && nv1.empty() && v1.empty() && nv2.empty())
   {
      cout << "All vectors are empty!" << endl; 
      cout << "Vector demo is done!" << endl;
   }
   
}


void array_demo()
{
   cout << endl << endl << "__________Array Demo__________" << endl << endl;
   
   
   GTUArray<int, 5> a1;
   cout << "--> An integer array object (a1) size 5 has been created." << endl << endl;
   

   a1.fill(2022);
   cout << "--> a1 filled with 2022." << endl;
   cout << "a1's elements (range based loop)" << endl;
   cout << "--------------------------------" << endl;
   for (auto i : a1)
      cout << i << endl;
   cout << endl << endl;
   

   GTUArray<int, 5>::GTUIterator itr = a1.begin();

   a1[0] = 1923;
   a1.at(2) = 1998;
   *(itr + 4) = 2005;
   a1[3] = 1956;
   cout << "--> Array elements changed by different accessors. (*iterator, at(), [])" << endl << endl;
   

   cout << "a1's current elements (range based loop)" << endl;
   cout << "--------------------------------" << endl;
   for (auto i : a1)
      cout << i << endl;
   cout << endl << endl;
   

   GTUArray<int, 5> a2(move(a1));
   cout << "--> GTUArray a2 has been created and a1 moved to a2. (Move constructor)" << endl << endl;
   

   sort(a2.begin(), a2.end());
   cout << "-->a2 has been sorted." << endl << endl;
   

   cout << "a2's current elements (for_each loop)" << endl;
   cout << "--------------------------------" << endl;
   for_each (a2.begin(), a2.end(), test_print_int);
   cout << endl << endl;
   

   auto found = find(a2.begin(), a2.end(), 1923);
   if (found != a2.end())
      cout << "--> 1923 is found in a2." << endl << endl;
   else
      cout << "Could not find." << endl << endl;
   

   a2.erase(a2.end() - 1);
   cout << "--> Last term of the a2 has been erased. (Instead you'll see a garbage value)" << endl;
   cout << "a2's current elements (for_each loop)" << endl;
   cout << "--------------------------------" << endl;
   for_each (a2.begin(), a2.end(), test_print_int);
   cout << endl << endl;

   a2.clear();
   cout << "a2 has been cleared." << endl << endl;
   

   if(a2.empty() && a1.empty())
   {
      cout << "All GTUArrays are empty!" << endl; 
      cout << "GTUArray demo is done!" << endl;
   }
   

}
void set_demo()
{
   cout << endl << endl << "__________Set Demo__________" << endl << endl;
   
   GTUSet<char> s1;
   cout << "--> An integer set object (s1) been created." << endl << endl;
   

   s1.insert('C');
   s1.insert('S');
   s1.insert('E');
   s1.insert('G');
   s1.insert('T');
   s1.insert('U');
   s1.insert('O');
   s1.insert('O');
   s1.insert('P');
   
   cout << "--> s1 filled by letters 'C' 'S' 'E' 'G' 'T' 'U' 'O' 'P' (does not allow add same element twice)" << endl; 
   cout << "s1's elements (range based loop)" << endl;
   cout << "--------------------------------" << endl;
   for (auto i : s1)
      cout << i << endl;
   cout << endl << endl;

   GTUSet<char> s2(move(s1));
   cout << "--> s1 moved to s2 (move constructor). s1 size: " << s1.size() << endl << endl;
   
   
   GTUSet<char> s3;
   s3.insert('M');
   s3.insert('I');
   s3.insert('T');
   s3.insert('C');
   s3.insert('S');
   s3.insert('E');
   cout << "--> GTUSet<char> s3 has been created." << endl;
   cout << "Letters 'M' 'I' 'T' 'C' 'S' 'E' inserted." << endl << endl;
   
   
   s3.erase('M');
   cout << "-->'M' erased from the s3" << endl << endl;
   // sleep_until(system_clock::now() + milliseconds(700));
   
   cout << "s3's elements (range based loop)" << endl;
   cout << "--------------------------------" << endl;
   for (auto i : s3)
      cout << i << endl;
   cout << endl << endl;
   

   cout << "Intersect of s2 and s3: " << endl;
   cout << "------------------------" << endl;
   for (auto i : s2.Intersect(s3))
      cout << i << endl;
   cout << endl << endl;
   

   GTUSet<char> Uni = s2 + s3;
   cout << "Union of s2 and s3: (display with for_each)" << endl;
   cout << "-------------------------------------------" << endl;
   for_each(Uni.begin(), Uni.end(), test_print_chr);
   cout << endl << endl;
   

   cout << "Complement of s2 with s3:" << endl;
   cout << "-------------------------" << endl;
   for (auto i : s2 - s3)
      cout << i << endl;
   cout << endl << endl;
   


   auto found = find(Uni.begin(), Uni.end(), 'C');
   if (found != Uni.end())
      cout << "--> 'C' is found in Union Set." << endl << endl;
   else
      cout << "Could not find." << endl << endl;
   

   sort(Uni.begin(), Uni.end());
   cout << "--> Union set has been sorted." << endl;
   

   cout << "Union of s2 and s3: (display with for_each)" << endl;
   cout << "-------------------------------------------" << endl;
   for_each(Uni.begin(), Uni.end(), test_print_chr);
   cout << endl << endl;
   

   Uni.clear();
   cout << "Union set has been cleared." << endl;
   
   s2.clear();
   cout << "s2 set has been cleared." << endl;
   
   s3.clear();
   cout << "s3 set has been cleared." << endl << endl;
   

   if(Uni.empty() && s1.empty() && s2.empty() && s3.empty())
   {
      cout << "All GTUSet's are empty!" << endl; 
      cout << "GTUSet demo is done!" << endl;
   }
   
}

int main(void)
{
   cout << endl << "--------- Demo of YusufArslanGTU_Containers classes and iterators ---------" << endl << endl;

   vector_demo();
   array_demo();
   set_demo();

   cout << endl << "-------------- End of the demo --------------" << endl << endl;
   
}
