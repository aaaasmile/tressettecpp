//gfx_util.cpp

#include "StdAfx.h"
#include "win_type_global.h"
#include "gfx_util.h"
#include <math.h>


SDL_Color GFX_UTIL_COLOR::White = { 255, 255, 255, 0 };
SDL_Color GFX_UTIL_COLOR::Gray = { 128, 128, 128, 0 };
SDL_Color GFX_UTIL_COLOR::Red = { 255, 0, 0, 0 };
SDL_Color GFX_UTIL_COLOR::Green = { 0, 255, 0, 0 };
SDL_Color GFX_UTIL_COLOR::Black = { 0, 0, 0, 0 };
SDL_Color GFX_UTIL_COLOR::Orange = { 255, 200, 0, 0 };
SDL_Color GFX_UTIL_COLOR::Blue = { 0, 0, 255, 0 };


/**********************************************************************************************
	SET TRANSLUCENCY FOR AN AREA
********************************************************************************************/
void GFX_UTIL::ScreenShade(SDL_Surface *surface, SDL_Rect *rect, float opacity, unsigned char r1, unsigned char g1, unsigned char b1)
{
	Uint32 pixel;
	Uint8 r, g, b;
	bool bunlock = false;
	if (surface == NULL)
		return;
	if (SDL_LockSurface(surface) == 0)
		bunlock = true;
	//SET TRANSPARENCY FOR THE BOARD AREA
	for (int y = rect->y; y < rect->y + rect->h; y++)
		for (int x = rect->x; x < rect->x + rect->w; x++)
		{
			pixel = GetPixel(surface, x, y);
			SDL_GetRGB(pixel, surface->format, &r, &g, &b);
			r = (Uint8)((float)r*opacity);
			g = (Uint8)((float)g*opacity);
			b = (Uint8)((float)b*opacity);
			SetPixel(surface, x, y, SDL_MapRGBA(surface->format, r, g, b, 255));
		}
	if (bunlock == true)
		SDL_UnlockSurface(surface);
	rectangleRGBA(surface, rect->x, rect->y, rect->x + rect->w, rect->y + rect->h, 0, 0, 0, 255);
	rectangleRGBA(surface, rect->x + 1, rect->y + 1, rect->x + rect->w - 2, rect->y + rect->h - 2, r1, g1, b1, 255);

}

/** ********************************************************************************************
	SHAKE THE SCREEN FOR THE SPECIFIED TIME PERIOD
********************************************************************************************/
void GFX_UTIL::ScreenShake(SDL_Surface *screen, int val, int time, int delay, SDL_Renderer* psdlRenderer)
{
	// TODO: basta togliere il primo livello di commenti e poi continuare
	//SDL_Texture *backup; //SDL 2.0
	//SDL_Rect rectimg, rectfill;

	////backup = SDL_DisplayFormat(screen); //SDL 1.2
	////SDL_BlitSurface(screen, &screen->clip_rect, backup, &backup->clip_rect);
	//backup = SDL_CreateTextureFromSurface(psdlRenderer, screen); //SDL 2.0

	//rectimg.x = rectfill.x = 0;
	//rectimg.w = rectfill.w = screen->w;
	//rectimg.h = screen->h - val;

	//rectfill.h = val;
	//for (int k = 0; k < time; k++)
	//{
	//	rectimg.y = val*-1;
	//	rectfill.y = screen->h - val;
	//	//SDL_BlitSurface(backup, &backup->clip_rect, screen, &rectimg); //SDL 1.2
	//	SDL_RenderCopy(psdlRenderer, backup, backup->cl, &rectimg); //SDL 2.0 // TODO clip_rect???

	//	SDL_FillRect(screen, &rectfill, SDL_MapRGB(screen->format, 0, 0, 0));
	//	//SDL_Flip(screen);//SDL 1.2
	//	SDL_UpdateTexture(backup, NULL, screen->pixels, screen->pitch); //SDL 2.0
	//	SDL_RenderCopy(psdlRenderer, backup, NULL, NULL);
	//	SDL_RenderPresent(psdlRenderer);

	//	SDL_Delay(delay);

	//	rectimg.y = val;
	//	rectfill.y = 0;
	//	SDL_BlitSurface(backup, &backup->clip_rect, screen, &rectimg);
	//	SDL_FillRect(screen, &rectfill, SDL_MapRGB(screen->format, 0, 0, 0));
	//	SDL_Flip(screen);
	//	SDL_Delay(delay);
	//}
	////SDL_BlitSurface(backup, &backup->clip_rect, screen, &screen->clip_rect);
	////SDL_Flip(screen);
	//SDL_UpdateTexture(backup, NULL, screen->pixels, screen->pitch); //SDL 2.0
	//SDL_RenderCopy(psdlRenderer, backup, NULL, NULL);
	//SDL_RenderPresent(psdlRenderer);
	//

	////SDL_FreeSurface(backup); //SDL 1.2
	//SDL_DestroyTexture(backup); //SDL 2.0
}


