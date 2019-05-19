// OptionGfx.cpp: implementation of the OptionGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OptionGfx.h"
#include "cButtonGfx.h"
#include "gfx_util.h"
#include "cCheckBoxGfx.h"
#include "cEditGfx.h"
#include "cComboGfx.h"
#include "cSettings.h"
#include "EngineApp.h"
#include "lang_gen.h"
#include "cMusicManager.h"
#include "CoreEnv.h"
#include "InfoComm.h"
#include "cProgressBarGfx.h"

extern cEngineApp* g_MainApp;

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
    m_pComboAlg_Pl_1 = 0;
    m_pComboAlg_Pl_2 = 0;
    m_pComboAlg_Pl_3 = 0;
    m_pComboAlg_Pl_4 = 0;
    m_bShowAlgControls = FALSE;
    m_pCheckShowAlgControl = 0;
    m_pComboLang = 0;
    m_pCheckShowAnimations = 0;
    m_pProgSpeedAni = 0;
    m_bShowProgSpeedAni = FALSE;
    m_pCheckBlockAfterManoend = 0;
    m_pCheckSignalRightMouse = 0;
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
    delete m_pCheckShowAnimations;
    delete m_pComboAlg_Pl_1;
    delete m_pComboAlg_Pl_2;
    delete m_pComboAlg_Pl_3;
    delete m_pComboAlg_Pl_4;
    delete m_pCheckShowAlgControl;
    delete m_pComboLang;
    delete m_pProgSpeedAni;
    delete m_pCheckBlockAfterManoend;
    delete m_pCheckSignalRightMouse;
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
    m_psdlRenderer = pRenderer;
    ASSERT(pRect);
    ASSERT(pScreen);
    m_rctOptBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFontTxt;
    m_pFontCtrl = pFontWinCtrl;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctOptBox.w, m_rctOptBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 10, 100, 10, 0));
    //SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 200); SDL 1.2
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
    rctBt1.x = ( m_rctOptBox.w - rctBt1.w) / 2 +  m_rctOptBox.x - rctBt1.w - iSpace2bt;
    m_pBtOK->Init(&rctBt1, pScreen,  m_pFontText, MYIDOK, pRenderer);
    m_pBtOK->SetState(cButtonGfx::INVISIBLE);
    
    
    // button cancel
    m_pBtCancel = new cButtonGfx;
    m_pBtCancel->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = ( m_rctOptBox.w - rctBt1.w) / 2 +  m_rctOptBox.x + rctBt1.w + iSpace2bt;
    m_pBtCancel->Init(&rctBt1, pScreen,  m_pFontText, MYIDCANCEL, pRenderer);
    m_pBtCancel->SetState(cButtonGfx::INVISIBLE);
    
    // check box music
    m_pCheckMusic = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + 60;
    rctBt1.x = m_pBtOK->m_rctButt.x ;
    m_pCheckMusic->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckMusic->Init(&rctBt1, pScreen,  m_pFontText, MYIDMUSICCHK);
    m_pCheckMusic->SetState(cCheckBoxGfx::INVISIBLE);

    //checkbox sound effect
    m_pCheckSoundEffect = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pCheckMusic->m_rctButt.y + 40;
    rctBt1.x = m_pCheckMusic->m_rctButt.x;
    m_pCheckSoundEffect->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckSoundEffect->Init(&rctBt1, pScreen,  m_pFontText, MYIDSOUNDEFFECT);
    m_pCheckSoundEffect->SetState(cCheckBoxGfx::INVISIBLE);


    // edit name 
    m_pEditName = new cEditGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pCheckSoundEffect->m_rctButt.y + m_pCheckMusic->m_rctButt.h  + 30;
    rctBt1.x = m_pBtOK->m_rctButt.x ;
    m_pEditName->Init(&rctBt1, pScreen,  m_pFontText, MYEDITNAME, pRenderer);
    m_pEditName->SetState(cEditGfx::INVISIBLE);

    // combo language
    m_pComboLang = new cComboGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pEditName->m_rctButt.y + m_pEditName->m_rctButt.h  + 35;
    rctBt1.x = m_pBtOK->m_rctButt.x ;
    m_pComboLang->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ComboCmdClicked);
    m_pComboLang->Init(&rctBt1, pScreen,  m_pFontText, MYIDCOMBOLAN, pRenderer);
    m_pComboLang->SetState(cComboGfx::INVISIBLE);

    // combo alg player 1
    m_pComboAlg_Pl_1 = new cComboGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pComboLang->m_rctButt.y + m_pComboLang->m_rctButt.h  + 65;
    rctBt1.x = m_pComboLang->m_rctButt.x ;
    m_pComboAlg_Pl_1->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ComboCmdClicked);
    m_pComboAlg_Pl_1->Init(&rctBt1, pScreen,  m_pFontText, MYIDCOMBOALG_PL1, pRenderer);
    m_pComboAlg_Pl_1->SetState(cComboGfx::INVISIBLE);

    // combo alg player 2
    m_pComboAlg_Pl_2 = new cComboGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pComboAlg_Pl_1->m_rctButt.y + m_pComboAlg_Pl_1->m_rctButt.h  + 35;
    rctBt1.x = m_pComboAlg_Pl_1->m_rctButt.x ;
    m_pComboAlg_Pl_2->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ComboCmdClicked);
    m_pComboAlg_Pl_2->Init(&rctBt1, pScreen,  m_pFontText, MYIDCOMBOALG_PL2, pRenderer);
    m_pComboAlg_Pl_2->SetState(cComboGfx::INVISIBLE);

    // combo alg player 3
    m_pComboAlg_Pl_3 = new cComboGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pComboLang->m_rctButt.y + m_pComboLang->m_rctButt.h  + 65;
    rctBt1.x = m_pComboAlg_Pl_1->m_rctButt.x +  m_pComboAlg_Pl_1->m_rctButt.w + 50;
    m_pComboAlg_Pl_3->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ComboCmdClicked);
    m_pComboAlg_Pl_3->Init(&rctBt1, pScreen,  m_pFontText, MYIDCOMBOALG_PL3, pRenderer);
    m_pComboAlg_Pl_3->SetState(cComboGfx::INVISIBLE);

    // combo alg player 4
    m_pComboAlg_Pl_4 = new cComboGfx;
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_pComboAlg_Pl_2->m_rctButt.y ;
    rctBt1.x = m_pComboAlg_Pl_3->m_rctButt.x ;
    m_pComboAlg_Pl_4->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ComboCmdClicked);
    m_pComboAlg_Pl_4->Init(&rctBt1, pScreen,  m_pFontText, MYIDCOMBOALG_PL4, pRenderer);
    m_pComboAlg_Pl_4->SetState(cComboGfx::INVISIBLE);

    // checkbox shows alg control
    m_pCheckShowAlgControl = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pComboLang->m_rctButt.y;
    rctBt1.x = m_pComboAlg_Pl_3->m_rctButt.x;
    m_pCheckShowAlgControl->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckShowAlgControl->Init(&rctBt1, pScreen,  m_pFontText, MYIDCHKSHOWALGCONTROL);
    m_pCheckShowAlgControl->SetState(cCheckBoxGfx::INVISIBLE);

    // checkbox signal with right mouse button
    m_pCheckSignalRightMouse = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pCheckMusic->m_rctButt.y;
    rctBt1.x = m_pComboAlg_Pl_3->m_rctButt.x;
    m_pCheckSignalRightMouse->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckSignalRightMouse->Init(&rctBt1, pScreen,  m_pFontText, MYIDCHKSIGNALRMOUSE);
    m_pCheckSignalRightMouse->SetState(cCheckBoxGfx::INVISIBLE);
    

    // checkbox continue after mano end
    m_pCheckBlockAfterManoend = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pCheckSignalRightMouse->m_rctButt.y + 40;
    rctBt1.x = m_pComboAlg_Pl_3->m_rctButt.x;
    m_pCheckBlockAfterManoend->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckBlockAfterManoend->Init(&rctBt1, pScreen,  m_pFontText, MYIDCHKBLOCKAFTERMANOEND);
    m_pCheckBlockAfterManoend->SetState(cCheckBoxGfx::INVISIBLE);
    
    // checkbox show animations
    m_pCheckShowAnimations = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pCheckBlockAfterManoend->m_rctButt.y + 40;
    rctBt1.x = m_pComboAlg_Pl_3->m_rctButt.x;
    m_pCheckShowAnimations->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pCheckShowAnimations->Init(&rctBt1, pScreen,  m_pFontText, MYIDCHKSHOWANIMATIONS);
    m_pCheckShowAnimations->SetState(cCheckBoxGfx::INVISIBLE);

    // progressbar animation speed
    m_pProgSpeedAni = new cProgressBarGfx;
    rctBt1.w = 140;
    rctBt1.h = 28;
    rctBt1.y = m_pCheckShowAnimations->m_rctButt.y + 30;
    rctBt1.x = m_pCheckShowAlgControl->m_rctButt.x;
    m_pProgSpeedAni->m_fncbClickEvent = MakeDelegate(this, &OptionGfx::ClickCheckBox);
    m_pProgSpeedAni->Init(&rctBt1, pScreen, NULL,  m_pFontText, MYIDPROGBARSPEEDANI, pRenderer);
    m_pProgSpeedAni->SetState(cProgressBarGfx::INVISIBLE);

    
}


