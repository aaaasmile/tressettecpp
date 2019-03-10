
//cMesgBoxGfx.cpp

#include "StdAfx.h"
#include "cMesgBoxGfx.h"
#include "gfx_util.h"
#include "cButtonGfx.h"


////////////////////////////////////////
//       cMesgBoxGfx
/*!
*/
cMesgBoxGfx::cMesgBoxGfx(void)
{
    m_pScreen = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_pBtButt1 = 0;
    m_pBtButt2 = 0;
    m_bTerminated = FALSE;
}


////////////////////////////////////////
//       ~cMesgBoxGfx
/*!
*/
cMesgBoxGfx::~cMesgBoxGfx(void)
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    delete m_pBtButt1;
    delete m_pBtButt2;
}


////////////////////////////////////////
//       Init
/*! Init the message box
// \param SDL_Rect* pRect : rect of the message box
// \param SDL_Surface*  pScreen : main screen
// \param TTF_Font* pFont : font of the message
// \param eMSGBOX_TYPE eval : type of the message box
*/
void cMesgBoxGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, eMSGBOX_TYPE eval, SDL_Renderer* pRenderer)
{
    ASSERT(pRect);
    ASSERT(pScreen && pFont);
    m_rctMsgBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFont;
    m_eTypeMsg = eval;
    m_psdlRenderer = pRenderer;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctMsgBox.w, m_rctMsgBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 30, 80, 157, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 70); //SDL 1.2
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 70); // SDL 2.0

    m_colCurrent = GFX_UTIL_COLOR::White;
    SDL_Rect rctBt1;

    if (m_eTypeMsg == MB_YES_NO)
    {
        int iSpace2bt = 20;
        // button yes
        m_pBtButt1 = new cButtonGfx;
        rctBt1.w = 120;
        rctBt1.h = 28;
        rctBt1.y = m_rctMsgBox.y + m_rctMsgBox.h - 10 - rctBt1.h;
        rctBt1.x = (m_rctMsgBox.w - (2 * rctBt1.w + iSpace2bt)) / 2 + m_rctMsgBox.x;
        m_pBtButt1->Init(&rctBt1, pScreen, pFont, MB_ID_BUTT_YES, pRenderer);
        m_pBtButt1->SetState(cButtonGfx::INVISIBLE);
        m_pBtButt1->m_fncbClickEvent = MakeDelegate(this, &cMesgBoxGfx::ButCmdClicked);

        // button no
        m_pBtButt2 = new cButtonGfx;
        rctBt1.w = 120;
        rctBt1.h = 28;
        rctBt1.y = m_pBtButt1->m_rctButt.y;
        rctBt1.x = m_pBtButt1->m_rctButt.x + m_pBtButt1->m_rctButt.w + iSpace2bt;
        m_pBtButt2->Init(&rctBt1, pScreen, pFont, MB_ID_BUTT_NO, pRenderer);
        m_pBtButt2->SetState(cButtonGfx::INVISIBLE);
        m_pBtButt2->m_fncbClickEvent = MakeDelegate(this, &cMesgBoxGfx::ButCmdClicked);

    }
    else if (m_eTypeMsg == MBOK)
    {
        m_pBtButt1 = new cButtonGfx;
        rctBt1.w = 120;
        rctBt1.h = 28;
        rctBt1.y = m_rctMsgBox.y + m_rctMsgBox.h - 10 - rctBt1.h;
        rctBt1.x = (m_rctMsgBox.w - rctBt1.w) / 2 + m_rctMsgBox.x;
        m_pBtButt1->Init(&rctBt1, pScreen, pFont, 0, pRenderer);
        m_pBtButt1->SetState(cButtonGfx::INVISIBLE);
        m_pBtButt1->m_fncbClickEvent = MakeDelegate(this, &cMesgBoxGfx::ButCmdClicked);
    }
    else
    {
        ASSERT(0);
    }

}

////////////////////////////////////////
//       ButCmdClicked
/*! button click callback
// \param int iButID :
*/
void cMesgBoxGfx::ButCmdClicked(int iButID)
{
    if (!m_bTerminated)
    {
        m_bTerminated = TRUE;
        if (m_eTypeMsg == MB_YES_NO)
        {
            if (MB_ID_BUTT_YES == iButID)
            {
                // user click on yes
                m_iResult = MB_RES_YES;
            }
            else if (MB_ID_BUTT_NO == iButID)
            {
                // user click on no
                m_iResult = MB_RES_NO;
            }
        }
        else
        {
            m_iResult = iButID;
        }
    }
}


