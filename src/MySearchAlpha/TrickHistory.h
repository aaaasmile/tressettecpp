
// TrickHistory.h: interface for the TrickHistory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRICKHISTORY_H__E5BFD3AE_A7FE_4D9D_B146_3F2C42D1504C__INCLUDED_)
#define AFX_TRICKHISTORY_H__E5BFD3AE_A7FE_4D9D_B146_3F2C42D1504C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include "InfoComm.h"
#include "ConstSearchAlpha.h"
#include "cCardItem.h"
#include "win_type_global.h"

//! class  TrickHistory
class TrickHistoryItem
{
public:
    TrickHistoryItem();
    virtual ~TrickHistoryItem();
    TrickHistoryItem(BYTE byPlS, BYTE byTn) {
        m_Player_Start = byPlS;
        m_Player_Taken = 0xff;
        m_TrickNum = byTn;
        m_PointsTrick = 0;
    }

    //! card list trick
    CARDLIST    m_Trick;
    //! player that start the trick
    BYTE        m_Player_Start;
    //! player thar take the trick
    BYTE        m_Player_Taken;
    //! trick number
    BYTE        m_TrickNum;
    //! trick points
    BYTE        m_PointsTrick;
};


typedef std::vector<TrickHistoryItem>TRICKHISTORY;




#endif // !defined(AFX_TRICKHISTORY_H__E5BFD3AE_A7FE_4D9D_B146_3F2C42D1504C__INCLUDED_)


