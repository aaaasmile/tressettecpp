// cMenuMgr.cpp: implementation of the cMenuMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "win_type_global.h"
#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <math.h>
#include "cMenuMgr.h"
#include "AppGfx.h"
#include "cMenuMgr.h"
#include "Languages.h"
#include "gfx_util.h"

#include "cLabelLinkGfx.h"
#include "cLabelGfx.h"
#include "myexception.h"

static const char* lpszUrlHome = "http://www.invido.it";
static const char* lpszMsgUrl = "Go to www.invido.it";
static const char* lpszVersion = "Ver 2.1.0 20180527"; // formato simile a 'Ver 0.5.4 14042008'
static const char* lpszIniFontVera = "data/font/vera.ttf"; 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const SDL_Color cMenuMgr::staColor_on = {253, 252, 250};
const SDL_Color cMenuMgr::staColor_off = {128,128,128};
const SDL_Color cMenuMgr::staColor_white = {255,255,255};
const SDL_Color cMenuMgr::staColor_ombre = { 87, 87, 87, 50 };
const SDL_Color cMenuMgr::staColor_black= { 0, 0, 0 };
const SDL_Color cMenuMgr::staColor_gray= { 128, 128, 128};

////////////////////////////////////////
//       cMenuMgr
/*! 
// \param cEngineApp* pApp : 
// \param cInvidoGfx* pGfx : 
*/
cMenuMgr::cMenuMgr(AppGfx* pApp, cInvidoGfx* pGfx)
{
    m_pApp = pApp;
    m_pfont1 = 0;
    m_pfont2 = 0;
    m_pInvidoGfx = pGfx;
    m_ifocus_valuesM_A = 0;
    m_pLanString = 0;
    m_pMenuBox = 0;
    m_pScene_background = 0;
    m_bMouseInside = FALSE;
}

////////////////////////////////////////
//       ~cMenuMgr
/*! 
*/
cMenuMgr::~cMenuMgr()
{
    if (m_pMenuBox)
    {
        SDL_FreeSurface(m_pMenuBox);
        m_pMenuBox = NULL;
    }
    delete m_phomeUrl;
    delete m_pLabelVersion;
}


