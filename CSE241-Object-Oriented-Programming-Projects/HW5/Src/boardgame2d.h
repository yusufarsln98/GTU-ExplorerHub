/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Interface of BoardGame2D class.
    This class is the base class for the games can be represent in 2D.
*/

#ifndef BoardGame2D_H
#define BoardGame2D_H

#include <iostream>
#include <string>
#include <vector>

using std::istream;
using std::ostream;
using std::string;
using std::vector;

namespace BoardGamesArslan
{
    class BoardGame2D
    {
        public:
            BoardGame2D(void);
            // Default constructor for derived classes.
            
            virtual void playUser(string mov) = 0;
            // Takes string and makes a single move.
            // Implementations of this function will be done in the derived classes.

            virtual void playUser() final;
            // Takes a string for the next move i a loop and plays game until it is over.
            // Implementations of this function will be done in the derived classes.
            
            virtual void playAuto(void) = 0;
            // Makes a random move by computer.
            // Implementations of this function will be done in the derived classes.

            virtual void playAutoAll(void) final;
            // Plays any board game randomly until it is over.
            
            virtual void print(void) const = 0;
            // Prints the board to the screen in proper.
            // Implementations of this function will be done in the derived classes.
            
            friend ostream& operator<<(ostream &out, const BoardGame2D &B);
            //  Clears the screen and moves cursor to the left then calls print() function.
            
            virtual bool endGame(void) const = 0;
            // Checks if the game over.
            // Implementations of this function will be done in the derived classes.

            virtual int boardScore(void) const = 0;
            // Return de score.
            // Implementations of this function will be done in the derived classes.

            virtual void initiliaze(void) = 0;
            // Initiliazes the board.
            // Implementations of this function will be done in the derived classes.
            
            static void playVector(vector<BoardGame2D*> games);
            // Takes vector of BoardGame2D derived classes and plays until it is done.
        
            virtual ~BoardGame2D();
            // Destructor for the delete dynamic objects.

        protected:
            vector<vector<char>> board; // 2D Board
            string move;                // To display movement has been done.
    };
}   // End of BoardGamesArslan namespace


#endif
