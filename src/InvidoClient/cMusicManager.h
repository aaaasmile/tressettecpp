
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
    enum // music
    {
     // if you want to add music, make here:
        MUSIC_INIT_SND,
     //... untill here. Thank you.
        NUM_OF_SOUNDS
    };
    enum // effects: nota che l'ordine è importante e viene usato durante il caricamento
    {
        // synth voice
        SND_WAV_SYF_MONTE,
        SND_WAV_SYF_VUVIA,
        SND_WAV_SYF_CHIADIPIU,
        SND_WAV_SYF_FUORIGI,
        SND_WAV_SYF_INVIDO,
        SND_WAV_SYF_NO,
        SND_WAV_SYF_PARTIDA,
        SND_WAV_SYF_TRASMAS,
        SND_WAV_SYF_NOEF,
        SND_WAV_SYF_VABENE,
        SND_WAV_SYF_GIOCA,
        // igor voice
        SND_IG_CHIAMAPIU,
        SND_IG_FUORIGIOCO,
        SND_IG_GIOCA,
        SND_IG_INV_NORM,
        SND_IG_MONTE_NORM,
        SND_IG_NO,
        SND_IG_PARTIDA,
        SND_IG_TRASMAS,
        SND_IG_TRASNOEF,
        SND_IG_VABENE,
        SND_IG_VUVIA,
        SND_IG_BORTOLO,
        //effects
        SND_EFC_CLICK,

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
