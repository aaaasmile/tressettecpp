
// cBalloonGfx.cpp: implementation of the cBalloonGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cBalloonGfx.h"
#include "gfx_util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cBalloonGfx::cBalloonGfx()
{
    m_uiInitTick = 0;
    m_pImageBall = 0;
    m_bEnabled = FALSE;
    m_uiShowTick = 0;
    m_pFontText = 0;
    m_pImageArrow = 0;
    m_alphaVal = -1;
}

cBalloonGfx::~cBalloonGfx()
{

}

////////////////////////////////////////
//       Init
/*! Init control
// \param SDL_Rect& rct :
// \param SDL_Surface* pImage :
*/
void cBalloonGfx::Init(SDL_Rect& rct, SDL_Surface* pImage, TTF_Font* pFont, int alphaVal)
{
    ASSERT(pImage);
    m_destWIN = rct;
    m_pImageBall = pImage;
    m_alphaVal = alphaVal;

    //SDL_SetAlpha(m_pImageBall, SDL_SRCALPHA, 80);
    SDL_SetSurfaceBlendMode(m_pImageBall, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pImageBall, alphaVal);

    m_colCurrent = GFX_UTIL_COLOR::Black;
    m_pFontText = pFont;
}


////////////////////////////////////////
//       SetStyle
/*! Set the ballon style
// \param eStyle eVal : new style
// \param SDL_Surface* pImage : arrow image
*/
void cBalloonGfx::SetStyle(eStyle eVal, SDL_Surface* pImage)
{
    ASSERT(m_alphaVal != -1);
    m_pImageArrow = pImage;
    //SDL_SetAlpha(m_pImageArrow, SDL_SRCALPHA, 80);
    SDL_SetSurfaceBlendMode(m_pImageArrow, SDL_BLENDMODE_BLEND); //SDL 2.0
    SDL_SetSurfaceAlphaMod(m_pImageArrow, m_alphaVal);
    m_eStyle = eVal;

    int iXbody_middle = (m_destWIN.x + m_destWIN.w / 2);

    m_ArrWIN.w = pImage->w;
    m_ArrWIN.h = pImage->h;
    if (m_eStyle == ARROW_DWN_LEFT ||
        m_eStyle == ARROW_DWN_RIGHT)
    {
        m_ArrWIN.x = iXbody_middle - m_pImageArrow->w / 2;
        m_ArrWIN.y = m_destWIN.y + m_destWIN.h;
    }
    else if (m_eStyle == ARROW_UP)
    {
        m_ArrWIN.x = iXbody_middle - m_pImageArrow->w / 2;
        m_ArrWIN.y = m_destWIN.y - m_pImageArrow->h;
    }
}


////////////////////////////////////////
//       Draw
/*! Draw the ballon
// \param SDL_Surface* pScreen :
*/
void cBalloonGfx::Draw(SDL_Surface* pScreen)
{
    if (m_bEnabled)
    {
        Uint32 uiNowTime = SDL_GetTicks();
        if ((uiNowTime - m_uiInitTick) < m_uiShowTick)
        {
            int tx, ty;
            TTF_SizeText(m_pFontText, m_strText.c_str(), &tx, &ty);
            int iXOffSet = (m_destWIN.w - tx) / 2;
            if (iXOffSet < 0)
            {
                iXOffSet = 1;
            }
            int iYOffset = (m_destWIN.h - ty) / 2 - 10;

            // draw body
            SDL_BlitSurface(m_pImageBall, NULL, pScreen, &m_destWIN);
            // draw arrow
            SDL_BlitSurface(m_pImageArrow, NULL, pScreen, &m_ArrWIN);

            // text
            GFX_UTIL::DrawString(pScreen, m_strText.c_str(), m_destWIN.x + iXOffSet,
                m_destWIN.y + iYOffset, m_colCurrent, m_pFontText, false);

            if (m_strText2.length() > 0)
            {
                GFX_UTIL::DrawString(pScreen, m_strText2.c_str(), m_destWIN.x + iXOffSet,
                    m_destWIN.y + 2 * iYOffset + 10, m_colCurrent, m_pFontText, false);
            }
        }
        else
        {
            // time exceed
            m_bEnabled = FALSE;
        }
    }
}



////////////////////////////////////////
//       StartShow
/*! Start to show the control
// \param LPCSTR lpszText :
*/
void cBalloonGfx::StartShow(LPCSTR lpszText)
{
    startshow(lpszText, 2500);
}

////////////////////////////////////////
//       StartShow
/*!
// \param LPCSTR lpszText :
// \param Uint32 uiTick :
*/
void cBalloonGfx::StartShow(LPCSTR lpszText, Uint32 uiTick)
{
    startshow(lpszText, uiTick);
}


////////////////////////////////////////
//       startshow
/*!
// \param LPCSTR lpszText :
// \param Uint32 uiTick :
*/
void cBalloonGfx::startshow(LPCSTR lpszText, Uint32 uiTick)
{
    m_strText2 = "";
    m_bEnabled = TRUE;
    m_uiInitTick = SDL_GetTicks();
    m_uiShowTick = uiTick;
    m_strText = lpszText;
    if (m_strText.length() > 12)
    {
        // line too long split it in two
        int iPosSpace = (int)m_strText.find_first_of(' ');
        int iLenText = (int)m_strText.length();
        STRING strL1 = m_strText.substr(0, iPosSpace);
        STRING strL2 = m_strText.substr(iPosSpace + 1, iLenText - iPosSpace);
        m_strText = strL1;
        m_strText2 = strL2;
    }
}

////////////////////////////////////////
//       Disable
/*! Disable ballon
*/
void cBalloonGfx::Disable()
{
    Uint32 uiNowTime = SDL_GetTicks();
    // make sure that the ballon was shown for a garanted time
    if ((uiNowTime - m_uiInitTick) > m_uiShowTick)
    {
        m_bEnabled = FALSE;
    }
}
