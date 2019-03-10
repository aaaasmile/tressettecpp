
//cDelayNextAction.cpp

#include "StdAfx.h"
#include "win_type_global.h"
#include "SDL.h"
#include "cDelayNextAction.h"

////////////////////// cDelayNextAction 

cDelayNextAction::cDelayNextAction()
{
    m_eChangeVal = CHANGE_AVAIL;
}

////////////////////////////////////////
//       CanStart
/*! Provides TRUE if not delay is ongoing, FALSE if delay is active
*/
BOOL cDelayNextAction::CanStart()
{

	BOOL bRet = FALSE;
	if (!m_bDelayNextAction)
	{
		// no delay request
		return TRUE;
	}

	Uint32 uiNowTime = SDL_GetTicks();
	if (uiNowTime - m_uiStartDelTime > m_uiDelayTick)
	{
		bRet = TRUE;
		m_bDelayNextAction = FALSE;
	}

	return bRet;
}


////////////////////////////////////////
//       Reset
/*! Reset the delay action ( disable delay)
*/
void cDelayNextAction::Reset()
{
    TRACE ("Reset Check point called\n");

	m_uiStartDelTime = 0;
	m_bDelayNextAction = FALSE;
	m_uiDelayTick = 0;
    m_eChangeVal = CHANGE_AVAIL;
}


////////////////////////////////////////
//       ChangeCurrDelay
/*! Chenge the value of the current delay
// \param Uint32 uiVal : new value
*/
void cDelayNextAction::ChangeCurrDelay(Uint32 uiVal)
{
    if (m_eChangeVal == CHANGE_AVAIL)
    {
        TRACE ("Change current delay\n");
        m_uiDelayTick = uiVal;
    }
}

////////////////////////////////////////
//       CheckPoint
/*! Set a checkpoint to delay an action. The action should be enable after a acknowledge 
// with the function call CanStart()
// \param Uint32 uiVal : 
// \param eChangeble eVal:  if no changeble, change the curret delay as noeffect
*/
void cDelayNextAction::CheckPoint(Uint32 uiVal, eChangeble eVal)
{
    TRACE ("Check point called\n");

	m_uiStartDelTime = SDL_GetTicks();
	m_bDelayNextAction = TRUE;
	m_uiDelayTick = uiVal;
    m_eChangeVal = eVal;

}
