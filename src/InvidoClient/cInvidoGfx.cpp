// cInvidoGfx.cpp
#pragma warning(disable:4786)

#include "StdAfx.h"
#include "win_type_global.h"

#include <stdio.h>
#include <SDL_image.h>
#include <SDL_endian.h>

#include "cDelayNextAction.h"
#include "cInvidoGfx.h"
#include "gfx_util.h"
#include "AppGfx.h"
#include "cTipoDiMazzo.h"
#include "InvidoSettings.h"
#include "cButtonGfx.h"
#include <time.h>
#include "Languages.h"
#include "cBalloonGfx.h"
#include "cMesgBoxGfx.h"
#include "cMusicManager.h"
#include "cPopUpMenuGfx.h"

#define FPS (1000 / 30)

static const char* lpszImageDir = "data/images/";
static const char* lpszImageBack = "im000740.jpg";
static const char* lpszMazziDir = "data/mazzi/";
static const char* lpszFontConsoleImg = "data/images/ConsoleFont.png";
static const char* lpszaImage_filenames[cInvidoGfx::NUM_ANIMAGES] =
{
    "data/images/tocca.png",
    "data/images/LedOff.bmp",
    "data/images/LedOn.bmp",
    "data/images/canela.bmp",
    "data/images/uovo.bmp",
    "data/images/vertical.png",
    "data/images/cornerdl.png",
    "data/images/cornerdr.png",
    "data/images/cornerul.png",
    "data/images/cornerur.png",
    "data/images/horizontal.png",
    "data/images/LedOnBlue.bmp",
    "data/images/LedOnRed.bmp",
    "data/images/canela_obl.bmp",
    "data/images/balloon_body.pcx",
    "data/images/balloon_up.pcx"
};

static const char* lpszCST_INFO = "[INFO]";
static const char* lpszCST_SCORE = "[SCORE]";
static const char* lpszCST_SU = "[SU]";

//invido core
cInvidoCore*  g_pInvidoCore;

static cInvidoGfx* g_stacInvidoGfx = 0;

////////////////////////////////////////
//       fnEffectTer
/*! Effect terminated notification of music manager
// \param int iCh :
*/
void fnEffectTer(int iCh)
{
    // do something
    ASSERT(g_stacInvidoGfx);
    g_stacInvidoGfx->NtfyTermEff(iCh);
}


////////////////////////////////////////
//       cInvidoGfx
/*! constructor
*/
cInvidoGfx::cInvidoGfx(AppGfx*  pApp)
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
    m_pFontStatus = 0;
    m_pDeckType = 0;

    for (int i = 0; i < NUM_ANIMAGES; i++)
    {
        m_pAnImages[i] = 0;
    }
    m_pMatchPoints = 0;
    m_pInvidoCore = 0;
    m_bPlayerCanPlay = FALSE;
    m_iPlayerThatHaveMarkup = 0;
    for (int j = 0; j < NUMOFBUTTON; j++)
    {
        m_pbtArrayCmd[0] = 0;
    }
    m_pLangMgr = 0;
    m_pMusicMgr = 0;
    g_stacInvidoGfx = this;
    m_bMatchTerminated = FALSE;
    m_pAlphaDisplay = 0;
}


////////////////////////////////////////
//       ~cInvidoGfx
/*! Destructor
*/
cInvidoGfx::~cInvidoGfx()
{
    cleanup();
}

