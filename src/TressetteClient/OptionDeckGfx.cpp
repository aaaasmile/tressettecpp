// OptionDeckGfx.cpp: implementation of the OptionDeckGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OptionDeckGfx.h"
#include "cButtonGfx.h"
#include "gfx_util.h"
#include "cComboGfx.h"
#include "cSettings.h"
#include "EngineApp.h"
#include "lang_gen.h"
#include "CoreEnv.h"
#include "InfoComm.h"
#include "ErrorMsg.h"

#include <SDL_image.h>
#include <SDL_endian.h>


extern cEngineApp* g_MainApp;

static const char* lpszMazziDir = "data/mazzi/";


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       OptionDeckGfx
/*!
*/
OptionDeckGfx::OptionDeckGfx()
{
    m_pScreen = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_pBtOK = 0;
    m_pBtCancel = 0;
    m_bTerminated = FALSE;
    m_pComboDeck = 0;
    for (int i = 0; i < cTipoDiMazzo::NUM_OF_MAZZI; i++)
    {
        m_pDeckAll[i] = 0;
    }
}


////////////////////////////////////////
//       ~OptionDeckGfx
/*!
*/
OptionDeckGfx::~OptionDeckGfx()
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    delete m_pBtOK;
    delete m_pBtCancel;
    delete m_pComboDeck;

    for (int i = 0; i < cTipoDiMazzo::NUM_OF_MAZZI; i++)
    {
        if (m_pDeckAll[i])
        {
            SDL_FreeSurface(m_pDeckAll[i]);
        }
    }

}



