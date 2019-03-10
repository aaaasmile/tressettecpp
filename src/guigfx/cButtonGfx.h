
// cButtonGfx.h: interface for the cButtonGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FastDelegate.h"
using namespace fastdelegate;


//! class  cButtonGfx  
class cButtonGfx  
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

    enum eType
    {
        TEXT_BUTTON,
        BITMAP_BUTTON
    };

	cButtonGfx();
   	virtual ~cButtonGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID, SDL_Renderer* psdlRenderer);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse move event
    void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background, SDL_Texture* pScreenTexture);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! mouse down
    void   MouseDown(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background, SDL_Texture* pScreenTexture);
    //! draw the button 
    void   DrawButton(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   RedrawButton(SDL_Surface* pScreen, SDL_Surface* pScene_background, SDL_Texture* pScreenTexture);
    //! set a button type (bitmap or text)
    void   SetButtonType(eType eTypevalue){m_eButType = eTypevalue;}
    //! set bitmap surfaces
    void   SetButBitmapSurfaces(SDL_Surface* pS1, SDL_Surface* pS2, SDL_Surface* pS3)
        {m_pSurf_Bitmap_Act1 = pS1; m_pSurf_Bitmap_MOv2 = pS2; m_pSurf_Bitmap_Pus3 = pS3;}

private:
    void   drawBtAsBitmap(SDL_Surface*  pScreen);

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
	SDL_Renderer*     m_psdlRenderer;
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button id
    int             m_iButID;
    //! button is hold down
    BOOL            m_bMouseIsDown;
    //! button type
    eType           m_eButType;
    //! normal bitmap bitmap
    SDL_Surface*    m_pSurf_Bitmap_Act1;
    //! mouse over bitmap
    SDL_Surface*    m_pSurf_Bitmap_MOv2;
    //! button pushed bitmap
    SDL_Surface*    m_pSurf_Bitmap_Pus3;
    

};

#endif // !defined(AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