void cInvidoGfx::Initialize(SDL_Surface *pScreen, SDL_Renderer* pRender, SDL_Texture* pScreenTexture)
{
    m_psdlRenderer = pRender;
    m_pScreen = pScreen;
    m_pScreenTexture = pScreenTexture;

    cleanup();
    CHAR ErrBuff[512];

    cLanguages* pLangMgr = m_pApp->GetLanguageMan();
    m_pLangMgr = pLangMgr;

    // points name
    m_MapPunti[SC_PATTA] = pLangMgr->GetStringId(cLanguages::ID_S_PATA).c_str();
    m_MapPunti[SC_CANELA] = pLangMgr->GetStringId(cLanguages::ID_S_CANELA).c_str();
    m_MapPunti[SC_INVIDO] = pLangMgr->GetStringId(cLanguages::ID_S_INVIDO).c_str();
    m_MapPunti[SC_TRASMAS] = pLangMgr->GetStringId(cLanguages::ID_S_TRASMAS).c_str();
    m_MapPunti[SC_TRASMASNOEF] = pLangMgr->GetStringId(cLanguages::ID_S_TRASMASNOEF).c_str();
    m_MapPunti[SC_FUERAJEUQ] = pLangMgr->GetStringId(cLanguages::ID_S_FUERAJEUQ).c_str();
    m_MapPunti[SC_PARTIDA] = pLangMgr->GetStringId(cLanguages::ID_S_PARTIDA).c_str();

    // buttons  strings
    m_Map_bt_Say[AMONTE] = pLangMgr->GetStringId(cLanguages::ID_S_BT_AMONTE).c_str();
    m_Map_bt_Say[INVIDO] = pLangMgr->GetStringId(cLanguages::ID_S_BT_INVIDO).c_str();
    m_Map_bt_Say[TRASMAS] = pLangMgr->GetStringId(cLanguages::ID_S_BT_TRASMAS).c_str();
    m_Map_bt_Say[TRASMASNOEF] = pLangMgr->GetStringId(cLanguages::ID_S_BT_TRASMASNOEF).c_str();
    m_Map_bt_Say[FUERAJEUQ] = pLangMgr->GetStringId(cLanguages::ID_S_BT_FUERAJEUQ).c_str();
    m_Map_bt_Say[PARTIDA] = pLangMgr->GetStringId(cLanguages::ID_S_BT_PARTIDA).c_str();
    m_Map_bt_Say[VABENE] = pLangMgr->GetStringId(cLanguages::ID_S_BT_VABENE).c_str();
    m_Map_bt_Say[VADOVIA] = pLangMgr->GetStringId(cLanguages::ID_S_BT_VADOVIA).c_str();
    m_Map_bt_Say[CHIAMADIPIU] = pLangMgr->GetStringId(cLanguages::ID_S_BT_CHIAMADIPIU).c_str();
    m_Map_bt_Say[NO] = pLangMgr->GetStringId(cLanguages::ID_S_BT_NO).c_str();
    m_Map_bt_Say[GIOCA] = pLangMgr->GetStringId(cLanguages::ID_S_BT_GIOCA).c_str();
    m_Map_bt_Say[VADODENTRO] = pLangMgr->GetStringId(cLanguages::ID_S_BT_VADODENTRO).c_str();
    m_Map_bt_Say[CHIAMA_BORTOLO] = pLangMgr->GetStringId(cLanguages::ID_S_BT_CHIAMA_BORTOLO).c_str();
    m_Map_bt_Say[NOTHING] = "";

    // say strings
    m_Map_fb_Say[AMONTE] = pLangMgr->GetStringId(cLanguages::ID_S_AMONTE).c_str();
    m_Map_fb_Say[INVIDO] = pLangMgr->GetStringId(cLanguages::ID_S_INVIDO).c_str();
    m_Map_fb_Say[TRASMAS] = pLangMgr->GetStringId(cLanguages::ID_S_TRASMAS).c_str();
    m_Map_fb_Say[TRASMASNOEF] = pLangMgr->GetStringId(cLanguages::ID_S_TRASMASNOEF).c_str();
    m_Map_fb_Say[FUERAJEUQ] = pLangMgr->GetStringId(cLanguages::ID_S_FUERAJEUQ).c_str();
    m_Map_fb_Say[PARTIDA] = pLangMgr->GetStringId(cLanguages::ID_S_PARTIDA).c_str();
    m_Map_fb_Say[VABENE] = pLangMgr->GetStringId(cLanguages::ID_S_VABENE).c_str();
    m_Map_fb_Say[VADOVIA] = pLangMgr->GetStringId(cLanguages::ID_S_VADOVIA).c_str();
    m_Map_fb_Say[CHIAMADIPIU] = pLangMgr->GetStringId(cLanguages::ID_S_CHIAMADIPIU).c_str();
    m_Map_fb_Say[NO] = pLangMgr->GetStringId(cLanguages::ID_S_NO).c_str();
    m_Map_fb_Say[GIOCA] = pLangMgr->GetStringId(cLanguages::ID_S_GIOCA).c_str();
    m_Map_fb_Say[VADODENTRO] = pLangMgr->GetStringId(cLanguages::ID_S_VADODENTRO).c_str();

    // sound call echo player
    m_Map_id_EchoSay[AMONTE] = cMusicManager::SND_IG_MONTE_NORM;
    m_Map_id_EchoSay[INVIDO] = cMusicManager::SND_IG_INV_NORM;
    m_Map_id_EchoSay[TRASMAS] = cMusicManager::SND_IG_TRASMAS;
    m_Map_id_EchoSay[TRASMASNOEF] = cMusicManager::SND_IG_TRASNOEF;
    m_Map_id_EchoSay[FUERAJEUQ] = cMusicManager::SND_IG_FUORIGIOCO;
    m_Map_id_EchoSay[PARTIDA] = cMusicManager::SND_IG_PARTIDA;
    m_Map_id_EchoSay[VABENE] = cMusicManager::SND_IG_VABENE;
    m_Map_id_EchoSay[VADOVIA] = cMusicManager::SND_IG_VUVIA;
    m_Map_id_EchoSay[CHIAMADIPIU] = cMusicManager::SND_IG_CHIAMAPIU;
    m_Map_id_EchoSay[NO] = cMusicManager::SND_IG_NO;
    m_Map_id_EchoSay[GIOCA] = cMusicManager::SND_IG_GIOCA;
    m_Map_id_EchoSay[CHIAMA_BORTOLO] = cMusicManager::SND_IG_BORTOLO;
    //sound synth opponent
    m_Map_idSynth_Say[AMONTE] = cMusicManager::SND_WAV_SYF_MONTE;
    m_Map_idSynth_Say[INVIDO] = cMusicManager::SND_WAV_SYF_INVIDO;
    m_Map_idSynth_Say[TRASMAS] = cMusicManager::SND_WAV_SYF_TRASMAS;
    m_Map_idSynth_Say[TRASMASNOEF] = cMusicManager::SND_WAV_SYF_NOEF;
    m_Map_idSynth_Say[FUERAJEUQ] = cMusicManager::SND_WAV_SYF_FUORIGI;
    m_Map_idSynth_Say[PARTIDA] = cMusicManager::SND_WAV_SYF_PARTIDA;
    m_Map_idSynth_Say[VABENE] = cMusicManager::SND_WAV_SYF_VABENE;
    m_Map_idSynth_Say[VADOVIA] = cMusicManager::SND_WAV_SYF_VUVIA;
    m_Map_idSynth_Say[CHIAMADIPIU] = cMusicManager::SND_WAV_SYF_CHIADIPIU;

    m_Map_idSynth_Say[NO] = cMusicManager::SND_WAV_SYF_NO;
    m_Map_idSynth_Say[GIOCA] = cMusicManager::SND_WAV_SYF_GIOCA;



    m_pDeckType = new cTipoDiMazzo;
    m_pDeckType->SetTypeIndex(g_Options.All.iTipoMazzo);
    // init deck with all  images of the cards
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
        if (i == IMG_CORNER_DL || i == IMG_CORNER_DR || i == IMG_CORNER_UL || i == IMG_CORNER_UR ||
            i == IMG_TOCCA_PLAYER)
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
        SDL_SetColorKey(m_pAnImages[i], TRUE, SDL_MapRGB(m_pAnImages[i]->format, rr, gg, bb)); // SDL 2.0
    }

    // command buttons
    if (m_pbtArrayCmd[0] == 0)
    {
        SDL_Rect rctBt;
        rctBt.w = 120;
        rctBt.h = 28;
        rctBt.y = m_pScreen->h - 155 - rctBt.h - 20;
        int iXButInit = m_pScreen->w - rctBt.w - 20;

        for (i = 0; i < NUMOFBUTTON; i++)
        {
            rctBt.x = iXButInit - i * (rctBt.w + 10);
            m_pbtArrayCmd[i] = new cButtonGfx;
            m_pbtArrayCmd[i]->Init(&rctBt, m_pScreen, m_pFontStatus, i, m_psdlRenderer);
            // delegate
            m_pbtArrayCmd[i]->m_fncbClickEvent = MakeDelegate(this, &cInvidoGfx::ButCmdClicked);
        }
    }

    // ballon
    SDL_Rect destWIN;
    destWIN.x = 320;
    destWIN.y = 100;
    destWIN.w = m_pAnImages[IMG_BALLOON]->w;
    destWIN.h = m_pAnImages[IMG_BALLOON]->h;
    m_pbalGfx = new cBalloonGfx;
    m_pbalGfx->Init(destWIN, m_pAnImages[IMG_BALLOON], m_pFontStatus, 200);
    m_pbalGfx->SetStyle(cBalloonGfx::ARROW_UP, m_pAnImages[IMG_BALL_ARROW_UP]);

    // music manager
    m_pMusicMgr = m_pApp->GetMusicManager();

    // messagebox background surface
    m_pAlphaDisplay = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);

}


////////////////////////////////////////
//       cleanup
/*! Free all allocated resources
*/
void cInvidoGfx::cleanup()
{
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
    if (m_pDeckType)
    {
        delete m_pDeckType;
        m_pDeckType = NULL;
    }
    if (m_pAlphaDisplay)
    {
        SDL_FreeSurface(m_pAlphaDisplay);
        m_pAlphaDisplay = NULL;
    }

}

////////////////////////////////////////
//       drawStaticScene
/*! Draw the table, included all cards, status, chat
*/
void cInvidoGfx::drawStaticScene()
{
    if (m_pScene_background)
    {
        SDL_BlitSurface(m_pScene_background, NULL, m_pScreen, NULL);
    }

    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        renderCard(&m_aOpponentCards[i]);
        renderCard(&m_aPlayerCards[i]);
    }
    for (int k = 0; k < NUM_CARDS_PLAYED; k++)
    {
        renderCard(&m_CardsTable[k]);
    }

    showPlayerMarkup(m_iPlayerThatHaveMarkup);

    // shows names
    renderPlayerName(PLAYER1);
    renderPlayerName(PLAYER2);

    // show score (leds and points)
    showCurrentScore();

    // draw command buttons
    for (int j = 0; j < NUMOFBUTTON; j++)
    {
        m_pbtArrayCmd[j]->DrawButton(m_pScreen);
    }

    // ballon
    m_pbalGfx->Draw(m_pScreen);

    SDL_RenderClear(m_psdlRenderer);
    SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); // sdl 2.0
    SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
    SDL_RenderPresent(m_psdlRenderer);
}


////////////////////////////////////////
//       renderCard
/*! Render a card gfx
// \param cCardGfx* pCard : pointer to the card
*/
void cInvidoGfx::renderCard(cCardGfx* pCard)
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
void cInvidoGfx::renderPlayerName(int iPlayerIx)
{
    cPlayer* pPlayer = m_pInvidoCore->GetPlayer(iPlayerIx);

    char txt_to_render[256];
    static char un_char = ' ';

    if (iPlayerIx == PLAYER2)
    {
        sprintf(txt_to_render, "%s", pPlayer->GetName());
        GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, 150, 25, 310, 17, m_pSurf_Bar);
        GFX_UTIL::DrawString(m_pScreen, txt_to_render, 315, 21, GFX_UTIL_COLOR::White, m_pFontText, false);
    }
    else if (iPlayerIx == PLAYER1)
    {
        sprintf(txt_to_render, "%s", pPlayer->GetName());
        GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, 150, 25, 310, m_pScreen->h - 35, m_pSurf_Bar);
        GFX_UTIL::DrawString(m_pScreen, txt_to_render, 315, m_pScreen->h - 31, GFX_UTIL_COLOR::White, m_pFontText, true);
    }
    else
    {
        ASSERT(0);
    }

}


