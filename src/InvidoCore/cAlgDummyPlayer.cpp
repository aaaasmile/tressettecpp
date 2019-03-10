

// cAlgDummyPlayer.cpp: implementation of the cAlgDummyPlayer class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "win_type_global.h"
#include <map>
#include "cAlgDummyPlayer.h"
#include "TraceService.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


typedef std::map<eSayPlayer, LPCSTR> _MAP_SAY;
static _MAP_SAY  g_MapSay;


cAlgDummyPlayer::cAlgDummyPlayer()
{
    m_pCoreGame = 0;
    m_iOppIndex = NOT_VALID_INDEX;
    m_pTracer = TraceService::Instance();
    // say strings
    g_MapSay[AMONTE] = "A monte";
    g_MapSay[INVIDO] = "Invido";
    g_MapSay[TRASMAS] = "Tras mas";
    g_MapSay[TRASMASNOEF] = "Tras mas noef";
    g_MapSay[FUERAJEUQ] = "Feura jeuq";
    g_MapSay[PARTIDA] = "Partida";
    g_MapSay[VABENE] = "Va bene";
    g_MapSay[VADOVIA] = "Vado via";
    g_MapSay[CHIAMADIPIU] = "Chiama di più";
    g_MapSay[NO] = "No";
    g_MapSay[VADODENTRO] = "Vado dentro";
    g_MapSay[GIOCA] = "Gioca";

}

cAlgDummyPlayer::~cAlgDummyPlayer()
{

}


////////////////////////////////////////
//       ALG_SetCoreInterface
/*! 
// \param I_CORE_Game* pCore : 
*/
void cAlgDummyPlayer::ALG_SetCoreInterface(I_CORE_Game* pCore)
{
    m_pCoreGame = pCore;
}


////////////////////////////////////////
//       ALG_SetPlayerIndex
/*! set player index
// \param int iIndex : 
*/
void cAlgDummyPlayer::ALG_SetPlayerIndex(int iIndex) 
{
    m_iMyIndex = iIndex;
}


////////////////////////////////////////
//       ALG_SetOpponentIndex
/*! set opponent index
// \param int iIndex : 
// \param int iOpponentNr : 
*/
void cAlgDummyPlayer::ALG_SetOpponentIndex(int iIndex, int iOpponentNr) 
{
    m_iOppIndex =  iIndex;
}


    //! set associate index
void cAlgDummyPlayer::ALG_SetAssociateIndex(int iIndex) 
{

}


////////////////////////////////////////
//       ALG_NewMatch
/*! new match notification
// \param int iNumPlayer : 
*/
void cAlgDummyPlayer::ALG_NewMatch(int iNumPlayer) 
{
    
    
}


////////////////////////////////////////
//       ALG_NewGiocata
/*! new giocata notification
// \param CARDINFO* pCardArray : 
// \param int iNumOfCards : 
*/
void cAlgDummyPlayer::ALG_NewGiocata(const CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) 
{
    ASSERT(iNumOfCards == NUM_CARDS_HAND);
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_vct_Cards_CPU[i].SetCardInfo(pCardArray[i]); 
    }
    m_MyLastSay = VABENE;
    m_OpponentSay = VABENE;

    if (m_pTracer)
    {
        CardSpec Card;
        m_pTracer->AddSimpleTrace(3, "[TRALG]Cards of player %d are: \n", m_iMyIndex) ;
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            Card.SetCardInfo(pCardArray[i]);
            m_pTracer->AddSimpleTrace( 3, "[%s] ", Card.GetName() );
        }
        m_pTracer->AddSimpleTrace( 3, "\n");
    }
}

void cAlgDummyPlayer::ALG_PlayerHasVadoDentro(int iPlayerIx)
{
    ASSERT(0);
}


////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player has played a card
// \param int iPlayerIx : 
// \param CARDINFO* pCard : 
*/
void cAlgDummyPlayer::ALG_PlayerHasPlayed(int iPlayerIx, const CARDINFO* pCard) 
{
    ASSERT(pCard);
    if (iPlayerIx == m_iMyIndex)
    {
        CardSpec Card;
        CardSpec CardUndef;
        Card.SetCardInfo(*pCard); 
        BOOL bFound = FALSE;
        // card successfully played
        for (int i = 0; !bFound && i < NUM_CARDS_HAND; i++)
        {
            if (Card == m_vct_Cards_CPU[i])
            {
                // card found
                m_vct_Cards_CPU[i] = CardUndef;
                bFound = TRUE;
            }
        }
        ASSERT(bFound);
        if (m_pTracer)
        {
            m_pTracer->AddSimpleTrace( 3,"[TRALG]Player %d has played [%s]\n", iPlayerIx, Card.GetName() ); 
        }
    }
    else
    {
        m_OpponentSay = VABENE;
    }
}

////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player has said something
// \param int iPlayerIx : 
// \param eSayPlayer eSay : 
*/
void cAlgDummyPlayer::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay) 
{
    if (iPlayerIx == m_iOppIndex)
    {
        m_OpponentSay = eSay;
    }
    else if (iPlayerIx == m_iMyIndex)
    {
        if (m_pTracer)
        {
            LPCSTR lpsNameSay = g_MapSay[eSay];
            m_pTracer->AddSimpleTrace( 3,"[TRALG]Player %d has said %s\n", iPlayerIx, lpsNameSay ); 
        }
    }
}


