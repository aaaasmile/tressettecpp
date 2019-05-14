// cGameMainGfx.cpp
#include "StdAfx.h"
#pragma warning(disable:4786)
#include "win_type_global.h"


#include <stdio.h>
#include <SDL_image.h>
#include <SDL_endian.h>

#include "cDelayNextAction.h"
#include "cGameMainGfx.h"
#include "gfx_util.h"
#include "EngineApp.h"


#include "cSettings.h"

#include "cButtonGfx.h"

#include <time.h>

#include "lang_gen.h"
#include "cBalloonGfx.h"
#include "cMesgBoxGfx.h"
#include "cMusicManager.h"
#include "ErrorMsg.h"
#include "cPopUpMenuGfx.h"
#include "AlgSupport.h"


#define FPS (1000 / 30)

static const char* lpszImageDir = "data/images/";
static const char* lpszImageBack = "im000740.jpg";
static const char* lpszMazziDir = "data/mazzi/";
static const char* lpszFontConsoleImg = "data/images/ConsoleFont.png";
static const char* lpszaImage_filenames[cGameMainGfx::NUM_ANIMAGES] =
{
    "data/images/tocca.png",
    "data/images/LedOff.bmp",
    "data/images/LedOn.bmp",
    "data/images/vertical.png",
    "data/images/horizontal.png",
    "data/images/LedOnBlue.bmp",
    "data/images/LedOnRed.bmp",
    "data/images/balloon_body.pcx",
    "data/images/balloon_down_left.pcx",
    "data/images/balloon_down_right.pcx",
    "data/images/balloon_up.pcx",
    "data/images/home_1.png",
    "data/images/home_2.png",
    "data/images/home_3.png",
    "data/images/puntodom_1.png",
    "data/images/puntodom_2.png",
    "data/images/puntodom_3.png"
};


static const char* lpszCST_INFO = "[INFO]";
static const char* lpszCST_SCORE = "[SCORE]";
static const char* lpszCST_SU = "[SU]";



//invido core
cCore*  g_pCore;
extern cEngineApp* g_MainApp;



////////////////////// cGameMainGfx

cGameMainGfx* g_stacGameMainGfx = 0;

////////////////////////////////////////
//       fnEffectTer
/*! Effect terminated notification of music manager
// \param int iCh :
*/
void fnEffectTer(int iCh)
{
    // do something
    ASSERT(g_stacGameMainGfx);
    g_stacGameMainGfx->NtfyTermEff(iCh);
}


////////////////////////////////////////
//       cGameMainGfx
/*! constructor
*/
cGameMainGfx::cGameMainGfx(cEngineApp*  pApp)
{
    m_pScene_background = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_pApp = pApp;
    m_bStartdrag = false;

    m_iSymbolWidth = 84;
    m_iSymbolHeigth = 144;
    m_pDeck = 0;
    m_pSymbols = 0;
    m_pSmallSymbols = 0;
    m_pFontStatus = 0;
    m_pDeckType = 0;

    for (int i = 0; i < NUM_ANIMAGES; i++)
    {
        m_pAnImages[i] = 0;
    }
    m_pMatchPoints = 0;
    m_pCoreEngine = 0;
    m_bPlayerCanPlay = FALSE;
    m_iPlayerThatHaveMarkup = 0;
    for (int j = 0; j < NUMOFBUTTON; j++)
    {
        m_pbtArrayCmd[0] = 0;
    }
    m_pLangMgr = 0;
    m_pMusicMgr = 0;
    g_stacGameMainGfx = this;
    m_bMatchTerminated = FALSE;

    m_bDisplayConsole = FALSE;
    m_pAlphaDisplay = 0;
    m_eCurrentDeckType = cTipoDiMazzo::PIACENTINA;
    m_bInitPython = FALSE;
    m_iPlAlreadyPlayed = 0;
}


////////////////////////////////////////
//       ~cGameMainGfx
/*! Destructor
*/
cGameMainGfx::~cGameMainGfx()
{


}

////////////////////////////////////////
//       Initialize
/*! Initialize the game gfx with the background
// \param SDL_Surface *s : screen surface
*/
void cGameMainGfx::Initialize(SDL_Surface *s)
{
    m_pScreen = s;

    CHAR ErrBuff[512];

    cLanguages* pLangMgr = m_pApp->GetLanguageMan();
    m_pLangMgr = pLangMgr;

    m_pDeckType = new cTipoDiMazzo;
    m_pDeckType->SetType((cTipoDiMazzo::eTypeMazzo)g_Options.All.iTipoMazzo);
    // init deck with all  images of  cards
    initDeck();

    std::string strFileName;

    // load background
    if (g_Options.All.bFotoBack)
    {
        strFileName = lpszImageDir;
        strFileName += lpszImageBack;

        SDL_RWops *srcBack = SDL_RWFromFile(strFileName.c_str(), "rb");
        if (srcBack == 0)
        {
            sprintf(ErrBuff, "Unable to load %s background image", strFileName.c_str());
            throw Error::Init(ErrBuff);
        }
        m_pScene_background = IMG_LoadJPG_RW(srcBack);
    }
    else
    {
        // use a default green surface 
        m_pScene_background = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
        SDL_FillRect(m_pScene_background, NULL, SDL_MapRGBA(m_pScreen->format, 0, 80, 0, 0));
    }


    // create stack regions
    createRegionsInit();

    m_pFontStatus = m_pApp->GetFontAriblk();
    m_pFontText = m_pApp->GetFontVera();

    // load images for animation stuff
    int rr = 0;
    int gg = 0;
    int bb = 0;
    int i;
    for (i = 0; i < NUM_ANIMAGES; i++)
    {
        m_pAnImages[i] = IMG_Load(lpszaImage_filenames[i]);
        if (i == IMG_TOCCA_PLAYER ||
            i == IMG_BT_RF1 || i == IMG_BT_RF2 || i == IMG_BT_RF3 || i == IMG_BT_INFO1 || i == IMG_BT_INFO2 || i == IMG_BT_INFO3)
        {
            gg = 0;
            rr = 0xff;
            bb = 0xff;
        }
        else
        {
            rr = 0;
            gg = 0;
            bb = 0;
        }
        if (m_pAnImages[i] == 0)
        {
            // image not found
            sprintf(ErrBuff, "Image not found %s", lpszaImage_filenames[i]);
            throw Error::Init(ErrBuff);
        }
        //SDL_SetColorKey(m_pAnImages[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(m_pAnImages[i]->format, rr, gg, bb));
        SDL_SetColorKey(m_pAnImages[i], TRUE, SDL_MapRGB(m_pAnImages[i]->format, rr, gg, bb)); // SDL 2.0
    }

    //SDL_EnableKeyRepeat(250, 30);

    // command buttons
    if (m_pbtArrayCmd[0] == 0)
    {
        // we use command buttons for toolbar
        SDL_Rect rctBt;
        rctBt.w = m_pAnImages[IMG_BT_RF1]->w;
        rctBt.h = m_pAnImages[IMG_BT_RF1]->h;
        rctBt.y = 20;
        int iXButInit = 20;

        for (i = 0; i < NUMOFBUTTON; i++)
        {
            rctBt.x = iXButInit + i * (rctBt.w + 4);
            m_pbtArrayCmd[i] = new cButtonGfx;
            m_pbtArrayCmd[i]->Init(&rctBt, m_pScreen, /*m_pFontText*/m_pFontStatus, i, m_psdlRenderer);
            // delegate
            m_pbtArrayCmd[i]->m_fncbClickEvent = MakeDelegate(this, &cGameMainGfx::ButCmdClicked);
            // set type bitmap
            m_pbtArrayCmd[i]->SetButtonType(cButtonGfx::BITMAP_BUTTON);
            if (i == BUTID_EXIT)
            {
                // set bitmap for exit button
                m_pbtArrayCmd[i]->SetButBitmapSurfaces(m_pAnImages[IMG_BT_RF1], m_pAnImages[IMG_BT_RF2],
                    m_pAnImages[IMG_BT_RF3]);
            }
            else if (i == BUTID_INFO)
            {
                // set bitmap for exit button
                m_pbtArrayCmd[i]->SetButBitmapSurfaces(m_pAnImages[IMG_BT_INFO1], m_pAnImages[IMG_BT_INFO2],
                    m_pAnImages[IMG_BT_INFO3]);
            }
        }
        //enable all buttons
        enableNumButtonsCmd(NUMOFBUTTON);
    }

    // ballon
    for (i = 0; i < MAX_NUM_PLAYERS; i++)
    {

        SDL_Rect destWIN;
        m_pbalGfx[i] = new cBalloonGfx;
        destWIN.w = m_pAnImages[IMG_BALLOON]->w;
        destWIN.h = m_pAnImages[IMG_BALLOON]->h;

        if (i == PLAYER1) // player gui
        {
            destWIN.x = (m_pScreen->w - m_pAnImages[IMG_BALLOON]->w) / 2 - 10;
            //destWIN.y = 450;
            destWIN.y = m_pScreen->h - m_pAnImages[IMG_BALLOON]->h - 40;
            // first make init
            m_pbalGfx[i]->Init(destWIN, m_pAnImages[IMG_BALLOON], m_pFontStatus, 200);
            // setstyle comes after init
            m_pbalGfx[i]->SetStyle(cBalloonGfx::ARROW_DWN_RIGHT, m_pAnImages[IMG_BALL_ARROW_DWRIGHT]);
        }
        else if (i == PLAYER2) // opponente alla destra
        {
            destWIN.x = m_pScreen->w - m_pAnImages[IMG_BALLOON]->w - 10;
            //destWIN.y = 250;
            destWIN.y = (m_pScreen->h - m_pAnImages[IMG_BALLOON]->h) / 2 - 20;
            // first make init
            m_pbalGfx[i]->Init(destWIN, m_pAnImages[IMG_BALLOON], m_pFontStatus, 200);
            // setstyle comes after init
            m_pbalGfx[i]->SetStyle(cBalloonGfx::ARROW_DWN_RIGHT, m_pAnImages[IMG_BALL_ARROW_DWRIGHT]);
        }
        else if (i == PLAYER3) // socio
        {
            //destWIN.x = 320;
            destWIN.x = (m_pScreen->w - m_pAnImages[IMG_BALLOON]->w) / 2 - 20;
            //destWIN.y = 100;
            destWIN.y = m_pAnImages[IMG_BALLOON]->h + 5;
            // first make init
            m_pbalGfx[i]->Init(destWIN, m_pAnImages[IMG_BALLOON], m_pFontStatus, 200);
            // setstyle comes after init
            m_pbalGfx[i]->SetStyle(cBalloonGfx::ARROW_UP, m_pAnImages[IMG_BALL_ARROW_UP]);
        }
        else if (i == PLAYER4) //opponente alla sinistra
        {
            destWIN.x = 20;
            //destWIN.y = 250;
            destWIN.y = (m_pScreen->h - m_pAnImages[IMG_BALLOON]->h) / 2 - 20;
            // first make init
            m_pbalGfx[i]->Init(destWIN, m_pAnImages[IMG_BALLOON], m_pFontStatus, 200);
            // setstyle comes after init
            m_pbalGfx[i]->SetStyle(cBalloonGfx::ARROW_DWN_RIGHT, m_pAnImages[IMG_BALL_ARROW_DWLEFT]);
        }

    }

    // music manager
    m_pMusicMgr = m_pApp->GetMusicManager();

    // messagebox background surface
    m_pAlphaDisplay = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);

}