////////////////////////////////////////
//       Init
/*! Initilialize stuff
*/
void cMenuMgr::Init(SDL_Surface *pScreen, SDL_Renderer* pRenderer)
{
    CHAR ErrBuff[Error::BUFDIM];
    m_pScreen = pScreen;
	m_psdlRenderer = pRenderer;

    m_iSx = m_pScreen->clip_rect.w;
	m_iDebx = m_iSx / 6;
	m_iSy = m_pScreen->clip_rect.h;
	m_iDeby = m_iSy / 5;

    m_rctPanel.w = m_iSx - m_iDebx*2;
    m_rctPanel.h = m_iSy - m_iDeby*2;
    m_rctPanel.x = m_iDebx;
    m_rctPanel.y = m_iDeby;

    m_pfont1 = m_pApp->GetFontAriblk(); 
    m_pfont2 = m_pApp->GetFontVera(); 
    m_pLanString = m_pApp->GetLanguageMan();
    
    m_pMenuBox = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctPanel.w, m_rctPanel.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pMenuBox, NULL, SDL_MapRGBA(m_pScreen->format, 255, 0, 0, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 127); // SDL 1.2
	SDL_SetSurfaceBlendMode(m_pMenuBox, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceAlphaMod(m_pMenuBox, 127); //SDL 2.0

    // link to invido.it
    m_pfont3 = TTF_OpenFont(lpszIniFontVera, 11);
    if (m_pfont3 == 0)
    {
        sprintf(ErrBuff, "Unable to load font %s, error: %s\n", lpszIniFontVera , SDL_GetError());
        throw Error::Init(ErrBuff);
    }
    TTF_SetFontStyle(m_pfont3, TTF_STYLE_UNDERLINE);
    SDL_Rect rctBt1;
    rctBt1.h = 28;
    rctBt1.w = 150;
    rctBt1.y = m_pScreen->h -  rctBt1.h  - 20;
    rctBt1.x = m_pScreen->w -  rctBt1.w  - 20;
    m_phomeUrl = new cLabelLinkGfx;
    m_phomeUrl->m_fncbClickEvent = MakeDelegate(this, &cMenuMgr::LabelClicked);
    m_phomeUrl->Init(&rctBt1, m_pScreen,  m_pfont3, MYIDLABELURL, m_psdlRenderer); 
    m_phomeUrl->SetState(cLabelLinkGfx::INVISIBLE);
    m_phomeUrl->SetUrl(lpszUrlHome); 
    m_phomeUrl->SetWindowText(lpszMsgUrl);


    // label version
    m_pLabelVersion = new cLabelGfx;
    rctBt1.h = 28;
    rctBt1.w = 150;
    rctBt1.y = m_phomeUrl->m_rctButt.y - 20;
    rctBt1.x = m_phomeUrl->m_rctButt.x;
    m_pLabelVersion->m_fncbClickEvent = MakeDelegate(this, &cMenuMgr::LabelClicked);
    m_pLabelVersion->Init(&rctBt1, m_pScreen,  m_pfont2, MYIDLABELVER, m_psdlRenderer); 
    m_pLabelVersion->SetState(cLabelGfx::INVISIBLE);
    m_pLabelVersion->SetWindowText(lpszVersion);
    
}

////////////////////////////////////////
//       LabelClicked
/*! 
*/
void cMenuMgr::LabelClicked(int iButID)
{

}


////////////////////////////////////////
//       drawStaticSpriteEx
/*! 
// \param int src_x : 
// \param int src_y : 
// \param int src_dx : 
// \param int src_dy : 
// \param int dst_x : 
// \param int dst_y : 
// \param SDL_Surface* sprite : 
*/
void cMenuMgr::drawStaticSpriteEx(int src_x, int src_y, int src_dx, int src_dy, 
                                  int dst_x, int dst_y, SDL_Surface* sprite) 
{
	SDL_Rect src_rec = {src_x, src_y, src_dx, src_dy};
	SDL_Rect dst_rec = {dst_x, dst_y, 0, 0};
	SDL_BlitSurface(sprite, &src_rec, m_pScreen, &dst_rec);
}

void cMenuMgr::drawRect(int x, int y, int dx, int dy, SDL_Color c) 
{
	drawStaticLine(x, y, dx, y, c);
	drawStaticLine(x, y, x, dy, c);
	drawStaticLine(dx, y, dx, dy, c);
	drawStaticLine(x, dy, dx, dy, c);
}

void cMenuMgr::drawStaticLine(int x0, int y0, int x1, int y1, SDL_Color color) 
{
	int d = (int)sqrtf(
		pow((float)(x1 - x0), 2.0f) +
		pow((float)(y1 - y0), 2.0f)
	);
	static int x = 0, y = 0;
	static int w = m_pScreen->w;
	static int h = m_pScreen->h;
	for(int t = 0; t < d; t++) 
    {
		x = x0 + (x1 - x0)*t/d;
		y = y0 + (y1 - y0)*t/d;
		if((x >= 0) && (y >= 0) && (x < w) && (y < h)) 
        {
            setPixel(m_pScreen, x, y, color);
		}
	}
}

void cMenuMgr::setPixel ( SDL_Surface* pSurface , int x , int y , SDL_Color color ) 
{
    //convert color
    Uint32 col = SDL_MapRGB ( pSurface->format , color.r , color.g , color.b ) ;

    //determine position
    char* pPosition = ( char* ) pSurface->pixels ;

    //offset by y
    pPosition += ( pSurface->pitch * y ) ;

    //offset by x
    pPosition += ( pSurface->format->BytesPerPixel * x ) ;

    //copy pixel data
    memcpy ( pPosition , &col , pSurface->format->BytesPerPixel ) ;
}

void cMenuMgr::fillRect(int x0, int y0, int width, int height, Uint32 color) 
{
	SDL_Rect rect = { x0, y0, width, height };
	SDL_FillRect(m_pScreen, &rect, color);
}

////////////////////////////////////////
//       drawBackground
/*! Draw menu background
*/
void cMenuMgr::drawBackground()
{
    SDL_BlitSurface(m_pScene_background, NULL, m_pScreen, NULL); 

	m_iSx = m_pScreen->clip_rect.w;
	m_iDebx = m_iSx / 6;
	m_iSy = m_pScreen->clip_rect.h;
	m_iDeby = m_iSy / 5;

	Uint32 c_bluefg = SDL_MapRGB(m_pScreen->format, 51, 72, 133);
	Uint32 c_redfg = SDL_MapRGB(m_pScreen->format, 153, 202, 51);
	
    // don't invert, because content overwrite header
    // content
    GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, m_rctPanel.w, m_rctPanel.h, m_rctPanel.x, m_rctPanel.y, m_pMenuBox);

    // header bar
    fillRect(m_iDebx, m_iDeby-2, m_iSx - m_iDebx*2, 38, c_redfg);
    
	
    drawRect(m_iDebx-1, m_iDeby-1, m_iSx - m_iDebx + 1, m_iSy - m_iDeby + 1, staColor_gray);
	drawRect(m_iDebx-2, m_iDeby-2, m_iSx - m_iDebx + 2, m_iSy - m_iDeby + 2, staColor_black);
	drawRect(m_iDebx, m_iDeby, m_iSx - m_iDebx, m_iSy - m_iDeby, staColor_white);
	drawRect(m_iDebx, m_iDeby, m_iSx - m_iDebx, m_iDeby + 36, staColor_white);
}