////////////////////////////////////////
//       initDeck
/*! Inizializza il mazzo
*/
int cInvidoGfx::initDeck()
{
    // load deck from pac file
    if (m_pDeck == NULL)
    {
        loadCardPac();
    }

    // use assert because if loadCardPac failed an exception is thrown
    ASSERT(m_pDeck)

        m_SrcBack.x = 0;
    m_SrcBack.y = 0;

    m_SrcCard.y = 0;
    m_SrcCard.w = m_iCardWidth;
    m_SrcCard.h = m_iCardHeight;

    // symbols

    std::string strFileSymbName = lpszMazziDir;
    strFileSymbName += m_pDeckType->GetSymbolFileName();

    m_pSymbols = SDL_LoadBMP(strFileSymbName.c_str());

    if (m_pSymbols == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Error on load deck file (symbols) %s", strFileSymbName.c_str());
        throw Error::Init(ErrBuff);
    }

    if (m_pDeckType->GetSymbolFileName() == "symb_336.bmp")
    {
        SDL_SetColorKey(m_pSymbols, TRUE, SDL_MapRGB(m_pSymbols->format, 242, 30, 206)); // SDL 2.0
    }
    else
    {
        SDL_SetColorKey(m_pSymbols, TRUE, SDL_MapRGB(m_pSymbols->format, 0, 128, 0)); // SDL 2.0
    }

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
void cInvidoGfx::createRegionsInit()
{
    // opponent cards
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_aOpponentCards[i].m_iX = (m_iCardWidth * i) + ((i + 1) * 17);
        m_aOpponentCards[i].m_iY = 10;
        m_aOpponentCards[i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_aOpponentCards[i].SetSymbSurf(m_pSymbols, m_iSymbolWidth, m_iSymbolHeigth);
    }

    // player cards
    for (int k = 0; k < NUM_CARDS_HAND; k++)
    {
        m_aPlayerCards[k].m_iX = (m_iCardWidth * k) + ((k + 1) * 17);
        m_aPlayerCards[k].m_iY = m_iCardHeight * 3 + 10;
        m_aPlayerCards[k].SetCardInfo(k, m_iCardWidth, m_iCardHeight);
        m_aPlayerCards[k].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_aPlayerCards[k].SetSymbSurf(m_pSymbols, m_iSymbolWidth, m_iSymbolHeigth);
    }

    // cards played
    for (int g = 0; g < NUM_CARDS_PLAYED; g++)
    {
        m_CardsTable[g].m_iX = (m_iCardWidth * (2 - 1)) + ((2 + g * 3) * 17);
        m_CardsTable[g].m_iY = m_iCardHeight * 2 - m_iCardHeight / 2 + 10;
        m_CardsTable[g].State = cCardGfx::CSW_ST_INVISIBLE;
        m_CardsTable[g].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
        m_CardsTable[g].SetSymbSurf(m_pSymbols, m_iSymbolWidth, m_iSymbolHeigth);
    }
}


////////////////////////////////////////
//       animateBeginGiocata
/*! Animation new giocata (card distribution)
*/
void cInvidoGfx::animateBeginGiocata()
{
    TRACE("animateBeginGiocata - begin\n");
    Uint32 uiTickTot = 0;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    cCardGfx cardTmp[NUM_CARDS_HAND];
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        cardTmp[i].Copy(&m_aPlayerCards[i]);
        cardTmp[i].m_iY = 40;
        cardTmp[i].SetDeckSurface(m_pDeck, m_iCardWidth, m_iCardHeight);
    }
    cardTmp[0].m_iX = 10;
    cardTmp[1].m_iX = 10;
    cardTmp[2].m_iX = 10;
    int yspeed = 0;
    int xspeed = 0;
    int GRAVITY = 1;
    BOOL bEnd = FALSE;
    do
    {
        // clear screen
        SDL_BlitSurface(m_pScene_background, NULL, m_pScreen, NULL);

        for (int iManoNum = 0; iManoNum < NUM_CARDS_HAND; iManoNum++)
        {
            if (iManoNum == 0)
            {
                if (cardTmp[iManoNum].m_iX > m_aPlayerCards[NUM_CARDS_HAND - 1].m_iX +
                    m_aPlayerCards[NUM_CARDS_HAND - 1].m_iWidth)
                {
                    // go back on x
                    xspeed = -6;
                }
                yspeed = yspeed + GRAVITY;
                xspeed = xspeed + GRAVITY;
            }
            cardTmp[iManoNum].m_iX += xspeed;
            cardTmp[iManoNum].m_iY += yspeed;

            if (cardTmp[iManoNum].m_iY >= m_aPlayerCards[iManoNum].m_iY)
            {
                // ok the card reach the position
                cardTmp[iManoNum].m_iY = m_aPlayerCards[iManoNum].m_iY;
                cardTmp[iManoNum].m_iX = m_aPlayerCards[iManoNum].m_iX;
                //uiTickTot
                bEnd = TRUE;
            }

            // update card position
            cardTmp[iManoNum].DrawCard(m_pScreen);
        }
        SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); // sdl 2.0
        SDL_RenderClear(m_psdlRenderer);
        SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
        SDL_RenderPresent(m_psdlRenderer);

        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();
        uiTickTot = uiNowTime - uiInitialTick;
        if (uiNowTime < uiLast_time + FPS)
        {
            SDL_Delay(uiLast_time + FPS - uiNowTime);
            uiLast_time = uiNowTime;
        }
    } while (uiTickTot < 1500);

    TRACE("animateBeginGiocata - end\n");

    // restore previous scene
    drawStaticScene();

}

////////////////////////////////////////
//       animateManoEnd
/*! Animate mano end. Move played cards together and than move it to the trick winner.
// \param int iPlayerIx : player that win the trick
*/
void cInvidoGfx::animateManoEnd(int iPlayerIx)
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


    // move on x
    cardTmp[0].m_iVy = 0;
    cardTmp[0].m_iVx = +iPhase1Speed;
    cardTmp[1].m_iVy = 0;
    cardTmp[1].m_iVx = -iPhase1Speed;

    // freeze the current display used as background
    SDL_Surface* pCurrentDisplay = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w,
        m_pScreen->h, 32, 0, 0, 0, 0);

    SDL_BlitSurface(m_pScreen, NULL, pCurrentDisplay, NULL);


    BOOL bEnd = FALSE;
    BOOL bPhase1_X = FALSE;
    int loopCount = 0;
    SDL_Texture* pTextureAlphaDisplay = SDL_CreateTextureFromSurface(m_psdlRenderer, m_pAlphaDisplay);
    do
    {
        // clear screen
        SDL_BlitSurface(pCurrentDisplay, NULL, m_pAlphaDisplay, NULL);

        for (int iCardPlayedIndex = 0; iCardPlayedIndex < NUM_CARDS_PLAYED; iCardPlayedIndex++)
        {

            cardTmp[iCardPlayedIndex].m_iX += cardTmp[iCardPlayedIndex].m_iVx;
            cardTmp[iCardPlayedIndex].m_iY += cardTmp[iCardPlayedIndex].m_iVy;

            if (cardTmp[iCardPlayedIndex].State == cCardGfx::CSW_ST_VISIBLE)
            {
                // update card position
                cardTmp[iCardPlayedIndex].DrawCard(m_pAlphaDisplay);
            }
        }
        if (!bPhase1_X && cardTmp[1].m_iX <= cardTmp[0].m_iX)
        {
            // ok the card reach the central position
            cardTmp[0].m_iVx = 0;
            cardTmp[1].m_iVx = 0;
            bPhase1_X = TRUE;
        }

        SDL_BlitSurface(m_pAlphaDisplay, NULL, m_pScreen, NULL);
        //SDL_Flip(m_pScreen); //SDL 1.2
        SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); // sdl 2.0
        SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
        SDL_RenderPresent(m_psdlRenderer);

        int iIncVel = iPhase2Speed;

        if (bPhase1_X)
        {
            // second step, move cards to the trick winner
            if (iPlayerIx == 0)
            {
                cardTmp[0].m_iVy += iIncVel;
                cardTmp[1].m_iVy += iIncVel;
                if (cardTmp[1].m_iY >= m_pScreen->h)
                {
                    // cards outside of the screen
                    bEnd = TRUE;
                }
            }
            else if (iPlayerIx == 1)
            {
                cardTmp[0].m_iVy -= iIncVel;
                cardTmp[1].m_iVy -= iIncVel;
                if (cardTmp[0].m_iY <= 0)
                {
                    // cards outside of the screen
                    bEnd = TRUE;
                }
            }
            else
            {
                // patada
                cardTmp[0].m_iVx -= iIncVel;
                cardTmp[1].m_iVx -= iIncVel;
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
        loopCount += 1;
        if (loopCount > 100) {
            bEnd = TRUE;
        }
        //} while (uiTickTot < 2000 && !bEnd);
    } while (!bEnd);

    SDL_FreeSurface(pCurrentDisplay);
}


