

// cEditGfx.h: interface for the cEditGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cEditGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_cEditGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FastDelegate.h"
using namespace fastdelegate;


//! class  cEditGfx  
class cEditGfx  
{
    // use fastdelegate to implement the observer pattern and avoid using the callback interface on observer
    typedef FastDelegate1<int> CLICKEVENT;
    enum
    {
        XOFFSET = 5
    };
public:
    //! enum eSate
    enum  eSate
    {
        VISIBLE,
        INVISIBLE,
        SELECTED
    };

	cEditGfx();
   	virtual ~cEditGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID, SDL_Renderer* psdlRenderer);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! get window text
    LPCSTR GetWindowText(){return m_strButText.c_str();}
    //! mouse move event
    void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! draw the button 
    void   DrawControl(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! provides the current state
    eSate  GetState(){return m_eState;}
    //! redraw the button
    void   RedrawButton(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture);
    //! control lost the focus
    void   LostFocus();
    //! control becomes focus
    void   GetFocus();
    //! key down event
    void   KeyDown(SDL_Event &event);
	void   TextInput(SDL_Event &event);
    //! set the numeric only flag
    void   SetNumericOnly(BOOL bVal){m_bOnlyNum = bVal;}

private:
	size_t FindCaretPosInBuffer();
	size_t FindLastLogicalPos();

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
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
	SDL_Renderer*   m_psdlRenderer;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! current text color
    SDL_Color       m_colBorder;
    //! button id
    int             m_iButID;
    //! caret start time
    Uint32          m_uiStartTime;
    //! show caret flag
    BOOL            m_bShowCaret;
    //! caret logical position
    size_t            m_iCarLogPos;
    //! numeric input mask flag
    BOOL            m_bOnlyNum;
	UINT			m_iMaxLen;
    

};

#endif // !defined(AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
