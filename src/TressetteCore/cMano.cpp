

//cMano.cpp
#include "StdAfx.h"
#include "cMano.h"
#include "cCoreEngine.h"
#include "cMatchPoints.h"



////////////////////////////////////////
//       intToEScore
/*! Help function to convert integer score in enum score
// \param int iVal : 
*/
static eGiocataScoreState intToEScore(int iVal)
{
    eGiocataScoreState eVal = SC_NOSCORE;
    ASSERT(0);
    return eVal;
}

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  cPendQuestion CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////
//       = 
/*! 
// \param const cPendQuestion &r : 
*/
void cPendQuestion::operator = (const cPendQuestion &r)
{
    m_eScore = r.m_eScore;
    m_bIsAMonte = r.m_bIsAMonte;
    m_iPlayerIx = r.m_iPlayerIx;
}

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CMANO CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! constructor
cMano::cMano()
{
    m_pCoreEngine = NULL;
    m_pGiocata = NULL;
    m_eManoState = MNST_WAIT_NEW_MANO;
    m_pScore = NULL;
    
    //initialize map for action tracing
    m_MapActionNames[MANO_WAITPL_TOPLAY] = "WAITPL_TOPLAY";
    m_MapActionNames[MANO_WAIPL_TORESP]  = "WAIPL_TORESP";
    m_MapActionNames[MANO_SAYBUIDA]      = "SAYBUIDA";
    m_MapActionNames[MANO_AMONTE]        = "AMONTE";
    m_MapActionNames[MANO_VADODENTRO]    = "VADODENTRO";
    m_MapActionNames[MANO_VADOVIA]       = "VADOVIA";
    m_MapActionNames[MANO_END]           = "END";
    m_MapActionNames[MANO_CHANGESCORE]   = "CHANGESCORE";
    m_MapActionNames[MANO_NO_ACTION]     = "NO_ACTION";

    
   

    //initilize map player status
    m_MapManoStatePl[PLAYER1] = MNST_WAIT_PLAY_PLAYER_1;
    m_MapManoStatePl[PLAYER2] = MNST_WAIT_PLAY_PLAYER_2;
    m_MapManoStatePl[PLAYER3] = MNST_WAIT_PLAY_PLAYER_3;
    m_MapManoStatePl[PLAYER4] = MNST_WAIT_PLAY_PLAYER_4;

    // responce status
    m_MapManoStateResp[PLAYER1] = MNST_WAIT_RESP_PLAYER_1;
    m_MapManoStateResp[PLAYER2] = MNST_WAIT_RESP_PLAYER_2;
    m_MapManoStateResp[PLAYER3] = MNST_WAIT_RESP_PLAYER_3;
    m_MapManoStateResp[PLAYER4] = MNST_WAIT_RESP_PLAYER_4;

    // player index map init
    m_MapPlayerOnState[MNST_WAIT_PLAY_PLAYER_1] = PLAYER1;
    m_MapPlayerOnState[MNST_WAIT_PLAY_PLAYER_2] = PLAYER2;
    m_MapPlayerOnState[MNST_WAIT_PLAY_PLAYER_3] = PLAYER3;
    m_MapPlayerOnState[MNST_WAIT_PLAY_PLAYER_4] = PLAYER4;

    // action on state init
    m_MapActionOnState[MNST_WAIT_PLAY_PLAYER_1] = MANO_WAITPL_TOPLAY;
    m_MapActionOnState[MNST_WAIT_PLAY_PLAYER_2] = MANO_WAITPL_TOPLAY;
    m_MapActionOnState[MNST_WAIT_PLAY_PLAYER_3] = MANO_WAITPL_TOPLAY;
    m_MapActionOnState[MNST_WAIT_PLAY_PLAYER_4] = MANO_WAITPL_TOPLAY;
    m_MapActionOnState[MNST_MANO_END] = MANO_END;
    m_MapActionOnState[MNST_WAIT_RESP_PLAYER_1] = MANO_WAIPL_TORESP;
    m_MapActionOnState[MNST_WAIT_RESP_PLAYER_2] = MANO_WAIPL_TORESP;
    m_MapActionOnState[MNST_WAIT_RESP_PLAYER_3] = MANO_WAIPL_TORESP;
    m_MapActionOnState[MNST_WAIT_RESP_PLAYER_4] = MANO_WAIPL_TORESP;

    

    m_pTable = 0;

}