////////////////////////////////////////
//       animGiocataEnd
/*! Shows a little animation because giocata is terminated.
// \param int iPlayerIx : Player that wons the giocata
*/
void cInvidoGfx::animGiocataEnd(int iPlayerIx, BOOL bIsPata)
{
    int iTickTot = 0;
    int iTickFlashDiff = 0;
    SDL_Rect destWIN;
    SDL_Rect destLOS;
    BOOL bFlash = TRUE;
    int iCooYA = m_pScreen->h - 30;;
    int iCooYB = 20;

    if (iPlayerIx == PLAYER1)
    {
        destWIN.y = iCooYA;
        destLOS.y = iCooYB;
    }
    else
    {
        destWIN.y = iCooYB;
        destLOS.y = iCooYA;
    }

    int iInitialTick = SDL_GetTicks();
    int iFlashTickStart = iInitialTick;
    do
    {
        for (int iManoNum = 0; iManoNum < NUM_CARDS_HAND; iManoNum++)
        {
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL))
            {
                return; // stop the animation
            }

            // this is the only value to be changed if leds are moved
            destWIN.x = 400 + 16 * iManoNum;
            destLOS.x = destWIN.x;

            if (bFlash)
            {
                // winner is  ON
                destWIN.w = m_pAnImages[IMG_LEDGREEN_ON]->w;
                destWIN.h = m_pAnImages[IMG_LEDGREEN_ON]->h;
                SDL_BlitSurface(m_pAnImages[IMG_LEDGREEN_ON], NULL, m_pScreen, &destWIN);

            }
            else
            {
                // winner  off for flashing
                destWIN.w = m_pAnImages[IMG_LEDGREEN_OFF]->w;
                destWIN.h = m_pAnImages[IMG_LEDGREEN_OFF]->h;
                SDL_BlitSurface(m_pAnImages[IMG_LEDGREEN_OFF], NULL, m_pScreen, &destWIN);
            }

            if (!bIsPata)
            {
                // loser is red, not flash
                destLOS.w = m_pAnImages[IMG_LED_REDON]->w;
                destLOS.h = m_pAnImages[IMG_LED_REDON]->h;
                SDL_BlitSurface(m_pAnImages[IMG_LED_REDON], NULL, m_pScreen, &destLOS);
            }
            else
            {
                // giocata patada
                if (bFlash)
                {
                    // players are  ON
                    destLOS.w = m_pAnImages[IMG_LED_BLUEON]->w;
                    destLOS.h = m_pAnImages[IMG_LED_BLUEON]->h;
                    SDL_BlitSurface(m_pAnImages[IMG_LED_BLUEON], NULL, m_pScreen, &destLOS);

                    destWIN.w = m_pAnImages[IMG_LED_BLUEON]->w;
                    destWIN.h = m_pAnImages[IMG_LED_BLUEON]->h;
                    SDL_BlitSurface(m_pAnImages[IMG_LED_BLUEON], NULL, m_pScreen, &destWIN);

                }
                else
                {
                    // players also off
                    destLOS.w = m_pAnImages[IMG_LEDGREEN_OFF]->w;
                    destLOS.h = m_pAnImages[IMG_LEDGREEN_OFF]->h;
                    SDL_BlitSurface(m_pAnImages[IMG_LEDGREEN_OFF], NULL, m_pScreen, &destLOS);
                }
            }



        }
        SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); // sdl 2.0
        SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
        SDL_RenderPresent(m_psdlRenderer);

        int iNowTick = SDL_GetTicks();
        iTickFlashDiff = iNowTick - iFlashTickStart;
        if (iTickFlashDiff > 90)
        {
            bFlash = bFlash ? FALSE : TRUE;
            iFlashTickStart = iNowTick;
        }
        iTickTot = iNowTick - iInitialTick;
    } while (iTickTot < 1000);
}


////////////////////////////////////////
//       animateCards
/*! Shows a little animation.
*/
int cInvidoGfx::animateCards()
{
    srand((unsigned)time(NULL));

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
            SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); // sdl 2.0
            SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
            SDL_RenderPresent(m_psdlRenderer);
        } while ((cardGfx.m_iX + 73 > 0) && (cardGfx.m_iX < m_pScreen->w));
    } while (1);

    return 0;
}

////////////////////////////////////////
//       showOkMsgBox
/*! Show an ok messge box
*/
void cInvidoGfx::showOkMsgBox(LPCSTR strText)
{
    // prepare the size of the box
    cMesgBoxGfx   MsgBox;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w - 100;
    rctBox.h = 130;
    rctBox.y = (m_pScreen->h - rctBox.h) / 2;
    rctBox.x = (m_pScreen->w - rctBox.w) / 2;

    MsgBox.Init(&rctBox, m_pScreen, m_pFontStatus, cMesgBoxGfx::MBOK, m_psdlRenderer);
    MsgBox.Show(m_pScreen, "Ok", "", strText);
}

////////////////////////////////////////
//       loadCardPac
/*! Carica il mazzo delle carte dal file in formato pac
*/
int cInvidoGfx::loadCardPac()
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
//       showYesNoMsgBox
/*! Show yes/no message box
// \param LPCSTR strText : Content of the messagebox
\return :1 for yes
\return :0 for no
*/
int  cInvidoGfx::showYesNoMsgBox(LPCSTR strText)
{
    ASSERT(m_pAlphaDisplay);

    // prepare the size of the box
    cMesgBoxGfx   MsgBox;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w - 100;
    rctBox.h = 130;
    rctBox.y = (m_pScreen->h - rctBox.h) / 2;
    rctBox.x = (m_pScreen->w - rctBox.w) / 2;

    // show a mesage box with alpha
    MsgBox.Init(&rctBox, m_pScreen, m_pFontStatus, cMesgBoxGfx::MB_YES_NO, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);

    STRING strTextYes = m_pLangMgr->GetStringId(cLanguages::ID_YES);
    STRING strTextNo = m_pLangMgr->GetStringId(cLanguages::ID_NO);
    int iRes = MsgBox.Show(m_pAlphaDisplay, strTextYes.c_str(), strTextNo.c_str(), strText);

    return iRes;
}


////////////////////////////////////////
//       InitInvidoVsCPU
/*! Init the 2 players invido game: player against CPU
*/
void cInvidoGfx::InitInvidoVsCPU()
{

    if (m_pInvidoCore)
    {
        delete m_pInvidoCore;
        m_pInvidoCore = 0;
    }
    m_pInvidoCore = new cInvidoCore();
    m_pInvidoCore->Create(NULL, 2);
    g_pInvidoCore = m_pInvidoCore;

    m_pInvidoCore->SetRandomSeed((unsigned)time(NULL));


    cPlayer* pPlayer1 = m_pInvidoCore->GetPlayer(PLAYER1);
    cPlayer* pPlayer2 = m_pInvidoCore->GetPlayer(PLAYER2);

    pPlayer1->SetType(PT_LOCAL);
    pPlayer1->SetName(g_Options.All.strPlayerName.c_str());
    pPlayer1->SetLevel(HMI, this);

    pPlayer2->SetType(PT_MACHINE);
    pPlayer2->SetName("Re Adlinvidu");
    pPlayer2->SetLevel(ADVANCED, NULL);
    m_pMatchPoints = m_pInvidoCore->GetMatchPointsObj();

    TRACE("Partita tra %s e %s", pPlayer1->GetName(), pPlayer2->GetName());

    m_bMatchTerminated = FALSE;
}


