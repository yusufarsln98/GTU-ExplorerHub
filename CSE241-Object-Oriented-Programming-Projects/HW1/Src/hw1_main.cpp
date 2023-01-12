/*
Yusuf Arslan - CSE241 Object Orianted Programing

1st Homework - Peg Solitare

20.10.2021
*/

// MAIN FUNCTION OF THE PROGRAM

#include "hw1_lib.h"        // Include libraries from hw1_lib.h.

// Const integers will be used in the program.
const int B1size = 9, B2size = 11, B3size = 10, B4size = 9, B5size = 11;

int main (void)
{
    int boardType = 0;      // Takes board type from user.

    srand(time(NULL));      // Generates random numbers.


    // ----------------------------- Creating boards with 2D vectors -----------------------------

    vector<vector<Cells>> Board1
    {
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::emp, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal}

    };
    
    vector<vector<Cells>> Board2
    {
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::emp, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal}
    };

    vector<vector<Cells>> Board3
    {
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::emp, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal}
    };

    vector<vector<Cells>> Board4
    {
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::emp, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal}
    };

    vector<vector<Cells>> Board5
    {
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal},
        {Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::emp, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal},
        {Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::peg, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal}
    };

    vector<vector<Cells>> Board6
    {
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::emp, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::wal, Cells::wal},
        {Cells::wal, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::wal},
        {Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal, Cells::peg, Cells::wal},
        {Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal, Cells::wal}
    };
    
    // ----------------------------- Creating boards with 2D vectors -----------------------------


    //  ---------------------- Display boards ----------------------

    cout << "1-" << endl;
    display_boards(Board1, B1size, B1size);

    cout << "2-" << endl;
    display_boards(Board2, B2size, B2size);
    
    cout << "3-" << endl;
    display_boards(Board3, B3size, B3size);
    
    cout << "4-" << endl;
    display_boards(Board4, B4size, B4size);
    
    cout << "5-" << endl;
    display_boards(Board5, B5size, B5size);

    cout << "6-" << endl;
    display_boards(Board6, 7, 11);

    //  ---------------------- Display boards ----------------------


    // Take the number of board from user

    cout << "\nPlease enter the board type from 1 to 6." << endl << endl;
    
    while (boardType <= 0 || boardType >= 7)
    {
        cin >> boardType;
        if (boardType <= 0 || boardType >= 7)
            cout << "\nError! Enter a valid number." << endl;
    }
    
    // Redirect to the game according to the user's choice.
    switch (boardType)
    {
    case 1:
        play_game(Board1, B1size);
        break;
    case 2:
        play_game(Board2, B2size);
        break;
    case 3:
        play_game(Board3, B3size);
        break;
    case 4:
        play_game(Board4, B4size);
        break;
    case 5:
        play_game(Board5, B5size);
        break;
    case 6:
        play_triangle_game(Board6, 7, 11);
        break;
    }

    return 0;
}
// ------------------------- END OF THE MAIN FUNCTION -------------------------
