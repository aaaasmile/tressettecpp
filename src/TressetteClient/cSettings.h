// cSettings.h
// Settings definition. Settings uses a persintence and a global access method.
// Automatic class header file generated with ruby template settings_expat_h.rtemp
// Please don't change me manually, but use code generator
// Created at Sat Sep 02 21:45:38 +0200 2017


#ifndef   __CUSTOMSETTINGS_INI_H_
#define   __CUSTOMSETTINGS_INI_H_  

#include <string>

namespace SpacecSettings
{
  typedef struct stUserData
  {
    STRING* pStringValue;
    int*    pIntValue;
    BOOL    bIsString;
    BOOL    bCopyData;
  }XML_MYUSERDATA;

  class cSettings
  {
    private:
      BOOL        m_isUsingXmlFile;
    public:
      cSettings();
      BOOL IsUsingXmlFile(){return m_isUsingXmlFile;}
      void   SetIsUsingXmlFile(BOOL val){m_isUsingXmlFile = val;}
      
      class SubAll
      {
        public:
            SubAll();
            
            //!The name of the player
            STRING strPlayerName;
              
            //!Delay animation timer
            int iDelayTimer;
              
            //!Automatic termination hand
            int bAutoterminate;
              
            //!CPU level engine
            int iLevel;
              
            //!Kind of deck
            int iTipoMazzo;
              
            //!Language ID
            int iLanguageID;
              
            //!Music enabled
            int bMusicOn;
              
            //!Music volume
            int iMusicVolume;
              
            //!Debug level
            int iDebugLevel;
              
            //!Flag for using python as init script
            int bUsePythonAsInit;
              
            //!Flag for using python notification
            int bUsePythonNotification;
              
            //!Flag for using python console
            int bUsePythonConsole;
              
            //!python init script name
            STRING strPythonInitScriptName;
              
            //!Verbose level
            int iVerbose;
              
            //!Player calls echo
            int bMyCallEcho;
              
            //!Enable sound effect
            int bSoundEffect;
              
            //!Enable foto on background
            int bFotoBack;
              
            //!Enable animation on play card
            int bAnimatePlayCard;
              
            //!Animation speed level (0 slow, 5 fast)
            int iAniSpeedLevel;
              
            //!Pause game after mano end
            int bBlockOnManoEnd;
              
            //!Make signals with right mouse button
            int bSignalWithRMouse;
              
      };
    public:
      SubAll All;
      
      class SubNetwork
      {
        public:
            SubNetwork();
            
            //!Server name
            STRING strServerName;
              
            //!Peer name
            STRING strPeerName;
              
            //!Port server value
            int iPortServer;
              
            //!Port client value
            int iPortClient;
              
            //!Login name
            STRING strLogin;
              
            //!login password
            STRING strPassw;
              
      };
    public:
      SubNetwork Net;
      
      class SubMatch
      {
        public:
            SubMatch();
            
            //!Localization of the game
            int iLocalGameType;
              
            //!Flag for using good game declaration
            int bUseGoodGameDecla;
              
            //!Points target to terminate a  match
            int iScoreGoal;
              
            //!Player name index 2
            STRING strPlayerName_2;
              
            //!Player name index 3
            STRING strPlayerName_3;
              
            //!Player name index 4
            STRING strPlayerName_4;
              
            //!Level of player 1
            int iLevel_Pl_1;
              
            //!Level of player 2
            int iLevel_Pl_2;
              
            //!Level of player 3
            int iLevel_Pl_3;
              
            //!Level of player 4
            int iLevel_Pl_4;
              
            //!Algorithm plugin name player 1
            STRING strAlgPlugin_Pl_1;
              
            //!Algorithm plugin name player 2
            STRING strAlgPlugin_Pl_2;
              
            //!Algorithm plugin name player 3
            STRING strAlgPlugin_Pl_3;
              
            //!Algorithm plugin name player 4
            STRING strAlgPlugin_Pl_4;
              
            //!Dll plugin name player 1
            STRING strPluginDll_Pl_1;
              
            //!Dll plugin name player 2
            STRING strPluginDll_Pl_2;
              
            //!Dll plugin name player 3
            STRING strPluginDll_Pl_3;
              
            //!Dll plugin name player 4
            STRING strPluginDll_Pl_4;
              
      };
    public:
      SubMatch Match;
      
    
  };

  //! write settings in the xml file
  void    WriteProfile(const char* lpsFileName);
  //! retrieves setting from xml file
  void    GetProfile(const char* lpsFileName);
    
};//end namespace

extern SpacecSettings::cSettings g_Options;

#endif
