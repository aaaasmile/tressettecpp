
// cLabelLinkGfx.h: interface for the cLabelLinkGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cLabelLinkGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_cLabelLinkGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FastDelegate.h"
using namespace fastdelegate;

//! class  cLabelLinkGfx  
class cLabelLinkGfx  
{
    // use fastdelegate to implement the observer pattern and avoid using the callback interface on observer
    typedef FastDelegate1<int> CLICKEVENT;
    
public:
    //! enum eSate
    enum  eSate
    {
        VISIBLE,
        INVISIBLE,
        PRESSED
    };

    cLabelLinkGfx();
    virtual ~cLabelLinkGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID, SDL_Renderer* psdlRenderer);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse move event
    void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! draw the button 
    virtual void   Draw(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   Redraw(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture);
    //! set the url
    void   SetUrl(LPCSTR lpszUrl){m_strUrl = lpszUrl;}

public:
    //! button state
    eSate         m_eState;
    //! rectangle of the button
    SDL_Rect      m_rctButt; 
    //! text on the button
    STRING        m_strButText;
    //! enabled flag
    BOOL          m_bIsEnabled;
    //! click the event
    CLICKEVENT    m_fncbClickEvent;

protected:
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button id
    int             m_iButID;
    //! url
    STRING          m_strUrl;
	SDL_Renderer*   m_psdlRenderer;
};

#endif // !defined(AFX_cLabelLinkGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
