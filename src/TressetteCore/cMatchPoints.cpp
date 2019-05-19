

// cMatchPoints.cpp: implementation of the cMatchPoints class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "cMatchPoints.h"
#include "cMano.h"



////////////////////////////////////////
//       cMatchPoints
/*! 
*/
cMatchPoints::cMatchPoints()
{
    m_iNumPlayers = NUM_PLAY_INVIDO_2;
    m_pMano = 0;
    m_bGameAbandoned = FALSE;
    for (int iManoNum = 0; iManoNum < NUM_CARDS_HAND; iManoNum++)
    {
        m_ManoDetailInfo[iManoNum].Reset(); 
    }
    m_eCurrentScore = SC_NOSCORE;
    m_iScoreGoal = SCORE_GOAL;
}


////////////////////////////////////////
//       ~cMatchPoints
/*! 
*/
cMatchPoints::~cMatchPoints()
{

}


////////////////////////////////////////
//       MatchStart
/*! A new match is started
*/
void    cMatchPoints::MatchStart(int iNumPlayer)
{
    for (int i = 0; i < MAX_NUM_PLAYER; i++)
    {
        m_vctPlayerPoints[i] = 0;
    }
    m_iNumPlayers = iNumPlayer;
    m_iPlayerMatchWin = NOT_VALID_INDEX;
    
    m_bMatchInSpecialScore = FALSE;
    m_vctGiocataInfo.clear();
}

////////////////////////////////////////
//       GiocataStart
/*! A new giocata is started
*/
void cMatchPoints::GiocataStart()
{
    CardSpec CardUndef;
    for (int i = 0; i < MAX_NUM_PLAYER; i++)
    {
        m_vctHandWons[i] = 0;
        m_vctCardPlayed[i].cardSpec  = CardUndef;
        m_vctCardPlayed[i].iPlayerIx   = NOT_VALID_INDEX;
    }
    m_iNumCardsPlayed = 0;
    m_eCurrentScore = SC_NOSCORE;
    m_iPlayerWonsHand = NOT_VALID_INDEX;
    m_iPlayerFirstHand = NOT_VALID_INDEX;
    m_iPlayerGiocataWin = NOT_VALID_INDEX;
    m_eIsGiocataEnd = GES_ON_GOING;
    m_bIsManoPatatda = FALSE;
    m_iManoRound = 0;
    m_bOldManoPatada = FALSE;
    for (int iManoNum = 0; iManoNum < NUM_CARDS_HAND; iManoNum++)
    {
        m_ManoDetailInfo[iManoNum].Reset(); 
    }
    m_iPlayerChangeScore = NOT_VALID_INDEX;
    m_bGameAbandoned = FALSE;

    m_vctCardTaken_1.clear();
    m_vctCardTaken_2.clear();

    m_iPlayerLastMano = NOT_VALID_INDEX;

    m_CurrGiocataInfo.Reset();
}


////////////////////////////////////////
//       PlayerPlay
/*! Player has played a card
// \param int iPlayerIx : 
// \param CARDINFO* pCard : 
*/
void    cMatchPoints::PlayerPlay(int iPlayerIx, CARDINFO* pCard)
{
    CardSpec Card;
    ASSERT(pCard);
    Card.SetCardInfo(*pCard); 
    ASSERT(m_iNumCardsPlayed < MAX_NUM_PLAYER && m_iNumCardsPlayed >= 0);
    m_vctCardPlayed[m_iNumCardsPlayed].iPlayerIx  = iPlayerIx;
    m_vctCardPlayed[m_iNumCardsPlayed].cardSpec = Card;
    m_iNumCardsPlayed++;
    
}


////////////////////////////////////////
//       CheckRejecting
/*! Check if the card is compatible with the game. In tressette the player have to play the same seed of
// the first played card.
// \param int iPlayerIx : player tha play a card 
// \param CARDINFO* pCard : card to be played
*/
BOOL  cMatchPoints::CheckRejecting(int iPlayerIx, CARDINFO* pCard)
{
    BOOL bRes = FALSE;
    if (m_iNumCardsPlayed == 0)
    {
        // first card, no more check
        bRes = TRUE;
    }
    else
    {
        CardSpec Card;
        Card = m_vctCardPlayed[0].cardSpec;
        if (Card.GetSuit() ==  pCard->eSuit )
        {
            // ok same suit
            bRes = TRUE;
        }
    }
    return bRes;
}


