// AlgPlayerInterface.h


#ifndef ___ALGPLAYER_H_
#define ___ALGPLAYER_H_

#include "InvidoInfoComm.h"

//! class I_CORE_Game
/**Interface implemented by core game engine. This set of function are available
// to player algorithm to communicate with the core engine
*/
class I_CORE_Game
{
public:
    I_CORE_Game(){}
    //! player say something
    virtual BOOL Player_saySomething(int iPlayerIx, eSayPlayer eSay ) = 0;
    //! player play a card
    virtual BOOL Player_playCard(int iPlayerIx, const CARDINFO* pCardInfo) = 0;
    virtual BOOL Player_vaDentro(int iPlayerIx, const CARDINFO* pCardInfo) = 0;
    //! player abandon the game
    virtual void  AbandonGame(int iPlayerIx) = 0;
    //! provides admitted commands
    virtual void  GetAdmittedCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex) = 0;
    //! suplementary commands
    virtual void  GetMoreCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex) = 0;
};

//! class I_MatchScore
/** Interface to access information about the current match score.
*/
class I_MatchScore
{
public:
    I_MatchScore(){}
    virtual BOOL    IsGiocatEnd() = 0;
    virtual BOOL    IsGiocataMonte() = 0;
    virtual BOOL    IsManoPatada() = 0;
    virtual BOOL    IsGiocataPatada() = 0;
    virtual BOOL    IsMatchEnd() = 0;
    virtual int     GetManoWinner() = 0;
    virtual int     GetGiocataWinner() = 0;
    virtual int     GetMatchWinner() = 0;
    virtual eGiocataScoreState GetCurrScore() = 0;
    virtual int     GetPointsPlayer(int iPlayerIx) = 0;
    virtual int     GetManoNum() = 0;
    virtual BOOL    IsGameAbandoned() = 0;
    
};

//! class I_ALGPlayer
/** Inteface to be implemented from player algorithm. Functions are called by 
// core and implemented by player. The player table is composed like so:
-------
|1    2| 
|0    3|
|------|
The player becomes an index on the virtual game table.
*/
class I_ALG_Player
{
public:
    I_ALG_Player(){}
    //! set core interface
    virtual void ALG_SetCoreInterface(I_CORE_Game* pCore) = 0;
    //! set player index
    virtual void ALG_SetPlayerIndex(int iIndex) = 0;
    //! set opponent index. iIndex is opponent index on the table, 
    // iOpponentNr is the ordinal number of opponent
    virtual void ALG_SetOpponentIndex(int iIndex, int iOpponentNr) = 0;
    //! set associate index
    virtual void ALG_SetAssociateIndex(int iIndex) = 0;
    //! new match notification
    virtual void ALG_NewMatch(int iNumPlayer) = 0;
    //! new giocata notification
    virtual void ALG_NewGiocata(const CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) = 0;
    //! player has played a card
    virtual void ALG_PlayerHasPlayed(int iPlayerIx, const CARDINFO* pCard) = 0;
    virtual void ALG_PlayerHasVadoDentro(int iPlayerIx) = 0;
    //! player has said something
    virtual void ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay) = 0;
    //! player have to play notification
    virtual void ALG_Play() = 0;
    //! mano end notification. iPlayerIx is the player that have to play.
    virtual void ALG_ManoEnd(I_MatchScore* pScore) = 0;
    //! giocata end notification
    virtual void ALG_GiocataEnd(I_MatchScore* pScore) = 0;
    //! match end notification
    virtual void ALG_MatchEnd(I_MatchScore* pScore) = 0;
    //! player have to respond
    virtual void ALG_HaveToRespond() = 0;
    //! giocata score changed
    virtual void ALG_GicataScoreChange(eGiocataScoreState eNewScore) = 0;
    //! player has said something not correct
    virtual void ALG_PlayerSaidWrong(int iPlayerIx) = 0;
};

// Interface tracer
class I_GuiTracer
{
public:
    I_GuiTracer(){}
    virtual void    TraceData(const BYTE *pbyData, int nDataLen, char* pTextComment)=0;
    virtual void    Trace(const char* szFmt, ...)=0;
};

#endif