////////////////////////////////////////
//       findDllInstalled
/*! 
// \param VCT_STRING& vctInstPlug : 
// \param VCT_STRING& vctEngNam : 
*/
void OptionGfx::findDllInstalled(VCT_STRING& vctInstPlug, VCT_STRING& vctEngNam)
{
#ifdef WIN32
    typedef void (__stdcall *tFN_GetName )(char* pOutName);
    WIN32_FIND_DATA fd;
    STRING strFilter = stalpszPluginDir;
    strFilter +=  "*.dll";
    HANDLE hFind;
    STRING strPlugName;
    STRING strEngineName;

    if ((hFind = ::FindFirstFile (strFilter.c_str() , &fd)) != INVALID_HANDLE_VALUE) 
    {
        do
        {
            strPlugName = stalpszPluginDir;
            strPlugName +=  fd.cFileName;
            
            // retrive the plugin-name
            HMODULE hDll = LoadLibrary(strPlugName.c_str());
            if (hDll)
            {
                char buffName[512];
                tFN_GetName  fnGetName;
                fnGetName         = (tFN_GetName)GetProcAddress(hDll, "GetName" );
                if (fnGetName)
                {
                    fnGetName(buffName);
                    strEngineName = buffName;

                    // ok plugin is compatible
                    vctEngNam.push_back(strEngineName);
                    vctInstPlug.push_back(strPlugName);
                }


                //FreeLibrary(hDll); 
            }
            
        }
        while (::FindNextFile (hFind, &fd)) ;

        ::FindClose (hFind);
    }
    
#endif
}

