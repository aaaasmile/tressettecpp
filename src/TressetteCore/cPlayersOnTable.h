
//cPlayersOnTable.h

#ifndef __PLAYERSONTABLE_H
#define __PLAYERSONTABLE_H

#include "cPlayer.h"


//! class cPlayersOnTable
/* player on table ring
*/ 
class cPlayersOnTable
{
public:
    enum eSwitchPLayer
    {
        SWITCH_TO_NEXT,
        NO_SWITCH
    };
    cPlayersOnTable();

    void         SetFirst(long lIndex);
    cPlayer*     GetFirst(){return &m_vctPlayers[m_lPlayFirst];}
    //! create the player list
    void         Create(int iNumPlayers);
    //! provide the player in the list and update the iterator
    cPlayer*     GetPlayerToPlay(eSwitchPLayer eVal);
    //! get player from index
    cPlayer*     GetPlayerIndex(long lIndex);
    //! calculate the distance between 2 players
    int          CalcDistance(int iPlayerRef, int PlayerTmp);
    //! calculate circle index
    void         CalcCircleIndex(int* paPlayerDeck);
    //! calculate circle index with custom initial value
    void         CalcCircleIndex_Cust(int* paPlayerDeck, int iPlayerIni);
    //! check if some  players has a level python
    BOOL         IsLevelPython();
private:
    //! vector of players
    VCT_PLAYERS   m_vctPlayers;
    //! current player index
    long          m_lCurrent;
    //! number of players
    long          m_lNumPlayers;
    //! player index who play first in the next match
    long          m_lPlayFirst;
    
};


#endif
