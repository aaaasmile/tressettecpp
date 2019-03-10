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


// cGiocata.cpp
#include "StdAfx.h"
#include "cGiocata.h"
#include "cMano.h"
#include "cCoreEngine.h"
#include "cMatchPoints.h"

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CGIOCATA CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! constructor
cGiocata::cGiocata()
{
    m_pCoreEngine = NULL;
    m_pPartita = NULL;
    m_pMano = NULL;
    m_eGiocataStatus = WAIT_NEW_GIOCATA;
}


////////////////////////////////////////
//       NewGiocata
/*! Start a new giocata
*/
void  cGiocata::NewGiocata(long lPlayerIx)
{

    cActionItemGio Action;

    if ( m_eGiocataStatus ==  WAIT_NEW_GIOCATA)
    {
        m_eGiocataStatus = GIOCATA_ONGOING;
        // next action
        Action.m_vct_lArg.push_back(lPlayerIx);
        Action.m_eNextAction = GIOC_START;
        m_deqNextAction.push_back(Action);
    }
    else
    {
        m_pCoreEngine->RaiseError("Giocata state not right\n");
        ASSERT(0);
    }
}



////////////////////////////////////////
//       NextAction
/*! Take the next action
*/
void cGiocata::NextAction()
{
    size_t iNumAct = m_deqNextAction.size();
    if (iNumAct == 0)
    {
        // no action
        return ;
    }
    cActionItemGio Action = m_deqNextAction.front();

    switch(Action.m_eNextAction)
    {
        case GIOC_START:
            // gioca is started
            ASSERT(Action.m_vct_lArg.size() > 0);
            m_pCoreEngine->Giocata_Start(Action.m_vct_lArg[0]);
            // mano state
            m_pMano->NewMano(Action.m_vct_lArg[0]);
            
            break;

        case GIOC_END:
            // giocata is eneded
            m_pCoreEngine->Giocata_End();
            break;


        case GIOC_NO_ACTION:
            // nothing to do
            break;

        default:
            ASSERT(0);
            break;
    }
    m_deqNextAction.pop_front();
   
}


////////////////////////////////////////
//       Update_Giocata
/*! A Mano is terminated, update the giocata.
// \param long lPlayerIx : player that must play
*/
void  cGiocata::Update_Giocata(long lPlayerIx, I_MatchScore* pIScore)
{
    // check mano
    ASSERT(m_eGiocataStatus == GIOCATA_ONGOING);
    ASSERT(pIScore);
    cActionItemGio Action;

    if (pIScore->IsGiocatEnd() )
    {
        // giocata is terminated
        m_eGiocataStatus =  WAIT_NEW_GIOCATA;
        Action.m_eNextAction = GIOC_END;
        m_deqNextAction.push_back(Action);
    }
    else
    {
        m_pMano->NewMano(lPlayerIx);
        
    }

}


////////////////////////////////////////
//       Reset
/*! Reset giocata status
*/
void  cGiocata::Reset()
{
    m_eGiocataStatus = WAIT_NEW_GIOCATA;
}


