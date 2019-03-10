

// cGiocata.h

#ifndef ___CGIOCATA____H
#define ___CGIOCATA____H

#include "cInvidoCoreEnv.h"
#include <deque>

class cInvidoCore;
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
    void    SetCore(cInvidoCore* pVal){m_pInvidoCore = pVal;}
    void    SetPartita(cPartita* pVal){m_pPartita = pVal;}
    void    SetMano(cMano* pVal){m_pMano = pVal;}
    //! start a new giocata
    void    NewGiocata(long lPlayerIx);
    void    Update_Giocata(long lPlayerIx, I_MatchScore* pIScore);
    void    Reset();
    //! do the next action
    void    NextAction();

private:
    cInvidoCore*     m_pInvidoCore;
    cPartita*        m_pPartita;
    eGiocataStatus   m_eGiocataStatus;
    cMano*           m_pMano;
    //! next action queue
    DEQ_ACTIT_GIO    m_deqNextAction;
};


#endif