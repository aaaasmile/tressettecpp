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



// cPartita.h

#ifndef __CPARTITA_H__
#define __CPARTITA_H__

#include "CoreEnv.h"

class cCore;
class cGiocata;
class I_MatchScore;

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CPARTITA CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cPartita
/** class to manage a new partita
*/
class cPartita
{
//! enum action type
enum eFN_ACTION
{
    //! partita end
    ACT_PARTITA_END,
    //! no action
    NO_ACTION
};
public:
    cPartita();

public:
    void    SetCore(cCore* pVal){m_pCoreEngine = pVal;}
    void    SetGiocata(cGiocata* pVal){m_pGiocata = pVal;}
    void    NewPartita(long lPlayerIx);
    void    Update_Partita(I_MatchScore* pIScore);
    void    Reset();
    //! do the next action
    void    NextAction();

private:
    ePartitaStatus   m_PartitaState;
    cCore*           m_pCoreEngine;
    cGiocata*        m_pGiocata;
    long             m_lGiocStart;
    //! next action 
    eFN_ACTION         m_eNextAction;
};


#endif
