//AppGfx.cpp
// Engine application for Invido game

#include "StdAfx.h"
#include "win_type_global.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include "AppGfx.h"
#include <sdl.h>
#include <SDL_thread.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include <time.h>
#include "Languages.h"
#include "cHightScoreMgr.h"
#include "cMusicManager.h"
#include "InvidoSettings.h"
#include "cDelayNextAction.h"
#include "cInvidoGfx.h"
#include "cTipoDiMazzo.h"
#include "cMenuMgr.h"
#include "credits.h"
#include "fading.h"
#include "OptionGfx.h"
#include "EnterNameGfx.h"
#include "TraceService.h"


#ifdef WIN32
#include "Shlwapi.h"
#include "shellapi.h"
#include "Shlobj.h"
#endif


static const char* lpszIconRes = "data/images/icona_asso.bmp";
// key is stored in regestry as HKU
#ifdef WIN32
static const char* lpszIniFileOptions = "Software\\Invido.it\\InvidoClientSdl";
#else
static const char* lpszIniFileOptions = "data/options.ini";
#endif
static const char* lpszIniFontAriblk = "data/font/ariblk.ttf";
static const char* lpszIniFontVera = "data/font/vera.ttf";
static const char* lpszImageDir = "data/images/";
static const char* lpszImageSplash = "modify_01.jpg";
static const char* lpszCreditsTitle = "data/images/titlecredits.png";
static const char* lpszHelpFileName = "data/help/invido-guida.pdf";
static const char* lpszTraceFileName = "invido.log";
static const char* lpszFolderTrace = "InvidoTrace";
// nota che la versione del programma si trova nel file cMenuMgr.cpp

AppGfx* g_MainApp = 0;


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// class cEngineApp ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       cEngineApp
/*! constructor
*/
AppGfx::AppGfx()
{
    m_pWindow = NULL;
    m_psdlRenderer = NULL;
    m_iScreenW = 800; //640;
    m_iScreenH = 600; //480;
    m_iBpp = 0;
    m_pMusicManager = 0;
    m_pLanString = 0;
    m_pMenuMgr = 0;
    m_pfontAriblk = 0;
    m_pfontVera = 0;
    m_pSlash = 0;
    m_pMxAccOptions = 0;
    m_pOptCond = 0;
    g_MainApp = this;
    m_bOpzWinRunning = FALSE;
    m_pTitleCredits = 0;
}


////////////////////////////////////////
//       ~cEngineApp
/*! destructor
*/
AppGfx::~AppGfx()
{
    terminate();
}


////////////////////////////////////////
//       loadProfile
/*! Load profiles in g_Options
*/
void AppGfx::loadProfile()
{
    SpaceInvidoSettings::GetProfile(lpszIniFileOptions);
}


////////////////////////////////////////
//       writeProfile
/*! Write profiles g_Options in ini file
*/
void AppGfx::writeProfile()
{
    SpaceInvidoSettings::WriteProfile(lpszIniFileOptions);
}

