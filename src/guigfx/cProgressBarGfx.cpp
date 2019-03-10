// cProgressBarGfx.cpp: implementation of the cProgressBarGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cProgressBarGfx.h"
#include "gfx_util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cProgressBarGfx::cProgressBarGfx()
{
    m_eState = INVISIBLE;
    m_pFontText = 0;
    m_iButID = 0;
    m_bIsEnabled = TRUE;
    m_pSurf_Bar = 0;
    m_pImageCursor = 0;
    m_pSurf_BoxSel = 0;
    m_pSurf_BoxUNSel = 0;
    m_iLowRange = 0;
    m_iUpRange = 5;
    m_iNumOfStep = 6;
    m_iCurrLevel = 0;
    m_bOnDrag = FALSE;
}

cProgressBarGfx::~cProgressBarGfx()
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    if (m_pSurf_BoxSel)
    {
        SDL_FreeSurface(m_pSurf_BoxSel);
        m_pSurf_BoxSel = NULL;
    }
    if (m_pSurf_BoxUNSel)
    {
        SDL_FreeSurface(m_pSurf_BoxUNSel);
        m_pSurf_BoxUNSel = NULL;
    }
}

////////////////////////////////////////
//       Init
/*! Init the progressbar
// \param SDL_Rect* pRect : control dimension
// \param SDL_Surface*  pScreen : screen
// \param SDL_Surface*  pCursor : cursor image
*/
void  cProgressBarGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, SDL_Surface*  pCursor,
    TTF_Font* pFont, int iButID, SDL_Renderer* pRenderer)
{
    m_rctButt = *pRect;
    m_psdlRenderer = pRenderer;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctButt.w, m_rctButt.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 255, 0, 0, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 127); //SDL 1.2
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 127); // SDL 2.0
    m_pFontText = pFont;

    m_colCurrent = GFX_UTIL_COLOR::White;
    m_iButID = iButID;
    m_pImageCursor = pCursor;

    m_rctCursor.w = 15;
    m_rctCursor.h = 20;

    // selected surface cursor
    m_pSurf_BoxSel = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctCursor.w, m_rctCursor.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_BoxSel, NULL, SDL_MapRGBA(pScreen->format, 200, 200, 130, 0));
    //SDL_SetAlpha(m_pSurf_BoxSel, SDL_SRCALPHA, 127);//SDL 1.2
    SDL_SetSurfaceBlendMode(m_pSurf_BoxSel, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_BoxSel, 127);// SDL 2.0

    //unselected suface cursor
    m_pSurf_BoxUNSel = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctCursor.w, m_rctCursor.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_BoxUNSel, NULL, SDL_MapRGBA(pScreen->format, 255, 128, 30, 0));
    //SDL_SetAlpha(m_pSurf_BoxUNSel, SDL_SRCALPHA, 127);//SDL 1.2
    SDL_SetSurfaceBlendMode(m_pSurf_BoxUNSel, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_BoxUNSel, 127);// SDL 2.0

    m_bOnDrag = FALSE;

    m_strLabelBEG = "slow";
    m_strLabelEND = "fast";

}


////////////////////////////////////////
//       SetState
/*!
// \param eSate eVal :
*/
void   cProgressBarGfx::SetState(eSate eVal)
{
    eSate eOldState = m_eState;
    m_eState = eVal;
    if (eOldState != m_eState &&
        m_eState == VISIBLE)
    {
        m_colCurrent = GFX_UTIL_COLOR::White;
    }
}

////////////////////////////////////////
//       MouseUp
/*! Mouse up event
// \param SDL_Event &event :
*/
void   cProgressBarGfx::MouseUp(SDL_Event &event)
{
    if (m_eState == VISIBLE && m_bIsEnabled)
    {
        if (event.motion.x >= m_rctButt.x - m_rctCursor.w / 2 && event.motion.x <= m_rctButt.x + m_rctButt.w + m_rctCursor.w / 2 &&
            event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            if (m_bOnDrag)
            {
                // we are dragging the cursor
                int iXspace = (m_rctButt.x - m_rctButt.x + m_rctButt.w) / (m_iNumOfStep - 1);
                if (event.motion.x <= m_rctButt.x + iXspace / 2)
                {
                    m_iCurrLevel = 0;
                }
                else if (event.motion.x >= m_rctButt.x + m_rctButt.w - iXspace / 2)
                {
                    m_iCurrLevel = m_iNumOfStep - 1;
                }
                else
                {
                    for (int i = 1; i < m_iNumOfStep; i++)
                    {
                        int iXInf = m_rctButt.x + iXspace * i - iXspace / 2;
                        int iXSup = m_rctButt.x + iXspace * i + iXspace / 2;
                        if (event.motion.x >= iXInf &&
                            event.motion.x <= iXSup)
                        {
                            // level found
                            m_iCurrLevel = i;
                            break;
                        }

                    }
                }
                m_bOnDrag = FALSE;
            }
        }
        else
        {
            m_bOnDrag = FALSE;
        }
    }
}


////////////////////////////////////////
//       MouseDown
/*!
// \param SDL_Event &event :
*/
void   cProgressBarGfx::MouseDown(SDL_Event &event)
{
    if (m_eState == VISIBLE && m_bIsEnabled)
    {
        if (event.motion.x >= m_rctButt.x - m_rctCursor.w / 2 && event.motion.x <= m_rctButt.x + m_rctButt.w + m_rctCursor.w / 2 &&
            event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            m_bOnDrag = TRUE;
        }
    }
}


