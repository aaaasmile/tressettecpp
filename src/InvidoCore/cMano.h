

//cMano.h

#ifndef ____CMANO_H
#define ____CMANO_H

#include "cInvidoCoreEnv.h"
#include "AlgPlayerInterface.h"
#include <deque>
#include <map>

class cInvidoCore;
class cGiocata;
class cMatchPoints;

//! enum action type
enum eFN_MANOACTION
{
    //! wait player to play
    MANO_WAITPL_TOPLAY = 0,
    //! wait to respond
    MANO_WAIPL_TORESP,
    //! say something not correct
    MANO_SAYBUIDA,
    //! go a monte
    MANO_AMONTE,
    //! action vado dentro
    MANO_VADODENTRO,
    //! action vado via
    MANO_VADOVIA,
    //! mano is terminated
    MANO_END,
    //! mano change score
    MANO_CHANGESCORE,
    //! no action
    MANO_NO_ACTION
};

typedef std::map<eSayPlayer, eGiocataScoreState> MAP_SAY_SCORE;
typedef std::map<eGiocataScoreState, eSayPlayer> MAP_SCORE_SAY;
typedef std::map<eFN_MANOACTION, STRING>      MAP_ACTION_NAMES;
typedef std::map<int, eManoStatus>            MAP_PL_STATUS;
typedef std::map<eManoStatus, int>            MAP_STATUS_PL;
typedef std::map<eManoStatus, eFN_MANOACTION> MAP_STATUS_ACTION;
typedef std::map<eGiocataScoreState, eGiocataScoreState>   MAP_SCORE_SCORENEXT;
typedef std::deque< eManoStatus >             DEQ_TABLESTATE;


//////////////////////////////////////////////////////////////////////

//! class cPendQuestion
/** pendi question information
*/
class cPendQuestion
{
public:
    cPendQuestion(){m_bIsAMonte = FALSE; m_eScore= SC_CANELA; m_iPlayerIx = NOT_VALID_INDEX;}
    cPendQuestion(BOOL bVal, eGiocataScoreState eSc, int iPl){m_bIsAMonte = bVal; m_eScore= eSc; m_iPlayerIx = iPl;}

    //! assignement operator
    void operator = (const cPendQuestion &r); 

    //! score of the pending call
    eGiocataScoreState   m_eScore;
    //! flag of a monte question
    BOOL                 m_bIsAMonte;
    //! player index of the call
    int                  m_iPlayerIx;
};

typedef std::deque< cPendQuestion > DEQ_PENDQUESTION;

//////////////////////////////////////////////////////////////////////

#ifndef VCT_INT
    typedef std::vector<int> VCT_INT;
#endif

//! class cActionItem
/** action item in the queue
*/
class cActionItem
{
public:
    //! constructor
    cActionItem(){m_eNextAction = MANO_NO_ACTION;}

    eFN_MANOACTION      m_eNextAction;
    //! argument list for action calls
    VCT_INT            m_vct_iArg;

};

typedef std::deque< cActionItem > DEQ_ACTIONITEM;


class cPlayersOnTable;
class TraceService;
/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CMANO CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cMano
/**
Class cMano to manage when 2 players play a card
*/
class cMano
{
public:
    cMano();
    void    SetCore(cInvidoCore* pVal){m_pInvidoCore = pVal;}
    void    SetGiocata(cGiocata* pVal){ m_pGiocata = pVal;}
    void    SetScore(cMatchPoints* pVal){m_pScore = pVal;}
    //! start a new mano
    void    NewMano(int iPlayerIx);
    //! on mano player say something
    BOOL    Player_Say(int iPlayerIx, eSayPlayer eSay);
    // player play a card
    BOOL    Player_Play(int iPlayerIx, BOOL vadoDentro);
    //! reset a mano
    void    Reset();
    //! next action
    void    NextAction();
    //! get state
    eManoStatus GetState(){return m_eManoState;}
    //! start  match
    void    MatchStart();
    //! provides available calls
    void    GetAdmittedCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex);
    void    GetMoreCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex);
    void    CommandWithPendingQuestion(cPendQuestion& PendQues, VCT_COMMANDS& vct_Commands, int iPlayerIndex);
    //! giocata start notification
    void    GiocataStart();

private:
    void    actionOnQuestion(cPendQuestion&  PendQues);
    void    handleVadoVia(int iPlayerIx);
    void    handleVaBene(int iPlayerIx);
    void    handle_ScoreCalled(int iPlayerIx, eSayPlayer eSay);
    void    handle_MonteCall(int iPlayerIx, eSayPlayer eSay);
    void    handle_CallMoreOrInvido(int iPlayerIx);
    void    handle_CallNo(int iPlayerIx);
    void    add_Action(int iPlayerIx, eFN_MANOACTION eAct);
    BOOL    get_LastPendQuest(cPendQuestion& PendQues);
    void    add_QuestMonte(int iPlayerIx);
    void    remove_LastQuestion();
    void    restore_StateBeforeQuest();
    void    clearQuestions();
    void    save_StateBeforeQuest();
    BOOL    IsPlayerOnCardPl();
    eManoStatus  nextTableState();
    BOOL    nextAvailSayScore(eSayPlayer* peSayAvail);
    BOOL    isScoreBigClosed(eGiocataScoreState eS1, eGiocataScoreState eS2);
    void    actionWithoutQuestion();
    void    giocata_Go_Amonte(int iPlayerIx);
    BOOL    isGiocataAMonte();
    BOOL    get_LastPendScoreQuest(cPendQuestion& PendQues);
    void    removeObsoleteActions();

private:
    //! invido core engine
    cInvidoCore*        m_pInvidoCore;
    //! giocata object
    cGiocata*           m_pGiocata;
    //! mano status
    eManoStatus         m_eManoState;
    //! old mano status
    eManoStatus         m_eOldManoState;
    //! type of all players
    eTypeOfPLayer       m_eTypePlayer[MAX_NUM_PLAYER];
    //! Number of players that still have to play
    int                 m_iNumOfPlayers;
    //! next action queue 
    DEQ_ACTIONITEM      m_deqNextAction;
    //! match info score
    cMatchPoints*       m_pScore;
    //! pending question queue
    DEQ_PENDQUESTION    m_deqPendQuestion;
    //! map of action names
    MAP_ACTION_NAMES    m_MapActionNames;
    //! map say score, for conversion
    MAP_SAY_SCORE       m_MapSayScore;
    //! map "have to play" state
    MAP_PL_STATUS       m_MapManoStatePl;
    //! map "have to responce" state
    MAP_PL_STATUS       m_MapManoStateResp;
    //! map player index on status
    MAP_STATUS_PL       m_MapPlayerOnState;
    //! map action on state
    MAP_STATUS_ACTION   m_MapActionOnState;
    //! table queue mano state
    DEQ_TABLESTATE      m_deqTableState;
    //! table object
    cPlayersOnTable*    m_pTable;
    //! player index that change the score
    int                 m_iPlayerChangeScore;
    //! map the score with the closest next
    MAP_SCORE_SCORENEXT m_mapScoreScNext;
    //! map score with say
    MAP_SCORE_SAY       m_mapScoreSay;
    //! tracer service
    TraceService*       m_pTracer;
};

#endif