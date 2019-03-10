

// cGiocata.cpp
#include "StdAfx.h"
#include "cGiocata.h"
#include "cMano.h"
#include "cInvidoCore.h"
#include "cMatchPoints.h"

/////////////////////////////////////////////////////////////////////////////////////
//   *******************  CGIOCATA CLASS ***************************************
/////////////////////////////////////////////////////////////////////////////////////

//! constructor
cGiocata::cGiocata()
{
    m_pInvidoCore = NULL;
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
        m_pInvidoCore->RaiseError("Giocata state not right\n");
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
    m_deqNextAction.pop_front();

    switch(Action.m_eNextAction)
    {
        case GIOC_START:
            // gioca is started
            ASSERT(Action.m_vct_lArg.size() > 0);
            m_pInvidoCore->Giocata_Start(Action.m_vct_lArg[0]);
            // mano state
            m_pMano->NewMano(Action.m_vct_lArg[0]);
            
            break;

        case GIOC_END:
            // giocata is eneded
            m_pInvidoCore->Giocata_End();
            break;


        case GIOC_NO_ACTION:
            // nothing to do
            break;

        default:
            ASSERT(0);
            break;
    }
    

   
}


////////////////////////////////////////
//       Update_Giocata
/*! A Mano is terminated, update the giocata.
// \param long lPlayerIx: player that have start the trick
// \param I_MatchScore* pIScore : score informations
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
    m_deqNextAction.clear();
}


