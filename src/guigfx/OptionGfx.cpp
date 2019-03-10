// OptionGfx.cpp: implementation of the OptionGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OptionGfx.h"
#include "cButtonGfx.h"
#include "gfx_util.h"
#include "cCheckBoxGfx.h"
#include "cEditGfx.h"
#include "cComboGfx.h"
#include "InvidoSettings.h"
#include "AppGfx.h"
#include "Languages.h"
#include "cMusicManager.h"
#include "cInvidoCoreEnv.h"
#include "InvidoInfoComm.h"
#include "cProgressBarGfx.h"

extern AppGfx* g_MainApp;

static const char* stalpszUSER = "USER";
static const char* stalpszCPUDEFAULT = "CPU_DEFAULT";
static const char* stalpszPluginDir = "./plugin/";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       OptionGfx
/*!
*/
OptionGfx::OptionGfx()
{
    m_pScreen = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_pBtOK = 0;
    m_pBtCancel = 0;
    m_bTerminated = FALSE;
    m_pCheckMusic = 0;
    m_pEditName = 0;
    m_pCheckSoundEffect = 0;
    m_bShowAlgControls = FALSE;
    m_pComboLang = 0;
    m_pCheckShowFotoBack = 0;
}


////////////////////////////////////////
//       ~OptionGfx
/*!
*/
OptionGfx::~OptionGfx()
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    delete m_pBtOK;
    delete m_pBtCancel;
    delete m_pEditName;
    delete m_pCheckMusic;
    delete m_pCheckSoundEffect;
    delete m_pComboLang;
    delete m_pCheckShowFotoBack;
}

////////////////////////////////////////
//       Init
/*!
// \param SDL_Rect* pRect :
// \param SDL_Surface*  pScreen :
// \param TTF_Font* pFont :
*/
void OptionGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl, SDL_Renderer* pRenderer)
{
    ASSERT(pRect);
    ASSERT(pScreen && pFontWinCtrl);
    m_rctOptBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFontTxt;
    m_pFontCtrl = pFontWinCtrl;
    m_psdlRenderer = pRenderer;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctOptBox.w, m_rctOptBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 10, 100, 10, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 200); // SDL 1.2
    SDL_SetSurfaceBlendMode(m_pSurf_Bar, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 200); //SDL 2.0

    SDL_Rect rctBt1;
    int iSpace2bt = 20;

    // button ok
    m_pBtOK = new cButtonGfx;
    m_pBtOK->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = (m_rctOptBox.w - rctBt1.w) / 2 + m_rctOptBox.x - rctBt1.w - iSpace2bt;
    m_pBtOK->Init(&rctBt1, pScreen, m_pFontText, MYIDOK, pRenderer);
    m_pBtOK->SetState(cButtonGfx::INVISIBLE);


    // button cancel
    m_pBtCancel = new cButtonGfx;
    m_pBtCancel->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = (m_rctOptBox.w - rctBt1.w) / 2 + m_rctOptBox.x + rctBt1.w + iSpace2bt;
    m_pBtCancel->Init(&rctBt1, pScreen, m_pFontText, MYIDCANCEL, pRenderer);
    m_pBtCancel->SetState(cButtonGfx::INVISIBLE);

    // check box music
    m_pCheckMusic = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + 60;
    rctBt1.x = m_pBtOK->m_rctButt.x;
    m_pCheckMusic->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckMusic->Init(&rctBt1, pScreen, m_pFontText, MYIDMUSICCHK);
    m_pCheckMusic->SetState(cCheckBoxGfx::INVISIBLE);

    //checkbox sound effect
    m_pCheckSoundEffect = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pCheckMusic->m_rctButt.y + 40;
    rctBt1.x = m_pCheckMusic->m_rctButt.x;
    m_pCheckSoundEffect->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckSoundEffect->Init(&rctBt1, pScreen, m_pFontText, MYIDSOUNDEFFECT);
    m_pCheckSoundEffect->SetState(cCheckBoxGfx::INVISIBLE);


    // edit name 
    m_pEditName = new cEditGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pCheckSoundEffect->m_rctButt.y + m_pCheckMusic->m_rctButt.h + 30;
    rctBt1.x = m_pBtOK->m_rctButt.x;
    m_pEditName->Init(&rctBt1, pScreen, m_pFontText, MYEDITNAME, pRenderer);
    m_pEditName->SetState(cEditGfx::INVISIBLE);

    // combo language
    m_pComboLang = new cComboGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pEditName->m_rctButt.y + m_pEditName->m_rctButt.h + 35;
    rctBt1.x = m_pBtOK->m_rctButt.x;
    m_pComboLang->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ComboCmdClicked);
    m_pComboLang->Init(&rctBt1, pScreen, m_pFontText, MYIDCOMBOLAN, pRenderer);
    m_pComboLang->SetState(cComboGfx::INVISIBLE);

    // checkbox show foto background
    m_pCheckShowFotoBack = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pComboLang->m_rctButt.y + 40;
    rctBt1.x = m_pComboLang->m_rctButt.x;
    m_pCheckShowFotoBack->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckShowFotoBack->Init(&rctBt1, pScreen, m_pFontText, MYIDSHOWFOTOBACK);
    m_pCheckShowFotoBack->SetState(cCheckBoxGfx::INVISIBLE);
}

