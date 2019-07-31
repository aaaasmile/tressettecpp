// AlgSupport.cpp
#include "StdAfx.h"
#include "win_type_global.h"
#include "AlgSupport.h"

////////////////////////////////////////
//       GetAvailbDeclGoodGames
/*! Provides good game declarations
// \param VCT_CARDINFO& vctCardInHand : card in a hand to be analized
// \param VCT_GOODGAMEDETAIL& vctGoodGameRec : good game list result
*/
void AlgSupport::GetAvailbDeclGoodGames(VCT_CARDINFO& vctCardInHand, VCT_GOODGAMEDETAIL& vctGoodGameRec)
{

    size_t iNumOfCards = vctCardInHand.size();
    VCT_INT vctInHand_Bastoni;
    VCT_INT vctInHand_Spade;
    VCT_INT vctInHand_Coppe;
    VCT_INT vctInHand_Denari;
	UINT i;
    for (i = 0; i < iNumOfCards; i++)
    {
        if (vctCardInHand[i].eSeed == BASTONI)
        {
            vctInHand_Bastoni.push_back(i);
        }
        else if (vctCardInHand[i].eSeed == SPADE)
        {
            vctInHand_Spade.push_back(i);
        }
        else if (vctCardInHand[i].eSeed == COPPE)
        {
            vctInHand_Coppe.push_back(i);
        }
        else if (vctCardInHand[i].eSeed == DENARI)
        {
            vctInHand_Denari.push_back(i);
        }
    }

    int iNumDue = 0;
    int iNumTre = 0;
    int iNumAssi = 0;
    eSUIT eSegnoMancAsso = UNDEF;
    eSUIT eSegnoMancDue = UNDEF;
    eSUIT eSegnoMancTre = UNDEF;
    BOOL bDue = FALSE;
    BOOL bAsso = FALSE;
    BOOL bTre = FALSE;
    BOOL bNapolaSpade = FALSE;
    BOOL bNapolaDenari = FALSE;
    BOOL bNapolaCoppe = FALSE;
    BOOL bNapolaBastoni = FALSE;

    // look on bastoni
    for ( i = 0; i < vctInHand_Bastoni.size(); i++)
    {
        CARDINFO CardCurr = vctCardInHand[vctInHand_Bastoni[i]]; 
        if ( CardCurr.byIndex == 0 )
        {
            iNumAssi++;
            bAsso = TRUE;
            
        }
        else if (CardCurr.byIndex == 1)
        {
            iNumDue++;
            bDue = TRUE;
        }
        else if (CardCurr.byIndex == 2)
        {
            iNumTre++;
            bTre = TRUE;
        }
    }
    if (bAsso && bDue && bTre)
    {
        bNapolaBastoni = TRUE;
    }
    if (!bAsso)
    {
        eSegnoMancAsso = BASTONI;
    }
    if (!bDue)
    {
        eSegnoMancDue = BASTONI;
    }
    if (!bTre)
    {
        eSegnoMancTre = BASTONI;
    }

    // look on coppe
    bDue = FALSE;
    bAsso = FALSE;
    bTre = FALSE;
    for ( i = 0; i < vctInHand_Coppe.size(); i++)
    {
        CARDINFO CardCurr = vctCardInHand[vctInHand_Coppe[i]]; 
        if ( CardCurr.byIndex == 10 )
        {
            iNumAssi++;
            bAsso = TRUE;
        }
        else if (CardCurr.byIndex == 11)
        {
            iNumDue++;
            bDue = TRUE;
        }
        else if (CardCurr.byIndex == 12)
        {
            iNumTre++;
            bTre = TRUE;
        }
    }
    if (bAsso && bDue && bTre)
    {
        bNapolaCoppe = TRUE;
    }
    if (!bAsso)
    {
        eSegnoMancAsso = COPPE;
    }
    if (!bDue)
    {
        eSegnoMancDue = COPPE;
    }
    if (!bTre)
    {
        eSegnoMancTre = COPPE;
    }


    // look on denari
    bDue = FALSE;
    bAsso = FALSE;
    bTre = FALSE;
    for ( i = 0; i < vctInHand_Denari.size(); i++)
    {
        CARDINFO CardCurr = vctCardInHand[vctInHand_Denari[i]]; 
        if ( CardCurr.byIndex == 20 )
        {
            iNumAssi++;
            bAsso = TRUE;
        }
        else if (CardCurr.byIndex == 21)
        {
            iNumDue++;
            bDue = TRUE;
        }
        else if (CardCurr.byIndex == 22)
        {
            iNumTre++;
            bTre = TRUE;
        }
    }
    if (bAsso && bDue && bTre)
    {
        bNapolaDenari = TRUE;
    }
    if (!bAsso)
    {
        eSegnoMancAsso = DENARI;
    }
    if (!bDue)
    {
        eSegnoMancDue = DENARI;
    }
    if (!bTre)
    {
        eSegnoMancTre = DENARI;
    }

    // look on spade
    bDue = FALSE;
    bAsso = FALSE;
    bTre = FALSE;
    for ( i = 0; i < vctInHand_Spade.size(); i++)
    {
        CARDINFO CardCurr = vctCardInHand[vctInHand_Spade[i]]; 
        if ( CardCurr.byIndex == 30 )
        {
            iNumAssi++;
            bAsso = TRUE;
        }
        else if (CardCurr.byIndex == 31)
        {
            iNumDue++;
            bDue = TRUE;
        }
        else if (CardCurr.byIndex == 32)
        {
            iNumTre++;
            bTre = TRUE;
        }
    }
    if (bAsso && bDue && bTre)
    {
        bNapolaSpade = TRUE;
    }
    if (!bAsso)
    {
        eSegnoMancAsso = SPADE;
    }
    if (!bDue)
    {
        eSegnoMancDue = SPADE;
    }
    if (!bTre)
    {
        eSegnoMancTre = SPADE;
    }

    // store available declarations
    GoodGameDetail currDecl;
    if (iNumDue == 3)
    {
        currDecl.eGGval = TRE_DUE;
        currDecl.eSManca = eSegnoMancDue;
        vctGoodGameRec.push_back(currDecl);
    }
    else if (iNumDue == 4)
    {
        currDecl.eGGval = QUATTRO_DUE;
        currDecl.eSManca = UNDEF;
        vctGoodGameRec.push_back(currDecl);
    }
    if (iNumTre == 3)
    {
        currDecl.eGGval = TRE_TRE;
        currDecl.eSManca = eSegnoMancTre;
        vctGoodGameRec.push_back(currDecl);
    }
    else if (iNumTre == 4)
    {
        currDecl.eGGval = QUATTRO_TRE;
        currDecl.eSManca = UNDEF;
        vctGoodGameRec.push_back(currDecl);
    }
    if (iNumAssi == 3)
    {
        currDecl.eGGval = TRE_ASSI;
        currDecl.eSManca = eSegnoMancAsso;
        vctGoodGameRec.push_back(currDecl);
    }
    else if (iNumAssi == 4)
    {
        currDecl.eGGval = QUATTRO_ASSI;
        currDecl.eSManca = UNDEF;
        vctGoodGameRec.push_back(currDecl);
    }

    if (bNapolaBastoni)
    {
        currDecl.eGGval = NAPOLETANA;
        currDecl.eSManca = BASTONI;
        vctGoodGameRec.push_back(currDecl);
    }
    if (bNapolaCoppe)
    {
        currDecl.eGGval = NAPOLETANA;
        currDecl.eSManca = COPPE;
        vctGoodGameRec.push_back(currDecl);
    }
    if (bNapolaDenari)
    {
        currDecl.eGGval = NAPOLETANA;
        currDecl.eSManca = DENARI;
        vctGoodGameRec.push_back(currDecl);
    }
    if (bNapolaSpade)
    {
        currDecl.eGGval = NAPOLETANA;
        currDecl.eSManca = SPADE;
        vctGoodGameRec.push_back(currDecl);
    }
}

