//AlgCompareFunct.h

#ifndef _ALGCOMPAREFUNCT____H_
#define _ALGCOMPAREFUNCT____H_

//!Functor to compare 2 cardinfo structure
class cmpCardOnIndex
{
    typedef CARDINFO* PCARDINFO;
public:
    // constructor
    explicit cmpCardOnIndex(const PCARDINFO vct_val)
    {
        vct_MazzoInHand = vct_val;
    }

    // sort cards in descending mode (3,2,1,re,...) and spade, denari, coppe, bastoni
    bool operator ()(const int iIndex_1, const int iIndex_2) const
    {
        CARDINFO Card_1 = vct_MazzoInHand[iIndex_1];
        CARDINFO Card_2 = vct_MazzoInHand[iIndex_2];

        if (Card_1.eSuit > Card_2.eSuit  )
        {
            // swap element
            return true;
        }
        else if (Card_1.eSuit == Card_2.eSuit)
        {
            int iVal_1 = g_RankTable[Card_1.byIndex];
            int iVal_2 = g_RankTable[Card_2.byIndex];
            if (iVal_1 > iVal_2)
            {
                // bigger card, swap
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            // don't swap
            return false;
        }
    }
private:
    PCARDINFO   vct_MazzoInHand;
};

//! Functor to compare 2 list of card indexes to order it on size
class cmpListOnSize
{
public: 
    cmpListOnSize(){}
    //! sort list in descending mode
    bool operator ()(const VCT_INT* pList1, const VCT_INT* pList2) const
    {
        if (pList1->size() > pList2->size())
        {
            // swap it
            return true;
        }
        else
        {
            return false;
        }
    }

};



#endif

