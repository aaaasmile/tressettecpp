//gfx_util.h

#ifndef __GFX_UTIL__H
#define __GFX_UTIL__H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

namespace  GFX_UTIL
{
	///READ PIXEL FROM A SURFACE
	Uint32 inline GetPixel(SDL_Surface *surface, int x, int y);
	///WRITE PIXEL TO A SURFACE
	void inline   SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

    void DrawString(SDL_Surface * screen, const char * strText, int x, int y, SDL_Color color, TTF_Font * customfont, bool isUtf8);

	///DRAW A NON-FILLED BOX (RGBA)
	void rectangleRGBA(SDL_Surface *screen,int x,int y,int x2,int y2,unsigned char r,unsigned char g,unsigned char b,unsigned char a);
	///DRAW A FILLED BOX (RGBA)
	void boxRGBA(SDL_Surface *screen,int x1,int y1,int x2,int y2,unsigned char r,unsigned char g,unsigned char b,unsigned char a);

	///SET TRANSLUCENCY FOR AN AREA
	void ScreenShade(SDL_Surface *surface, SDL_Rect *rect, float opacity, unsigned char r, unsigned char g,unsigned char b);
	///SHAKE THE SCREEN FOR THE SPECIFIED TIME PERIOD
	void ScreenShake(SDL_Surface *screen,int val, int time,int delay, SDL_Renderer* psdlRenderer);
    //! draw a sprite
    void DrawStaticSpriteEx(SDL_Surface *screen, int src_x, int src_y, int src_dx, int src_dy, int dst_x, int dst_y, SDL_Surface* sprite);
    //! draw a line
    void DrawStaticLine(SDL_Surface *screen, int x0, int y0, int x1, int y1, SDL_Color color);
    //! draw a broken line
	void DrawStaticBrokenLine(SDL_Surface *screen, int x0, int y0, int x1, int y1, const SDL_Color *color1, const SDL_Color *color2, int break_size);	
    //! draw rectangle
    void DrawRect(SDL_Surface *screen,int x, int y, int dx, int dy, SDL_Color c) ;
};

//! class GFX_UTIL_COLOR
/** define colors constant
*/ 
class GFX_UTIL_COLOR
{
public:
    GFX_UTIL_COLOR(){}
    static SDL_Color White;
    static SDL_Color Gray;
    static SDL_Color Red;
    static SDL_Color Green;
    static SDL_Color Black;
    static SDL_Color Orange;
    static SDL_Color Blue;
};

//! namespace for std::string utility functions
namespace STR_UTIL
{
    //! convert a number to string
    std::string intToString(int iNumber);
};

#endif