////////////////////////////////////////
//       MatchLoop
/*! Match loop
*/
void cInvidoGfx::MatchLoop()
{
    Mix_ChannelFinished(fnEffectTer);
    m_pInvidoCore->NewMatch();
    drawStaticScene();

    SDL_Event event;
    int done = 0;
    Uint32 uiLast_time;
    Uint32 uiFrame = 0;
    Uint32 uiNowTime = 0;
    m_DelayAction.Reset();

    uiLast_time = SDL_GetTicks();
    STRING strTextTmp;
    TRACE("Inizio partita loop \n");
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
                    TRACE("Partita finita per scelta utente\n");
                    return;
                }
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = 1;
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

        // next action on the game
        if (m_DelayAction.CanStart())
        {
            m_pInvidoCore->NextAction();
        }

        // SDL 2.0
        SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch);
        SDL_RenderClear(m_psdlRenderer);
        SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
        SDL_RenderPresent(m_psdlRenderer);
    }
}

////////////////////////////////////////
//       handleMouseDownEvent
/*! Mouse down event happens
// \param SDL_Event &event :
*/
void cInvidoGfx::handleMouseDownEvent(SDL_Event &event)
{
    int i;
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        // check if the player have to play a card
        for (i = 0; i < NUM_CARDS_HAND; i++)
        {
            // check if a card was clicked
            if (m_aPlayerCards[i].MouseInCard(event.button.x, event.button.y))
            {
                // click on player card
                clickOnPlayerCard(i);
            }
        }
    }
    else if (event.button.button == SDL_BUTTON_RIGHT)
    {
        // mouse right
        // use the right button to show a popup menu 
        if (m_bPlayerCanPlay)
        {
            for (i = 0; i < NUM_CARDS_HAND; i++)
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
                        if (eSay == VADODENTRO)
                        {
                            vadoDentro(iIndexCardSelected);
                        }
                        else
                        {
                            INP_PlayerSay(eSay);
                            if (g_Options.All.bMyCallEcho)
                            {
                                int iMusId = m_Map_id_EchoSay[eSay];
                                if (m_pMusicMgr->PlayEffect(iMusId))
                                {
                                    m_DelayAction.CheckPoint(2260, cDelayNextAction::CHANGE_AVAIL);
                                }
                            }
                        }
                    }
                    // stop search other cards
                    break;
                }
            }
        }
    }
}

// showPopUpCallMenu
void cInvidoGfx::showPopUpCallMenu(CardSpec&   cardClicked, int iX, int iY, eSayPlayer* peSay)
{

    TRACE("show popup menu\n");
    ASSERT(peSay);
    ASSERT(m_pAlphaDisplay);
    *peSay = NOTHING;
    VCT_COMMANDS vct_cmd;
    ASSERT(m_pInvidoCore);
    m_pInvidoCore->GetMoreCommands(vct_cmd, m_PlayerGuiIndex);
    vct_cmd.push_back(NOTHING);

    size_t iNumCmdsAval = vct_cmd.size();

    // prepare the size of the box
    cPopUpMenuGfx   PopUpMenu;
    SDL_Rect rctBox;
    rctBox.w = m_pScreen->w; // max value, width is autocalculated
    rctBox.h = m_pScreen->h; // max value hight is autocalculated
    rctBox.y = iY;
    rctBox.x = iX;

    // show a mesage box
    PopUpMenu.Init(&rctBox, m_pScreen, m_pFontText, m_psdlRenderer);
    SDL_BlitSurface(m_pScreen, NULL, m_pAlphaDisplay, NULL);

    for (size_t i = 0; i < iNumCmdsAval; i++)
    {
        eSayPlayer eSay = vct_cmd[i];
        STRING strTmp = m_Map_bt_Say[eSay];

        PopUpMenu.AddLineText(strTmp.c_str());
    }

    PopUpMenu.Show(m_pAlphaDisplay);
    // menu is terminated
    if (PopUpMenu.MenuIsSelected())
    {
        // the user choice a menu
        int iIndexSel = PopUpMenu.GetSlectedIndex();
        *peSay = vct_cmd[iIndexSel];
    }
    else
    {
        *peSay = NOTHING;
    }

    TRACE("END popup menu\n");
    drawStaticScene();

}



////////////////////////////////////////
//       clickOnPlayerCard
/*! A player card was clicked
// \param int iIndex : index of the card clicked
*/
void cInvidoGfx::clickOnPlayerCard(int iIndex)
{
    TRACE("card clicked %d\n", iIndex);
    if (m_bPlayerCanPlay && (m_aPlayerCards[iIndex].State == cCardGfx::CSW_ST_VISIBLE))
    {
        m_pInvidoCore->Player_playCard(PLAYER_ME, m_aPlayerCards[iIndex].cardSpec.GetCardInfo());
        m_bPlayerCanPlay = FALSE;
    }
}

void cInvidoGfx::vadoDentro(int cardIx)
{
    TRACE("Card vado dentro %d\n", cardIx);
    if (m_bPlayerCanPlay && (m_aPlayerCards[cardIx].State == cCardGfx::CSW_ST_VISIBLE))
    {
        m_CardVadoDentroIndex = cardIx;
        m_pInvidoCore->Player_vaDentro(PLAYER_ME, m_aPlayerCards[cardIx].cardSpec.GetCardInfo());
        m_bPlayerCanPlay = FALSE;
    }
}

void cInvidoGfx::renderScreen()
{
    SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); // sdl 2.0
    SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
    SDL_RenderPresent(m_psdlRenderer);
}

void cInvidoGfx::drawVadoDentroCard(cCardGfx* pCard)
{
    drawStaticScene();
    pCard->SetSymbolTocard(cCardGfx::SYMBOL_BRISCNET, m_iCardWidth, m_iCardHeight, m_pScreen);
    renderCard(pCard);
    renderScreen();
}

////////////////////////////////////////
//       drawPlayedCard
/*! Draw a card that was played
// \param cCardGfx* pCard :
*/
void cInvidoGfx::drawPlayedCard(cCardGfx* pCard)
{
    int iIndexToUse = 0;
    if (m_CardsTable[0].State == cCardGfx::CSW_ST_INVISIBLE)
    {
        // first card  played
        iIndexToUse = 0;
    }
    else
    {
        // second card played
        iIndexToUse = 1;
    }
    drawStaticScene();

    m_CardsTable[iIndexToUse].CopyButNoPosition(pCard);
    renderCard(&m_CardsTable[iIndexToUse]);
    pCard->SetSymbolTocard(cCardGfx::SYMBOL_BRISCNET, m_iCardWidth, m_iCardHeight, m_pScreen);
    renderCard(pCard);
    renderScreen();

}

////////////////////////////////////////
//       HandleMouseMoveEvent
void cInvidoGfx::handleMouseMoveEvent(SDL_Event &event)
{
    for (int i = 0; i < NUMOFBUTTON; i++)
    {
        m_pbtArrayCmd[i]->MouseMove(event, m_pScreen, m_pScene_background, m_pScreenTexture);
    }
}

