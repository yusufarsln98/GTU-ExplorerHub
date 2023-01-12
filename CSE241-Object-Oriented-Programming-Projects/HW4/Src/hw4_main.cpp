/*
Yusuf Arslan
CSE 241 - OOP
Homework4

Main file
*/

#include "hw4_lib.h"    
using namespace sets;

int main(void)
{
    // ------ Testing The Program ------ 
    // User will be directed through the terminal.

    // Test includes:
    // 1- Constructions
    // 2- All requested overloading operations
    // 3- add and remove functions
    // 4- Static variable
    // 5- DeMorgan rule

    cout << "-- To see the test step by step, press enter until the program is finished. --" << endl << endl;
    getchar();
    
    DayofYearSet set1;
    cout << endl << "--> An empty set created with defaut constructor." << endl << endl;
    cout << set1;
    getchar();
    
    set1.add(23, 8);
    set1.add(18, 5);
    set1.add(12, 7);
    set1.add(14, 12);
    cout << "--> 4 element added to the set. Current set is:" << endl << endl;
    cout << set1;
    getchar();
    
    
    DayofYearSet set2(1, 1);
    cout << endl << "--> A set created with integer constructor parameters." << endl << endl;
    cout << set2;
    getchar();
    
    set2.add(12, 7);
    set2.add(14, 12);
    cout << "--> 2 element added to the set. Current set is:" << endl << endl;
    cout << set2;
    getchar();


    vector <DayofYearSet::DayofYear> DateSet = {{31, 7}, {1,1}, {17, 5}, {18, 5}, {3, 3}, {24, 12}, {18, 10}, {12, 12}};
    DayofYearSet set3(DateSet);
    cout << endl << "--> A set created with vector parameter constructor." << endl << endl;
    cout << set3;
    getchar();

    set3.remove(1, 1);
    set3.add(2, 1);
    cout << "Element January 1 removed from the set." << endl;
    cout << "Element January 2 added to the set." << endl << endl;
    cout << set3;
    getchar();

    DayofYearSet set4 = set1 + set2 + set3;
    cout << "Set created by + overloading operator (s1 + s2 + s3). \n(Same elements did not duplicated.)" << endl << endl;
    cout << set4;
    getchar();
    
    set4.add(31, 12);
    set4.remove(14, 12);
    set4.remove(18, 5);
    cout << "2 element removed then 1 element added to the previous union set." << endl << endl;
    cout << set4;
    getchar();

    cout << "Enter to test overloading functions with set1 and set4." << endl;
    cout << "-------------------------------------------------------" << endl;
    getchar();

    cout << "set1: " << endl << set1 << "set4: " << endl << set4 << endl;

    cout << "____Enter to see set1 + set4" << endl;
    getchar();
    cout << set1 + set4;

    cout << "____Enter to see set1 - set4" << endl;
    getchar();
    cout << set1 - set4;

    cout << "____Enter to see set4 - set1" << endl;
    getchar();
    cout << set4 - set1;
    
    cout << "____Enter to see set4 ^ set1" << endl;
    getchar();
    cout << (set4^set1);
    cout << "____Enter to see set1 ^ set4" << endl;
    cout << "Which suppose to be same with upper one." << endl;
    getchar();
    cout << (set1^set4);

    cout << "____Enter to see !set4. (note: it is a long set!)" << endl;
    getchar();
    cout << !set4;
    
    cout << "___Enter to see implementaion of [] function." << endl;
    getchar();
    
    cout << "set4 before:" << endl << set4;
    cout << "Element going to be change is (MM-DD) " << set4[0].get_month() << '-' << set4[0].get_day() << endl; 
    set4[0].set_month(1);
    set4[0].set_day(10);
    cout << endl << "set4 after:" << endl << set4;
    getchar();

    cout << "--> Total number of created DayofYear objects (static): " << DayofYearSet::get_totalDates() << endl;
    getchar();

    cout << "___Enter to see if my program works by DeMorgan Rule." << endl;
    cout << "Here I send sets to the function with call by value and call by reference." << endl;
    getchar();

    cout << endl << " --> Check set1 and set2" << endl;
    getchar();
    DeMorgan(set1, set2);

    cout << endl << "--> Check set3 and set1" << endl;
    getchar();
    DeMorgan(set3, set1);

    cout << endl << "--> Check set2 and set4" << endl;
    getchar();
    DeMorgan(set2, set4);

    cout << endl << "--> Check set4 + !set2 and !set3" << endl;
    getchar();
    DeMorgan(set4 + !set2, !set3);

    cout << endl << "--> Check set2 - set1 and !set3 + set4" << endl;
    getchar();
    DeMorgan(set2 - set1, !set3 + set4);
    
    cout << endl << "--> Check set1 ^ set2 and set3 + set4" << endl;
    getchar();
    DeMorgan((set1 ^ set2),(set3 + set4));

    cout << endl << "--> Check set4 and !set3" << endl;
    getchar();
    DeMorgan(set4, !set3);

    cout << "All tests are done. Good Bye!" << endl << endl; 

    // -------- End Of The Test --------

    return 0;
}

