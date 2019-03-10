
//cPopUpMenuGfx.cpp

#include "StdAfx.h"
#include "cPopUpMenuGfx.h"
#include "gfx_util.h"


////////////////////////////////////////
//       cPopUpMenuGfx
/*!
*/
cPopUpMenuGfx::cPopUpMenuGfx(void)
{
    m_pScreen = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_bTerminated = FALSE;
    m_iCurrDataIndex = 0;
    m_bMenuSelected = TRUE;
}


////////////////////////////////////////
//       ~cPopUpMenuGfx
/*!
*/
cPopUpMenuGfx::~cPopUpMenuGfx(void)
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }

}


////////////////////////////////////////
//       Init
/*! Init the message box
// \param SDL_Rect* pRect : rect of the message box
// \param SDL_Surface*  pScreen : main screen
// \param TTF_Font* pFont : font of the message
// \param eMSGBOX_TYPE eval : type of the message box
*/
void cPopUpMenuGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, SDL_Renderer* pRenderer)
{
    ASSERT(pRect);
    ASSERT(pScreen && pFont);
    m_rctMsgBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFont;
    m_psdlRenderer = pRenderer;

    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctMsgBox.w, m_rctMsgBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 40, 0, 0, 0));
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 125); // SDL 2.0

    m_colCurrent = GFX_UTIL_COLOR::White;
}

////////////////////////////////////////
//       Show
/*! Show the message box
// \param SDL_Surface* pScene_background :
*/
void  cPopUpMenuGfx::Show(SDL_Surface* pScene_background)
{
    if (m_vctDataStrings.size() == 0)
    {
        return;
    }

    m_bTerminated = FALSE;
    m_bMenuSelected = TRUE;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    int FPS = 3;

    // create a shadow surface
    SDL_Surface* pShadowSrf = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
    SDL_Texture* pScreenTexture = SDL_CreateTextureFromSurface(m_psdlRenderer, pShadowSrf); //SDL 2.0

    // search the max string len
    int iMaxIndex = 0;
    int iMaxLen = 0;
    for (UINT i = 0; i < m_vctDataStrings.size(); i++)
    {
        int iLenCurr = (int)m_vctDataStrings[i].length();
        if (iLenCurr > iMaxLen)
        {
            iMaxIndex = i;
            iMaxLen = iLenCurr;
        }
    }

    int iEmptySpaceOn_Y = 7;
    int tx, ty;
    TTF_SizeText(m_pFontText, m_vctDataStrings[iMaxIndex].c_str(), &tx, &ty);
    // resize control to best fit the text
    int iNew_W = tx + 5;
    int iNew_H = (int)((ty + iEmptySpaceOn_Y) * m_vctDataStrings.size() + iEmptySpaceOn_Y);

    if (iNew_W < 100)
        iNew_W = 100;

    m_rctMsgBox.w = iNew_W;
    m_rctMsgBox.h = iNew_H;

    // fit the box in the screen: change position if it is clipped
    if ((m_rctMsgBox.h + m_rctMsgBox.y) > m_pScreen->h)
    {
        m_rctMsgBox.y = m_pScreen->h - m_rctMsgBox.h - 5;
    }
    if ((m_rctMsgBox.w + m_rctMsgBox.y) > m_pScreen->w)
    {
        m_rctMsgBox.x = m_pScreen->w - m_rctMsgBox.w - 5;
    }

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
                    m_bTerminated = TRUE;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {

                    m_bTerminated = TRUE;
                    m_bMenuSelected = FALSE;

                }
            }
            if (event.type == SDL_MOUSEMOTION)
            {
                // move the current selection in the menu
                if (event.motion.x >= m_rctMsgBox.x && event.motion.x <= m_rctMsgBox.x + m_rctMsgBox.h &&
                    event.motion.y >= m_rctMsgBox.y && event.motion.y <= m_rctMsgBox.y + m_rctMsgBox.h)
                {
                    // mouse inside the menu
                    for (UINT i = 0; i < m_vctDataStrings.size(); i++)
                    {
                        if (event.motion.y >= (Sint32)((ty + iEmptySpaceOn_Y) * i + m_rctMsgBox.y) &&
                            event.motion.y <= (Sint32)(iEmptySpaceOn_Y + (ty + iEmptySpaceOn_Y) * (i + 1) + m_rctMsgBox.y))
                        {
                            // i is the selected index
                            m_iCurrDataIndex = i;
                            break;
                        }
                    }
                    m_bMenuSelected = TRUE;
                }
                else
                {
                    m_bMenuSelected = FALSE;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                m_bTerminated = TRUE;
            }
        }

        // the menu box
        GFX_UTIL::DrawStaticSpriteEx(pShadowSrf, 0, 0, m_rctMsgBox.w, m_rctMsgBox.h, m_rctMsgBox.x,
            m_rctMsgBox.y, m_pSurf_Bar);



        if (m_bMenuSelected)
        {
            //draw selected bar
            SDL_Rect  rectHeader;
            Uint32 colorHeader = SDL_MapRGB(m_pScreen->format, 255, 0, 0);
            rectHeader.x = m_rctMsgBox.x + 1;
            rectHeader.y = m_rctMsgBox.y + (ty + iEmptySpaceOn_Y) * m_iCurrDataIndex + iEmptySpaceOn_Y;
            rectHeader.h = ty;
            rectHeader.w = m_rctMsgBox.w - 1;
            SDL_FillRect(pShadowSrf, &rectHeader, colorHeader);
        }

        // draw the text
        for (UINT i = 0; i < m_vctDataStrings.size(); i++)
        {
            STRING strText = m_vctDataStrings[i];

            int iXOffSet = 5;
            int iYOffset = iEmptySpaceOn_Y + i*(ty + iEmptySpaceOn_Y);

            GFX_UTIL::DrawString(pShadowSrf, strText.c_str(), m_rctMsgBox.x + iXOffSet,
                m_rctMsgBox.y + iYOffset, m_colCurrent, m_pFontText, false);
        }

        // draw border
        GFX_UTIL::DrawRect(pShadowSrf, m_rctMsgBox.x - 1, m_rctMsgBox.y - 1, m_rctMsgBox.x + m_rctMsgBox.w + 1,
            m_rctMsgBox.y + m_rctMsgBox.h + 1, GFX_UTIL_COLOR::Gray);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctMsgBox.x - 2, m_rctMsgBox.y - 2, m_rctMsgBox.x + m_rctMsgBox.w + 2,
            m_rctMsgBox.y + m_rctMsgBox.h + 2, GFX_UTIL_COLOR::Black);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctMsgBox.x, m_rctMsgBox.y, m_rctMsgBox.x + m_rctMsgBox.w,
            m_rctMsgBox.y + m_rctMsgBox.h, m_colCurrent);

        SDL_BlitSurface(pShadowSrf, NULL, m_pScreen, NULL);
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
}

////////////////////////////////////////
//       AddLineText
/*!
// \param LPCSTR strLine :
*/
void   cPopUpMenuGfx::AddLineText(LPCSTR strLine)
{
    m_vctDataStrings.push_back(strLine);
}