////////////////////////////////////////
//       loadCardPac
/*! Carica il mazzo delle carte dal file in formato pac
*/
int cGameMainGfx::loadCardPac()
{
    Uint32          timetag;
    char            describtion[100];
    Uint8           num_anims;
    Uint16          w, h;
    Uint16          frames;

    int FRAMETICKS = (1000 / FPS);
    int THINKINGS_PER_TICK = 1;

    std::string strFileName = lpszMazziDir;
    strFileName += m_pDeckType->GetResFileName();

    SDL_RWops *src = SDL_RWFromFile(strFileName.c_str(), "rb");
    if (src == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Error on load deck file %s", strFileName.c_str());
        throw Error::Init(ErrBuff);
    }
    SDL_RWread(src, describtion, 100, 1);
    timetag = SDL_ReadLE32(src);
    SDL_RWread(src, &num_anims, 1, 1);
    // witdh of the picture (pac of 4 cards)
    w = SDL_ReadLE16(src);
    // height of the picture (pac of 10 rows of cards)
    h = SDL_ReadLE16(src);
    frames = SDL_ReadLE16(src);

    for (int i = 0; i < frames; i++)
    {
        SDL_ReadLE16(src);
    }

    m_pDeck = IMG_LoadPNG_RW(src);
    if (!m_pDeck)
    {
        fprintf(stderr, "Cannot create deck: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetColorKey(m_pDeck, TRUE, SDL_MapRGB(m_pDeck->format, 0, 128, 0)); // SDL 2.0

    m_iCardWidth = w / 4;
    m_iCardHeight = h / 10;

    return 0;
}


////////////////////////////////////////
//       Dispose
/*! Free stuff after game
*/
void cGameMainGfx::Dispose()
{
    delete m_pCoreEngine;
    m_pCoreEngine = 0;
    delete m_pDeckType;
    m_pDeckType = 0;
    int i;
    for (i = 0; i < NUMOFBUTTON; i++)
    {
        delete m_pbtArrayCmd[i];
        m_pbtArrayCmd[i] = 0;
    }
    for (i = 0; i < MAX_NUM_PLAYERS; i++)
    {
        delete m_pbalGfx[i];
        m_pbalGfx[i] = 0;
    }

    if (m_pScene_background)
    {
        SDL_FreeSurface(m_pScene_background);
        m_pScene_background = NULL;
    }

    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    if (m_pAlphaDisplay)
    {
        SDL_FreeSurface(m_pAlphaDisplay);
        m_pAlphaDisplay = NULL;
    }
}

////////////////////////////////////////
//       Init4PlayerGameVsCPU
/*! Init the 4 players invido game: player against CPU
*/
void cGameMainGfx::Init4PlayerGameVsCPU()
{

    m_pCoreEngine = new cCore();
    m_pCoreEngine->Create(4);
    g_pCore = m_pCoreEngine;

    m_pMatchPoints = m_pCoreEngine->GetMatchPointsObj();


    // random seed
    m_pCoreEngine->SetRandomSeed((unsigned)time(NULL));

    // local type
    m_pCoreEngine->SetLocalType((eTypeLocal)g_Options.Match.iLocalGameType);
    // good game calls
    m_pCoreEngine->SetGoodGameCallEnabled(g_Options.Match.bUseGoodGameDecla);
    // match goal
    m_pMatchPoints->SetScoreGoal(g_Options.Match.iScoreGoal);

    cPlayer* pPlayer1 = m_pCoreEngine->GetPlayer(PLAYER1);
    cPlayer* pPlayer2 = m_pCoreEngine->GetPlayer(PLAYER2);
    cPlayer* pPlayer3 = m_pCoreEngine->GetPlayer(PLAYER3);
    cPlayer* pPlayer4 = m_pCoreEngine->GetPlayer(PLAYER4);

    // set level and iformations of all players

    // first pair
    pPlayer1->SetType(PT_LOCAL);
    pPlayer1->SetName(g_Options.All.strPlayerName.c_str());
    if (g_Options.Match.iLevel_Pl_1 == HMI)
    {
        pPlayer1->SetLevel(HMI, this);
    }
    else
    {
        pPlayer1->SetLevel((eGameLevel)g_Options.Match.iLevel_Pl_1, NULL);
    }
    pPlayer1->InitPlugin(g_Options.Match.strPluginDll_Pl_1.c_str());

    pPlayer3->SetType(PT_MACHINE);
    pPlayer3->SetName(g_Options.Match.strPlayerName_3.c_str());
    pPlayer3->SetLevel((eGameLevel)g_Options.Match.iLevel_Pl_3, NULL);
    pPlayer3->InitPlugin(g_Options.Match.strPluginDll_Pl_3.c_str());

    // opponent pair
    pPlayer2->SetType(PT_MACHINE);
    pPlayer2->SetName(g_Options.Match.strPlayerName_2.c_str());
    pPlayer2->SetLevel((eGameLevel)g_Options.Match.iLevel_Pl_2, NULL);
    pPlayer2->InitPlugin(g_Options.Match.strPluginDll_Pl_2.c_str());

    pPlayer4->SetType(PT_MACHINE);
    pPlayer4->SetName(g_Options.Match.strPlayerName_4.c_str());
    pPlayer4->SetLevel((eGameLevel)g_Options.Match.iLevel_Pl_4, NULL);
    pPlayer4->InitPlugin(g_Options.Match.strPluginDll_Pl_4.c_str());

    m_bMatchTerminated = FALSE;
    m_pCoreEngine->NoInitScript();
}


////////////////////////////////////////
//       initDeck
/*! Inizializza il mazzo
*/
int cGameMainGfx::initDeck()
{
    // load deck from pac file
    if (m_pDeck == NULL)
    {
        loadCardPac();
        m_eCurrentDeckType = m_pDeckType->GetType();
    }
    else if (m_eCurrentDeckType != m_pDeckType->GetType())
    {
        // deck is changed
        SDL_FreeSurface(m_pDeck);
        loadCardPac();
    }

    // use assert because if loadCardPac failed an exception is thrown
    ASSERT(m_pDeck);
    m_SrcBack.x = 0;
    m_SrcBack.y = 0;

    m_SrcCard.y = 0;
    m_SrcCard.w = m_iCardWidth;
    m_SrcCard.h = m_iCardHeight;

    // symbols

    std::string strFileSymbName = lpszMazziDir;
    strFileSymbName += m_pDeckType->GetSymbolFileName();

    std::string strFileSymbSmallName = lpszMazziDir;
    strFileSymbSmallName += "symb_336_small.bmp";

    if (m_pSymbols)
    {
        SDL_FreeSurface(m_pSymbols);
    }
    if (m_pSmallSymbols)
    {
        SDL_FreeSurface(m_pSmallSymbols);
    }

    m_pSmallSymbols = SDL_LoadBMP(strFileSymbSmallName.c_str());
    if (m_pSmallSymbols == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Error on load small symbols %s", strFileSymbSmallName.c_str());
        throw Error::Init(ErrBuff);
    }
    //SDL_SetColorKey(m_pSmallSymbols, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSmallSymbols->format, 242, 30, 206));
    SDL_SetColorKey(m_pSmallSymbols, TRUE, SDL_MapRGB(m_pSymbols->format, 242, 30, 206)); // SDL 2.0

    m_pSymbols = SDL_LoadBMP(strFileSymbName.c_str());
    if (m_pSymbols == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Error on load deck file (symbols) %s", strFileSymbName.c_str());
        throw Error::Init(ErrBuff);
    }

    if (m_pDeckType->GetSymbolFileName() == "symb_336.bmp")
    {
        //SDL_SetColorKey(m_pSymbols, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSymbols->format, 242, 30, 206));
        SDL_SetColorKey(m_pSymbols, TRUE, SDL_MapRGB(m_pSymbols->format, 242, 30, 206)); // SDL 2.0
    }
    else
    {
        //SDL_SetColorKey(m_pSymbols, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(m_pSymbols->format, 0, 128, 0));
        SDL_SetColorKey(m_pSymbols, TRUE, SDL_MapRGB(m_pSymbols->format, 0, 128, 0)); // SDL 2.0
    }

    m_iSymbolSmallWidth = m_pSmallSymbols->w / 4;
    m_iSymbolSmallHeigth = m_pSmallSymbols->h;

    m_iSymbolWidth = m_pSymbols->w / 4;
    m_iSymbolHeigth = m_pSymbols->h;

    m_SrcBack.w = m_iSymbolWidth;
    m_SrcBack.h = m_iSymbolHeigth;

    SDL_SetSurfaceBlendMode(m_pSymbols, SDL_BLENDMODE_BLEND);

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(m_pScreen->format, 0, 0, 0, 0));
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 127); //SDL 2.0

    return 0;
}

////////////////////////////////////////
//       createRegionsInit
/*! Create region for the table
*/
void cGameMainGfx::createRegionsInit()
{
    // opponent cards on right site
    int i;

    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_aOpponentCards[0][i].m_iX = m_pScreen->w - m_iCardWidth - 10;
        m_aOpponentCards[0][i].m_iY = 70 + i * 15;

        m_aOpponentCards[0][i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_aOpponentCards[0][i].SetSymbSurf(m_pSmallSymbols, m_iSymbolSmallWidth, m_iSymbolSmallHeigth);

        m_aOpponentCards[0][i].State = cCardGfx::CSW_ST_BACK;
    }

    // partner
    int iInitialX = (m_pScreen->w - (15 * NUM_CARDS_HAND + m_iCardWidth)) / 2;
    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_aOpponentCards[1][i].m_iX = 15 * i + iInitialX;
        m_aOpponentCards[1][i].m_iY = 10;

        m_aOpponentCards[1][i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_aOpponentCards[1][i].SetSymbSurf(m_pSmallSymbols, m_iSymbolSmallWidth, m_iSymbolSmallHeigth);

        m_aOpponentCards[1][i].State = cCardGfx::CSW_ST_BACK;
    }

    // opponent on the left site
    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_aOpponentCards[2][i].m_iX = 10;
        m_aOpponentCards[2][i].m_iY = 70 + i * 15;

        m_aOpponentCards[2][i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_aOpponentCards[2][i].SetSymbSurf(m_pSmallSymbols, m_iSymbolSmallWidth, m_iSymbolSmallHeigth);

        m_aOpponentCards[2][i].State = cCardGfx::CSW_ST_BACK;
    }

    // cards on player
    int stepX = (m_iCardWidth * 75) / 100;
    if (m_pScreen->w - (NUM_CARDS_HAND * stepX + m_iCardWidth) < 0)
    {
        stepX = (m_pScreen->w - m_iCardWidth) / NUM_CARDS_HAND;
    }
    int widthAllCardsPlayer = NUM_CARDS_HAND * stepX + m_iCardWidth;
    int initialCardX = (m_pScreen->w - widthAllCardsPlayer) / 2;
    for (int k = 0; k < NUM_CARDS_HAND; k++)
    {
        m_aPlayerCards[k].m_iX = initialCardX + k * stepX;
        m_aPlayerCards[k].m_iY = m_pScreen->h - m_iCardHeight - 4;
        m_aPlayerCards[k].SetCardInfo(k, m_iCardWidth, m_iCardHeight);
        m_aPlayerCards[k].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_aPlayerCards[k].SetSymbSurf(m_pSymbols, m_iSymbolWidth, m_iSymbolHeigth);
        m_aPlayerCards[k].m_iZOrder = k;
        m_aPlayerCards[k].State = cCardGfx::CSW_ST_BACK;
    }

    // cards on table played
    int iRefTableX = (m_pScreen->w - 2 * m_iCardWidth) / 2 - 30;
    int iRefTableY = (m_pScreen->h - 2 * m_iCardHeight) / 2;
    for (int g = 0; g < NUM_CARDS_PLAYED; g++)
    {
        // use the player position neighboor
        if (g == 0)
        {
            // near to player me
            m_CardsTable[g].m_iX = iRefTableX + m_iCardWidth;
            m_CardsTable[g].m_iY = iRefTableY + 80;
        }
        else if (g == 1)
        {
            // near to opponent on right site
            m_CardsTable[g].m_iX = iRefTableX + m_iCardWidth + 50;
            m_CardsTable[g].m_iY = iRefTableY + 50;
        }
        else if (g == 2)
        {
            // near to the partner
            m_CardsTable[g].m_iX = iRefTableX + m_iCardWidth;
            m_CardsTable[g].m_iY = iRefTableY + 30;
        }
        else if (g == 3)
        {
            // near to opponent on left site
            m_CardsTable[g].m_iX = iRefTableX + m_iCardWidth - 50;
            m_CardsTable[g].m_iY = iRefTableY + 50;
        }


        m_CardsTable[g].State = cCardGfx::CSW_ST_INVISIBLE;
        m_CardsTable[g].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_CardsTable[g].SetSymbSurf(m_pSymbols, m_iSymbolWidth, m_iSymbolHeigth);
    }
}