////////////////////////////////////////
//       NextAction
/*! Next action. Call a function in cInvidoCore
*/
void    cMano::NextAction()
{
    size_t iNumAct = m_deqNextAction.size();
    if (iNumAct == 0)
    {
        // no action
        return ;
    }
    cActionItem Action = m_deqNextAction.front();
    eGiocataScoreState  eScore;
    //TRACE("Process action (NextAction): %d\n", Action.m_eNextAction);
    m_deqNextAction.pop_front();
    
    switch(Action.m_eNextAction)
    {
        case MANO_WAITPL_TOPLAY:
            ASSERT(Action.m_vct_iArg.size() > 0);
            // may be m_eNextAction is modified
            m_pCoreEngine->NtyWaitingPlayer_Toplay(Action.m_vct_iArg[0]);
            break;

        case MANO_AMONTE:
            m_pCoreEngine->Giocata_AMonte(); 
            break;

        case MANO_VADODENTRO:
            //m_pCoreEngine->;
            // TO DO
            ASSERT(0);
            break;

        case MANO_VADOVIA:
            m_pCoreEngine->Player_VaVia(Action.m_vct_iArg[0]);
            break;

        case MANO_WAIPL_TORESP:
            m_pCoreEngine->NtyWaitingPlayer_ToResp(Action.m_vct_iArg[0]);
            break;

        case MANO_END:
            m_pCoreEngine->Mano_End(); 
            break;

        case MANO_CHANGESCORE:
            eScore = intToEScore(Action.m_vct_iArg[0]);
            m_pCoreEngine->ChangeGiocataScore(eScore);
            // process the next action without waiting the next trigger
            NextAction();
            break;

        case MANO_NO_ACTION:
            // nothing to do
            // process the next action without waiting the next trigger
            NextAction();
            break;

        case MANO_SAYBUIDA:
            m_pCoreEngine->NtyPlayerSayBuiada(Action.m_vct_iArg[0]);
            break;

        default:
            ASSERT(0);
            break;
    }
    
    
}


////////////////////////////////////////
//       GiocataStart
/*! Giocata start notification. Initialize variables stored over mano.
*/
void  cMano::GiocataStart()
{
    // reset player change score  index
    m_iPlayerChangeScore = NOT_VALID_INDEX;
        
}

////////////////////////////////////////
//       MatchStart
/*! A new match is started
*/
void  cMano::MatchStart()
{
    m_iNumOfPlayers = m_pCoreEngine->GetNumOfPlayers();
    for (int i = 0; i <m_iNumOfPlayers; i++ )
    {
        cPlayer* pPlayer = m_pCoreEngine->GetPlayer(i) ;
        m_eTypePlayer[i] = pPlayer->GetType();
    }
      
    m_pTable = m_pCoreEngine->GetTable(); 
    
}

////////////////////////////////////////
//       NewMano
/*! Start a new mano
// \param int iPlayerIx : player that have to play
*/
void  cMano::NewMano(int iPlayerIx)
{
    clearQuestions();

    if (m_eManoState == MNST_WAIT_NEW_MANO ||
        m_eManoState == MNST_MANO_END)
    {
        
        ASSERT(iPlayerIx >= 0 && iPlayerIx < m_iNumOfPlayers);
        // set action
        add_Action(iPlayerIx, MANO_WAITPL_TOPLAY);
        
        //prepare state queue on table players
        int aTablePlayer[MAX_NUM_PLAYER];
        
        // calculate the array of player indexes
        m_pTable->CalcCircleIndex_Cust(aTablePlayer, iPlayerIx);
        m_deqTableState.clear();
        for (int i = 0; i < m_iNumOfPlayers; i++)
        {
            int iTmpPlayer = aTablePlayer[i];
            eManoStatus eVal = m_MapManoStatePl[iTmpPlayer];
            m_deqTableState.push_back(eVal);
        }
        m_deqTableState.push_back(MNST_MANO_END);

        // next state
        m_eManoState = nextTableState();
        

    }
    else
    {
         m_pCoreEngine->RaiseError("Mano state not correct\n");
         ASSERT(0);
    }
}

