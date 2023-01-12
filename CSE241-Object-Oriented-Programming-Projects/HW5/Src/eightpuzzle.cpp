/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Implementation of EightPuzzle class derived from BoardGame2D class.
*/

#include <iostream>
#include <string>
#include <cstdlib>

#include "eightpuzzle.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace BoardGamesArslan
{
    EightPuzzle::EightPuzzle(void) : BoardGame2D()
    {
        // Default constructor.
        // Calls initiliaze() function to initiliaze object with a board.
        initiliaze();
    }
    void EightPuzzle::playUser(string mov)
    {
        if (!isEntryProper(mov))
        {
            // Check if entry is in valid format.
            move = "invalid entry";
            return;
        }

        int i1, i2;
        string cel, dir;
        
        cel = mov.substr(0, 1);
        dir = mov.substr(2);

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if(cel[0] == board[i][j])
                    {i1 = i; i2 = j;}
        
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
            board[i1 - 1][i2] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        case 'D':
            board[i1 + 1][i2] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        case 'L':
            board[i1][i2 - 1] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        case 'R':
            board[i1][i2 + 1] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        }
        move.clear();
        move = cel + " " + dir;
    }   
    void EightPuzzle::playAuto(void)
    {
        int i1, i2, dirint;
        string dir;
        char temp;

        // Make a random valid move.
        do
        {
            i1 = rand() % 3;
            i2 = rand() % 3;
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
        
        temp = board[i1][i2];
        
        // Perform the move.
        switch (dir[0])
        {
        case 'U':
            board[i1 - 1][i2] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        case 'D':
            board[i1 + 1][i2] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        case 'L':
            board[i1][i2 - 1] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        case 'R':
            board[i1][i2 + 1] = board[i1][i2];
            board[i1][i2] = '.';
            break;
        }
        move.clear();
        move.push_back(temp);
        move += (" " + dir);
    }
    void EightPuzzle::print(void) const
    {
        // Display the board.
        cout << endl << "      ";
        for(int i = 0; i < 11; i++)
        {
            cout << "—";
        }
        cout << endl;
        for (int i = 0; i < board.size(); i++)
        {
            cout << "     | ";
            for (int j = 0; j < board[0].size(); j++)
            {
                cout << board[i][j] << " | ";
            }
            cout << endl << "      ";
            for(int i = 0; i < 11; i++)
            {
                cout << "—";
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
    bool EightPuzzle::endGame(void) const
    {
        // Check if the game is over.
        vector<char> temp;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                temp.push_back(board[i][j]);
        
        if(totalInversion(temp) == 0)
            return true;

        return false;
    }
    int EightPuzzle::boardScore(void) const
    {
        // Return de total inversion as score.
        // If inversion is 0 then the game is over.
        vector<char> temp;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                temp.push_back(board[i][j]);

        return totalInversion(temp);
    }
    void EightPuzzle::initiliaze(void)
    {
        // Initiliaze the board according to the solvable condition.
        vector<char> shuf = {'1', '2', '3', '4', '5', '6', '7', '8', '.'};
        vector<char> temp;
        
        do
        {
            shuffle(shuf);
        } while (!(totalInversion(shuf) % 2 == 0 && totalInversion(shuf) != 0));
        
        for(int i = 0; i < shuf.size(); i++)
        {
            temp.push_back(shuf[i]);
            if(i % 3 == 2)
            {
                board.push_back(temp);
                temp.clear();
            }
        }
    }
    void EightPuzzle::shuffle(vector<char> &shuf) const
    {
        // Shuffle the board randomly.
        int i1, i2;
        char temp;
        for (int i = 0; i < 1000; i++)
        {
            i1 = rand() % 9;
            i2 = rand() % 9;
            temp = shuf[i1];
            shuf[i1] = shuf[i2];
            shuf[i2] = temp;
        }
    }
    int EightPuzzle::totalInversion(const vector<char> &vD1) const
    {
        // Check the right side of the all elements then calculate total inversions.
        // Which mean count number of smaller number from the selected number on the right side of the array.
        vector<char> inversion;
        for(int i = 0; i < vD1.size(); i++)
        {
            if (vD1[i] != '.')
                inversion.push_back(vD1[i]);
        }

        int count = 0;
        for(int i = 0; i < inversion.size() - 1; i++)
            for(int j = i + 1; j < inversion.size(); j++)
                if (inversion[i] > inversion[j])
                    count++;
        
        return count;
    }
    bool EightPuzzle::isMoveValid(int i1, int i2, string dir) const
    {
        // According to the space, check if move is valid.
        switch (dir[0])
        {
        case 'U':
            if(i1 != 0 && board[i1 - 1][i2] == '.')
                return true;
            break;
        case 'D':
            if(i1 != 2 && board[i1 + 1][i2] == '.')
                return true;
            break;
        case 'L':
            if(i2 != 0 && board[i1][i2 - 1] == '.')
                return true;
            break;
        case 'R':
            if(i2 != 2 && board[i1][i2 + 1] == '.')
                return true;
            break;
        }
        return false;
    }
    bool EightPuzzle::isEntryProper(string mov) const
    {
        // Check if entry is valid.
        if (mov.size() < 4)
            return false;

        string cel;
        cel = mov.substr(0, 1);

        if (!(cel[0] >= '1' && cel[0] <= '8'))
            return false;
        
        string dir;
        dir = mov.substr(2);
        
        if(!(dir.compare("UP") == 0 || dir.compare("DOWN") == 0 ||
            dir.compare("RIGHT") == 0 || dir.compare("LEFT") == 0))
            return false;
        
        return true;
    }
    EightPuzzle::~EightPuzzle(void) {}
}   // End of BoardGamesArslan namespace