////////////////////////////////////////
//       drawStaticScene
/*! Draw the table, included all cards, status, chat
*/
void cGameMainGfx::drawStaticScene()
{
    //renderChatPlayers();
    if (m_pScene_background)
    {
        SDL_BlitSurface(m_pScene_background, NULL, m_pScreen, NULL);
    }


    // render cards in hand
    for (int g = 0; g < NUM_OTHER; g++)
    {
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            renderCard(&m_aOpponentCards[g][i]);
            if (g == 0)
            {
                // UI player
                if (m_aPlayerCards[i].State == cCardGfx::CSW_ST_SYMBOL)
                {
                    // symbol card i drawn first
                    renderCard(&m_aPlayerCards[i]);
                    if (i > 0)
                    {
                        if (m_aPlayerCards[i - 1].State != cCardGfx::CSW_ST_SYMBOL)
                        {
                            // redraw the previous card to make it in background
                            renderCard(&m_aPlayerCards[i - 1]);
                        }
                    }
                }
                else
                {
                    renderCard(&m_aPlayerCards[i]);
                }
            }
        }
    }

    // cards played on the table
    size_t iNumCardPlayed = m_vctPlayedCardsGfx.size();
    for (int k = 0; k < iNumCardPlayed; k++)
    {
        cCardGfx* pCardGfx = m_vctPlayedCardsGfx[k];
        renderCard(pCardGfx);
    }

    showPlayerMarkup(m_iPlayerThatHaveMarkup);

    // shows names
    int i;
    int iNumPlayers = m_pCoreEngine->GetNumOfPlayers();
    for (i = 0; i < iNumPlayers; i++)
    {
        renderPlayerName(i);
    }

    // show score (leds and points)
    showCurrentScore();

    // draw command buttons
    for (int j = 0; j < NUMOFBUTTON; j++)
    {
        m_pbtArrayCmd[j]->DrawButton(m_pScreen);
    }


    // ballon
    for (i = 0; i < MAX_NUM_PLAYERS; i++)
    {
        m_pbalGfx[i]->Draw(m_pScreen);
    }

    //SDL_Flip(m_pScreen);
    m_pApp->FlipScreen(m_pScreen);
}


////////////////////////////////////////
//       renderCard
/*! Render a card gfx
// \param cCardGfx* pCard : pointer to the card
*/
void cGameMainGfx::renderCard(cCardGfx* pCard)
{
    if (pCard->State == cCardGfx::CSW_ST_INVISIBLE)
    {
        return;
    }
    else if (pCard->State == cCardGfx::CSW_ST_SYMBOL)
    {
        pCard->DrawSymbol(m_pScreen);
    }
    else if (pCard->State == cCardGfx::CSW_ST_VISIBLE)
    {
        pCard->DrawCard(m_pScreen);
    }
    else if (pCard->State == cCardGfx::CSW_ST_BACK)
    {
        pCard->DrawCardBack(m_pScreen);
    }
    else
    {
        ASSERT(0);
    }
}


////////////////////////////////////////
//       renderPlayerName
/*! Display the name of the player
// \param int iPlayerIx :
*/
void cGameMainGfx::renderPlayerName(int iPlayerIx)
{
    cPlayer* pPlayer = m_pCoreEngine->GetPlayer(iPlayerIx);

    char txt_to_render[256];
    static char un_char = ' ';

    int iLenBar = 100;
    int iX3 = 165;
    int iY3 = 25;

    int iX1 = m_pScreen->w - 100;//690;
    int iY1 = m_pScreen->h - 40; //560;

    int iX2 = iX1;
    int iY2 = 30;

    int iX4 = 16;
    int iY4 = m_pScreen->h - 200; //360;

    if (iPlayerIx == PLAYER2)
    {
        // first opponent 
        sprintf(txt_to_render, "%s", pPlayer->GetName());
        GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, iLenBar, 25, iX2, iY2, m_pSurf_Bar);
        GFX_UTIL::DrawString(m_pScreen, txt_to_render, iX2 + 5, iY2 + 4, GFX_UTIL_COLOR::White, m_pFontText, true);
    }
    else if (iPlayerIx == PLAYER1)
    {
        // user
        sprintf(txt_to_render, "%s", pPlayer->GetName());
        GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, iLenBar, 25, iX1, iY1, m_pSurf_Bar);
        GFX_UTIL::DrawString(m_pScreen, txt_to_render, iX1 + 5, iY1 + 4, GFX_UTIL_COLOR::Orange, m_pFontText, true);
    }
    else if (iPlayerIx == PLAYER3)
    {
        // socio
        sprintf(txt_to_render, "%s", pPlayer->GetName());
        GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, iLenBar, 25, iX3, iY3, m_pSurf_Bar);
        GFX_UTIL::DrawString(m_pScreen, txt_to_render, iX3 + 5, iY3 + 4, GFX_UTIL_COLOR::White, m_pFontText, true);
    }
    else if (iPlayerIx == PLAYER4)
    {
        // second opponent
        sprintf(txt_to_render, "%s", pPlayer->GetName());
        GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, iLenBar, 25, iX4, iY4, m_pSurf_Bar);
        GFX_UTIL::DrawString(m_pScreen, txt_to_render, iX4 + 5, iY4 + 4, GFX_UTIL_COLOR::White, m_pFontText, true);
    }
    else
    {
        ASSERT(0);
    }

}


////////////////////////////////////////
//       waitOnEvent
/*! Block the main loop until the user press a key or a mouse
*/
void cGameMainGfx::waitOnEvent()
{
    SDL_Event event;
    BOOL bEnd = FALSE;
    while (!bEnd)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN ||
                event.type == SDL_KEYDOWN)
            {
                // event is raised
                bEnd = TRUE;
            }
        }
    }
}

////////////////////////////////////////
//       animateBeginGiocata
/*! Animation new giocata (card distribution)
*/
void cGameMainGfx::animateBeginGiocata()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
    }

    Uint32 uiTickTot = 0;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    Uint32 uiFrameRate = 3;

    int iInitialSpeed;

    switch (g_Options.All.iAniSpeedLevel)
    {
    case 0:
        iInitialSpeed = 0;
        break;
    case 1:
        iInitialSpeed = 20;
        break;
    case 2:
        iInitialSpeed = 40;
        break;
    case 3:
        iInitialSpeed = 60;
        break;
    case 4:
        iInitialSpeed = 80;
        break;
    case 5:
        iInitialSpeed = 100;
        break;

    default:
        iInitialSpeed = 20;
        break;
    }

    cCardGfx cardTmp[NUM_CARDS_HAND];
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        cardTmp[i].Copy(&m_aPlayerCards[i]);
        cardTmp[i].m_iY = 40 + i;
        cardTmp[i].m_iX = 10 + i;
        cardTmp[i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        cardTmp[i].SetSymbSurf(m_pSymbols, m_iSymbolWidth, m_iSymbolHeigth);
        cardTmp[i].State = cCardGfx::CSW_ST_BACK;
        cardTmp[i].m_iVx = iInitialSpeed;
        cardTmp[i].m_iVy = iInitialSpeed;
    }
    BOOL bEnd = FALSE;
    int iCardMovingIx = 0;
    do
    {
        if (!bEnd)
        {
            // clear screen
            SDL_BlitSurface(m_pScene_background, NULL, m_pScreen, NULL);

            // update speed
            if (cardTmp[iCardMovingIx].m_iVx <= 9)
            {
                cardTmp[iCardMovingIx].m_iVx += 1;
                cardTmp[iCardMovingIx].m_iVy += 1;
            }

            if (cardTmp[iCardMovingIx].m_iX > m_aPlayerCards[iCardMovingIx].m_iX +
                m_aPlayerCards[iCardMovingIx].m_iWidth)
            {
                // go back on x
                cardTmp[iCardMovingIx].m_iVx -= 4;
            }
            if (cardTmp[iCardMovingIx].m_iX <= 0)
            {
                cardTmp[iCardMovingIx].m_iVx = 6;
            }

            // new position
            cardTmp[iCardMovingIx].m_iX += cardTmp[iCardMovingIx].m_iVx;
            cardTmp[iCardMovingIx].m_iY += cardTmp[iCardMovingIx].m_iVy;
        }

        // move the cards in the hand
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN ||
                event.type == SDL_KEYDOWN)
            {
                // stop the animation
                drawStaticScene();
                m_DelayAction.CheckPoint(500, cDelayNextAction::CHANGE_AVAIL);
                return;
            }
        }

        if (!bEnd)
        {
            // render all cards
            if (cardTmp[iCardMovingIx].m_iY >= m_aPlayerCards[iCardMovingIx].m_iY)
            {
                // ok the card reach the position, move the next one
                cardTmp[iCardMovingIx].Copy(&m_aPlayerCards[iCardMovingIx]);
                iCardMovingIx++;
                if (iCardMovingIx >= NUM_CARDS_HAND)
                {
                    bEnd = TRUE;
                }
            }
            for (int i = 0; i < NUM_CARDS_HAND; i++)
            {
                cardTmp[i].DrawGeneric(m_pScreen);
            }

            //SDL_Flip(m_pScreen);
            m_pApp->FlipScreen(m_pScreen);

        }

        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();

        if (uiNowTime < (uiLast_time + uiFrameRate))
        {
            int iDelayTime = uiFrameRate - (uiNowTime - uiLast_time);
            SDL_Delay(iDelayTime);
            TRACE("Delay time %d\n", iDelayTime);
            uiLast_time = uiNowTime;
        }
        uiTickTot = uiNowTime - uiInitialTick;
    } while (uiTickTot < 3000 && !bEnd);
    //while(!bEnd);

    // restore begin scene
    m_DelayAction.CheckPoint(500, cDelayNextAction::CHANGE_AVAIL);
    drawStaticScene();

}