////////////////////////////////////////
//       Player_Play
/*! The player has played a card. Return true if the play was admitted.
// \param ong iPlayerIx : player index
*/
BOOL  cMano::Player_Play(int iPlayerIx)
{
    //TRACE("Player%d play state %d \n", iPlayerIx, m_eManoState);
    if (m_eManoState == MNST_WAIT_NEW_MANO ||
        m_eManoState == MNST_MANO_END)
    {
        //don't accept play if the mano is not initialized
        return FALSE;
    }
    
    if ( !IsPlayerOnCardPl() )
    {
        // status is not card playing: question is pending
        
        cPendQuestion PendQues;
        if (get_LastPendQuest(PendQues))
        {
            if (PendQues.m_iPlayerIx == iPlayerIx)
            {
                // same player has make a question: waiting the responce before play
                return FALSE;
            }
            if (PendQues.m_bIsAMonte)
            {
                // a monte call is pending: play a card is not admitted
                return FALSE;
            }
            else
            {
                // score question is pending: silent accept the question
                m_pScore->ChangeCurrentScore(PendQues.m_eScore, PendQues.m_iPlayerIx); 
                // clear question list
                clearQuestions();
                // save the player index that make a change
                m_iPlayerChangeScore = PendQues.m_iPlayerIx;
            }
        }
        else
        {
            // no question and no player state. Wrong state
            ASSERT(0);
        }
    }

    eManoStatus eExpectedState = m_MapManoStatePl[iPlayerIx];
    if (eExpectedState != m_eManoState)
    {
        // player is not allowed to play
        return FALSE;
    }

    // next state
    m_eManoState = nextTableState();
    // new player on play
    int iNewPlayer = m_MapPlayerOnState[m_eManoState];
    // new action
    eFN_MANOACTION eAct_Type = m_MapActionOnState[m_eManoState];

    add_Action(iNewPlayer, eAct_Type);

   
    return TRUE;
}


////////////////////////////////////////
//       Player_Say
/*! Player say something
// \param int iPlayerIx : index of the player that say
*/
BOOL  cMano::Player_Say(int iPlayerIx, eSayPlayer eSay)
{
    //TRACE("Player%d say %d, state %d \n", iPlayerIx, eSay,m_eManoState);
    if (m_eManoState == MNST_WAIT_NEW_MANO)
    {
        //don't accept calls if the mano is not initialized
        ASSERT(0);
        return FALSE;
    }
    
    BOOL bRes = TRUE;
    
    
    return bRes;
}


////////////////////////////////////////
//       isScoreBigClosed
/*! Return TRUE if the first argument is bigger as the second in the closest manner.
// \param eGiocataScoreState eS1 : first score
// \param eGiocataScoreState eS2 : second score
*/
BOOL cMano::isScoreBigClosed(eGiocataScoreState eS1, eGiocataScoreState eS2)
{
    BOOL bRes = FALSE;

    // eS2 is the smaller score
    eGiocataScoreState eTmp = m_mapScoreScNext[eS2];
    if (eTmp == eS1)
    {
        // ok the 2 score are enought closed
        bRes = TRUE;
    }
    return bRes;
}

////////////////////////////////////////
//       actionOnQuestion
/*!Select the action of the question call
// \param cPendQuestion& PendQues : last question done
*/
void  cMano::actionOnQuestion(cPendQuestion& PendQues)
{
  
    if ( IsPlayerOnCardPl() )    
    {
        // save the state because we are going in calling phase
        save_StateBeforeQuest();
    }   

    //prepare state queue on table players
    int aTablePlayer[MAX_NUM_PLAYER];
    // calculate the array of player indexes
    m_pTable->CalcCircleIndex_Cust(aTablePlayer, PendQues.m_iPlayerIx);
    // use the index of the next player
    int iPlayerNext = aTablePlayer[1];
    add_Action(iPlayerNext, MANO_WAIPL_TORESP);

    m_eManoState = m_MapManoStateResp[iPlayerNext];
}


////////////////////////////////////////
//       actionWithoutQuestion
/*! There is no question pending, take an action to retrigger the state
*/
void  cMano::actionWithoutQuestion()
{
    ASSERT(m_deqPendQuestion.size() == 0);
    if ( !IsPlayerOnCardPl() )
    {
        // status is not card playing, but responding
        // restore the old state playing
        restore_StateBeforeQuest();

    }
    else
    {
        // retrigger the play status
        int iPlayerIx = m_MapPlayerOnState[m_eManoState];
        eFN_MANOACTION eAct_Type = m_MapActionOnState[m_eManoState];
        add_Action(iPlayerIx, eAct_Type);
    }
}



////////////////////////////////////////
//       Reset
/*! Reset mano state
*/
void  cMano::Reset()
{
    m_deqNextAction.clear();
    m_eManoState = MNST_WAIT_NEW_MANO;
}


