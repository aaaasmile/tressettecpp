

// EnterNameGfx.cpp: implementation of the EnterNameGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EnterNameGfx.h"
#include "cButtonGfx.h"
#include "gfx_util.h"
#include "cCheckBoxGfx.h"
#include "cEditGfx.h"
#include "cComboGfx.h"
#include "InvidoSettings.h"
#include "AppGfx.h"
#include "Languages.h"
#include "cMusicManager.h"
#include "cInvidoCoreEnv.h"
#include "InvidoInfoComm.h"

extern AppGfx* g_MainApp;

static const char* stalpszUSER = "USER";
static const char* stalpszCPUDEFAULT = "CPU_DEFAULT";
static const char* stalpszPluginDir = "./plugin/";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       EnterNameGfx
/*!
*/
EnterNameGfx::EnterNameGfx()
{
    m_pScreen = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_pBtOK = 0;
    m_bTerminated = FALSE;
    m_pEditName = 0;
}


////////////////////////////////////////
//       ~EnterNameGfx
/*!
*/
EnterNameGfx::~EnterNameGfx()
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    delete m_pBtOK;
    delete m_pEditName;
}



////////////////////////////////////////
//       Init
/*!
// \param SDL_Rect* pRect :
// \param SDL_Surface*  pScreen :
// \param TTF_Font* pFont :
*/
void EnterNameGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl, SDL_Renderer* psdlRenderer)
{
    ASSERT(pRect);
    ASSERT(pScreen && m_pFontCtrl);
    m_rctOptBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFontTxt;
    m_pFontCtrl = pFontWinCtrl;
    m_psdlRenderer = psdlRenderer;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctOptBox.w, m_rctOptBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 10, 100, 10, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 200); //SDL 1.2
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 200); // SDL 2.0

    SDL_Rect rctBt1;
    int iSpace2bt = 20;

    // button ok
    m_pBtOK = new cButtonGfx;
    m_pBtOK->m_fncbClickEvent = MakeDelegate(this, &EnterNameGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = (m_rctOptBox.w - rctBt1.w) / 2 + m_rctOptBox.x;
    m_pBtOK->Init(&rctBt1, pScreen, m_pFontText, MYIDOK, psdlRenderer);
    m_pBtOK->SetState(cButtonGfx::INVISIBLE);

    // edit name 
    m_pEditName = new cEditGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pBtOK->m_rctButt.y - rctBt1.h - 30;
    rctBt1.x = (m_rctOptBox.w - rctBt1.w) / 2 + m_rctOptBox.x;
    m_pEditName->Init(&rctBt1, pScreen, m_pFontText, MYEDITNAME, psdlRenderer);
    m_pEditName->SetState(cEditGfx::INVISIBLE);
}


