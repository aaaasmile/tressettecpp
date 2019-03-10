
// cLabelLinkGfx.cpp: implementation of the cLabelLinkGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cLabelLinkGfx.h"
#include "gfx_util.h"

#ifdef WIN32
#include "shellapi.h"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cLabelLinkGfx::cLabelLinkGfx()
{
	m_eState = INVISIBLE;
	m_pFontText = 0;
	m_iButID = 0;
	m_bIsEnabled = TRUE;
	m_pSurf_Bar = 0;
}

cLabelLinkGfx::~cLabelLinkGfx()
{
	if (m_pSurf_Bar)
	{
		SDL_FreeSurface(m_pSurf_Bar);
		m_pSurf_Bar = NULL;
	}
}




////////////////////////////////////////
//       Init
/*! Init the button
// \param SDL_Rect* pRect :
// \param SDL_Surface*  pScreen :
*/
void  cLabelLinkGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID, SDL_Renderer* psdlRenderer)
{
	m_rctButt = *pRect;
	m_psdlRenderer = psdlRenderer;

	// black bar surface
	m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctButt.w, m_rctButt.h, 32, 0, 0, 0, 0);
	SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 255, 0, 0, 0));
	//SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 127); //SDL 1.2
	SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 127); // SDL 2.0

	m_pFontText = pFont;

	m_colCurrent = GFX_UTIL_COLOR::White;
	m_iButID = iButID;

}


////////////////////////////////////////
//       SetState
/*!
// \param eSate eVal :
*/
void   cLabelLinkGfx::SetState(eSate eVal)
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
*/
void   cLabelLinkGfx::MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture)
{
	if (m_eState == VISIBLE && m_bIsEnabled)
	{
		if (event.motion.x >= m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
			event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
		{
			// mouse inner button
			m_colCurrent = GFX_UTIL_COLOR::Orange;
			Redraw(pScreen, pScene_background, pScreenTexture);
		}
		else
		{
			// mouse outside
			if (m_colCurrent.r == GFX_UTIL_COLOR::Orange.r &&
				m_colCurrent.g == GFX_UTIL_COLOR::Orange.g &&
				m_colCurrent.b == GFX_UTIL_COLOR::Orange.b)
			{
				// button was selected
				m_colCurrent = GFX_UTIL_COLOR::White;
				Redraw(pScreen, pScene_background, pScreenTexture);
			}
		}
	}
}


////////////////////////////////////////
//       MouseUp
/*! Mouse up event
// \param SDL_Event &event :
*/
void   cLabelLinkGfx::MouseUp(SDL_Event &event)
{
	if (m_eState == VISIBLE && m_bIsEnabled)
	{
		if (event.motion.x >= m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
			event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
		{
			// mouse go up inner the button
			// send a click event 
			m_fncbClickEvent(m_iButID);
			if (m_strUrl.length())
			{
#ifdef WIN32
				ShellExecute(0, "open", m_strUrl.c_str(), 0, 0, SW_SHOWNORMAL);
#endif
			}
		}
	}
}


////////////////////////////////////////
//       Draw
/*! Draw the label with text
// \param SDL_Surface*  pScreen :
*/
void   cLabelLinkGfx::Draw(SDL_Surface*  pScreen)
{
	if (m_eState != INVISIBLE)
	{
		if (m_bIsEnabled)
		{
			// begin stuff mouse
			Uint8 state;
			int mx, my;
			state = SDL_GetMouseState(&mx, &my);
			if (mx >= m_rctButt.x  && mx <= m_rctButt.x + m_rctButt.w &&
				my >= m_rctButt.y  && my <= m_rctButt.y + m_rctButt.h)
			{
				// mouse on button
				m_colCurrent = GFX_UTIL_COLOR::Orange;
			}
			else
			{
				m_colCurrent = GFX_UTIL_COLOR::White;
			}
			// end stuff mouse

			int tx, ty;
			TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);
			int iXOffSet = (m_rctButt.w - tx) / 2;
			if (iXOffSet < 0)
			{
				iXOffSet = 1;
			}
			int iYOffset = (m_rctButt.h - ty) / 2;

			iYOffset = 0;
			iXOffSet = 0;
			GFX_UTIL::DrawString(pScreen, m_strButText.c_str(), m_rctButt.x + iXOffSet,
				m_rctButt.y + iYOffset, m_colCurrent, m_pFontText, false);


		}
		else
		{
			// button disabled 
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
void cLabelLinkGfx::Redraw(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture)
{
	if (pScene_background)
	{
		//SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt); //SDL 1.2
		SDL_RenderCopy(m_psdlRenderer, pScene_background, &m_rctButt, &m_rctButt); //SDL 2.0
	}
	Draw(pScreen);
	//SDL_Flip(pScreen);
	// SDL 2.0
	SDL_UpdateTexture(pScreenTexture, NULL, pScreen->pixels, pScreen->pitch);
	SDL_RenderCopy(m_psdlRenderer, pScreenTexture, NULL, NULL);
	SDL_RenderPresent(m_psdlRenderer);
}
