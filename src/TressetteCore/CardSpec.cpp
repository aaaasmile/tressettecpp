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
        m_CardInfo.eSuit = BASTONI;
        m_strSuitName = g_SuitName[BASTONI];
    }
    else if (m_CardInfo.byIndex >= 10 && m_CardInfo.byIndex < 20 )
    {
        m_CardInfo.eSuit = COPPE;
        m_strSuitName = g_SuitName[COPPE];
    }
    else if (m_CardInfo.byIndex >= 20 && m_CardInfo.byIndex < 30 )
    {
        m_CardInfo.eSuit = DENARI;
        m_strSuitName = g_SuitName[DENARI];
    }
    else if (m_CardInfo.byIndex  >= 30 && m_CardInfo.byIndex < 40 )
    {
        m_CardInfo.eSuit = SPADE;
        m_strSuitName = g_SuitName[SPADE];
    }
    else
    {
        m_CardInfo.eSuit = UNDEF;
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
    m_CardInfo.eSuit = r.m_CardInfo.eSuit; 
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
    m_CardInfo.eSuit = UNDEF;
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
    m_CardInfo.eSuit = Card.eSuit;   
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
    pCardInfo->eSuit = m_CardInfo.eSuit;  
    pCardInfo->iRank = m_CardInfo.iRank ;
}


