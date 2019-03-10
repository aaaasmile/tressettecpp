//AppGfx.h

#ifndef __ENGINE_APP_H
#define __ENGINE_APP_H

#include <stack>

#include "myexception.h"


class cHightScoreMgr;
class cLanguages;
class cInvidoGfx;
class cMusicManager;
class cMenuMgr;
class TraceService;

//! class cEngineApp
class AppGfx
{
public:
	AppGfx();
	~AppGfx();

	//! init stuff
	void            Init();
	//! language translation
	cLanguages*     GetLanguageMan() { return m_pLanString; }
	//! play the invido
	int		        PlayGame();
	//! main loop
	void            MainLoop();
	//! provides font vera
	TTF_Font*       GetFontVera() { return m_pfontVera; }
	//! provide font ariblk
	TTF_Font*       GetFontAriblk() { return m_pfontAriblk; }
	//! Leave current menu
	void            LeaveMenu();
	//! set next menu
	void            SetNextMenu(int iVal) { m_Histmenu.push(iVal); }
	//! show menu help
	void            ShowHelp();
	//! provides music manager
	cMusicManager*  GetMusicManager() { return m_pMusicManager; }
	//! show credits screen
	void            ShowCredits();
	//! show options
	void            ShowOptionsGeneral();
	STRING          GetApplicationDir() { return m_strApplicationDir; }
	void            SetApplicationDir(STRING val) { m_strApplicationDir = val; }


private:
	void    intWindowAndRender();
	void    terminate();
	void    hightScoreMenu();

	void    loadProfile();
	void    writeProfile();
	void    drawSplash();
	void    loadSplash();
	void    showEditUserName();
	void    updateScreenTexture();

private:
	SDL_Surface*      m_pScreen;
	SDL_Texture*      m_pScreenTexture;
	SDL_Window*       m_pWindow;
	SDL_Renderer*     m_psdlRenderer;
	//! splash surface
	SDL_Surface*      m_pSlash;
	//! title credits
	SDL_Surface*      m_pTitleCredits;
	//! screen width
	int               m_iScreenW;
	//! screen height
	int               m_iScreenH;
	//! bit per pixel
	int               m_iBpp;
	//! hight score data
	cHightScoreMgr*   m_pHScore;
	//! get strings on differnt languages
	cLanguages*       m_pLanString;
	//! grafic game engines
	cInvidoGfx*       m_pInvidoGfx;
	//! music player  
	cMusicManager*    m_pMusicManager;
	//! menu state stack
	std::stack<int>   m_Histmenu;
	//! menu handler
	cMenuMgr*         m_pMenuMgr;
	//! font 
	TTF_Font*         m_pfontVera;
	//! font
	TTF_Font*	      m_pfontAriblk;
	//! mutex access dialog opions
	SDL_mutex*        m_pMxAccOptions;
	//! condition dialog terminated
	SDL_cond*         m_pOptCond;
	//! running flag option window
	BOOL              m_bOpzWinRunning;
	// application directory
	STRING            m_strApplicationDir;
    TraceService*     m_pTracer;
};


#endif