////////////////////////////////////////
//       Show
/*! Show the message box
// \param SDL_Surface* pScene_background :
*/
int  cMesgBoxGfx::Show(SDL_Surface* pScene_background, LPCSTR lpsBut1_txt, LPCSTR lpsBut2_txt, LPCSTR lpsMsg_txt)
{
    m_iResult = MB_RES_YES;
    m_bTerminated = FALSE;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    int FPS = 3;

    m_strMsgText = lpsMsg_txt;
    if (m_pBtButt1)
    {
        m_pBtButt1->SetWindowText(lpsBut1_txt);
        m_pBtButt1->SetState(cButtonGfx::VISIBLE);
    }
    if (m_eTypeMsg == MB_YES_NO)
    {
        m_pBtButt2->SetWindowText(lpsBut2_txt);
        m_pBtButt2->SetState(cButtonGfx::VISIBLE);
    }
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
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    // key on focus
                    if (m_eTypeMsg == MB_YES_NO)
                    {
                        // default key is yes
                        ButCmdClicked(MB_ID_BUTT_YES);
                    }
                    else
                    {
                        ButCmdClicked(0);
                    }
                    break;
                }
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                // Not needed because mouse recognition is done on draw button

            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (m_pBtButt1)
                {
                    m_pBtButt1->MouseUp(event);
                }
                if (m_pBtButt2)
                {
                    m_pBtButt2->MouseUp(event);
                }
            }
        }
        // the msg box
        GFX_UTIL::DrawStaticSpriteEx(pShadowSrf, 0, 0, m_rctMsgBox.w, m_rctMsgBox.h, m_rctMsgBox.x, m_rctMsgBox.y, m_pSurf_Bar);

        // draw the text
        int tx, ty;
        int iXOffSet;
        int iYOffset;
        if (m_vctDataStrings.size() > 0)
        {
            int iYinitial = 10;
            int iEmptySpaceOn_Y = 4;
            // draw the text
            for (UINT i = 0; i < m_vctDataStrings.size(); i++)
            {
                STRING strText = m_vctDataStrings[i];
                TTF_SizeText(m_pFontText, strText.c_str(), &tx, &ty);

                iXOffSet = (m_rctMsgBox.w - tx) / 2;
                iYOffset = i*ty + iEmptySpaceOn_Y + iYinitial;

                GFX_UTIL::DrawString(pShadowSrf, strText.c_str(), m_rctMsgBox.x + iXOffSet,
                    m_rctMsgBox.y + iYOffset, m_colCurrent, m_pFontText, false);
            }
        }
        else
        {
            // draw only a line in the middle
            TTF_SizeText(m_pFontText, m_strMsgText.c_str(), &tx, &ty);
            iXOffSet = (m_rctMsgBox.w - tx) / 2;
            if (iXOffSet < 0)
            {
                iXOffSet = 1;
            }
            iYOffset = (m_rctMsgBox.h - ty) / 2;
            GFX_UTIL::DrawString(pShadowSrf, m_strMsgText.c_str(), m_rctMsgBox.x + iXOffSet,
                m_rctMsgBox.y + iYOffset, m_colCurrent, m_pFontText, false);
        }


        // draw border
        GFX_UTIL::DrawRect(pShadowSrf, m_rctMsgBox.x - 1, m_rctMsgBox.y - 1, m_rctMsgBox.x + m_rctMsgBox.w + 1,
            m_rctMsgBox.y + m_rctMsgBox.h + 1, GFX_UTIL_COLOR::Gray);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctMsgBox.x - 2, m_rctMsgBox.y - 2, m_rctMsgBox.x + m_rctMsgBox.w + 2,
            m_rctMsgBox.y + m_rctMsgBox.h + 2, GFX_UTIL_COLOR::Black);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctMsgBox.x, m_rctMsgBox.y, m_rctMsgBox.x + m_rctMsgBox.w,
            m_rctMsgBox.y + m_rctMsgBox.h, m_colCurrent);


        // draw buttons
        if (m_pBtButt1)
        {
            m_pBtButt1->DrawButton(pShadowSrf);
        }
        if (m_eTypeMsg == MB_YES_NO)
        {
            m_pBtButt2->DrawButton(pShadowSrf);
        }

        SDL_BlitSurface(pShadowSrf, NULL, m_pScreen, NULL);
        //SDL_Flip(m_pScreen); //SDL 1.2
        SDL_UpdateTexture(pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); //SDL 2.0
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
    SDL_DestroyTexture(pScreenTexture); //SDL 2.0

    return m_iResult;
}