////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cAlgDummyPlayer::ALG_Play() 
{
    CardSpec cardUndef;
    
    int iSayFiber = CASO(6);
    if (iSayFiber >= 4)
    {
        
        // instead of play a card, say something
        VCT_COMMANDS vct_cmd;
        ASSERT(m_pCoreGame);

        m_pCoreGame->GetAdmittedCommands(vct_cmd, m_iMyIndex); 
        size_t iNumCmds = vct_cmd.size();
        if (iNumCmds > 0)
        {
            eSayPlayer eSay;
            
            int iTry = 0;
            do
            {
                size_t iRndIndex = CASO(iNumCmds);
                eSay = vct_cmd[iRndIndex];
                iTry++;
            }
            while (eSay == VADOVIA && iTry < 5);
            m_MyLastSay = eSay;
            m_pCoreGame->Player_saySomething(m_iMyIndex, eSay); 
        }
    }
    else
    {
        // play a card in a dummy art
        int iCartaPos = CASO(3);
        int iLoops = 0;
        while (m_vct_Cards_CPU[iCartaPos] == cardUndef && iLoops < NUM_CARDS_HAND)
        {
            iCartaPos++;
            if (iCartaPos >= NUM_CARDS_HAND)
            {
                iCartaPos = 0;
            }
            iLoops ++;
        }
        ASSERT(m_pCoreGame);
        m_pCoreGame->Player_playCard(m_iMyIndex, m_vct_Cards_CPU[iCartaPos].GetCardInfo()); 
    }
}

////////////////////////////////////////
//       ALG_ManoEnd
/*! mano end notification
*/
void cAlgDummyPlayer::ALG_ManoEnd(I_MatchScore* pScore) 
{

}

////////////////////////////////////////
//       ALG_GiocataEnd
/*! 
*/
void cAlgDummyPlayer::ALG_GiocataEnd(I_MatchScore* pScore) 
{
    if (m_pTracer)
    {
        if (m_iMyIndex == 0)
        {
            BOOL bIsPata = pScore->IsGiocataPatada();
            if ( bIsPata )
            {
                // giocata patada
                m_pTracer->AddSimpleTrace( 3,"[TRALG]Giocata patada\n");
            }
            else if ( pScore->IsGiocataMonte() )
            {
                // giocata a monte
                m_pTracer->AddSimpleTrace( 3,"[TRALG]Giocata a monte\n");
            }
            else
            {
                // winner
                int iPlWinner = pScore->GetGiocataWinner();

                m_pTracer->AddSimpleTrace( 3,"[TRALG]Giocata vinta da %d\n", iPlWinner ); 
                m_pTracer->AddSimpleTrace( 3,"[TRALG]Punteggio player 0: %d, punteggio player 1: %d\n", 
                                   pScore->GetPointsPlayer(m_iMyIndex),
                                   pScore->GetPointsPlayer(m_iOppIndex));
            }
        }
    }
}

////////////////////////////////////////
//       ALG_MatchEnd
/*! match end notification
*/
void cAlgDummyPlayer::ALG_MatchEnd(I_MatchScore* pScore) 
{
    if (m_pTracer)
    {
        if (m_iMyIndex == 0)
        {
            int iPlWinner = pScore->GetMatchWinner();
            m_pTracer->AddSimpleTrace( 3,"[TRALG]Match vinto da %d\n", iPlWinner ); 
            m_pTracer->AddSimpleTrace( 3,"[TRALG]Punteggio player 0: %d, punteggio player 1: %d\n", 
                                   pScore->GetPointsPlayer(m_iMyIndex),
                                   pScore->GetPointsPlayer(m_iOppIndex));
        }
    }
}

////////////////////////////////////////
//       ALG_Say
/*! Algorithm is invited to responce
*/
void cAlgDummyPlayer::ALG_Say()
{
    if (m_OpponentSay == AMONTE && m_MyLastSay == NO)
    {
        // a monte was called and i was responsed NO, don't change idea
        m_pCoreGame->Player_saySomething(m_iMyIndex, m_MyLastSay);
        return ;
    }

    size_t iRndIndex;
    VCT_COMMANDS vct_cmd;
    ASSERT(m_pCoreGame);

    m_pCoreGame->GetAdmittedCommands(vct_cmd, m_iMyIndex); 
    size_t iNumCmds = vct_cmd.size();
    if (iNumCmds > 0)
    {
        iRndIndex = CASO(iNumCmds);
        m_MyLastSay = vct_cmd[iRndIndex];
        m_pCoreGame->Player_saySomething(m_iMyIndex, vct_cmd[iRndIndex]); 
        
    }
    else
    {
        ASSERT(0);
    }

}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*! 
// \param eGiocataScoreState eNewScore : 
*/
void cAlgDummyPlayer::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{
    m_eScoreCurrent = eNewScore;
    if (m_pTracer)
    {
        if (m_iMyIndex == 0)
        {
            m_pTracer->AddSimpleTrace( 3,"[TRALG]Score changed to %d\n", eNewScore ); 
        }
    }
}

void cAlgDummyPlayer::ALG_PlayerSaidWrong(int iPlayerIx)
{
}