////////////////////////////////////////
//       add_Action
/*! Add an action on the queue
// \param int iPar_0 : Parameter 0 of action (player, score)
// \param eFN_MANOACTION eAct : 
*/
void cMano::add_Action(int iPar_0, eFN_MANOACTION eAct)
{
    cActionItem Action;

    Action.m_eNextAction = eAct;
    Action.m_vct_iArg.push_back(iPar_0);
    if (eAct == MANO_WAITPL_TOPLAY ||
        eAct == MANO_WAIPL_TORESP)
    {
        // remove action scheduled but not yet executed because obsolete
        removeObsoleteActions();

    }
    m_deqNextAction.push_back(Action);

    STRING strActName = m_MapActionNames[eAct];
    //TRACE("cMano-> Action scheduled %s, param: %d\n", strActName.c_str(), iPar_0 );    
}


////////////////////////////////////////
//       removeObsoleteActions
/*! Remove all aboslete actions from queue. Obsolete actions are MANO_WAITPL_TOPLAY and
// MANO_WAIPL_TORESP. An action becomes obsolete when another action comes that substitute 
// the old one.
*/
void cMano::removeObsoleteActions()
{
    size_t iNumAct = m_deqNextAction.size();
    for (int i = 0; i < iNumAct; i++)
    {
        cActionItem Action = m_deqNextAction[i];
        if (Action.m_eNextAction == MANO_WAITPL_TOPLAY ||
            Action.m_eNextAction == MANO_WAIPL_TORESP)
        {
            // this is an obselete action, make it inoffensive
            m_deqNextAction[i].m_eNextAction = MANO_NO_ACTION;
        }
    }
}

////////////////////////////////////////
//       get_LastPendQuest
/*! Provides the last pending question. Return TRUE if a question is present.
// \param cPendQuestion& PendQues : 
*/
BOOL cMano::get_LastPendQuest(cPendQuestion& PendQues)
{
    BOOL bRes = FALSE;
    size_t iNumEle = m_deqPendQuestion.size();
    if (iNumEle > 0)
    {
        PendQues = m_deqPendQuestion[iNumEle - 1];
        bRes = TRUE;
    }
    return bRes;
}


////////////////////////////////////////
//       restore_StateBeforeQuest
/*! Restore the state before the question was done
*/
void cMano::restore_StateBeforeQuest()
{
    m_eManoState = m_eOldManoState;
    eFN_MANOACTION eAct_Type = m_MapActionOnState[m_eManoState];
    
    int iPlayerIx = m_MapPlayerOnState[m_eManoState];
    add_Action(iPlayerIx, eAct_Type);
}


////////////////////////////////////////
//       save_StateBeforeQuest
/*! Save the state before question
*/
void cMano::save_StateBeforeQuest()
{
    m_eOldManoState = m_eManoState;
}


////////////////////////////////////////
//       clearQuestions
/*! Clear all questions pending
*/
void    cMano::clearQuestions()
{
    //TRACE("Clear all pending questions\n");
    m_deqPendQuestion.clear();
}


////////////////////////////////////////
//       IsPlayerOnCardPl
/*! Return true if on player have to play, false otherwise
*/
BOOL cMano::IsPlayerOnCardPl()
{
    BOOL bRes = FALSE;
    if (m_eManoState == MNST_WAIT_PLAY_PLAYER_1 || 
        m_eManoState == MNST_WAIT_PLAY_PLAYER_2 ||
        m_eManoState == MNST_WAIT_PLAY_PLAYER_3 || 
        m_eManoState == MNST_WAIT_PLAY_PLAYER_4 )
    {
        bRes =  TRUE;
    }
    return bRes;
}



////////////////////////////////////////
//       nextTableState
/*! Provides the next on the mano. 
*/
eManoStatus  cMano::nextTableState()
{
    ASSERT(m_deqTableState.size() > 0);
    eManoStatus   eRetState;
    if (m_deqTableState.size() > 0)
    {
        eRetState = m_deqTableState[0];
        m_deqTableState.pop_front();
    }


    return eRetState;
}


////////////////////////////////////////
//       nextAvailSayScore
/*! Provides the next available score
// \param eSayPlayer* peSayAvail : 
*/
BOOL cMano::nextAvailSayScore(eSayPlayer* peSayAvail)
{
    BOOL bRet = TRUE;
    
    return bRet;
}

