/*
    Tressette
    Copyright (C) 2005  Igor Sarzi Sartori

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Igor Sarzi Sartori
    www.invido.it
    6colpiunbucosolo@gmx.net
*/


// OptionGameGfx.cpp: implementation of the OptionGameGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OptionGameGfx.h"
#include "cButtonGfx.h"
#include "gfx_util.h"
#include "cComboGfx.h"
#include "cSettings.h"
#include "EngineApp.h"
#include "lang_gen.h"
#include "CoreEnv.h"
#include "InfoComm.h"
#include "ErrorMsg.h"
#include "cCheckBoxGfx.h"
#include "cEditGfx.h"

#include <SDL_image.h>
#include <SDL_endian.h>


extern cEngineApp* g_MainApp;

static const char* lpszMazziDir = "data/mazzi/";


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       OptionGameGfx
/*! 
*/
OptionGameGfx::OptionGameGfx()
{
    m_pScreen = 0;
    m_pFontText = 0;
    m_pSurf_Bar = 0;
    m_pBtOK = 0;
    m_pBtCancel = 0;
    m_bTerminated = FALSE;
    m_pComboLocal = 0;
    m_pCheckEnableGoodGame = 0;
    m_pEditPointsGoal = 0;
}


////////////////////////////////////////
//       ~OptionGameGfx
/*! 
*/
OptionGameGfx::~OptionGameGfx()
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
    delete m_pBtOK;
    delete m_pBtCancel;
    delete m_pComboLocal;
    delete m_pCheckEnableGoodGame;
    delete m_pEditPointsGoal;
}



////////////////////////////////////////
//       Init
/*! 
// \param SDL_Rect* pRect : 
// \param SDL_Surface*  pScreen : 
// \param TTF_Font* pFont : 
*/
void OptionGameGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl)
{
    ASSERT(pRect);
    ASSERT(pScreen);
    //ASSERT(m_pFontCtrl);
    m_rctOptBox = *pRect;
    m_pScreen = pScreen;
    m_pFontText = pFontTxt;
    m_pFontCtrl = pFontWinCtrl;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctOptBox.w, m_rctOptBox.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 10, 100, 10, 0));
    SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 200);

    SDL_Rect rctBt1;
    int iSpace2bt = 20;
    
    // button ok
    m_pBtOK = new cButtonGfx;
    m_pBtOK->m_fncbClickEvent = MakeDelegate(this, &OptionGameGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = ( m_rctOptBox.w - rctBt1.w) / 2 +  m_rctOptBox.x - rctBt1.w - iSpace2bt;
    m_pBtOK->Init(&rctBt1, pScreen,  m_pFontText, MYIDOK);
    m_pBtOK->SetState(cButtonGfx::INVISIBLE);
    
    
    // button cancel
    m_pBtCancel = new cButtonGfx;
    m_pBtCancel->m_fncbClickEvent = MakeDelegate(this, &OptionGameGfx::ButCmdClicked);
    rctBt1.w = 120;
    rctBt1.h = 28;
    rctBt1.y = m_rctOptBox.y + m_rctOptBox.h - 10 - rctBt1.h;
    rctBt1.x = ( m_rctOptBox.w - rctBt1.w) / 2 +  m_rctOptBox.x + rctBt1.w + iSpace2bt;
    m_pBtCancel->Init(&rctBt1, pScreen,  m_pFontText, MYIDCANCEL);
    m_pBtCancel->SetState(cButtonGfx::INVISIBLE);
    
    // combo deck selection
    m_pComboLocal = new cComboGfx;
    m_pComboLocal->m_fncbClickEvent = MakeDelegate(this, &OptionGameGfx::ComboCmdClicked);
    rctBt1.w = 180;
    rctBt1.h = 26;
    rctBt1.y = m_rctOptBox.y + 80;
    rctBt1.x = m_rctOptBox.x + 50;
    m_pComboLocal->Init(&rctBt1, pScreen,  m_pFontText, MYIDCOMBODECK);
    m_pComboLocal->SetState(cComboGfx::INVISIBLE);

    // checkbox enable good game 
    m_pCheckEnableGoodGame = new cCheckBoxGfx;
    rctBt1.w = 180;
    rctBt1.h = 28;
    rctBt1.y = m_pComboLocal->m_rctButt.y + m_pComboLocal->m_rctButt.h + 50;
    rctBt1.x = m_pComboLocal->m_rctButt.x;
    m_pCheckEnableGoodGame->m_fncbClickEvent = MakeDelegate(this, &OptionGameGfx::ClickCheckBox);
    m_pCheckEnableGoodGame->Init(&rctBt1, pScreen,  m_pFontText, MYIDCHECKGOODGAMECALL);
    m_pCheckEnableGoodGame->SetState(cCheckBoxGfx::INVISIBLE);

    // edit score goal
    m_pEditPointsGoal = new cEditGfx;
    rctBt1.w = 50;
    rctBt1.h = 26;
    rctBt1.y = m_pCheckEnableGoodGame->m_rctButt.y + m_pCheckEnableGoodGame->m_rctButt.h  + 30;
    rctBt1.x = m_pCheckEnableGoodGame->m_rctButt.x ;
    m_pEditPointsGoal->Init(&rctBt1, pScreen,  m_pFontText, MYEDITSCOREGOAL);
    m_pEditPointsGoal->SetState(cEditGfx::INVISIBLE);
    m_pEditPointsGoal->SetNumericOnly(TRUE); 
}


