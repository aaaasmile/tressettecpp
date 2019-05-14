// cMusicManager.h: interface for the cMusicManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMUSICMANAGER_H__166CCA3D_1404_45EE_821B_544A592F0B4F__INCLUDED_)
#define AFX_CMUSICMANAGER_H__166CCA3D_1404_45EE_821B_544A592F0B4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL_mixer.h"


//! class cMusicManager  
class cMusicManager
{
public:
    enum
    {
        /*
        // DON'T change the position or change the load sequence
        SND_IG_CHIAMAPIU = 0,
        SND_IG_FUORIGIOCO,
        SND_IG_INV_LONG,
        SND_IG_INV_NORM,
        SND_IG_INV_SECCO,
        SND_IG_MONTE_AMUNT,
        SND_IG_MONTE_NORM,
        SND_IG_NO_BORTOLO,
        SND_IG_NO_FRONTE,
        SND_IG_NO_NORMAL,
        SND_IG_PARTIDA,
        SND_IG_TRASMAS_LONG,
        SND_IG_TRASMAS_NEUT,
        SND_IG_NOEF_DILECT,
        SND_IG_NOEF_NORMA,
        SND_IG_VABENE_GIOCA,
        SND_IG_VABENEONLY,
        SND_IG_VAVIA,
        // DON'T change the position or change the load sequence
        SND_IG_VUVIA,
        // if you want to add music, make here:
        */
        MUSIC_INIT_SND,
        //MUSIC_ONPLAY,
        //... untill herre. Thank you.
        NUM_OF_SOUNDS
    };
    enum
    {
        //effects
        SND_EFC_CLICK,
        SND_EFC_CARDFALSE,

        NUM_OF_WAV
    };
    enum eLoopType
    {
        LOOP_ON,
        LOOP_OFF
    };
    //! constructor
    cMusicManager();
    //! destructor
    virtual ~cMusicManager();

    //! init stuff
    void Init();
    //! stop playng music
    void StopMusic();
    //! play a music resource
    BOOL PlayMusic(int iID, eLoopType eVal);
    //! play an effect (wav only)
    BOOL PlayEffect(int iID);
    //! load music resource
    void LoadMusicRes();
    //! info on playing music
    BOOL IsPLayingMusic();
    //! change the volume music
    void SetVolumeMusic(int iVal);

private:
    //! music collection  
    Mix_Chunk*        m_pMusicsWav[NUM_OF_WAV];
    Mix_Music*        m_pMusics[NUM_OF_SOUNDS];
    //! music available flag
    BOOL     m_bMusicAvailable;

};

#endif // !defined(AFX_CMUSICMANAGER_H__166CCA3D_1404_45EE_821B_544A592F0B4F__INCLUDED_)