////////////////////////////////////////
//       drawStringSH
/*! 
*/
void cMenuMgr::drawStringSH(const char* tmp, int x, int y, SDL_Color& color, TTF_Font* customfont)
{
    int tx, ty;
	TTF_SizeText(customfont, tmp, &tx, &ty);
	SDL_Surface* s = TTF_RenderText_Blended(customfont, tmp, staColor_ombre);
	drawStaticSpriteEx(0, 0, tx, ty, x+2, y+2, s);
	SDL_FreeSurface(s);
	s = TTF_RenderText_Blended(customfont, tmp, color);
	drawStaticSpriteEx(0, 0, tx, ty, x, y, s);
	SDL_FreeSurface(s);
}


////////////////////////////////////////
//       HandleRootMenu
/*! This is the first menu 0.1
*/
void   cMenuMgr::HandleRootMenu()
{
    // show the link url label 
    m_phomeUrl->SetState(cLabelLinkGfx::VISIBLE); 
    m_pLabelVersion->SetState(cLabelGfx::VISIBLE); 

    SDL_Color c = staColor_white;
	drawBackground();
    int iNumItemInMenu = 4;
	
	// Draw title bar
	drawStringSH(m_pLanString->GetStringId(cLanguages::ID_WELCOMETITLEBAR).c_str(), 
                 m_iDebx+10, m_iDeby+5, c, m_pfont1);
	
	// Play
	if (m_ifocus_valuesM_A != 0)
    {
        c = staColor_off; 
    }
    else 
    {
        c = staColor_on;
    }
	drawStringSH(m_pLanString->GetStringId(cLanguages::ID_START).c_str(),
                 m_iDebx+10, m_iDeby+50, c, m_pfont1);
	// Options
	if (m_ifocus_valuesM_A != 1) 	
    {
        c = staColor_off; 
    }
    else 
    {
        c = staColor_on;
    }
	drawStringSH( m_pLanString->GetStringId(cLanguages::ID_MEN_OPTIONS).c_str(),
                  m_iDebx+10, m_iDeby+90, c, m_pfont1);
	// Credits
	if (m_ifocus_valuesM_A != 2)
    {
        c = staColor_off;
    }
    else 
    {
        c = staColor_on;
    }
	drawStringSH(m_pLanString->GetStringId(cLanguages::ID_CREDITS).c_str(),
                 m_iDebx+10, m_iDeby+130, c, m_pfont1);

    // Help
    if (m_ifocus_valuesM_A != 3)
    {
        c = staColor_off;
    }
    else 
    {
        c = staColor_on;
    }
	drawStringSH(m_pLanString->GetStringId(cLanguages::ID_MN_HELP).c_str(),
                 m_iDebx+10, m_iDeby+170, c, m_pfont1);

	// Quit
	if (m_ifocus_valuesM_A != 4) 	
    {
        c = staColor_off;
    }
    else 
    {
        c = staColor_on;
    }
	drawStringSH( m_pLanString->GetStringId(cLanguages::ID_EXIT).c_str(),
                  m_iDebx+10, m_iSy-m_iDeby-40, c, m_pfont1);
	
    SDL_Event event;
	while (SDL_PollEvent(&event)) 
    {
		if(event.type == SDL_QUIT) 
        {
            m_pApp->LeaveMenu(); 
            break;
        }

		if(event.type == SDL_KEYDOWN) 
        {			
			if(event.key.keysym.sym == SDLK_UP) 
            {
				m_ifocus_valuesM_A--;
				if(m_ifocus_valuesM_A < 0) 
                {
                    m_ifocus_valuesM_A = 0;
                }
			}			
			if(event.key.keysym.sym == SDLK_DOWN) 
            {
				m_ifocus_valuesM_A++;
				if(m_ifocus_valuesM_A > iNumItemInMenu) 
                {
                    m_ifocus_valuesM_A = iNumItemInMenu;
                }
			}
			if(event.key.keysym.sym == SDLK_RETURN) 
            {
				rootMenuNext();
			}
			if (event.key.keysym.sym == SDLK_ESCAPE ) 
            {
				m_pApp->LeaveMenu(); 
            }
		}
        if (event.type == SDL_MOUSEMOTION)
        {
            if ( event.motion.x >= m_rctPanel.x && event.motion.x <=  m_rctPanel.x + m_rctPanel.h &&
                 event.motion.y >= m_rctPanel.y && event.motion.y <= m_rctPanel.y + m_rctPanel.h)
            {
                // mouse is inner to the box 
                if ( event.motion.y >= m_iDeby+90 && event.motion.y < m_iDeby+130 )
                {
                    m_ifocus_valuesM_A = 1;
                }
                else if ( event.motion.y >= m_iDeby+130 && event.motion.y < m_iDeby+170 )
                {
                    m_ifocus_valuesM_A = 2;
                }
                else if ( event.motion.y < m_iDeby+90)
                {
                    m_ifocus_valuesM_A = 0;
                }
                else if ( event.motion.y >= m_iDeby+170 && event.motion.y < m_iDeby+230 )
                {
                    m_ifocus_valuesM_A = 3;
                }
                else if ( event.motion.y >= m_iSy-m_iDeby-40)
                {
                    m_ifocus_valuesM_A = 4;
                }
                m_bMouseInside = TRUE;
            }
            else
            {
                // mouse outside, no focus
                m_bMouseInside = FALSE;
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (m_bMouseInside)
            {
                rootMenuNext();
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            m_phomeUrl->MouseUp(event);
        }
	}
    // draw url label
    m_phomeUrl->Draw(m_pScreen);
    // draw label version
    m_pLabelVersion->Draw(m_pScreen);
}


////////////////////////////////////////
//       rootMenuNext
/*! Next menu after root
*/
void   cMenuMgr::rootMenuNext()
{

    switch(m_ifocus_valuesM_A) 
    {
	    case 0 :			// Play
		    m_pApp->SetNextMenu(MENU_GAME); 
            break;
	    case 1 :		 	// Options
		    m_pApp->SetNextMenu(MENU_OPTIONS);
            break;
        case 2 :		 	// Credits
		    m_pApp->SetNextMenu(MENU_CREDITS);
            break;
        case 3 :		 	// Help
		    m_pApp->SetNextMenu(MENU_HELP);
            break;
	    case 4 :			// Quit
		    m_pApp->LeaveMenu(); 
            break;
    }
}