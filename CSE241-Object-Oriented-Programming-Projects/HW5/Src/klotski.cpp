/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Implementation of Klotski class derived from BoardGame2D class.
*/

#include <iostream>
#include <string>
#include <cstdlib>

#include "klotski.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

namespace BoardGamesArslan
{
    enum PieceType {v1 = '1', v2 = '2', v3 = '3', v4 = '4', s1 = '5', s2 = '6', 
                    s3 = '7', s4 = '8', h1 = '9', Re = '0', Sp = ' ', Wa = '.'};
    // Enum of pieces to make code more readable.
    
    Klotski::Klotski(void) : BoardGame2D()
    {
        // Default constructor.
        // Calls initiliaze() function to initiliaze object with a board.
        initiliaze();
    }
    void Klotski::playUser(string mov)
    {
        if (!isEntryProper(mov))
        {
            // Check if entry is in valid format.
            move = "invalid entry";
            return;
        }

        char peg;
        string dir;
        peg = mov[0];
        dir = mov.substr(2);

        if (!isMoveValid(peg, dir))
        {
            // Check if move is valid.
            move = "invalid move";
            return; 
        }

        // Make the move.
        int luc1, luc2, rdc1, rdc2;
        bool isfound = false;
        
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (isfound == false && board[i][j] == peg)
                {
                    luc1 = i; luc2 = j; isfound = true; 
                }
                else if (isfound == true && board[i][j] == peg)
                {
                    rdc1 = i; rdc2 = j;
                }
            }
        }

        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                if (board[i][j] == peg) board[i][j] = Sp;

        switch (dir[0])
        {
        case 'U':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1 - 2 && i <= rdc1 - 2)
                        if (j >= luc2 && j <= rdc2)
                            board[i][j] = peg;
                }
            }
            break;
        case 'D':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1 + 2 && i <= rdc1 + 2)
                        if (j >= luc2 && j <= rdc2)
                            board[i][j] = peg;
                }
            }
            break;
        case 'L':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1&& i <= rdc1)
                        if (j >= luc2 - 2 && j <= rdc2 - 2)
                            board[i][j] = peg;
                }
            }
            break;
        case 'R':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1&& i <= rdc1)
                        if (j >= luc2 + 2 && j <= rdc2 + 2)
                            board[i][j] = peg;
                }
            }
            break;
        }
        move.clear();
        move.push_back(peg);
        move += (" " + dir);
    }   
    void Klotski::playAuto(void)
    {
        char peg; 
        int dirint;
        string dir;
        
        // Make a random valid move.
        do
        {
            peg = rand() % 10 + '0';
            dirint = rand() % 4 + 1;
            
            if (dirint == 1)
                dir = "UP";
            else if (dirint == 2)
                dir = "DOWN";
            else if (dirint == 3)
                dir = "LEFT";
            else if (dirint == 4)
                dir = "RIGHT";
        } while(!isMoveValid(peg, dir));
        
        // Perform the move.
        int luc1, luc2, rdc1, rdc2;
        bool isfound = false;
        
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (isfound == false && board[i][j] == peg)
                {
                    luc1 = i; luc2 = j; isfound = true; 
                }
                else if (isfound == true && board[i][j] == peg)
                {
                    rdc1 = i; rdc2 = j;
                }
            }
        }

        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                if (board[i][j] == peg) board[i][j] = Sp;

        switch (dir[0])
        {
        case 'U':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1 - 2 && i <= rdc1 - 2)
                        if (j >= luc2 && j <= rdc2)
                            board[i][j] = peg;
                }
            }
            break;
        case 'D':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1 + 2 && i <= rdc1 + 2)
                        if (j >= luc2 && j <= rdc2)
                            board[i][j] = peg;
                }
            }
            break;
        case 'L':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1&& i <= rdc1)
                        if (j >= luc2 - 2 && j <= rdc2 - 2)
                            board[i][j] = peg;
                }
            }
            break;
        case 'R':
            for (int i = 0; i < board.size(); i++)
            {
                for (int j = 0; j < board[0].size(); j++)
                {
                    if (i >= luc1&& i <= rdc1)
                        if (j >= luc2 + 2 && j <= rdc2 + 2)
                            board[i][j] = peg;
                }
            }
            break;
        }
        move.clear();
        move.push_back(peg);
        move += (" " + dir);
    }
    void Klotski::print(void) const
    {
        // Display the board.
        cout << endl;
        for (int i = 0; i < board.size(); i++)
        {
            cout << "     ";
            for (int j = 0; j < board[0].size(); j++)
            {
                if(!(i == 0 || j == 0 || i == board.size() - 1 || j == board[0].size() - 1))
                {
                    if (board[i][j] != board[i - 1][j] && board[i][j] != board[i][j - 1] && board[i][j] != ' ' && board[i][j] != '.')
                    {
                        if (board[i][j] == v1)
                            cout << "┌1";
                        if (board[i][j] == v2)
                            cout << "┌2"; 
                        if (board[i][j] == v3)
                            cout << "┌3"; 
                        if (board[i][j] == v4)
                            cout << "┌4"; 
                        if (board[i][j] == s1)
                            cout << "┌5"; 
                        if (board[i][j] == s2)
                            cout << "┌6"; 
                        if (board[i][j] == s3)
                            cout << "┌7"; 
                        if (board[i][j] == s4)
                            cout << "┌8";
                        if (board[i][j] == h1)
                            cout << "┌9"; 
                        if (board[i][j] == Re)
                            cout << "┌0";
                    }
                    else if (board[i][j] != board[i - 1][j] && board[i][j] != board[i][j + 1] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "┐ ";
                    else if (board[i][j] != board[i][j - 1] && board[i][j] != board[i + 1][j] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "└─";
                    else if (board[i][j] != board[i][j + 1] && board[i][j] != board[i + 1][j] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "┘ ";
                    else if (board[i][j] == board[i - 1][j] && board[i][j] == board[i + 1][j] && board[i][j] == board[i][j - 1] && 
                             board[i][j] == board[i][j + 1] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "  ";
                    else if (board[i][j] != board[i - 1][j] && board[i][j] == board[i][j + 1] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "──";
                    else if (board[i][j] != board[i + 1][j] && board[i][j] == board[i][j + 1] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "──";
                    else if (board[i][j] != board[i][j - 1] && board[i][j] == board[i + 1][j] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "│ ";
                    else if (board[i][j] != board[i][j + 1] && board[i][j] == board[i + 1][j] && board[i][j] != Sp && board[i][j] != Wa)
                        cout << "│ ";
                    else
                       cout << board[i][j] << ' ';                     
                }
                else
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
    bool Klotski::endGame(void) const
    {
        // Check if the game is over.
        if(board[9][3] == Re && board[12][6] == Re)
            return true;

        return false;
    }
    int Klotski::boardScore(void) const
    {
        // Return de total inversion as score.
        // If inversion is 0 then the game is over.
        int i1, i2;
        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++)
                if(Re == board[i][j])
                    {i1 = i; i2 = j;}
        return ((-1) * (i1 - 12));
    }
    void Klotski::initiliaze(void)
    {
        // Initiliaze the board according to the solvable condition.
        vector<vector<char>> newBoard = 
        {
            {Wa, Wa, Wa, Wa, Wa, Wa, Wa, Wa, Wa, Wa},
            {Wa, v1, v1, Re, Re, Re, Re, v2, v2, Wa},
            {Wa, v1, v1, Re, Re, Re, Re, v2, v2, Wa},
            {Wa, v1, v1, Re, Re, Re, Re, v2, v2, Wa},
            {Wa, v1, v1, Re, Re, Re, Re, v2, v2, Wa},
            {Wa, v3, v3, h1, h1, h1, h1, v4, v4, Wa},
            {Wa, v3, v3, h1, h1, h1, h1, v4, v4, Wa},
            {Wa, v3, v3, s2, s2, s3, s3, v4, v4, Wa},
            {Wa, v3, v3, s2, s2, s3, s3, v4, v4, Wa},
            {Wa, s1, s1, Sp, Sp, Sp, Sp, s4, s4, Wa},
            {Wa, s1, s1, Sp, Sp, Sp, Sp, s4, s4, Wa},
            {Wa, Wa, Wa, Sp, Sp, Sp, Sp, Wa, Wa, Wa},
            {Wa, Wa, Wa, Sp, Sp, Sp, Sp, Wa, Wa, Wa},
            {Wa, Wa, Wa, Wa, Wa, Wa, Wa, Wa, Wa, Wa}
        };
        board = newBoard;
    }
    bool Klotski::isMoveValid(char peg, string dir) const
    {
        // According to the space, check if move is valid.
        int i1, i2;
        bool isfound = false;
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if(peg == board[i][j])
                {
                    i1 = i; 
                    i2 = j;
                    isfound = true;
                    break;
                }
            }
            if (isfound == true) break;
        }

        if (peg == v1 || peg == v2 || peg == v3 || peg == v4)
        {
            if      (dir[0] == 'U' && board[i1 - 1][i2] == Sp && board[i1 - 1][i2 + 1] == Sp)
                return true;
            else if (dir[0] == 'D' && board[i1 + 4][i2] == Sp && board[i1 + 4][i2 + 1] == Sp)
                return true;
            else if (dir[0] == 'L' && board[i1][i2 - 1] == Sp && board[i1 + 3][i2 - 1] == Sp)
                return true;
            else if (dir[0] == 'R' && board[i1][i2 + 2] == Sp && board[i1 + 3][i2 + 2] == Sp)
                return true;
        }
        else if (peg == s1 || peg == s2 || peg == s3 || peg == s4)
        {

            if      (dir[0] == 'U' && board[i1 - 1][i2] == Sp && board[i1 - 1][i2 + 1] == Sp)
                return true;
            else if (dir[0] == 'D' && board[i1 + 2][i2] == Sp && board[i1 + 2][i2 + 1] == Sp)
                return true;
            else if (dir[0] == 'L' && board[i1][i2 - 1] == Sp && board[i1 + 1][i2 - 1] == Sp)
                return true;
            else if (dir[0] == 'R' && board[i1][i2 + 2] == Sp && board[i1 + 1][i2 + 2] == Sp)
                return true;
        }
        else if (peg == h1)
        {
            if      (dir[0] == 'U' && board[i1 - 1][i2] == Sp && board[i1 - 1][i2 + 3] == Sp)
                return true;
            else if (dir[0] == 'D' && board[i1 + 2][i2] == Sp && board[i1 + 2][i2 + 3] == Sp)
                return true;
            else if (dir[0] == 'L' && board[i1][i2 - 1] == Sp && board[i1 + 1][i2 - 1] == Sp)
                return true;
            else if (dir[0] == 'R' && board[i1][i2 + 4] == Sp && board[i1 + 1][i2 + 4] == Sp)
                return true;
        
        }
        else if (peg == Re)
        {
            if      (dir[0] == 'U' && board[i1 - 1][i2] == Sp && board[i1 - 1][i2 + 3] == Sp)
                return true;
            else if (dir[0] == 'D' && board[i1 + 4][i2] == Sp && board[i1 + 4][i2 + 3] == Sp)
                return true;
            else if (dir[0] == 'L' && board[i1][i2 - 1] == Sp && board[i1 + 3][i2 - 1] == Sp)
                return true;
            else if (dir[0] == 'R' && board[i1][i2 + 4] == Sp && board[i1 + 3][i2 + 4] == Sp)
                return true;
        }
        return false;
    }
    bool Klotski::isEntryProper(string mov) const
    {
        // Check if entry is valid.
        if (mov.size() < 4)
            return false;

        string peg;
        peg = mov.substr(0, 1);

        if (!(peg[0] >= '0' && peg[0] <= '9'))
            return false;
        
        string dir;
        dir = mov.substr(2);
        
        if(!(dir.compare("UP") == 0 || dir.compare("DOWN") == 0 ||
            dir.compare("RIGHT") == 0 || dir.compare("LEFT") == 0))
            return false;
        
        return true;
    }
    Klotski::~Klotski(void) {}
}   // End of BoardGamesArslan namespace