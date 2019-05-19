

// cMazzo.cpp
#include "StdAfx.h"
#include <win_type_global.h>
#include "cMazzo.h"
#include "cCoreEngine.h"
#include "cSettings.h"


////////////////////////////////////////////////////////////////
//   *******************      cMazzo CLASS *********************
////////////////////////////////////////////////////////////////

cMazzo::cMazzo()
{
    m_lNextCard = 0;
    m_pCoreGame = 0;
    m_iRndSeed = 63200;
}




////////////////////////////////////////
//       Create
/*! Create a deck for invido game
*/
void  cMazzo::Create() 
{
    m_vctCards.reserve(NUM_CARDS);
    m_vctCards.clear();

#ifdef DECK_FOR_INVIDO
    //invido card index (32 cards)
    int aCardIndex[]={0,1,2,5,6,7,8,9,10,11,12,15,16,17,18,19,20,21,22,25,26,27,28,29,30,31,32,35,36,37,38,39};
#else
    int aCardIndex[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39};
#endif

    for (int i = 0; i < NUM_CARDS; i++)
    {
        m_vctCards.push_back(aCardIndex[i]);
    }

    m_lNextCard = 0;

  
}


////////////////////////////////////////
//       SetIndexRaw
/*! Set the card value at defined position. Use this function to override the shuffle of deck.
*/
void  cMazzo::SetIndexRaw(int iIndex, long lVal)
{
    size_t iNumEle = m_vctCards.size();
    if (iIndex < iNumEle && iIndex >= 0)
    {
        m_vctCards[iIndex] = lVal;
    }
}

////////////////////////////////////////
//       CloneFrom
/*! Clone the deck from another deck
// \param cMazzo &Master : deck to be cloned
*/
bool  cMazzo::CloneFrom(cMazzo &Master)
{
    m_lNextCard = Master.GetNextCardVal();
    m_vctCards = Master.GetVectorIndexes();

    return true;
}


////////////////////////////////////////
//       DeckRewind
/*! Position of the deck at the begin
*/
void cMazzo::DeckRewind()
{
    m_lNextCard = 0;
}


////////////////////////////////////////
//       CheckDeck
/*! Check if the deck is ok
*/
void  cMazzo::CheckDeck()
{
    VCT_LONG vctErr;
    for (UINT i = 0; i < m_vctCards.size(); i++)
    {
        BOOL bIndexFound = FALSE;
        for (UINT j = 0; j < m_vctCards.size(); j++)
        {
            if ( m_vctCards[j] == i)
            {
                // ok index found
                bIndexFound = TRUE;
                break;
            }

        }
        if (!bIndexFound)
        {
            // not ok, this index is not found
            TRACE("Deck NOT OK, index %d not found\n", i);
            vctErr.push_back(i);
        }
    }
    if (vctErr.size() == 0)
    {
        TRACE("Deck OK\n");
    }
    else
    {
        TRACE("Deck error found (%d)\n", vctErr.size());
        ASSERT(0);
    }
    
}

////////////////////////////////////////
//       Shuffle
/*! Shuffle deck
*/
bool cMazzo::Shuffle()
{
    IT_VCTLONG it_tmp;

    
      
    it_tmp = m_vctCards.begin();
                            // Leave the deck card to the first position
    
                            // use the rand() function to shuffle the pool (deck is not shuffled)
    std::random_shuffle(it_tmp, m_vctCards.end());
    if (g_Options.All.iDebugLevel > 3 )
    {
        Utility::TraceContainer(m_vctCards, "Cards mazzo"); 
    }
    
    return true;
}


////////////////////////////////////////
//       PickNextCard
/*! Provides the next card on card pull on table
// \param BOOL* pbEnd : return BOOLean result if card are present 
*/
long cMazzo::PickNextCard(BOOL* pbEnd)
{
   long lResult = NOT_VALID_INDEX;
   size_t iNumEle = m_vctCards.size();
   if (m_lNextCard >= iNumEle)
   {
      *pbEnd = FALSE;
      return lResult; 
   }
   *pbEnd = TRUE;

   lResult = m_vctCards[m_lNextCard];
   m_lNextCard ++;

   return lResult;
}


////////////////////////////////////////
//       PickNextCard
/*! Provides the next card on card pull on table. Works as iterator and increment the stack index.
// \param CardSpec* pRes : returned cards
*/
BOOL cMazzo::PickNextCard(CardSpec* pRes)
{
    ASSERT(pRes);
    
    pRes->Reset();
    BOOL  bValid  = FALSE;
    
    size_t iNumEle = m_vctCards.size();
    if (m_lNextCard < iNumEle)
    {
        bValid = TRUE;
        long lIndex = m_vctCards[m_lNextCard];
        
        pRes->SetCardIndex(lIndex);    
        
        m_lNextCard ++;
    }
    else
    {
        // deck is terminated, why pick another card
        ASSERT(0);
    }
    

    return bValid;
}

////////////////////////////////////////
//       ThrowTableCard
/*! Make the "briscola" and provides the card index that lies on table (briscola)
*/
long cMazzo::ThrowTableCard()
{
    long lResult = NOT_VALID_INDEX;
    size_t iNumEle = m_vctCards.size();
    if (m_lNextCard >= iNumEle)
    {
        return lResult; 
    }

    lResult = m_vctCards[m_lNextCard];

                           // swap the next card with the last
    long lLast = m_vctCards[NUM_CARDS - 1]; 
    m_vctCards[NUM_CARDS - 1] = m_vctCards[m_lNextCard];
    m_vctCards[m_lNextCard] = lLast;

    return lResult; 
}


////////////////////////////////////////
//       TraceIt
/*! 
*/
void cMazzo::TraceIt()
{
    Utility::TraceContainer(m_vctCards, "Cards mazzo"); 
}


////////////////////////////////////////
//       IsMoreCards
/*! 
*/
bool cMazzo::IsMoreCards()
{
    bool bRet = false;
    if ( m_lNextCard < NUM_CARDS)
    {
        bRet = true;
    }
    return bRet;
}

////////////////////////////////////////
//       GetIndexNextCard
/*! Return the next card on top of the deck. No increment next card.
// \param BOOL* pbEnd : returned BOOLean result if card are present 
*/
long cMazzo::GetIndexNextCard(BOOL* pbEnd)
{
   long lResult = NOT_VALID_INDEX;
   if (m_lNextCard >= NUM_CARDS)
   {
      *pbEnd = FALSE;
      return lResult; 
   }
   *pbEnd = TRUE;

   lResult = m_vctCards[m_lNextCard];
   
   return lResult;
}