////////////////////////////////////////
//       Show
/*! Shows the option window
// \param SDL_Surface* pScene_background :
*/
void OptionGfx::Show(SDL_Surface* pScene_background)
{
    int iRes = 0;
    m_bTerminated = FALSE;
    Uint32 uiInitialTick = SDL_GetTicks();
    Uint32 uiLast_time = uiInitialTick;
    int FPS = 3;

    cLanguages* pLan = g_MainApp->GetLanguageMan();

    // prepare strings on controls

    // button ok
    STRING strTextBt;
    strTextBt = pLan->GetStringId(cLanguages::ID_OK);
    m_pBtOK->SetWindowText(strTextBt.c_str());
    m_pBtOK->SetState(cButtonGfx::VISIBLE);

    // button cancel
    strTextBt = pLan->GetStringId(cLanguages::ID_CANCEL);
    m_pBtCancel->SetWindowText(strTextBt.c_str());
    m_pBtCancel->SetState(cButtonGfx::VISIBLE);


    // checkbox music
    strTextBt = pLan->GetStringId(cLanguages::ID_MUSIC);
    m_pCheckMusic->SetWindowText(strTextBt.c_str());
    m_pCheckMusic->SetState(cCheckBoxGfx::VISIBLE);
    m_pCheckMusic->SetCheckState(g_Options.All.bMusicOn);

    //checkbox sound effect
    strTextBt = pLan->GetStringId(cLanguages::ID_SOUNDEFFECT);
    m_pCheckSoundEffect->SetWindowText(strTextBt.c_str());
    m_pCheckSoundEffect->SetState(cCheckBoxGfx::VISIBLE);
    m_pCheckSoundEffect->SetCheckState(g_Options.All.bSoundEffect);


    // Edit name
    strTextBt = g_Options.All.strPlayerName;
    STRING strNameTitle = pLan->GetStringId(cLanguages::ID_NAME);
    m_pEditName->SetWindowText(strTextBt.c_str());
    m_pEditName->SetState(cEditGfx::VISIBLE);

    // combobox language selection
    STRING strLangSelectTitle = pLan->GetStringId(cLanguages::ID_LANGUAGE);
    strTextBt = pLan->GetStringId(cLanguages::ID_ITALIANO);
    m_pComboLang->AddLineText(strTextBt.c_str());
    strTextBt = pLan->GetStringId(cLanguages::ID_DIALETMN);
    m_pComboLang->AddLineText(strTextBt.c_str());
    strTextBt = pLan->GetStringId(cLanguages::ID_ENGLISH);
    m_pComboLang->AddLineText(strTextBt.c_str());
    m_pComboLang->SetState(cComboGfx::VISIBLE);
    m_pComboLang->SelectIndex(g_Options.All.iLanguageID);

    // checkbox show foto background
    strTextBt = pLan->GetStringId(cLanguages::ID_SHOWFOTOBACK);
    m_pCheckShowFotoBack->SetWindowText(strTextBt.c_str());
    m_pCheckShowFotoBack->SetState(cCheckBoxGfx::VISIBLE);
    m_pCheckShowFotoBack->SetCheckState(g_Options.All.bFotoBack);

    // create a shadow surface
    SDL_Surface* pShadowSrf = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
    SDL_Texture* pScreenTexture = SDL_CreateTextureFromSurface(m_psdlRenderer, pShadowSrf); //SDL 2.0
    while (!m_bTerminated)
    {
        // background
        SDL_BlitSurface(pScene_background, NULL, pShadowSrf, NULL);

        // wait until the user click on button
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                m_bTerminated = TRUE;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    // confirm the dialog
                    ButCmdClicked(MYIDOK);
                    break;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    // escape character
                    ButCmdClicked(MYIDCANCEL);
                    break;
                }
                else
                {
                    // submitt the key on the child controls
                    m_pEditName->KeyDown(event);
                }
                break;
            case SDL_TEXTINPUT:
                m_pEditName->TextInput(event);
                break;
            case SDL_MOUSEBUTTONUP:
                m_pBtCancel->MouseUp(event);
                m_pBtOK->MouseUp(event);
                m_pCheckMusic->MouseUp(event);
                m_pCheckSoundEffect->MouseUp(event);
                m_pEditName->MouseUp(event);
                m_pComboLang->MouseUp(event);
                m_pCheckShowFotoBack->MouseUp(event);
            default:
                break;
            }
        }

        // the msg box
        GFX_UTIL::DrawStaticSpriteEx(pShadowSrf, 0, 0, m_rctOptBox.w, m_rctOptBox.h, m_rctOptBox.x,
            m_rctOptBox.y, m_pSurf_Bar);
        // draw border
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x - 1, m_rctOptBox.y - 1, m_rctOptBox.x + m_rctOptBox.w + 1,
            m_rctOptBox.y + m_rctOptBox.h + 1, GFX_UTIL_COLOR::Gray);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x - 2, m_rctOptBox.y - 2, m_rctOptBox.x + m_rctOptBox.w + 2,
            m_rctOptBox.y + m_rctOptBox.h + 2, GFX_UTIL_COLOR::Black);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x, m_rctOptBox.y, m_rctOptBox.x + m_rctOptBox.w,
            m_rctOptBox.y + m_rctOptBox.h, m_colCurrent);

        //header bar
        SDL_Rect  rectHeader;
        Uint32 colorHeader = SDL_MapRGB(m_pScreen->format, 153, 202, 51);
        rectHeader.x = m_rctOptBox.x + 1;
        rectHeader.y = m_rctOptBox.y + 1;
        rectHeader.h = 30;
        rectHeader.w = m_rctOptBox.w - 1;
        SDL_FillRect(pShadowSrf, &rectHeader, colorHeader);
        GFX_UTIL::DrawStaticLine(pShadowSrf, rectHeader.x, rectHeader.y + rectHeader.h,
            rectHeader.x + rectHeader.w, rectHeader.y + rectHeader.h, GFX_UTIL_COLOR::White);
        // text header
        GFX_UTIL::DrawString(pShadowSrf, m_strHeaderText.c_str(), rectHeader.x + 10,
            rectHeader.y, GFX_UTIL_COLOR::White, m_pFontCtrl, false);

        // draw buttons
        m_pBtOK->DrawButton(pShadowSrf);
        m_pBtCancel->DrawButton(pShadowSrf);
        // draw checkbox music
        m_pCheckMusic->DrawButton(pShadowSrf);
        //draw checkbox sound effect
        m_pCheckSoundEffect->DrawButton(pShadowSrf);

        // name label
        GFX_UTIL::DrawString(pShadowSrf, strNameTitle.c_str(), m_pEditName->m_rctButt.x,
            m_pEditName->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange, m_pFontText, false);

        // draw edit name control
        m_pEditName->DrawControl(pShadowSrf);

        // language selection label
        GFX_UTIL::DrawString(pShadowSrf, strLangSelectTitle.c_str(), m_pComboLang->m_rctButt.x,
            m_pComboLang->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange, m_pFontText, false);

        // draw the language combobox selection
        m_pComboLang->DrawButton(pShadowSrf);

        //draw checkbox show foto in background
        m_pCheckShowFotoBack->DrawButton(pShadowSrf);


        //render the dialogbox
        SDL_BlitSurface(pShadowSrf, NULL, m_pScreen, NULL);
        SDL_UpdateTexture(pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch);
        SDL_RenderCopy(m_psdlRenderer, pScreenTexture, NULL, NULL);
        SDL_RenderPresent(m_psdlRenderer);

        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();
        if (uiNowTime < uiLast_time + FPS)
        {
            SDL_Delay(uiLast_time + FPS - uiNowTime);
            uiLast_time = uiNowTime;
        }
    }
    SDL_FreeSurface(pShadowSrf);
    SDL_DestroyTexture(pScreenTexture);
}


