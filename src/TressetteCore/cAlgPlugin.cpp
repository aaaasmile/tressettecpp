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


// cAlgPlugin.cpp: implementation of the cAlgPlugin class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "cAlgPlugin.h"
#include "ErrorMsg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////






////////////////////////////////////////
//       cAlgPlugin
/*! Constructor
*/
cAlgPlugin::cAlgPlugin()
{
    m_pCoreGame = 0;
    m_iOppIndex = NOT_VALID_INDEX;
    m_hDll = 0;
    m_fnSetCore = 0;
    m_fnSetPlayerIndex  = 0;
    m_fnNewGiocata      = 0;
    m_fnPlayerHasPlayed = 0;
    m_fnPlayerHasSaid   = 0;
    m_fnPlay            = 0;
    m_fnManoEnd         = 0;
    m_fnGiocataEnd      = 0;
    m_fnMatchEnd        = 0;
    m_fnGetName         = 0;
    m_fnNewMatch        = 0;

}


////////////////////////////////////////
//       ~cAlgPlugin
/*! Destructor
*/
cAlgPlugin::~cAlgPlugin()
{

}


////////////////////////////////////////
//       Init
/*! Init the plugin
// \param LPCSTR lpsModuleName : plugin name 
*/
void  cAlgPlugin::Init(LPCSTR lpsModuleName)
{
#ifdef WIN32
    m_hDll = LoadLibrary(lpsModuleName); 

    m_fnSetCore         = (tFN_SetCore)GetProcAddress(m_hDll, "SetCoreInterface" );
    m_fnSetPlayerIndex  = (tFN_SetPlayerIndex)GetProcAddress(m_hDll, "SetPlayerIndex" );
    m_fnNewGiocata      = (tFN_NewGiocata)GetProcAddress(m_hDll, "NewGiocata" );
    m_fnPlayerHasPlayed = (tFN_PlayerHasPlayed)GetProcAddress(m_hDll, "PlayerHasPlayed" );
    m_fnPlayerHasSaid   = (tFN_PlayerHasSaid)GetProcAddress(m_hDll, "PlayerHasSaid" );
    m_fnPlay            = (tFN_Play)GetProcAddress(m_hDll, "Play" );
    m_fnManoEnd         = (tFN_ManoEnd)GetProcAddress(m_hDll, "ManoEnd" );
    m_fnGiocataEnd      = (tFN_GiocataEnd)GetProcAddress(m_hDll, "GiocataEnd" );
    m_fnMatchEnd        = (tFN_MatchEnd)GetProcAddress(m_hDll, "MatchEnd" );
    m_fnGetName         = (tFN_GetName)GetProcAddress(m_hDll, "GetName" );
    m_fnNewMatch        = (tFN_NewMatch)GetProcAddress(m_hDll, "NewMatch" );
#endif    
    if (m_hDll == 0)
    {
        sprintf(m_aErrBuff, "%s not found.", lpsModuleName);
        throw Error::Generic(m_aErrBuff);
    }
    else if (m_fnSetCore == 0 ||
        m_fnSetPlayerIndex == 0 ||
        m_fnNewGiocata == 0 ||
        m_fnPlayerHasPlayed == 0 ||
        m_fnPlayerHasSaid == 0 ||
        m_fnPlay == 0 ||
        m_fnManoEnd == 0 ||
        m_fnGiocataEnd == 0 ||
        m_fnMatchEnd == 0 ||
        m_fnGetName == 0 ||
        m_fnNewMatch == 0
        )
    {
        sprintf(m_aErrBuff, "Algorithm dll %s is not OK, functions are missed or the dll is build incorrectly ", lpsModuleName);
        throw Error::Generic(m_aErrBuff);
    }
    
    
    
}

