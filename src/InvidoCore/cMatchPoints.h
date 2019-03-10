

// cMatchPoints.h: interface for the cMatchPoints class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMATCHPOINTS_H__A8E0031A_CF94_4322_9E51_9C761FDDDC7C__INCLUDED_)
#define AFX_CMATCHPOINTS_H__A8E0031A_CF94_4322_9E51_9C761FDDDC7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <deque>
#include "InvidoInfoComm.h"
#include "cInvidoCoreEnv.h"
#include "CardSpec.h"

class cMano;


//! class cManoInfo
class cManoInfo
{
public:
    cManoInfo(){}
    //! reset info
    void  Reset(){bIsPlayed = FALSE;bIsPata = FALSE; iPlayerIndex = NOT_VALID_INDEX;}

    //! player index who wons the mano
    int   iPlayerIndex;
    //! true if mano was played
    BOOL  bIsPlayed;
    //! true if mano was patada
    BOOL  bIsPata;
};

//! class cGiocataInfo
class cGiocataInfo
{
public:
    cGiocataInfo(){eScore = SC_AMONTE; iPlayerIndex = NOT_VALID_INDEX;}
    cGiocataInfo(int iVal, eGiocataScoreState eVal){eScore = eVal; iPlayerIndex = iVal;}

    //! int player win (invalid index if it was "pata" or "monte")
    int                iPlayerIndex;
    //! player score
    eGiocataScoreState eScore;
};

typedef std::vector<cGiocataInfo> VCT_GIOCATAINFO;

//! class cCardPlayed
// information about played card
class cCardPlayed
{
public:
    cCardPlayed(){}

    //! information about card played
    CardSpec cardSpec;
    //! player index
    int iPlayerIx;
};

//!class cMatchPoints  
/** class that provides match points informations. All informations are about the current match
*/ 
class cMatchPoints  : public I_MatchScore
{
    //! enum eGiocataEndState
    enum eGiocataEndState
    {
        //! giocata is ongoing
        GES_ON_GOING,
        //! giocata terminated with a winner
        GES_HAVE_WINNER,
        //! giocata terminated with a draw
        GES_PATADA,
        //! giocata a monte
        GES_AMONTE
    };
public:
	cMatchPoints();
	virtual ~cMatchPoints();

    //! start a new match
    void    MatchStart(int iNumPlayer);
    //! start a giocata
    void    GiocataStart();
    //! giocata end
    void    GiocataEnd();
    //! player play
    void    PlayerPlay(int iPlayerIx, CARDINFO* pCard);
    //! mano end
    void    ManoEnd();
    //! change current score 
    void    ChangeCurrentScore(eGiocataScoreState eVal, int iPlayer);
    //! mano informations
    void    GetManoInfo(int iManoNum, int* piPlayerIx, BOOL* pbIsPlayed, BOOL* pbIsPata);
    //! giocata informations
    void    GetGiocataInfo(int iNumGiocata, cGiocataInfo* pGiocInfo);
    //! provides number of giocate
    int     GetNumGiocateInCurrMatch(){return (int)m_vctGiocataInfo.size();}
    //! player abandon giocata
    void    PlayerVaVia(int iPlayerIx);
    //! set mano object
    void    SetManoObj(cMano* pVal){m_pMano = pVal;} 
    //! giocata  a monte
    void    AMonte();
    //! set the winner (if a game was interrupted)
    void    SetTheWinner(int iPlayerIx);
    //! provides the number of cards played in the current mano
    int     GetCurrNumCardPlayed(){return m_iNumCardsPlayed;}

//interface I_MatchScore
    //! provides the winner of the hand. In case of remis return the initial player
    virtual int     GetManoWinner(){return m_iPlayerWonsHand;}
    //! provides the winner of the giocata. In case of remis return the initial player
    virtual int     GetGiocataWinner(){return m_iPlayerGiocataWin;}
    //! provides the winner of the match
    virtual int     GetMatchWinner(){return m_iPlayerMatchWin;}
    //! true if the giocata is ended
    virtual BOOL    IsGiocatEnd();
    //! provides the current score
    virtual eGiocataScoreState GetCurrScore(){return m_eCurrentScore;}
    //! true if the mano was patada
    virtual BOOL    IsManoPatada() {return m_bIsManoPatatda;}
    //! true if the giocata was patada
    virtual BOOL    IsGiocataPatada(){if(m_eIsGiocataEnd == GES_PATADA)return TRUE;else return FALSE;}
    //! true if giocata was a monte
    virtual BOOL    IsGiocataMonte(){if(m_eIsGiocataEnd == GES_AMONTE)return TRUE;else return FALSE;}
    //! true if the match is ended
    virtual BOOL    IsMatchEnd(){if(m_iPlayerMatchWin != NOT_VALID_INDEX)return TRUE;else return FALSE;}
    //! provides points of one player
    virtual int     GetPointsPlayer(int iPlayerIx){ASSERT(iPlayerIx >= 0 && iPlayerIx < MAX_NUM_PLAYER);return m_vctPlayerPoints[iPlayerIx];}
    //! provides the mano index
    virtual int     GetManoNum(){return m_iManoRound;}
    //! true if the game was abandoned
    virtual BOOL    IsGameAbandoned(){return m_bGameAbandoned;}

private:
    void    beginSpecialTurn();

private:
    //! points players
    int           m_vctPlayerPoints[MAX_NUM_PLAYER];
    //! mano wons player
    int           m_vctHandWons[MAX_NUM_PLAYER];
    //! current score
    eGiocataScoreState  m_eCurrentScore;
    //! current score changer
    int                 m_iPlayerChangeScore;
    //! cards played
    cCardPlayed   m_vctCardPlayed[MAX_NUM_PLAYER];
    //! number of cards played
    int           m_iNumCardsPlayed;
    //! player who wons the mano
    int           m_iPlayerWonsHand;
    //! number of players
    int           m_iNumPlayers;
    //! flag to mark if a mano was patada
    BOOL          m_bIsManoPatatda;
    //! flag to mark if a giocata was patada
    eGiocataEndState   m_eIsGiocataEnd;
    //! player who catch the first hand
    int           m_iPlayerFirstHand;
    //! mano round
    int           m_iManoRound;
    //! giocata winner
    int           m_iPlayerGiocataWin;
    //! match winner
    int           m_iPlayerMatchWin;
    //! points to win the match
    int           m_iScoreGoal;
    //! match in special score round
    BOOL          m_bMatchInSpecialScore;
    //! mano inner giocata was patada
    BOOL          m_bOldManoPatada;
    //! mano detailed information
    cManoInfo     m_ManoDetailInfo[NUM_CARDS_HAND];
    //! giocate info details
    VCT_GIOCATAINFO     m_vctGiocataInfo;
    //! mano state object
    cMano*              m_pMano;
    //! game abandoned flag
    BOOL           m_bGameAbandoned;
};

#endif // !defined(AFX_CMATCHPOINTS_H__A8E0031A_CF94_4322_9E51_9C761FDDDC7C__INCLUDED_)