////////////////////////////////////////
//       Init
/*! Init application
*/
void AppGfx::Init()
{
    // load settings from the registry
    loadProfile();
    CHAR ErrBuff[512];
    if (!SDL_WasInit(SDL_INIT_VIDEO))
    {
        if (SDL_Init(0) < 0)
        {
            sprintf(ErrBuff, "Couldn't initialize SDL: %s\n", SDL_GetError());
            throw Error::Init(ErrBuff);
        }
    }
    intWindowAndRender();

    m_pMusicManager = new cMusicManager;
    m_pMusicManager->Init();

    m_pInvidoGfx = new cInvidoGfx(this);
    m_pLanString = new cLanguages;
    m_pHScore = new cHightScoreMgr;

    // set application language
    m_pLanString->SetLang((cLanguages::eLangId)g_Options.All.iLanguageID);

    // caption
    SDL_SetWindowTitle(m_pWindow, m_pLanString->GetCStringId(cLanguages::ID_INVIDO)); // SDL 2.0


    //trasparent icon
    SDL_Surface * psIcon = SDL_LoadBMP(lpszIconRes);
    if (psIcon == 0)
    {
        sprintf(ErrBuff, "Icon not found");
        throw Error::Init(ErrBuff);
    }
    SDL_SetColorKey(psIcon, TRUE, SDL_MapRGB(psIcon->format, 0, 128, 0)); // SDL 2.0

    SDL_SetWindowIcon(m_pWindow, psIcon); // SDL 2.0

    // font TTF
    if (TTF_Init() == -1)
    {
        sprintf(ErrBuff, "Font init error");
        throw Error::Init(ErrBuff);
    }
    // font Ariblk
    std::string strFileFontStatus = lpszIniFontAriblk;
    m_pfontAriblk = TTF_OpenFont(strFileFontStatus.c_str(), 22);
    if (m_pfontAriblk == 0)
    {
        sprintf(ErrBuff, "Unable to load font %s, error: %s\n", strFileFontStatus.c_str(), SDL_GetError());
        throw Error::Init(ErrBuff);
    }
    // font Vera
    strFileFontStatus = lpszIniFontVera;
    m_pfontVera = TTF_OpenFont(strFileFontStatus.c_str(), 11);
    if (m_pfontVera == 0)
    {
        sprintf(ErrBuff, "Unable to load font %s, error: %s\n", strFileFontStatus.c_str(), SDL_GetError());
        throw Error::Init(ErrBuff);
    }

    // game invido app
    m_pInvidoGfx->SetMainApp(this);

    // menu manager
    m_pMenuMgr = new cMenuMgr(this, m_pInvidoGfx);
    m_pMenuMgr->Init(m_pScreen, m_psdlRenderer);

    // set main menu
    m_Histmenu.push(cMenuMgr::QUITAPP);
    m_Histmenu.push(cMenuMgr::MENU_ROOT);
    m_pTracer = TraceService::Instance();
#ifdef WIN32
    TCHAR szPath[1024];
    if (SUCCEEDED(SHGetFolderPath(NULL,
        CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE,
        NULL,
        0,
        szPath)))
    {
        PathAppend(szPath, lpszFolderTrace);
        DWORD dwAttrib = GetFileAttributes(szPath);

        if (!(dwAttrib != INVALID_FILE_ATTRIBUTES &&
            (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))) {
            LPSECURITY_ATTRIBUTES attr;
            attr = NULL;
            CreateDirectory(szPath, attr);
        }
        TCHAR fname[128];
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        sprintf(fname, "%d-%02d-%02d_%02d%02d%02d-%s", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, lpszTraceFileName);
        
        PathAppend(szPath, fname);

        m_pTracer->SetOutputChannel(TR_CORE_CH, TraceService::OT_FILE, szPath);
        m_pTracer->EnableChannel(TR_CORE_CH, TRUE);
    }
#else
    //m_pTracer->SetOutputChannel(TR_CORE_CH, TraceService::OT_FILE, "trace_coregame.txt");
#endif
    // background
    loadSplash();
    drawSplash();

    // credits title
    m_pTitleCredits = IMG_Load(lpszCreditsTitle);
    if (m_pTitleCredits == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Unable to load %s  image\n", lpszCreditsTitle);
        throw Error::Init(ErrBuff);
    }

    // load music
    // music manager initialization is a long process, update also a progress bar
    m_pMusicManager->LoadMusicRes();

    m_pMxAccOptions = SDL_CreateMutex();
    m_pOptCond = SDL_CreateCond();

    m_pTracer->AddSimpleTrace(TR_CORE_CH, "Init invido game ok");
}


