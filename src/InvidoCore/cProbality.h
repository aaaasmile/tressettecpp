

//cProbality.h

#ifndef __CPROBABILITY_H____
#define __CPROBABILITY_H____

#include "cInvidoCoreEnv.h"

#include "cMazzo.h"
#include "CardSpec.h"

typedef std::vector<VCT_SINGLECARD>             MTX_HANDCOMBI;


/////////////////////////////////////////////////////////////////////////////////////
// *********************************     CPROBABILITY CLASS  ************************
/////////////////////////////////////////////////////////////////////////////////////


//! class cProbality
/**
// class used to calculate probability correlated to the game
*/
class cProbality
{
public:
    cProbality(){m_bIndexNotInit = true;m_iCardOnHand = 3;}

    //! develop all hand possibile hands with the cards on deck
    void SvilCombiHands(VCT_MAZZO &vct_Mazzo, MTX_HANDCOMBI &mtx_Result);
    //! coefficiente binomiale 
    double BinomialCoef(long lN, long lK);
    //! fattoriale
    double Fattorial(long lN);
   
    // operators
   friend std::ostream &operator << (std::ostream &stream, const MTX_HANDCOMBI &o);

private:
    //! status indici inizializzati
    bool            m_bIndexNotInit;
    //! indici di sviluppo sistema (da usare per sviluppare il sistema in tempi diversi)
    VCT_LONG        m_vctCounter;
    //! cards on hand
    int             m_iCardOnHand;
    

};


#endif