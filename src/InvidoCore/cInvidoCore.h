

// cInvidoCoreEngine.h

#ifndef _C_INVIDOCORE_H_
#define _C_INVIDOCORE_H_


#include "cInvidoCoreEnv.h"
#include "cProbality.h"
#include "cPartita.h"
#include "cMano.h"
#include "cGiocata.h"


#include "cPlayersOnTable.h"

#include "cMatchPoints.h"

class cMazzo;
class TraceService;

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CINVIDOCORE CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cInvidoCore
/** the core class for the invido. Hold all information about game in progress, level
cards and so on.
*/
class cInvidoCore : public I_CORE_Game
{
public:
    cInvidoCore();
    ~cInvidoCore();

    //!create the engine 
    void  Create(cPlayer* pHmiPlayer, int iNumPlayers);
    //! provides information about whon won the game
    BOOL  WhoWonsTheGame(cPlayer** ppPlayer);
    //! provides the index of the player that have to play
    BOOL  GetPlayerInPlaying(cPlayer** ppPlayer);
    //! set the game type
    void  SetGameType(eGameType eVal){m_eGameType = eVal;}
    //!provides a player 
    cPlayer*           GetPlayer(int iIndex){return m_PlayersOnTable.GetPlayerIndex(iIndex);}
    //! error message, somithing was wrong
    void               RaiseError( const std::string &errorMsg);
    //! provides the number of players
    int                GetNumOfPlayers(){return m_lNumPlayers;}
    //! provides match points object
    cMatchPoints*      GetMatchPointsObj(){return &m_MatchPoints;}
    //! provides the player table
    cPlayersOnTable*   GetTable(){return &m_PlayersOnTable;}

// functions related to the script engine
    //! notify event to the script engine
    void               NotifyScript(eScriptNotification eVal);
    //! script override deck
    void               Script_OverrideDeck(int iPlayer, int iC1, int iC2, int iC3);
    //! script say
    void               Script_Say(int iPlayer, eSayPlayer eSay);
    //! script play
    void               Script_Play(int iPlayer, CardSpec& CardPlayed);
    //! script notification algorithm
    void               NotifyScriptAlgorithm(int iPlayerIx, eScriptNotification eVal);
    //! script match end
    void               Script_MatchEnd();
    //! set the start player
    void               Script_SetStartPlayer(int iPlayer);
    //! script want to check an item
    int                Script_CheckResult(int iTypeOfItem, int iParam1, int iExpectedVal );
    
// functions called from cMano
    //! a Mano is terminated
    void      Mano_End();
    //! wait  player  have to play
    void      NtyWaitingPlayer_Toplay(int iPlayerIx);
    //! wait player responce 
    void      NtyWaitingPlayer_ToResp(int iPlayerIx);
    //! player say something not correct
    void      NtyPlayerSayBuiada(int iPlayerIx);
    //! giocata score is changed
    void      ChangeGiocataScore(eGiocataScoreState eNewScore);
    //! player abandon current giocata
    void      Player_VaVia(int iPlayerIx);
    //! giocata a monte
    void      Giocata_AMonte();
    

//functions called from cGiocata
    //! a giocata is ended
    void      Giocata_End();
    //! start a new giocata: shuffle and distribuite cards
    void      Giocata_Start(long lPlayerIx);

//function called from cPartita
    //! partita is terminated
    void      Partita_End();
    

// functions called from HMI
    //! start a new match
    void      NewMatch();
    //! next state
    void      NextAction();
    //! set Random seed
    void      SetRandomSeed(int iVal){m_pMyMazzo->SetRandomSeed(iVal);}
    
    
// I_CORE_Game: functions called from algorithm
    //! player say something
    BOOL      Player_saySomething(int iPlayerIx, eSayPlayer eSay );
    //! card is played from a player
    BOOL      Player_playCard(int iPlayerIx, const CARDINFO* pCardInfo);
    BOOL      Player_vaDentro(int iPlayerIx, const CARDINFO* pCardInfo);
    //! provides admitted commands
    void      GetAdmittedCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex);
    void      GetMoreCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex);
    //! player abandon the game
    void      AbandonGame(int iPlayerIx);

private:
    CardSpec*    isCardInPlayerHand(int iPlayerIx, const CARDINFO* pCardInfo);
    CardSpec*    checkValidCardPlayed(int iPlayerIx, const CARDINFO * pCardInfo);
    void         resetCardInfoPlayers();
    BOOL         resetCard(int iPlayerIx, CARDINFO* pCardInfo);
    int          getNewMatchFirstPlayer();
    
private:
    //! players on table
    cPlayersOnTable   m_PlayersOnTable;
    //! Game type
    eGameType         m_eGameType;
    //! number of players
    long          m_lNumPlayers;
    //! player index that must play now
    cPlayer*      m_pPlHaveToPlay;
    //! player index that has started the game
    cPlayer*      m_pStartPlayer;
    //! level of the game
    eGameLevel                m_eGameLevel;
    //! match statistic
    MATCH_STATISTIC           m_Match_Stat;
    //! deck
    cMazzo*                   m_pMyMazzo;
    //! partita
    cPartita                  m_Partita;
    //! giocata
    cGiocata                  m_Giocata;
    //! mano
    cMano                     m_Mano;
    //! players algorithm
    I_ALG_Player*             m_vctAlgPlayer[MAX_NUM_PLAYER];
    //! points handler in match
    cMatchPoints              m_MatchPoints;
    //! store cards of all players
    CardSpec                  m_aCardInfo[NUM_CARDS_HAND * MAX_NUM_PLAYER];
    //! tracer service
    TraceService*             m_pTracer;
};

#endif