
//cDelayNextAction.h

#ifndef __CDELAY_NO_ACTION_H
#define __CDELAY_NO_ACTION_H




//! class cDelayNextAction 
// delay next action
class cDelayNextAction
{
public:
    enum eChangeble
    {
        NOCHANGE,
        CHANGE_AVAIL
    };
	cDelayNextAction();
	//! provides trigger to call next action
	BOOL  CanStart();
	//! reset
	void  Reset();
	//! start delay
	void  CheckPoint(Uint32 uiVal, eChangeble eVal);
    //! change the delay time only
    void  ChangeCurrDelay(Uint32 uiVal);

private:
	//! delay start time
	Uint32   m_uiStartDelTime;
	//! delay next action
	BOOL     m_bDelayNextAction;
	//! tick to delay
	Uint32   m_uiDelayTick;
    //! mutex access data
    SDL_mutex*        m_pMxAcc;
    //! chaange type of delay
    eChangeble  m_eChangeVal;
};





#endif