

// cHightScoreMgr.h: interface for the cHightScoreMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHIGHTSCOREMGR_H__6D4D1807_CD5D_4D2F_AB63_A5A94EE9CD50__INCLUDED_)
#define AFX_CHIGHTSCOREMGR_H__6D4D1807_CD5D_4D2F_AB63_A5A94EE9CD50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class cHightScoreMgr  
{
public:
	cHightScoreMgr();
	virtual ~cHightScoreMgr();

     //! load hightscore
    void    Load();
    //! save hight score
    void    Save();

public:
    std::string       HS_Names[10];
    unsigned int HS_Scores[10];


};

#endif // !defined(AFX_CHIGHTSCOREMGR_H__6D4D1807_CD5D_4D2F_AB63_A5A94EE9CD50__INCLUDED_)
