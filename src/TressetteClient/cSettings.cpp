// cSettings.cpp
// Settings definition. Settings uses a persintence and a global access method.
// Automatic class implementation file generated with ruby template settings_expat_cpp.rtemp
// Please don't change me manually, but use code generator gensettings.rb
// Created at Sat Sep 02 21:45:38 +0200 2017

#include "StdAfx.h"
#include "win_type_global.h"
#include "cSettings.h"
#include <fstream>
#include "expat.h"

using namespace SpacecSettings;

// global object
cSettings g_Options;

static const char* lpszSubAll = "SubAll";
    
static const char* lpszSubAllstrPlayerName = "SubAllstrPlayerName";
  
static const char* lpszSubAlliDelayTimer = "SubAlliDelayTimer";
  
static const char* lpszSubAllbAutoterminate = "SubAllbAutoterminate";
  
static const char* lpszSubAlliLevel = "SubAlliLevel";
  
static const char* lpszSubAlliTipoMazzo = "SubAlliTipoMazzo";
  
static const char* lpszSubAlliLanguageID = "SubAlliLanguageID";
  
static const char* lpszSubAllbMusicOn = "SubAllbMusicOn";
  
static const char* lpszSubAlliMusicVolume = "SubAlliMusicVolume";
  
static const char* lpszSubAlliDebugLevel = "SubAlliDebugLevel";
  
static const char* lpszSubAllbUsePythonAsInit = "SubAllbUsePythonAsInit";
  
static const char* lpszSubAllbUsePythonNotification = "SubAllbUsePythonNotification";
  
static const char* lpszSubAllbUsePythonConsole = "SubAllbUsePythonConsole";
  
static const char* lpszSubAllstrPythonInitScriptName = "SubAllstrPythonInitScriptName";
  
static const char* lpszSubAlliVerbose = "SubAlliVerbose";
  
static const char* lpszSubAllbMyCallEcho = "SubAllbMyCallEcho";
  
static const char* lpszSubAllbSoundEffect = "SubAllbSoundEffect";
  
static const char* lpszSubAllbFotoBack = "SubAllbFotoBack";
  
static const char* lpszSubAllbAnimatePlayCard = "SubAllbAnimatePlayCard";
  
static const char* lpszSubAlliAniSpeedLevel = "SubAlliAniSpeedLevel";
  
static const char* lpszSubAllbBlockOnManoEnd = "SubAllbBlockOnManoEnd";
  
static const char* lpszSubAllbSignalWithRMouse = "SubAllbSignalWithRMouse";
  

static const char* lpszSubNetwork = "SubNetwork";
    
static const char* lpszSubNetworkstrServerName = "SubNetworkstrServerName";
  
static const char* lpszSubNetworkstrPeerName = "SubNetworkstrPeerName";
  
static const char* lpszSubNetworkiPortServer = "SubNetworkiPortServer";
  
static const char* lpszSubNetworkiPortClient = "SubNetworkiPortClient";
  
static const char* lpszSubNetworkstrLogin = "SubNetworkstrLogin";
  
static const char* lpszSubNetworkstrPassw = "SubNetworkstrPassw";
  

static const char* lpszSubMatch = "SubMatch";
    
static const char* lpszSubMatchiLocalGameType = "SubMatchiLocalGameType";
  
static const char* lpszSubMatchbUseGoodGameDecla = "SubMatchbUseGoodGameDecla";
  
static const char* lpszSubMatchiScoreGoal = "SubMatchiScoreGoal";
  
static const char* lpszSubMatchstrPlayerName_2 = "SubMatchstrPlayerName_2";
  
static const char* lpszSubMatchstrPlayerName_3 = "SubMatchstrPlayerName_3";
  
static const char* lpszSubMatchstrPlayerName_4 = "SubMatchstrPlayerName_4";
  
static const char* lpszSubMatchiLevel_Pl_1 = "SubMatchiLevel_Pl_1";
  
static const char* lpszSubMatchiLevel_Pl_2 = "SubMatchiLevel_Pl_2";
  