/** ********************************************************************************************
	DRAW A NON-FILLED BOX (RGBA)
********************************************************************************************/
void GFX_UTIL::rectangleRGBA(SDL_Surface *screen, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	int x, y;
	Uint32 color;
	bool bneedunlock = false;
	if (screen == NULL)
		return;
	if (SDL_LockSurface(screen) == 0)
		bneedunlock = true;

	color = SDL_MapRGBA(screen->format, r, g, b, a);

	for (x = x1; x < x2; x++)
	{
		SetPixel(screen, x, y1, color);
		SetPixel(screen, x, y2 - 1, color);
	}

	for (y = y1; y < y2; y++)
	{
		SetPixel(screen, x1, y, color);
		SetPixel(screen, x2 - 1, y, color);
	}
	if (bneedunlock == true)
		SDL_UnlockSurface(screen);

}
/** ********************************************************************************************
	DRAW A FILLED BOX (RGBA)
********************************************************************************************/
void GFX_UTIL::boxRGBA(SDL_Surface *screen, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	int x, y;
	Uint32 color;
	bool bneedunlock = false;
	if (screen == NULL)
		return;

	if (SDL_LockSurface(screen) == 0)
		bneedunlock = true;

	color = SDL_MapRGBA(screen->format, r, g, b, a);

	for (y = y1; y < y2; y++)
	{
		for (x = x1; x < x2; x++)
		{
			SetPixel(screen, x, y, color);
		}
	}
	if (bneedunlock == true)
		SDL_UnlockSurface(screen);

}


////////////////////////////////////////
//       GetPixel
/*!
// \param SDL_Surface *surface :
// \param int x :
// \param int y :
*/
Uint32 inline GFX_UTIL::GetPixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *)p;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

////////////////////////////////////////
//       SetPixel
/*!
// \param SDL_Surface *surface :
// \param int x :
// \param int y :
// \param Uint32 pixel :
*/
void inline GFX_UTIL::SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

void GFX_UTIL::DrawString(SDL_Surface *screen, const char* strText, int x, int y,
	SDL_Color color, TTF_Font* customfont, bool isUtf8)
{
	int tx, ty;
	TTF_SizeText(customfont, strText, &tx, &ty);
    SDL_Surface* surFont;
    if (isUtf8) {
        surFont = TTF_RenderUTF8_Blended(customfont, strText, color);
    }
    else {
        surFont = TTF_RenderText_Blended(customfont, strText, color);
    }
	GFX_UTIL::DrawStaticSpriteEx(screen, 0, 0, tx, ty, x, y, surFont);
	SDL_FreeSurface(surFont);
}

void GFX_UTIL::DrawStaticSpriteEx(SDL_Surface *screen, int src_x, int src_y, int src_dx, int src_dy,
	int dst_x, int dst_y, SDL_Surface* sprite)
{
	SDL_Rect src_rec = { src_x, src_y, src_dx, src_dy };
	SDL_Rect dst_rec = { dst_x, dst_y, 0, 0 };
	SDL_BlitSurface(sprite, &src_rec, screen, &dst_rec);
}

void GFX_UTIL::DrawStaticLine(SDL_Surface *screen, int x0, int y0, int x1, int y1,
	SDL_Color color)
{
	int d = (int)sqrtf(
		pow((float)(x1 - x0), 2.0f) +
		pow((float)(y1 - y0), 2.0f)
	);
	static int x = 0, y = 0;
	static int w = screen->w;
	static int h = screen->h;
	for (int t = 0; t < d; t++)
	{
		x = x0 + (x1 - x0)*t / d;
		y = y0 + (y1 - y0)*t / d;
		if ((x >= 0) && (y >= 0) && (x < w) && (y < h))
		{
			GFX_UTIL::SetPixel(screen, x, y, SDL_MapRGBA(screen->format, color.r, color.g, color.b, 255));
		}
	}
}


void GFX_UTIL::DrawRect(SDL_Surface *screen, int x, int y, int dx, int dy, SDL_Color color)
{
	DrawStaticLine(screen, x, y, dx, y, color);
	DrawStaticLine(screen, x, y, x, dy, color);
	DrawStaticLine(screen, dx, y, dx, dy, color);
	DrawStaticLine(screen, x, dy, dx, dy, color);
}


void GFX_UTIL::DrawStaticBrokenLine(SDL_Surface *screen, int x0, int y0, int x1, int y1,
	const SDL_Color *color1, const SDL_Color *color2, int break_size)
{

}

///////////////////////////// Namespace STR_UTIL


////////////////////////////////////////
//       intToString
/*!
// \param int iNumber :
*/
std::string STR_UTIL::intToString(int iNumber)
{
	std::string temp;
	char buffer[64];
	sprintf(buffer, "%d", iNumber);
	temp = buffer;
	return temp;

}