////////////////////////////////////////
//       ALG_SetCoreInterface
/*! 
// \param I_CORE_Game* pCore : 
*/
void cAlgPlugin::ALG_SetCoreInterface(I_CORE_Game* pCore)
{
    if (m_fnSetCore)
    {
        m_fnSetCore(pCore);
    }
    else
    {
        sprintf(m_aErrBuff, "Function SetCore not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
}


////////////////////////////////////////
//       ALG_SetPlayerIndex
/*! set player index
// \param int iIndex : 
*/
void cAlgPlugin::ALG_SetPlayerIndex(int iIndex) 
{
    if (m_fnSetPlayerIndex)
    {
        m_fnSetPlayerIndex(iIndex);
    }
    else
    {
        sprintf(m_aErrBuff, "Function SetPlayerIndex not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
}


////////////////////////////////////////
//       ALG_SetOpponentIndex
/*! set opponent index
// \param int iIndex : 
// \param int iOpponentNr : 
*/
void cAlgPlugin::ALG_SetOpponentIndex(int iIndex, int iOpponentNr) 
{
    // not used
}


////////////////////////////////////////
//       ALG_SetAssociateIndex
/*! Set associate index (the algorithm player index) to recognize notifications of a player.
// \param int iIndex : new index of the algorithm
*/
void cAlgPlugin::ALG_SetAssociateIndex(int iIndex) 
{
    // not used
}


////////////////////////////////////////
//       ALG_NewMatch
/*! new match notification
// \param int iNumPlayer : 
*/
void cAlgPlugin::ALG_NewMatch(int iNumPlayer) 
{
    if (m_fnNewMatch)
    {
        m_fnNewMatch(iNumPlayer);
    }
    else
    {
        sprintf(m_aErrBuff, "Function NewMatch not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
}

////////////////////////////////////////
//       ALG_NewGiocata
/*! new giocata notification
// \param CARDINFO* pCardArray : 
// \param int iNumOfCards : 
*/
void cAlgPlugin::ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) 
{
    ASSERT(iNumOfCards == NUM_CARDS_HAND);
    if (m_fnNewGiocata)
    {
        m_fnNewGiocata(pCardArray, iNumOfCards,  iPlayerIx);
    }
    else
    {
        sprintf(m_aErrBuff, "Function NewGiocata not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
    
}


////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player has played a card
// \param int iPlayerIx : 
// \param CARDINFO* pCard : 
*/
void cAlgPlugin::ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard) 
{
    ASSERT(pCard);
    if (m_fnPlayerHasPlayed)
    {
        m_fnPlayerHasPlayed(iPlayerIx, pCard);
    }
    else
    {
        sprintf(m_aErrBuff, "Function PlayerHasPlayed not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
    
}

////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player has said something
// \param int iPlayerIx : 
// \param eSayPlayer eSay : 
*/
void cAlgPlugin::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay) 
{
    if (m_fnPlayerHasSaid)
    {
        m_fnPlayerHasSaid(iPlayerIx, eSay);
    }
    else
    {
        sprintf(m_aErrBuff, "Function PlayerHasSaid not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
}


////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cAlgPlugin::ALG_Play() 
{
    if (m_fnPlay)
    {
        m_fnPlay();
    }
    else
    {
        sprintf(m_aErrBuff, "Function Play not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    }
}

////////////////////////////////////////
//       ALG_ManoEnd
/*! mano end notification
*/
void cAlgPlugin::ALG_ManoEnd(I_MatchScore* pScore) 
{
    if (m_fnManoEnd)
    {
        m_fnManoEnd(pScore);
    }
    else
    {
        sprintf(m_aErrBuff, "Function ManoEnd not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    } 
}

////////////////////////////////////////
//       ALG_GiocataEnd
/*! 
*/
void cAlgPlugin::ALG_GiocataEnd(I_MatchScore* pScore) 
{
    if (m_fnGiocataEnd)
    {
        m_fnGiocataEnd(pScore);
    }
    else
    {
        sprintf(m_aErrBuff, "Function GiocataEnd not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    } 
}

////////////////////////////////////////
//       ALG_MatchEnd
/*! match end notification
*/
void cAlgPlugin::ALG_MatchEnd(I_MatchScore* pScore) 
{
    if (m_fnMatchEnd)
    {
        m_fnMatchEnd(pScore);
    }
    else
    {
        sprintf(m_aErrBuff, "Function MatchEnd not set in plugin.");
        throw Error::Generic(m_aErrBuff);
    } 
}

////////////////////////////////////////
//       ALG_Say
/*! Algorithm is invited to responce
*/
void cAlgPlugin::ALG_Say()
{
    // not used
    ASSERT(0);
}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*! 
// \param eGiocataScoreState eNewScore : 
*/
void cAlgPlugin::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{
    // not used
}


////////////////////////////////////////
//       ALG_PLayerSaidFalse
/*! player said somithing false
// \param int iPlayerIx : 
*/
void cAlgPlugin::ALG_PLayerSaidFalse(int iPlayerIx)
{
    // not used
}

////////////////////////////////////////
//       ALG_PLayerDeclareGoodGame
/*! 
// \param int iPlayerIx : 
// \param eDeclGoodGame eValgg : 
// \param eSUIT eValsuit : 
*/
void cAlgPlugin::ALG_PLayerDeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSUIT eValsuit)
{
    
}


