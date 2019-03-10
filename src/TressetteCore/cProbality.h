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



//cProbality.h

#ifndef __CPROBABILITY_H____
#define __CPROBABILITY_H____

#include "CoreEnv.h"

#include "cMazzo.h"
#include "CardSpec.h"

typedef std::vector<VCT_SINGLECARD>             MTX_HANDCOMBI;


/////////////////////////////////////////////////////////////////////////////////////
// *********************************     CPROBABILITY CLASS  ************************
/////////////////////////////////////////////////////////////////////////////////////


//! class cProbality
/**
// class used to calculate probability correlated to the game
*/
class cProbality
{
public:
    cProbality(){m_bIndexNotInit = true;m_iCardOnHand = 3;}

    //! develop all hand possibile hands with the cards on deck
    void SvilCombiHands(VCT_MAZZO &vct_Mazzo);
    //! coefficiente binomiale 
    double BinomialCoef(long lN, long lK);
    //! fattoriale
    double Fattorial(long lN);
    //! clear developed hands
    void   Clear();
    //! check the brsc freq prob
    void   CheckBriscFreq(int iIndexBris, int* piRes);


    // operators
   friend std::ostream &operator << (std::ostream &stream, const MTX_HANDCOMBI &o);

private:
    //! status indici inizializzati
    bool            m_bIndexNotInit;
    //! indici di sviluppo sistema (da usare per sviluppare il sistema in tempi diversi)
    VCT_LONG        m_vctCounter;
    //! cards on hand
    int             m_iCardOnHand;
    //! developed hands
    MTX_HANDCOMBI   m_mtxAllHands;

};


#endif
