// cMusicManager.cpp: implementation of the cMusicManager class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "win_type_global.h"
#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "AppGfx.h" 

#include "cMusicManager.h"
#include "InvidoSettings.h"

extern AppGfx TheApp;

static const char* lpszMusicDir = "data/music";
static const char* lpszVoiceIgSubDir = "/voci/ig";
static const char* lpszaSound_filenames[cMusicManager::NUM_OF_SOUNDS] = 
{
    "data/music/wolmer-invido.ogg"
};

static const char* lpszaEffects_filenames[cMusicManager::NUM_OF_WAV] = 
{
    // synth voice
    "data/music/voci/synth_female/amonte.wav",
    "data/music/voci/synth_female/avuvia.wav",
    "data/music/voci/synth_female/chiamadipiu.wav",
    "data/music/voci/synth_female/fuorigioco.wav",
    "data/music/voci/synth_female/invido.wav",
    "data/music/voci/synth_female/no.wav",
    "data/music/voci/synth_female/partida.wav",
    "data/music/voci/synth_female/trasmas.wav",
    "data/music/voci/synth_female/trasmasnof.wav",
    "data/music/voci/synth_female/vabene.wav",
    "data/music/voci/synth_female/gioca.wav",
    // igor voice
    "data/music/voci/ig/chiamadipiu_4bit.wav",
    "data/music/voci/ig/foerajeuq_n_4bit.wav",
    "data/music/voci/ig/gioca_4bit.wav",
    "data/music/voci/ig/invido_secco_4bit.wav",
    "data/music/voci/ig/monte_n_4bit.wav",
    "data/music/voci/ig/no_n_4bit.wav",
    "data/music/voci/ig/partida_n_4bit.wav",
    "data/music/voci/ig/trasmas_n_4bit.wav",
    "data/music/voci/ig/trasmasnoef_n_4bit.wav",
    "data/music/voci/ig/vabene_4bit.wav",
    "data/music/voci/ig/vuvia_n_4bit.wav",
    "data/music/voci/ig/no_bortolo_4bit.wav",
    //other wav
    "data/music/effects/click_4bit.wav"
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cMusicManager::cMusicManager()
{
    for (int i = 0; i < NUM_OF_SOUNDS; i++)
    {
        m_pMusics[i] = 0;
    }
    m_bMusicAvailable = FALSE;
    for (int j = 0; j < NUM_OF_WAV; j++)
    {
        m_pMusicsWav[j] = 0;
    }

}

cMusicManager::~cMusicManager()
{

}


////////////////////////////////////////
//       Init
/*! Initialize audio stuff
*/
void cMusicManager::Init()
{
    // sound
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr,
  	      "\nWarning: I could not initialize audio!\n"
	      "The Simple DirectMedia error that occured was:\n"
	      "%s\n\n", SDL_GetError());
	       
    }
    else
    {
        if (Mix_OpenAudio(44100, AUDIO_S16, 2, 1024) < 0)
        {
            fprintf(stderr,
	        "\nWarning: I could not set up audio for 44100 Hz "
	        "16-bit stereo.\n"
	        "The Simple DirectMedia error that occured was:\n"
	        "%s\n\n", SDL_GetError());
            
        }
        else
        {
            m_bMusicAvailable = TRUE;
        }
    }
}


////////////////////////////////////////
//       LoadMusicRes
/*! Load musis resource
*/
void cMusicManager::LoadMusicRes()
{
    // load musics
    for (int i = 0; i < NUM_OF_SOUNDS; i++)
    {
        STRING strFileTmp2 =  lpszaSound_filenames[i];
        m_pMusics[i] = Mix_LoadMUS( strFileTmp2.c_str() );
    }
    

    //load effects
    for (int j = 0; j < NUM_OF_WAV; j++)
    {
        m_pMusicsWav[j] = Mix_LoadWAV(lpszaEffects_filenames[j]);
    }

}

////////////////////////////////////////
//       StopMusic
/*! Stop play music
*/
void cMusicManager::StopMusic()
{
    Mix_FadeOutMusic(100);
    Mix_HaltMusic();
}


////////////////////////////////////////
//       IsPLayingMusic
/*! Return TRUE if music is playing, false otherwise
*/
BOOL cMusicManager::IsPLayingMusic()
{
    return Mix_PlayingMusic();
}
////////////////////////////////////////
//       PlayMusic
/*! Start play music
*/
BOOL cMusicManager::PlayMusic(int iID, eLoopType eVal)
{
   if (iID < 0 || iID >=  NUM_OF_SOUNDS  || !m_bMusicAvailable)
   {
       // sound not available
       return FALSE;
   }
   if (m_pMusics[iID] == 0)
   {
       // resource not found
       return FALSE;
   }
   
   if (eVal == LOOP_OFF)
   {
       // play music only once
       Mix_PlayMusic(m_pMusics[iID], 0);
   }
   else
   {
       // play music infinitly
       Mix_PlayMusic(m_pMusics[iID], -1);
   }


   return TRUE;
}


////////////////////////////////////////
//       PlayEffect
/*! Play a music chunk
// \param int iID : 
*/
BOOL cMusicManager::PlayEffect(int iID)
{
    if (iID < 0 || iID >=  NUM_OF_WAV  || !m_bMusicAvailable)
    {
        // sound not available
        return FALSE;
    }
    Mix_PlayChannel(-1, m_pMusicsWav[iID], 0);

    return TRUE;
}


////////////////////////////////////////
//       SetVolumeMusic
/*! Change volume of music
// \param int iVal : 
*/
void cMusicManager::SetVolumeMusic(int iVal)
{
    int iCurr = Mix_VolumeMusic(iVal);
    
}
