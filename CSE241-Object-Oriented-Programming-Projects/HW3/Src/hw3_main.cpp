/*
    Object Orianted Programing - CSE 241
    Yusuf Arslan
    Homework 3
*/
#include "hw3_lib.h"

// Static variables
int PegSolitare::gameNum = 0;
int PegSolitare::currentGame = 0;
int PegSolitare::totalPegNum = 0;

int main(void)
{
    srand(time(NULL));                          // Generates random numbers

    int opr;
    vector<PegSolitare> games;

    // Menu
    cout << endl << "------- Welcome to Peg Solitare Game -------" << endl;
    cout << endl << "Press 'Enter' to display default boards. " << endl;
    getchar();


    // Create a default board.
    PegSolitare::increase_gameNum();
    games.push_back(PegSolitare());
    PegSolitare::increase_totalPegNum(games[0].get_defaultPegNum());
    
    
    // Create another game starts with 6th board.
    PegSolitare::increase_gameNum();
    games.push_back(PegSolitare(6));
    PegSolitare::increase_totalPegNum(games[0].get_defaultPegNum());

    // Create another game starts with board in file board1.txt
    PegSolitare::increase_gameNum();
    games.push_back(PegSolitare("board1.txt"));
    PegSolitare::increase_totalPegNum(games[0].get_defaultPegNum());

    // Display Boards
    games[PegSolitare::get_currentGame()].display_defBoards();

    view_menu();
    cout << endl << "There is 3 open game. 2 of them has default boards." << endl;
    cout << "I want to use constructors which I've created." << endl << endl;

    // Oriant functions according to entry.
    do
    {
        cout << "__ENTER operation you want to do:  " << endl;
        cout << "(Game number " << PegSolitare::get_currentGame() << " is open.)" << endl;
        cin >> opr;
        getchar();
        switch (opr)
        {
        case 1:
            create_new_game(games);
            break;
        case 2:
            games[PegSolitare::get_currentGame()].lead_game();
            break;
        case 3:
            display_available_games(games);
            break;
        case 4:
            PegSolitare::input_currentGame(games);
            break;
        case 5:
            cout << endl << "Total peg number in the game is: " << PegSolitare::get_totalPegNum() << endl << endl;
            break;
        case 6:
            board_comparision(games);
            break;
        case 8:
            view_menu();
            break;
        case -1:
            cout << endl << "Program terminated. Goodbye! " << endl;
            break;
        default:
            cerr << endl << "Invalid input, try again. (To view menu enter '8') " << endl << endl;
            break;
        }

    } while (opr != -1);

    return 0;
}