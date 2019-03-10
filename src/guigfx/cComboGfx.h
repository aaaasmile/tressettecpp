// cComboGfx.h: interface for the cComboGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cComboGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_cComboGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include "FastDelegate.h"
using namespace fastdelegate;


//! class  cComboGfx  
class cComboGfx  
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

	cComboGfx();
   	virtual ~cComboGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID, SDL_Renderer* psdlRenderer);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse move event
	void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! draw the button 
    void   DrawButton(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   RedrawButton(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture);
    //! add a line in the combo
    void   AddLineText(LPCSTR strLine);
    //! select an index
    void   SelectIndex(UINT iIndex);
    //! provides the selected index
    int    GetSlectedIndex(){return m_iCurrDataIndex;}
    //! provides the selected text
    LPCSTR GetSelectedText(){return m_vctDataStrings[m_iCurrDataIndex].c_str();}

public:
    //! button state
    eSate         m_eState;
    //! rectangle of the button
    SDL_Rect      m_rctButt; 
    //! rect area text
    SDL_Rect      m_rctText;
    //! rect area up
    SDL_Rect      m_rctBoxUp;
    //! rect area down
    SDL_Rect      m_rctBoxDown;
    //! text on the button
    STRING        m_strButText;
    //! enabled flag
    BOOL          m_bIsEnabled;
    //! click the event
    CLICKEVENT    m_fncbClickEvent;

private:
	SDL_Renderer*   m_psdlRenderer;
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
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
    //! vector of data strings
    VCT_STRING      m_vctDataStrings;
    //! current index
    UINT            m_iCurrDataIndex;
    

};

#endif // !defined(AFX_cComboGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
