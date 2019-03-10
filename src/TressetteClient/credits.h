// credits.h

#ifndef __CREDITS_H
#define __CREDITS_H



//! class cCredits
class cCredits
{
	enum eTypeFont
	{
		EASY,
		MAIN
	};
public:
	cCredits(TTF_Font* pFont);
	int Show(SDL_Surface* screen,SDL_Surface *pSurfTitle, SDL_Renderer* psdlRenderer);

private:
	void draw_text(char * str, int offset, SDL_Surface* screen);

	void draw_textFontM(char * str, int offset, SDL_Surface* screen);

private:
	//! current line in scrolling
	int               m_iLine;
	//! font used
    TTF_Font*         m_pMainFont;
	//! type of font
	eTypeFont         m_eFontType;
    //! text color
    //! current text color
    SDL_Color         m_colCurrent;
};


#endif
