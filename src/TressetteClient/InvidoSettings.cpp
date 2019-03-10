// cSettings.cpp


#include "StdAfx.h"
#include "InvidoSettings.h"
#include "win_type_global.h"
#include "regkey.h"

using namespace SpaceInvidoSettings;

// global options object
InvidoSettings  g_Options;

static const char* lpszSubAll = "SubAll";
static const char* lpszSubAlliDelayTimer = "SubAlliDelayTimer";
static const char* lpszSubAllbAutoterminate = "SubAllbAutoterminate";
static const char* lpszSubAlliLevel = "SubAlliLevel";
static const char* lpszSubAlliTipoMazzo = "SubAlliTipoMazzo";
static const char* lpszSubAlliLanguageID = "SubAlliLanguageID";
static const char* lpszSubAllbMusicOn = "SubAllbMusicOn";
static const char* lpszSubAlliMusicVolume = "SubAlliMusicVolume";
static const char* lpszSubAlliDebugLevel = "SubAlliDebugLevel";
static const char* lpszSubAllbUsePython = "SubAllbUsePython";
static const char* lpszSubAlliVerbose = "SubAlliVerbose";
static const char* lpszSubAllbMyCallEcho = "SubAllbMyCallEcho";
static const char* lpszSubAllbSoundEffect = "SubAllbSoundEffect";
static const char* lpszSubAllbFotoBack = "SubAllbFotoBack";
static const char* lpszSubAllbUseSplashJpg = "SubAllbUseSplashJpg";
static const char* lpszSubAlliAniSpeedLevel = "SubAlliAniSpeedLevel";
static const char* lpszSubAllstrPlayerName = "SubAllstrPlayerName";

//! constructor
InvidoSettings::InvidoSettings()
{

}

InvidoSettings::SubAll::SubAll()
{
	iDelayTimer = 300;
	bAutoterminate = 1;
	iLevel = 1;
	iTipoMazzo = 0;
	iLanguageID = 0;
	bMusicOn = 0;
	iMusicVolume = 80;
	iDebugLevel = 0;
	bUsePython = 0;
	iVerbose = 3;
	bMyCallEcho = 1;
	bSoundEffect = 1;
	bFotoBack = 1;
	bUseSplashJpg = 1;
	iAniSpeedLevel = 2;
	strPlayerName = "Remigiu";
}

void SpaceInvidoSettings::WriteProfile(const char* strKeyRoot)
{
	RegistryKey RegKey;
	LONG lRes;
	char buff[1024];
	strcpy(buff, strKeyRoot);
	strcat(buff, "\\");
	strcat(buff, lpszSubAll);
	lRes = RegKey.Open(HKEY_CURRENT_USER, buff);
	if (lRes)
	{
		lRes = RegKey.Create(HKEY_CURRENT_USER, buff);
	}
	if (!lRes)
	{
		RegKey.setRegDWordValue(g_Options.All.iDelayTimer, lpszSubAlliDelayTimer);
		RegKey.setRegDWordValue(g_Options.All.bAutoterminate, lpszSubAllbAutoterminate);
		RegKey.setRegDWordValue(g_Options.All.iLevel, lpszSubAlliLevel);
		RegKey.setRegDWordValue(g_Options.All.iTipoMazzo, lpszSubAlliTipoMazzo);
		RegKey.setRegDWordValue(g_Options.All.iLanguageID, lpszSubAlliLanguageID);
		RegKey.setRegDWordValue(g_Options.All.bMusicOn, lpszSubAllbMusicOn);
		RegKey.setRegDWordValue(g_Options.All.iMusicVolume, lpszSubAlliMusicVolume);
		RegKey.setRegDWordValue(g_Options.All.iDebugLevel, lpszSubAlliDebugLevel);
		RegKey.setRegDWordValue(g_Options.All.bUsePython, lpszSubAllbUsePython);
		RegKey.setRegDWordValue(g_Options.All.iVerbose, lpszSubAlliVerbose);
		RegKey.setRegDWordValue(g_Options.All.bMyCallEcho, lpszSubAllbMyCallEcho);
		RegKey.setRegDWordValue(g_Options.All.bSoundEffect, lpszSubAllbSoundEffect);
		RegKey.setRegDWordValue(g_Options.All.bFotoBack, lpszSubAllbFotoBack);
		RegKey.setRegDWordValue(g_Options.All.bUseSplashJpg, lpszSubAllbUseSplashJpg);
		RegKey.setRegDWordValue(g_Options.All.iAniSpeedLevel, lpszSubAlliAniSpeedLevel);
		RegKey.setRegStringValue(g_Options.All.strPlayerName.c_str(), lpszSubAllstrPlayerName);
		RegKey.Close();
	}
}


void SpaceInvidoSettings::GetProfile(const char* strKeyRoot)
{
	RegistryKey RegKey;
	LONG lRes;
	char buff[1024];

	lRes = RegKey.Open(HKEY_CURRENT_USER, strKeyRoot);
	if (!lRes)
	{
		strcpy(buff, strKeyRoot);
		strcat(buff, "\\");
		strcat(buff, lpszSubAll);
		RegKey.Close();
		lRes = RegKey.Open(HKEY_CURRENT_USER, buff);
		if (!lRes)
		{
			g_Options.All.iDelayTimer = RegKey.getRegDWordValue(300, lpszSubAlliDelayTimer);
			g_Options.All.bAutoterminate = RegKey.getRegDWordValue(1, lpszSubAllbAutoterminate);
			g_Options.All.iLevel = RegKey.getRegDWordValue(1, lpszSubAlliLevel);
			g_Options.All.iTipoMazzo = RegKey.getRegDWordValue(0, lpszSubAlliTipoMazzo);
			g_Options.All.iLanguageID = RegKey.getRegDWordValue(0, lpszSubAlliLanguageID);
			g_Options.All.bMusicOn = RegKey.getRegDWordValue(0, lpszSubAllbMusicOn);
			g_Options.All.iMusicVolume = RegKey.getRegDWordValue(80, lpszSubAlliMusicVolume);
			g_Options.All.iDebugLevel = RegKey.getRegDWordValue(0, lpszSubAlliDebugLevel);
			g_Options.All.bUsePython = RegKey.getRegDWordValue(0, lpszSubAllbUsePython);
			g_Options.All.iVerbose = RegKey.getRegDWordValue(3, lpszSubAlliVerbose);
			g_Options.All.bMyCallEcho = RegKey.getRegDWordValue(1, lpszSubAllbMyCallEcho);
			g_Options.All.bSoundEffect = RegKey.getRegDWordValue(1, lpszSubAllbSoundEffect);
			g_Options.All.bFotoBack = RegKey.getRegDWordValue(1, lpszSubAllbFotoBack);
			g_Options.All.bUseSplashJpg = RegKey.getRegDWordValue(1, lpszSubAllbUseSplashJpg);
			g_Options.All.iAniSpeedLevel = RegKey.getRegDWordValue(2, lpszSubAlliAniSpeedLevel);
			g_Options.All.strPlayerName = RegKey.getRegStringValue("Remigiu", lpszSubAllstrPlayerName);
		}
		else
		{
			RegKey.Create(HKEY_CURRENT_USER, buff);
		}
	}
	else
	{
		RegKey.Create(HKEY_CURRENT_USER, strKeyRoot);
	}
	RegKey.Close();
}
