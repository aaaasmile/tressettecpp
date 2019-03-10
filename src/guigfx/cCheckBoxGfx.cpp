// cCheckBoxGfx.cpp: implementation of the cCheckBoxGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cCheckBoxGfx.h"
#include "gfx_util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cCheckBoxGfx::cCheckBoxGfx()
{
    m_eState = INVISIBLE;
    m_pFontText = 0;
    m_bIsEnabled = TRUE;
    m_iButID = -1;
    m_bNoSkin = TRUE;

}

cCheckBoxGfx::~cCheckBoxGfx()
{
}



////////////////////////////////////////
//       Init
/*!
// \param SDL_Rect* pRect :
// \param SDL_Surface*  pScreen :
// \param TTF_Font* pFont :
// \param int iButID :
*/
void  cCheckBoxGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID)
{

    m_rctButt = *pRect;

    m_pFontText = pFont;

    m_colCurrent = GFX_UTIL_COLOR::White;
    m_colBorder = m_colCurrent;



    m_bClickState = FALSE;

    m_iButID = iButID;

}



////////////////////////////////////////
//       SetState
/*!
// \param eSate eVal :
*/
void   cCheckBoxGfx::SetState(eSate eVal)
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
//       MouseMove
/*!
// \param SDL_Event &event :
// \param SDL_Surface* pScreen :
// \param SDL_Surface* pScene_background :
*/
void   cCheckBoxGfx::MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background)
{

}


////////////////////////////////////////
//       MouseUp
/*!
// \param SDL_Event &event :
*/
void   cCheckBoxGfx::MouseUp(SDL_Event &event)
{
    if (m_eState == VISIBLE && m_bIsEnabled)
    {
        if (event.motion.x >= m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
            event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            if (m_bClickState)
            {
                m_bClickState = FALSE;
            }
            else
            {
                m_bClickState = TRUE;
            }
            // mouse go up inner the control
            m_fncbClickEvent(m_iButID);

        }
    }
}



////////////////////////////////////////
//       DrawButton
/*!
// \param SDL_Surface*  pScreen :
*/
void   cCheckBoxGfx::DrawButton(SDL_Surface*  pScreen)
{
    if (m_eState != INVISIBLE)
    {
        if (m_bIsEnabled)
        {

            int iXOffSet = 0;
            int iYOffset = 0;

            // draw the checkbox
            if (m_bClickState)
            {

                // checked
                if (m_bNoSkin)
                {
                    SDL_Rect rctCheck;
                    rctCheck.x = m_rctButt.x;
                    rctCheck.y = m_rctButt.y;
                    rctCheck.w = CHECK_W;
                    rctCheck.h = CHECK_H;

                    // border
                    GFX_UTIL::DrawRect(pScreen, rctCheck.x - 1, rctCheck.y - 1, rctCheck.x + rctCheck.w + 1,
                        rctCheck.y + rctCheck.h + 1, GFX_UTIL_COLOR::Gray);
                    GFX_UTIL::DrawRect(pScreen, rctCheck.x - 2, rctCheck.y - 2, rctCheck.x + rctCheck.w + 2,
                        rctCheck.y + rctCheck.h + 2, GFX_UTIL_COLOR::Black);
                    /*
                    GFX_UTIL::DrawRect(pScreen, rctCheck.x, rctCheck.y, rctCheck.x +  rctCheck.w,
                                        rctCheck.y + rctCheck.h , m_colBorder);
                                        */
                                        // x
                    GFX_UTIL::DrawStaticLine(pScreen, rctCheck.x, rctCheck.y, rctCheck.x + rctCheck.w,
                        rctCheck.y + rctCheck.h, GFX_UTIL_COLOR::Orange);
                    GFX_UTIL::DrawStaticLine(pScreen, rctCheck.x + rctCheck.w, rctCheck.y, rctCheck.x,
                        rctCheck.y + rctCheck.h, GFX_UTIL_COLOR::Orange);

                    iXOffSet = rctCheck.w + 10;
                    iYOffset = rctCheck.h;
                }
                else
                {
                    ASSERT(0); // don't support skin
                }
            }
            else
            {
                // unchecked
                if (m_bNoSkin)
                {
                    SDL_Rect rctCheck;
                    rctCheck.x = m_rctButt.x;
                    rctCheck.y = m_rctButt.y;
                    rctCheck.w = CHECK_W;
                    rctCheck.h = CHECK_H;

                    // border
                    GFX_UTIL::DrawRect(pScreen, rctCheck.x - 1, rctCheck.y - 1, rctCheck.x + rctCheck.w + 1,
                        rctCheck.y + rctCheck.h + 1, GFX_UTIL_COLOR::Gray);
                    GFX_UTIL::DrawRect(pScreen, rctCheck.x - 2, rctCheck.y - 2, rctCheck.x + rctCheck.w + 2,
                        rctCheck.y + rctCheck.h + 2, GFX_UTIL_COLOR::Black);
                    /*
                    GFX_UTIL::DrawRect(pScreen, rctCheck.x, rctCheck.y, rctCheck.x +  rctCheck.w,
                                        rctCheck.y + rctCheck.h , m_colBorder);
                                        */

                    iXOffSet = rctCheck.w + 10;
                    iYOffset = rctCheck.h;

                }
                else
                {
                    ASSERT(0); // don't support skin
                }

            }

            int tx, ty;
            TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);

            if (iXOffSet < 0)
            {
                iXOffSet = 1;
            }
            //int iYOffset = (m_rctButt.h - ty)/2 ;
            GFX_UTIL::DrawString(pScreen, m_strButText.c_str(), m_rctButt.x + iXOffSet,
                m_rctButt.y + iYOffset - ty, m_colCurrent, m_pFontText, false);



            //ASSERT(m_strButText != "-");
        }
        else
        {
            // button disabled 
            // TO DO
        }
    }
}

////////////////////////////////////////
//       RedrawButton
/*! Redraw the button
// \param SDL_Surface* pScreen :
// \param SDL_Surface* pScene_background :
*/
void   cCheckBoxGfx::RedrawButton(SDL_Surface* pScreen, SDL_Surface* pScene_background)
{
    if (pScene_background)
    {
        SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt);
    }
    DrawButton(pScreen);
    //SDL_Flip(pScreen);
}