////////////////////////////////////////
//       animateManoEnd
/*! Animate mano end. Move played cards together and than move it to the trick winner.
// \param int iPlayerIx : player that win the trick
*/
void cGameMainGfx::animateManoEnd(int iPlayerIx)
{
    Uint32 uiTickTot = 0;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    Uint32 uiFrameRate = 3;
    cCardGfx cardTmp[NUM_CARDS_PLAYED];
    for (int i = 0; i < NUM_CARDS_PLAYED; i++)
    {
        cardTmp[i].Copy(&m_CardsTable[i]);
        cardTmp[i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
    }

    int iPhase1Speed = 2;
    int iPhase2Speed = 1;

    switch (g_Options.All.iAniSpeedLevel)
    {
    case 0:
        iPhase1Speed = 1;
        iPhase2Speed = 1;
        break;
    case 1:
        iPhase1Speed = 2;
        iPhase2Speed = 2;
        break;
    case 2:
        iPhase1Speed = 3;
        iPhase2Speed = 3;
        break;
    case 3:
        iPhase1Speed = 5;
        iPhase2Speed = 5;
        break;
    case 4:
        iPhase1Speed = 7;
        iPhase2Speed = 7;
        break;
    case 5:
        iPhase1Speed = 10;
        iPhase2Speed = 10;
        break;

    default:
        iPhase1Speed = 2;
        iPhase2Speed = 1;
        break;
    }

    // move on y
    cardTmp[0].m_iVy = -iPhase1Speed;
    cardTmp[0].m_iVx = 0;
    cardTmp[2].m_iVy = 2;
    cardTmp[2].m_iVx = 0;

    // move on x
    cardTmp[1].m_iVy = 0;
    cardTmp[1].m_iVx = -iPhase1Speed;
    cardTmp[3].m_iVy = 0;
    cardTmp[3].m_iVx = iPhase1Speed;

    // freeze the current display used as background
    SDL_Surface* pCurrentDisplay = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w,
        m_pScreen->h, 32, 0, 0, 0, 0);

    SDL_BlitSurface(m_pScreen, NULL, pCurrentDisplay, NULL);


    BOOL bEnd = FALSE;
    BOOL bPhase1_Y = FALSE;
    BOOL bPhase1_X = FALSE;
    do
    {
        // clear screen
        SDL_BlitSurface(pCurrentDisplay, NULL, m_pAlphaDisplay, NULL);

        for (int iCardPlayedIndex = 0; iCardPlayedIndex < NUM_CARDS_PLAYED; iCardPlayedIndex++)
        {

            cardTmp[iCardPlayedIndex].m_iX += cardTmp[iCardPlayedIndex].m_iVx;
            cardTmp[iCardPlayedIndex].m_iY += cardTmp[iCardPlayedIndex].m_iVy;

            // update card position
            cardTmp[iCardPlayedIndex].DrawCard(m_pAlphaDisplay);
        }
        if (!bPhase1_Y && cardTmp[0].m_iY <= cardTmp[2].m_iY)
        {
            cardTmp[0].m_iVy = 0;
            cardTmp[2].m_iVy = 0;
            bPhase1_Y = TRUE;
        }
        if (!bPhase1_X && cardTmp[1].m_iX <= cardTmp[3].m_iX)
        {
            // ok the card reach the central position
            cardTmp[1].m_iVx = 0;
            cardTmp[3].m_iVx = 0;
            bPhase1_X = TRUE;
        }

        SDL_BlitSurface(m_pAlphaDisplay, NULL, m_pScreen, NULL);
        //SDL_Flip(m_pScreen);
        m_pApp->FlipScreen(m_pScreen);

        int iIncVel = iPhase2Speed;

        if (bPhase1_X && bPhase1_Y)
        {
            // second step, move cards to the trick winner
            if (iPlayerIx == 0)
            {
                cardTmp[0].m_iVy += iIncVel;
                cardTmp[1].m_iVy += iIncVel;
                cardTmp[2].m_iVy += iIncVel;
                cardTmp[3].m_iVy += iIncVel;
                if (cardTmp[2].m_iY >= m_pScreen->h)
                {
                    // cards outside of the screen
                    bEnd = TRUE;
                }
            }
            else if (iPlayerIx == 1)
            {
                cardTmp[0].m_iVx += iIncVel;
                cardTmp[1].m_iVx += iIncVel;
                cardTmp[2].m_iVx += iIncVel;
                cardTmp[3].m_iVx += iIncVel;
                if (cardTmp[3].m_iX >= m_pScreen->w)
                {
                    // cards outside of the screen
                    bEnd = TRUE;
                }
            }
            else if (iPlayerIx == 2)
            {
                cardTmp[0].m_iVy -= iIncVel;
                cardTmp[1].m_iVy -= iIncVel;
                cardTmp[2].m_iVy -= iIncVel;
                cardTmp[3].m_iVy -= iIncVel;
                if (cardTmp[0].m_iY <= 0)
                {
                    // cards outside of the screen
                    bEnd = TRUE;
                }
            }
            else if (iPlayerIx == 3)
            {
                cardTmp[0].m_iVx -= iIncVel;
                cardTmp[1].m_iVx -= iIncVel;
                cardTmp[2].m_iVx -= iIncVel;
                cardTmp[3].m_iVx -= iIncVel;
                if (cardTmp[1].m_iX <= 0)
                {
                    // cards outside of the screen
                    bEnd = TRUE;
                }
            }

        }

        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();
        uiTickTot = uiNowTime - uiInitialTick;
        if (uiNowTime < uiLast_time + uiFrameRate)
        {
            SDL_Delay(uiLast_time + uiFrameRate - uiNowTime);
            uiLast_time = uiNowTime;
        }
    } while (uiTickTot < 2000 && !bEnd);

    SDL_FreeSurface(pCurrentDisplay);
}


////////////////////////////////////////
//       animGiocataEnd
/*! Shows a little animation because giocata is terminated.
// \param int iPlayerIx : Player that wons the giocata
*/
void cGameMainGfx::animGiocataEnd(int iPlayerIx)
{

}


////////////////////////////////////////
//       animateCards
/*! Shows a little animation.
*/
int cGameMainGfx::animateCards()
{
    //srand((unsigned)time(NULL));

    int rot;
    int xspeed;
    int yspeed;

    int		GRAVITY = 1;
    int		MAXY = m_pScreen->h;
    float	BOUNCE = 0.8f;
    cCardGfx cardGfx;

    do
    {
        rot = rand() % 2;
        cardGfx.cardSpec.SetCardIndex(rand() % 40);

        cardGfx.m_iX = rand() % m_pScreen->w;
        cardGfx.m_iY = rand() % m_pScreen->h / 2;

        if (rot)
        {
            xspeed = -4;
        }
        else
        {
            xspeed = 4;
        }

        yspeed = 0;

        do //while card is within the m_pScreen
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL))
                return -1; // stop the animation

            yspeed = yspeed + GRAVITY;
            cardGfx.m_iX += xspeed;
            cardGfx.m_iY += yspeed;

            if (cardGfx.m_iY + m_iCardHeight > MAXY)
            {
                cardGfx.m_iY = MAXY - m_iCardHeight;
                yspeed = int(-yspeed * BOUNCE);
            }

            cardGfx.DrawCard(m_pScreen);
            //SDL_Flip(m_pScreen);
            m_pApp->FlipScreen(m_pScreen);
        } while ((cardGfx.m_iX + 73 > 0) && (cardGfx.m_iX < m_pScreen->w));
    } while (1);

    return 0;
}

////////////////////////////////////////
//       showOkMsgBox
/*! Show an ok messge box
*/
void cGameMainGfx::showOkMsgBox(LPCSTR strText)
{
    ASSERT(m_pAlphaDisplay);
    // prepare the size of the box
    cMesgBoxGfx   MsgBox;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w - 100;
    rctBox.h = 130;
    rctBox.y = (m_pScreen->h - rctBox.h) / 2;
    rctBox.x = (m_pScreen->w - rctBox.w) / 2;

    // show a mesage box
    MsgBox.Init(&rctBox, m_pScreen, m_pFontStatus, cMesgBoxGfx::MBOK, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);
    STRING strTextBt = m_pLangMgr->GetStringId(cLanguages::ID_OK);
    MsgBox.Show(m_pAlphaDisplay, strTextBt.c_str(), "", strText);
}


////////////////////////////////////////
//       showResultMsgBox
/*! Show a window with match points
// \param VCT_STRING& vct_strText : text to render
*/
void cGameMainGfx::showResultMsgBox(VCT_STRING& vct_strText)
{
    ASSERT(m_pAlphaDisplay);
    // prepare the size of the box
    cMesgBoxGfx   MsgBox;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w - 100;
    rctBox.h = m_pScreen->h - 180;
    rctBox.y = 80;
    rctBox.x = (m_pScreen->w - rctBox.w) / 2;

    // show a mesage box
    MsgBox.Init(&rctBox, m_pScreen, m_pFontStatus, cMesgBoxGfx::MBOK, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);

    for (UINT i = 0; i < vct_strText.size(); i++)
    {
        MsgBox.AddLineText(vct_strText[i].c_str());
    }

    STRING strTextBt = m_pLangMgr->GetStringId(cLanguages::ID_OK);
    MsgBox.Show(m_pAlphaDisplay, strTextBt.c_str(), "", "");
}


////////////////////////////////////////
//       showDeclarMsgBox
/*! Show a good game declaration box
// \param int iPlayerIx :
// \param LPCSTR strText :
*/
void cGameMainGfx::showDeclarMsgBox(int iPlayerIx, LPCSTR strText)
{
    ASSERT(m_pAlphaDisplay);
    // prepare the size of the box
    cMesgBoxGfx   MsgBox;
    SDL_Rect rctBox;
    rctBox.w = 350;
    rctBox.h = 170;

    if (iPlayerIx == 0)
    {
        rctBox.y = (m_pScreen->h - rctBox.h) - 100;
        rctBox.x = (m_pScreen->w - rctBox.w) / 2;
    }
    else if (iPlayerIx == 1)
    {
        rctBox.y = (m_pScreen->h - rctBox.h) / 2;
        rctBox.x = (m_pScreen->w - rctBox.w) - 10;
    }
    else if (iPlayerIx == 2)
    {
        rctBox.y = 50;
        rctBox.x = (m_pScreen->w - rctBox.w) / 2;
    }
    else if (iPlayerIx == 3)
    {
        rctBox.y = (m_pScreen->h - rctBox.h) / 2;
        rctBox.x = 50;
    }


    // show a mesage box
    MsgBox.Init(&rctBox, m_pScreen, /*m_pFontText*/ m_pFontStatus, cMesgBoxGfx::MBOK, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);
    STRING strTextBt = m_pLangMgr->GetStringId(cLanguages::ID_OK);

    cPlayer* pPlayer = m_pCoreEngine->GetPlayer(iPlayerIx);
    STRING strTmp2 = pPlayer->GetName();
    STRING strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_ACCUSA);
    STRING strLine = strTmp2 + " " + strTmp + ":";
    MsgBox.AddLineText(strLine.c_str());
    MsgBox.AddLineText(strText);

    MsgBox.Show(m_pAlphaDisplay, strTextBt.c_str(), "", "");
    // default display
    drawStaticScene();
}


////////////////////////////////////////
//       showYesNoMsgBox
/*! Show yes/no message box
// \param LPCSTR strText : Content of the messagebox
\return :1 for yes
\return :0 for no
*/
int  cGameMainGfx::showYesNoMsgBox(LPCSTR strText)
{
    ASSERT(m_pAlphaDisplay);

    // prepare the size of the box
    cMesgBoxGfx   MsgBox;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w - 100;
    rctBox.h = 130;
    rctBox.y = (m_pScreen->h - rctBox.h) / 2;
    rctBox.x = (m_pScreen->w - rctBox.w) / 2;

    // show a mesage box
    MsgBox.Init(&rctBox, m_pScreen, m_pFontStatus, cMesgBoxGfx::MB_YES_NO, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);

    STRING strTextYes = m_pLangMgr->GetStringId(cLanguages::ID_YES);
    STRING strTextNo = m_pLangMgr->GetStringId(cLanguages::ID_NO);
    int iRes = MsgBox.Show(m_pAlphaDisplay, strTextYes.c_str(), strTextNo.c_str(), strText);

    return iRes;
}


////////////////////////////////////////
//       showPopUpCallMenu
/*! Show a popup menu to select what the user say
// \param int iX : mouse x position
// \param int iY : mouse y position
// \param eSayPlayer eSay : say result
*/
void cGameMainGfx::showPopUpCallMenu(CardSpec&   cardClicked, int iX, int iY, eSayPlayer* peSay)
{
    if (m_iTrickRound >= NUM_CARDS_HAND)
    {
        // last trick, don't need to show call menu
        return;
    }

    if ((m_iPlAlreadyPlayed > 0) && (m_pCoreEngine->GetLocalType() == LT_CHITARELLA ||
        m_pCoreEngine->GetLocalType() == LT_ROMANA))
    {
        // don't show declaration pop-up in this local
        return;
    }

    TRACE("show popup menu\n");
    ASSERT(peSay);
    ASSERT(m_pAlphaDisplay);
    *peSay = NOTHING;
    VCT_SIGNALS vctAvail;
    m_pCoreEngine->GetAdmittedSignals(cardClicked, vctAvail, m_iPlayer1Index);
    size_t iNumCmdsAval = vctAvail.size();

    if (iNumCmdsAval == 0)
    {
        // no commands available
        return;
    }

    // prepare the size of the box
    cPopUpMenuGfx   Menu;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w; // max value, width is autocalculated
    rctBox.h = m_pScreen->h; // max value hight is autocalculated
    rctBox.y = iY;
    rctBox.x = iX;

    // show a mesage box
    Menu.Init(&rctBox, m_pScreen, m_pFontText, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);

    for (int i = 0; i < iNumCmdsAval; i++)
    {
        Menu.AddLineText(vctAvail[i].lpcText);
    }

    Menu.Show(m_pAlphaDisplay);
    // menu is terminated
    if (Menu.MenuIsSelected())
    {
        // the user choice a menu
        int iIndexSel = Menu.GetSlectedIndex();
        *peSay = vctAvail[iIndexSel].eSay;
    }
    else
    {
        *peSay = NOTHING;
    }

    TRACE("END popup menu\n");
    drawStaticScene();

}


