/*
Yusuf Arslan
CSE 241 - OOP
Homework4

Library file - Class and function definations
*/
#include "hw4_lib.h"

int DayNumbers[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// Keeps the days in a month (total 365)

namespace sets
{
    int DayofYearSet::totalDates = 0;
    // Static integer keeps total DayofYear object alive.
    
    // ---- Constructors ----
    DayofYearSet::DayofYearSet(void) {/* Intentionally Empty */}
    DayofYearSet::DayofYearSet(int newDay, int newMonth)
    {
        add(newDay, newMonth);
    }
    DayofYearSet::DayofYearSet(const vector<DayofYear> &newSet)
    {
        for (int i = 0; i < newSet.size(); i++)
        {
            add(newSet[i].get_day(), newSet[i].get_month());
        }
    }
    DayofYearSet::DayofYearSet(const DayofYearSet &newObject)
    {
        Size = newObject.size();
        Dates = new DayofYear[size()];
        for (int i = 0; i < size(); i++)
        {
            Dates[i].set_month(newObject[i].get_month());
            Dates[i].set_day(newObject[i].get_day());
            totalDates++;
        }
    }


    // ---- Operator Overloadings ----
    // Return the DayofYear object
    DayofYearSet::DayofYear& DayofYearSet::operator[](int index) const
    {
        if (index >= size() || index < 0)
        {
            cerr << "Invalid index entered. Program Terminated!" << endl << endl;
            exit(1);
        }
        return Dates[index];
    }

    // Stream insertion operator overloading
    ostream& operator<<(ostream &outputStream, const DayofYearSet &mySet)
    {
        cout << "Elements in current set are: " << endl;
        cout << "---------------------------- " << endl;
        for (int i = 0; i < mySet.size(); i++)
        {
            switch (mySet.Dates[i].get_month())
            {
            case 1:
                cout << "January    ";
                break;
            case 2:
                cout << "February   ";
                break;
            case 3:
                cout << "March      ";
                break;
            case 4:
                cout << "April      ";
                break;
            case 5:
                cout << "May        ";
                break;
            case 6:
                cout << "Jun        ";
                break;
            case 7:
                cout << "July       ";
                break;
            case 8:
                cout << "August     ";
                break;
            case 9:
                cout << "Semptember ";
                break;
            case 10:
                cout << "October    ";
                break;
            case 11:
                cout << "November   ";
                break;
            case 12:
                cout << "December   ";
                break;
            }
            cout << mySet.Dates[i].get_day() << endl;
        }
        cout << endl << "Total Days: " << mySet.size() << endl << endl;

        return outputStream;
    }

    // Comparision operators
    // Return true if both sets have same object, even in different orders.
    bool DayofYearSet::operator==(const DayofYearSet &rightSet) const
    {
        if (size() == 0 && rightSet.size() == 0) return true;
        if (size() != rightSet.size()) return false;
        
        bool controller;
        for (int i = 0; i < size(); i++)
        {
            for (int j = 0; j < size(); j++)
            {
                if (Dates[i].get_day() == rightSet.Dates[j].get_day() && 
                    Dates[i].get_month() == rightSet.Dates[j].get_month())
                {
                    controller = true;
                    break;
                }
                else
                    controller = false;
            }
            if (controller == false) return false;

        }
        return true;
    }

    // Return false if both sets not equal
    bool DayofYearSet::operator!=(const DayofYearSet &rightSet) const
    {
        if (size() != rightSet.size())
        {
            return true;
        }

        int controller = 0;
        for (int i = 0; i < size(); i++)
        {
            for (int j = 0; j < size(); j++)
            {
                if (Dates[i].get_day() == rightSet.Dates[j].get_day() && 
                    Dates[i].get_month() == rightSet.Dates[j].get_month())
                {
                    controller++;
                }
            }
        }
        if (controller == size()) return false;

        return true;
    }

    // Adds a new element to the set
    // If there is a request to duplicate the element then terminates the program.
    void DayofYearSet::add(int newDay, int newMonth)
    {
        for (int i = 0; i < size(); i++)
        {
            if(Dates[i].get_day() == newDay && Dates[i].get_month() == newMonth)
            {
                cerr << "Duplicating elements are not allowed. Program Terminated!" << endl;
                exit(1);
            }
        }
        // Vector keeps all elements of the set
        vector<DayofYear> tempDates(size());
        for (int i = 0; i < size(); i++)
        {
            tempDates[i].set_month(Dates[i].get_month());
            tempDates[i].set_day(Dates[i].get_day());
        }

        if (Dates != nullptr) delete [] Dates;

        // Then, reallocation of the DayofYear*
        Size++;
        Dates = new DayofYear[size()];

        // Copies previous elements
        for (int i = 0; i < size() - 1; i++)
        {
            Dates[i].set_month(tempDates[i].get_month());
            Dates[i].set_day(tempDates[i].get_day());
        }
        // Adds last element
        Dates[size() - 1].set_month(newMonth);
        Dates[size() - 1].set_day(newDay);
        totalDates++;

        return;
    }

    // Takes Day and Month then removes it from the set
    // If Date is not exist, then passes it
    void DayofYearSet::remove(int rmDay, int rmMonth)
    {
        DayofYear *newSet = nullptr;
        DayofYear *temp;

        bool isexist = false;

        for (int i = 0, j = 1; i < size(); i++)
        {
            if (!(Dates[i].get_day() == rmDay && Dates[i].get_month() == rmMonth))
            {
                temp = newSet;
                newSet = new DayofYear[j];
                if (temp != nullptr)
                {
                    for (int k = 0; k < j - 1; k++)
                    {
                        newSet[k].set_month(temp[k].get_month());
                        newSet[k].set_day(temp[k].get_day());
                        
                    }
                }
                newSet[j - 1].set_month(Dates[i].get_month());
                newSet[j - 1].set_day(Dates[i].get_day());
                
                if (temp != nullptr) delete [] temp;
                j++;
            }
            else
            {
                isexist = true;
            }
                
        }
        if (isexist == true)
        {
            Size--;
            totalDates--;
        }
        else
        {
            cout << "__There is no such an element." << endl;
            cout << "Nothing has been removed!" << endl << endl;
        }
        if (Dates != nullptr) delete [] Dates;

        Dates = newSet;
    }

    // Union operator
    // Combine two set, if there is duplicated element then takes only one of them.
    // Then return union set
    const DayofYearSet DayofYearSet::operator+(const DayofYearSet &rightSet) const
    {
        vector<DayofYear> temp;
        for (int i = 0; i < size(); i++)
        {
            temp.push_back(DayofYear(Dates[i].get_day(),Dates[i].get_month()));
        }
        
        if (this == &rightSet) return DayofYearSet(temp);

        bool isexist;
        for (int i = 0; i < rightSet.size(); i++)
        {
            for (int j = 0; j < temp.size(); j++)
            {
                if (rightSet.Dates[i].get_day() == temp[j].get_day() && 
                    rightSet.Dates[i].get_month() == temp[j].get_month())
                {
                    isexist = true;
                    break;
                }
                else
                    isexist = false;
            }
            if (isexist == false)
            {
                temp.push_back(DayofYear(rightSet.Dates[i].get_day(), rightSet.Dates[i].get_month()));
            }
        }

        return DayofYearSet(temp);
    }

    // Differ operator
    // Remove element from first one which second one also has it
    // Then return the differ set
    const DayofYearSet DayofYearSet::operator-(const DayofYearSet &rightSet) const
    {
        vector<DayofYear> temp;

        bool isexist;

        for (int i = 0; i < size(); i++)
        {
            for (int j = 0; j < rightSet.size(); j++)
            {
                if (Dates[i].get_day() == rightSet.Dates[j].get_day() && 
                    Dates[i].get_month() == rightSet.Dates[j].get_month())
                {
                    isexist = true;
                    break;
                }
                else
                    isexist = false;
            }
            if (isexist == false)
            {
                temp.push_back(DayofYear(Dates[i].get_day(), Dates[i].get_month()));
            }
        }

        return DayofYearSet(temp);
    }

    // Takes intersection of both set
    // Then, returns the set
    const DayofYearSet DayofYearSet::operator^(const DayofYearSet &rightSet) const
    {
        vector<DayofYear> temp;

        bool isexist;

        for (int i = 0; i < size(); i++)
        {
            for (int j = 0; j < rightSet.size(); j++)
            {
                if (Dates[i].get_day() == rightSet.Dates[j].get_day() && 
                    Dates[i].get_month() == rightSet.Dates[j].get_month())
                {
                    isexist = true;
                    break;
                }
                else
                    isexist = false;
            }
            if (isexist == true)
            {
                temp.push_back(DayofYear(Dates[i].get_day(), Dates[i].get_month()));
            }
        }
        
        return DayofYearSet(temp);
    }

    // Takes complement of the set
    // Then returns the set
    const DayofYearSet DayofYearSet::operator!(void) const
    {
        vector<DayofYear> temp;
        decltype (true) isexist;

        for(auto i = 0; i < 12; i++)
        {
            for(auto j = 1; j <= DayNumbers[i]; j++)
            {
                for(auto k = 0; k < size(); k++)
                {
                    if(Dates[k].get_day() == j && Dates[k].get_month() == i + 1)
                    {
                        isexist = true;
                        break;
                    }
                    else
                    {
                        isexist = false;
                    }
                }
                if (isexist == false)
                {
                    temp.push_back(DayofYear(j, i + 1));
                }
            }
        }
        return DayofYearSet(temp);
    }

    // Assigment operator
    DayofYearSet& DayofYearSet::operator=(const DayofYearSet &rightSet)
    {
        if (size() != rightSet.size())
        {
            if (Dates != nullptr) delete [] Dates;
            totalDates -= size();
            Size = rightSet.size();
            totalDates += size();
            Dates = new DayofYear[size()];
        }
        for(int i = 0; i < size(); i++)
        {
            Dates[i].set_month(rightSet[i].get_month());
            Dates[i].set_day(rightSet[i].get_day());
        }
        return *this;
    }

    // Destructor
    DayofYearSet::~DayofYearSet(void)
    {
        if (Dates != nullptr) delete [] Dates;
    }

    // --- Constructors of inner class ---
    DayofYearSet::DayofYear::DayofYear(void)
                                    : Day(31), Month(12){};

    DayofYearSet::DayofYear::DayofYear(int newDay, int newMonth)
                                    : Day(newDay), Month(newMonth)
    {
        if (Month < 1 || Month > 12 || Day < 1 || Day > DayNumbers[Month - 1])
        {
            cerr << "Invalid Date. Program Terminated!" << endl;
            exit(1);
        }
    }

    // --- Setter and getter of inner class
    void DayofYearSet::DayofYear::set_day(int newDay)
    {
        if (newDay < 1 || newDay > DayNumbers[Month - 1])
        {
            cerr << "Invalid Day. Program Terminated!" << endl;
            exit(1);
        }
        Day = newDay;
        return;
    }

    void DayofYearSet::DayofYear::set_month(int newMonth)
    {
        if (newMonth < 1 || newMonth > 12)
        {
            cerr << "Invalid Month. Program Terminated!" << endl;
            exit(1);
        }
        Month = newMonth;
        return;
    }
}

// Takes two set and implement De Morgan formula
// If program is not broken the formula is always true
void DeMorgan(sets::DayofYearSet Set1, const sets::DayofYearSet &Set2)
{
    cout << endl << "First Set   !(Set1 + Set2) " << endl << !(Set1 + Set2);
    cout << "Second Set   (!Set1 ^ !Set2)" << endl << (!Set1 ^ !Set2) << endl << endl;
    if (!(Set1 + Set2) == (!Set1 ^ !Set2))
    {
        cout << "DeMorgan is workedddd!" << endl << endl;
    }
    else
    {
        cout << "You will never see here 3:-)" << endl << endl;
    }
    return;
}

