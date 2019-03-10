

//cMazzo.h

#ifndef __CMAZZO_H
#define __CMAZZO_H

#include "win_type_global.h"

#include "cInvidoCoreEnv.h"
#include "CardSpec.h"

class cInvidoCore;

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
    void SetCoreEngine(cInvidoCore* pVal){m_pCoreGame = pVal;}
    //! create a deck
    void       Create();
    //! clone a deck
    bool       CloneFrom(cMazzo &Master);
    //! value of the next card
    long       GetNextCardVal(){return m_lNextCard;}
    //! shuffle the deck
    bool       Shuffle();
    //! reset the deck
    void       Reset(){m_lNextCard = 0;}
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
	size_t     Count(){return m_vctCards.size();}
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

private:
    //! vector of cards in the play (mazzo)
    VCT_LONG      m_vctCards;
    //! index to the next card in the mazzo
    long          m_lNextCard;
    //! core engine 
    cInvidoCore*  m_pCoreGame;
    //! random seed
    int           m_iRndSeed;
};


typedef std::vector<char>                       VCT_MAZZO;

#endif