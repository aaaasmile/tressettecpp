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


// cGiocata.h

#ifndef ___CGIOCATA____H
#define ___CGIOCATA____H

#include "CoreEnv.h"
#include <deque>

class cCore;
class cPartita;
class cMano;
class I_MatchScore;

//! enum action type
enum eFN_ACTION_GIO
{
    //! giocata start
    GIOC_START,
    //! giocata end
    GIOC_END,
    //! no action
    GIOC_NO_ACTION
};

//! class cActionItemGio
/** action item in the queue of giocata tasks
*/
class cActionItemGio
{
public:
    //! constructor
    cActionItemGio(){m_eNextAction = GIOC_NO_ACTION;}

    eFN_ACTION_GIO      m_eNextAction;
    //! argument list for action calls
    VCT_LONG            m_vct_lArg;
};

typedef std::deque< cActionItemGio > DEQ_ACTIT_GIO;


/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CGIOCATA CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! class cGiocata
/**
Manage a giocata on invido. There is 3 mano on one giocata.
*/
class cGiocata
{
public:
    cGiocata();
public:
    void    SetCore(cCore* pVal){m_pCoreEngine = pVal;}
    void    SetPartita(cPartita* pVal){m_pPartita = pVal;}
    void    SetMano(cMano* pVal){m_pMano = pVal;}
    //! start a new giocata
    void    NewGiocata(long lPlayerIx);
    void    Update_Giocata(long lPlayerIx, I_MatchScore* pIScore);
    void    Reset();
    //! do the next action
    void    NextAction();

private:
    cCore*     m_pCoreEngine;
    cPartita*        m_pPartita;
    eGiocataStatus   m_eGiocataStatus;
    cMano*           m_pMano;
    //! next action queue
    DEQ_ACTIT_GIO    m_deqNextAction;
};


#endif
