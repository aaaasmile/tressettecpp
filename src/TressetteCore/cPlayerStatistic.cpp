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



//cPlayerStatistic.cpp
#include "StdAfx.h"
#include "cPlayerStatistic.h"


cPlayerStatistic::cPlayerStatistic()
{
    Reset();
}


////////////////////////////////////////
//       Reset
/*! Reset statistic to the initial values
*/
void cPlayerStatistic::Reset()
{
    for (int i = 0; i < NUM_SEEDS; i++)
    {
       bynStroz[i] = 2;
       bynRe[i] = 1;
       bynHorse[i] = 1;
       bynFanti[i] = 1;
    }

    lNumBrisc = 0;
    lNumCarac = 0;
    lNumHand = 0;
    lScore = 0;
    bynBriscHad = 0;
    bynPointsHad = 0;
    bynBriscFirstHad = 0 ;
    bynBriscPointsHad = 0;
    lCaracHad = 0;
    lRemNumBrisc = 10;
    lRemNumPoints = 120;
    lInHand_nBris = 0;
    lInHand_nCarac = 0;
    lInHand_nLisc = 0;

}


////////////////////////////////////////
//       Clone
/*! Clone this element
// \param cPlayerStatistic* pNew : destination pointer element
*/
void cPlayerStatistic::Clone(cPlayerStatistic* pNew) 
{
    ASSERT(pNew);
    pNew->lScore = lScore;
    pNew->lNumHand = lNumHand;
    pNew->lNumBrisc = lNumBrisc;
    pNew->lNumCarac = lNumCarac;
    for (int i = 0; i < NUM_SEEDS ; i++)
    {
        pNew->bynStroz[i] = bynStroz[i];
        pNew->bynRe[i] = bynRe[i];
        pNew->bynHorse[i] = bynHorse[i];
        pNew->bynFanti[i] = bynFanti[i];
    }
    pNew->lRemNumBrisc = lRemNumBrisc;
    pNew->lRemNumPoints = lRemNumPoints;
    pNew->eLastPlayed = eLastPlayed;
    pNew->bynBriscHad = bynBriscHad;
    pNew->bynPointsHad = bynPointsHad;
    pNew->bynBriscPointsHad = bynBriscPointsHad;
    pNew->bynBriscFirstHad = bynBriscFirstHad;
    pNew->lCaracHad = lCaracHad;
    pNew->lInHand_nBris = lInHand_nBris;
    pNew->lInHand_nCarac = lInHand_nCarac;
    pNew->lInHand_nLisc = lInHand_nLisc;
    pNew->lSegniWons = lSegniWons;
}