////////////////////////////////////////
//       GetCardPlayedOnTrick
/*! Provides the card played in the current trick
// \param int iIndex : index of the card played
// \param CardSpec* pResCard : card result
*/
void  cMatchPoints::GetCardPlayedOnTrick(int iIndex, CardSpec* pResCard)
{
    ASSERT(pResCard);
    if (iIndex >= 0 && iIndex < MAX_NUM_PLAYER)
    {
        // index ok
        *pResCard = m_vctCardPlayed[iIndex].cardSpec; 
    }
}

////////////////////////////////////////
//       ManoEnd
/*! Mano is terminated. Calculate the mano winner and if the mano is patada.
*/
void    cMatchPoints::ManoEnd()
{
    ASSERT(m_iNumCardsPlayed == m_iNumPlayers);
    int iManoTerminatedIndex = m_iManoRound;
    ASSERT(iManoTerminatedIndex >= 0 && iManoTerminatedIndex < NUM_CARDS_HAND);
    m_iManoRound++;
    // hand is terminated
    if (m_iNumPlayers == NUM_PLAYER_STD) // consistency check
    {
        int arPoints[NUM_PLAYER_STD];
        memset(arPoints, 0, NUM_PLAYER_STD*sizeof(int));

        // give points only if it was the same seed as the first
        arPoints[0] = g_RankTable[m_vctCardPlayed[PLAYER1].cardSpec.GetCardIndex()];
        eSUIT eFirst = m_vctCardPlayed[PLAYER1].cardSpec.GetSuit(); 
        if (m_vctCardPlayed[PLAYER2].cardSpec.GetSuit() == eFirst)
        {
            arPoints[1] = g_RankTable[m_vctCardPlayed[PLAYER2].cardSpec.GetCardIndex()];
        }
        if (m_vctCardPlayed[PLAYER3].cardSpec.GetSuit() == eFirst)
        {
            arPoints[2] = g_RankTable[m_vctCardPlayed[PLAYER3].cardSpec.GetCardIndex()];
        }
        if (m_vctCardPlayed[PLAYER4].cardSpec.GetSuit() == eFirst)
        {
            arPoints[3] = g_RankTable[m_vctCardPlayed[PLAYER4].cardSpec.GetCardIndex()];
        }
        
        m_bIsManoPatatda = FALSE;
        // mano is played
        m_ManoDetailInfo[iManoTerminatedIndex].bIsPlayed = TRUE;

        // find the bigger card scored
        int iPointsMax = arPoints[0];
        int iPlayerWinneIx = m_vctCardPlayed[PLAYER1].iPlayerIx;
        for (int i = 1; i< NUM_PLAYER_STD; i++)
        {
            if(arPoints[i] > iPointsMax)
            {
                iPointsMax = arPoints[i];
                iPlayerWinneIx = m_vctCardPlayed[i].iPlayerIx;
            }
        }
        // we have a mano winner
        m_iPlayerWonsHand = iPlayerWinneIx;
        m_ManoDetailInfo[iManoTerminatedIndex].iPlayerIndex = iPlayerWinneIx;
        if (iPlayerWinneIx == PLAYER1 ||
            iPlayerWinneIx == PLAYER3)
        {
            // first pair win
            for (int i = 0; i < NUM_PLAYER_STD; i++)
            {
                m_vctCardTaken_1.push_back(m_vctCardPlayed[i].cardSpec );
            }
        }
        else
        {
            // second pair win
            for (int i = 0; i < NUM_PLAYER_STD; i++)
            {
                m_vctCardTaken_2.push_back(m_vctCardPlayed[i].cardSpec );
            }
        }
        
        // check if giocata is also terminated
        if (m_iManoRound >= NUM_CARDS_HAND)
        {
            // mark giocata end.
            // points are calculated on GiocataEnd
            m_eIsGiocataEnd = GES_HAVE_WINNER;
            m_iPlayerLastMano = iPlayerWinneIx;
        }
    }
    else
    {
        ASSERT(0);
    }
    // reset info about mano
    m_iNumCardsPlayed = 0;
}


////////////////////////////////////////
//       PlayerVaVia
/*! Player abandon giocata
// \param int iPlayerIx : 
*/
void    cMatchPoints::PlayerVaVia(int iPlayerIx)
{
    m_eIsGiocataEnd = GES_HAVE_WINNER;
    if (iPlayerIx == PLAYER1)
    {
        m_iPlayerGiocataWin = PLAYER2;
    }
    else
    {
        m_iPlayerGiocataWin = PLAYER1;
    }
}


