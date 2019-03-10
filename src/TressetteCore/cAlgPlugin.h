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


// cAlgPlugin.h: interface for the cAlgPlugin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cAlgPlugin_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_)
#define AFX_cAlgPlugin_H__C00C987D_219F_4552_893D_1A67CCACCC8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlgPlayerInterface.h"
#include "CoreEnv.h"
#include "CardSpec.h"

#ifndef WIN32
	#define HMODULE int
	#define __stdcall
#endif

//! class cAlgPlugin  
/** class that implement a wrapper on the plugin algorithm
*/
class cAlgPlugin  : public I_ALG_Player
{
    typedef void (__stdcall *tFN_SetCore)(I_CORE_Game* pCore);
    typedef void (__stdcall *tFN_SetPlayerIndex)(int iPlayerIndex);
    typedef void (__stdcall *tFN_NewGiocata )(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx);
    typedef void (__stdcall *tFN_PlayerHasPlayed )(int iPlayerIx, CARDINFO* pCard);
    typedef void (__stdcall *tFN_PlayerHasSaid )(int iPlayerIx, eSayPlayer eSay);
    typedef void (__stdcall *tFN_Play )();
    typedef void (__stdcall *tFN_ManoEnd )(I_MatchScore* pScore);
    typedef void (__stdcall *tFN_GiocataEnd )(I_MatchScore* pScore);
    typedef void (__stdcall *tFN_MatchEnd )(I_MatchScore* pScore);
    typedef void (__stdcall *tFN_GetName )(char* pOutName);
    typedef void (__stdcall *tFN_NewMatch )(int iNumPlayer);

public:
	cAlgPlugin();
	virtual ~cAlgPlugin();

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


// other methods
    void  Init(LPCSTR lpsModuleName);

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
    //! cards played on tricks
    VCT_CARDSPEC         m_vctCardsPlayedTricks;   
    //! dll handler
    HMODULE              m_hDll;
// exported functions of the dll
    tFN_SetCore          m_fnSetCore;
    tFN_SetPlayerIndex   m_fnSetPlayerIndex;
    tFN_NewGiocata       m_fnNewGiocata;
    tFN_PlayerHasPlayed  m_fnPlayerHasPlayed;
    tFN_PlayerHasSaid    m_fnPlayerHasSaid;
    tFN_Play             m_fnPlay;
    tFN_ManoEnd          m_fnManoEnd;
    tFN_GiocataEnd       m_fnGiocataEnd;
    tFN_NewMatch         m_fnNewMatch;
    tFN_MatchEnd         m_fnMatchEnd;
    tFN_GetName          m_fnGetName;
    //! error message buffer
    char                 m_aErrBuff[512];
};

#endif 