static const char* lpszSubMatchiLevel_Pl_3 = "SubMatchiLevel_Pl_3";
  
static const char* lpszSubMatchiLevel_Pl_4 = "SubMatchiLevel_Pl_4";
  
static const char* lpszSubMatchstrAlgPlugin_Pl_1 = "SubMatchstrAlgPlugin_Pl_1";
  
static const char* lpszSubMatchstrAlgPlugin_Pl_2 = "SubMatchstrAlgPlugin_Pl_2";
  
static const char* lpszSubMatchstrAlgPlugin_Pl_3 = "SubMatchstrAlgPlugin_Pl_3";
  
static const char* lpszSubMatchstrAlgPlugin_Pl_4 = "SubMatchstrAlgPlugin_Pl_4";
  
static const char* lpszSubMatchstrPluginDll_Pl_1 = "SubMatchstrPluginDll_Pl_1";
  
static const char* lpszSubMatchstrPluginDll_Pl_2 = "SubMatchstrPluginDll_Pl_2";
  
static const char* lpszSubMatchstrPluginDll_Pl_3 = "SubMatchstrPluginDll_Pl_3";
  
static const char* lpszSubMatchstrPluginDll_Pl_4 = "SubMatchstrPluginDll_Pl_4";
  


static const char* lpszTAB2  = "  ";
static const char* lpszTAB4  = "    ";



//! constructor
cSettings::cSettings()
{
}


cSettings::SubAll::SubAll()
{
  
  
  strPlayerName = "Remigio";
  
  
  iDelayTimer = 300;
  
  
  bAutoterminate = 1;
  
  
  iLevel = 1;
  
  
  iTipoMazzo = 0;
  
  
  iLanguageID = 0;
  
  
  bMusicOn = 1;
  
  
  iMusicVolume = 80;
  
  
  iDebugLevel = 2;
  
  
  bUsePythonAsInit = 0;
  
  
  bUsePythonNotification = 0;
  
  
  bUsePythonConsole = 0;
  
  
  strPythonInitScriptName = "";
  
  
  iVerbose = 3;
  
  
  bMyCallEcho = 1;
  
  
  bSoundEffect = 1;
  
  
  bFotoBack = 1;
  
  
  bAnimatePlayCard = 1;
  
  
  iAniSpeedLevel = 0;
  
  
  bBlockOnManoEnd = 0;
  
  
  bSignalWithRMouse = 1;
  
}

cSettings::SubNetwork::SubNetwork()
{
  
  
  strServerName = "127.0.0.1";
  
  
  strPeerName = "127.0.0.1";
  
  
  iPortServer = 8790;
  
  
  iPortClient = 8791;
  
  
  strLogin = "";
  
  
  strPassw = "";
  
}

cSettings::SubMatch::SubMatch()
{
  
  
  iLocalGameType = 1;
  
  
  bUseGoodGameDecla = 1;
  
  
  iScoreGoal = 33;
  
  
  strPlayerName_2 = "Bombolo";
  
  
  strPlayerName_3 = "Socio";
  
  
  strPlayerName_4 = "Cucciolo";
  
  
  iLevel_Pl_1 = 4;
  
  
  iLevel_Pl_2 = 0;
  
  
  iLevel_Pl_3 = 0;
  
  
  iLevel_Pl_4 = 0;
  
  
  strAlgPlugin_Pl_1 = "";
  
  
  strAlgPlugin_Pl_2 = "";
  
  
  strAlgPlugin_Pl_3 = "";
  
  
  strAlgPlugin_Pl_4 = "";
  
  
  strPluginDll_Pl_1 = "";
  
  
  strPluginDll_Pl_2 = "";
  
  
  strPluginDll_Pl_3 = "";
  
  
  strPluginDll_Pl_4 = "";
  
}


