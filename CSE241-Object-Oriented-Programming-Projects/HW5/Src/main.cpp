#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "boardgame2d.h"
#include "pegsolitaire.h"
#include "eightpuzzle.h"
#include "klotski.h"

using namespace BoardGamesArslan;
using std::cout;
using std::endl;
using std::this_thread::sleep_until; 
using std::chrono::system_clock;
using std::chrono::seconds;


void driver(void)
{
    // Firstly create 3 object then call playUser() function one by one.
    // Secondly create a BoardGame2D* vector and push 6 object into it then test it.
    
    cout << "\u001b[2J";
    cout << "\u001b[1000A";

    cout << "--------- Driver for BoardGame2D project ---------" << endl << endl;
    cout << "Please follow the instructions." << endl << endl;

    PegSolitaire p1;
    cout << "The Peg Solitaire object has been created." << endl; 
    cout << "You are redirected to the BoardGame2D::PlayUser() function." << endl;

    sleep_until(system_clock::now() + seconds(3));
    cout << "\u001b[2J";
    cout << "\u001b[1000A";
    p1.playUser();
    sleep_until(system_clock::now() + seconds(3));


    cout << "\u001b[2J";
    cout << "\u001b[1000A";
    EightPuzzle e1;
    cout << "The Eight Puzzle object has been created." << endl; 
    cout << "You are redirected to the BoardGame2D::PlayUser() function." << endl;
    sleep_until(system_clock::now() + seconds(2));
    cout << "\u001b[2J";
    cout << "\u001b[1000A";
    e1.playUser();
    sleep_until(system_clock::now() + seconds(3));

    cout << "\u001b[2J";
    cout << "\u001b[1000A";
    Klotski k1;
    cout << "The Klotski object has been created." << endl; 
    cout << "You are redirected to the BoardGame2D::PlayUser() function." << endl;
    sleep_until(system_clock::now() + seconds(2));
    cout << "\u001b[2J";
    cout << "\u001b[1000A";
    k1.playUser();
    sleep_until(system_clock::now() + seconds(5));

    
    cout << "\u001b[2J";
    cout << "\u001b[1000A";
    cout << "vector<BoardGame2D*> games has been created." << endl << endl;
    cout << "For all derived class 2 object has been created" << endl;
    cout << "(1- Derived o1;" << endl;
    cout << " 2- Derived *o2 = new Derived; )" << endl << endl;
    cout << "All object pushed to the games vector." << endl;
    cout << "Then static BoardGame2D::playvector(games) invoked." << endl;
    sleep_until(system_clock::now() + seconds(6));


    vector<BoardGame2D*> games;
    PegSolitaire *p2 = new PegSolitaire;
    PegSolitaire p3;

    games.push_back(p2);
    games.push_back(&p3);

    EightPuzzle *e2 = new EightPuzzle;
    EightPuzzle e3;
    games.push_back(e2);
    games.push_back(&e3);

    Klotski *k2 = new Klotski;
    Klotski k3;
    games.push_back(k2);
    games.push_back(&k3);

    BoardGame2D::playVector(games);

    delete p2;
    delete e2;
    delete k2;
}
    
int main(void)
{
    srand(time(0));
    driver();

    return 0;   
}
