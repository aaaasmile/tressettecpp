

// cPlayer.h


#ifndef  __CPLAYER_H__
#define  __CPLAYER_H__

#include "cInvidoCoreEnv.h"
#include "CardSpec.h"
#include "cPlayerStatistic.h"


/////////////////////////////////////////////////////////////////////////////////////
// *********************************     CPLAYER CLASS  ****************************
/////////////////////////////////////////////////////////////////////////////////////

//! enum for navigating in the cards hand
enum eCARDINDEX
{
    CIX_0 = 0,
    CIX_1 = 1,
    CIX_2 = 2
};

//prefix increment applied to enum eCARDINDEX
inline eCARDINDEX &operator++ (eCARDINDEX & eF)
{
   return eF = (eF >= CIX_2) ?  CIX_0 : eCARDINDEX(eF + 1);
}
//postfix increment applied to enum eFieldType
inline eCARDINDEX &operator++ (eCARDINDEX & eF, int)
{
   return eF = (eF >= CIX_2) ?  CIX_0 : eCARDINDEX(eF + 1);
}



//! class cPlayer 
/** Store information about the player
*/
class cPlayer
{
typedef std::vector<I_ALG_Player*> VCT_PALG;
public: 
    cPlayer();
    virtual ~cPlayer();

    //! create a default player
    void    Create();
    //! set the type
    void    SetType(eTypeOfPLayer eVal);
    //! set player level
    void    SetLevel(eGameLevel eNewLevel, I_ALG_Player* I_val);
    //! get player level
    eGameLevel GetLevel(){return m_eLevel;}
    //! provides player type
    eTypeOfPLayer  GetType(){return m_eKind;}
    //! provides player index
    int     GetIndex(){return m_iIndex;}
    //! set index
    void    SetIndex(int iVal){m_iIndex = iVal;}
    //! provides player name
    CHAR*   GetName(){return m_pPlayerName;}
    //! set player name
    void    SetName(LPCSTR lpszName);
    //! provides algorithm 
    I_ALG_Player* GetAlg(){return m_pIAlgorithm;}
    
    friend std::ostream &operator << (std::ostream &stream, const cPlayer &o);
    //! copy constructor
    cPlayer(const cPlayer&a);
    //! operator assignement
    cPlayer& operator=(const cPlayer&a);

private:
    //! playername
    CHAR             m_pPlayerName[BUFF_NAME];
    //! kind of player
    eTypeOfPLayer    m_eKind;
    //! player index
    int              m_iIndex;
    //! algorithm interface
    I_ALG_Player*    m_pIAlgorithm;
    //! created algorithms to destroy
    VCT_PALG         m_vctAlgToDestroy;
    //! player level 
    eGameLevel       m_eLevel;
};

typedef std::vector<cPlayer>  VCT_PLAYERS;

//operators
inline std::ostream &operator << (std::ostream &stream, const cPlayer &o)
{ 
    stream << o.m_pPlayerName << std::endl;
   
    return stream;
}


#endif


