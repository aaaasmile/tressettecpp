// cCheckBoxGfx.h: interface for the cCheckBoxGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCHECKBOXGFX_H__60E65099_85E9_47E5_A9A5_F149A96840FF__INCLUDED_)
#define AFX_CCHECKBOXGFX_H__60E65099_85E9_47E5_A9A5_F149A96840FF__INCLUDED_

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FastDelegate.h"
using namespace fastdelegate;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//! class cCheckBoxGfx 
class cCheckBoxGfx  
{
private:
    // use fastdelegate to implement the observer pattern and avoid using the callback interface on observer
    typedef FastDelegate1<int> CLICKEVENT;

    enum
    {
        CHECK_W = 16,
        CHECK_H = 16

    };

public:
	cCheckBoxGfx();
	virtual ~cCheckBoxGfx();

public:
    //! enum eSate
    enum  eSate
    {
        VISIBLE,
        INVISIBLE,
    };

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse move event
    void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! draw the button 
    void   DrawButton(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   RedrawButton(SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! provides click state
    BOOL   GetCheckState(){return m_bClickState;}
    //! set check state
    void   SetCheckState(BOOL bVal){m_bClickState = bVal;}

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
 
private:
    //! button font
    TTF_Font*	   m_pFontText;
    //! current text color
    SDL_Color      m_colCurrent;
    //! click state
    BOOL           m_bClickState;
    //! control id
    int            m_iButID;
    //! no skin flag
    BOOL           m_bNoSkin;
    //! current text color
    SDL_Color      m_colBorder;

};

#endif // !defined(AFX_CCHECKBOXGFX_H__60E65099_85E9_47E5_A9A5_F149A96840FF__INCLUDED_)