////////////////////////////////////////
//       Init
/*!
// \param SDL_Rect* pRect :
// \param SDL_Surface*  pScreen :
// \param TTF_Font* pFont :
*/
void OptionDeckGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl, SDL_Renderer* pRenderer)
{
    ASSERT(pRect);
    ASSERT(pScreen && pFontWinCtrl);
    m_rctOptBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFontTxt;
    m_pFontCtrl = pFontWinCtrl;
    m_pDeckType = new cTipoDiMazzo();
    m_psdlRenderer = pRenderer;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctOptBox.w, m_rctOptBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 10, 100, 10, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 200);
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 200); //SDL 2.0

    SDL_Rect rctBt1;
    int iSpace2bt = 20;

    // button ok
    m_pBtOK = new cButtonGfx;
    m_pBtOK->m_fncbClickEvent = MakeDelegate(this, &OptionDeckGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = (m_rctOptBox.w - rctBt1.w) / 2 + m_rctOptBox.x - rctBt1.w - iSpace2bt;
    m_pBtOK->Init(&rctBt1, pScreen, m_pFontText, MYIDOK, pRenderer);
    m_pBtOK->SetState(cButtonGfx::INVISIBLE);


    // button cancel
    m_pBtCancel = new cButtonGfx;
    m_pBtCancel->m_fncbClickEvent = MakeDelegate(this, &OptionDeckGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = (m_rctOptBox.w - rctBt1.w) / 2 + m_rctOptBox.x + rctBt1.w + iSpace2bt;
    m_pBtCancel->Init(&rctBt1, pScreen, m_pFontText, MYIDCANCEL, pRenderer);
    m_pBtCancel->SetState(cButtonGfx::INVISIBLE);

    // combo deck selection
    m_pComboDeck = new cComboGfx;
    m_pComboDeck->m_fncbClickEvent = MakeDelegate(this, &OptionDeckGfx::ComboCmdClicked);
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_rctOptBox.y + 80;
    rctBt1.x = (m_rctOptBox.x + m_rctOptBox.w - rctBt1.w) / 2;
    m_pComboDeck->Init(&rctBt1, pScreen, m_pFontText, MYIDCOMBODECK, pRenderer);
    m_pComboDeck->SetState(cComboGfx::INVISIBLE);

    // init deck surface
    for (int i = 0; i < cTipoDiMazzo::NUM_OF_MAZZI; i++)
    {
        loadCardPac((cTipoDiMazzo::eTypeMazzo) i, &m_pDeckAll[i], &m_CardOnEachDeck[0][i]);
        // the surface of the card 0 is already set in function loadCardPac
        m_CardOnEachDeck[0][i].m_iX = rctBt1.x;
        m_CardOnEachDeck[0][i].m_iY = rctBt1.y + rctBt1.h + 50;
        m_CardOnEachDeck[0][i].cardSpec.SetCardIndex(9);

        m_CardOnEachDeck[1][i].SetDeckSurface(m_pDeckAll[i], m_CardOnEachDeck[0][i].m_iWidth, m_CardOnEachDeck[0][i].m_iHeight);
        m_CardOnEachDeck[1][i].m_iX = m_CardOnEachDeck[0][i].m_iX + 10 + m_CardOnEachDeck[0][i].m_iWidth;
        m_CardOnEachDeck[1][i].m_iY = rctBt1.y + rctBt1.h + 50;
        m_CardOnEachDeck[1][i].cardSpec.SetCardIndex(7);

        m_CardOnEachDeck[2][i].SetDeckSurface(m_pDeckAll[i], m_CardOnEachDeck[0][i].m_iWidth, m_CardOnEachDeck[0][i].m_iHeight);
        m_CardOnEachDeck[2][i].m_iX = m_CardOnEachDeck[1][i].m_iX + 10 + m_CardOnEachDeck[1][i].m_iWidth;
        m_CardOnEachDeck[2][i].m_iY = rctBt1.y + rctBt1.h + 50;
        m_CardOnEachDeck[2][i].cardSpec.SetCardIndex(5);
    }
}


////////////////////////////////////////
//       loadCardPac
/*!
// \param cTipoDiMazzo::eTypeMazzo eType :
// \param SDL_Surface* surf_DestDeck :
*/
void  OptionDeckGfx::loadCardPac(cTipoDiMazzo::eTypeMazzo eType, SDL_Surface** ppsurf_DestDeck, cCardGfx* pCard)
{
    Uint32          timetag;
    char            describtion[100];
    Uint8           num_anims;
    Uint16          w, h;
    Uint16          frames;
    Uint16        *delays;

    ASSERT(pCard);
    ASSERT(ppsurf_DestDeck);
    int FRAMETICKS = (1000 / (1000 / 30));
    int THINKINGS_PER_TICK = 1;

    std::string strFileName = lpszMazziDir;
    m_pDeckType->SetType(eType);
    strFileName += m_pDeckType->GetResFileName();

    SDL_RWops *src = SDL_RWFromFile(strFileName.c_str(), "rb");
    if (src == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Error on load deck file %s", strFileName.c_str());
        throw Error::Init(ErrBuff);
    }
    SDL_RWread(src, describtion, 100, 1);
    timetag = SDL_ReadLE32(src);
    SDL_RWread(src, &num_anims, 1, 1);
    // witdh of the picture (pac of 4 cards)
    w = SDL_ReadLE16(src);
    // height of the picture (pac of 10 rows of cards)
    h = SDL_ReadLE16(src);
    frames = SDL_ReadLE16(src);

    delays = (Uint16*)malloc(sizeof(Uint16)*frames);
    if (!delays)
        return;

    for (int i = 0; i < frames; i++)
    {
        // file format stores delays in 1/100th of second
        // we will convert them to game ticks
        delays[i] = THINKINGS_PER_TICK*((10 * SDL_ReadLE16(src)) / FRAMETICKS);
    }

    SDL_Surface *s = IMG_LoadPNG_RW(src);
    SDL_SetColorKey(s, TRUE, SDL_MapRGB(s->format, 0, 128, 0)); // SDL 2.0

    *ppsurf_DestDeck = s;

    pCard->SetDeckSurface(s, w / 4, h / 10);

}

////////////////////////////////////////
//       Show
/*! Shows the option window
// \param SDL_Surface* pScene_background :
*/
void OptionDeckGfx::Show(SDL_Surface* pScene_background)
{
    int iRes = 0;
    m_bTerminated = FALSE;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    int FPS = 3;

    cLanguages* pLan = g_MainApp->GetLanguageMan();

    // prepare strings on controls

    // button ok
    STRING strTextBt;
    strTextBt = pLan->GetStringId(cLanguages::ID_OK);
    m_pBtOK->SetWindowText(strTextBt.c_str());
    m_pBtOK->SetState(cButtonGfx::VISIBLE);

    // button cancel
    strTextBt = pLan->GetStringId(cLanguages::ID_CANCEL);
    m_pBtCancel->SetWindowText(strTextBt.c_str());
    m_pBtCancel->SetState(cButtonGfx::VISIBLE);


    // combobox deck selection
    STRING strDeckSelectTitle = pLan->GetStringId(cLanguages::ID_CHOOSEMAZZO);
    for (int i = 0; i < cTipoDiMazzo::NUM_OF_MAZZI; i++)
    {
        strTextBt = m_pDeckType->GetMazzoNameOnType((cTipoDiMazzo::eTypeMazzo) i);
        m_pComboDeck->AddLineText(strTextBt.c_str());
    }

    m_pComboDeck->SetState(cComboGfx::VISIBLE);
    m_pComboDeck->SelectIndex(g_Options.All.iTipoMazzo);


    // create a shadow surface
    SDL_Surface* pShadowSrf = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
    SDL_Texture* pScreenTexture = SDL_CreateTextureFromSurface(m_psdlRenderer, pShadowSrf); //SDL 2.0
    while (!m_bTerminated)
    {
        // background
        SDL_BlitSurface(pScene_background, NULL, pShadowSrf, NULL);

        // wait until the user click on button
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_bTerminated = TRUE;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    // confirm the dialog
                    ButCmdClicked(MYIDOK);
                    break;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    // escape character
                    ButCmdClicked(MYIDCANCEL);
                    break;

                }

            }
            if (event.type == SDL_MOUSEMOTION)
            {

            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                m_pBtCancel->MouseUp(event);
                m_pBtOK->MouseUp(event);
                m_pComboDeck->MouseUp(event);
            }
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
        m_pBtCancel->DrawButton(pShadowSrf);


        // deck selection label
        GFX_UTIL::DrawString(pShadowSrf, strDeckSelectTitle.c_str(), m_pComboDeck->m_rctButt.x,
            m_pComboDeck->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange, m_pFontText, false);

        // draw the deck combobox selection
        m_pComboDeck->DrawButton(pShadowSrf);

        // draw card
        int iCurrIndex = m_pComboDeck->GetSlectedIndex();
        m_CardOnEachDeck[0][iCurrIndex].DrawCard(pShadowSrf);
        m_CardOnEachDeck[1][iCurrIndex].DrawCard(pShadowSrf);
        m_CardOnEachDeck[2][iCurrIndex].DrawCard(pShadowSrf);


        //render the dialogbox
        SDL_BlitSurface(pShadowSrf, NULL, m_pScreen, NULL);
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
void   OptionDeckGfx::ButCmdClicked(int iButID)
{
    if (!m_bTerminated)
    {
        m_bTerminated = TRUE;
        m_iResult = iButID;
        if (iButID == MYIDOK)
        {
            // the user has pressed the button OK

            // update deck property
            g_Options.All.iTipoMazzo = m_pComboDeck->GetSlectedIndex();

        }
    }
}

////////////////////////////////////////
//       ComboCmdClicked
/*! Combobox callback
// \param int iButID :
*/
void   OptionDeckGfx::ComboCmdClicked(int iButID)
{

}