////////////////////////////////////////
//       ComboCmdClicked
/*! Combobox callback
// \param int iButID :
*/
void   OptionGfx::ComboCmdClicked(int iButID)
{

}

////////////////////////////////////////
//       ButCmdClicked
/*! button click callback
// \param int iButID :
*/
void   OptionGfx::ButCmdClicked(int iButID)
{
    if (!m_bTerminated)
    {
        m_bTerminated = TRUE;
        m_iResult = iButID;
        if (iButID == MYIDOK)
        {
            // the user has pressed the button OK

            BOOL bOldMusic = g_Options.All.bMusicOn;
            // update all properties
            g_Options.All.strPlayerName = m_pEditName->GetWindowText();
            g_Options.All.bMusicOn = m_pCheckMusic->GetCheckState();
            g_Options.All.iLanguageID = m_pComboLang->GetSlectedIndex();
            g_Options.All.bSoundEffect = m_pCheckSoundEffect->GetCheckState();
            g_Options.All.bFotoBack = m_pCheckShowFotoBack->GetCheckState();

            cLanguages* pLan = g_MainApp->GetLanguageMan();
            pLan->SetLang((cLanguages::eLangId)g_Options.All.iLanguageID);
            cMusicManager* pMusic = g_MainApp->GetMusicManager();
            if (bOldMusic != g_Options.All.bMusicOn)
            {
                // music state changed
                if (bOldMusic)
                {
                    pMusic->StopMusic();
                }
            }



        }
    }
}


////////////////////////////////////////
//       ClickCheckBox
/*! Callback on ALL checkbox.
// \param int iButID :
*/
void   OptionGfx::ClickCheckBox(int iButID)
{
    if (iButID == MYIDCHKSHOWALGCONTROL)
    {

    }
    if (iButID == MYIDCHKSHOWANIMATIONS)
    {

    }
}