////////////////////////////////////////
//       ClickCheckBox
/*! 
// \param int iButID : 
*/
void OptionGameGfx::ClickCheckBox(int iButID)
{
    
}

////////////////////////////////////////
//       Show
/*! Shows the option window
// \param SDL_Surface* pScene_background : 
*/
void OptionGameGfx::Show(SDL_Surface* pScene_background)
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
    

    // combobox local game selection
    STRING strDeckSelectTitle = pLan->GetStringId(cLanguages::ID_CHOOSELOCALGAME);
    strTextBt = pLan->GetStringId(cLanguages::ID_LOCAL_NEUTRAL);
    m_pComboLocal->AddLineText(strTextBt.c_str());
    strTextBt = pLan->GetStringId(cLanguages::ID_LOCAL_BREDACISONI);
    m_pComboLocal->AddLineText(strTextBt.c_str());
    strTextBt = pLan->GetStringId(cLanguages::ID_LOCAL_CHITARELLA);
    m_pComboLocal->AddLineText(strTextBt.c_str());
    
    /*
    strTextBt = pLan->GetStringId(cLanguages::ID_LOCAL_ROMANA);
    m_pComboLocal->AddLineText(strTextBt.c_str());
    */
   
    m_pComboLocal->SetState(cComboGfx::VISIBLE); 
    m_pComboLocal->SelectIndex(g_Options.Match.iLocalGameType);

    // checkbox enable goodgame
    strTextBt = pLan->GetStringId(cLanguages::ID_ENABLEDECLARGG);
    m_pCheckEnableGoodGame->SetWindowText(strTextBt.c_str()); 
    m_pCheckEnableGoodGame->SetState(cCheckBoxGfx::VISIBLE); 
    m_pCheckEnableGoodGame->SetCheckState(g_Options.Match.bUseGoodGameDecla);

    //edit score goal
    CHAR buffer[128];
    sprintf(buffer, "%d", g_Options.Match.iScoreGoal);
    strTextBt = buffer ;
    STRING strScoreGoal = pLan->GetStringId(cLanguages::ID_SCOREGOAL);
    m_pEditPointsGoal->SetWindowText(strTextBt.c_str()); 
    m_pEditPointsGoal->SetState(cEditGfx::VISIBLE); 
   

    // create a shadow surface
    SDL_Surface* pShadowSrf = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);

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
                    m_pEditPointsGoal->KeyDown(event);
                }
                
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                
            }
            if(event.type == SDL_MOUSEBUTTONUP)
            {
                m_pBtCancel->MouseUp(event); 
                m_pBtOK->MouseUp(event); 
                m_pComboLocal->MouseUp(event);
                m_pCheckEnableGoodGame->MouseUp(event);
                m_pEditPointsGoal->MouseUp(event);
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
                                 rectHeader.y, GFX_UTIL_COLOR::White, m_pFontCtrl);
        

        // draw buttons
        m_pBtOK->DrawButton(pShadowSrf); 
        m_pBtCancel->DrawButton(pShadowSrf); 
       
        
        // deck selection label
        GFX_UTIL::DrawString(pShadowSrf, strDeckSelectTitle.c_str(), m_pComboLocal->m_rctButt.x , 
                    m_pComboLocal->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText);

        // draw the deck combobox selection
        m_pComboLocal->DrawButton(pShadowSrf); 

        //draw the checkbox enable goodgame
        m_pCheckEnableGoodGame->DrawButton(pShadowSrf); 

         // score goal  label
        GFX_UTIL::DrawString(pShadowSrf, strScoreGoal.c_str(), m_pEditPointsGoal->m_rctButt.x , 
                    m_pEditPointsGoal->m_rctButt.y - 20, GFX_UTIL_COLOR::Orange , m_pFontText);

        // draw the edit score goal
        m_pEditPointsGoal->DrawControl(pShadowSrf); 


        //render the dialogbox
        SDL_BlitSurface(pShadowSrf, NULL, m_pScreen, NULL);
        SDL_Flip(m_pScreen);

        // synch to frame rate
        Uint32 uiNowTime = SDL_GetTicks();
        if (uiNowTime < uiLast_time + FPS)
        {
            SDL_Delay(uiLast_time + FPS - uiNowTime);
            uiLast_time = uiNowTime;
        }
    }
    SDL_FreeSurface(pShadowSrf);
}



////////////////////////////////////////
//       ButCmdClicked
/*! button click callback
// \param int iButID : 
*/
void   OptionGameGfx::ButCmdClicked(int iButID)
{
    if (!m_bTerminated)
    {
        m_bTerminated = TRUE;
        m_iResult = iButID;
        if (iButID == MYIDOK)
        {
            // the user has pressed the button OK

            // update local prop
            g_Options.Match.iLocalGameType  = m_pComboLocal->GetSlectedIndex();
            g_Options.Match.bUseGoodGameDecla = m_pCheckEnableGoodGame->GetCheckState(); 
            int iTmp = atoi(m_pEditPointsGoal->GetWindowText());
            if (iTmp >= 6 && iTmp <= 101)
            {
                g_Options.Match.iScoreGoal = iTmp;
            }
        }
    }
}

////////////////////////////////////////
//       ComboCmdClicked
/*! Combobox callback
// \param int iButID : 
*/
void   OptionGameGfx::ComboCmdClicked(int iButID)
{

}