////////////////////////////////////////
//       NewMatch
/*!
*/
void cGameMainGfx::NewMatch()
{
    Mix_ChannelFinished(fnEffectTer);

    // a new match is being started
    m_pCoreEngine->NewMatch();

    // draw the static scene
    drawStaticScene();

}

////////////////////////////////////////
//       MatchLoop
/*! Match loop
*/
void cGameMainGfx::MatchLoop()
{

    SDL_Event event;
    int done = 0;
    Uint32 uiLast_time;
    Uint32 uiFrame = 0;
    Uint32 uiNowTime = 0;
    m_DelayAction.Reset();

    STRING strTextTmp;
    uiLast_time = SDL_GetTicks();

    while (done == 0 &&
        m_bMatchTerminated == FALSE)
    {
        uiFrame++;

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                // user want to exit the match
                // show a messagebox for confirm
                strTextTmp = m_pLangMgr->GetStringId(cLanguages::ID_MATCHENDQUESTION);
                if (showYesNoMsgBox(strTextTmp.c_str()) == cMesgBoxGfx::MB_RES_YES)
                {
                    return;
                }
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    strTextTmp = m_pLangMgr->GetStringId(cLanguages::ID_MATCHENDQUESTION);
                    if (showYesNoMsgBox(strTextTmp.c_str()) == cMesgBoxGfx::MB_RES_YES)
                    {
                        done = 1;
                    }

                }
                handleKeyDownEvent(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseDownEvent(event);
                break;

            case SDL_MOUSEMOTION:
                handleMouseMoveEvent(event);
                break;

            case SDL_MOUSEBUTTONUP:
                handleMouseUpEvent(event);
                break;
            }
        }

        uiNowTime = SDL_GetTicks();
        if (uiNowTime > uiLast_time + FPS)
        {
            drawStaticScene();
            uiLast_time = uiNowTime;
        }


        // actualize display
        // next action on the game
        if (m_DelayAction.CanStart())
        {
            m_pCoreEngine->NextAction();
        }

        // actualize display
        //SDL_Flip(m_pScreen);
        m_pApp->FlipScreen(m_pScreen);

        if (m_pApp->IsWxClient())
        {
            // go back to the wx client
            done = 1;
        }

    }
}

////////////////////////////////////////
//       handleMouseDownEvent
/*! Mouse down event happens
// \param SDL_Event &event :
*/
void cGameMainGfx::handleMouseDownEvent(SDL_Event &event)
{


    if (event.button.button == SDL_BUTTON_LEFT)
    {
        // check if the player have to play a card
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            // check if a card was clicked
            if (m_aPlayerCards[i].MouseInCard(event.button.x, event.button.y))
            {
                int iIndex_1 = i;
                int iIndex_2 = i + 1;
                int iZor_1 = m_aPlayerCards[iIndex_1].m_iZOrder;
                // check if another card was clicked
                // could be only the next
                eSayPlayer eSay = NOTHING;
                if (iIndex_2 < NUM_CARDS_HAND)
                {
                    if (m_aPlayerCards[iIndex_2].MouseInCard(event.button.x, event.button.y))
                    {
                        int iZor_2 = m_aPlayerCards[iIndex_2].m_iZOrder;
                        // other card have a click
                        // check the z order
                        if (iZor_1 > iZor_2)
                        {
                            // card is played correctly
                            if (!g_Options.All.bSignalWithRMouse)
                            {
                                // ask about user signal
                                // shows declaration pop-up
                                showPopUpCallMenu(m_aPlayerCards[iIndex_1].cardSpec, event.button.x, event.button.y, &eSay);
                            }
                            if (clickOnPlayerCard(iIndex_1))
                            {
                                if (eSay != NOTHING)
                                {
                                    // trigger signal
                                    m_pCoreEngine->Player_saySomething(m_iPlayer1Index, eSay);
                                }
                                break;
                            }
                        }
                        else
                        {
                            if (!g_Options.All.bSignalWithRMouse)
                            {
                                // ask about user signal
                                // shows declaration pop-up
                                showPopUpCallMenu(m_aPlayerCards[iIndex_2].cardSpec, event.button.x, event.button.y, &eSay);
                            }
                            if (clickOnPlayerCard(iIndex_2))
                            {
                                if (eSay != NOTHING)
                                {
                                    // trigger signal
                                    m_pCoreEngine->Player_saySomething(m_iPlayer1Index, eSay);
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        if (!g_Options.All.bSignalWithRMouse)
                        {
                            // ask about user signal
                            // shows declaration pop-up
                            showPopUpCallMenu(m_aPlayerCards[i].cardSpec, event.button.x, event.button.y, &eSay);
                        }
                        // only one card has a click
                        if (clickOnPlayerCard(i))
                        {
                            if (eSay != NOTHING)
                            {
                                // trigger signal
                                m_pCoreEngine->Player_saySomething(m_iPlayer1Index, eSay);
                            }
                            break;
                        }
                    }
                }
                else
                {
                    if (!g_Options.All.bSignalWithRMouse)
                    {
                        // ask about user signal
                        // shows declaration pop-up
                        showPopUpCallMenu(m_aPlayerCards[i].cardSpec, event.button.x, event.button.y, &eSay);
                    }
                    // no other cards
                    if (clickOnPlayerCard(i))
                    {
                        if (eSay != NOTHING)
                        {
                            // trigger signal
                            m_pCoreEngine->Player_saySomething(m_iPlayer1Index, eSay);
                        }
                        break;
                    }
                }
            }

        }

    }
    else if (event.button.button == SDL_BUTTON_RIGHT)
    {
        // mouse right
        // use the right button to show a popup menu to select a signal and play a card
        // check if the player is on turn and if was clicked on a card
        if (m_bPlayerCanPlay && g_Options.All.bSignalWithRMouse)
        {
            for (int i = 0; i < NUM_CARDS_HAND; i++)
            {
                if (m_aPlayerCards[i].State == cCardGfx::CSW_ST_VISIBLE &&
                    m_aPlayerCards[i].MouseInCard(event.button.x, event.button.y))
                {
                    // take care of Zorder
                    int iIndex_1 = i;
                    int iIndex_2 = i + 1;
                    int iZor_1 = m_aPlayerCards[iIndex_1].m_iZOrder;
                    int iZor_2 = -1;
                    if (iIndex_2 < NUM_CARDS_HAND)
                    {
                        if (m_aPlayerCards[iIndex_2].MouseInCard(event.button.x, event.button.y))
                        {
                            // overlap the second card
                            iZor_2 = m_aPlayerCards[iIndex_2].m_iZOrder;
                        }
                    }
                    int iIndexCardSelected = iIndex_1;
                    if (iZor_2 > iZor_1)
                    {
                        iIndexCardSelected = iIndex_2;
                    }

                    eSayPlayer eSay = NOTHING;
                    showPopUpCallMenu(m_aPlayerCards[iIndexCardSelected].cardSpec, event.button.x, event.button.y, &eSay);
                    if (eSay != NOTHING)
                    {
                        BOOL bCardPlayed = clickOnPlayerCard(iIndexCardSelected);
                        if (bCardPlayed)
                        {
                            // card palyed
                            // set also call
                            m_pCoreEngine->Player_saySomething(m_iPlayer1Index, eSay);
                        }
                    }
                    // stop search other cards
                    break;
                }
            }
        }
    }
    for (int i = 0; i < NUMOFBUTTON; i++)
    {
        m_pbtArrayCmd[i]->MouseDown(event, m_pScreen, m_pScene_background, m_pScreenTexture);
    }
}


////////////////////////////////////////
//       clickOnPlayerCard
/*! A player card was clicked
// \param int iIndex : index of the card clicked
*/
BOOL  cGameMainGfx::clickOnPlayerCard(int iIndex)
{
    BOOL bRet = FALSE;
    TRACE("card clicked %d\n", iIndex);
    if (m_bPlayerCanPlay && (m_aPlayerCards[iIndex].State == cCardGfx::CSW_ST_VISIBLE))
    {
        BOOL bGiocAdmit = m_pCoreEngine->Player_playCard(m_iPlayer1Index, m_aPlayerCards[iIndex].cardSpec.GetCardInfo());
        if (bGiocAdmit)
        {
            // card admitted
            m_bPlayerCanPlay = FALSE;
            TRACE("Player is blocked\n");
            bRet = TRUE;
        }
        else
        {
            // card is not admitted
            // force to draw the card for a little with color reversed
            m_aPlayerCards[iIndex].StartShowReversed();
            if (g_Options.All.bSoundEffect)
            {
                // play sound effect on error card clicked
                m_pMusicMgr->PlayEffect(cMusicManager::SND_EFC_CARDFALSE);
                m_DelayAction.CheckPoint(60, cDelayNextAction::CHANGE_AVAIL);

            }
        }
    }
    return bRet;
}



////////////////////////////////////////
//       drawPlayedCard
/*! Draw a card that was played
// \param cCardGfx* pCard : card played
// \param int iPlayerIx: player index that played
*/
void cGameMainGfx::drawPlayedCard(cCardGfx* pCard, int iPlayerIx)
{
    ASSERT(iPlayerIx >= 0 && iPlayerIx < NUM_CARDS_PLAYED);

    if (g_Options.All.bAnimatePlayCard)
    {
        animatePlayCard(pCard, iPlayerIx);
    }
    else
    {

        drawStaticScene();

        m_CardsTable[iPlayerIx].CopyButNoPosition(pCard);
        renderCard(&m_CardsTable[iPlayerIx]);
        pCard->SetSymbolTocard(cCardGfx::SYMBOL_BRISCNET, m_iCardWidth, m_iCardHeight, m_pScreen);
        renderCard(pCard);
        m_vctPlayedCardsGfx.push_back(&m_CardsTable[iPlayerIx]);

        //SDL_Flip(m_pScreen);
        m_pApp->FlipScreen(m_pScreen);
    }

}


////////////////////////////////////////
//       animatePlayCard
/*!
// \param cCardGfx* pCard :
// \param int iPlayerIx :
*/
void cGameMainGfx::animatePlayCard(cCardGfx* pCard, int iPlayerIx)
{
    Uint32 uiTickTot = 0;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    Uint32 uiFrameRate = 3;
    cCardGfx cardTmp;
    cardTmp.Copy(pCard);
    cardTmp.SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);

    int iTimeSlow = 30;

    switch (g_Options.All.iAniSpeedLevel)
    {
    case 0:
        iTimeSlow = 100;
        break;
    case 1:
        iTimeSlow = 60;
        break;
    case 2:
        iTimeSlow = 20;
        break;
    case 3:
        iTimeSlow = 6;
        break;
    case 4:
        iTimeSlow = 3;
        break;
    case 5:
        iTimeSlow = 1;
        break;

    default:
        iTimeSlow = 30;
        break;
    }



    cardTmp.m_iVx = (m_CardsTable[iPlayerIx].m_iX - cardTmp.m_iX) / iTimeSlow;
    cardTmp.m_iVy = (m_CardsTable[iPlayerIx].m_iY - cardTmp.m_iY) / iTimeSlow;


    // make card to play invisible and draw a background
    pCard->State = cCardGfx::CSW_ST_INVISIBLE;
    drawStaticScene();

    // freeze the current display used as background
    SDL_Surface* pCurrentDisplay = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w,
        m_pScreen->h, 32, 0, 0, 0, 0);

    SDL_BlitSurface(m_pScreen, NULL, pCurrentDisplay, NULL);

    int iX0 = cardTmp.m_iX;
    int iY0 = cardTmp.m_iY;
    int iXF = m_CardsTable[iPlayerIx].m_iX;
    int iYF = m_CardsTable[iPlayerIx].m_iY;

    // use + 1 to avoid division by 0
    int iM = 1;
    if (iXF - iX0 != 0)
    {
        iM = (iYF - iY0) * 1000 / (iXF - iX0);
    }
    int iQ = iY0 - iM * iX0 / 1000;

    BOOL bEnd = FALSE;
    BOOL bXEnd = FALSE;
    do
    {
        // clear screen
        SDL_BlitSurface(pCurrentDisplay, NULL, m_pAlphaDisplay, NULL);

        if (((iXF > iX0) && (iXF - iX0 < 2)) ||
            ((iX0 >= iXF) && (iX0 - iXF < 2)))
        {
            // we need to move only on Y and not on X
            cardTmp.m_iY += cardTmp.m_iVy;
        }
        else
        {
            cardTmp.m_iX += cardTmp.m_iVx;
            if (cardTmp.m_iVx > 0)
            {
                if (cardTmp.m_iX > iXF + 4)
                {
                    if (bXEnd)
                    {
                        // second time that X limit is reached 
                        bEnd = TRUE;
                    }
                    cardTmp.m_iX = iXF;
                    bXEnd = TRUE;
                }
            }
            else
            {
                if (cardTmp.m_iX < iXF - 4)
                {
                    if (bXEnd)
                    {
                        // second time that X limit is reached 
                        bEnd = TRUE;
                    }
                    cardTmp.m_iX = iXF;
                    bXEnd = TRUE;
                }
            }
            cardTmp.m_iY = iM * cardTmp.m_iX / 1000 + iQ;
        }

        // update card position
        cardTmp.DrawCard(m_pAlphaDisplay);

        if (iPlayerIx == 0)
        {

            if (cardTmp.m_iX <= m_CardsTable[iPlayerIx].m_iX)
            {
                if (cardTmp.m_iVx < 0)
                {

                    //if (cardTmp.m_iVx > -6)
                    cardTmp.m_iVx -= 2;
                }
                else
                {
                    //if (cardTmp.m_iVx < 6)
                    cardTmp.m_iVx++;
                }

            }
            else
            {
                if (cardTmp.m_iVx > 0)
                {
                    cardTmp.m_iVx -= 2;
                }
                else
                {
                    cardTmp.m_iVx--;
                }
            }

            if (cardTmp.m_iY <= (m_CardsTable[iPlayerIx].m_iY))
            {
                // cards on target
                bEnd = TRUE;
            }
            else
            {
                cardTmp.m_iVy -= 1;
            }
        }
        else if (iPlayerIx == 2)
        {

            if (cardTmp.m_iX <= m_CardsTable[iPlayerIx].m_iX)
            {
                if (cardTmp.m_iVx < 0)
                    cardTmp.m_iVx += 2;
                else
                    cardTmp.m_iVx++;

            }
            else
            {
                if (cardTmp.m_iVx > 0)
                    cardTmp.m_iVx -= 2;
                else
                    cardTmp.m_iVx--;
            }

            if (cardTmp.m_iY >= (m_CardsTable[iPlayerIx].m_iY))
            {
                // cards outside of the screen
                bEnd = TRUE;
            }
            else
            {
                cardTmp.m_iVy += 1;
            }
        }
        else if (iPlayerIx == 1)
        {
            if (cardTmp.m_iY < m_CardsTable[iPlayerIx].m_iY)
            {
                if (cardTmp.m_iVy < 0)
                    cardTmp.m_iVy += 2;
                else if (cardTmp.m_iVy < 6)
                    cardTmp.m_iVy++;
            }
            else
            {
                if (cardTmp.m_iVy > 0)
                    cardTmp.m_iVy -= 2;
                else if (cardTmp.m_iVy > -6)
                    cardTmp.m_iVy--;
            }

            if (cardTmp.m_iX <= (m_CardsTable[iPlayerIx].m_iX))
            {
                // cards outside of the screen
                bEnd = TRUE;
            }
            else
            {
                cardTmp.m_iVx -= 1;
            }
        }
        else if (iPlayerIx == 3)
        {
            if (cardTmp.m_iY < m_CardsTable[iPlayerIx].m_iY)
            {
                if (cardTmp.m_iVy < 0)
                    cardTmp.m_iVy += 2;
                else if (cardTmp.m_iVy < 6)
                    cardTmp.m_iVy++;
            }
            else
            {
                if (cardTmp.m_iVy > 0)
                    cardTmp.m_iVy -= 2;
                else if (cardTmp.m_iVy > -6)
                    cardTmp.m_iVy--;
            }

            if (cardTmp.m_iX >= (m_CardsTable[iPlayerIx].m_iX))
            {
                // cards outside of the screen
                bEnd = TRUE;
            }
            else
            {
                cardTmp.m_iVx += 1;
            }
        }
        if (bEnd)
        {
            m_CardsTable[iPlayerIx].CopyButNoPosition(pCard);
            m_CardsTable[iPlayerIx].State = cCardGfx::CSW_ST_VISIBLE;
            renderCard(&m_CardsTable[iPlayerIx]);
            pCard->SetSymbolTocard(cCardGfx::SYMBOL_BRISCNET, m_iCardWidth, m_iCardHeight, m_pScreen);
            renderCard(pCard);
            m_vctPlayedCardsGfx.push_back(&m_CardsTable[iPlayerIx]);
        }

        SDL_BlitSurface(m_pAlphaDisplay, NULL, m_pScreen, NULL);
        //SDL_Flip(m_pScreen);
        m_pApp->FlipScreen(m_pScreen);


        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();
        uiTickTot = uiNowTime - uiInitialTick;
        if (uiNowTime < uiLast_time + uiFrameRate)
        {
            SDL_Delay(uiLast_time + uiFrameRate - uiNowTime);
            uiLast_time = uiNowTime;
        }
    } while (uiTickTot < 2000 && !bEnd);
    ASSERT(bEnd);
    if (!bEnd)
    {
        m_CardsTable[iPlayerIx].CopyButNoPosition(pCard);
        m_CardsTable[iPlayerIx].State = cCardGfx::CSW_ST_VISIBLE;
        renderCard(&m_CardsTable[iPlayerIx]);
        pCard->SetSymbolTocard(cCardGfx::SYMBOL_BRISCNET, m_iCardWidth, m_iCardHeight, m_pScreen);
        renderCard(pCard);
        m_vctPlayedCardsGfx.push_back(&m_CardsTable[iPlayerIx]);
    }

    SDL_FreeSurface(pCurrentDisplay);
}




