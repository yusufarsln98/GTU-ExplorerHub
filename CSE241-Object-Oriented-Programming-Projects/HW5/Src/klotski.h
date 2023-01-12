/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Interface of Klotski class derived from BoardGame2D class.
*/

#include <iostream>
using std::string;

#ifndef Klotski_H
#define Klotski_H

#include "boardgame2d.h"


namespace BoardGamesArslan
{
    class Klotski : public BoardGame2D
    {
        public:
            Klotski(void);
            virtual void playUser(string mov);
            using BoardGame2D::playUser; 
            // Checks function playUser in base class either.
            
            virtual void playAuto(void);
            virtual void print(void) const;
            virtual bool endGame(void) const;
            virtual int boardScore(void) const;
            virtual void initiliaze(void);
            bool isEntryProper(string mov) const;
            bool isMoveValid(char peg, string dir) const;
            ~Klotski();
    };
}   // End of BoardGamesArslan namespace

#endif