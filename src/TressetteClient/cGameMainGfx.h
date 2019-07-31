// cGameMainGfx.h

#ifndef __CINVIDO_GFX_H
#define __CINVIDO_GFX_H


#include <map>
#include <SDL_ttf.h>
#include "cCoreEngine.h"
#include "cCardGfx.h"
#include "AlgPlayerInterface.h"
#include "cDelayNextAction.h"
#include "cTipoDiMazzo.h"

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
const unsigned int CRD_NSYMBOL = 0;
const unsigned int CRD_XSYMBOL = 1;
const unsigned int CRD_OSYMBOL = 2;
const unsigned int CRD_HSYMBOL = 3;

class cEngineApp;
class cCore;
class cButtonGfx;
class cBalloonGfx;
class cLanguages;
class cMusicManager;

typedef std::map<eGiocataScoreState, STRING> MAP_SCORE;
typedef std::map<eSayPlayer, int> MAP_INTID;
typedef std::vector<int> VCT_INT;
typedef std::vector<cCardGfx*> VCT_CARDGFX;

//Functor to compare 2 cardinfo structure
class cmpCardInfoSuit
{
public:
    bool operator ()(const PCARDINFO& Card_1, const PCARDINFO& Card_2) const
    {
        if (Card_1->eSeed > Card_2->eSeed)
        {
            // swap element
            return true;
        }
        else if (Card_1->eSeed == Card_2->eSeed)
        {
            int iVal_1 = g_RankTable[Card_1->byIndex];
            int iVal_2 = g_RankTable[Card_2->byIndex];
            if (iVal_1 > iVal_2)
            {
                // bigger card, swap
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            // don't swap
            return false;
        }
    }
};

//! class cGameMainGfx
/**
// class to handle the tressete game grafic during the match.
// This class is created when the game is started.
*/
class cGameMainGfx : public I_ALG_Player
{
public:
    //! image index label. Add a new image always before the lNUM_ANIMAGEs
    enum
    {
        IMG_TOCCA_PLAYER = 0,
        IMG_LEDGREEN_OFF,
        IMG_LEDGREEN_ON,
        IMG_VERTICAL,
        IMG_HORIZONTAL,
        IMG_LED_BLUEON,
        IMG_LED_REDON,
        IMG_BALLOON,
        IMG_BALL_ARROW_DWLEFT,
        IMG_BALL_ARROW_DWRIGHT,
        IMG_BALL_ARROW_UP,
        IMG_BT_RF1,
        IMG_BT_RF2,
        IMG_BT_RF3,
        IMG_BT_INFO1,
        IMG_BT_INFO2,
        IMG_BT_INFO3,
        NUM_ANIMAGES
    };
    //! other constants
    enum
    {
        NUMOFBUTTON = 2,
        MAX_NUM_PLAYERS = 4,
        BUTID_EXIT = 0,
        BUTID_INFO = 1
    };

    cGameMainGfx(cEngineApp*  pApp);
    ~cGameMainGfx();
    //! Initialize gfx
    void Initialize(SDL_Surface *pScreen, SDL_Renderer* pRender, SDL_Texture* pScreenTexture);

    //! match loop
    void MatchLoop();
    //! init  4 player game
    void Init4PlayerGameVsCPU();
    //! New match
    void NewMatch();
    //! Set app
    void SetMainApp(cEngineApp* pVal) { m_pApp = pVal; }
    //! show chat mode
    void ShowChat(bool bVal) { m_bShowChat = TRUE; }
    //! the player say something. Gui voice input.
    void INP_PlayerSay(eSayPlayer eSay);
    //! button click callback
    void ButCmdClicked(int iButID);
    //! notification from music manager, effect is terminated
    void NtfyTermEff(int iCh);
    //! set python script init
    void SetPythonInitScript(BOOL bVal, LPCSTR strFileName) { m_bWeHaveAInitPythonScript = bVal; m_strFileInitPy = strFileName; }

    //Interface I_ALG_Player (callback functions from core engine)
    virtual void ALG_SetCoreInterface(I_CORE_Game* pCore) {}
    //! set player index
    virtual void ALG_SetPlayerIndex(int iIndex) { m_iPlayer1Index = iIndex; }
    //! set opponent index
    virtual void ALG_SetOpponentIndex(int iIndex, int iOpponentNr) { m_iOpponentIndex = iIndex; }
    //! set associate index
    virtual void ALG_SetAssociateIndex(int iIndex) {}
    //! new match notification
    virtual void ALG_NewMatch(int iNumPlayer) {}
    //! new giocata notification
    virtual void ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx);
    //! player has played a card
    virtual void ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard);
    //! player has said something
    virtual void ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay);
    //! player have to play notification
    virtual void ALG_Play();
    //! mano end notification
    virtual void ALG_ManoEnd(I_MatchScore* pScore);
    //! giocata end notification
    virtual void ALG_GiocataEnd(I_MatchScore* pScore);
    //! match end notification
    virtual void ALG_MatchEnd(I_MatchScore* pScore);
    //! player say
    virtual void ALG_Say();
    //! giocata score changed
    virtual void ALG_GicataScoreChange(eGiocataScoreState eNewScore);
    //! player said somithing false
    virtual void ALG_PLayerSaidFalse(int iPlayerIx);
    //! player has declared a good game
    virtual void ALG_PLayerDeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg, eSUIT eValsuit);

