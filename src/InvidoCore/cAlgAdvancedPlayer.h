// cAlgAdvancedPlayer.h: interface for the cAlgAdvancedPlayer class.
#if !defined(AFX_cAlgAdvancedPlayer_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
#define AFX_cAlgAdvancedPlayer_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlgPlayerInterface.h"
#include "cInvidoCoreEnv.h"
#include "CardSpec.h"
#include <functional>

class TraceService;

//! predicate to sort an hand based on his value
class cmpHandValue : public std::unary_function<cmpHandValue, bool>
{
private:
    int m_lValRef;

public:
    // constructor
    explicit cmpHandValue(){}
    //operator ()
    bool operator ()(const VCT_SINGLECARD &o1, const VCT_SINGLECARD &o2)
    {      
        int iPoints2 = 0;
        int iPoints1 = 0;
        size_t iNumCards = o1.size();
        if (iPoints1 >= iPoints2)
        {
            // no swap
            return false;
        }
        else
        {
            // swap
            return true;
        }
    }
};

//! class cAlgAdvancedPlayer  
/** class that implement a dummy player
*/
class cAlgAdvancedPlayer  : public I_ALG_Player
{
public:
	cAlgAdvancedPlayer();
	virtual ~cAlgAdvancedPlayer();

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
    //! player respond
    virtual void ALG_HaveToRespond();
    //! giocata score changed
    virtual void ALG_GicataScoreChange(eGiocataScoreState eNewScore);
    //! player said something wrong
    virtual void ALG_PlayerSaidWrong(int iPlayerIx);

private:
	void      PlayAsFirst();
	void      PlayAsSecond();
	BOOL      IsPlayerFirst();
	int	      NumMano();
    BOOL      Cagna(int  lastNumChiamate);
    BOOL      ChiamaDiPiu(int  lastNumChiamate);
    BOOL      ChiamaAMonte(int  lastNumChiamate);
    void      Chiama(eSayPlayer eSay, int lastChiamataNum);
    void      GiocaACaso();
    void      doVadoDentro(int cardPos);
    void      handleSayAmonte(int curr_mano, int pointsFirstCard, int lastNumChiamate, int maxpoints, int sum_points);
    void      handleSayPopints(int curr_mano, int pointsFirstCard, int lastNumChiamate, int maxpoints, int sum_points);

private:
    //! cards hold on cpu
    CardSpec               m_vct_Cards_CPU[NUM_CARDS_HAND];
	//! cards played in this giocata
	std::vector<CardSpec>  m_vct_Cards_played[NUM_HANDS];
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
    eSayPlayer           m_sayOppRisp;
    //! player algorith said
    eSayPlayer           m_MyLastSay;
    eSayPlayer           m_sayMyRisp;
    //! tracer
    TraceService*        m_pTracer;
    int                  m_arrIxPlayerWonHand[NUM_CARDS_HAND];
    BOOL                 m_bLastManoPatada;
    int                  m_iNumChiamateMonte;
    int                  m_iNumManiWon;
    int                  m_iPlayerOnTurn;
    int                  m_iNumChiamateInGiocata;
    int                  m_itrChan;
    BOOL                 m_bIamCalledPoints;
    int                  m_iCPUCardDentroPos;
    bool                 m_opponetIsVadoDentro;
    bool                 m_WonFirstHand;
    int                  m_ixCurrMano;
};

#endif // !defined(AFX_cAlgAdvancedPlayer_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