////////////////////////////////////////
//       DrawControl
/*! Draw the label with text
// \param SDL_Surface*  pScreen :
*/
void   cProgressBarGfx::DrawControl(SDL_Surface*  pScreen)
{
    ASSERT(m_iNumOfStep > 0);

    if (m_eState != INVISIBLE)
    {
        if (m_bIsEnabled)
        {

            // draw the horizontal base line
            int iX0 = m_rctButt.x;
            int iY0 = m_rctButt.y + (m_rctButt.h / 2);
            int iX1 = m_rctButt.x + m_rctButt.w;
            int iY1 = iY0;
            GFX_UTIL::DrawStaticLine(pScreen, iX0, iY0, iX1, iY1, GFX_UTIL_COLOR::Black);
            GFX_UTIL::DrawStaticLine(pScreen, iX0, iY0 - 1, iX1, iY1 - 1, GFX_UTIL_COLOR::Gray);
            // draw vertical marks
            int iYmarkoff = 3;
            int iXspace = (iX1 - iX0) / (m_iNumOfStep - 1);
            for (int i = 0; i < m_iNumOfStep; i++)
            {

                int iVX0 = i* iXspace + iX0;
                int iVY0 = iY0 - iYmarkoff;
                int iVX1 = iVX0;
                int iVY1 = iY0 + iYmarkoff;
                GFX_UTIL::DrawStaticLine(pScreen, iVX0, iVY0, iVX1, iVY1, GFX_UTIL_COLOR::Black);
                GFX_UTIL::DrawStaticLine(pScreen, iVX0 - 1, iVY0, iVX1 - 1, iVY1, GFX_UTIL_COLOR::Gray);
            }

            // draw labels

            // label on x0
            int tx, ty;
            int iXOffSet = 1;
            TTF_SizeText(m_pFontText, m_strLabelBEG.c_str(), &tx, &ty);
            int iYOffset = iYmarkoff + 1;
            GFX_UTIL::DrawString(pScreen, m_strLabelBEG.c_str(), iX0 + iXOffSet,
                iY0 + iYOffset, GFX_UTIL_COLOR::White, m_pFontText, false);

            // label on x1
            TTF_SizeText(m_pFontText, m_strLabelEND.c_str(), &tx, &ty);

            iXOffSet = iX1 - tx - iX0;
            GFX_UTIL::DrawString(pScreen, m_strLabelEND.c_str(), iX0 + iXOffSet,
                iY0 + iYOffset, GFX_UTIL_COLOR::White, m_pFontText, false);



            BOOL bUpBoxSel = FALSE;
            // draw the cursor
            if (m_iCurrLevel < 0)
            {
                m_iCurrLevel = 0;
            }
            else if (m_iCurrLevel >= m_iNumOfStep)
            {
                m_iCurrLevel = m_iNumOfStep - 1;
            }
            m_rctCursor.x = iX0 + m_iCurrLevel  * iXspace - m_rctCursor.w / 2;
            m_rctCursor.y = iY1 - m_rctCursor.h / 2;
            if (bUpBoxSel || m_bOnDrag)
            {
                GFX_UTIL::DrawStaticSpriteEx(pScreen, 0, 0, m_rctCursor.w, m_rctCursor.h, m_rctCursor.x,
                    m_rctCursor.y, m_pSurf_BoxSel);
            }
            else
            {
                // draw unselected cursor
                GFX_UTIL::DrawStaticSpriteEx(pScreen, 0, 0, m_rctCursor.w, m_rctCursor.h, m_rctCursor.x,
                    m_rctCursor.y, m_pSurf_BoxUNSel);
            }

            // draw the cursor border
            GFX_UTIL::DrawRect(pScreen, m_rctCursor.x, m_rctCursor.y,
                m_rctCursor.x + m_rctCursor.w, m_rctCursor.y + m_rctCursor.h, GFX_UTIL_COLOR::Black);

        }
        else
        {
            //  disabled 
            // TO DO
        }
    }
}



////////////////////////////////////////
//       Redraw
/*! Redraw the button
// \param SDL_Surface* pScreen :
// \param SDL_Surface* pScene_background :
*/
void   cProgressBarGfx::RedrawControl(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture)
{
    if (pScene_background)
    {
        //SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt); //SDL 1.2
        SDL_RenderCopy(m_psdlRenderer, pScene_background, &m_rctButt, &m_rctButt); //SDL 2.0
    }
    DrawControl(pScreen);
    //SDL_Flip(pScreen); //SDL 1.2
    SDL_UpdateTexture(pScreenTexture, NULL, pScreen->pixels, pScreen->pitch); //SDL 2.0
    SDL_RenderCopy(m_psdlRenderer, pScreenTexture, NULL, NULL);
    SDL_RenderPresent(m_psdlRenderer);
}



////////////////////////////////////////
//       GetCurrLevel
/*! Provides the level
*/
int  cProgressBarGfx::GetCurrLevel()
{
    int iValOffset = (m_iUpRange - m_iLowRange) / m_iNumOfStep;
    if (iValOffset < 1)
    {
        iValOffset = 1;
    }

    int iValFin = m_iCurrLevel * iValOffset + m_iLowRange;

    return iValFin;
}