////////////////////////////////////////
//       HandleMouseUpEvent
void cInvidoGfx::handleMouseUpEvent(SDL_Event &event)
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
void cInvidoGfx::handleKeyDownEvent(SDL_Event &event)
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
void cInvidoGfx::showPlayerMarkup(int iPlayerIx)
{
    SDL_Rect dest;
    if (iPlayerIx == PLAYER1)
    {
        dest.x = 350;
        dest.y = 500;
    }
    else if (iPlayerIx == PLAYER2)
    {
        dest.x = 350;
        dest.y = 50;
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
void    cInvidoGfx::showPointsPlayer(int iPlayerIx, VCT_INT& vct_Points)
{
    int iCurr_Y;
    SDL_Rect dest;
    int iInitial_X1 = 550;
    int iInitial_X2 = iInitial_X1 + 120;
    if (iPlayerIx == PLAYER1)
    {
        dest.x = iInitial_X1;
    }
    else
    {
        dest.x = iInitial_X2;
    }
    int iInitial_X = dest.x;
    iCurr_Y = 50;

    int iNumPoints = (int)vct_Points.size();
    int iCaneliOnLine = 0;
    int iEggOnLine = 0;
    int iY_NextCanela = iCurr_Y;
    int iY_NextEgg = iCurr_Y;
    int iCanelaInterl = 12;
    int iX_NextEgg = iInitial_X;
    for (int i = 0; i < iNumPoints; i++)
    {
        int iCurrPoint = vct_Points[i];
        if (iCurrPoint == 1)
        {
            dest.x = iInitial_X;
            iCaneliOnLine++;
            // draw canela
            if (iCaneliOnLine == 1)
            {
                if (iY_NextCanela <= iY_NextEgg)
                {
                    if (iEggOnLine == 0)
                    {
                        iY_NextCanela = iY_NextEgg;
                    }
                    else
                    {
                        iY_NextCanela = iY_NextEgg + m_pAnImages[IMG_UOVO]->h + 3;
                    }
                }

                dest.y = iY_NextCanela;
                dest.w = m_pAnImages[IMG_CANELA]->w;
                dest.h = m_pAnImages[IMG_CANELA]->h;
                SDL_BlitSurface(m_pAnImages[IMG_CANELA], NULL, m_pScreen, &dest);

                iY_NextCanela += iCanelaInterl;
            }
            else if (iCaneliOnLine == 2)
            {
                dest.y = iY_NextCanela;
                dest.w = m_pAnImages[IMG_CANELA]->w;
                dest.h = m_pAnImages[IMG_CANELA]->h;
                SDL_BlitSurface(m_pAnImages[IMG_CANELA], NULL, m_pScreen, &dest);

                iY_NextCanela -= iCanelaInterl;
            }
            else if (iCaneliOnLine == 3)
            {
                dest.y = iY_NextCanela;
                dest.w = m_pAnImages[IMG_CANELA_OBL]->w;
                dest.h = m_pAnImages[IMG_CANELA_OBL]->h;
                SDL_BlitSurface(m_pAnImages[IMG_CANELA_OBL], NULL, m_pScreen, &dest);
                if (iEggOnLine != 1)
                {
                    iY_NextCanela += dest.h + 3;
                }
                else
                {
                    iY_NextCanela = iY_NextEgg + m_pAnImages[IMG_UOVO]->h + 3;
                }
                iCaneliOnLine = 0;
            }
            else
            {
                ASSERT(0);
            }
        }
        else if (iCurrPoint == 3)
        {
            // draw egg
            iEggOnLine++;
            if (iEggOnLine <= 1)
            {
                // first egg on the line
                if (iCaneliOnLine == 0)
                {
                    if (iY_NextEgg < iY_NextCanela)
                    {
                        iY_NextEgg = iY_NextCanela;
                    }
                }
                else if (iCaneliOnLine == 1)
                {
                    int iPossY = iY_NextCanela + m_pAnImages[IMG_CANELA_OBL]->h + 3;
                    if (iY_NextEgg < iPossY)
                    {
                        iY_NextEgg = iPossY;
                    }
                }
                else
                {
                    // 2 caneli drawn
                    int iPossY = iY_NextCanela + m_pAnImages[IMG_CANELA_OBL]->h + 3;
                    if (iY_NextEgg < iPossY)
                    {
                        iY_NextEgg = iPossY;
                    }
                }
                dest.y = iY_NextEgg;
                dest.x = iInitial_X;
                iX_NextEgg += 40;

            }
            else if (iEggOnLine <= 2)
            {
                // second egg
                iEggOnLine = 0;
                dest.y = iY_NextEgg;
                dest.x = iX_NextEgg;
                iY_NextEgg += m_pAnImages[IMG_UOVO]->h + 3;
                iX_NextEgg = iInitial_X;
            }
            dest.w = m_pAnImages[IMG_UOVO]->w;
            dest.h = m_pAnImages[IMG_UOVO]->h;
            SDL_BlitSurface(m_pAnImages[IMG_UOVO], NULL, m_pScreen, &dest);
        }
        else
        {
            ASSERT(0);
        }
    }

}

////////////////////////////////////////
//       showManoScore
/*! Show the score of the mano using leds.
*/
void cInvidoGfx::showManoScore(BOOL bIsPlayed, int iPlayerIx, BOOL bIsPata, int iManoNum)
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
            // patada, both blue
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
//       guiPlayerTurn
/*! Inform that the player have to play using the GUI
// \param int iPlayer :
*/
void cInvidoGfx::guiPlayerTurn(int iPlayer)
{
    ASSERT(m_pMatchPoints);
    m_bPlayerCanPlay = TRUE;

    m_iPlayerThatHaveMarkup = iPlayer;

    // update the screen
    drawStaticScene();

    cPlayer* pPlayer = m_pInvidoCore->GetPlayer(iPlayer);

    if (g_Options.All.iVerbose > 5)
    {
        TRACE("%s Player che deve giocare %d: %s\n", lpszCST_INFO, iPlayer, pPlayer->GetName());
    }
}


////////////////////////////////////////
//       showCurrentScore
/*! Show the current match score
*/
void cInvidoGfx::showCurrentScore()
{
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

    int iBackOff = 10;

    // score background
    GFX_UTIL::DrawStaticSpriteEx(m_pScreen, 0, 0, iX_end - iX1 + iBackOff,
        iY_end - iY1 + iBackOff + 30, iX1 - iBackOff / 2, iY1 - iBackOff / 2, m_pSurf_Bar);


    SDL_Rect dest;

    // vertical line
    int i;
    for (i = iY1; i < iY_end; i += m_pAnImages[IMG_VERTICAL]->h)
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

    // name on grid - player 1
    cPlayer* pPlayer = m_pInvidoCore->GetPlayer(PLAYER1);
    STRING strTmp = pPlayer->GetName();
    int iLenName = (int)strTmp.length();
    GFX_UTIL::DrawString(m_pScreen, pPlayer->GetName(), iX_vertical - (9 * iLenName), iY1, GFX_UTIL_COLOR::White, m_pFontText, true);
    // player 2
    pPlayer = m_pInvidoCore->GetPlayer(PLAYER2);
    GFX_UTIL::DrawString(m_pScreen, pPlayer->GetName(), iX_vertical + 10, iY1, GFX_UTIL_COLOR::White, m_pFontText, false);

    // current giocata score
    eGiocataScoreState eCurrScore = m_pMatchPoints->GetCurrScore();
    STRING lpsNamePoints = m_MapPunti[eCurrScore];
    if (m_pMatchPoints->IsGiocataMonte())
    {
        lpsNamePoints = m_pLangMgr->GetStringId(cLanguages::ID_S_AMONTE).c_str();
    }
    CHAR buffTmp[256];
    sprintf(buffTmp, "%s: %s", m_pLangMgr->GetStringId(cLanguages::ID_STA_PTCURRENT).c_str(), lpsNamePoints.c_str());
    int tx, ty;
    TTF_SizeText(m_pFontText, buffTmp, &tx, &ty);
    int iX_posCurrScore = iX_vertical - tx / 2;
    int iY_posCurrScore = iY_end + 10;
    GFX_UTIL::DrawString(m_pScreen, buffTmp, iX_posCurrScore,
        iY_posCurrScore, GFX_UTIL_COLOR::White, m_pFontText, false);

    //player score
    int iNumGiocate = m_pMatchPoints->GetNumGiocateInCurrMatch();
    VCT_INT vct_Point_pl1;
    for (int j = 0; j < NUM_PLAY_INVIDO_2; j++)
    {
        vct_Point_pl1.clear();
        for (int iNumGio = 0; iNumGio < iNumGiocate; iNumGio++)
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

}

////////////////////////////////////////
//       enableCmds
/*! Enable available commands
*/
void cInvidoGfx::enableCmds()
{
    VCT_COMMANDS vct_cmd;
    ASSERT(m_pInvidoCore);
    m_pInvidoCore->GetAdmittedCommands(vct_cmd, m_PlayerGuiIndex);

    // reset button to default strings
    size_t iNumCmd = vct_cmd.size();
    enableOnlyCmdButtons(iNumCmd);

    for (size_t i = 0; i < iNumCmd; i++)
    {
        // set the command with the new command
        eSayPlayer eSay = vct_cmd[i];
        STRING strTmp = m_Map_bt_Say[eSay];
        setCmdButton(i, eSay, strTmp.c_str());
    }
}


////////////////////////////////////////
//       enableOnlyCmdButtons
/*! Enables buttons for commands. If the parameter is 0, all buttons are disabled
// \param int iNumButt : number of buttons to be enabled
*/
void  cInvidoGfx::enableOnlyCmdButtons(size_t iNumButt)
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
void cInvidoGfx::setCmdButton(size_t iButtonIndex, eSayPlayer eSay, LPCSTR strCaption)
{
    if (iButtonIndex >= 0 && iButtonIndex < NUMOFBUTTON)
    {
        m_pbtArrayCmd[iButtonIndex]->SetWindowText(strCaption);
        m_CmdDet[iButtonIndex] = eSay;
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
void cInvidoGfx::ButCmdClicked(int iButID)
{
    if (iButID >= 0 && iButID < NUMOFBUTTON)
    {
        // first 6 ids are say commands buttons
        eSayPlayer eSay = m_CmdDet[iButID];
        if (m_pInvidoCore->Player_saySomething(m_PlayerGuiIndex, eSay))
        {
            // said something admitted
            //disable all buttons
            enableOnlyCmdButtons(0);
            drawStaticScene();
            // play what i say (echo mode)
            if (g_Options.All.bMyCallEcho)
            {
                int iMusId = m_Map_id_EchoSay[eSay];
                if (m_pMusicMgr->PlayEffect(iMusId))
                {
                    m_DelayAction.CheckPoint(2260, cDelayNextAction::CHANGE_AVAIL);
                }
            }
        }
    }
}


////////////////////////////////////////
//       NtfyTermEff
/*! Effect playing is terminated
// \param int iCh :
*/
void cInvidoGfx::NtfyTermEff(int iCh)
{
    m_DelayAction.ChangeCurrDelay(50);
}


// ***************************************************
//********  interface invido core  callback **********
// ***************************************************

////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cInvidoGfx::ALG_Play()
{
    guiPlayerTurn(m_PlayerGuiIndex);
    enableCmds();
}


////////////////////////////////////////
//       ALG_HaveToRespond
/*! player have to responce notification
*/
void cInvidoGfx::ALG_HaveToRespond()
{
    TRACE("%s %s\n", lpszCST_SU, m_pLangMgr->GetStringId(cLanguages::ID_CP_RISP1).c_str());
    enableCmds();
}


////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player say something
// \param int iPlayerIx :
// \param eSayPlayer SaySomeThing :
*/
void cInvidoGfx::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer SaySomeThing)
{
    m_pbalGfx->Disable();

    if (iPlayerIx == m_iOpponentIndex)
    {
        // viene solo ripetuta la voce dell'avversario. Quella del giocatore è in echo
        cPlayer* pPlayer = m_pInvidoCore->GetPlayer(iPlayerIx);
        STRING lpsNameSay = m_Map_fb_Say[SaySomeThing];
        TRACE("%s %s %s %s:  %s\n", lpszCST_INFO,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_PLAYER).c_str(), pPlayer->GetName(),
            m_pLangMgr->GetStringId(cLanguages::ID_CP_DICE).c_str(), lpsNameSay.c_str());

        m_pbalGfx->StartShow(lpsNameSay.c_str());
        if (g_Options.All.bSoundEffect)
        {
            // say also with music
            int iMusId = m_Map_idSynth_Say[SaySomeThing];
            m_pMusicMgr->PlayEffect(iMusId);
            m_DelayAction.CheckPoint(60, cDelayNextAction::CHANGE_AVAIL);
        }
    }
    else
    {
        enableCmds();
    }
}

void cInvidoGfx::ALG_PlayerHasVadoDentro(int iPlayerIx)
{
    if (iPlayerIx == m_PlayerGuiIndex && m_CardVadoDentroIndex >= 0 && m_CardVadoDentroIndex < NUM_CARDS_HAND)
    {
        if (m_aPlayerCards[m_CardVadoDentroIndex].State == cCardGfx::CSW_ST_VISIBLE)
        {
            TRACE("card played %s\n", m_aPlayerCards[m_CardVadoDentroIndex].cardSpec.GetName());

            drawVadoDentroCard(&m_aPlayerCards[m_CardVadoDentroIndex]);

        }
        m_DelayAction.CheckPoint(600, cDelayNextAction::NOCHANGE);
    }
    else if (iPlayerIx == m_iOpponentIndex)
    {
        STRING lpsNameSay = m_Map_fb_Say[VADODENTRO];
        m_pbalGfx->StartShow(lpsNameSay.c_str());
        CardSpec Card;
        Card.SetCardIndex(3);
        opponentHasPlayedCard(Card, TRUE);
    }
    else
    {
        ASSERT(0);
    }
}

void cInvidoGfx::opponentHasPlayedCard(CardSpec& Card, BOOL vadoDentro)
{
    BOOL bFound = FALSE;
    for (int iIndex = 0; !bFound && iIndex < NUM_CARDS_HAND; iIndex++)
    {
        if (m_aOpponentCards[iIndex].State == cCardGfx::CSW_ST_BACK)
        {

            if (vadoDentro) {
                TRACE("Opponent va dentro, draw it\n");
                drawVadoDentroCard(&m_aOpponentCards[iIndex]);
            }
            else {
                TRACE("card played %s\n", Card.GetName());
                m_aOpponentCards[iIndex].State = cCardGfx::CSW_ST_VISIBLE;
                m_aOpponentCards[iIndex].cardSpec = Card;
                drawPlayedCard(&m_aOpponentCards[iIndex]);
            }
            bFound = true;
        }
    }
    ASSERT(bFound);
    cPlayer* pPlayer = m_pInvidoCore->GetPlayer(m_iOpponentIndex);
    TRACE("%s %s ha giocato %s\n", lpszCST_INFO, pPlayer->GetName(), Card.GetName());
    int iNumCardPlayed = m_pMatchPoints->GetCurrNumCardPlayed();
    if (iNumCardPlayed == 1)
    {
        // first card played from opponent, don't need a delay
        m_DelayAction.CheckPoint(50, cDelayNextAction::NOCHANGE);

    }
    else
    {
        // opponent was not the first, delay action to show a little the current table
        m_DelayAction.CheckPoint(600, cDelayNextAction::NOCHANGE);
    }
}

////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player  play a card
// \param int iPlayerIx :
// \param CardSpec Card :
*/
void cInvidoGfx::ALG_PlayerHasPlayed(int iPlayerIx, const CARDINFO* pCard)
{
    // disable ballon
    m_pbalGfx->Disable();

    CardSpec Card;
    Card.SetCardInfo(*pCard);

    // markup player that have to play
    cPlayer* pPlayer = 0;

    m_pInvidoCore->GetPlayerInPlaying(&pPlayer);
    ASSERT(pPlayer);

    if (pPlayer)
    {
        m_iPlayerThatHaveMarkup = pPlayer->GetIndex();
    }

    bool bFound = false;
    if (iPlayerIx == m_iOpponentIndex)
    {
        // opponent play a card
        opponentHasPlayedCard(Card, FALSE);

    }
    else if (iPlayerIx == m_PlayerGuiIndex)
    {
        // HMI has played correctly
        for (int iIndex = 0; !bFound && iIndex < NUM_CARDS_HAND; iIndex++)
        {
            if (m_aPlayerCards[iIndex].cardSpec == Card)
            {
                TRACE("card played %s\n", Card.GetName());

                drawPlayedCard(&m_aPlayerCards[iIndex]);
                bFound = true;

            }
        }
        // min dealy before cpu play 
        m_DelayAction.CheckPoint(600, cDelayNextAction::NOCHANGE);

        ASSERT(bFound);
    }
    else
    {
        ASSERT(0);
    }
    if (bFound)
    {
        // card was played correctly
        // make a feedback 
        m_pMusicMgr->PlayEffect(cMusicManager::SND_EFC_CLICK);
    }
}

////////////////////////////////////////
//       ALG_NewGiocata
/*! Cards are distruited. Draw it.
*/
void cInvidoGfx::ALG_NewGiocata(const CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx)
{
    TRACE("ALG_NewGiocata\n");
    m_bPlayerCanPlay = FALSE;

    ASSERT(iNumOfCards == NUM_CARDS_HAND);

    // NOTE: to set cards is better to use pCardArray.
    // Cards of the opponent are not yet set, so we can't display it.
    // This is correct because the Gfx engine operate like a player and not have to 
    // know the opponent cards

    // player
    CardSpec tmpCardSpec;
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        tmpCardSpec.SetCardInfo(pCardArray[i]);
        m_aPlayerCards[i].cardSpec = tmpCardSpec; // overloaded operator = that copy all important fields
        m_aPlayerCards[i].State = cCardGfx::CSW_ST_VISIBLE;
    }

    // opponent
    for (int j = 0; j < NUM_CARDS_HAND; j++)
    {
        m_aOpponentCards[j].State = cCardGfx::CSW_ST_BACK;
    }

    // cards played
    for (int k = 0; k < NUM_CARDS_PLAYED; k++)
    {
        m_CardsTable[k].State = cCardGfx::CSW_ST_INVISIBLE;
    }

    animateBeginGiocata();

}

////////////////////////////////////////
//       ALG_ManoEnd
/*! Mano is terminated
*/
void cInvidoGfx::ALG_ManoEnd(I_MatchScore* pScore)
{
    ASSERT(pScore);
    m_bPlayerCanPlay = FALSE;

    int iPlayerIx = pScore->GetManoWinner();
    int iManoNum = pScore->GetManoNum();

    // necessary to show the cards played on the table
    SDL_Delay(500);

    // update the screen
    drawStaticScene();
    if (pScore->IsManoPatada())
    {
        cPlayersOnTable* pTable = m_pInvidoCore->GetTable();

        m_iPlayerThatHaveMarkup = pTable->GetFirstOnTrick();
        cPlayer* pPlayer = pTable->GetPlayerIndex(m_iPlayerThatHaveMarkup);

        // Mano patada, tocca a
        TRACE("%s %s %s\n", lpszCST_INFO,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_MANOPATA).c_str(), pPlayer->GetName());

        // animation of pata, use an index outside the player table
        animateManoEnd(21);
    }
    else
    {
        cPlayer* pPlayer = m_pInvidoCore->GetPlayer(iPlayerIx);
        // Mano vinta da
        TRACE("%s %s %s\n", lpszCST_INFO,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_MANOVINTA).c_str(), pPlayer->GetName());

        animateManoEnd(iPlayerIx);
        m_iPlayerThatHaveMarkup = iPlayerIx;
    }

    // cards played
    for (int k = 0; k < NUM_CARDS_PLAYED; k++)
    {
        m_CardsTable[k].State = cCardGfx::CSW_ST_INVISIBLE;
    }

    drawStaticScene();
}


