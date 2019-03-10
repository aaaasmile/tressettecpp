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

// cAlgDefault.cpp: implementation of the cAlgDefault class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "cAlgDefault.h"
#include "cSettings.h"
#include "cAlgABSolver.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace AlgSupport;

// hand information on suit
static AlgSupport::HandInfo tableHandInfo[] = 
{
    // 10-0-0-0
    {_10_0_0_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 9-1-0-0
    {_9_1_0_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 8-2-0-0
    {_8_2_0_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 8-1-1-0
    {_8_1_1_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 7-3-0-0
    {_7_3_0_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 7-2-1-0
    {_7_2_1_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 7-1-1-1
    {_7_1_1_1,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF},
    // 6-4-0-0
    {_6_4_0_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 6-3-1-0
    {_6_3_1_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 6-2-2-0
    {_6_2_2_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 6-2-1-1
    {_6_2_1_1,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 5-5-0-0
    {_5_5_0_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 5-4-1-0
    {_5_4_1_0,MOLTOFORTE,MOLTO_SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 5-3-2-0
    {_5_3_2_0,FORTE,SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 5-3-1-1
    {_5_3_1_1,FORTE,SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 5-2-2-1
    {_5_2_2_1,FORTE,SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 4-4-2-0
    {_4_4_2_0,FORTE,SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 4-4-1-1
    {_4_4_1_1,FORTE,SBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 4-3-3-0
    {_4_3_3_0,ATTACCO,SEMIBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 4-3-2-1
    {_4_3_2_1,ATTACCO,SEMIBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 4-2-2-2
    {_4_2_2_2,ATTACCO,SEMIBILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 3-3-3-1
    {_3_3_3_1,DEBOLE,BILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}, 
    // 3-3-2-2
    {_3_3_2_2,DEBOLE,BILANCIATA,0,0,0,0,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,PIZZ_NONE,NOTDEF,NOTDEF,NOTDEF,NOTDEF}
};

////////////////////////////////////////
//       cAlgDefault
/*! Constructor
*/
cAlgDefault::cAlgDefault()
{
    m_pCoreGame = 0;
    m_iMyIndex = NOT_VALID_INDEX;
    m_iTrickRound = 0;
    m_eLocal = LT_NEUTRO;

    // fill the map to get an entry in the table hand info
    m_mapHandInfo["10-0-0-0"] =  &tableHandInfo[0];
    m_mapHandInfo["9-1-0-0"] =  &tableHandInfo[1];
    m_mapHandInfo["8-2-0-0"] =  &tableHandInfo[2];
    m_mapHandInfo["8-1-1-0"] =  &tableHandInfo[3];
    m_mapHandInfo["7-3-0-0"] =  &tableHandInfo[4];
    m_mapHandInfo["7-2-1-0"] =  &tableHandInfo[5];
    m_mapHandInfo["7-1-1-1"] =  &tableHandInfo[6];
    m_mapHandInfo["6-4-0-0"] =  &tableHandInfo[7];
    m_mapHandInfo["6-3-1-0"] =  &tableHandInfo[8];
    m_mapHandInfo["6-2-2-0"] =  &tableHandInfo[9];
    m_mapHandInfo["6-2-1-1"] =  &tableHandInfo[10];
    m_mapHandInfo["5-5-0-0"] =  &tableHandInfo[11];
    m_mapHandInfo["5-4-1-0"] =  &tableHandInfo[12];
    m_mapHandInfo["5-3-2-0"] =  &tableHandInfo[13];
    m_mapHandInfo["5-3-1-1"] =  &tableHandInfo[14];
    m_mapHandInfo["5-2-2-1"] =  &tableHandInfo[15];
    m_mapHandInfo["4-4-2-0"] =  &tableHandInfo[16];
    m_mapHandInfo["4-4-1-1"] =  &tableHandInfo[17];
    m_mapHandInfo["4-3-3-0"] =  &tableHandInfo[18];
    m_mapHandInfo["4-3-2-1"] =  &tableHandInfo[19];
    m_mapHandInfo["4-2-2-2"] =  &tableHandInfo[20];
    m_mapHandInfo["3-3-3-1"] =  &tableHandInfo[21];
    m_mapHandInfo["3-3-2-2"] =  &tableHandInfo[22];

    m_pABSolver = 0;
}


////////////////////////////////////////
//       ~cAlgDefault
/*! Destructor
*/
cAlgDefault::~cAlgDefault()
{
    if (m_pABSolver)
    {
        delete m_pABSolver;
        m_pABSolver = 0;
    }
}


////////////////////////////////////////
//       ALG_SetCoreInterface
/*! 
// \param I_CORE_Game* pCore : 
*/
void cAlgDefault::ALG_SetCoreInterface(I_CORE_Game* pCore)
{
    m_pCoreGame = pCore;
}


////////////////////////////////////////
//       ALG_SetPlayerIndex
/*! set player index
// \param int iIndex : 
*/
void cAlgDefault::ALG_SetPlayerIndex(int iIndex) 
{
    m_iMyIndex = iIndex;
}

////////////////////////////////////////
//       ALG_NewMatch
/*! new match notification
// \param int iNumPlayer : 
*/
void cAlgDefault::ALG_NewMatch(int iNumPlayer) 
{
    newAlgSolver();
    m_eLocal = (eTypeLocal)g_Options.Match.iLocalGameType;   
}


////////////////////////////////////////
//       calculateSuiteIndexes
/*! calculate suite indexes
*/
void cAlgDefault::calculateSuiteIndexes()
{
    m_vctInHand_Bastoni.clear();
    m_vctInHand_Denari.clear();
    m_vctInHand_Coppe.clear();
    m_vctInHand_Spade.clear();
    
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        if ( m_arrCardAllPlayers[m_iMyIndex][i].byIndex == NOT_VALID_INDEX)
        {
            continue;
        }
        
        // store indexes in suit list
        if (m_arrCardAllPlayers[m_iMyIndex][i].eSuit == BASTONI)
        {
            m_vctInHand_Bastoni.push_back(i);
        }
        else if (m_arrCardAllPlayers[m_iMyIndex][i].eSuit == SPADE)
        {
            m_vctInHand_Spade.push_back(i);
        }
        else if (m_arrCardAllPlayers[m_iMyIndex][i].eSuit == COPPE)
        {
            m_vctInHand_Coppe.push_back(i);
        }
        else if (m_arrCardAllPlayers[m_iMyIndex][i].eSuit == DENARI)
        {
            m_vctInHand_Denari.push_back(i);
        }
    }
    // sort all list in order to have a descending list
    std::sort(m_vctInHand_Spade.begin(), m_vctInHand_Spade.end(), cmpCardOnIndex(m_arrCardAllPlayers[m_iMyIndex]) );
    std::sort(m_vctInHand_Bastoni.begin(), m_vctInHand_Bastoni.end(), cmpCardOnIndex(m_arrCardAllPlayers[m_iMyIndex]) );
    std::sort(m_vctInHand_Coppe.begin(), m_vctInHand_Coppe.end(), cmpCardOnIndex(m_arrCardAllPlayers[m_iMyIndex]) );
    std::sort(m_vctInHand_Denari.begin(), m_vctInHand_Denari.end(), cmpCardOnIndex(m_arrCardAllPlayers[m_iMyIndex]) );

}

////////////////////////////////////////
//       ALG_NewGiocata
/*! new giocata notification
// \param CARDINFO* pCardArray : hand card array 
// \param int iNumOfCards : number of cards in the hand
// \param int iPlayerIx : Player that start the giocata
*/
void cAlgDefault::ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) 
{
    ASSERT(m_iMyIndex != NOT_VALID_INDEX);
    ASSERT(m_pABSolver);

    m_vctCardsPlayedTricks.clear();
    m_iTrickRound = 0;
    m_currTrickInfo.Reset(); 

    if (iNumOfCards == NUM_CARDS_HAND)
    {
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            // store the card
            m_arrCardAllPlayers[m_iMyIndex][i] = pCardArray[i];
        }
        calculateSuiteIndexes();
        
        if (g_Options.All.iDebugLevel > 5 )
        {
            traceAllCardInHand("--- After sort, card in hand:----\n");
        }
        // retrive hand force
        MTX_PINDEX mtxPIndex;
        orderSuitListOnFreq(mtxPIndex);
        CHAR buff[64];
        int iCountIndexes = mtxPIndex[0]->size() + mtxPIndex[1]->size() + 
                            mtxPIndex[2]->size() + mtxPIndex[3]->size();

        if ( iCountIndexes == NUM_CARDS_HAND)
        {
            sprintf(buff, "%d-%d-%d-%d", (mtxPIndex[0])->size(), 
                                 (mtxPIndex[1])->size(), (mtxPIndex[2])->size(), (mtxPIndex[3])->size());
            STRING strKey = buff;
            m_currHandInfo = *(m_mapHandInfo[strKey]);

            // calculate pizzico number
            calculatePizzOnHand();

            m_firstHandInfo = m_currHandInfo;

            // cards of other user
            otherPlayersCardRandom();
            // prepare cards at the begin of the trick
            copyCardsBeginTrick();

            for (int j = 0; j < MAX_NUM_PLAYER; j++ )
            {
                // setup the alphabeta alg
                m_pABSolver->SetHands(j,  &m_arrCardAllPlayers[j][0], NUM_CARDS_HAND);
            }
            m_pABSolver->SetInitialPlayer( iPlayerIx );
        }
        else
        {
            // program error
            ASSERT(0);
        }

    }
    else
    {
        // program error
        ASSERT(0);
    }
}


////////////////////////////////////////
//       copyCardsBeginTrick
/*! Copy cards of all players in the begin trick card array 
*/
void cAlgDefault::copyCardsBeginTrick()
{
    for (int i = 0; i < MAX_NUM_PLAYER; i++)
    {
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
            m_arrCardAllTrickInit[i][j] = m_arrCardAllPlayers[i][j];
        }
    }
}


////////////////////////////////////////
//       calculatePizzOnHand
/*! hand info: calculate pizzichi distribution
*/
void cAlgDefault::calculatePizzOnHand()
{
    BOOL bTre = FALSE;
    BOOL bDue = FALSE;
    BOOL bAsso =  FALSE;
    m_currHandInfo.iNum3 = 0;
    m_currHandInfo.iNum2 = 0;
    m_currHandInfo.iNum1 = 0;
    m_currHandInfo.iNumOfPizzichi = 0;


    // bastoni
    m_currHandInfo.ePizzOnBastoni = PIZZ_NONE;
    checkListBigCards(&m_vctInHand_Bastoni, bTre, bDue, bAsso);
    if (bTre && bDue && bAsso)
    {
        m_currHandInfo.ePizzOnBastoni = NAPOLA;
    }
    else if (bTre && bDue)
    {
        m_currHandInfo.ePizzOnBastoni = VENTICINQUE;
    }
    else if (bTre && bAsso)
    {
        m_currHandInfo.ePizzOnBastoni = VENTINOVE;
    }
    else if (bDue && bAsso)
    {
        m_currHandInfo.ePizzOnBastoni = VENTOTTO;
    }
    else if (bTre)
    {
        m_currHandInfo.iNum3 ++;
        m_currHandInfo.iNumOfPizzichi ++;
        m_currHandInfo.ePizzOnBastoni = TRE;
    }
    else if(bDue)
    {
        m_currHandInfo.iNum2 ++;
        m_currHandInfo.iNumOfPizzichi ++;
        m_currHandInfo.ePizzOnBastoni = DUE;
    }
    else if(bAsso)
    {
        m_currHandInfo.iNum1 ++;
        m_currHandInfo.iNumOfPizzichi ++;
        m_currHandInfo.ePizzOnBastoni = ASSO;
    }
    // denari
    bTre = FALSE;
    bDue = FALSE;
    bAsso =  FALSE;
    m_currHandInfo.ePizzOnDenari = PIZZ_NONE;
    checkListBigCards(&m_vctInHand_Denari, bTre, bDue, bAsso);
    if (bTre && bDue && bAsso)
    {
        m_currHandInfo.ePizzOnDenari = NAPOLA;
    }
    else if (bTre && bDue)
    {
        m_currHandInfo.ePizzOnDenari = VENTICINQUE;
    }
    else if (bTre && bAsso)
    {
        m_currHandInfo.ePizzOnDenari = VENTINOVE;
    }
    else if (bDue && bAsso)
    {
        m_currHandInfo.ePizzOnDenari = VENTOTTO;
    }
    else if (bTre)
    {
        m_currHandInfo.iNum3 ++;
        m_currHandInfo.iNumOfPizzichi ++;
        m_currHandInfo.ePizzOnDenari = TRE;
    }
    else if(bDue)
    {
        m_currHandInfo.iNum2 ++;
        m_currHandInfo.iNumOfPizzichi ++;
        m_currHandInfo.ePizzOnDenari = DUE;
    }
    else if(bAsso)
    {
        m_currHandInfo.iNum1 ++;
        m_currHandInfo.iNumOfPizzichi ++;
        m_currHandInfo.ePizzOnDenari = ASSO;
    }
    // coppe
    bTre = FALSE;
    bDue = FALSE;
    bAsso =  FALSE;
    m_currHandInfo.ePizzOnCoppe = PIZZ_NONE;
    checkListBigCards(&m_vctInHand_Coppe, bTre, bDue, bAsso);
    if (bTre && bDue && bAsso)
    {
        m_currHandInfo.ePizzOnCoppe = NAPOLA;
    }
    else if (bTre && bDue)
    {
        m_currHandInfo.ePizzOnCoppe = VENTICINQUE;
    }
    else if (bTre && bAsso)
    {
        m_currHandInfo.ePizzOnCoppe = VENTINOVE;
    }
    else if (bDue && bAsso)
    {
        m_currHandInfo.ePizzOnCoppe = VENTOTTO;
    }
    else if (bTre)
    {
        m_currHandInfo.ePizzOnCoppe = TRE;
        m_currHandInfo.iNum3 ++;
        m_currHandInfo.iNumOfPizzichi ++;
    }
    else if(bDue)
    {
        m_currHandInfo.ePizzOnCoppe = DUE;
        m_currHandInfo.iNum2 ++;
        m_currHandInfo.iNumOfPizzichi ++;
    }
    else if(bAsso)
    {
        m_currHandInfo.ePizzOnCoppe = ASSO;
        m_currHandInfo.iNum1 ++;
        m_currHandInfo.iNumOfPizzichi ++;
    }
    // spade
    bTre = FALSE;
    bDue = FALSE;
    bAsso =  FALSE;
    m_currHandInfo.ePizzOnSpade = PIZZ_NONE;
    checkListBigCards(&m_vctInHand_Spade, bTre, bDue, bAsso);
    if (bTre && bDue && bAsso)
    {
        m_currHandInfo.ePizzOnSpade  = NAPOLA;
    }
    else if (bTre && bDue)
    {
        m_currHandInfo.ePizzOnSpade = VENTICINQUE;
    }
    else if (bTre && bAsso)
    {
        m_currHandInfo.ePizzOnSpade = VENTINOVE;
    }
    else if (bDue && bAsso)
    {
        m_currHandInfo.ePizzOnSpade = VENTOTTO;
    }
    else if (bTre)
    {
        m_currHandInfo.ePizzOnSpade  = TRE;
        m_currHandInfo.iNum3 ++;
        m_currHandInfo.iNumOfPizzichi ++;
    }
    else if(bDue)
    {
        m_currHandInfo.ePizzOnSpade  = DUE;
        m_currHandInfo.iNum2 ++;
        m_currHandInfo.iNumOfPizzichi ++;
    }
    else if(bAsso)
    {
        m_currHandInfo.ePizzOnSpade  = ASSO;
        m_currHandInfo.iNum1 ++;
        m_currHandInfo.iNumOfPizzichi ++;
    }
}

////////////////////////////////////////
//       otherPlayersCardRandom
/*! Distribuite cards to other players randomly
*/
void cAlgDefault::otherPlayersCardRandom()
{
    VCT_INT vctCards;
    for (int i = 0; i < NUM_CARDS_MAZZBRI; i++)
    {
        BOOL bCardAlreadyInDeck = FALSE;
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
            if ( i == m_arrCardAllPlayers[m_iMyIndex][j].byIndex  )
            {
                bCardAlreadyInDeck = TRUE;
                break;
            }
        }
        if (!bCardAlreadyInDeck)
        {
            // make a deck with all other cards, in sum 30 cards
            vctCards.push_back(i);
        }
    }
    ASSERT(NUM_CARDS_MAZZBRI - NUM_CARDS_HAND  == vctCards.size() );
    // shuffle the deck
    std::random_shuffle(vctCards.begin(), vctCards.end());
    // distribuite cards to all other players
    UINT iCardCount = 0;
    for (int k = 0; k < MAX_NUM_PLAYER; k++)
    {
        if (k == m_iMyIndex)
        {
            continue;
        }
        for (int g = 0; g < NUM_CARDS_HAND; g++)
        {
            CardSpec cdTemp;
            ASSERT(iCardCount < vctCards.size() );
            cdTemp.SetCardIndex( vctCards[iCardCount] ) ;
            cdTemp.FillInfo(&m_arrCardAllPlayers[k][g])  ;
            iCardCount++;
        }
    }

}

////////////////////////////////////////
//       traceAllCardInHand
/*! Trace all card in the hand
// \param LPCSTR strComment : comment shows before the complete card list
*/
void cAlgDefault::traceAllCardInHand(LPCSTR strComment)
{
    TRACE(strComment);
    traceListInhand(m_vctInHand_Spade);
    traceListInhand(m_vctInHand_Bastoni);
    traceListInhand(m_vctInHand_Coppe);
    traceListInhand(m_vctInHand_Denari);
}

////////////////////////////////////////
//       traceListInhand
/*! Trace cards in the vctListIndexes.
// \param VCT_INT vctListIndexes : index card list to be traced
*/
void cAlgDefault::traceListInhand(VCT_INT& vctListIndexes)
{
    for (UINT i = 0; i < vctListIndexes.size(); i++)
    {
        CARDINFO Card_1 = m_arrCardAllPlayers[m_iMyIndex][vctListIndexes[i]];
        TRACE("card: %s \n", Card_1.CardName);
    }
}

////////////////////////////////////////
//       removeListIndex
/*! remove the iIndex from the list vctInHand
// \param VCT_INT&  vctInHand : list with card indexes
// \param int iIndex : index to remove
*/
void cAlgDefault::removeListIndex(VCT_INT&  vctInHand, int iIndex)
{
    VCT_INT vctTmp;
    vctTmp.reserve(NUM_CARDS_HAND);
    for (UINT i = 0; i < vctInHand.size(); i++)
    {
        if (vctInHand[i] != iIndex)
        {
            vctTmp.push_back(vctInHand[i]);
        }
    }
    vctInHand = vctTmp;
}


////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player has played a card
// \param int iPlayerIx : player that has played
// \param CARDINFO* pCard : card played
*/
void cAlgDefault::ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard) 
{
    if (iPlayerIx == m_iMyIndex)
    {
        // card was played from the current player
        BOOL bFound = FALSE;
        BOOL bFoundValid = FALSE;
        // card successfully played
        for (int i = 0; !bFound && i < NUM_CARDS_HAND; i++)
        {
            if (pCard->byIndex  == m_arrCardAllPlayers[m_iMyIndex][i].byIndex )
            {
                for (int j = NUM_CARDS_HAND - 1; j >= 0; j--)
                {
                    // find a first valid card
                    if (m_arrCardAllPlayers[m_iMyIndex][j].byIndex  != NOT_VALID_INDEX)
                    {
                        // swap with the last valid
                        m_arrCardAllPlayers[m_iMyIndex][i] = m_arrCardAllPlayers[m_iMyIndex][j];
                        
                        m_arrCardAllPlayers[m_iMyIndex][j].byIndex = NOT_VALID_INDEX;
                        m_arrCardAllPlayers[m_iMyIndex][j].eSuit = UNDEF;
                        bFoundValid = TRUE;
                        //Adjust indexes
                        calculateSuiteIndexes();
                        break;
                        
                    }
                }
                bFound = TRUE;
            }
            
        }
        ASSERT(bFound);
        ASSERT(bFoundValid);
    }
    else
    {
        BOOL bTerminate = FALSE;
        int iIndexToInvalidate = 0;
        // other players has played the card
        // adjust player hand
        for (int g = 0; g < MAX_NUM_PLAYER && !bTerminate; g++)
        {
            if (g == m_iMyIndex)
            {
                continue;
            }
            for (int k = 0; k < NUM_CARDS_HAND; k++)
            {
                if ( m_arrCardAllPlayers[g][k].byIndex  == pCard->byIndex )
                {
                    // card found on player g
                    if (iPlayerIx == g)
                    {
                        // ok, card was assigned to the correct player
                        // invalidate it
                        iIndexToInvalidate = k;

                    }
                    else
                    {
                        // cards is in the hand of an another player
                        // change it with the first card on player 
                        m_arrCardAllPlayers[g][k] = m_arrCardAllPlayers[iPlayerIx][0];
                        iIndexToInvalidate = 0;

                        swapCardOnInitTrick(iPlayerIx, pCard);

                    }
                    // make the selected index invalid: put it at the end
                    for (int h = NUM_CARDS_HAND - 1; h >= 0; h-- )
                    {
                        if (m_arrCardAllPlayers[iPlayerIx][h].byIndex  != NOT_VALID_INDEX)
                        {
                            m_arrCardAllPlayers[iPlayerIx][iIndexToInvalidate] = 
                                            m_arrCardAllPlayers[iPlayerIx][h];
                        
                            m_arrCardAllPlayers[iPlayerIx][h].byIndex = NOT_VALID_INDEX;
                            m_arrCardAllPlayers[iPlayerIx][h].eSuit = UNDEF;
                            break;
                        }
                    }
                    bTerminate = TRUE;
                }
            }
        }
        ASSERT(bTerminate);
    }

    m_vctCardsPlayedTricks.push_back(*pCard);

    CardSpec cardPlayed;
    cardPlayed.SetCardInfo(*pCard); 
    m_currTrickInfo.vctCardsPlayed.push_back(cardPlayed); 
    m_currTrickInfo.byNumPlayerPlayed ++;
    if (m_currTrickInfo.vctCardsPlayed.size() == 1)
    {
        m_currTrickInfo.iPlayer_S = iPlayerIx;
    }
 
    
}


////////////////////////////////////////
//       swapCardOnInitTrick
/*! The trick initial could be inconsistent (hands of other players are random) with card played.
// Swap the card played with the player that real play it.
// \param int iPlayerIx : player that play the card
// \param CARDINFO* pCard : card played
*/
void cAlgDefault::swapCardOnInitTrick(int iPlayerIx, CARDINFO* pCard)
{
    for (int g = 0; g < MAX_NUM_PLAYER; g++)
    {
        if (g == m_iMyIndex)
        {
            continue;
        }
        for (int k = 0; k < NUM_CARDS_HAND; k++)
        {
            if ( m_arrCardAllTrickInit[g][k].byIndex  == pCard->byIndex )
            {
                // swap  cards in the stored initial trick array, use the first card as index
                CARDINFO ciTemp = m_arrCardAllTrickInit[g][k];
                m_arrCardAllTrickInit[g][k] = m_arrCardAllTrickInit[iPlayerIx][0];
                m_arrCardAllTrickInit[iPlayerIx][0] = ciTemp;
    
                //TRACE("[%d]Swap card: %s with %s (playerplay: %d, plaswap: %d, cardhasplayed: %s)\n", m_iMyIndex,m_arrCardAllTrickInit[g][k].CardName, ciTemp.CardName, iPlayerIx, g, pCard->CardName  );
                // ok ready to return
                return;
            }
        }
    }
    ASSERT(0); // we should find the card in the swap
}

////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player has said something
// \param int iPlayerIx : 
// \param eSayPlayer eSay : 
*/
void cAlgDefault::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay) 
{
    SayPlayer stPlaySaid;
    stPlaySaid.eSay =  eSay; 
    stPlaySaid.iPlayerIx = iPlayerIx;
    m_currTrickInfo.vctSayPlayer.push_back( stPlaySaid ); 
}


////////////////////////////////////////
//       lookforDeclGoodGames
/*! Look inside the hand if good games are to be declared.
*/
void cAlgDefault::lookforDeclGoodGames()
{
    VCT_GOODGAMEDETAIL vct_GGRec;
    VCT_CARDINFO vctMyCards;
    for (int j = 0; j < NUM_CARDS_HAND; j++)
    {
        vctMyCards.push_back(m_arrCardAllPlayers[m_iMyIndex][j]);
    }

    // retrives all available good games
    AlgSupport::GetAvailbDeclGoodGames(vctMyCards, vct_GGRec);


    for (UINT i = 0; i < vct_GGRec.size(); i++)
    {
        m_pCoreGame->DeclareGoodGame( m_iMyIndex, vct_GGRec[i].eGGval, vct_GGRec[i].eSManca); 
    }

   
}

////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cAlgDefault::ALG_Play() 
{
    ASSERT(m_pCoreGame);

    CardSpec cardUndef;
    m_iTrickRound++;

    if (m_iTrickRound == 1)
    {
        // look if some declaration are available
        lookforDeclGoodGames();
    }
    
    BOOL bViaDalGioco = FALSE;
    BOOL bBusso = FALSE;
    BOOL bStayQuite = FALSE;
    CARDINFO cardToPlay;

    // play a card in a dummy art
    //playRandom(cardToPlay);
    
    //m_pABSolver->Solve(); 
    if (m_vctCardsPlayedTricks.size() == 0)
    {
        // i am the first
        playAsFirst(cardToPlay);
    }
    else
    {
        playAsNotFirst(cardToPlay);
    }
    
    //eventually make a declaration
    if (!bStayQuite)
    {
        signalSomething(cardToPlay, bViaDalGioco, bBusso);
    }

    // play the card
    // pay attention that the core call the callback function ALG_PlayerHasPlayed
    BOOL bRes = m_pCoreGame->Player_playCard(m_iMyIndex, &cardToPlay ); 
    ASSERT(bRes);
    
}


////////////////////////////////////////
//       playAsFirst
/*! Provides the card to play. Player is the first.
// \param CARDINFO& cardToPlay : cards to play
*/
void cAlgDefault::playAsFirst(CARDINFO& cardToPlay)
{
    MTX_PINDEX mtxPIndex;
    orderSuitListOnFreq(mtxPIndex);

    // IF NAPULA
    //PLAY NAPULA
    if (m_firstHandInfo.ePizzOnCoppe == AlgSupport::NAPOLA && m_vctInHand_Coppe.size() > 0)
    {
        int iCardIx = m_vctInHand_Coppe[0];
        cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
        return;
    }
    else if (m_firstHandInfo.ePizzOnBastoni  == AlgSupport::NAPOLA && m_vctInHand_Bastoni.size() > 0)
    {
        int iCardIx = m_vctInHand_Bastoni[0];
        cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
        return;
    }
    else if (m_firstHandInfo.ePizzOnSpade == AlgSupport::NAPOLA && m_vctInHand_Spade.size() > 0)
    {
        int iCardIx = m_vctInHand_Spade[0];
        cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
        return;
    }
    else if (m_firstHandInfo.ePizzOnDenari == AlgSupport::NAPOLA && m_vctInHand_Denari.size() > 0)
    {
        int iCardIx = m_vctInHand_Denari[0];
        cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
        return;
    }
    // ENDIF

    if (m_iTrickRound == 1)
    {
        // IF (MOLTOFORTE || FORTE)  THEN EXAMS_BIGGER_SEED
        //    IF 25 THEN  PLAY 3 ||
        //    IF 29 THEN  PLAY 3 ||
        //    IF ONLY_ASSO THEN PLAY BIGGER SCARTINO
        //    ELSE PLAY BIGGER SCARTINO
        // END_SEED_INSPECT
        ASSERT(m_currHandInfo.eForce != NOTDEF);

        if ( m_currHandInfo.eForce == FORTE || 
             m_currHandInfo.eForce == MOLTOFORTE )
        {
            eSUIT          eSuitStark = UNDEF ;
            UINT iPos = 0;
            ePizzicoInSuit ePizz = pizzicoOnBiggerSeed( eSuitStark );
            if ( ePizz != ASSO && ePizz != DUE )
            {
                
                iPos = 0;
            }
            else
            {
                // bigger seed grant index inner the list
                iPos = 1;
            }
            VCT_INT* pList = getListOnSuite(eSuitStark);
            ASSERT(iPos < pList->size());
            int iCardIx = (* pList)[iPos];
            cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
            return;
        }
         
        // IF ATTACCO THEN WHILE EXAMS_BIGGER_SEED
        //    IF 25 THEN  PLAY 3 ||
        //    IF 28 THEN  PLAY BIGGER SCARTINO ||
        //    IF 29 THEN  PLAY BIGGER SCARTINO
        // ENDIF
        if ( m_currHandInfo.eForce == ATTACCO  )
        {
            eSUIT          eSuitStark = UNDEF ;
            ePizzicoInSuit ePizz = pizzicoOnBiggerSeed( eSuitStark );
            if ( ePizz != VENTICINQUE)
            {
                // index of the bigger scartino
                int iCardIx  = indexOfTheBiggerScartino(eSuitStark);
                cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
                return;
            }
            // on 25 play the 3 (the first card)
            VCT_INT* pList = getListOnSuite(eSuitStark);
            int iCardIx = (* pList)[0];
            cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
            return;
        }
        
        // IF DEBOLE THEN 
        //   WHILE EXAMS_BIGGER_SEED
        //      IF ASSO ISPRESENT CHANGESEED
        //      ELSE EXITLOOP 
        //   LOOP
        //   PLAY THE SMALLER 
        // ENDIF 
        if ( m_currHandInfo.eForce == DEBOLE  )
        {
            eSUIT          eSuitStark = UNDEF ;
            ePizzicoInSuit ePizz = pizzicoOnBiggerSeed( eSuitStark );
            eSUIT          eSuitStarkInitial = eSuitStark;
            BOOL bSearchTer  = FALSE;
            VCT_SUITE vct_exclude;
            do
            {
                if ( ePizz == VENTINOVE || 
                     ePizz == VENTOTTO ||
                     ePizz == ASSO)
                {
                    vct_exclude.push_back( eSuitStark );
                    if(vct_exclude.size() < 4)
                    {
                        // change seed
                        ePizz = pizzicoOnBiggerSeed( eSuitStark, &vct_exclude );
                    }
                    else
                    {
                        // each seed has something, so back to the inial start suit
                        eSuitStark = eSuitStarkInitial; 
                        bSearchTer = TRUE;
                    }
                }
                else
                {
                    bSearchTer = TRUE;
                }
            }while(!bSearchTer);

            // index of the bigger scartino
            int iCardIx = indexOfTheBiggerScartino(eSuitStark);
            cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
            return;
        }
		
    }
    else
    {
        // use alpha beta
        useAlphaBeta(cardToPlay);
        
    }
}

////////////////////////////////////////
//       playAsNotFirst
/*! Provides the card to play. Player is not the first (second, third or fourth).
// \param CARDINFO& cardToPlay : 
*/
void cAlgDefault::playAsNotFirst(CARDINFO& cardToPlay)
{
	if ( m_currTrickInfo.byNumPlayerPlayed > 1)
	{
        // partner has already played
        BOOL bPartnetBusso = FALSE;
        int iPartner = AlgSupport::GetPartnerIndex( m_iMyIndex );
        for (UINT i = 0; i < m_currTrickInfo.vctSayPlayer.size() ; i++ )
        {
            if ( m_currTrickInfo.vctSayPlayer[i].eSay == BUSSO_LAMIGLIORE  && 
                 m_currTrickInfo.vctSayPlayer[i].iPlayerIx == iPartner )
            {
                bPartnetBusso = TRUE;
                break;
            }
        }
        // PARTNER HAS BUSSO THE BEST CARD
		// IF CARDS ON SEED
		//   PLAY THE BIGGER ON SEED
        // END
		if (bPartnetBusso)
        {
            eSUIT eSuitStark;
            eSuitStark = m_currTrickInfo.vctCardsPlayed[0].GetSuit() ;
            VCT_INT* pList = getListOnSuite(eSuitStark);
            if (pList->size() > 0)
            {
                int iCardIx = (* pList)[0];
                cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCardIx];
                return;
            }
        }
    }
    
    //if (m_iTrickRound == 1)
    if (0)
    {
    	// TO DO
        // TAKE IT OR LEAVE IT
        // this is not so simple, avoid it and use alpha beta
        ASSERT(0);
    }
    else
    {
        // use alpha beta

        // adjust deph because we are inner the trick
        int iDeph = 12 -  m_currTrickInfo.byNumPlayerPlayed;
        //int iDeph = 12;
        int iTotDeph = ( NUM_CARDS_HAND - ( m_iTrickRound - 1)) * 4 - m_currTrickInfo.byNumPlayerPlayed;
        if ( iTotDeph < iDeph)
        {
            iDeph = iTotDeph;
        }

        m_pABSolver->SetHandDeph(iDeph); 
        for (int j = 0; j < MAX_NUM_PLAYER; j++ )
        {
            // setup the alphabeta alg
            // all valid cards are sorted, valid card are at the beginning, at the the invalid one
            m_pABSolver->SetHands(j,  &m_arrCardAllTrickInit[j][0], NUM_CARDS_HAND - ( m_iTrickRound - 1) );
        }

        if (g_Options.All.iDebugLevel > 4  )
        {
            traceAllTrickInit();
        }
        
        // set the current trick history
        CARDINFO arrTrickHist[MAX_NUM_PLAYER];
        ASSERT(m_currTrickInfo.byNumPlayerPlayed == m_currTrickInfo.vctCardsPlayed.size() );
	int k;
        for ( k = 0; k < m_currTrickInfo.byNumPlayerPlayed; k++)
        {
            m_currTrickInfo.vctCardsPlayed[k].FillInfo(&arrTrickHist[k]);
        }
        
        if (g_Options.All.iDebugLevel > 4  )
        {
            traceArrOfCardInfo(arrTrickHist, k);
        }

        // set the current player that have to play
        m_pABSolver->SetInitialPlayer(m_iMyIndex);
        m_pABSolver->SetCurrTrickHistory(m_currTrickInfo.iPlayer_S, arrTrickHist, m_currTrickInfo.byNumPlayerPlayed );
        
        m_pABSolver->Solve(); 
        m_pABSolver->GetBestCardToPlay(m_iMyIndex, &cardToPlay); 
        //ASSERT(0);
    }
}


////////////////////////////////////////
//       traceAllTrickInit
/*! Trace all cards of all players (init trick)
*/
void cAlgDefault::traceAllTrickInit()
{
    TRACE("Playerme %d\n:", m_iMyIndex );
    for (int i = 0; i < MAX_NUM_PLAYER; i++)
    {
        TRACE("Player %d:\n", i);
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
            TRACE( "%s, ", m_arrCardAllTrickInit[i][j].CardName );
        }
        TRACE("\n");
    }
}


////////////////////////////////////////
//       traceArrOfCardInfo
/*! Trace an array of cards 
// \param CARDINFO* arrTrickHist : cards to be traced
// \param int iNumEle : number of elements
*/
void cAlgDefault::traceArrOfCardInfo(CARDINFO* arrTrickHist, int iNumEle)
{
    for (int i = 0; i < iNumEle; i++)
    {
        TRACE( "%s, ", arrTrickHist[i].CardName );
    }
    TRACE("\n");
}


////////////////////////////////////////
//       useAlphaBeta
/*! Use alpha beta alg to get the card to play. Use this function ONLY at the begin of the trick
// \param CARDINFO& cardToPlay : card to play result
*/
void cAlgDefault::useAlphaBeta(CARDINFO& cardToPlay)
{
    for (int j = 0; j < MAX_NUM_PLAYER; j++ )
    {
        // setup the alphabeta alg
        // all valid cards are sorted, valid card are at the beginning, at the end the invalid one
        m_pABSolver->SetHands(j,  &m_arrCardAllPlayers[j][0], NUM_CARDS_HAND - (m_iTrickRound - 1));
    }
    int iDeph = 12  - m_currTrickInfo.byNumPlayerPlayed ;
    int iTotDeph = ( NUM_CARDS_HAND - ( m_iTrickRound - 1)) * 4 - m_currTrickInfo.byNumPlayerPlayed;
    if ( iTotDeph < iDeph)
    {
        iDeph = iTotDeph;
    }

    m_pABSolver->SetInitialPlayer( m_iMyIndex );
    m_pABSolver->Solve(); 
    m_pABSolver->GetBestCardToPlay(m_iMyIndex, &cardToPlay); 
}


////////////////////////////////////////
//       orderSuitListOnFreq
/*! Order suite list on size.
// \param MTX_PINDEX& mtxPIndex : sort result 
*/
void cAlgDefault::orderSuitListOnFreq(MTX_PINDEX& mtxPIndex)
{
    mtxPIndex.clear();
    mtxPIndex.push_back(&m_vctInHand_Bastoni);
    mtxPIndex.push_back(&m_vctInHand_Denari);
    mtxPIndex.push_back(&m_vctInHand_Coppe);
    mtxPIndex.push_back(&m_vctInHand_Spade);

    std::sort(mtxPIndex.begin(), mtxPIndex.end(), cmpListOnSize());

    if (g_Options.All.iDebugLevel > 5  )
    {
        TRACE("List order\n");
        for (UINT i = 0; i < mtxPIndex.size(); i++)
        {
            VCT_INT* pList = mtxPIndex[i];
            int iNumEle = pList->size();
            if ( iNumEle > 0 )
            {
                CardSpec Card;
                // pick the first item of the list to print the suit
                int iCurrIndex = (*pList)[0];
                // use CardSpec to fill all info about this card
                Card.SetCardIndex( m_arrCardAllPlayers[m_iMyIndex][iCurrIndex].byIndex ); 
                TRACE("List suit %s, num elements: %d\n", Card.GetSuitName(), iNumEle);
            }
            else
            {
                TRACE("List empty\n");
            }
        }
    }

}

////////////////////////////////////////
//       developFirstHandTypes
/*! Develop combination of suite in the hand at the beginnig of a new giocata
*/
void cAlgDefault::developFirstHandTypes()
{
    // develop all combinations of the first hand
    /*
    10-0-0-0 = 
    9-1-0-0 = 
    8-2-0-0 = 
    8-1-1-0 = 
    7-3-0-0 = 
    7-2-1-0 = 
    7-1-1-1 = 
    6-4-0-0 = 
    6-3-1-0 = 
    6-2-2-0 = 
    6-2-1-1 = 
    5-5-0-0 = 
    5-4-1-0 = 
    5-3-2-0 = 
    5-3-1-1 = 
    5-2-2-1 = 
    4-4-2-0 = 
    4-4-1-1 = 
    4-3-3-0 = 
    4-3-2-1 = 
    4-2-2-2 = 
    3-3-3-1 = 
    3-3-2-2 = 
    */
    int j0 = 10;
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    CHAR buff[64];
    VCT_STRING vctAllMyComb;
    int iCurrIndexToChange = 0;
    BOOL bNoWrite = FALSE;
    BOOL bEnd = FALSE;
    while (!bEnd)
    {
        if (!bNoWrite)
        {
            if( (j0 + j1 + j2 + j3) == 10 && 
                (j0 >= j1 && j1 >= j2 && j2 >= j3)) 
            {
                sprintf(buff,"%d-%d-%d-%d = ", j0, j1, j2, j3);
                STRING strCurrCombi = buff;
                vctAllMyComb.push_back(strCurrCombi);
            }
        }
        switch (iCurrIndexToChange)
        {
            case 0:
               j0 --;
               if (j0 < 3)
               {
                   // end
                   bEnd = TRUE;
                   break;
               }
               bNoWrite = FALSE;
               j1 = 10 - j0;
               j2 = 0;
               j3 = 0;
               iCurrIndexToChange = 1;
               break;
            case 1:
                j1 --;
                if (j1 <= 0)
                {
                    // redo the switch
                    iCurrIndexToChange = 0;
                    bNoWrite = TRUE;
                }
                else
                {
                    bNoWrite = FALSE;
                    j2 = 10 - j0 - j1;
                    j3 = 0;
                    iCurrIndexToChange = 2;
                }
                break;
            case 2:
                j2 --;
                if (j2 <= 0)
                {
                    // redo the switch
                    iCurrIndexToChange = 1;
                    bNoWrite = TRUE;
                }
                else
                {
                    bNoWrite = FALSE;
                    j3 = 10 - j0 - j1 - j2;
                    iCurrIndexToChange = 3;
                }
                break;

            case 3:
                j3 --;
                if (j3 + j0 + j1 + j2 < 10)
                {
                    // redo the switch
                    iCurrIndexToChange = 2;
                    bNoWrite = TRUE;
                }
                else
                {
                    bNoWrite = FALSE;
                    iCurrIndexToChange = 3;
                }
                break;
        }
    }
    int iNumCombi = vctAllMyComb.size();
    //Utility::SaveContainerToFile(vctAllMyComb, "miecombi.txt");
    //TO DO: calculate the prob of each entry
    // we first calculate COMBIN( 10, A) * COMBIN ( 10, B) * COMBIN( 10, C) * COMBIN( 10, D)
    // Next we multiply by 24 for permutations of the four suits. 
    //Finally, we scan the numbers "A", "B", "C", "D" to see if any number occurs more than once. 
    //For each occasion where a number appears twice we divide by FACT(2) = 2. 
    //(In this problem there can't be more than 1 pair of matched numbers, but this could occur in 
    //other problems). Then, for each set where 3 numbers match 
    //(e.g. if we were using 7, 2, 2, 2) we divide by FACT(3) = 6. 
    //(These are the only matched sets that can occur in this problem, but more complicated 
    // problems would extend this rule).
    // Total comination are COMBIN( 40,10)
}



////////////////////////////////////////
//       playRandom
/*! Play a card in a random manner
// \param CARDINFO& cardToPlay : 
*/
void cAlgDefault::playRandom(CARDINFO& cardToPlay)
{
    int iCartaPos = CASO(10);
    int iLoops = 0;
    VCT_CARDINFO vctSameSuit;
    if (m_vctCardsPlayedTricks.size() > 0)
    {
        ASSERT(m_vctCardsPlayedTricks[0].eSuit != UNDEF);
        // check suit
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            if (m_arrCardAllPlayers[m_iMyIndex][i].eSuit == m_vctCardsPlayedTricks[0].eSuit)
            {
                // same suit
                ASSERT(m_arrCardAllPlayers[m_iMyIndex][i].eSuit != UNDEF);
                ASSERT(m_arrCardAllPlayers[m_iMyIndex][i].byIndex  != NOT_VALID_INDEX);
                vctSameSuit.push_back(m_arrCardAllPlayers[m_iMyIndex][i]); 
            }
        }
    }
    if (vctSameSuit.size() > 0 )
    {
        iCartaPos = CASO( vctSameSuit.size() );
        // use a copy otherwise on notification  ALG_PlayerHasPlayed goes reset
        cardToPlay = vctSameSuit[iCartaPos];
    }
    else
    {
        while (m_arrCardAllPlayers[m_iMyIndex][iCartaPos].eSuit == UNDEF && iLoops < NUM_CARDS_HAND)
        {
            iCartaPos++;
            if (iCartaPos >= NUM_CARDS_HAND)
            {
                iCartaPos = 0;
            }
            iLoops ++;
        }
        ASSERT(m_pCoreGame);
        ASSERT(m_arrCardAllPlayers[m_iMyIndex][iCartaPos].eSuit != UNDEF );
        // use a copy otherwise on notification  ALG_PlayerHasPlayed goes reset
        cardToPlay = m_arrCardAllPlayers[m_iMyIndex][iCartaPos];
    }
}


////////////////////////////////////////
//       signalSomething
/*! Exams the hand and make  signal
*/
void cAlgDefault::signalSomething(CARDINFO& cardPlayed, BOOL bViaDalGioco, BOOL bBusso)
{
    if ((m_eLocal == LT_CHITARELLA || m_eLocal ==  LT_ROMANA) && m_currTrickInfo.byNumPlayerPlayed > 0 )
    {
        // admit declarations only for the first in the trick
        return;
    }
    
    if (bViaDalGioco && m_eLocal == LT_BREDA)
    {
        m_pCoreGame->Player_saySomething(m_iMyIndex, VIA_DAQUESTOGIOCO );
    }
    else if (bBusso)
    {
        m_pCoreGame->Player_saySomething(m_iMyIndex, BUSSO_LAMIGLIORE );
    }
    else
    {
        VCT_INT* pListIndexCard = getListOnSuite(cardPlayed.eSuit);
        BOOL bDue = FALSE;
        BOOL bTre = FALSE;
        BOOL bAsso = FALSE;

        int iNumCard = pListIndexCard->size();
        ASSERT(iNumCard > 0);
        if (iNumCard == 1)
        {
            if (m_eLocal == LT_CHITARELLA)
            {
                m_pCoreGame->Player_saySomething(m_iMyIndex, PIOMBO );
            }
            else
            {
                m_pCoreGame->Player_saySomething(m_iMyIndex, VOLO );
            }
        }
        else if (iNumCard == 2)
        {
            m_pCoreGame->Player_saySomething(m_iMyIndex, PUNTO_ANCORAUNA );
        }
        else if (iNumCard > 2)
        {
            checkListBigCards(pListIndexCard, bTre, bDue, bAsso);
            if (bTre && !isTre(cardPlayed))
            {
                m_pCoreGame->Player_saySomething(m_iMyIndex, HO_ILTRE );
            }
            else if (bDue && !isDue(cardPlayed))
            {
                m_pCoreGame->Player_saySomething(m_iMyIndex, HO_ILDUE );
            }
            else if (bAsso && !isAsso(cardPlayed))
            {
                m_pCoreGame->Player_saySomething(m_iMyIndex, HO_ASSO );
            }
            else
            {
                m_pCoreGame->Player_saySomething(m_iMyIndex, STRISCIO_NEHOTANTE );
            }

        }
    }
}


////////////////////////////////////////
//       isTre
/*! Return true if the card is a 3
// \param CARDINFO& cardPlayed : card to exam
*/
BOOL cAlgDefault::isTre(CARDINFO& cardPlayed)
{
    BOOL bRes = FALSE;

    if (cardPlayed.byIndex == 2 ||
        cardPlayed.byIndex == 12 ||
        cardPlayed.byIndex == 22 ||
        cardPlayed.byIndex == 32 )
    {
        bRes = TRUE;
    }
    return bRes;
}

////////////////////////////////////////
//       isDue
/*! Return true if the card is a 2
// \param CARDINFO& cardPlayed : card to exam
*/
BOOL cAlgDefault::isDue(CARDINFO& cardPlayed)
{
    BOOL bRes = FALSE;

    if (cardPlayed.byIndex == 1 ||
        cardPlayed.byIndex == 11 ||
        cardPlayed.byIndex == 21 ||
        cardPlayed.byIndex == 31 )
    {
        bRes = TRUE;
    }
    return bRes;
}

////////////////////////////////////////
//       isAsso
/*! Return true if the card is a asso
// \param CARDINFO& cardPlayed : card to exam
*/
BOOL cAlgDefault::isAsso(CARDINFO& cardPlayed)
{
    BOOL bRes = FALSE;

    if (cardPlayed.byIndex == 0 ||
        cardPlayed.byIndex == 10 ||
        cardPlayed.byIndex == 20 ||
        cardPlayed.byIndex == 30 )
    {
        bRes = TRUE;
    }
    return bRes;
}

////////////////////////////////////////
//       checkListBigCards
/*! Check the list if big card are present
// \param VCT_INT* pListIndexCard : 
// \param BOOL bTre : 
// \param BOOL bDue : 
// \param BOOL bAsso : 
*/
void cAlgDefault::checkListBigCards(VCT_INT* pListIndexCard, BOOL& bTre, BOOL& bDue, BOOL& bAsso)
{
    bAsso = FALSE;
    bDue = FALSE;
    bTre = FALSE;

    for (UINT i = 0; i < pListIndexCard->size(); i++)
    {
        int iIndex = (*pListIndexCard)[i];
        switch ( m_arrCardAllPlayers[m_iMyIndex][iIndex].byIndex)
        {
            // ass
            case 0:
            case 10:
            case 20:
            case 30:
                bAsso = TRUE;
                break;

            // two
            case 1:
            case 11:
            case 21:
            case 31:
                bDue = TRUE;
                break;

                // 3
            case 2:
            case 12:
            case 22:
            case 32:
                bTre = TRUE;
                break;
        }
    }
}


////////////////////////////////////////
//       getListOnSuite
/*! Provides the list on suite
// \param eSUIT eSuit : suite for the list
*/
VCT_INT* cAlgDefault::getListOnSuite(eSUIT eSuit)
{
    VCT_INT* pRes;
    switch(eSuit)
    {
        case BASTONI:
            pRes = &m_vctInHand_Bastoni;
            break;
        case COPPE:
            pRes = &m_vctInHand_Coppe;
            break;
        case DENARI:
            pRes = &m_vctInHand_Denari;
            break;
        case SPADE:
            pRes = &m_vctInHand_Spade;
            break;
    }
    return pRes;
}


////////////////////////////////////////
//       indexOfTheBiggerScartino
/*! Provides the index of the biggest scartino card in a index list
// \param eSUIT eSuitStark : suite to search
*/
int cAlgDefault::indexOfTheBiggerScartino( eSUIT eSuitStark )
{
    int iRetVal = 0;

    VCT_INT* pList = getListOnSuite(eSuitStark);

    int iMax = 0;
    for(UINT i = 0; i < pList->size(); i++)
    {
        int iCardIndex = (*pList)[i];
        int iCurrRank = m_arrCardAllPlayers[m_iMyIndex][iCardIndex].iRank;
        if ( iCurrRank > iMax && iCurrRank != 11 && iCurrRank != 12 && iCurrRank != 13)
        {
            // max rank of not pizzico
            iMax = iCurrRank;
            iRetVal = iCardIndex;
        }
    }

    return iRetVal;
}

////////////////////////////////////////
//       pizzicoOnBiggerSeed
/*! Check all suite list and provides the biggest suite on size. 
// \param eSUIT& eSuitStark : returned biggest suite value
// \param VCT_SUITE* pVct : exclude a suite list
// \return : value of the pizzico in the biggest suite 
*/
ePizzicoInSuit cAlgDefault::pizzicoOnBiggerSeed( eSUIT& eSuitStark , VCT_SUITE* pVct)
{
    ePizzicoInSuit eRetVal = PIZZ_NONE;
    eSuitStark = UNDEF;

    BOOL bNoCoppe = FALSE;
    BOOL bNoBastoni = FALSE;
    BOOL bNoDenari = FALSE;
    BOOL bNoSpade = FALSE;

    int iSpadeSize = m_vctInHand_Spade.size();
    int iBastSize = m_vctInHand_Bastoni.size();
    int iCoppeSize = m_vctInHand_Coppe.size();
    int iDenariSize = m_vctInHand_Denari.size();

    if ( pVct )
    {
        for (UINT i = 0; i < pVct->size(); i++)
        {
            if ( (*pVct)[i] == BASTONI )
            {
                bNoBastoni = TRUE;
                iBastSize = 0;
            }
            else if ( (*pVct)[i] == COPPE )
            {
                bNoCoppe = TRUE;
                iCoppeSize = 0;
            }
            else if ( (*pVct)[i] == DENARI )
            {
                bNoDenari = TRUE;
                iDenariSize = 0;
            }
            else if ( (*pVct)[i] == SPADE )
            {
                bNoSpade = TRUE;
                iSpadeSize = 0;
            }
            else
            {
                ASSERT(0);
            }
        }
        
    }

    if (iBastSize >=  iCoppeSize &&
        iBastSize >=  iDenariSize &&
        iBastSize >=  iSpadeSize && !bNoBastoni)
    {
        // bastoni is the most populated suite
        eRetVal = m_currHandInfo.ePizzOnBastoni;
        eSuitStark = BASTONI;
    }
    
    if (iCoppeSize >=  iBastSize &&
        iCoppeSize >=  iDenariSize &&
        iCoppeSize >=  iSpadeSize && !bNoCoppe)
    {
        if (eRetVal == PIZZ_NONE ||
            eRetVal > m_currHandInfo.ePizzOnCoppe)
        {
            // coppe is the most populated suite
            eRetVal = m_currHandInfo.ePizzOnCoppe;
            eSuitStark = COPPE;
        }
    }

    if (iDenariSize >=  iBastSize &&
        iDenariSize >=  iCoppeSize &&
        iDenariSize >=  iSpadeSize && !bNoDenari)
    {
        if (eRetVal == PIZZ_NONE ||
            eRetVal > m_currHandInfo.ePizzOnDenari)
        {
            // denari is the most populated suite
            eRetVal = m_currHandInfo.ePizzOnDenari;
            eSuitStark = DENARI;
        }
    }

    if (iSpadeSize >=  iBastSize &&
        iSpadeSize >=  iCoppeSize &&
        iSpadeSize >=  iDenariSize && !bNoSpade)
    {
        if (eRetVal == PIZZ_NONE ||  
            eRetVal > m_currHandInfo.ePizzOnSpade)
        {
            // spade is the most populated suite
            eRetVal = m_currHandInfo.ePizzOnSpade;
            eSuitStark = SPADE;
        }
    }



    ASSERT(eSuitStark != UNDEF);

    return eRetVal;
}

////////////////////////////////////////
//       ALG_PLayerDeclareGoodGame
/*! 
// \param int iPlayerIx : 
// \param eDeclGoodGame eValgg : 
// \param eSUIT eValsuit : 
*/
void cAlgDefault::ALG_PLayerDeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSUIT eValsuit)
{
    
}

////////////////////////////////////////
//       ALG_ManoEnd
/*! mano end notification
*/
void cAlgDefault::ALG_ManoEnd(I_MatchScore* pScore) 
{
    m_vctCardsPlayedTricks.clear(); 
    m_currTrickInfo.Reset(); 
    copyCardsBeginTrick();

    // WORK AROUND, we have to reset instead of delete
    newAlgSolver();
    
}


////////////////////////////////////////
//       newAlgSolver
/*! Create a new algorithm solver
*/
void cAlgDefault::newAlgSolver()
{
    if (m_pABSolver)
    {
        delete m_pABSolver;
    }
    m_pABSolver = new cAlgABSolver();
    m_pABSolver->SetMaxCalcTime(2000);
    m_pABSolver->InitDeck();
}

////////////////////////////////////////
//       ALG_GiocataEnd
/*! 
*/
void cAlgDefault::ALG_GiocataEnd(I_MatchScore* pScore) 
{

}

////////////////////////////////////////
//       ALG_MatchEnd
/*! match end notification
*/
void cAlgDefault::ALG_MatchEnd(I_MatchScore* pScore) 
{

}

////////////////////////////////////////
//       ALG_Say
/*! Algorithm is invited to responce
*/
void cAlgDefault::ALG_Say()
{
    ASSERT(0);
}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*! 
// \param eGiocataScoreState eNewScore : 
*/
void cAlgDefault::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{
}


////////////////////////////////////////
//       ALG_PLayerSaidFalse
/*! player said somithing false
// \param int iPlayerIx : 
*/
void cAlgDefault::ALG_PLayerSaidFalse(int iPlayerIx)
{
}

////////////////////////////////////////
//       ALG_SetOpponentIndex
/*! set opponent index
// \param int iIndex : 
// \param int iOpponentNr : 
*/
void cAlgDefault::ALG_SetOpponentIndex(int iIndex, int iOpponentNr) 
{
}


////////////////////////////////////////
//       ALG_SetAssociateIndex
/*! Set associate index (the algorithm player index) to recognize notifications of a player.
// \param int iIndex : new index of the algorithm
*/
void cAlgDefault::ALG_SetAssociateIndex(int iIndex) 
{

}

