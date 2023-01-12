/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Implementation of PegSolitare class derived from BoardGame2D class.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "pegsolitaire.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace BoardGamesArslan
{
    PegSolitaire::PegSolitaire(void) : BoardGame2D()
    {
        // Default constructor.
        // Calls initiliaze() function to initiliaze object with a board.
        initiliaze();
    }
    void PegSolitaire::playUser(string mov)
    {
        if (!isEntryProper(mov))
        {
            // Check if entry is in valid format.
            move = "invalid entry";
            return;
        }

        int i1, i2;
        string dir;
        
        i1 = mov[0] - '1';
        i2 = mov[1] - 'A';

        dir = mov.substr(3);

        if (!isMoveValid(i1, i2, dir))
        {
            // Check if move is valid.
            move = "invalid move";
            return; 
        }

        // Make the move.
        switch (dir[0])
        {
        case 'U':
            board[i1][i2] = '.';
            board[i1 - 1][i2] = '.'; 
            board[i1 - 2][i2] = 'o';
            break;
        case 'D':
            board[i1][i2] = '.';
            board[i1 + 1][i2] = '.';
            board[i1 + 2][i2] = 'o';
            break;
        case 'L':
            board[i1][i2] = '.';
            board[i1][i2 - 1] = '.';
            board[i1][i2 - 2] = 'o';
            break;
        case 'R':
            board[i1][i2] = '.';
            board[i1][i2 + 1] = '.';
            board[i1][i2 + 2] = 'o';
            break;
        }
        
        move.clear();
        move.push_back(static_cast<char>(i1 + '1'));
        move.push_back(static_cast<char>(i2 + 'A'));
        move += (" " + dir);
    }   
    void PegSolitaire::playAuto(void)
    {
        int i1, i2, dirint;
        string dir;
        
        // Make a random valid move.
        do
        {
            i1 = rand() % 9;
            i2 = rand() % 9;
            dirint = rand() % 4 + 1;
            
            if (dirint == 1)
                dir = "UP";
            else if (dirint == 2)
                dir = "DOWN";
            else if (dirint == 3)
                dir = "LEFT";
            else if (dirint == 4)
                dir = "RIGHT";
        } while(!isMoveValid(i1, i2, dir));
        
        // Perform the move.
        switch (dir[0])
        {
        case 'U':
            board[i1][i2] = '.';
            board[i1 - 1][i2] = '.'; 
            board[i1 - 2][i2] = 'o';
            break;
        case 'D':
            board[i1][i2] = '.';
            board[i1 + 1][i2] = '.';
            board[i1 + 2][i2] = 'o';
            break;
        case 'L':
            board[i1][i2] = '.';
            board[i1][i2 - 1] = '.';
            board[i1][i2 - 2] = 'o';
            break;
        case 'R':
            board[i1][i2] = '.';
            board[i1][i2 + 1] = '.';
            board[i1][i2 + 2] = 'o';
            break;
        }

        move.clear();
        move.push_back(static_cast<char>(i1 + '1'));
        move.push_back(static_cast<char>(i2 + 'A'));
        move += (" " + dir);
    }
    void PegSolitaire::print(void) const
    {
        // Display the board.
        char label = 'A';

        cout << endl << "      ";
        for (int i = 0; i < board[0].size(); i++, label++)
            cout << label << " ";

        cout << endl << endl;

        for (int i = 0; i < board.size(); i++)
        {
            cout << i + 1 << "     ";
            for (int j = 0; j < board[0].size(); j++)
            {
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        
        cout << endl << endl;
        if (move.compare("invalid entry") == 0)
            cout << "Invalid entry. Try Again!" << endl << endl;
        else if (move.compare("invalid move") == 0)
            cout << "Invalid move. The move could not be performed." << endl << endl;
        else if (move.size() != 0)
            cout << "Move " << move << " has been performed." << endl << endl;
    }
    bool PegSolitaire::endGame(void) const
    {
        // Check if the game is over.
        for(int i = 0; i < board.size(); i++)
        {
            for(int j = 0; j < board[0].size(); j++)
            {
                if(isMoveValid(i, j, "UP") || isMoveValid(i, j, "DOWN") ||
                   isMoveValid(i, j, "LEFT") || isMoveValid(i, j, "RIGHT"))
                   return false;
            }
        }

        return true;
    }
    int PegSolitaire::boardScore(void) const
    {
        int count = 0;
        
        // Calculate score then return it.
        for(int i = 0; i < board.size(); i++)
        {
            for(int j = 0; j < board[0].size(); j++)
            {
                if(board[i][j] == 'o')
                    count++;
            }
        }
        return count;
    }
    void PegSolitaire::initiliaze(void)
    {
        // Initiliaze the board.
        vector<vector<char>> newBoard =
        {
            {' ', ' ', ' ', 'o', 'o', 'o', ' ', ' ', ' '},
            {' ', ' ', ' ', 'o', 'o', 'o', ' ', ' ', ' '},
            {' ', ' ', ' ', 'o', 'o', 'o', ' ', ' ', ' '},
            {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
            {'o', 'o', 'o', 'o', '.', 'o', 'o', 'o', 'o'},
            {'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
            {' ', ' ', ' ', 'o', 'o', 'o', ' ', ' ', ' '},
            {' ', ' ', ' ', 'o', 'o', 'o', ' ', ' ', ' '},
            {' ', ' ', ' ', 'o', 'o', 'o', ' ', ' ', ' '}
        };
        board = newBoard;
    }
    bool PegSolitaire::isMoveValid(int i1, int i2, string dir) const
    {
        // Check if move is valid.
        switch (dir[0])
        {
        case 'U':
            if (i1 >= 2 && board[i1][i2] == 'o' && board[i1 - 1][i2] == 'o' && board[i1 - 2][i2] == '.')
                return true;
            break;
        case 'D':
            if (i1 <= 6 && board[i1][i2] == 'o' && board[i1 + 1][i2] == 'o' && board[i1 + 2][i2] == '.')
                return true;
            break;
        case 'L':
            if (i2 >= 2 && board[i1][i2] == 'o' && board[i1][i2 - 1] == 'o' && board[i1][i2 - 2] == '.')
                return true;
            break;
        case 'R':
            if (i2 <= 6 && board[i1][i2] == 'o' && board[i1][i2 + 1] == 'o' && board[i1][i2 + 2] == '.')
                return true;
            break;
        }
        return false;
    }
    bool PegSolitaire::isEntryProper(string mov) const
    {
        // Check if entry is in valid format.
        if (mov.size() < 5)
            return false;

        string cel;
        cel = mov.substr(0, 2);

        if (!(cel[1] >= 'A' && cel[1] <= 'I') || !(cel[0] >= '1' && cel[0] <= '9'))
            return false;
        
        string dir;
        dir = mov.substr(3);
        
        if(!(dir.compare("UP") == 0 || dir.compare("DOWN") == 0 ||
            dir.compare("RIGHT") == 0 || dir.compare("LEFT") == 0))
            return false;
        
        return true;
    }
    PegSolitaire::~PegSolitaire(void){}
}   // End of BoardGamesArslan namespace