////////////////////////////////////////
//       loadSplash
/*! load splash screen
*/
void AppGfx::loadSplash()
{
    // load background
    if (g_Options.All.bUseSplashJpg)
    {

        std::string strFileName = lpszImageDir;
        strFileName += lpszImageSplash;

        SDL_RWops *srcBack = SDL_RWFromFile(strFileName.c_str(), "rb");
        if (srcBack == 0)
        {
            CHAR ErrBuff[512];
            sprintf(ErrBuff, "Unable to load %s background image\n", strFileName.c_str());
            throw Error::Init(ErrBuff);
        }
        m_pSlash = IMG_LoadJPG_RW(srcBack);
    }
    else
    {
        int w, h;
        SDL_GetWindowSize(m_pWindow, &w, &h);
        m_pSlash = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
        SDL_FillRect(m_pSlash, NULL, SDL_MapRGBA(m_pSlash->format, 0, 80, 0, 0));
    }
}


////////////////////////////////////////
//       drawSplash
/*!
*/
void AppGfx::drawSplash()
{
    SDL_BlitSurface(m_pSlash, NULL, m_pScreen, NULL);
    updateScreenTexture();
}

void AppGfx::updateScreenTexture()
{
    // SDL 2.0
    SDL_UpdateTexture(m_pScreenTexture, NULL, m_pScreen->pixels, m_pScreen->pitch); //SDL 2.0
    SDL_RenderClear(m_psdlRenderer);
    SDL_RenderCopy(m_psdlRenderer, m_pScreenTexture, NULL, NULL);
    SDL_RenderPresent(m_psdlRenderer);
}


////////////////////////////////////////
//       terminate
/*! Terminate stuff
*/
void AppGfx::terminate()
{
    writeProfile();

    SDL_ShowCursor(SDL_ENABLE);

    if (m_pScreen != NULL)
    {
        SDL_FreeSurface(m_pScreen);
        m_pScreen = NULL;
    }
    if (m_pScreenTexture != NULL)
    {
        SDL_DestroyTexture(m_pScreenTexture);
    }

    if (m_pSlash)
    {
        SDL_FreeSurface(m_pSlash);
        m_pSlash = 0;
    }

    if (m_pTitleCredits)
    {
        SDL_FreeSurface(m_pTitleCredits);
        m_pTitleCredits = 0;
    }

    delete m_pLanString;
    delete m_pInvidoGfx;
    delete m_pMusicManager;
    delete m_pHScore;
    SDL_DestroyWindow(m_pWindow); // sdl 2.0

    SDL_Quit();
}



////////////////////////////////////////
//       MainLoop
/*! Main loop
*/
void AppGfx::MainLoop()
{
    bool bquit = false;

    // set background of menu
    m_pMenuMgr->SetBackground(m_pSlash);

    while (!bquit && !m_Histmenu.empty())
    {
        switch (m_Histmenu.top())
        {
        case cMenuMgr::MENU_ROOT:
            if (g_Options.All.bMusicOn && !m_pMusicManager->IsPLayingMusic())
            {
                m_pMusicManager->PlayMusic(cMusicManager::MUSIC_INIT_SND, cMusicManager::LOOP_ON);
            }
            m_pMenuMgr->HandleRootMenu();

            break;

        case cMenuMgr::MENU_GAME:
            PlayGame();
            break;

        case cMenuMgr::MENU_HELP:
            ShowHelp();
            break;

        case cMenuMgr::MENU_CREDITS:
            ShowCredits();
            break;

        case cMenuMgr::MENU_OPTIONS:
            ShowOptionsGeneral();
            break;

        case cMenuMgr::QUITAPP:
        default:
            bquit = true;
            break;

        }

        // actualize display
        updateScreenTexture();
    }
}


