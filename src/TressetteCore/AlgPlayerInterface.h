// AlgPlayerInterface.h


// Version 0.1

#ifndef ___ALGPLAYER_H_
#define ___ALGPLAYER_H_

#include "InfoComm.h"


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
    virtual void ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) = 0;
    //! player has played a card
    virtual void ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard) = 0;
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
    //! player have to say
    virtual void ALG_Say() = 0;
    //! giocata score changed
    virtual void ALG_GicataScoreChange(eGiocataScoreState eNewScore) = 0;
    //! player has said something not correct
    virtual void ALG_PLayerSaidFalse(int iPlayerIx) = 0;
    //! player has declared a good game
    virtual void ALG_PLayerDeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSEED eValsuit) = 0;
};



#endif



