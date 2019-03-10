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



// cCoreEngine.h

#ifndef _C_INVIDOCORE_H_
#define _C_INVIDOCORE_H_


#include "CoreEnv.h"
#include "cProbality.h"
#include "cPartita.h"
#include "cMano.h"
#include "cGiocata.h"


#include "cPlayersOnTable.h"

#include "cMatchPoints.h"

class cMazzo;
class TraceService;

typedef std::map<eSayPlayer, STRING> MAP_SAY;

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  cCore CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cCore
/** the core class for the invido. Hold all information about game in progress, level
cards and so on.
*/
class cCore : public I_CORE_Game
{
public:
    cCore();
    ~cCore();

    //!create the engine 
    void  Create( int iNumPlayers);
    //! provides information about whon won the game
    BOOL  WhoWonsTheGame(cPlayer** ppPlayer);
    //! provides the index of the player that have to play
    BOOL  GetPlayerInPlaying(cPlayer** ppPlayer);
    //! set the game type
    void  SetGameType(eGameType eVal){m_eGameType = eVal;}
    //! provides the player that start the game
    cPlayer*           GetStartPlayer(){return m_PlayersOnTable.GetFirst();}
    //!provides a player 
    cPlayer*           GetPlayer(int iIndex){return m_PlayersOnTable.GetPlayerIndex(iIndex);}
    //! error message, somithing was wrong
    void               RaiseError( const std::string &errorMsg); 
    //! provides the number of players
    int                GetNumOfPlayers(){return m_lNumPlayers;}
    //! provides match points object
    cMatchPoints*      GetMatchPointsObj(){return &m_MatchPoints;}
    //! notify event to the script engine
    void               NotifyScript(eScriptNotification eVal);
    //! provides the player table
    cPlayersOnTable*   GetTable(){return &m_PlayersOnTable;}
    //! set wich type of localized game is played
    void               SetLocalType(eTypeLocal eLocal);
    //! get current local type
    eTypeLocal         GetLocalType(){return m_eLocalType;}
    //! Provides the text of the call
    STRING             GetComandString(eSayPlayer eSay);
    //! set if good game call are enabled
    void               SetGoodGameCallEnabled(BOOL bVal){m_bGooGameAreEnabled = bVal;}
    //! the match init without a script
    void               NoInitScript();
     //! provides admitted commands
    void               GetAdmittedSignals(CardSpec&   cardClicked, VCT_SIGNALS& vct_Signals, int iPlayerIndex);

// script functions
    //! script override deck
    void               Script_OverrideDeck(int iPlayer, int vctCardPlayer[]);
    //! script say
    void               Script_Say(int iPlayer, eSayPlayer eSay);
    //! script play
    void               Script_Play(int iPlayer, CardSpec& CardPlayed);
    //! script check deck
    void               Script_CheckDeck();
    //! script set the start player
    void               Script_SetStartPlayer(int iPlayer);

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
    void      SetRandomSeed(int iVal);
    
    
// I_CORE_Game: functions called from algorithm
    //! player say something
    BOOL      Player_saySomething(int iPlayerIx, eSayPlayer eSay );
    //! card is played from a player
    BOOL      Player_playCard(int iPlayerIx, CARDINFO* pCardInfo);
    //! player abandon the game
    void      AbandonGame(int iPlayerIx);
    //! declare good game
    BOOL      DeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSUIT eValsuit);

private:
    BOOL    isCardInPlayerHand(int iPlayerIx, CARDINFO* pCardInfo);
    void    resetCardInfoPlayers();
    BOOL    resetCard(int iPlayerIx, CARDINFO* pCardInfo);
    BOOL    isDeclarationInPlayerHand(int iPlayerIx, eDeclGoodGame eValgg,  eSUIT eValsuit);
    void    checkForBussoVoloLiscieBasse(BOOL& bBusso, BOOL& bVolo, BOOL& bLiscio, int iPlayerIndex, CardSpec&   cardClicked);
    BOOL    checkForStriscioNeHoTante(int iPlayerIndex, CardSpec&   cardClicked);

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
    //! algorith players
    I_ALG_Player*             m_vctAlgPlayer[MAX_NUM_PLAYER];
    //! points handler in match
    cMatchPoints              m_MatchPoints;
    //! store cards of all players
    CardSpec                  m_aCardInfo[NUM_CARDS_HAND * MAX_NUM_PLAYER];
    //! local type 
    eTypeLocal                m_eLocalType;
    //! defaults signals  available
    VCT_SIGNALS               m_vctSignAvail;
    //! flag to shuffle the deck (used only with script)
    BOOL                      m_bSuspendShuffle;
    //! good game enable flag
    BOOL                      m_bGooGameAreEnabled;
    //! first player index set from script
    int                       m_iFirstPlayerPython;
    //! tracer
    TraceService*             m_pTracer;
    //! map names of player calls for feedback
    MAP_SAY                   m_Map_fb_Say;
};

#endif
