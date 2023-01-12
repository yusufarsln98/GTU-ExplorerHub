/*
Yusuf Arslan - CSE241 Object Orianted Programing

2nd Homework - Peg Solitare v2

25.10.2021
*/

#include "hw2_lib.h"

// Const integers will be used during the program.
const int B1size = 9, B2size = 11, B3size = 10, B4size = 9, B5size = 11, B6row = 7, B6clm = 11;

// MAIN FUNCTION OF THE PROGRAM

int main (void)
{
    srand(time(NULL));                          // Generates random numbers
    string str, filename;                       // To read from console
    int moveNum = 0, player;                    // Number of move and which player was the last one
    int arbrow, arbclm;                         // Dimensions of arbitrary boards
    vector<vector<Cells>> arbBoard;             // Declaration of arbitrary boards
    fstream inputStream;                         
    
    // --------------------- Initializations of first 6 boards ---------------------
    
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
    // --------------------- Initializations of first 6 boards ---------------------

    

    // Print instructions
    cout << "------ PEG SOLITARE ------ " << endl;
    cout << "---------------------------" << endl;
    display_instructions();
    
    cout << "Press enter to view the boards.";
    getchar();
    
    // ------- Print Default Boards -------
    display_default_boards(Board1, Board2, Board3, Board4, Board5, Board6);
    
    // ------- Print Arbitrary and Saved Boards -------
    display_arbitrary_boards();

    
    // ------- Menu -------
    while (1)
    {
        cout << "(To display instructions, ENTER \"instructions\")" << endl;
        cout << "--> Please enter what you want to do:\n";
        
        getline(cin, str);
        if (str.compare("exit") == 0) break;
        else if (str.compare("1") == 0) play_game(Board1, B1size, B1size, moveNum, str); 
        else if (str.compare("2") == 0) play_game(Board2, B2size, B2size, moveNum, str); 
        else if (str.compare("3") == 0) play_game(Board3, B3size, B3size, moveNum, str); 
        else if (str.compare("4") == 0) play_game(Board4, B4size, B4size, moveNum, str); 
        else if (str.compare("5") == 0) play_game(Board5, B5size, B5size, moveNum, str); 
        else if (str.compare("6") == 0) play_triangle_game(Board6, B6row, B6clm, moveNum, str); 
        else if (str.compare("instructions") == 0) display_instructions();
        else 
            cerr << endl << "WRONG INPUT! ";

        if (str.compare(0, 4, "load") == 0)
        {
            filename = str.substr(5);
            read_arbBoard(arbBoard, filename, moveNum, player, arbrow, arbclm);
            play_game(arbBoard, arbrow, arbclm, moveNum, str);
        }

        moveNum = 0;
    }

    return 0;
}



