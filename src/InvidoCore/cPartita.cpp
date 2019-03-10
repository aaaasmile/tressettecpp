// cPartita.cpp

#include "StdAfx.h"
#include "cPartita.h"
#include "cGiocata.h"
#include "cInvidoCore.h"
#include "cInvidoCoreEnv.h"
#include "cMatchPoints.h"


/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CPARTITA CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! constructor
cPartita::cPartita()
{
    m_pGiocata = NULL;
    m_pInvidoCore = NULL;
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
        m_pInvidoCore->RaiseError("Partita state not right\n");
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
            m_pInvidoCore->Partita_End();
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
            m_pInvidoCore->RaiseError("m_lGiocStart index not right\n");
            break;
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
