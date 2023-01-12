/*
Yusuf Arslan
CSE 241 - OOP
Homework4

Header file - Class and function declerations
*/
#include <iostream>
#include <vector>
#include <string>
#include<cstdlib>

using namespace std;

namespace sets
{
    class DayofYearSet
    {
        public:
            class DayofYear
            {
                public:
                    DayofYear(void);
                    DayofYear(int newDay, int newMonth);

                    void set_day(int newDay); 
                    void set_month(int newMonth);

                    int get_day(void) const {return Day; };
                    int get_month(void) const {return Month; };
                private:
                    int Day;
                    int Month;
            };

            DayofYearSet(void);
            DayofYearSet(int newDay, int newMonth);
            DayofYearSet(const vector<DayofYear> &newSet);
            DayofYearSet(const DayofYearSet& newObject);

            DayofYear& operator[](int index) const;
            friend ostream& operator<<(ostream &outputStream, const DayofYearSet &mySet);
            bool operator==(const DayofYearSet &rightSet) const;
            bool operator!=(const DayofYearSet &rightSet) const;
            void add(int newDay, int newMonth);
            void remove(int rmDay, int rmMonth);
            int size(void) const {return Size; };
            const DayofYearSet operator+(const DayofYearSet &rightSet) const;
            const DayofYearSet operator-(const DayofYearSet &rightSet) const;
            const DayofYearSet operator^(const DayofYearSet &rightSet) const;
            const DayofYearSet operator!(void) const;
            static int get_totalDates(void) {return totalDates; };

            DayofYearSet& operator=(const DayofYearSet &rightSet);
            ~DayofYearSet(void);

        private:
            DayofYear *Dates = nullptr;
            int Size = 0;
            static int totalDates;
    };
}

void DeMorgan(sets::DayofYearSet Set1, const sets::DayofYearSet &Set2);