//! Write the object g_Options in the xml file
void SpacecSettings::WriteProfile(const char* lpszFileName)
{
  std::ofstream out_settings;
  out_settings.open( lpszFileName );
  out_settings << "<settings>\n"; 
  
out_settings << lpszTAB2 << "<SubAll>\n";
    
      
    out_settings << lpszTAB4 << "<SubAllstrPlayerName>" << g_Options.All.strPlayerName.c_str() << "</SubAllstrPlayerName>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliDelayTimer>" << g_Options.All.iDelayTimer << "</SubAlliDelayTimer>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbAutoterminate>" << g_Options.All.bAutoterminate << "</SubAllbAutoterminate>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliLevel>" << g_Options.All.iLevel << "</SubAlliLevel>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliTipoMazzo>" << g_Options.All.iTipoMazzo << "</SubAlliTipoMazzo>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliLanguageID>" << g_Options.All.iLanguageID << "</SubAlliLanguageID>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbMusicOn>" << g_Options.All.bMusicOn << "</SubAllbMusicOn>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliMusicVolume>" << g_Options.All.iMusicVolume << "</SubAlliMusicVolume>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliDebugLevel>" << g_Options.All.iDebugLevel << "</SubAlliDebugLevel>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbUsePythonAsInit>" << g_Options.All.bUsePythonAsInit << "</SubAllbUsePythonAsInit>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbUsePythonNotification>" << g_Options.All.bUsePythonNotification << "</SubAllbUsePythonNotification>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbUsePythonConsole>" << g_Options.All.bUsePythonConsole << "</SubAllbUsePythonConsole>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllstrPythonInitScriptName>" << g_Options.All.strPythonInitScriptName.c_str() << "</SubAllstrPythonInitScriptName>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliVerbose>" << g_Options.All.iVerbose << "</SubAlliVerbose>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbMyCallEcho>" << g_Options.All.bMyCallEcho << "</SubAllbMyCallEcho>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbSoundEffect>" << g_Options.All.bSoundEffect << "</SubAllbSoundEffect>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbFotoBack>" << g_Options.All.bFotoBack << "</SubAllbFotoBack>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbAnimatePlayCard>" << g_Options.All.bAnimatePlayCard << "</SubAllbAnimatePlayCard>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAlliAniSpeedLevel>" << g_Options.All.iAniSpeedLevel << "</SubAlliAniSpeedLevel>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbBlockOnManoEnd>" << g_Options.All.bBlockOnManoEnd << "</SubAllbBlockOnManoEnd>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubAllbSignalWithRMouse>" << g_Options.All.bSignalWithRMouse << "</SubAllbSignalWithRMouse>\n";
      
    
  out_settings << lpszTAB2 << "</SubAll>\n";
  
out_settings << lpszTAB2 << "<SubNetwork>\n";
    
      
    out_settings << lpszTAB4 << "<SubNetworkstrServerName>" << g_Options.Net.strServerName.c_str() << "</SubNetworkstrServerName>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubNetworkstrPeerName>" << g_Options.Net.strPeerName.c_str() << "</SubNetworkstrPeerName>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubNetworkiPortServer>" << g_Options.Net.iPortServer << "</SubNetworkiPortServer>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubNetworkiPortClient>" << g_Options.Net.iPortClient << "</SubNetworkiPortClient>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubNetworkstrLogin>" << g_Options.Net.strLogin.c_str() << "</SubNetworkstrLogin>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubNetworkstrPassw>" << g_Options.Net.strPassw.c_str() << "</SubNetworkstrPassw>\n";
      
    
  out_settings << lpszTAB2 << "</SubNetwork>\n";
  
out_settings << lpszTAB2 << "<SubMatch>\n";
    
      
    out_settings << lpszTAB4 << "<SubMatchiLocalGameType>" << g_Options.Match.iLocalGameType << "</SubMatchiLocalGameType>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchbUseGoodGameDecla>" << g_Options.Match.bUseGoodGameDecla << "</SubMatchbUseGoodGameDecla>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchiScoreGoal>" << g_Options.Match.iScoreGoal << "</SubMatchiScoreGoal>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPlayerName_2>" << g_Options.Match.strPlayerName_2.c_str() << "</SubMatchstrPlayerName_2>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPlayerName_3>" << g_Options.Match.strPlayerName_3.c_str() << "</SubMatchstrPlayerName_3>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPlayerName_4>" << g_Options.Match.strPlayerName_4.c_str() << "</SubMatchstrPlayerName_4>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchiLevel_Pl_1>" << g_Options.Match.iLevel_Pl_1 << "</SubMatchiLevel_Pl_1>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchiLevel_Pl_2>" << g_Options.Match.iLevel_Pl_2 << "</SubMatchiLevel_Pl_2>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchiLevel_Pl_3>" << g_Options.Match.iLevel_Pl_3 << "</SubMatchiLevel_Pl_3>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchiLevel_Pl_4>" << g_Options.Match.iLevel_Pl_4 << "</SubMatchiLevel_Pl_4>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrAlgPlugin_Pl_1>" << g_Options.Match.strAlgPlugin_Pl_1.c_str() << "</SubMatchstrAlgPlugin_Pl_1>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrAlgPlugin_Pl_2>" << g_Options.Match.strAlgPlugin_Pl_2.c_str() << "</SubMatchstrAlgPlugin_Pl_2>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrAlgPlugin_Pl_3>" << g_Options.Match.strAlgPlugin_Pl_3.c_str() << "</SubMatchstrAlgPlugin_Pl_3>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrAlgPlugin_Pl_4>" << g_Options.Match.strAlgPlugin_Pl_4.c_str() << "</SubMatchstrAlgPlugin_Pl_4>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPluginDll_Pl_1>" << g_Options.Match.strPluginDll_Pl_1.c_str() << "</SubMatchstrPluginDll_Pl_1>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPluginDll_Pl_2>" << g_Options.Match.strPluginDll_Pl_2.c_str() << "</SubMatchstrPluginDll_Pl_2>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPluginDll_Pl_3>" << g_Options.Match.strPluginDll_Pl_3.c_str() << "</SubMatchstrPluginDll_Pl_3>\n";
      
    
      
    out_settings << lpszTAB4 << "<SubMatchstrPluginDll_Pl_4>" << g_Options.Match.strPluginDll_Pl_4.c_str() << "</SubMatchstrPluginDll_Pl_4>\n";
      
    
  out_settings << lpszTAB2 << "</SubMatch>\n";
  
  
  out_settings << "</settings>\n";
  out_settings.close(); 
}