////////////////////////////////////////
//       ALG_GiocataEnd
/*! Giocata is terminated
*/
void cInvidoGfx::ALG_GiocataEnd(I_MatchScore* pScore)
{
    int iPlayerIx = pScore->GetGiocataWinner();

    BOOL bIsPata = pScore->IsGiocataPatada();
    STRING strMsgFinGiocata;
    if (bIsPata)
    {
        // giocata patada
        TRACE("%s %s\n", lpszCST_INFO,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_GIOCATAPATA).c_str());
        strMsgFinGiocata = m_pLangMgr->GetStringId(cLanguages::ID_CP_GIOCATAPATA);
    }
    else if (pScore->IsGiocataMonte())
    {
        // giocata a monte
        TRACE("%s %s\n", lpszCST_INFO,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_GIOCATAMONTE).c_str());
        strMsgFinGiocata = m_pLangMgr->GetStringId(cLanguages::ID_CP_GIOCATAMONTE);
        bIsPata = TRUE;
    }
    else
    {
        // giocata with a winner
        CHAR buffText[512];

        int iPlayLoser;
        if (iPlayerIx == m_PlayerGuiIndex)
        {
            iPlayLoser = m_iOpponentIndex;
        }
        else
        {
            iPlayLoser = m_PlayerGuiIndex;
        }
        cPlayer* pPlayer = m_pInvidoCore->GetPlayer(iPlayerIx);
        cPlayer* pPlLoser = m_pInvidoCore->GetPlayer(iPlayLoser);

        // Giocata vinta da
        TRACE("%s %s %s (%s %d)\n", lpszCST_INFO,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_GIOCATAVINTA).c_str(),
            pPlayer->GetName(),
            m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(), pScore->GetCurrScore());
        sprintf(buffText, "%s \"%s\" (%s %d)", m_pLangMgr->GetStringId(cLanguages::ID_CP_GIOCATAVINTA).c_str(), pPlayer->GetName(), m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(), pScore->GetCurrScore());
        // punti
        TRACE("%s %s %s %d, %s %s %d\n", lpszCST_SCORE, pPlayer->GetName(),
            m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(), pScore->GetPointsPlayer(iPlayerIx),
            pPlLoser->GetName(), m_pLangMgr->GetStringId(cLanguages::ID_CP_PUNTI).c_str(), pScore->GetPointsPlayer(iPlayLoser));


        strMsgFinGiocata = buffText;
    }
    m_bPlayerCanPlay = FALSE;
    drawStaticScene();
    animGiocataEnd(iPlayerIx, bIsPata);
    showOkMsgBox(strMsgFinGiocata.c_str());
}


