// cProgressBarGfx.h: interface for the cProgressBarGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cProgressBarGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_cProgressBarGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FastDelegate.h"
using namespace fastdelegate;


//! class  cProgressBarGfx  
class cProgressBarGfx  
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

	cProgressBarGfx();
   	virtual ~cProgressBarGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, SDL_Surface*  pCursor, TTF_Font* pFont, int iButID, SDL_Renderer* pRenderer);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! mouse down
    void   MouseDown(SDL_Event &event);
    //! draw the button 
    void   DrawControl(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   RedrawControl(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture);
    //! set the number of steps
    void   SetNumStep(int iVal){m_iNumOfStep = iVal;}
    //! set the range
    void   SetRange(int iLowRange, int iUpRange){m_iLowRange = iLowRange; m_iUpRange = iUpRange;}
    //! set the current level
    void   SetCurrLevel(int iVal){m_iCurrLevel = iVal;}
    //! provides the current selected level
    int    GetCurrLevel();
    //! set value label begin
    void   SetLabelBEG(LPCSTR lpszVal){m_strLabelBEG = lpszVal;}
    //! set value label end
    void   SetLabelEND(LPCSTR lpszVal){m_strLabelEND = lpszVal;}

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
    //! cursor image
    SDL_Surface*    m_pImageCursor;
    //! selected surface
    SDL_Surface*    m_pSurf_BoxSel;
    //! unselected surface
    SDL_Surface*    m_pSurf_BoxUNSel;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button id
    int             m_iButID;
    //! rectangle cursor
    SDL_Rect        m_rctCursor;
    //! low range
    int             m_iLowRange;
    //! up range
    int             m_iUpRange;
    //! number of steps
    int             m_iNumOfStep;
    //! current level
    int             m_iCurrLevel;
    //! drag flag
    BOOL            m_bOnDrag;
    //! label begin
    STRING          m_strLabelBEG;
    //! label end   
    STRING          m_strLabelEND;
};

#endif // !defined(AFX_cProgressBarGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