public:
    //! animation images
    SDL_Surface*      m_pAnImages[NUM_ANIMAGES];

private:
    void    renderScreen();
    void    cleanup();
    int     animateCards();
    void    drawStaticScene();
    void    renderChatPlayers();
    int     initDeck();
    int     loadCardPac();
    void    createRegionsInit();
    void    renderCard(cCardGfx* pCard);
    void    drawPlayedCard(cCardGfx* pCard, int iPlayerIx);

    void    handleKeyDownEvent(SDL_Event &event);
    void	handleMouseDownEvent(SDL_Event &event);
    void    handleMouseMoveEvent(SDL_Event &event);
    void    handleMouseUpEvent(SDL_Event &event);
    BOOL    clickOnPlayerCard(int iIndex);
    void    showPlayerMarkup(int iPlayerIx);
    void    showManoScore(BOOL bIsPlayed, int iPlayerIx, BOOL bIsPata, int iManoNum);
    void    guiPlayerTurn(int iPlayer);
    void    showCurrentScore();
    void    showPointsPlayer(int iPlayerIx, VCT_INT& vct_Points);
    void    animGiocataEnd(int iPlayerIx);
    void    enableCmds();
    void    setCmdButton(int iButtonIndex, eSayPlayer eSay, LPCSTR strCaption);
    void    enableNumButtonsCmd(int iNumButt);
    void    renderPlayerName(int iPlayerIx);
    void    animateBeginGiocata();
    void    showOkMsgBox(LPCSTR strText);
    int     showYesNoMsgBox(LPCSTR strText);
    void    showPopUpCallMenu(CardSpec&   cardClicked, int iX, int iY, eSayPlayer* peSay);
    void    showResultMsgBox(VCT_STRING& vct_strText);
    void    disableBallons();
    BOOL    allBallonAreDisabled();
    void    animateManoEnd(int iPlayerIx);
    void    animatePlayCard(cCardGfx* pCard, int iPlayerIx);
    void    lookforDeclGoodGames();
    void    showDeclarMsgBox(int iPlayerIx, LPCSTR strText);
    void    waitOnEvent();

private:
    // SDL 2.0
    SDL_Renderer*     m_psdlRenderer;
    SDL_Texture*      m_pScreenTexture;

    //! main surface
    SDL_Surface*      m_pScreen;
    //! background surface
    SDL_Surface*      m_pScene_background;
    //! suface to draw message box
    SDL_Surface*      m_pAlphaDisplay;

    //! main deck image
    SDL_Surface*      m_pDeck;
    //! symbol surface
    SDL_Surface*      m_pSymbols;
    SDL_Surface*      m_pSmallSymbols;
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
    //! core game
    cCore*            m_pCoreEngine;
    //! Engine app pointer
    cEngineApp*       m_pApp;
    //! drag flag
    bool              m_bStartdrag;
    //! card width
    int               m_iCardWidth;
    //! card height
    int               m_iCardHeight;
    //! symbol width
    int               m_iSymbolWidth;
    int               m_iSymbolSmallWidth;
    //! symbol height
    int               m_iSymbolHeigth;
    int               m_iSymbolSmallHeigth;
    //! cards in player hand
    cCardGfx          m_aPlayerCards[NUM_CARDS_HAND];
    //! cards on cpu/oppent hand
    cCardGfx          m_aOpponentCards[NUM_OTHER][NUM_CARDS_HAND];
    //! cards taken
    cCardGfx          m_CardsTakenPla;
    //! cards taken from opponent
    cCardGfx          m_CardsTakenOpp;
    //! cards on table
    cCardGfx          m_CardsTable[NUM_CARDS_PLAYED];
    //! render cards played array
    VCT_CARDGFX       m_vctPlayedCardsGfx;
    //! show chat flag
    bool                  m_bShowChat;
    //! player1 index
    int                   m_iPlayer1Index;
    //! opponent index
    int                   m_iOpponentIndex;
    //! map dei nomi dei punteggi
    MAP_SCORE             m_MapPunti;
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
    //! balloon control
    cBalloonGfx*          m_pbalGfx[MAX_NUM_PLAYERS];
    //! language manager
    cLanguages*           m_pLangMgr;
    //! music manager
    cMusicManager*        m_pMusicMgr;
    //! flag match termninated
    BOOL                  m_bMatchTerminated;
    //! display console flag
    BOOL                  m_bDisplayConsole;
    //! current deck type
    cTipoDiMazzo::eTypeMazzo    m_eCurrentDeckType;
    //! mano count
    int                   m_iTrickRound;
    //! flag python engine initialized
    BOOL                  m_bInitPython;
    //! flag if a init script is present
    BOOL                  m_bWeHaveAInitPythonScript;
    //! init python script filename
    STRING                m_strFileInitPy;
    //! players that have already played
    int                   m_iPlAlreadyPlayed;

};

#endif //CGAME_H
