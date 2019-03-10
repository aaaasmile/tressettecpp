//CardSpec.h

#ifndef ___CARDSPEC_H_
#define ___CARDSPEC_H_


#include "AlgPlayerInterface.h"
#include "cInvidoCoreEnv.h"

//! class CardSpec
class  CardSpec
{
public:
    CardSpec();
    virtual ~CardSpec(){};

    //! set the index of the card
    void    SetCardIndex(int itmpIndex);
    //! provides index
    int     GetCardIndex(){return m_CardInfo.byIndex;}
    //! provides suit
    eSUIT   GetSuit(){return m_CardInfo.eSuit;}
    //! provides card name
    LPCSTR  GetName(){return m_CardInfo.CardName;}
    //! assignement operator
    void operator = (const CardSpec &r); 
    //! compair operator
    bool operator == (const CardSpec &r){return m_CardInfo.byIndex == r.m_CardInfo.byIndex;}
    bool operator != (const CardSpec &r){return m_CardInfo.byIndex != r.m_CardInfo.byIndex;}
    //! reset
    void    Reset();
    //! set symbol
    void    SetSymbol(int iVal){m_CardInfo.byIndex = iVal;}
    //! get symbol information
    int     GetSymbol(){return m_CardInfo.byIndex;}
    //! get card info pointer
    CARDINFO*  GetCardInfo(){return &m_CardInfo;}
    //! set card info
    void       SetCardInfo(const CARDINFO& Card);
    //! provides information structure
    void       FillInfo(CARDINFO* pCardInfo);
    int        GetPoints();

private:
    CARDINFO   m_CardInfo;
};


typedef std::vector<CardSpec> VCT_CARDSPEC;
typedef std::vector<char>                       VCT_SINGLECARD;
typedef std::vector<char>::iterator             IT_SINGLE_CARD;
typedef std::vector<VCT_SINGLECARD>::iterator   IT_SINGLE_HAND;



#endif