////////////////////////////////////////
//       HandleMouseMoveEvent
/*!
// \param SDL_Event &event :
*/
void cGameMainGfx::handleMouseMoveEvent(SDL_Event &event)
{
    for (int i = 0; i < NUMOFBUTTON; i++)
    {
        m_pbtArrayCmd[i]->MouseMove(event, m_pScreen, m_pScene_background, m_pScreenTexture);
    }

}

////////////////////////////////////////
//       HandleMouseUpEvent
/*! Mouse up event
// \param SDL_Event &event :
*/
void cGameMainGfx::handleMouseUpEvent(SDL_Event &event)
{
    for (int i = 0; i < NUMOFBUTTON; i++)
    {
        m_pbtArrayCmd[i]->MouseUp(event);
    }
}


////////////////////////////////////////
//       handleKeyDownEvent
/*! User press a key on keyboard
// \param SDL_Event &event :
*/
void cGameMainGfx::handleKeyDownEvent(SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_n)
    {
        //startNewMatch(); 
        drawStaticScene();
    }
    if (event.key.keysym.sym == SDLK_a)
    {
        animateCards();
    }; // Test animation
    if (event.key.keysym.sym == SDLK_r)
    {
        // refresh
        drawStaticScene();
    }; // Refresh
}



////////////////////////////////////////
//       showPlayerMarkup
/*! Show a little bitmap near to the player that have to play
// \param int iPlayerIx :
*/
void cGameMainGfx::showPlayerMarkup(int iPlayerIx)
{
    SDL_Rect dest;
    if (iPlayerIx == PLAYER1)
    {
        dest.x = m_pScreen->w - m_pAnImages[IMG_TOCCA_PLAYER]->w - 20;
        dest.y = m_pScreen->h - m_iCardHeight / 2;
    }
    else if (iPlayerIx == PLAYER2)
    {
        dest.x = m_pScreen->w - m_pAnImages[IMG_TOCCA_PLAYER]->w - 10;
        dest.y = m_pScreen->h / 2;
    }
    else if (iPlayerIx == PLAYER3)
    {
        dest.x = m_pScreen->w / 2 + 10;
        dest.y = m_iCardHeight / 2;
    }
    else if (iPlayerIx == PLAYER4)
    {
        dest.x = 10;
        dest.y = m_pScreen->h / 2;
    }
    else
    {
        ASSERT(0);
    }
    dest.w = m_pAnImages[IMG_TOCCA_PLAYER]->w;
    dest.h = m_pAnImages[IMG_TOCCA_PLAYER]->h;
    SDL_BlitSurface(m_pAnImages[IMG_TOCCA_PLAYER], NULL, m_pScreen, &dest);
}


////////////////////////////////////////
//       showPointsPlayer
/*! Shows the score of the players. Caneli are drawn max 3 one the same line, egg max 2. No caneli and eggs on
// the same line are possible.
// \param int iPlayerIx : player index
// \param VCT_INT& vct_Points : vector of points scored (sequence of 3 and 1)
*/
void    cGameMainGfx::showPointsPlayer(int iPlayerIx, VCT_INT& vct_Points)
{


}

////////////////////////////////////////
//       showManoScore
/*! Show the score of the mano using leds.
*/
void cGameMainGfx::showManoScore(BOOL bIsPlayed, int iPlayerIx, BOOL bIsPata, int iManoNum)
{
    SDL_Rect dest;
    SDL_Rect destOff;
    dest.x = 400 + 16 * iManoNum;
    destOff.x = dest.x;
    int iCooYA = m_pScreen->h - 30;
    int iCooYB = 20;

    if (iPlayerIx == PLAYER1 || !bIsPlayed || bIsPata)
    {
        dest.y = iCooYA;
        destOff.y = iCooYB;
    }
    else if (iPlayerIx == PLAYER2)
    {
        dest.y = iCooYB;
        destOff.y = iCooYA;
    }
    else
    {
        ASSERT(0);
    }
    if (bIsPlayed)
    {
        // winner is ON
        dest.w = m_pAnImages[IMG_LEDGREEN_ON]->w;
        dest.h = m_pAnImages[IMG_LEDGREEN_ON]->h;
        SDL_BlitSurface(m_pAnImages[IMG_LEDGREEN_ON], NULL, m_pScreen, &dest);
        if (bIsPata)
        {
            // pata, both blue
            destOff.w = m_pAnImages[IMG_LED_BLUEON]->w;
            destOff.h = m_pAnImages[IMG_LED_BLUEON]->h;
            SDL_BlitSurface(m_pAnImages[IMG_LED_BLUEON], NULL, m_pScreen, &destOff);

            dest.w = m_pAnImages[IMG_LED_BLUEON]->w;
            dest.h = m_pAnImages[IMG_LED_BLUEON]->h;
            SDL_BlitSurface(m_pAnImages[IMG_LED_BLUEON], NULL, m_pScreen, &dest);
        }
        else
        {
            // loser is red
            destOff.w = m_pAnImages[IMG_LED_REDON]->w;
            destOff.h = m_pAnImages[IMG_LED_REDON]->h;
            SDL_BlitSurface(m_pAnImages[IMG_LED_REDON], NULL, m_pScreen, &destOff);
        }
    }
    else
    {
        // mano was not played (both off)
        dest.w = m_pAnImages[IMG_LEDGREEN_OFF]->w;
        dest.h = m_pAnImages[IMG_LEDGREEN_OFF]->h;
        SDL_BlitSurface(m_pAnImages[IMG_LEDGREEN_OFF], NULL, m_pScreen, &dest);
        destOff.w = m_pAnImages[IMG_LEDGREEN_OFF]->w;
        destOff.h = m_pAnImages[IMG_LEDGREEN_OFF]->h;
        SDL_BlitSurface(m_pAnImages[IMG_LEDGREEN_OFF], NULL, m_pScreen, &destOff);
    }
}


////////////////////////////////////////
//       disableBallons
/*! Disable all ballons
*/
void cGameMainGfx::disableBallons()
{
    for (int i = 0; i < MAX_NUM_PLAYERS; i++)
    {
        m_pbalGfx[i]->Disable();
    }
}


