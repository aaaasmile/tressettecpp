//cPlayer.cpp

#include "StdAfx.h"
#include "cPlayer.h"
#include "cAlgDummyPlayer.h"
#include "cAlgAdvancedPlayer.h"

////////////////////////////////////////////////////////////////
//  *************************  PLAYER CLASS *******************
////////////////////////////////////////////////////////////////

////////////////////////////////////////
//       cPlayer
/*! Constructor
*/
cPlayer::cPlayer()
{
    m_iIndex = NOT_VALID_INDEX;
    m_pIAlgorithm = 0;
    m_eLevel = DUMMY;
}

////////////////////////////////////////
//       ~cPlayer
/*! Destructor
*/
cPlayer::~cPlayer()
{
    for (size_t i = 0; i < m_vctAlgToDestroy.size(); i++)
    {
        delete m_vctAlgToDestroy[i];
    }
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
    strcpy(m_pPlayerName,"Remigiu");
   
    m_iIndex = NOT_VALID_INDEX ;
    m_eLevel = DUMMY;
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
    if (m_pIAlgorithm != 0 && m_eLevel != HMI && m_eLevel != SERVER_LEVEL)
    {
        delete m_pIAlgorithm;
        m_pIAlgorithm = 0;
    }
    m_eLevel = eNewLevel;
    
    switch(eNewLevel)
    {
        case BEGINNER:
            ASSERT(0);
            break;

        case ADVANCED:
            m_pIAlgorithm = new cAlgAdvancedPlayer();
            m_vctAlgToDestroy.push_back(m_pIAlgorithm);
            break;

        case NIGHTMARE:
            ASSERT(0);
            break;

        case SERVER_LEVEL:
        case HMI:
            ASSERT(I_val);
            m_pIAlgorithm = I_val;
            break;

        default:
            ASSERT(0);

    }
}