////////////////////////////////////////
//       showEditUserName
/*! Show a dialogbox to change the user name
*/
void AppGfx::showEditUserName()
{
    EnterNameGfx Dlg;
    SDL_Rect rctWin;
    rctWin.w = 350;
    rctWin.h = 200;

    rctWin.x = (m_pScreen->w - rctWin.w) / 2;
    rctWin.y = (m_pScreen->h - rctWin.h) / 2;


    Dlg.Init(&rctWin, m_pScreen, m_pfontVera, m_pfontAriblk, m_psdlRenderer);
    Dlg.SetCaption(m_pLanString->GetStringId(cLanguages::ID_CHOOSENAME));
    Dlg.Show(m_pSlash);

    drawSplash();
}

////////////////////////////////////////
//       ShowHelp
/*! Show help menu
*/
void AppGfx::ShowHelp()
{
#ifdef WIN32
    std::string strFileName = lpszHelpFileName;
    STRING strCompleteHelpPath = m_strApplicationDir + "\\" + strFileName;
    ::ShellExecute(NULL, TEXT("open"), strCompleteHelpPath.c_str(), 0, 0, SW_SHOWNORMAL);
#endif
    LeaveMenu();
}


////////////////////////////////////////
//       ShowCredits
/*! Show credits screen
*/
void AppGfx::ShowCredits()
{
    cCredits aCred(m_pfontVera);

    aCred.Show(m_pScreen, m_pTitleCredits, m_psdlRenderer);

    LeaveMenu();
}


void AppGfx::intWindowAndRender()
{
    if (m_pWindow != NULL)
    {
        SDL_DestroyWindow(m_pWindow);
    }
    m_pWindow = SDL_CreateWindow("Invido", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iScreenW, m_iScreenH, SDL_WINDOW_SHOWN);
    if (m_pWindow == NULL)
    {
        fprintf(stderr, "Cannot create window: %s\n", SDL_GetError());
        exit(1);
    }
    m_psdlRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

    if (m_psdlRenderer == NULL)
    {
        fprintf(stderr, "Cannot create renderer: %s\n", SDL_GetError());
        exit(1);
    }
    m_pScreen = SDL_CreateRGBSurface(0, m_iScreenW, m_iScreenH, 32,
        0x00FF0000,
        0x0000FF00,
        0x000000FF,
        0xFF000000);
    m_pScreenTexture = SDL_CreateTexture(m_psdlRenderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        m_iScreenW, m_iScreenH);

}

////////////////////////////////////////
//       hightScoreMenu
/*! Shows the hight score menu
*/
void AppGfx::hightScoreMenu()
{
}


////////////////////////////////////////
//       LeaveMenu
/*! Leave the current menu
*/
void   AppGfx::LeaveMenu()
{
    drawSplash();

    m_Histmenu.pop();
}

////////////////////////////////////////
//       PlayGame
/*! Play the game vs cpu
*/
int  AppGfx::PlayGame()
{
    m_pMusicManager->StopMusic();

    // load and initialize background
    m_pInvidoGfx->Initialize(m_pScreen, m_psdlRenderer, m_pScreenTexture);
    // init invido core stuff
    m_pInvidoGfx->InitInvidoVsCPU();

    // match main loop
    m_pInvidoGfx->MatchLoop();

    // game terminated
    LeaveMenu();

    return 0;
}

////////////////////////////////////////
//       ShowOptionsGeneral
/*! Show the option general control
*/
void AppGfx::ShowOptionsGeneral()
{
    OptionGfx Options;

    SDL_Rect rctOptionWin;

    rctOptionWin.w = 500;
    rctOptionWin.h = 500;

    rctOptionWin.x = (m_pScreen->w - rctOptionWin.w) / 2;
    rctOptionWin.y = (m_pScreen->h - rctOptionWin.h) / 2;


    Options.Init(&rctOptionWin, m_pScreen, m_pfontVera, m_pfontAriblk, m_psdlRenderer);
    Options.SetCaption(m_pLanString->GetStringId(cLanguages::ID_OPT_CONTRL_GENERAL));
    Options.Show(m_pSlash);

    LeaveMenu();
}