////////////////////////////////////////
//       allBallonAreDisabled
/*! Check if all ballon are disabled
*/
BOOL  cGameMainGfx::allBallonAreDisabled()
{
    BOOL bRet = TRUE;
    for (int i = 0; i < MAX_NUM_PLAYERS; i++)
    {
        BOOL bTemp = m_pbalGfx[i]->GetEnableState();
        if (bTemp)
        {
            // one ballon is enabled
            bRet = FALSE;
            break;
        }
    }
    return bRet;
}


////////////////////////////////////////
//       guiPlayerTurn
/*! Inform that the player have to play using the GUI
// \param int iPlayer :
*/
void cGameMainGfx::guiPlayerTurn(int iPlayer)
{
    ASSERT(m_pMatchPoints);
    m_bPlayerCanPlay = TRUE;
    TRACE("Player can play\n");

    m_iPlayerThatHaveMarkup = iPlayer;

    // update the screen
    drawStaticScene();

}


////////////////////////////////////////
//       showCurrentScore
/*! Show the current match score
*/
void cGameMainGfx::showCurrentScore()
{
    /*
    // mano score
    for (int iManoNum = 0; iManoNum < NUM_CARDS_HAND; iManoNum++)
    {
    BOOL bIsPata;
    BOOL bIsPlayed;
    int iPlayerIx;
    m_pMatchPoints->GetManoInfo(iManoNum, &iPlayerIx, &bIsPlayed, &bIsPata);
    showManoScore(bIsPlayed, iPlayerIx, bIsPata, iManoNum);
    }

    // grid
    int iX1 = 540;
    int iY_oriz = 45;
    int iX_end = iX1 + 240;
    int iX_vertical = iX1 + (iX_end - iX1) / 2;
    int iY1 = iY_oriz - 30;
    int iY_end = iY1 + 300;

    SDL_Rect dest;

    // vertical line
    int i;
    for ( i = iY1; i < iY_end; i += m_pAnImages[IMG_VERTICAL]->h)
    {
    dest.x = iX_vertical - 2;
    dest.y = i;
    dest.w = m_pAnImages[IMG_VERTICAL]->w;
    dest.h = m_pAnImages[IMG_VERTICAL]->h;

    SDL_BlitSurface(m_pAnImages[IMG_VERTICAL], NULL, m_pScreen, &dest);
    }
    // horizontal
    dest.w = m_pAnImages[IMG_HORIZONTAL]->w;
    dest.h = m_pAnImages[IMG_HORIZONTAL]->h;
    for (i = iX1; i < iX_end; i += m_pAnImages[IMG_HORIZONTAL]->w)
    {
    dest.x = i;
    dest.y = iY_oriz;

    SDL_BlitSurface(m_pAnImages[IMG_HORIZONTAL], NULL, m_pScreen, &dest);
    }

    // name on grid
    cPlayer* pPlayer = m_pCoreEngine->GetPlayer(PLAYER1) ;
    STRING strTmp = pPlayer->GetName();
    int iLenName = strTmp.length();
    GFX_UTIL::DrawString(m_pScreen, pPlayer->GetName(), iX_vertical -(9 * iLenName), iY1, GFX_UTIL_COLOR::White, m_pFontText);
    pPlayer = m_pCoreEngine->GetPlayer(PLAYER2) ;
    GFX_UTIL::DrawString(m_pScreen, pPlayer->GetName(), iX_vertical + 10, iY1, GFX_UTIL_COLOR::White, m_pFontText);

    // current giocata score
    eGiocataScoreState eCurrScore =  m_pMatchPoints->GetCurrScore();
    STRING lpsNamePoints = m_MapPunti[eCurrScore];
    if (m_pMatchPoints->IsGiocataMonte())
    {
    lpsNamePoints = m_pLangMgr->GetStringId(cLanguages::ID_S_AMONTE).c_str();
    }
    CHAR buffTmp[256];
    sprintf(buffTmp, "%s: %s", m_pLangMgr->GetStringId(cLanguages::ID_STA_PTCURRENT).c_str(), lpsNamePoints.c_str());
    int tx, ty;
    TTF_SizeText(m_pFontText, buffTmp, &tx, &ty);
    int iX_posCurrScore = iX_vertical - tx/2;
    int iY_posCurrScore = iY_end + 10;
    GFX_UTIL::DrawString(m_pScreen, buffTmp, iX_posCurrScore,
    iY_posCurrScore, GFX_UTIL_COLOR::White, m_pFontText);

    //player score
    int iNumGiocate = m_pMatchPoints->GetNumGiocateInCurrMatch();
    VCT_INT vct_Point_pl1;
    for (int j = 0; j < NUM_PLAY_INVIDO_2; j++)
    {
    vct_Point_pl1.clear();
    for (int iNumGio = 0; iNumGio < iNumGiocate; iNumGio++ )
    {
    cGiocataInfo GioInfo;
    m_pMatchPoints->GetGiocataInfo(iNumGio, &GioInfo);

    if (GioInfo.eScore > 0)
    {
    if (GioInfo.iPlayerIndex == j)
    {
    if (GioInfo.eScore == SC_TRASMAS)
    {
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    }
    else if (GioInfo.eScore == SC_TRASMASNOEF)
    {
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    }
    else if (GioInfo.eScore == SC_FUERAJEUQ)
    {
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    }
    else if (GioInfo.eScore == SC_PARTIDA)
    {
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    vct_Point_pl1.push_back(3);
    }
    else
    {
    vct_Point_pl1.push_back(GioInfo.eScore);
    }

    }
    }
    }
    showPointsPlayer(j, vct_Point_pl1);
    }
    */
}

////////////////////////////////////////
//       enableCmds
/*! Enable available commands
*/
void cGameMainGfx::enableCmds()
{
}


////////////////////////////////////////
//       enableNumButtonsCmd
/*! Enables the buttons for receiving inputs. If the parameter is 0, all buttons are disabled
// \param int iNumButt : number of buttons to be enabled
*/
void    cGameMainGfx::enableNumButtonsCmd(int iNumButt)
{
    int i, j;
    for (i = 0; i < iNumButt; i++)
    {
        // enable buttons with commands
        m_pbtArrayCmd[i]->EnableWindow(TRUE);
        m_pbtArrayCmd[i]->SetState(cButtonGfx::VISIBLE);
    }
    for (j = i; j < NUMOFBUTTON; j++)
    {
        // the rest of buttons are disabled
        m_pbtArrayCmd[j]->EnableWindow(FALSE);
        m_pbtArrayCmd[j]->SetState(cButtonGfx::INVISIBLE);
        m_pbtArrayCmd[j]->SetWindowText("-");
        m_pbtArrayCmd[j]->RedrawButton(m_pScreen, m_pScene_background, m_pScreenTexture);
    }
}

////////////////////////////////////////
//       setCmdButton
/*! Set the command on the button
// \param int iButtonIndex :
// \param eSayPlayer eSay :
// \param LPCSTR strCaption :
*/
void cGameMainGfx::setCmdButton(int iButtonIndex, eSayPlayer eSay, LPCSTR strCaption)
{
    if (iButtonIndex >= 0 && iButtonIndex < NUMOFBUTTON)
    {
        m_pbtArrayCmd[iButtonIndex]->SetWindowText(strCaption);
        m_pbtArrayCmd[iButtonIndex]->RedrawButton(m_pScreen, m_pScene_background, m_pScreenTexture);

    }
    else
    {
        ASSERT(0);
    }
}



////////////////////////////////////////
//       ButCmdClicked
/*! Button clicked callback
// \param int iButID : button id
*/
void cGameMainGfx::ButCmdClicked(int iButID)
{
    if (iButID >= 0 && iButID < NUMOFBUTTON)
    {
        //ASSERT(0);
        if (BUTID_EXIT == iButID)
        {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
        }
        else if (BUTID_INFO == iButID)
        {
            g_MainApp->PickHelp();
        }
    }
}


////////////////////////////////////////
//       NtfyTermEff
/*! Effect playing is terminated
// \param int iCh :
*/
void cGameMainGfx::NtfyTermEff(int iCh)
{
    m_DelayAction.ChangeCurrDelay(50);
}


////////////////////////////////////////
//       lookforDeclGoodGames
/*!
*/
void cGameMainGfx::lookforDeclGoodGames()
{
    VCT_GOODGAMEDETAIL vct_GGRec;
    VCT_CARDINFO vctMyCards;
    for (int j = 0; j < NUM_CARDS_HAND; j++)
    {
        vctMyCards.push_back((*m_aPlayerCards[j].cardSpec.GetCardInfo()));
    }

    // retrives all available good games
    AlgSupport::GetAvailbDeclGoodGames(vctMyCards, vct_GGRec);


    for (UINT i = 0; i < vct_GGRec.size(); i++)
    {
        m_pCoreEngine->DeclareGoodGame(m_iPlayer1Index, vct_GGRec[i].eGGval, vct_GGRec[i].eSManca);
    }


}


// ***************************************************
//********  interface invido core  callback **********
// ***************************************************

////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cGameMainGfx::ALG_Play()
{

    guiPlayerTurn(m_iPlayer1Index);
    if (m_iTrickRound == 0)
    {
        lookforDeclGoodGames();
    }
    m_iTrickRound++;
}


////////////////////////////////////////
//       ALG_Say
/*! player have to responce notification
*/
void cGameMainGfx::ALG_Say()
{
}



////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player say something
// \param int iPlayerIx :
// \param eSayPlayer SaySomeThing :
*/
void cGameMainGfx::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer SaySomeThing)
{
    STRING lpsNameSay = m_pCoreEngine->GetComandString(SaySomeThing);
    if (lpsNameSay.length() == 0)
        return;


    disableBallons();


    Uint32        m_uiShowTick;
    switch (m_iPlAlreadyPlayed)
    {
    case 0:
        m_uiShowTick = 4000;
        break;
    case 1:
        m_uiShowTick = 3500;
        break;
    case 2:
        m_uiShowTick = 3000;
        break;
    case 3:
        m_uiShowTick = 2600;
        break;
    default:
        m_uiShowTick = 2500;
        break;
    }


    m_pbalGfx[iPlayerIx]->StartShow(lpsNameSay.c_str(), m_uiShowTick);


    /*
    if (g_Options.All.bSoundEffect )
    {
    // say also with music
    int iMusId = m_Map_idSynth_Say[SaySomeThing];
    m_pMusicMgr->PlayEffect(iMusId);
    m_DelayAction.CheckPoint(60, cDelayNextAction::CHANGE_AVAIL);
    }
    */
}


////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player  play a card
// \param int iPlayerIx :
// \param CardSpec Card :
*/
void cGameMainGfx::ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard)
{
    // disable ballon
    disableBallons();

    CardSpec Card;
    Card.SetCardInfo(*pCard);

    // markup player that have to play
    cPlayer* pPlayer = 0;

    m_pCoreEngine->GetPlayerInPlaying(&pPlayer);
    ASSERT(pPlayer);

    if (pPlayer)
    {
        m_iPlayerThatHaveMarkup = pPlayer->GetIndex();
    }

    bool bFound = false;
    if (iPlayerIx != m_iPlayer1Index)
    {
        int iOppIx = iPlayerIx - 1;
        // opponent play a card
        for (int iIndex = 0; !bFound && iIndex < NUM_CARDS_HAND; iIndex++)
        {
            if (m_aOpponentCards[iOppIx][iIndex].State == cCardGfx::CSW_ST_BACK)
            {
                m_aOpponentCards[iOppIx][iIndex].State = cCardGfx::CSW_ST_VISIBLE;
                m_aOpponentCards[iOppIx][iIndex].cardSpec = Card;
                TRACE("card played %s\n", Card.GetName());
                drawPlayedCard(&m_aOpponentCards[iOppIx][iIndex], iPlayerIx);
                bFound = true;

            }
        }
        ASSERT(bFound);
        cPlayer* pPlayer = m_pCoreEngine->GetPlayer(iPlayerIx);

    }
    else
    {
        // user player
        // card was played correctly
        for (int iIndex = 0; !bFound && iIndex < NUM_CARDS_HAND; iIndex++)
        {
            if (m_aPlayerCards[iIndex].cardSpec == Card)
            {
                TRACE("card played %s\n", Card.GetName());
                drawPlayedCard(&m_aPlayerCards[iIndex], iPlayerIx);
                bFound = true;

            }
        }
        ASSERT(bFound);

    }

    if (bFound)
    {
        // card was played correctly

        // make a feedback 
        m_pMusicMgr->PlayEffect(cMusicManager::SND_EFC_CLICK);
        int iNumCardPlayed = m_pMatchPoints->GetCurrNumCardPlayed();
        if (iNumCardPlayed == NUM_CARDS_PLAYED)
        {
            // first card played from opponent
            m_DelayAction.CheckPoint(1250, cDelayNextAction::NOCHANGE);

        }
        else
        {
            // opponent was not the first, delay action to show a little the current table
            m_DelayAction.CheckPoint(500, cDelayNextAction::NOCHANGE);
        }
    }
    // increment the number of players that have played
    m_iPlAlreadyPlayed++;
}

