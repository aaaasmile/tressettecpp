

// cCardItem.h: interface for the cCardItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCARDITEM_H__1F659C33_A31B_4EE8_BC51_1456F440E7F1__INCLUDED_)
#define AFX_CCARDITEM_H__1F659C33_A31B_4EE8_BC51_1456F440E7F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InfoComm.h"
#include <string>
#include "ConstSearchAlpha.h"
#include <deque>

//! class cCardItem
class cCardItem  
{
    
public:
	cCardItem();
	virtual ~cCardItem();

    void SetCardIndex(int itmpIndex);
    static int LetterToIndex(char lett);
    static int CardCompareSbF(cCardItem* pFirst, cCardItem* pSecond);

public:
    CARDINFO   CardInfo;
    char       CardLetter;
    char       SeedLetter;
    BYTE       Points;

private:
    std::string m_strSeedName;

};

typedef cCardItem* P_MYCARDITEM;
typedef std::deque<P_MYCARDITEM> CARDLIST; 
typedef CARDLIST::iterator CARDLIST_IT;


// Functor to sort the card list in ascending manner
class cmp2CardAscen
{
public:
    bool operator ()(const P_MYCARDITEM& Card_1, const P_MYCARDITEM& Card_2) const
    {
        if (Card_1->CardInfo.eSeed > Card_2->CardInfo.eSeed  )
        {
            // swap element
            return true;
        }
        else if (Card_1->CardInfo.eSeed == Card_2->CardInfo.eSeed)
        {
            if (Card_1->CardInfo.iRank > Card_2->CardInfo.iRank)
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
};

// Functor to sort the card list in descending manner. Using suit campare (same suit)
class cmp2CardDesc
{
public:
    bool operator ()(const P_MYCARDITEM& Card_1, const P_MYCARDITEM& Card_2) const
    {
        if (Card_1->CardInfo.eSeed < Card_2->CardInfo.eSeed  )
        {
            // swap element
            return true;
        }
        else if (Card_1->CardInfo.eSeed == Card_2->CardInfo.eSeed)
        {
            if (Card_1->CardInfo.iRank < Card_2->CardInfo.iRank)
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
};

// Functor to sort the card list in descending manner. Use only card value no matter wat the suite
class cmp2CardDescOnlyValue
{
public:
    bool operator ()(const P_MYCARDITEM& Card_1, const P_MYCARDITEM& Card_2) const
    {
        if (Card_1->Points < Card_2->Points)
        {
            // bigger card, swap
            return true;
        }
        else if (Card_1->Points == Card_2->Points)
        {
            if (Card_1->CardInfo.iRank < Card_2->CardInfo.iRank)
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
            return false;
        }       
    }
};

//! class cBestLine 
class cBestLine
{
public:
    cBestLine(){}
    void Clear(){m_CardListBest.clear(); m_vctPlayerList.clear();}

    CARDLIST  m_CardListBest;
    VCT_INT   m_vctPlayerList;

};

#endif // !defined(AFX_CCARDITEM_H__1F659C33_A31B_4EE8_BC51_1456F440E7F1__INCLUDED_)


