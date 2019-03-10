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



//cPlayer.cpp
#include "StdAfx.h"
#include "cPlayer.h"
#include "cAlgDefault.h"
#include "cAlgPlugin.h"

////////////////////////////////////////////////////////////////
//  *************************  PLAYER CLASS *******************
////////////////////////////////////////////////////////////////

////////////////////////////////////////
//       cPlayer
/*! Constructor
*/
cPlayer::cPlayer():m_pAlgPlugin(0)
{
    m_iIndex = NOT_VALID_INDEX;
    m_pIAlgorithm = 0;
    m_eLevel = DEFAULT;
}

////////////////////////////////////////
//       ~cPlayer
/*! Destructor
*/
cPlayer::~cPlayer()
{
    size_t iNumEle = m_vctAlgToDestroy.size();
    for (int i = 0; i < iNumEle; i++)
    {
        delete m_vctAlgToDestroy[i];
    }
    clearPlugIn();
    
}

////////////////////////////////////////
//       cPlayer
/*! Copy constructor
// \param const cPlayer&a : 
*/
cPlayer::cPlayer(const cPlayer&a)
{
   
    strncpy(m_pPlayerName, a.m_pPlayerName, BUFF_NAME);
    m_eKind = a.m_eKind;
    m_iIndex = a.m_iIndex ;
    m_pIAlgorithm = a.m_pIAlgorithm;
    m_eLevel = a.m_eLevel;
    m_pAlgPlugin = a.m_pAlgPlugin;
}


////////////////////////////////////////
//       operator=
/*! Copy player operator
// \param const cPlayer&a : 
*/
cPlayer& cPlayer::operator=(const cPlayer&a)
{
    strncpy(m_pPlayerName, a.m_pPlayerName, BUFF_NAME);
    m_eKind = a.m_eKind;
    m_iIndex = a.m_iIndex ;
    m_pIAlgorithm = a.m_pIAlgorithm;
    m_eLevel = a.m_eLevel;
    m_pAlgPlugin = a.m_pAlgPlugin;

    return *this;
}

////////////////////////////////////////
//       Create
/*! Create a default player
*/
void cPlayer::Create()
{
    CardSpec emptyCard;
    m_eKind = PT_LOCAL;
    strcpy(m_pPlayerName,"Anonimo");
   
    m_iIndex = NOT_VALID_INDEX ;
    m_eLevel = DEFAULT;
}


////////////////////////////////////////
//       SetName
/*! Set player name
// \param LPCSTR lpszName : new name
*/
void    cPlayer::SetName(LPCSTR lpszName)
{
    strncpy(m_pPlayerName, lpszName,BUFF_NAME-1);
}


////////////////////////////////////////
//       SetType
/*! Set type of player
// \param eTypeOfPLayer eVal : 
*/
void    cPlayer::SetType(eTypeOfPLayer eVal)
{
    m_eKind = eVal;
}


////////////////////////////////////////
//       SetLevel
/*! Set the level of the player. This crate a new algorithm class to manage the player AI.
// Algorithm inteface coulb be also delivered as input parameter.
// CAUTION on HMI algorithm, is not to be deleted, only copied
// \param eGameLevel eNewLevel : level player
// \param I_ALG_Player* I_val : eventually already created algorithm insterface
*/
void    cPlayer::SetLevel(eGameLevel eNewLevel, I_ALG_Player* I_val)
{
    if (m_pIAlgorithm != 0 && m_eLevel != HMI)
    {
        delete m_pIAlgorithm;
        m_pIAlgorithm = 0;
    }
    m_eLevel = eNewLevel;
    
    switch(eNewLevel)
    {
        case DEFAULT:
            
            m_pIAlgorithm = new cAlgDefault;
            m_vctAlgToDestroy.push_back(m_pIAlgorithm);
            break;

        case HMI:
            ASSERT(I_val);
            m_pIAlgorithm = I_val;
            break;

        case PLUGIN:
            clearPlugIn();
            m_pAlgPlugin = new cAlgPlugin;
            m_pIAlgorithm = m_pAlgPlugin;
            break;

        default:
            ASSERT(0);
            m_pIAlgorithm = new cAlgDefault;
            m_vctAlgToDestroy.push_back(m_pIAlgorithm);
            break;

    }
}


////////////////////////////////////////
//       InitPlugin
/*! Initialize the plugin
// \param LPCSTR strPluginName : plugin path name 
*/
void cPlayer::InitPlugin(LPCSTR strPluginName)
{
    if (m_pAlgPlugin && m_eLevel == PLUGIN)
    {
        m_pAlgPlugin->Init(strPluginName);
    }
    
}

////////////////////////////////////////
//       clearPlugIn
/*! 
*/
void cPlayer::clearPlugIn()
{
    if (m_pAlgPlugin)
    {
        delete m_pAlgPlugin;
        m_pAlgPlugin = 0;
    }
}

