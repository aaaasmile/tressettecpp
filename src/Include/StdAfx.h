
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C0F7C4A2_8B0F_4610_85F6_935059CA33AE__INCLUDED_)
#define AFX_STDAFX_H__C0F7C4A2_8B0F_4610_85F6_935059CA33AE__INCLUDED_

#pragma warning(disable:4786)
#pragma warning(disable:4996)
#pragma warning(disable:4251)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <valarray>


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <deque>
//#include <windows.h>
#include <string>
#include <assert.h>
#include <stdio.h>

#define APP_WIN_HEIGHT 700//480
#define APP_WIN_WIDTH 1024//800

#define OPT_WIN_GAME_WIDTH	500
#define OPT_WIN_GAME_HEIGHT 390

#define OPT_WIN_DECK_WIDTH	500
#define OPT_WIN_DECK_HEIGHT 360

#define OPT_WIN_GENERAL_WIDTH	500
#define OPT_WIN_GENERAL_HEIGHT 420

#define DLL_EXPORTIMPORT   __declspec( dllimport )


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C0F7C4A2_8B0F_4610_85F6_935059CA33AE__INCLUDED_)
