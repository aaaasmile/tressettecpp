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



//CardSpec.h

#ifndef ___CARDSPEC_H_
#define ___CARDSPEC_H_


#include "AlgPlayerInterface.h"
#include "CoreEnv.h"

//! class CardSpec
class  CardSpec
{
public:

    CardSpec();
    virtual ~CardSpec(){};

    //! set the index of the card
    void    SetCardIndex(int itmpIndex);
    //! provides index
    int     GetCardIndex(){return m_CardInfo.byIndex;}
    //! provides suit
    eSUIT   GetSuit(){return m_CardInfo.eSuit;}
    //! provides card name
    LPCSTR  GetName(){return m_CardInfo.CardName;}
    //! provides the suit card name
    LPCSTR  GetSuitName(){return m_strSuitName.c_str();}
    //! assignement operator
    void operator = (const CardSpec &r); 
    //! compair operator
    bool operator == (const CardSpec &r){return m_CardInfo.byIndex == r.m_CardInfo.byIndex;}
    //! operator >
    bool operator > (const CardSpec &r){return m_CardInfo.iRank > r.m_CardInfo.iRank;}
    //! return true if a card is a liscio, false otherwise
    BOOL     IsLiscio(){if (m_CardInfo.iRank < 11) return TRUE; else return FALSE;}
    //! reset
    void    Reset();
    //! set symbol
    void    SetSymbol(int iVal){m_iSymbolIx = iVal;}
    //! get symbol information
    int     GetSymbol(){return m_iSymbolIx;}
    //! get card info pointer
    CARDINFO*  GetCardInfo(){return &m_CardInfo;}
    //! set card info
    void       SetCardInfo(CARDINFO& Card);
    //! provides information structure
    void       FillInfo(CARDINFO* pCardInfo);

public:
    //! card info
    CARDINFO   m_CardInfo;

private:
    //! symbol index
    int        m_iSymbolIx;
    //! suit name
    STRING     m_strSuitName;
    //! card letter
    char       chCardLetter;
    //! suit letter
    char       chSuitLetter;
    //! card points
    BYTE       byPoints;
};


typedef std::vector<CardSpec> VCT_CARDSPEC;
typedef std::vector<char>                       VCT_SINGLECARD;
typedef std::vector<char>::iterator             IT_SINGLE_CARD;
typedef std::vector<VCT_SINGLECARD>::iterator   IT_SINGLE_HAND;



#endif
