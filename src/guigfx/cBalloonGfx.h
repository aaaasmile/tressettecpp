
// cBalloonGfx.h: interface for the cBalloonGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBALLOONGFX_H__E3B36325_213E_4794_8FDC_43E3046E0A79__INCLUDED_)
#define AFX_CBALLOONGFX_H__E3B36325_213E_4794_8FDC_43E3046E0A79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

//! class   cBalloonGfx  
class cBalloonGfx  
{
public:
    //! enum eStyle
    enum eStyle
    {
        ARROW_DWN_LEFT,
        ARROW_DWN_RIGHT,
        ARROW_UP
    };
public:
	cBalloonGfx();
	virtual ~cBalloonGfx();

    //! init balloon
    void Init(SDL_Rect& rct, SDL_Surface* pImage, TTF_Font* pFont, int alphaVal);
    //! set style
    void SetStyle(eStyle eVal, SDL_Surface* pImage);
    //! draw control
    void Draw(SDL_Surface* pScreen);
    //! start show the control
    void StartShow(LPCSTR lpszText);
    void StartShow(LPCSTR lpszText, Uint32 uiTick);
    //! disable
    void Disable();
    //! provides the enable flag
    BOOL GetEnableState(){return m_bEnabled;}

private:
    void    startshow(LPCSTR lpszText, Uint32 uiTick);

private:
    //! ballon position
    SDL_Rect      m_destWIN;
    //! arrow position
    SDL_Rect      m_ArrWIN;
    //! ballon image
    SDL_Surface*  m_pImageBall;
    //! arrow image
    SDL_Surface*  m_pImageArrow;
    //! string text
    STRING        m_strText;
    //! second line text
    STRING        m_strText2;
    //! init tick
    Uint32        m_uiInitTick;
    //! showing time
    Uint32        m_uiShowTick;
    //! balloon enabled
    BOOL          m_bEnabled;
    //! button font
    TTF_Font*	  m_pFontText;
    //! current text color
    SDL_Color     m_colCurrent;
    //! style
    eStyle        m_eStyle;
	int           m_alphaVal;
};

#endif // !defined(AFX_CBALLOONGFX_H__E3B36325_213E_4794_8FDC_43E3046E0A79__INCLUDED_)
