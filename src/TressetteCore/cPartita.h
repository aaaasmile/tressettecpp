
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
