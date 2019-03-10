
//cMesgBoxGfx.h

#ifndef C_MSG_BOX_H__
#define C_MSG_BOX_H__

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class  cButtonGfx;

//! class cMesgBoxGfx
class cMesgBoxGfx
{
	typedef std::vector<STRING> VCT_STRING;
public:
	cMesgBoxGfx(void);
	~cMesgBoxGfx(void);

	enum eMSGBOX_TYPE
	{
		MBOK,
		MB_YES_NO
	};
	enum
	{
		MB_RES_NO = 0,
		MB_RES_YES = 1,
		MB_ID_BUTT_YES = 2,
		MB_ID_BUTT_NO = 3,
	};

	//! init the msgbox
	void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, eMSGBOX_TYPE eval, SDL_Renderer* pRenderer);
	//! show the message box
	int    Show(SDL_Surface* pScene_background, LPCSTR lpsBut1_txt, LPCSTR lpsBut2_txt, LPCSTR lpsMsg_txt);
	//! button click callback
	void   ButCmdClicked(int iButID);
	//! add a line in the data list
	void   AddLineText(LPCSTR strLine) { m_vctDataStrings.push_back(strLine); }

private:
	SDL_Renderer*   m_psdlRenderer;
	//! rectangle of the messagebox
	SDL_Rect      m_rctMsgBox;
	//! text on the messagebox
	STRING        m_strMsgText;
	//! surface where to draw the button
	SDL_Surface*    m_pSurf_Bar;
	//! surface screen
	SDL_Surface*    m_pScreen;
	//! button font
	TTF_Font*	    m_pFontText;
	//! current text color
	SDL_Color       m_colCurrent;
	//! type of messagebox
	eMSGBOX_TYPE    m_eTypeMsg;
	//! button 1
	cButtonGfx*     m_pBtButt1;
	//! button 2
	cButtonGfx*     m_pBtButt2;
	//! terminated flag
	BOOL            m_bTerminated;
	//! result of click
	int             m_iResult;
	//! vector of data strings
	VCT_STRING      m_vctDataStrings;

};


#endif