////////////////////////////////////////
//       BinomialCoef
/*! Coefficiente binomiale
// \param long lN : numero di elementi
// \param long lK : classe
*/
double AlgSupport::BinomialCoef(long lN, long lK)
{
   double dResult = 0.0;
   double dNum, dDen;

   dNum = Fattorial(lN);
   dDen = Fattorial(lN - lK) * Fattorial(lK);

   dResult = dNum / dDen;

   return dResult;
}

////////////////////////////////////////
//       Fattorial
/*! Fattoriale di n elementi 
// \param long lN : numero degli elementi
*/
double AlgSupport::Fattorial(long lN)
{
   double dResult = 1.0;

   for (long i = 0; i < lN - 1; i++)
   {
      dResult *= lN - i;
   }
   
   return dResult;
}


////////////////////////////////////////
//       GetPartnerIndex
/*! Provides the index of the partner
// \param int iPlayerIndex : index of the player that make the request
*/
int  AlgSupport::GetPartnerIndex(int iPlayerIndex)
{ 
    if (iPlayerIndex == PLAYER1) return PLAYER3;
    if (iPlayerIndex == PLAYER2) return PLAYER4;
    if (iPlayerIndex == PLAYER3) return PLAYER1;
    if (iPlayerIndex == PLAYER4) return PLAYER2; 
    return NOT_VALID_INDEX;
}


