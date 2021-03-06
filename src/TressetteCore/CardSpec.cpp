

// CardSpec.cpp
#include "StdAfx.h"
#include "CardSpec.h"



////////////////////////////////////////
//       CardSpec
/*! Contructor
*/
CardSpec::CardSpec()
{
   Reset();
}

////////////////////////////////////////
//       SetCardIndex
/*! Adjust index and seed from card index
// \param long itmpIndex : index of 40 cards mazzo
*/
void CardSpec::SetCardIndex(int itmpIndex)
{
    if (itmpIndex >= 0 && itmpIndex <= NUM_CARDS_MAZZBRI)
    {
        m_CardInfo.byIndex = itmpIndex;
        m_CardInfo.iRank = g_RankTable[itmpIndex];
        chCardLetter = g_LetterName[itmpIndex];
        byPoints = g_PointsTable[itmpIndex];
    }
    else
    {
        return;
    }

    if (itmpIndex >= 0 && itmpIndex < NUM_CARDS_MAZZBRI)
    {
        strcpy(m_CardInfo.CardName, const_cast<CHAR*>(g_CardsNameX[itmpIndex].c_str()) );
    }

    if (m_CardInfo.byIndex >= 0 && m_CardInfo.byIndex < 10 )
    {
        m_CardInfo.eSeed = BASTONI;
        m_strSuitName = g_SuitName[BASTONI];
    }
    else if (m_CardInfo.byIndex >= 10 && m_CardInfo.byIndex < 20 )
    {
        m_CardInfo.eSeed = COPPE;
        m_strSuitName = g_SuitName[COPPE];
    }
    else if (m_CardInfo.byIndex >= 20 && m_CardInfo.byIndex < 30 )
    {
        m_CardInfo.eSeed = DENARI;
        m_strSuitName = g_SuitName[DENARI];
    }
    else if (m_CardInfo.byIndex  >= 30 && m_CardInfo.byIndex < 40 )
    {
        m_CardInfo.eSeed = SPADE;
        m_strSuitName = g_SuitName[SPADE];
    }
    else
    {
        m_CardInfo.eSeed = UNDEF;
        m_strSuitName = g_SuitName[UNDEF];
    }
}


////////////////////////////////////////
//       = 
/*! Assign operator
// \param const CardSpec &r : 
*/
void CardSpec::operator = (const CardSpec &r)
{
    strncpy(m_CardInfo.CardName, r.m_CardInfo.CardName, NUM_BYTE_NAME);
    m_CardInfo.byIndex = r.m_CardInfo.byIndex;
    m_CardInfo.eSeed = r.m_CardInfo.eSeed; 
    m_iSymbolIx = r.m_iSymbolIx;
    m_CardInfo.iRank = r.m_CardInfo.iRank ; 
    m_strSuitName = r.m_strSuitName;
}


////////////////////////////////////////
//       Reset
/*! Reset the card info
*/
void CardSpec::Reset()
{
    m_CardInfo.byIndex = NOT_VALID_INDEX;
    m_CardInfo.CardName[0] = '\0';
    m_CardInfo.eSeed = UNDEF;
    m_iSymbolIx = 0;
    m_strSuitName = "";
    m_CardInfo.iRank = 0;
}


////////////////////////////////////////
//       SetCardInfo
/*! Set the info detail of card info structure
// \param CARDINFO& Card : input structure 
*/
void  CardSpec::SetCardInfo(CARDINFO& Card)
{
    strncpy(m_CardInfo.CardName, Card.CardName, NUM_BYTE_NAME);
    m_CardInfo.byIndex = Card.byIndex;
    m_CardInfo.eSeed = Card.eSeed;   
    m_CardInfo.iRank = Card.iRank ;
}



////////////////////////////////////////
//       FillInfo
/*! Provides information structure 
*/
void CardSpec::FillInfo(CARDINFO* pCardInfo)
{
    ASSERT(pCardInfo);
    strncpy(pCardInfo->CardName, m_CardInfo.CardName, NUM_BYTE_NAME);
    pCardInfo->byIndex = m_CardInfo.byIndex;
    pCardInfo->eSeed = m_CardInfo.eSeed;  
    pCardInfo->iRank = m_CardInfo.iRank ;
}

int CardSpec::CardCompareSbF(CardSpec* pFirst, CardSpec* pSecond)
{
    int iRet = 0;
    if (pFirst->m_CardInfo.eSeed == pSecond->m_CardInfo.eSeed)
    {
        if (pFirst->m_CardInfo.iRank < pSecond->m_CardInfo.iRank)
        {
            iRet = 1;
        }
        else if (pFirst->m_CardInfo.iRank == pSecond->m_CardInfo.iRank)
        {
            iRet = 0;
        }
        else
        {
            iRet = -1;
        }
    }
    else
    {
        iRet = -1;
    }
    return iRet;
}


