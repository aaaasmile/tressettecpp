//cMano.cpp

#include "StdAfx.h"

#include "cMano.h"
#include "cInvidoCore.h"
#include "cMatchPoints.h"
#include "TraceService.h"

static const char* stalpzActionName[10] =
{
    "MANO_WAITPL_TOPLAY",
    "MANO_WAIPL_TORESP",
    "MANO_SAYBUIDA",
    "MANO_AMONTE",
    "MANO_VADODENTRO",
    "MANO_VADOVIA",
    "MANO_END",
    "MANO_CHANGESCORE",
    "MANO_NO_ACTION"
};

static const char*  stalpzManoState[10] =
{
    "MNST_WAIT_NEW_MANO"      ,
    "MNST_WAIT_PLAY_PLAYER_1" ,
    "MNST_WAIT_PLAY_PLAYER_2" ,
    "MNST_WAIT_PLAY_PLAYER_3" ,
    "MNST_WAIT_PLAY_PLAYER_4" ,
    "MNST_MANO_END",
    "MNST_WAIT_RESP_PLAYER_1" ,
    "MNST_WAIT_RESP_PLAYER_2",
    "MNST_WAIT_RESP_PLAYER_3" ,
    "MNST_WAIT_RESP_PLAYER_4"
};

////////////////////////////////////////
//       intToEScore
/*! Help function to convert integer score in enum score
// \param int iVal :
*/
static eGiocataScoreState intToEScore(int iVal)
{
    eGiocataScoreState eVal = SC_PATTA;
    switch (iVal)
    {
    case 0:
        break;
    case 1:
        eVal = SC_CANELA;
        break;
    case 3:
        eVal = SC_INVIDO;
        break;
    case 6:
        eVal = SC_TRASMAS;
        break;
    case 9:
        eVal = SC_TRASMASNOEF;
        break;
    case 12:
        eVal = SC_FUERAJEUQ;
        break;
    case 24:
        eVal = SC_PARTIDA;
        break;

    default:
        ASSERT(0);
    }
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
    m_pInvidoCore = NULL;
    m_pGiocata = NULL;
    m_eManoState = MNST_WAIT_NEW_MANO;
    m_pScore = NULL;

    //initialize map for action tracing
    m_MapActionNames[MANO_WAITPL_TOPLAY] = "WAITPL_TOPLAY";
    m_MapActionNames[MANO_WAIPL_TORESP] = "WAIPL_TORESP";
    m_MapActionNames[MANO_SAYBUIDA] = "SAYBUIDA";
    m_MapActionNames[MANO_AMONTE] = "AMONTE";
    m_MapActionNames[MANO_VADODENTRO] = "VADODENTRO";
    m_MapActionNames[MANO_VADOVIA] = "VADOVIA";
    m_MapActionNames[MANO_END] = "END";
    m_MapActionNames[MANO_CHANGESCORE] = "CHANGESCORE";
    m_MapActionNames[MANO_NO_ACTION] = "NO_ACTION";

    // initialize map for conversion say and score
    m_MapSayScore[AMONTE] = SC_AMONTE;
    m_MapSayScore[INVIDO] = SC_INVIDO;
    m_MapSayScore[TRASMAS] = SC_TRASMAS;
    m_MapSayScore[TRASMASNOEF] = SC_TRASMASNOEF;
    m_MapSayScore[FUERAJEUQ] = SC_FUERAJEUQ;
    m_MapSayScore[PARTIDA] = SC_PARTIDA;

    // score say map
    m_mapScoreSay[SC_AMONTE] = AMONTE;
    m_mapScoreSay[SC_INVIDO] = INVIDO;
    m_mapScoreSay[SC_TRASMAS] = TRASMAS;
    m_mapScoreSay[SC_TRASMASNOEF] = TRASMASNOEF;
    m_mapScoreSay[SC_FUERAJEUQ] = FUERAJEUQ;
    m_mapScoreSay[SC_PARTIDA] = PARTIDA;

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

    // score - score next
    m_mapScoreScNext[SC_CANELA] = SC_INVIDO;
    m_mapScoreScNext[SC_INVIDO] = SC_TRASMAS;
    m_mapScoreScNext[SC_TRASMAS] = SC_TRASMASNOEF;
    m_mapScoreScNext[SC_TRASMASNOEF] = SC_FUERAJEUQ;
    m_mapScoreScNext[SC_FUERAJEUQ] = SC_PARTIDA;

    m_pTable = 0;

    // get the tracer
    m_pTracer = TraceService::Instance();

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
        return;
    }
    cActionItem Action = m_deqNextAction.front();
    m_deqNextAction.pop_front();

    eGiocataScoreState  eScore;
    //TRACE("Process action (NextAction): %d\n", Action.m_eNextAction);
    if (m_pTracer->AddNewEntry(1, 1, EntryTraceDetail::TR_INFO, __FILE__, __LINE__))
        m_pTracer->AddCommentToLastEntry("Process action (NextAction): %s", stalpzActionName[Action.m_eNextAction]);

    switch (Action.m_eNextAction)
    {
    case MANO_WAITPL_TOPLAY:
        ASSERT(Action.m_vct_iArg.size() > 0);
        // may be m_eNextAction is modified
        m_pInvidoCore->NtyWaitingPlayer_Toplay(Action.m_vct_iArg[0]);
        if (m_pTracer->AddNewEntry(1, 2, EntryTraceDetail::TR_INFO, __FILE__, __LINE__))
            m_pTracer->AddCommentToLastEntry("Wait play player: %d", Action.m_vct_iArg[0]);
        break;

    case MANO_AMONTE:
        m_pInvidoCore->Giocata_AMonte();
        break;

    case MANO_VADODENTRO:
        //m_pInvidoCore->;
        // TO DO
        ASSERT(0);
        break;

    case MANO_VADOVIA:
        m_pInvidoCore->Player_VaVia(Action.m_vct_iArg[0]);
        break;

    case MANO_WAIPL_TORESP:
        m_pInvidoCore->NtyWaitingPlayer_ToResp(Action.m_vct_iArg[0]);
        break;

    case MANO_END:
        m_pInvidoCore->Mano_End();
        break;

    case MANO_CHANGESCORE:
        eScore = intToEScore(Action.m_vct_iArg[0]);
        m_pInvidoCore->ChangeGiocataScore(eScore);
        // process the next action without waiting the next trigger
        NextAction();
        break;

    case MANO_NO_ACTION:
        // nothing to do
        // process the next action without waiting the next trigger
        NextAction();
        break;

    case MANO_SAYBUIDA:
        m_pInvidoCore->NtyPlayerSayBuiada(Action.m_vct_iArg[0]);
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
    m_iNumOfPlayers = m_pInvidoCore->GetNumOfPlayers();
    for (int i = 0; i < m_iNumOfPlayers; i++)
    {
        cPlayer* pPlayer = m_pInvidoCore->GetPlayer(i);
        m_eTypePlayer[i] = pPlayer->GetType();
    }

    m_pTable = m_pInvidoCore->GetTable();

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
        m_pInvidoCore->RaiseError("Mano state not correct\n");
        ASSERT(0);
    }
}

