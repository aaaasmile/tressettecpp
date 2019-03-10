// cAlgDummyPlayer.h: interface for the cAlgDummyPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALGDUMMYPLAYER_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
#define AFX_CALGDUMMYPLAYER_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlgPlayerInterface.h"
#include "cInvidoCoreEnv.h"
#include "CardSpec.h"

class TraceService;

//! class cAlgDummyPlayer  
/** class that implement a dummy player
*/
class cAlgDummyPlayer  : public I_ALG_Player
{
public:
	cAlgDummyPlayer();
	virtual ~cAlgDummyPlayer();

// interface I_ALG_Player
    virtual void ALG_SetCoreInterface(I_CORE_Game* pCore);
    //! set player index
    virtual void ALG_SetPlayerIndex(int iIndex) ;
    //! set opponent index
    virtual void ALG_SetOpponentIndex(int iIndex, int iOpponentNr) ;
    //! set associate index
    virtual void ALG_SetAssociateIndex(int iIndex) ;
    //! new match notification
    virtual void ALG_NewMatch(int iNumPlayer) ;
    //! new giocata notification
    virtual void ALG_NewGiocata(const CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) ;
    //! player has played a card
    virtual void ALG_PlayerHasPlayed(int iPlayerIx, const CARDINFO* pCard) ;
    virtual void ALG_PlayerHasVadoDentro(int iPlayerIx);
    //! player has said something
    virtual void ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay) ;
    //! player have to play notification
    virtual void ALG_Play() ;
    //! mano end notification
    virtual void ALG_ManoEnd(I_MatchScore* pScore) ;
    //! giocata end notification
    virtual void ALG_GiocataEnd(I_MatchScore* pScore) ;
    //! match end notification
    virtual void ALG_MatchEnd(I_MatchScore* pScore) ;
    //! player say
    virtual void ALG_Say();
    //! giocata score changed
    virtual void ALG_GicataScoreChange(eGiocataScoreState eNewScore);
    virtual void ALG_PlayerSaidWrong(int iPlayerIx);

private:
    //! cards hold on cpu
    CardSpec             m_vct_Cards_CPU[NUM_CARDS_HAND];
    //! card played from opponent
    CardSpec             m_CardPlayed;
    //! current giocata score
    eGiocataScoreState   m_eScoreCurrent;
    //! core invido pointer
    I_CORE_Game*         m_pCoreGame;
    //! algorithm player index 
    int                  m_iMyIndex;
    //! opponent index
    int                  m_iOppIndex;
    //! opponent said
    eSayPlayer           m_OpponentSay;
    //! player algorith said
    eSayPlayer           m_MyLastSay;
    //! tracer
    TraceService*        m_pTracer;
};

#endif // !defined(AFX_CALGDUMMYPLAYER_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
