/*
    Yusuf Arslan - Gebze Technical University
    Bachelor of Computer Engineering
*/

/*
    Interface of PegSolitare class derived from BoardGame2D class.
*/

#include <iostream>
using std::string;

#ifndef PegSolitaire_H
#define PegSolitaire_H

#include "boardgame2d.h"


namespace BoardGamesArslan
{
    class PegSolitaire : public BoardGame2D
    {
        public:
            PegSolitaire(void);
            virtual void playUser(string mov);
            using BoardGame2D::playUser;        
            // Checks function playUser in base class either.
            
            virtual void playAuto(void);
            virtual void print(void) const;
            virtual bool endGame(void) const;
            virtual int boardScore(void) const;
            virtual void initiliaze(void);
            bool isEntryProper(string mov) const;
            bool isMoveValid(int i1, int i2, string dir) const;
            ~PegSolitaire();
    };
}   // End of BoardGamesArslan namespace

#endif