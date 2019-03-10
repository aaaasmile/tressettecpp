/*
    Tressette
    Copyright (C) 2005  Igor Sarzi Sartori

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Igor Sarzi Sartori
    www.invido.it
    6colpiunbucosolo@gmx.net
*/

// cAlgDefault.h: interface for the cAlgDefault class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cAlgDefault_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
#define AFX_cAlgDefault_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlgPlayerInterface.h"
#include "CoreEnv.h"
#include "CardSpec.h"
#include "AlgCompareFunct.h"
#include <map>
#include "AlgSupport.h"

class cAlgABSolver;

//! class cAlgDefault  
/** class that implement a dummy player
*/
class cAlgDefault  : public I_ALG_Player
{    
    friend class cAlgDefaultTest;
    
    typedef std::vector<VCT_INT>             MTX_HANDCOMBI;
    typedef std::vector<VCT_INT*>            MTX_PINDEX;
    typedef AlgSupport::HandInfo*            PHANDINFO;
    typedef std::map<STRING, PHANDINFO>      MAP_PHANDINFO;
public:
	cAlgDefault();
	virtual ~cAlgDefault();

    //! get hand info
    AlgSupport::HandInfo GetCurrenHandInfo(){return m_currHandInfo;}
   
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
    virtual void ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) ;
    //! player has played a card
    virtual void ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard) ;
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
    //! player said somithing false
    virtual void ALG_PLayerSaidFalse(int iPlayerIx);
    //! player has declared a good game
    virtual void ALG_PLayerDeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSUIT eValsuit);


private:
    void    lookforDeclGoodGames();
    void    traceAllCardInHand(LPCSTR strComment);
    void    traceListInhand(VCT_INT& vctListIndexes);
    void    removeListIndex(VCT_INT&  vctInHand, int iIndex);
    void    signalSomething(CARDINFO& cardPlayed, BOOL bViaDalGioco, BOOL bBusso);
    VCT_INT* getListOnSuite(eSUIT eSuit);
    void    checkListBigCards(VCT_INT* pListIndexCard, BOOL& bTre, BOOL& bDue, BOOL& bAsso);
    void    playRandom(CARDINFO& cardToPlay);
    void    playAsFirst(CARDINFO& cardToPlay);
    void    playAsNotFirst(CARDINFO& cardToPlay);
    void    developFirstHandTypes();
    void    orderSuitListOnFreq(MTX_PINDEX& mtxPIndex);
    BOOL    isTre(CARDINFO& cardPlayed);
    BOOL    isDue(CARDINFO& cardPlayed);
    BOOL    isAsso(CARDINFO& cardPlayed);
    void    otherPlayersCardRandom();
    void    calculatePizzOnHand();
    BOOL    isNapula();
    void    calculateSuiteIndexes();
    void    useAlphaBeta(CARDINFO& cardToPlay);
    AlgSupport::ePizzicoInSuit pizzicoOnBiggerSeed( eSUIT& eSuitStark , VCT_SUITE* pVct = NULL);
    int     indexOfTheBiggerScartino( eSUIT eSuitStark );
    void    copyCardsBeginTrick();
    void    traceAllTrickInit();
    void    traceArrOfCardInfo(CARDINFO* arrTrickHist, int iNumEle);
    void    swapCardOnInitTrick(int iPlayerIx, CARDINFO* pCard);
    void    newAlgSolver();

private:
    //! hands of all players
    CARDINFO             m_arrCardAllPlayers[MAX_NUM_PLAYER][NUM_CARDS_HAND];
    //! hands of all players at the begin of the trick
    CARDINFO             m_arrCardAllTrickInit[MAX_NUM_PLAYER][NUM_CARDS_HAND];
    //! core invido pointer
    I_CORE_Game*               m_pCoreGame;
    //! algorithm player index 
    int                        m_iMyIndex;
    //! mano count
    int                        m_iTrickRound;
    //! indexes of suit bastoni yet in hand
    VCT_INT                    m_vctInHand_Bastoni;
    //! indexes of suit bastoni yet in hand
    VCT_INT                    m_vctInHand_Denari;
    //! indexes of suit bastoni yet in hand
    VCT_INT                    m_vctInHand_Coppe;
    //! indexes of suit bastoni yet in hand
    VCT_INT                    m_vctInHand_Spade;
    //! cards played on tricks
    VCT_CARDINFO               m_vctCardsPlayedTricks;  
    //! map to find hand information
    MAP_PHANDINFO              m_mapHandInfo;
    //! current hand info
    AlgSupport::HandInfo       m_currHandInfo;
    //! first hand info
    AlgSupport::HandInfo       m_firstHandInfo;
    //! trick information
    AlgSupport::TrickInfo      m_currTrickInfo;            
    //! algorithm solver
    cAlgABSolver*              m_pABSolver;
    //! localization of the game
    eTypeLocal                 m_eLocal;
};

#endif // !defined(AFX_cAlgDefault_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