static void XMLCALL
startElement(void *userData, const char *name, const char **atts)
{
    XML_MYUSERDATA* pmyUserData = (XML_MYUSERDATA*)userData; 
    
    
    if ( strcmp("SubAllstrPlayerName", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.All.strPlayerName;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliDelayTimer", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iDelayTimer;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbAutoterminate", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bAutoterminate;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliLevel", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iLevel;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliTipoMazzo", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iTipoMazzo;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliLanguageID", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iLanguageID;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbMusicOn", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bMusicOn;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliMusicVolume", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iMusicVolume;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliDebugLevel", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iDebugLevel;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbUsePythonAsInit", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bUsePythonAsInit;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbUsePythonNotification", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bUsePythonNotification;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbUsePythonConsole", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bUsePythonConsole;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllstrPythonInitScriptName", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.All.strPythonInitScriptName;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliVerbose", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iVerbose;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbMyCallEcho", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bMyCallEcho;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbSoundEffect", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bSoundEffect;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbFotoBack", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bFotoBack;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbAnimatePlayCard", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bAnimatePlayCard;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAlliAniSpeedLevel", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.iAniSpeedLevel;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbBlockOnManoEnd", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bBlockOnManoEnd;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubAllbSignalWithRMouse", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.All.bSignalWithRMouse;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
  
    
    if ( strcmp("SubNetworkstrServerName", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Net.strServerName;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubNetworkstrPeerName", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Net.strPeerName;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubNetworkiPortServer", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Net.iPortServer;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubNetworkiPortClient", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Net.iPortClient;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubNetworkstrLogin", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Net.strLogin;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubNetworkstrPassw", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Net.strPassw;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
  
    
    if ( strcmp("SubMatchiLocalGameType", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.iLocalGameType;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchbUseGoodGameDecla", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.bUseGoodGameDecla;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchiScoreGoal", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.iScoreGoal;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPlayerName_2", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPlayerName_2;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPlayerName_3", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPlayerName_3;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPlayerName_4", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPlayerName_4;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchiLevel_Pl_1", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.iLevel_Pl_1;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchiLevel_Pl_2", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.iLevel_Pl_2;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchiLevel_Pl_3", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.iLevel_Pl_3;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchiLevel_Pl_4", name) == 0)
    {
    
        (*pmyUserData).pIntValue = &g_Options.Match.iLevel_Pl_4;
        (*pmyUserData).bIsString = FALSE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrAlgPlugin_Pl_1", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strAlgPlugin_Pl_1;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrAlgPlugin_Pl_2", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strAlgPlugin_Pl_2;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrAlgPlugin_Pl_3", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strAlgPlugin_Pl_3;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrAlgPlugin_Pl_4", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strAlgPlugin_Pl_4;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPluginDll_Pl_1", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPluginDll_Pl_1;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPluginDll_Pl_2", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPluginDll_Pl_2;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPluginDll_Pl_3", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPluginDll_Pl_3;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
    if ( strcmp("SubMatchstrPluginDll_Pl_4", name) == 0)
    {
    
        (*pmyUserData).pStringValue = &g_Options.Match.strPluginDll_Pl_4;
        (*pmyUserData).bIsString = TRUE;
    
        (*pmyUserData).bCopyData = TRUE;
        return ;
    }
    
  
}

static void XMLCALL
endElement(void *userData, const char *name)
{
    XML_MYUSERDATA* pmyUserData = (XML_MYUSERDATA*)userData;
    (*pmyUserData).bCopyData = FALSE;
} 

static void XMLCALL
charhndl(void *userData, const XML_Char *s, int len)
{
    XML_MYUSERDATA* pmyUserData = (XML_MYUSERDATA*)userData;
    if ((*pmyUserData).bCopyData)
    {
        STRING strValue;
        char* pValS = const_cast<char*>(s);
        char c;
        int iIndex = 0;
        c = pValS[iIndex];

        while (c != '<' && 
               c != '\0' )
        {
            strValue.append(1, c);
            iIndex++;
            c = pValS[iIndex];
        }
        (*pmyUserData).bCopyData = FALSE;
        if ((*pmyUserData).bIsString )
        {
            (*(*pmyUserData).pStringValue) = strValue; 
        }
        else
        {
            (*(*pmyUserData).pIntValue)  = atoi(strValue.c_str());
        }
    }
}

static void load_file(std::string& s, std::istream& is)
{
   s.erase();
   //
   // attempt to grow string buffer to match file size, this doesn t always work..
   s.reserve(is.rdbuf()->in_avail());
   char c;
   while(is.get(c))
   {
      // use logarithmic growth stategy, in case
      // in_avail (above) returned zero:
      if(s.capacity() == s.size())
         s.reserve(s.capacity() * 3);
      s.append(1, c);
   }
}


//! Read the object g_Options from the xml file
void SpacecSettings::GetProfile(const char* lpszFileName)
{
    std::ifstream inp_settings;
    inp_settings.open( lpszFileName );
    g_Options.SetIsUsingXmlFile(FALSE);
    if (inp_settings)
    {
        XML_Parser parser = XML_ParserCreate(NULL);
        XML_SetElementHandler(parser, startElement, endElement);
        XML_SetCharacterDataHandler(parser, charhndl);

        XML_MYUSERDATA myUserData;
        myUserData.bCopyData = FALSE;
        XML_SetUserData(parser, &myUserData);

        STRING strInpFile;
        load_file(strInpFile, inp_settings);

        if (XML_Parse(parser, strInpFile.c_str(), strInpFile.length(), TRUE) == XML_STATUS_ERROR) 
        {
            fprintf(stderr,
              "%s at line %d\n",
              XML_ErrorString(XML_GetErrorCode(parser)),
              XML_GetCurrentLineNumber(parser));

            return;
        }
        XML_ParserFree(parser);
        g_Options.SetIsUsingXmlFile(TRUE);
    }

    inp_settings.close();
}



