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
