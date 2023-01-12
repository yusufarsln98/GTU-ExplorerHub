/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Interface of EightPuzzle class derived from BoardGame2D class.
*/

#include <iostream>
using std::string;

#ifndef EightPuzzle_H
#define EightPuzzle_H

#include "boardgame2d.h"


namespace BoardGamesArslan
{
    class EightPuzzle : public BoardGame2D
    {
        public:
            EightPuzzle(void);
            virtual void playUser(string mov);
            using BoardGame2D::playUser; 
            // Checks playUser function in base class either.
            
            virtual void playAuto(void);
            virtual void print(void) const;
            virtual bool endGame(void) const;
            virtual int boardScore(void) const;
            virtual void initiliaze(void);
            void shuffle(vector<char> &shuf) const;
            int totalInversion(const vector<char> &vD1) const;
            bool isEntryProper(string mov) const;
            bool isMoveValid(int i1, int i2, string dir) const;
            ~EightPuzzle();
    };
}   // End of BoardGamesArslan namespace

#endif