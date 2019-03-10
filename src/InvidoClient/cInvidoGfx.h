

// cInvidoGfx.h

#ifndef __CINVIDO_GFX_H
#define __CINVIDO_GFX_H


#include <map>
#include <SDL_ttf.h>
#include "cInvidoCore.h"
#include "cCardGfx.h"
#include "AlgPlayerInterface.h"


//! region id to draw cards
enum 
{
    CRD_MAZZOALTRECARTE = 0,
    CRD_PLAYER1,            
    CRD_PLAYER2,            
    CRD_TAVOLO_1,           
    CRD_TAVOLO_2,           
    CRD_MAZZO_PLAYER1,      
    CRD_MAZZO_PLAYER2,          
};

//! drag cards information
struct DRAGCARD
{
	int x;
	int y;
	int width;
	int height;
};

// card sybols
const unsigned int CRD_NSYMBOL	=	0;
const unsigned int CRD_XSYMBOL	=	1;
const unsigned int CRD_OSYMBOL	=	2;
const unsigned int CRD_HSYMBOL	=	3;

class AppGfx;
class cInvidoCore;
class cTipoDiMazzo;
class cButtonGfx;
class cBalloonGfx;
class cLanguages;
class cMusicManager;

typedef std::map<eGiocataScoreState, STRING> MAP_SCORE;
typedef std::map<eSayPlayer, STRING> MAP_SAY;
typedef std::map<eSayPlayer, int> MAP_INTID;
typedef std::vector<int> VCT_INT;

//! class cInvidoGfx
/**
// class to handle the invido game grafic during the match.
*/
class cInvidoGfx : public I_ALG_Player
{
public:
    //! image index label. Add a new image always before the lNUM_ANIMAGEs
    enum
    {
        IMG_TOCCA_PLAYER,
        IMG_LEDGREEN_OFF,
        IMG_LEDGREEN_ON,
        IMG_CANELA,
        IMG_UOVO,
		IMG_VERTICAL,
		IMG_CORNER_DL,
		IMG_CORNER_DR,
		IMG_CORNER_UL,
		IMG_CORNER_UR,
		IMG_HORIZONTAL,
		IMG_LED_BLUEON,
		IMG_LED_REDON,
        IMG_CANELA_OBL,
        IMG_BALLOON,
		IMG_BALL_ARROW_UP,
        NUM_ANIMAGES
    };
    //! other constants
    enum
    {
        NUMOFBUTTON = 6
    };

	cInvidoGfx(AppGfx*  pApp);
	~cInvidoGfx();
    //! Initialize gfx
	void Initialize(SDL_Surface *s, SDL_Renderer* pRender, SDL_Texture* pScreenTexture);
    //! match loop
    void MatchLoop();
    //! init invido 2 player vs cpu
    void InitInvidoVsCPU();
    //! Set app
    void SetMainApp(AppGfx* pVal){m_pApp = pVal;}
    //! the player say something. Gui voice input.
    void INP_PlayerSay(eSayPlayer eSay);
    //! button click callback
    void ButCmdClicked(int iButID);
    //! notification from music manager, effect is terminated
    void NtfyTermEff(int iCh);
    //! provides a player (game should be created before)
    cPlayer*  GetPlayer(int iIndex){return m_pInvidoCore->GetPlayer(iIndex);}
    
//Interface I_ALG_Player (callback functions from core invido engine)
    virtual void ALG_SetCoreInterface(I_CORE_Game* pCore){}
    //! set player index
    virtual void ALG_SetPlayerIndex(int iIndex) {m_PlayerGuiIndex = iIndex;}
    //! set opponent index
    virtual void ALG_SetOpponentIndex(int iIndex, int iOpponentNr){m_iOpponentIndex = iIndex ;}
    //! set associate index
    virtual void ALG_SetAssociateIndex(int iIndex){}
    //! new match notification
    virtual void ALG_NewMatch(int iNumPlayer){}
    //! new giocata notification
    virtual void ALG_NewGiocata(const CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) ;
    //! player has played a card
    virtual void ALG_PlayerHasPlayed(int iPlayerIx, const CARDINFO* pCard) ;
    //! player has said something
    virtual void ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay);
    virtual void ALG_PlayerHasVadoDentro(int iPlayerIx);
    //! player have to play notification
    virtual void ALG_Play() ;
    //! mano end notification
    virtual void ALG_ManoEnd(I_MatchScore* pScore) ;
    //! giocata end notification
    virtual void ALG_GiocataEnd(I_MatchScore* pScore) ;
    //! match end notification
    virtual void ALG_MatchEnd(I_MatchScore* pScore) ;
    //! player have to respond
    virtual void ALG_HaveToRespond();
    //! giocata score changed
    virtual void ALG_GicataScoreChange(eGiocataScoreState eNewScore);
    //! player said something wrong
    virtual void ALG_PlayerSaidWrong(int iPlayerIx);