////////////////////////////////////////
//       calculatePointsTeam1
/*! Calculate current score of team 1 using the rank table.
*/
int cMatchPoints::calculatePointsTeam1()
{
    int iPoints = 0;

    int iPezze = 0;
    size_t iNumCardsTaken = m_vctCardTaken_1.size();
    for (int i = 0; i < iNumCardsTaken; i++)
    {
        int iCurrPoints = g_RankTable[m_vctCardTaken_1[i].GetCardIndex()];
        if (iCurrPoints == 11)
        {
            // ass
            iPoints++;
        }
        else if (iCurrPoints == 12 ||
                 iCurrPoints == 13 ||
                 iCurrPoints == 8 ||
                 iCurrPoints == 9 ||
                 iCurrPoints == 10)
        {
            // pezza
            iPezze++;
            if (iPezze >= 3)
            {
                // 3 pezze = one points
                iPoints++;
                iPezze = 0;
            }
        }
    }

    return iPoints;
}


////////////////////////////////////////
//       calculatePointsTeam2
/*! Calculate current score of team 2
*/
int cMatchPoints::calculatePointsTeam2()
{
    int iPoints = 0;

    int iPezze = 0;
    size_t iNumCardsTaken = m_vctCardTaken_2.size();
    for (int i = 0; i < iNumCardsTaken; i++)
    {
        int iCurrPoints = g_RankTable[m_vctCardTaken_2[i].GetCardIndex()];
        if (iCurrPoints == 11)
        {
            // ass
            iPoints++;
        }
        else if (iCurrPoints == 12 ||
                 iCurrPoints == 13 ||
                 iCurrPoints == 8 ||
                 iCurrPoints == 9 ||
                 iCurrPoints == 10)
        {
            // pezza
            iPezze++;
            if (iPezze >= 3)
            {
                // 3 pezze = one points
                iPoints++;
                iPezze = 0;
            }
        }
    }

    return iPoints;
}

////////////////////////////////////////
//       GiocataEnd
/*! Giocata is end. Update player score.
*/
void    cMatchPoints::GiocataEnd()
{
    if (m_eIsGiocataEnd == GES_HAVE_WINNER)
    {
        // calculate points first team
        int iPointsTeam1 = calculatePointsTeam1();
        int iPointsTeam2 = calculatePointsTeam2();

        // add points for the last mano taken
        if (m_iPlayerLastMano == PLAYER1 ||
            m_iPlayerLastMano == PLAYER3)
        {
            iPointsTeam1++;
        }
        else
        {
            iPointsTeam2++;
        }

        // update the stored score
        m_vctPlayerPoints[TEAM_1] += iPointsTeam1;
        m_vctPlayerPoints[TEAM_2] += iPointsTeam2;

        if (m_vctPlayerPoints[TEAM_1] >= m_iScoreGoal && 
            m_vctPlayerPoints[TEAM_1]  >  m_vctPlayerPoints[TEAM_2])
        {
            // match is terminated, winner is team 1
            m_iPlayerMatchWin = TEAM_1;
        }
        else if (m_vctPlayerPoints[TEAM_2] >= m_iScoreGoal && 
            m_vctPlayerPoints[TEAM_2]  >  m_vctPlayerPoints[TEAM_1])
        {
            // match is terminated, winner is team 2
            m_iPlayerMatchWin = TEAM_2;
        }
        // save the giocata info
        m_CurrGiocataInfo.iPointsTeam_1 = iPointsTeam1;
        m_CurrGiocataInfo.iPointsTeam_2 = iPointsTeam2;
        m_vctGiocataInfo.push_back(m_CurrGiocataInfo);
        
    }
    else
    {
        // pata or monte
        ASSERT(0);
    }
    for (int iManoNum = 0; iManoNum < NUM_CARDS_HAND; iManoNum++)
    {
        m_ManoDetailInfo[iManoNum].Reset(); 
    }
}



////////////////////////////////////////
//       IsGiocatEnd
/*! Return true if the current giocata is end
*/
BOOL   cMatchPoints::IsGiocatEnd()
{
    BOOL bRet = FALSE;

    if( m_eIsGiocataEnd == GES_AMONTE||
        m_eIsGiocataEnd == GES_PATADA||
        m_eIsGiocataEnd == GES_HAVE_WINNER)
    {
        bRet = TRUE;
    }
    return bRet;
}

////////////////////////////////////////
//       AMonte
/*! Giocata a monte
*/
void  cMatchPoints::AMonte()
{
    m_eIsGiocataEnd = GES_AMONTE;
}