////////////////////////////////////////
//       ALG_MatchEnd
/*! Match is end
*/
void cInvidoGfx::ALG_MatchEnd(I_MatchScore* pScore)
{

    int iPlayerIx = pScore->GetMatchWinner();
    int iPlayLoser;
    if (iPlayerIx == m_PlayerGuiIndex)
    {
        iPlayLoser = m_iOpponentIndex;
    }
    else
    {
        iPlayLoser = m_PlayerGuiIndex;
    }
    cPlayer* pPlayer = m_pInvidoCore->GetPlayer(iPlayerIx);
    cPlayer* pPlLoser = m_pInvidoCore->GetPlayer(iPlayLoser);
    m_bPlayerCanPlay = FALSE;

    // partita finita. player vince x:x
    CHAR buff[256];
    sprintf(buff, "%s. %s %s  %d : %d.", m_pLangMgr->GetStringId(cLanguages::ID_CP_PARTITAFIN).c_str(), pPlayer->GetName(),
        m_pLangMgr->GetStringId(cLanguages::ID_CP_VINCE).c_str(),
        pScore->GetPointsPlayer(iPlayerIx), pScore->GetPointsPlayer(iPlayLoser));

    TRACE("%s %s\n", lpszCST_INFO, buff);

    drawStaticScene();

    showOkMsgBox(buff);

    m_bMatchTerminated = TRUE;
}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*! giocata score changed
// \param eGiocataScoreState eNewScore :
*/
void cInvidoGfx::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{
    STRING lpsNamePoints = m_MapPunti[eNewScore];
    // Punteggio della giocata ora è:
    TRACE("%s %s: %s\n", lpszCST_INFO,
        m_pLangMgr->GetStringId(cLanguages::ID_CP_NOWPOINTS).c_str(), lpsNamePoints.c_str());
}


void cInvidoGfx::ALG_PlayerSaidWrong(int iPlayerIx)
{
    if (iPlayerIx == m_PlayerGuiIndex)
    {
        // Quello che hai chiamato non è corretto
        TRACE("%s, %s\n", lpszCST_SU,
            m_pLangMgr->GetStringId(cLanguages::ID_CP_BUIADA).c_str());
    }
}

////////////////////////////////////////
//       INP_PlayerSay
/*!
// \param eSayPlayer eSay :
*/
void cInvidoGfx::INP_PlayerSay(eSayPlayer eSay)
{
    m_pInvidoCore->Player_saySomething(m_PlayerGuiIndex, eSay);
}


