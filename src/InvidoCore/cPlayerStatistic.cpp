

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

