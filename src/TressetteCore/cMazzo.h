/*
    Tressette
    Copyright (C) 2005  Igor Sarzi Sartori

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Igor Sarzi Sartori
    www.invido.it
    6colpiunbucosolo@gmx.net
*/



//cMazzo.h

#ifndef __CMAZZO_H
#define __CMAZZO_H

#include "win_type_global.h"

#include "CoreEnv.h"
#include "CardSpec.h"

class cCore;

//! class cMazzo
/**
// Class used to handle the deck. This is done with a vector of long. The index  0 is always the deck
// image index.
*/
class cMazzo
{
public:
    cMazzo();

    //! set core game engine object
    void SetCoreEngine(cCore* pVal){m_pCoreGame = pVal;}
    //! create a deck
    void       Create();
    //! clone a deck
    bool       CloneFrom(cMazzo &Master);
    //! value of the next card
    long       GetNextCardVal(){return m_lNextCard;}
    //! shuffle the deck
    bool       Shuffle();
    //! pick the next on the deck
    long       PickNextCard(BOOL* pbEnd);
    //! pick the next on the deck
    BOOL       PickNextCard(CardSpec* pRes);
    //! throw the card on table. Used on games like briscola
    long       ThrowTableCard();
    //! trace the deck
    void       TraceIt();
    //! clear the deck
    void       Clear(){m_vctCards.clear();}
    //! row vetcors of index, better don't use it
    VCT_LONG   GetVectorIndexes(){return m_vctCards;}
    //! total number of cards on the deck
    size_t       Count(){return m_vctCards.size();}
    //! value of assigned deck position
    long       GetIndexRaw(long l){return m_vctCards[l];}
    //! provides if the deck has yet cards
    bool       IsMoreCards();
    //! provides the index of the next card without increment, not to be confused with PickNextCard()
    long       GetIndexNextCard(BOOL* pbEnd);
    //! set a deck card index
    void       SetIndexRaw(int iIndex, long lVal);
    //! set random seed
    void       SetRandomSeed(int iVal){m_iRndSeed = iVal;  srand(m_iRndSeed);}
    //! rewind the deck
    void       DeckRewind();
    //! check if the deck is ok
    void       CheckDeck();

private:
    //! vector of cards in the play (mazzo)
    VCT_LONG      m_vctCards;
    //! index to the next card in the mazzo
    long          m_lNextCard;
    //! core engine 
    cCore*        m_pCoreGame;
    //! random seed
    int           m_iRndSeed;
};


typedef std::vector<char>                       VCT_MAZZO;

#endif