////////////////////////////////////////
//       showComboBox_AlgPlayers
/*! Prepare data for comboboxs of players algorithm.
*/
void  OptionGfx::showComboBox_AlgPlayers()
{
    // retrieve the list of installed plugins
    m_vct_InstPlugDllName.clear();
    m_vct_PlugEngineName.clear();

    //get the list of installed plugins
    findDllInstalled(m_vct_InstPlugDllName, m_vct_PlugEngineName);

    // combobox algorithm players
    m_pComboAlg_Pl_1->AddLineText(stalpszUSER);

    m_pComboAlg_Pl_1->AddLineText(stalpszCPUDEFAULT);
    m_pComboAlg_Pl_2->AddLineText(stalpszCPUDEFAULT);
    m_pComboAlg_Pl_3->AddLineText(stalpszCPUDEFAULT);
    m_pComboAlg_Pl_4->AddLineText(stalpszCPUDEFAULT);

    // add the additional algorithm 
    for (UINT i = 0; i < m_vct_InstPlugDllName.size(); i++)
    {
        m_pComboAlg_Pl_1->AddLineText(m_vct_PlugEngineName[i].c_str());
        m_pComboAlg_Pl_2->AddLineText(m_vct_PlugEngineName[i].c_str());
        m_pComboAlg_Pl_3->AddLineText(m_vct_PlugEngineName[i].c_str());
        m_pComboAlg_Pl_4->AddLineText(m_vct_PlugEngineName[i].c_str());
    }

    m_pComboAlg_Pl_1->SetState(cComboGfx::VISIBLE); 
    m_pComboAlg_Pl_2->SetState(cComboGfx::VISIBLE); 
    m_pComboAlg_Pl_3->SetState(cComboGfx::VISIBLE); 
    m_pComboAlg_Pl_4->SetState(cComboGfx::VISIBLE); 
    // select the  level for each player

    // player 1
    if ((eGameLevel)g_Options.Match.iLevel_Pl_1 == HMI )
    {
        m_pComboAlg_Pl_1->SelectIndex(0);
    }
    else if ((eGameLevel)g_Options.Match.iLevel_Pl_1 == PLUGIN)
    {
        BOOL bFound = FALSE;
        for (UINT i = 0; i  < m_vct_PlugEngineName.size(); i++)
        {
            if (m_vct_PlugEngineName[i].compare(g_Options.Match.strAlgPlugin_Pl_1) == 0)
            {
                // plugin found
                m_pComboAlg_Pl_1->SelectIndex(i + 2);
                bFound = TRUE;
                break;
            }
        }
        if (!bFound)
        {
            // plugin name not found, select the default value
            m_pComboAlg_Pl_1->SelectIndex(0);
        }
    }
    else
    {
        // select the default alg type
        m_pComboAlg_Pl_1->SelectIndex(1);
    }
    // player 2
    if ((eGameLevel)g_Options.Match.iLevel_Pl_2 == PLUGIN)
    {
        // algorithm is a plugin
        BOOL bFound = FALSE;
        for (UINT i = 0; i  < m_vct_PlugEngineName.size(); i++)
        {
            if (m_vct_PlugEngineName[i].compare(g_Options.Match.strAlgPlugin_Pl_2) == 0)
            {
                // plugin found
                m_pComboAlg_Pl_2->SelectIndex(i + 1);
                bFound = TRUE;
                break;
            }
        }
        if (!bFound)
        {
            // plugin name not found, select the default value
            m_pComboAlg_Pl_2->SelectIndex(0);
        }
    }
    else
    {
        // select the default alg type
        m_pComboAlg_Pl_2->SelectIndex(0);
    }
    // player 3
    if ((eGameLevel)g_Options.Match.iLevel_Pl_3 == PLUGIN)
    {
        // algorithm is a plugin
        BOOL bFound = FALSE;
        for (UINT i = 0; i  < m_vct_PlugEngineName.size(); i++)
        {
            if (m_vct_PlugEngineName[i].compare(g_Options.Match.strAlgPlugin_Pl_3) == 0)
            {
                // plugin found
                m_pComboAlg_Pl_3->SelectIndex(i + 1);
                bFound = TRUE;
                break;
            }
        }
        if (!bFound)
        {
            // plugin name not found, select the default value
            m_pComboAlg_Pl_3->SelectIndex(0);
        }
    }
    else
    {
        // select the default alg type
        m_pComboAlg_Pl_3->SelectIndex(0);
    }
    // player 4
    if ((eGameLevel)g_Options.Match.iLevel_Pl_4 == PLUGIN)
    {
        // algorithm is a plugin
        BOOL bFound = FALSE;
        for (UINT i = 0; i  < m_vct_PlugEngineName.size(); i++)
        {
            if (m_vct_PlugEngineName[i].compare(g_Options.Match.strAlgPlugin_Pl_4) == 0)
            {
                // plugin found
                m_pComboAlg_Pl_4->SelectIndex(i + 1);
                bFound = TRUE;
                break;
            }
        }
        if (!bFound)
        {
            // plugin name not found, select the default value
            m_pComboAlg_Pl_4->SelectIndex(0);
        }
    }
    else
    {
        // select the default alg type
        m_pComboAlg_Pl_4->SelectIndex(0);
    }

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

    // checkbox show alg controls
    strTextBt = pLan->GetStringId(cLanguages::ID_SHOWALGCONTROL);
    m_pCheckShowAlgControl->SetWindowText(strTextBt.c_str()); 

// in this version disable algorithms in dll
///m_pCheckShowAlgControl->SetState(cCheckBoxGfx::VISIBLE); 
    m_pCheckShowAlgControl->SetCheckState(FALSE);

    // checkbox use right mouse for signals
    strTextBt = pLan->GetStringId(cLanguages::ID_SIGNARMOUSEBT);
    m_pCheckSignalRightMouse->SetWindowText(strTextBt.c_str()); 
    m_pCheckSignalRightMouse->SetState(cCheckBoxGfx::VISIBLE); 
    m_pCheckSignalRightMouse->SetCheckState(g_Options.All.bSignalWithRMouse);

    // checkbox block after mano end
    strTextBt = pLan->GetStringId(cLanguages::ID_BLOCKONMANOEND);
    m_pCheckBlockAfterManoend->SetWindowText(strTextBt.c_str()); 
    m_pCheckBlockAfterManoend->SetState(cCheckBoxGfx::VISIBLE); 
    m_pCheckBlockAfterManoend->SetCheckState(g_Options.All.bBlockOnManoEnd);

    // checkbox show animations
    strTextBt = pLan->GetStringId(cLanguages::ID_SHOWCARDANIMATION);
    m_pCheckShowAnimations->SetWindowText(strTextBt.c_str()); 
    m_pCheckShowAnimations->SetState(cCheckBoxGfx::VISIBLE); 
    m_pCheckShowAnimations->SetCheckState(g_Options.All.bAnimatePlayCard);

    // progress bar speed animation
    m_pProgSpeedAni->SetState(cProgressBarGfx::VISIBLE);
    m_pProgSpeedAni->SetNumStep(6);
    m_pProgSpeedAni->SetRange(0,5);
    m_pProgSpeedAni->SetCurrLevel(g_Options.All.iAniSpeedLevel);
    m_bShowProgSpeedAni = m_pCheckShowAnimations->GetCheckState(); 
    strTextBt = pLan->GetStringId(cLanguages::ID_SPEED_SLOW);
    m_pProgSpeedAni->SetLabelBEG(strTextBt.c_str());
    strTextBt = pLan->GetStringId(cLanguages::ID_SPEED_FAST);
    m_pProgSpeedAni->SetLabelEND(strTextBt.c_str()); 
    
    // combo algorithm players
    showComboBox_AlgPlayers();

    STRING strPlayer1 = pLan->GetStringId(cLanguages::ID_CP_PLAYER);
    STRING strPlayer2 = strPlayer1 + " 2";
    STRING strPlayer3 = strPlayer1 + " 3";
    STRING strPlayer4 = strPlayer1 + " 4";
    strPlayer1 += " 1";

    STRING strFrameAlg = pLan->GetStringId(cLanguages::ID_MANAGEPLAYER);

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
            if(event.type == SDL_QUIT) 
            {
                m_bTerminated = TRUE;
                break;
            }
            if(event.type == SDL_KEYDOWN) 
            {
                if(event.key.keysym.sym == SDLK_RETURN) 
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
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                
            }
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                m_pBtCancel->MouseUp(event); 
                m_pBtOK->MouseUp(event); 
                m_pCheckMusic->MouseUp(event);
                m_pCheckSoundEffect->MouseUp(event);
                m_pEditName->MouseUp(event);
                m_pComboLang->MouseUp(event);
                m_pComboAlg_Pl_1->MouseUp(event);
                m_pComboAlg_Pl_2->MouseUp(event);
                m_pComboAlg_Pl_3->MouseUp(event);
                m_pComboAlg_Pl_4->MouseUp(event);
                m_pCheckShowAlgControl->MouseUp(event);
                m_pCheckShowAnimations->MouseUp(event);
                m_pProgSpeedAni->MouseUp(event);
                m_pCheckBlockAfterManoend->MouseUp(event); 
                m_pCheckSignalRightMouse->MouseUp(event);
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                
                m_pProgSpeedAni->MouseDown(event);
            }
        }
        

        // the msg box
        GFX_UTIL::DrawStaticSpriteEx(pShadowSrf, 0, 0, m_rctOptBox.w, m_rctOptBox.h, m_rctOptBox.x, 
                                     m_rctOptBox.y, m_pSurf_Bar);
        // draw border
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x-1, m_rctOptBox.y-1, m_rctOptBox.x + m_rctOptBox.w + 1, 
                            m_rctOptBox.y + m_rctOptBox.h + 1, GFX_UTIL_COLOR::Gray );
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x-2, m_rctOptBox.y-2, m_rctOptBox.x + m_rctOptBox.w + 2,
                            m_rctOptBox.y + m_rctOptBox.h + 2, GFX_UTIL_COLOR::Black);
        GFX_UTIL::DrawRect(pShadowSrf, m_rctOptBox.x, m_rctOptBox.y, m_rctOptBox.x +  m_rctOptBox.w, 
                            m_rctOptBox.y + m_rctOptBox.h , m_colCurrent);

        //header bar
        SDL_Rect  rectHeader;
        Uint32 colorHeader = SDL_MapRGB(m_pScreen->format, 153, 202, 51);
        rectHeader.x = m_rctOptBox.x + 1;
        rectHeader.y = m_rctOptBox.y + 1;
        rectHeader.h = 30;
        rectHeader.w = m_rctOptBox.w-1;
        SDL_FillRect(pShadowSrf, &rectHeader, colorHeader);
        GFX_UTIL::DrawStaticLine(pShadowSrf, rectHeader.x, rectHeader.y + rectHeader.h, 
                          rectHeader.x + rectHeader.w, rectHeader.y + rectHeader.h, GFX_UTIL_COLOR::White);
        // text header
        GFX_UTIL::DrawString(pShadowSrf, m_strHeaderText.c_str(), rectHeader.x + 10 , 
                                 rectHeader.y, GFX_UTIL_COLOR::White, m_pFontCtrl, false);
        

        // draw buttons
        m_pBtOK->DrawButton(pShadowSrf); 
        m_pBtCancel->DrawButton(pShadowSrf); 
        // draw checkbox music
        m_pCheckMusic->DrawButton(pShadowSrf);
        //draw checkbox sound effect
        m_pCheckSoundEffect->DrawButton(pShadowSrf);
        
        // name label
        GFX_UTIL::DrawString(pShadowSrf, strNameTitle.c_str(), m_pEditName->m_rctButt.x , 
                    m_pEditName->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText, false);

        // draw edit name control
        m_pEditName->DrawControl(pShadowSrf); 
        
        // language selection label
        GFX_UTIL::DrawString(pShadowSrf, strLangSelectTitle.c_str(), m_pComboLang->m_rctButt.x , 
                    m_pComboLang->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText, false);

        // draw the language combobox selection
        m_pComboLang->DrawButton(pShadowSrf); 

        // draw checkbox show alg controls
        m_pCheckShowAlgControl->DrawButton(pShadowSrf); 

        // draw checkbox use rmouse for signal
        m_pCheckSignalRightMouse->DrawButton(pShadowSrf);

        // draw checkbox pause on  mano end
        m_pCheckBlockAfterManoend->DrawButton(pShadowSrf);

        // draw checkbox show animations
        m_pCheckShowAnimations->DrawButton(pShadowSrf);

        // draw progressbar speed animation control
        if (m_bShowProgSpeedAni)
        {
            m_pProgSpeedAni->DrawControl(pShadowSrf); 
        }

        if (m_bShowAlgControls)
        {
            // draw frame on alg player
            int iFrameOffset = 15;
            GFX_UTIL::DrawRect(pShadowSrf, m_pComboAlg_Pl_1->m_rctButt.x - iFrameOffset, m_pComboAlg_Pl_1->m_rctButt.y - 45, 
                   m_pComboAlg_Pl_3->m_rctButt.x +  m_pComboAlg_Pl_3->m_rctButt.w + iFrameOffset, 
                   m_pComboAlg_Pl_4->m_rctButt.y + m_pComboAlg_Pl_4->m_rctButt.h + iFrameOffset, GFX_UTIL_COLOR::Gray  );
            GFX_UTIL::DrawRect(pShadowSrf, m_pComboAlg_Pl_1->m_rctButt.x - iFrameOffset+1, m_pComboAlg_Pl_1->m_rctButt.y - 45+1, 
                   m_pComboAlg_Pl_3->m_rctButt.x +  m_pComboAlg_Pl_3->m_rctButt.w + iFrameOffset +1, 
                   m_pComboAlg_Pl_4->m_rctButt.y + m_pComboAlg_Pl_4->m_rctButt.h + iFrameOffset+1, GFX_UTIL_COLOR::Black   );

            // label frame alg
            GFX_UTIL::DrawString(pShadowSrf, strFrameAlg.c_str(), m_pComboAlg_Pl_1->m_rctButt.x , 
                m_pComboAlg_Pl_1->m_rctButt.y - 45, GFX_UTIL_COLOR::Orange    , m_pFontText, false);

            // alg player labels
            GFX_UTIL::DrawString(pShadowSrf, strPlayer1.c_str(), m_pComboAlg_Pl_1->m_rctButt.x , 
                        m_pComboAlg_Pl_1->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText, false);
            GFX_UTIL::DrawString(pShadowSrf, strPlayer2.c_str(), m_pComboAlg_Pl_2->m_rctButt.x , 
                        m_pComboAlg_Pl_2->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText, false);
            GFX_UTIL::DrawString(pShadowSrf, strPlayer3.c_str(), m_pComboAlg_Pl_3->m_rctButt.x , 
                        m_pComboAlg_Pl_3->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText, false);
            GFX_UTIL::DrawString(pShadowSrf, strPlayer4.c_str(), m_pComboAlg_Pl_4->m_rctButt.x , 
                        m_pComboAlg_Pl_4->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText, false);
        
            // draw all combo algorith selection
            m_pComboAlg_Pl_1->DrawButton(pShadowSrf);
            m_pComboAlg_Pl_2->DrawButton(pShadowSrf);
            m_pComboAlg_Pl_3->DrawButton(pShadowSrf);
            m_pComboAlg_Pl_4->DrawButton(pShadowSrf);
        }

        //render the dialogbox
        //SDL_Flip(m_pScreen);
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
            g_Options.All.strPlayerName =   m_pEditName->GetWindowText();
            g_Options.All.bMusicOn = m_pCheckMusic->GetCheckState();
            g_Options.All.iLanguageID = m_pComboLang->GetSlectedIndex();
            g_Options.All.bSoundEffect =  m_pCheckSoundEffect->GetCheckState();
            g_Options.All.bAnimatePlayCard =  m_pCheckShowAnimations->GetCheckState(); 
            g_Options.All.iAniSpeedLevel = m_pProgSpeedAni->GetCurrLevel();
            g_Options.All.bBlockOnManoEnd =  m_pCheckBlockAfterManoend->GetCheckState();
            g_Options.All.bSignalWithRMouse  = m_pCheckSignalRightMouse->GetCheckState(); 
            
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
            // update algorithm
            // player 1
            int iSelIndex = m_pComboAlg_Pl_1->GetSlectedIndex();
            if (iSelIndex == 0)
            {
                g_Options.Match.iLevel_Pl_1 = HMI; 
            }
            else if (iSelIndex == 1)
            {
                g_Options.Match.iLevel_Pl_1 = DEFAULT;
            }
            else
            {
                g_Options.Match.iLevel_Pl_1 = PLUGIN;
                g_Options.Match.strAlgPlugin_Pl_1 = m_pComboAlg_Pl_1->GetSelectedText();
                g_Options.Match.strPluginDll_Pl_1 = m_vct_InstPlugDllName[iSelIndex - 2]; 
            }
            // player 2
            iSelIndex = m_pComboAlg_Pl_2->GetSlectedIndex();
            if (iSelIndex == 0)
            {
                g_Options.Match.iLevel_Pl_2 = DEFAULT; 
            }
            else
            {
                g_Options.Match.iLevel_Pl_2 = PLUGIN;
                g_Options.Match.strAlgPlugin_Pl_2 = m_pComboAlg_Pl_2->GetSelectedText();
                g_Options.Match.strPluginDll_Pl_2 = m_vct_InstPlugDllName[iSelIndex - 1]; 
            }
            // player 3
            iSelIndex = m_pComboAlg_Pl_3->GetSlectedIndex();
            if (iSelIndex == 0)
            {
                g_Options.Match.iLevel_Pl_3 = DEFAULT; 
            }
            else
            {
                g_Options.Match.iLevel_Pl_3 = PLUGIN;
                g_Options.Match.strAlgPlugin_Pl_3 = m_pComboAlg_Pl_3->GetSelectedText();
                g_Options.Match.strPluginDll_Pl_3 = m_vct_InstPlugDllName[iSelIndex - 1]; 
            }
            // player 4
            iSelIndex = m_pComboAlg_Pl_4->GetSlectedIndex();
            if (iSelIndex == 0)
            {
                g_Options.Match.iLevel_Pl_4 = DEFAULT; 
            }
            else
            {
                g_Options.Match.iLevel_Pl_4 = PLUGIN;
                g_Options.Match.strAlgPlugin_Pl_4 = m_pComboAlg_Pl_4->GetSelectedText();
                g_Options.Match.strPluginDll_Pl_4 = m_vct_InstPlugDllName[iSelIndex - 1]; 
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
        // change state of show alg control
        if (m_pCheckShowAlgControl->GetCheckState())
        {
            // checked, shows controls
            m_bShowAlgControls = TRUE;
        }
        else
        {
            m_bShowAlgControls = FALSE;
        }
    }
    if (iButID == MYIDCHKSHOWANIMATIONS)
    {
        // change state of show alg control
        if (m_pCheckShowAnimations->GetCheckState())
        {
            // checked, shows controls
            m_bShowProgSpeedAni = TRUE;
        }
        else
        {
            m_bShowProgSpeedAni = FALSE;
        }
    }
}
