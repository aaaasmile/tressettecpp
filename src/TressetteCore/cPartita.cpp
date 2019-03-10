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



// cPartita.cpp
#include "StdAfx.h"
#include "cPartita.h"
#include "cGiocata.h"
#include "cCoreEngine.h"
#include "CoreEnv.h"
#include "cMatchPoints.h"


/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CPARTITA CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! constructor
cPartita::cPartita()
{
    m_pGiocata = NULL;
    m_pCoreEngine = NULL;
    m_PartitaState = WAIT_NEW_PARTITA;
    m_lGiocStart = 0;
    m_eNextAction = NO_ACTION;
}


////////////////////////////////////////
//       NewPartita
/*! Start a new partita
*/
void    cPartita::NewPartita(long lPlayerIx)
{
    m_lGiocStart = lPlayerIx ;

    if (m_PartitaState != PARTITA_ONGOING )
    {
        m_PartitaState = PARTITA_ONGOING;

        m_pGiocata->NewGiocata(m_lGiocStart);
    }
    else
    {
        m_pCoreEngine->RaiseError("Partita state not right\n");
    }
}

////////////////////////////////////////
//       NextAction
/*! Take the next action
*/
void cPartita::NextAction()
{
    switch(m_eNextAction)
    {
 
        case ACT_PARTITA_END:
            // partita is eneded
            m_pCoreEngine->Partita_End();
            break;

        case NO_ACTION:
            // nothing to do
            break;

        default:
            ASSERT(0);
            break;
    }

    m_eNextAction = NO_ACTION;
}



////////////////////////////////////////
//       Update_Partita
/*! Giocata is terminated, update the partita
*/
void    cPartita::Update_Partita(I_MatchScore* pIScore)
{
    ASSERT(pIScore);
    ASSERT(m_PartitaState == PARTITA_ONGOING);

    if ( pIScore->IsMatchEnd() )
    {
        // match is ended
        m_eNextAction = ACT_PARTITA_END;
        m_PartitaState = PARTITA_END;
    }
    else
    {
        int iNumPlayers = m_pCoreEngine->GetNumOfPlayers(); 

        if (iNumPlayers == 2)
        {
            // start a new giocata
            switch (m_lGiocStart)
            {
            case 0:
                m_lGiocStart = 1;
                break;
            case 1:
                m_lGiocStart = 0;
                break;
            default:
                m_pCoreEngine->RaiseError("m_lGiocStart index not right\n");
                break;
            }
        }
        else if (iNumPlayers == 4)
        {
            switch (m_lGiocStart)
            {
            case 0:
                m_lGiocStart = 1;
                break;
            case 1:
                m_lGiocStart = 2;
                break;
            case 2:
                m_lGiocStart = 3;
                break;
            case 3:
                m_lGiocStart = 0;
                break;
            default:
                m_pCoreEngine->RaiseError("m_lGiocStart index not right\n");
                break;
            }
        }
        else
        {
            // not supported number of players
            ASSERT(0);
        }

        m_pGiocata->NewGiocata(m_lGiocStart);
    }
    
}


////////////////////////////////////////
//       Reset
/*! 
*/
void    cPartita::Reset()
{
    m_PartitaState = WAIT_NEW_PARTITA;
    m_lGiocStart = 0;
}
