

// OptionGfx.h: interface for the OptionGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_)
#define AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cButtonGfx;
class cCheckBoxGfx;
class cEditGfx;
class cComboGfx;
class cProgressBarGfx;

//! calss OptionGfx
class OptionGfx  
{
    typedef std::vector<STRING> VCT_STRING;
    enum
    {
        MYIDOK = 0,
        MYIDCANCEL = 1,
        MYIDMUSICCHK = 2,
        MYEDITNAME = 3,
        MYIDCOMBOLAN = 4,
        MYIDSOUNDEFFECT = 5,
        MYIDCOMBOALG_PL1 = 6,
        MYIDCOMBOALG_PL2 = 7,
        MYIDCOMBOALG_PL3 = 8,
        MYIDCOMBOALG_PL4 = 9,
        MYIDCHKSHOWALGCONTROL = 10,
        MYIDCHKSHOWANIMATIONS = 11,
        MYIDPROGBARSPEEDANI = 12,
        MYIDCHKBLOCKAFTERMANOEND = 13,
        MYIDCHKSIGNALRMOUSE = 14,
        MYIDSHOWFOTOBACK = 15
    };
public:
	OptionGfx();
	virtual ~OptionGfx();

    //! init control
    void Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl, SDL_Renderer* pRenderer);
    //! shows the control
    void Show(SDL_Surface* pScene_background);
    //! button click callback
    void ButCmdClicked(int iButID);
    //! checkbox callback
    void ClickCheckBox(int iButID);
    //! combobox callback
    void ComboCmdClicked(int iButID);
    //! set caption text
    void SetCaption(STRING& strCaption){m_strHeaderText = strCaption;}

    
private:
	SDL_Renderer*   m_psdlRenderer;
    //! rectangle of the options control
    SDL_Rect        m_rctOptBox; 
    //! text on the messagebox
    SDL_Surface*    m_pSurf_Bar;
    //! surface screen
    SDL_Surface*    m_pScreen;
    //! text font
    TTF_Font*	    m_pFontText;
    //! button font
    TTF_Font*	    m_pFontCtrl;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button 1
    cButtonGfx*     m_pBtOK;
    //! button 2
    cButtonGfx*     m_pBtCancel;
    //! terminated flag
    BOOL            m_bTerminated;
    //! result of click
    int             m_iResult;
    //! header text
    STRING          m_strHeaderText;
    //! checkbox music
    cCheckBoxGfx*   m_pCheckMusic;
    //! checkbox effect
    cCheckBoxGfx*   m_pCheckSoundEffect;
    //! checkbox show foto back 
    cCheckBoxGfx*   m_pCheckShowFotoBack;
    //! Name edit control
    cEditGfx*       m_pEditName;
    //! combo language selection
    cComboGfx*      m_pComboLang;
    //! installed plugin list
    VCT_STRING      m_vct_InstPlugDllName;
    //! installed plugin engine name
    VCT_STRING      m_vct_PlugEngineName;
    //! shows advanced flag
    BOOL            m_bShowAlgControls;
    //! flag show progress bar animation speed
    BOOL              m_bShowProgSpeedAni;
   
};

#endif // !defined(AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_)
