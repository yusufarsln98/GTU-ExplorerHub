/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Implementations of BoardGame2D class.
*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using std::istream;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std::this_thread;   // sleep_for, sleep_until
using namespace std::chrono;        // nanoseconds, system_clock, seconds

#include "boardgame2d.h"

namespace BoardGamesArslan
{
    BoardGame2D::BoardGame2D(void){}
    void BoardGame2D::playUser(void)
    {
        // It asks the user what he/she wants to do and takes the appropriate action.

        cout << endl << "-------- Game Has Started --------" << endl << endl << endl;
        cout << "Instructors: " << endl << endl;
        cout << "1- For Peg Solitare enter cell and direction. <2B UP>" << endl;
        cout << "2- For Eight Puzzle and Klotski games enter cell and direction. <2 UP>" << endl;
        cout << "3- Type 'AUTO' to play automatically one step." << endl;
        cout << "4- Type 'FINISH' to play automatically until done." << endl;
        cout << "5- Type 'EXIT' to terminate the game." << endl << endl;
        cout << endl << "Press enter to continue." << endl;
        getchar();

        string ins = " ";
        while (!(endGame() || ins.compare("EXIT") == 0))
        {
            cout << *this;

            ins.clear();
            getline(cin, ins);
            
            if (ins.compare("FINISH") == 0)
                playAutoAll();
            else if (ins.compare("AUTO") == 0)
                playAuto();
            else if (ins.compare("EXIT") != 0)
                playUser(ins);
        }
        cout << "Game Over!" << endl;
        cout << "Last score is: " << boardScore();
        cout << " (0 is the best score)" << endl << endl;
        
    }
    void BoardGame2D::playAutoAll(void)
    {
        // Plays game automatically until it is over.
        // Displays boards with some pause gradually decreasing.
        
        int counter = 1, temp;
        char ind;
        bool printit = true;

        while(!endGame())
        {
            playAuto();
            if (counter < 5)
            {
                sleep_until(system_clock::now() + milliseconds(700));
                cout << *this;
            }
            else if (counter < 15)
            {
                sleep_until(system_clock::now() + milliseconds(500));
                cout << *this;
            }
            else if (counter < 30)
            {
                sleep_until(system_clock::now() + milliseconds(300));
                cout << *this;
            }
            else if (counter < 150)
            {
                sleep_until(system_clock::now() + milliseconds(100));
                cout << *this;
            }
            else if (printit == true)
            {
                cout << *this;
            }
            else if (printit == false && counter < temp)
            {
                cout << *this;
            }
            
            if (printit == true && counter == 150)
            {
                cout << endl << "Press 1 to skip viewing." << endl;
                cout << "Press 2 to continue viewing without pause. (It may take a long time to over)" << endl;
                cin >> ind;
                getchar();
                if (ind == '1') printit = false;
                temp = counter + 250;
            }
            counter++;
        }
        
        cout << *this;
        cout << "Played all moves automatically. (Total random move performed: " << counter << ")" << endl << endl;
    }
    ostream& operator<<(ostream &out, const BoardGame2D &B)
    {
        cout << "\u001b[2J";        // Clear screen.
        cout << "\u001b[1000A";     // Move cursor to the top left.
        B.print();                  // Call print function to display board.
        return out; 
    }
    void BoardGame2D::playVector(vector<BoardGame2D*> games)
    {
        // Takes a vector of BoardGame2D* and plays all of them automatically.
        for (int i = 0; i < games.size(); i++)
        {
            cout << "\u001b[2J";
            cout << "\u001b[1000A";
            cout << (i + 1) << ". element will be played automatically." << endl;
            sleep_until(system_clock::now() + seconds(1));
            
            cout << "\u001b[2J";
            cout << "\u001b[1000A";
            cout << *games[i];
            sleep_until(system_clock::now() + milliseconds(700));
            
            games[i]->playAutoAll();
            sleep_until(system_clock::now() + seconds(2));
        }
    }
    BoardGame2D::~BoardGame2D(void) {}
}   // End of BoardGamesArslan namespace