////////////////////////////////////////
//       beginSpecialTurn
/*! Begin the turn to 8-8
*/
void    cMatchPoints::beginSpecialTurn()
{
    m_iScoreGoal = SPECIAL_SCORE_GOAL;
    m_vctPlayerPoints[PLAYER1] = 0;
    m_vctPlayerPoints[PLAYER2] = 0;
    m_bMatchInSpecialScore = TRUE;
}



////////////////////////////////////////
//       GetManoInfo
/*! Provides mano informations inner to giocata
// \param int iManoNum : mano number to get info
// \param int* piPlayerIx : player winner index
// \param BOOL* pbIsPlayed : true if mano is already played
// \param BOOL* pbIsPata : true if mano is patada
*/
void    cMatchPoints::GetManoInfo(int iManoNum, int* piPlayerIx, BOOL* pbIsPlayed, BOOL* pbIsPata)
{
    ASSERT(pbIsPata);
    ASSERT(pbIsPlayed);
    ASSERT(piPlayerIx);
    if (iManoNum >= 0 && iManoNum < NUM_CARDS_HAND)
    {
        *pbIsPata = m_ManoDetailInfo[iManoNum].bIsPata; 
        *pbIsPlayed = m_ManoDetailInfo[iManoNum].bIsPlayed ;
        *piPlayerIx = m_ManoDetailInfo[iManoNum].iPlayerIndex ;

    }
    else
    {
        ASSERT(0);
    }
}


////////////////////////////////////////
//       GetGiocataInfo
/*! 
// \param cGiocataInfo* pGiocInfo : 
*/
void    cMatchPoints::GetGiocataInfo(int iNumGiocata, cGiocataInfo* pGiocInfo)
{
    ASSERT(pGiocInfo);
    size_t iNumItem = m_vctGiocataInfo.size();
    if (iNumGiocata >= 0 && iNumGiocata < iNumItem)
    {
        *pGiocInfo = m_vctGiocataInfo[iNumGiocata];
    }
}


////////////////////////////////////////
//       GetCurrGiocataInfo
/*! 
// \param cGiocataInfo* pGiocInfo : 
*/
void  cMatchPoints::GetCurrGiocataInfo(cGiocataInfo* pGiocInfo)
{
    *pGiocInfo = m_CurrGiocataInfo;
}


////////////////////////////////////////
//       ChangeCurrentScore
/*! Current giocata score is changed by a player
// \param eGiocataScoreState eVal : new score
// \param int iPlayer : player responsible for the change
*/
void    cMatchPoints::ChangeCurrentScore(eGiocataScoreState eVal, int iPlayer)
{ 
    if (eVal > 0)
    {
        ASSERT(iPlayer != m_iPlayerChangeScore);
    }
    m_eCurrentScore = eVal;
    m_iPlayerChangeScore = iPlayer;
}


////////////////////////////////////////
//       SetTheWinner
/*! One player abandon the game, we have a winner. The winner index is usualy calculated on giocata end.
// \param int iPlayerIx : 
*/
void  cMatchPoints::SetTheWinner(int iPlayerIx)
{
    m_iPlayerMatchWin = iPlayerIx;
    m_bGameAbandoned = TRUE;
}


////////////////////////////////////////
//       DeclareGoodGame
/*! 
// \param int iPlayerIx : 
// \param eDeclGoodGame eValgg : 
// \param eSUIT eValsuit : 
*/
void  cMatchPoints::DeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSUIT eValsuit)
{
    int iTeamIndex;
    int iPointsDeclaration;

    // calculate points of declaration
    if (eValgg == TRE_TRE ||
        eValgg == TRE_DUE ||
        eValgg == TRE_ASSI ||
        eValgg == NAPOLETANA )
    {
        iPointsDeclaration = 3;
    }
    else if( eValgg == QUATTRO_TRE ||
             eValgg == QUATTRO_DUE ||
             eValgg == QUATTRO_ASSI)
    {
        iPointsDeclaration = 4;
    }

    // update giocata info
    if (iPlayerIx == PLAYER1 ||
        iPlayerIx == PLAYER3)
    {
        iTeamIndex = TEAM_1;
        m_CurrGiocataInfo.iAccusePointTeam_1  += iPointsDeclaration;
    }
    else if (iPlayerIx == PLAYER2 ||
        iPlayerIx == PLAYER4)
    
    {
        iTeamIndex = TEAM_2;
        m_CurrGiocataInfo.iAccusePointTeam_2 += iPointsDeclaration;
    }

    
    // update current score
    m_vctPlayerPoints[iTeamIndex] += iPointsDeclaration;
    
}





