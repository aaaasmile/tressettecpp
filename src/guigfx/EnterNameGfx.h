

// EnterNameGfx.h: interface for the EnterNameGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EnterNameGfx_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_)
#define AFX_EnterNameGfx_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cButtonGfx;
class cEditGfx;


//! calss EnterNameGfx
class EnterNameGfx  
{
    typedef std::vector<STRING> VCT_STRING;
    enum
    {
        MYIDOK = 0,
        MYIDCANCEL,
        MYEDITNAME
    };
public:
	EnterNameGfx();
	virtual ~EnterNameGfx();

    //! init control
    void Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl, SDL_Renderer* psdlRenderer);
    //! shows the control
    void Show(SDL_Surface* pScene_background);
    //! button click callback
    void ButCmdClicked(int iButID);
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
    //! terminated flag
    BOOL            m_bTerminated;
    //! result of click
    int             m_iResult;
    //! header text
    STRING          m_strHeaderText;
    //! Name edit control
    cEditGfx*       m_pEditName;
};

#endif // !defined(AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_)