////////////////////////////////////////
//       ALG_NewGiocata
/*! Cards are distruited. Draw it.
*/
void cGameMainGfx::ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx)
{
    m_bPlayerCanPlay = FALSE;
    TRACE("Player is blocked\n");

    m_iTrickRound = 0;
    ASSERT(iNumOfCards == NUM_CARDS_HAND);

    // NOTE: to set the cards is better to use pCardArray and not using the core class.
    // Cards of the opponent are not yet set, so we can't display it.
    // This is correct because the Gfx engine operate like a player and not have to 
    // know the opponent cards

    // player

    // store cards in vector for sorting
    VCT_PCARDINFO vctRecCards;
    for (int h = 0; h < iNumOfCards; h++)
    {
        vctRecCards.push_back(&pCardArray[h]);
    }
    // sort the recived card on suit 
    std::sort(vctRecCards.begin(), vctRecCards.end(), cmpCardInfoSuit());
    CardSpec Card;
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        Card.SetCardInfo(*vctRecCards[i]);
        m_aPlayerCards[i].cardSpec = Card;
        m_aPlayerCards[i].State = cCardGfx::CSW_ST_VISIBLE;
    }

    // opponents
    for (int g = 0; g < NUM_OTHER; g++)
    {
        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
            m_aOpponentCards[g][j].State = cCardGfx::CSW_ST_BACK;
        }
    }

    // cards played
    for (int k = 0; k < NUM_CARDS_PLAYED; k++)
    {
        m_CardsTable[k].State = cCardGfx::CSW_ST_INVISIBLE;
    }

    m_vctPlayedCardsGfx.clear();

    if (g_Options.All.bAnimatePlayCard)
    {
        animateBeginGiocata();
    }
    else
    {
        // restore begin scene
        m_DelayAction.CheckPoint(500, cDelayNextAction::CHANGE_AVAIL);
        drawStaticScene();
    }
    // reset counter
    m_iPlAlreadyPlayed = 0;
    // markup to the first player
    cPlayer* pPlayer = 0;
    m_pCoreEngine->GetPlayerInPlaying(&pPlayer);
    ASSERT(pPlayer);

    if (pPlayer)
    {
        m_iPlayerThatHaveMarkup = pPlayer->GetIndex();
    }

}


////////////////////////////////////////
//       ALG_ManoEnd
/*! Mano is terminated
*/
void cGameMainGfx::ALG_ManoEnd(I_MatchScore* pScore)
{

    // wait a little beacuse a ballon could be shown
    // don't use SDL_Delay() because ballons are disabled in drawStaticScene
    Uint32 uiStartTime = SDL_GetTicks();
    Uint32 uiNowTime = uiStartTime;
    Uint32 uiLast_time = uiStartTime;
    while (uiNowTime < uiStartTime + 2000)
    {
        uiNowTime = SDL_GetTicks();
        if (uiNowTime > uiLast_time + 30)
        {
            drawStaticScene();
            uiLast_time = uiNowTime;
        }
        if (allBallonAreDisabled())
        {
            break;
        }
    }


    if (g_Options.All.bBlockOnManoEnd)
    {
        // wait until the user click on mouse or keyboard
        waitOnEvent();
    }


    ASSERT(pScore);
    m_bPlayerCanPlay = FALSE;
    TRACE("Player is blocked\n");

    int iPlayerIx = pScore->GetManoWinner();

    // cards played
    for (int k = 0; k < NUM_CARDS_PLAYED; k++)
    {
        m_CardsTable[k].State = cCardGfx::CSW_ST_INVISIBLE;
    }

    // update the screen
    m_iPlayerThatHaveMarkup = iPlayerIx;
    drawStaticScene();


    if (g_Options.All.bAnimatePlayCard)
    {
        // animate mano end
        animateManoEnd(iPlayerIx);
    }
    m_iPlAlreadyPlayed = 0;



}


////////////////////////////////////////
//       ALG_GiocataEnd
/*! Giocata is terminated
*/
void cGameMainGfx::ALG_GiocataEnd(I_MatchScore* pScore)
{
    int iPlayerIx = pScore->GetGiocataWinner();

    STRING strPuntiTot;

    // giocata with a winner
    CHAR buffText[512];

    int iIndex1 = TEAM_1;
    int iIndex2 = TEAM_2;

    int iNumPl = m_pCoreEngine->GetNumOfPlayers();
    if (iNumPl == 2)
    {
        iIndex2 = PLAYER2;
    }

    cPlayer*  pPlayer_Team1 = m_pCoreEngine->GetPlayer(iIndex1);
    cPlayer*  pPlayer_Team2 = m_pCoreEngine->GetPlayer(iIndex2);

    sprintf(buffText, "%s %s %d, %s %s %d",
        pPlayer_Team1->GetName(),
        m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(),
        pScore->GetPointsPlayer(iIndex1),
        pPlayer_Team2->GetName(),
        m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(),
        pScore->GetPointsPlayer(iIndex2));

    VCT_STRING vct_Text;
    strPuntiTot = buffText;
    STRING strPuntiGio;
    STRING strPuntiAccuse;

    // retrives points of the current giocata
    cGiocataInfo NowInfoGio;
    m_pMatchPoints->GetCurrGiocataInfo(&NowInfoGio);
    // build the message
    sprintf(buffText, "%s %s %d, %s %s %d",
        pPlayer_Team1->GetName(),
        m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(),
        NowInfoGio.iPointsTeam_1,
        pPlayer_Team2->GetName(),
        m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(),
        NowInfoGio.iPointsTeam_2);

    strPuntiGio = buffText;

    // points of current giocata
    vct_Text.push_back(m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTIGIOCATA));
    vct_Text.push_back(strPuntiGio);
    vct_Text.push_back("");

    // points of good game declarations
    if (g_Options.Match.bUseGoodGameDecla)
    {
        // build the message
        sprintf(buffText, "%s %s %d, %s %s %d",
            pPlayer_Team1->GetName(),
            m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(),
            NowInfoGio.iAccusePointTeam_1,
            pPlayer_Team2->GetName(),
            m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(),
            NowInfoGio.iAccusePointTeam_2);

        strPuntiAccuse = buffText;

        vct_Text.push_back(m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTIACCUSE));
        vct_Text.push_back(strPuntiAccuse);
        vct_Text.push_back("");
    }

    // total points
    vct_Text.push_back(m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTITOT));
    vct_Text.push_back(strPuntiTot);

    STRING strPartitaEndOn;
    sprintf(buffText, "%s %d",
        m_pLangMgr->GetStringId(cLanguages::ID_PUNTIMATCH_GOAL).c_str(),
        g_Options.Match.iScoreGoal);
    strPartitaEndOn = buffText;
    vct_Text.push_back("");
    vct_Text.push_back("");
    vct_Text.push_back(strPartitaEndOn);

    m_bPlayerCanPlay = FALSE;
    TRACE("Player is blocked\n");

    // draw a background and scene
    drawStaticScene();
    // little animation
    animGiocataEnd(iPlayerIx);

    // show results in a multiline messagebox 
    showResultMsgBox(vct_Text);
}


////////////////////////////////////////
//       ALG_MatchEnd
/*! Match is end
*/
void cGameMainGfx::ALG_MatchEnd(I_MatchScore* pScore)
{

    int iPlayerIx = pScore->GetMatchWinner();
    int iPlayLoser;
    if (iPlayerIx == m_iPlayer1Index)
    {
        iPlayLoser = m_iOpponentIndex;
    }
    else
    {
        iPlayLoser = m_iPlayer1Index;
    }
    cPlayer* pPlayer = m_pCoreEngine->GetPlayer(iPlayerIx);
    cPlayer* pPlLoser = m_pCoreEngine->GetPlayer(iPlayLoser);
    m_bPlayerCanPlay = FALSE;
    TRACE("Player is blocked\n");

    // partita finita. player vince x:x
    CHAR buff[256];

    sprintf(buff, "%s. %s %s  %d : %d.", m_pLangMgr->GetStringId(cLanguages::ID_CP_PARTITAFIN).c_str(), pPlayer->GetName(),
        m_pLangMgr->GetStringId(cLanguages::ID_CP_VINCE).c_str(),
        pScore->GetPointsPlayer(iPlayerIx), pScore->GetPointsPlayer(iPlayLoser));


    drawStaticScene();

    showOkMsgBox(buff);

    m_bMatchTerminated = TRUE;
}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*! giocata score changed
// \param eGiocataScoreState eNewScore :
*/
void cGameMainGfx::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{


}


////////////////////////////////////////
//       ALG_PLayerSaidFalse
/*!
// \param int iPlayerIx :
*/
void cGameMainGfx::ALG_PLayerSaidFalse(int iPlayerIx)
{

}


////////////////////////////////////////
//       ALG_PLayerDeclareGoodGame
/*! Display a call of a good game
// \param int iPlayerIx : player that make the good game
// \param eDeclGoodGame eValgg : good game value
// \param eSUIT eValsuit : suit to complete the declaration
*/
void cGameMainGfx::ALG_PLayerDeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg, eSUIT eValsuit)
{
    STRING strTmp;
    STRING strTmp1;

    // we need a word sbaglia or senza
    STRING strSenza;
    if (m_pCoreEngine->GetLocalType() == LT_BREDA)
    {
        strSenza = m_pLangMgr->GetStringId(cLanguages::ID_A_SBAGLIA);
    }
    else
    {
        strSenza = m_pLangMgr->GetStringId(cLanguages::ID_A_SENZA);
    }


    switch (eValgg)
    {
    case TRE_TRE:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_TRETRE);
        break;
    case TRE_DUE:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_TREDUE);
        break;
    case TRE_ASSI:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_TREASSI);
        break;
    case QUATTRO_TRE:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_4TRE);
        strSenza = "";
        break;
    case QUATTRO_DUE:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_4DUE);
        strSenza = "";
        break;
    case QUATTRO_ASSI:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_4ASSI);
        strSenza = "";
        break;
    case NAPOLETANA:
        strTmp = m_pLangMgr->GetStringId(cLanguages::ID_A_NAPOLA);
        strSenza = "";
        break;
    default:
        ASSERT(0);
        break;
    }
    switch (eValsuit)
    {
    case BASTONI:
        strTmp1 = m_pLangMgr->GetStringId(cLanguages::ID_A_BASTONI);
        break;
    case COPPE:
        strTmp1 = m_pLangMgr->GetStringId(cLanguages::ID_A_COPPE);
        break;
    case DENARI:
        strTmp1 = m_pLangMgr->GetStringId(cLanguages::ID_A_DENARI);
        break;
    case SPADE:
        strTmp1 = m_pLangMgr->GetStringId(cLanguages::ID_A_SPADE);
        break;
    default:
        strTmp1 = "";
        break;
    }


    STRING strLine;
    if (strSenza.length() > 0)
    {
        strLine = strTmp + " " + strSenza + " " + strTmp1;
    }
    else
    {
        strLine = strTmp + " " + strTmp1;
    }
    showDeclarMsgBox(iPlayerIx, strLine.c_str());
}

////////////////////////////////////////
//       INP_PlayerSay
/*!
// \param eSayPlayer eSay :
*/
void cGameMainGfx::INP_PlayerSay(eSayPlayer eSay)
{
    m_pCoreEngine->Player_saySomething(m_iPlayer1Index, eSay);
}