////////////////////////////////////////
//       Show
/*! Shows the option window
// \param SDL_Surface* pScene_background :
*/
void EnterNameGfx::Show(SDL_Surface* pScene_background)
{
    int iRes = 0;
    m_bTerminated = FALSE;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    int FPS = 3;

    cLanguages* pLan = g_MainApp->GetLanguageMan();

    // prepare strings on controls
    STRING strTextBt;
    strTextBt = pLan->GetStringId(cLanguages::ID_OK);
    m_pBtOK->SetWindowText(strTextBt.c_str());
    m_pBtOK->SetState(cButtonGfx::VISIBLE);



    // Edit name
    strTextBt = g_Options.All.strPlayerName;
    STRING strNameTitle = pLan->GetStringId(cLanguages::ID_NAME);
    m_pEditName->SetWindowText(strTextBt.c_str());
    m_pEditName->SetState(cEditGfx::VISIBLE);
    m_pEditName->GetFocus();

    // create a shadow surface
    SDL_Surface* pShadowSrf = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
    SDL_Texture* pScreenTexture = SDL_CreateTextureFromSurface(m_psdlRenderer, pShadowSrf);

    while (!m_bTerminated)
    {
        // background
        SDL_BlitSurface(pScene_background, NULL, pShadowSrf, NULL);

        // wait until the user click on button
        SDL_Event event;
        BOOLEAN bExitPool = FALSE;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
            case SDL_QUIT:
                m_bTerminated = TRUE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    // confirm the dialog
                    ButCmdClicked(MYIDOK);
                    bExitPool = TRUE;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    // escape character
                    ButCmdClicked(MYIDCANCEL);
                    bExitPool = TRUE;
                }
                else
                {
                    m_pEditName->KeyDown(event);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                m_pBtOK->MouseUp(event);
                m_pEditName->MouseUp(event);
                if (m_pEditName->GetState() == cEditGfx::VISIBLE)
                {
                    // control lost the focus
                    // force the focus on edit control because is the only one
                    m_pEditName->GetFocus();
                }
                break;

            case SDL_TEXTINPUT:
                m_pEditName->TextInput(event);
                break;
            }
            if (m_bTerminated || bExitPool) {
                break;
            }
            // SDL 1.2
            //if (event.type == SDL_QUIT)
            //{
            //	m_bTerminated = TRUE;
            //	break;
            //}
            //if (event.type == SDL_KEYDOWN)
            //{
            //	if (event.key.keysym.sym == SDLK_RETURN)
            //	{
            //		// confirm the dialog
            //		ButCmdClicked(MYIDOK);
            //		break;
            //	}
            //	else if (event.key.keysym.sym == SDLK_ESCAPE)
            //	{
            //		// escape character
            //		ButCmdClicked(MYIDCANCEL);
            //		break;

            //	}
            //	else
            //	{
            //		// submitt the key on the child controls
            //		m_pEditName->KeyDown(event);
            //	}
            //}
            //if (event.type == SDL_MOUSEMOTION)
            //{

            //}
            //if (event.type == SDL_MOUSEBUTTONUP)
            //{
            //	m_pBtOK->MouseUp(event);
            //	m_pEditName->MouseUp(event);
            //	if (m_pEditName->GetState() == cEditGfx::VISIBLE)
            //	{
            //		// control lost the focus
            //		// force the focus on edit control because is the only one
            //		m_pEditName->GetFocus();
            //	}
            //}
        }

        // the msg box
        GFX_UTIL::DrawStaticSpriteEx(pShadowSrf, 0, 0, m_rctOptBox.w, m_rctOptBox.h, m_rctOptBox.x,
            m_rctOptBox.y, m_pSurf_Bar);
        // draw border
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x - 1, m_rctOptBox.y - 1, m_rctOptBox.x + m_rctOptBox.w + 1,
            m_rctOptBox.y + m_rctOptBox.h + 1, GFX_UTIL_COLOR::Gray);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x - 2, m_rctOptBox.y - 2, m_rctOptBox.x + m_rctOptBox.w + 2,
            m_rctOptBox.y + m_rctOptBox.h + 2, GFX_UTIL_COLOR::Black);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x, m_rctOptBox.y, m_rctOptBox.x + m_rctOptBox.w,
            m_rctOptBox.y + m_rctOptBox.h, m_colCurrent);

        //header bar
        SDL_Rect  rectHeader;
        Uint32 colorHeader = SDL_MapRGB(m_pScreen->format, 153, 202, 51);
        rectHeader.x = m_rctOptBox.x + 1;
        rectHeader.y = m_rctOptBox.y + 1;
        rectHeader.h = 30;
        rectHeader.w = m_rctOptBox.w - 1;
        SDL_FillRect(pShadowSrf, &rectHeader, colorHeader);
        GFX_UTIL::DrawStaticLine(pShadowSrf, rectHeader.x, rectHeader.y + rectHeader.h,
            rectHeader.x + rectHeader.w, rectHeader.y + rectHeader.h, GFX_UTIL_COLOR::White);
        // text header
        GFX_UTIL::DrawString(pShadowSrf, m_strHeaderText.c_str(), rectHeader.x + 10,
            rectHeader.y, GFX_UTIL_COLOR::White, m_pFontCtrl, false);


        // draw buttons
        m_pBtOK->DrawButton(pShadowSrf);


        // name label
        GFX_UTIL::DrawString(pShadowSrf, strNameTitle.c_str(), m_pEditName->m_rctButt.x,
            m_pEditName->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange, m_pFontText, false);

        // draw edit name control
        m_pEditName->DrawControl(pShadowSrf);

        //render the dialogbox
        SDL_BlitSurface(pShadowSrf, NULL, m_pScreen, NULL);
        //SDL_Flip(m_pScreen); // SDL 1.2
        SDL_UpdateTexture(pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch);
        SDL_RenderCopy(m_psdlRenderer, pScreenTexture, NULL, NULL);
        SDL_RenderPresent(m_psdlRenderer);

        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();
        if (uiNowTime < uiLast_time + FPS)
        {
            SDL_Delay(uiLast_time + FPS - uiNowTime);
            uiLast_time = uiNowTime;
        }
    }
    SDL_FreeSurface(pShadowSrf);
    SDL_DestroyTexture(pScreenTexture);
}



////////////////////////////////////////
//       ButCmdClicked
/*! button click callback
// \param int iButID :
*/
void   EnterNameGfx::ButCmdClicked(int iButID)
{
    if (!m_bTerminated)
    {
        m_bTerminated = TRUE;
        m_iResult = iButID;
        if (iButID == MYIDOK)
        {
            // the user has pressed the button OK

            // update all properties
            g_Options.All.strPlayerName = m_pEditName->GetWindowText();
        }
    }
}