////////////////////////////////////////
//       Player_Play
/*! The player has played a card. Return true if the play was admitted.
// \param ong iPlayerIx : player index
// \param vadoDentro:  true if it was played with vado dentro 
*/
BOOL  cMano::Player_Play(int iPlayerIx, BOOL vadoDentro)
{
    //TRACE("Player%d play state %d \n", iPlayerIx, m_eManoState);
    if (m_pTracer->AddNewEntry(1, 3, EntryTraceDetail::TR_INFO, __FILE__, __LINE__))
        m_pTracer->AddCommentToLastEntry("Player%d play state %s", iPlayerIx, stalpzManoState[m_eManoState]);

    if (m_eManoState == MNST_WAIT_NEW_MANO ||
        m_eManoState == MNST_MANO_END)
    {
        //don't accept play if the mano is not initialized
        if (m_pTracer->AddNewEntry(1, 4, EntryTraceDetail::TR_WARN, __FILE__, __LINE__))
            m_pTracer->AddCommentToLastEntry("Don't accept card play %d %s", iPlayerIx, stalpzManoState[m_eManoState]);
        return FALSE;
    }

    if (!IsPlayerOnCardPl())
    {
        // status is not card playing: question is pending

        cPendQuestion PendQues;
        if (get_LastPendQuest(PendQues))
        {
            if (PendQues.m_iPlayerIx == iPlayerIx)
            {
                // same player has make a question: waiting the responce before play
                if (m_pTracer->AddNewEntry(1, 5, EntryTraceDetail::TR_WARN, __FILE__, __LINE__))
                    m_pTracer->AddCommentToLastEntry("Player %d, question is pending, wait responce", iPlayerIx);

                return FALSE;
            }
            if (PendQues.m_bIsAMonte)
            {
                // a monte call is pending: play a card is not admitted
                if (m_pTracer->AddNewEntry(1, 6, EntryTraceDetail::TR_WARN, __FILE__, __LINE__))
                    m_pTracer->AddCommentToLastEntry("Player %d, monte call is pending, wait responce", iPlayerIx);

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
            if (m_pTracer->AddNewEntry(1, 7, EntryTraceDetail::TR_ERR, __FILE__, __LINE__))
                m_pTracer->AddCommentToLastEntry("no question and no player state. Wrong state");
            ASSERT(0);
        }
    }

    eManoStatus eExpectedState = m_MapManoStatePl[iPlayerIx];
    if (eExpectedState != m_eManoState)
    {
        // player is not allowed to play
        if (m_pTracer->AddNewEntry(1, 8, EntryTraceDetail::TR_WARN, __FILE__, __LINE__))
            m_pTracer->AddCommentToLastEntry("Player %d, is not allowed to play, expected state %s: ", iPlayerIx, stalpzManoState[eExpectedState]);
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
    TRACE("Player%d say %d, state %d \n", iPlayerIx, eSay, m_eManoState);
    if (m_eManoState == MNST_WAIT_NEW_MANO ||
        m_eManoState == MNST_MANO_END)
    {
        //don't accept calls if the mano is not initialized
        return FALSE;
    }

    BOOL bRes = TRUE;

    if (eSay == INVIDO ||
        eSay == TRASMAS ||
        eSay == TRASMASNOEF ||
        eSay == FUERAJEUQ ||
        eSay == PARTIDA)
    {
        handle_ScoreCalled(iPlayerIx, eSay);
    }
    else if (eSay == AMONTE)
    {
        // a monte request
        handle_MonteCall(iPlayerIx, eSay);
    }
    else if (eSay == VABENE ||
        eSay == GIOCA)
    {
        handleVaBene(iPlayerIx);
    }
    else if (eSay == VADOVIA)
    {
        handleVadoVia(iPlayerIx);
    }
    else if (eSay == CHIAMADIPIU || eSay == CHIAMA_BORTOLO)
    {
        handle_CallMoreOrInvido(iPlayerIx);
    }
    else if (eSay == NO)
    {
        handle_CallNo(iPlayerIx);
    }
    else
    {
        ASSERT(0);
    }


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
//       handle_ScoreCalled
/*! A score change was called
// \param eSayPlayer eSay :
*/
void cMano::handle_ScoreCalled(int iPlayerIx, eSayPlayer eSay)
{
    int iAttScore = m_pScore->GetCurrScore();
    eGiocataScoreState   eScore;
    eScore = m_MapSayScore[eSay];

    cPendQuestion PendScoreQuesLast;
    cPendQuestion PendQuesMonte;
    if (get_LastPendScoreQuest(PendScoreQuesLast))
    {
        // pending point question
        // score call is admitted only if the pending question  was a small of the call score from opponent
        // How small? only the closest call is admitted (canela->invido->trasmas->noef->foera->partida)
        if (PendScoreQuesLast.m_iPlayerIx != iPlayerIx &&
            isScoreBigClosed(eScore, PendScoreQuesLast.m_eScore))
        {
            // score call admitted

            // implicit change of score to the first call
            m_pScore->ChangeCurrentScore(PendScoreQuesLast.m_eScore, PendScoreQuesLast.m_iPlayerIx);
            // save the player index that make a change
            m_iPlayerChangeScore = PendScoreQuesLast.m_iPlayerIx;
            add_Action(PendScoreQuesLast.m_eScore, MANO_CHANGESCORE);


            // new question state
            cPendQuestion  NewPendQues(FALSE, eScore, iPlayerIx);
            m_deqPendQuestion.push_back(NewPendQues);

            actionOnQuestion(NewPendQues);

        }
        else
        {
            // call not admitted
            add_Action(iPlayerIx, MANO_SAYBUIDA);
            cPendQuestion  PendTmp;
            if (get_LastPendQuest(PendTmp))
            {
                // repeat trigger to restore the status before call
                actionOnQuestion(PendTmp);
            }
            else
            {
                ASSERT(0);
            }
        }
    }
    else if (get_LastPendQuest(PendQuesMonte))
    {
        // if a question is pending, it could be only a monte
        // a monte pending question 
        ASSERT(PendQuesMonte.m_bIsAMonte);
        if (iPlayerIx == m_iPlayerChangeScore)
        {
            // the same player can't increment the score
            // call not admitted
            add_Action(iPlayerIx, MANO_SAYBUIDA);
            actionOnQuestion(PendQuesMonte);
        }

    }
    else if (eScore > iAttScore)
    {
        if (iPlayerIx == m_iPlayerChangeScore)
        {
            // the same player can't change the score
            add_Action(iPlayerIx, MANO_SAYBUIDA);
            actionWithoutQuestion();
        }
        else
        {
            // no pending question, call accepted
            cPendQuestion  NewPendQues(FALSE, eScore, iPlayerIx);
            m_deqPendQuestion.push_back(NewPendQues);

            actionOnQuestion(NewPendQues);
        }
    }
    else
    {
        // invalid callbecause eScore is to small
        add_Action(iPlayerIx, MANO_SAYBUIDA);
        actionWithoutQuestion();
    }
}



////////////////////////////////////////
//       handle_MonteCall
/*! A Monte call was said
// \param int iPlayerIx :
// \param eSayPlayer eSay :
*/
void cMano::handle_MonteCall(int iPlayerIx, eSayPlayer eSay)
{
    cPendQuestion PendQuesLast;

    if (get_LastPendQuest(PendQuesLast))
    {
        if (PendQuesLast.m_bIsAMonte)
        {
            // there is a MONTE pending question
            if (PendQuesLast.m_iPlayerIx != iPlayerIx)
            {
                // ok this giocata goes a monte
                giocata_Go_Amonte(iPlayerIx);
            }
            else
            {
                // the same player call a monte, ignore it
            }
        }
        else
        {
            // insert the question
            add_QuestMonte(iPlayerIx);
        }
    }
    else
    {
        // insert the question
        add_QuestMonte(iPlayerIx);
    }
}


////////////////////////////////////////
//       giocata_Go_Amonte
/*! Giocata is going a monte, set action and state.
// \param int iPlayerIx : player that make the giocata a monte
*/
void cMano::giocata_Go_Amonte(int iPlayerIx)
{
    m_pScore->ChangeCurrentScore(SC_AMONTE, iPlayerIx);
    add_Action(iPlayerIx, MANO_AMONTE);
    m_eManoState = MNST_WAIT_NEW_MANO;

    // clear question list
    clearQuestions();
}

////////////////////////////////////////
//       handle_CallMoreOrInvido
/*! Handle call more
// \param int iPlayerIx :
*/
void cMano::handle_CallMoreOrInvido(int iPlayerIx)
{
    // Nothing to do here
}


////////////////////////////////////////
//       handle_CallNo
/*! Negative responce
// \param int iPlayerIx :
*/
void  cMano::handle_CallNo(int iPlayerIx)
{
    cPendQuestion PendQues;
    if (get_LastPendQuest(PendQues))
    {
        // there is question pending, the responce is no
        // no is admitted only on "A monte" call
        if (PendQues.m_bIsAMonte)
        {
            // remove the monte question
            remove_LastQuestion();
            if (get_LastPendQuest(PendQues))
            {
                //there are other call pending
                actionOnQuestion(PendQues);
            }
            else
            {
                // no more question
                // action on no question
                actionWithoutQuestion();
            }
        }
        else
        {
            //not admitted, call is not amonte
            add_Action(iPlayerIx, MANO_SAYBUIDA);
            actionOnQuestion(PendQues);
        }
    }
    else
    {
        // not admitted
        add_Action(iPlayerIx, MANO_SAYBUIDA);
        actionWithoutQuestion();
    }

}

////////////////////////////////////////
//       handleVaBene
/*! Player say "Va bene"
// \param iPlayerIx : player index
*/
void  cMano::handleVaBene(int iPlayerIx)
{

    cPendQuestion PendQues;
    if (get_LastPendQuest(PendQues))
    {
        // question was pending
        if (PendQues.m_bIsAMonte)
        {
            // question was a monte, accept it
            giocata_Go_Amonte(iPlayerIx);

        }
        else
        {
            // change score question, set the new score
            m_pScore->ChangeCurrentScore(PendQues.m_eScore, PendQues.m_iPlayerIx);
            // save the player index that make a change
            m_iPlayerChangeScore = PendQues.m_iPlayerIx;
            add_Action(PendQues.m_eScore, MANO_CHANGESCORE);
            // clear question list
            clearQuestions();

            //restore the state before question
            restore_StateBeforeQuest();
        }

    }
    else
    {
        // no question was pending
        add_Action(iPlayerIx, MANO_SAYBUIDA);
        actionWithoutQuestion();
    }
}

////////////////////////////////////////
//       handleVadoVia
/*! Handle player say "Vado Via"
// \param int iPlayerIx : player that say vado via
*/
void  cMano::handleVadoVia(int iPlayerIx)
{
    cPendQuestion PendQues;
    if (get_LastPendQuest(PendQues))
    {
        if (PendQues.m_iPlayerIx != iPlayerIx &&
            !PendQues.m_bIsAMonte)
        {
            // last change score question not accepted
            add_Action(iPlayerIx, MANO_VADOVIA);
            // clear question list
            clearQuestions();
            m_eManoState = MNST_WAIT_NEW_MANO;

        }
        else
        {
            // amonte question or the player was already asking
            add_Action(iPlayerIx, MANO_SAYBUIDA);
            // restore trigger and state
            actionOnQuestion(PendQues);
        }
    }
    else
    {
        // no question was pending, the player leave the giocata
        add_Action(iPlayerIx, MANO_VADOVIA);
        // clear question list
        clearQuestions();
        m_eManoState = MNST_WAIT_NEW_MANO;
    }

}

////////////////////////////////////////
//       actionOnQuestion
/*!Select the action of the question call
// \param cPendQuestion& PendQues : last question done
*/
void  cMano::actionOnQuestion(cPendQuestion& PendQues)
{

    if (IsPlayerOnCardPl())
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
    if (!IsPlayerOnCardPl())
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
//       add_QuestMonte
/*! Add a monte question
// \param int iPlayerIx :
*/
void cMano::add_QuestMonte(int iPlayerIx)
{
    // add the MONTE question to the queue
    cPendQuestion  PendQues(TRUE, SC_AMONTE, iPlayerIx);
    m_deqPendQuestion.push_back(PendQues);

    actionOnQuestion(PendQues);
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
    TRACE("cMano-> Action scheduled %s, param: %d\n", strActName.c_str(), iPar_0);
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
//       get_LastPendScoreQuest
/*! Provides the last pending question with points (exclude calls a monte)
// \param cPendQuestion& PendQues :
*/
BOOL cMano::get_LastPendScoreQuest(cPendQuestion& PendQues)
{
    BOOL bRes = FALSE;
    size_t iNumEle = m_deqPendQuestion.size();
    int iCurr = 0;
    while (iNumEle - iCurr > 0)
    {
        size_t iIndexLast = iNumEle - iCurr - 1;
        PendQues = m_deqPendQuestion[iIndexLast];

        if (!PendQues.m_bIsAMonte)
        {
            // this is a score question, ok we have it
            bRes = TRUE;
            break;
        }
        iCurr++;
    }
    return bRes;
}


////////////////////////////////////////
//       remove_LastQuestion
/*! Remove the last question
*/
void cMano::remove_LastQuestion()
{
    size_t iNumEle = m_deqPendQuestion.size();
    if (iNumEle > 0)
    {
        m_deqPendQuestion.pop_back();
    }
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
    TRACE("Clear all pending questions\n");
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
        m_eManoState == MNST_WAIT_PLAY_PLAYER_4)
    {
        bRes = TRUE;
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
    eManoStatus   eRetState = MNST_WAIT_NEW_MANO;
    if (m_deqTableState.size() > 0)
    {
        eRetState = m_deqTableState[0];
        m_deqTableState.pop_front();
    }


    return eRetState;
}

void cMano::CommandWithPendingQuestion(cPendQuestion& PendQues, VCT_COMMANDS& vct_Commands, int iPlayerIndex)
{
    if (iPlayerIndex == PendQues.m_iPlayerIx)
    {
        // if pending question is from the same player,
        // he can say anything
        vct_Commands.clear();
        return;
    }
    // the question is an opponent question
    if (PendQues.m_bIsAMonte)
    {
        // pending question is "a monte"
        vct_Commands.push_back(VABENE);
        vct_Commands.push_back(NO);
    }
    else
    {
        // pending question is score
        vct_Commands.push_back(VADOVIA);
        vct_Commands.push_back(AMONTE);
        vct_Commands.push_back(GIOCA);
        // get the next score
        if (PendQues.m_eScore != PARTIDA)
        {
            // it is possible to call more score
            eGiocataScoreState eNextScore = m_mapScoreScNext[PendQues.m_eScore];
            eSayPlayer eCallMore = m_mapScoreSay[eNextScore];
            vct_Commands.push_back(eCallMore);
        }
    }
}

void cMano::GetMoreCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex)
{
    vct_Commands.clear();

    cPendQuestion PendQues;
    if (get_LastPendQuest(PendQues))
    {
        CommandWithPendingQuestion(PendQues, vct_Commands, iPlayerIndex);
        return;
    }
    vct_Commands.push_back(VADODENTRO);
    if (m_iPlayerChangeScore == iPlayerIndex)
    {
        vct_Commands.push_back(CHIAMADIPIU);
    }
    else if (m_iPlayerChangeScore == NOT_VALID_INDEX) {
        vct_Commands.push_back(CHIAMA_BORTOLO);
    }
}


////////////////////////////////////////
//       GetAdmittedCommands
/*! Provides all possible call commands on the actual game point.
*/
void    cMano::GetAdmittedCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex)
{
    vct_Commands.clear();

    cPendQuestion PendQues;
    eSayPlayer eSayAvail;
    if (get_LastPendQuest(PendQues))
    {
        CommandWithPendingQuestion(PendQues, vct_Commands, iPlayerIndex);
        return;
    }

    // no pending questions

    // check if the giocata is a monte
    if (isGiocataAMonte())
    {
        // game is gone a monte, no command available
        vct_Commands.clear();
    }
    else
    {
        // we are on game 
        vct_Commands.push_back(VADOVIA);
        vct_Commands.push_back(AMONTE);
        if (m_iPlayerChangeScore != iPlayerIndex)
        {
            // player can call in order to increase the score
            if (nextAvailSayScore(&eSayAvail))
            {
                vct_Commands.push_back(eSayAvail);
            }
        }
        else
        {
            // increment score not admitted
        }
    }
}

////////////////////////////////////////
//       nextAvailSayScore
/*! Provides the next available score
// \param eSayPlayer* peSayAvail :
*/
BOOL cMano::nextAvailSayScore(eSayPlayer* peSayAvail)
{
    BOOL bRet = TRUE;
    ASSERT(peSayAvail);
    eSayPlayer eTmp = AMONTE;

    // retrive current score
    cMatchPoints*  pMatchPoints = m_pInvidoCore->GetMatchPointsObj();
    ASSERT(pMatchPoints);
    eGiocataScoreState eCurrScore = pMatchPoints->GetCurrScore();


    if (eCurrScore == SC_PARTIDA)
    {
        // there is no points bigger as "partida"
        bRet = FALSE;
    }
    else
    {
        switch (eCurrScore)
        {
        case SC_CANELA:
            eTmp = INVIDO;
            break;
        case SC_INVIDO:
            eTmp = TRASMAS;
            break;

        case SC_TRASMAS:
            eTmp = TRASMASNOEF;
            break;

        case SC_TRASMASNOEF:
            eTmp = FUERAJEUQ;
            break;

        case SC_FUERAJEUQ:
            eTmp = PARTIDA;
            break;

        default:
            ASSERT(0);
            break;
        }
    }
    *peSayAvail = eTmp;
    return bRet;
}


////////////////////////////////////////
//       isGiocataAMonte
/*! TRUE if the giocata is gone a monte, FALSE otherwise.
*/
BOOL cMano::isGiocataAMonte()
{
    BOOL bRet = FALSE;
    cMatchPoints*  pMatchPoints = m_pInvidoCore->GetMatchPointsObj();
    ASSERT(pMatchPoints);
    eGiocataScoreState eCurrScore = pMatchPoints->GetCurrScore();
    if (eCurrScore == SC_AMONTE ||
        eCurrScore == SC_PATTA)
    {
        bRet = TRUE;
    }
    return bRet;
}

