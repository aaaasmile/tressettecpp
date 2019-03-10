//cPopUpMenuGfx.h

#ifndef C_POPUPMENUGFX_H__
#define C_POPUPMENUGFX_H__

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

//! class cPopUpMenuGfx
class  cPopUpMenuGfx
{
	typedef std::vector<STRING> VCT_STRING;
public:
	cPopUpMenuGfx(void);
	~cPopUpMenuGfx(void);

	//! init the msgbox
	void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, SDL_Renderer* pRenderer);
	//! show the message box
	void   Show(SDL_Surface* pScene_background);
	//! add a line in the combo
	void   AddLineText(LPCSTR strLine);
	//! provides the selected index
	int    GetSlectedIndex() { return m_iCurrDataIndex; }
	//! provides the selected flag
	BOOL   MenuIsSelected() { return m_bMenuSelected; }

private:
	SDL_Renderer*   m_psdlRenderer;
	//! rectangle of the messagebox
	SDL_Rect        m_rctMsgBox;
	//! surface where to draw the button
	SDL_Surface*    m_pSurf_Bar;
	//! surface screen
	SDL_Surface*    m_pScreen;
	//! button font
	TTF_Font*	    m_pFontText;
	//! current text color
	SDL_Color       m_colCurrent;
	//! terminated flag
	BOOL            m_bTerminated;
	//! vector of data strings
	VCT_STRING      m_vctDataStrings;
	//! current index
	int             m_iCurrDataIndex;
	//! menu selected flag
	BOOL            m_bMenuSelected;

};


#endif