private:
    int     animateCards();
    void    drawStaticScene();
    int     initDeck();
    int     loadCardPac();
    void    createRegionsInit();
    void    renderCard(cCardGfx* pCard);
    void    drawPlayedCard(cCardGfx* pCard);

    void    handleKeyDownEvent(SDL_Event &event);
	void	handleMouseDownEvent(SDL_Event &event);
	void    handleMouseMoveEvent(SDL_Event &event);
	void    handleMouseUpEvent(SDL_Event &event);
    void    clickOnPlayerCard(int iIndex);
    void    vadoDentro(int cardIx);
    void    renderScreen();
    void    drawVadoDentroCard(cCardGfx * pCard);
    void    showPlayerMarkup(int iPlayerIx);
    void    showManoScore(BOOL bIsPlayed, int iPlayerIx, BOOL bIsPata, int iManoNum);
    void    guiPlayerTurn(int iPlayer);
    void    showCurrentScore();
    void    showPointsPlayer(int iPlayerIx ,  VCT_INT& vct_Points);
    void    animGiocataEnd(int iPlayerIx, BOOL bIsPata);
    void    enableCmds();
    void    setCmdButton(size_t iButtonIndex, eSayPlayer eSay, LPCSTR strCaption);
    void    enableOnlyCmdButtons(size_t iNumButt);
    void    renderPlayerName(int iPlayerIx);
    void    cleanup();
    void    animateBeginGiocata();
    void    showOkMsgBox(LPCSTR strText);
    int     showYesNoMsgBox(LPCSTR strText);
    void    animateManoEnd(int iPlayerIx);
    void    showPopUpCallMenu(CardSpec&   cardClicked, int iX, int iY, eSayPlayer* peSay);
    void    opponentHasPlayedCard(CardSpec & Card, BOOL vadoDentro);
private:
    //! from AppGfx
	SDL_Surface*      m_pScreen;
	SDL_Renderer*     m_psdlRenderer;
	SDL_Texture*      m_pScreenTexture;

    //! background surface
	SDL_Surface*      m_pScene_background;
     //! suface to draw message box
    SDL_Surface*      m_pAlphaDisplay;
    //! main deck image
	SDL_Surface*      m_pDeck;
    //! symbol surface
    SDL_Surface*      m_pSymbols;
    //! rect of back card
    SDL_Rect          m_SrcBack;
    //! rect of front card
    SDL_Rect          m_SrcCard;
    //! deck type
    cTipoDiMazzo*     m_pDeckType;
     //! font status bar
    TTF_Font*         m_pFontStatus;
    //! font
    TTF_Font*	      m_pFontText;
    //! bar surface
    SDL_Surface*      m_pSurf_Bar;
     //! invido core game
    cInvidoCore*      m_pInvidoCore;
    //! Engine app pointer
    AppGfx*       m_pApp;
    //! drag flag
    bool              m_bStartdrag;
    //! card width
    int               m_iCardWidth;
    //! card height
    int               m_iCardHeight;
    //! symbol width
    int               m_iSymbolWidth;
    //! symbol height
    int               m_iSymbolHeigth;
    //! cards in player hand
    cCardGfx          m_aPlayerCards[NUM_CARDS_HAND];
    //! cards on cpu/oppent hand
    cCardGfx          m_aOpponentCards[NUM_CARDS_HAND];
    //! cards taken
    cCardGfx          m_CardsTakenPla;
    //! cards taken from opponent
    cCardGfx          m_CardsTakenOpp;
    //! cards on table
    cCardGfx          m_CardsTable[NUM_CARDS_PLAYED];
    //! animation images
    SDL_Surface*      m_pAnImages[NUM_ANIMAGES];
    //! player gui index
    int                   m_PlayerGuiIndex;
    //! opponent index
    int                   m_iOpponentIndex;
    //! index card vado dentro
    int                   m_CardVadoDentroIndex;
    //! map dei nomi dei punteggi
    MAP_SCORE             m_MapPunti;
    //! map names of player calls for buttons
    MAP_SAY               m_Map_bt_Say;
    //! map names of player calls for feedback
    MAP_SAY               m_Map_fb_Say;
    //! map music id
    MAP_INTID             m_Map_id_EchoSay;
    //! map synth id
    MAP_INTID             m_Map_idSynth_Say;
    //! match points information
    cMatchPoints*         m_pMatchPoints;   
    //! player can play on the gui
    BOOL                  m_bPlayerCanPlay;
	//! player with markup
	int                   m_iPlayerThatHaveMarkup;
	//! delay next action
	cDelayNextAction      m_DelayAction;
    //! command button array
    cButtonGfx*           m_pbtArrayCmd[NUMOFBUTTON];
    //! command say associated with the button
    eSayPlayer            m_CmdDet[NUMOFBUTTON];
    //! balloon control
    cBalloonGfx*          m_pbalGfx;
    //! language manager
    cLanguages*           m_pLangMgr;
    //! music manager
    cMusicManager*        m_pMusicMgr;
    //! flag match termninated
    BOOL                  m_bMatchTerminated;
};

#endif //CGAME_H
