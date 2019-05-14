
//cTipoDiMazzo.cpp

#include "StdAfx.h"

#include "cTipoDiMazzo.h"
#include "lang_gen.h"
#include <assert.h>

////////////////////////////////////////
//       GetMazzoNameOnType
/*!
// \param eTypeMazzo eType :
*/
std::string  cTipoDiMazzo::GetMazzoNameOnType(eTypeMazzo eType)
{
    std::string strMazzo = getMazzoName(eType);
    return strMazzo;
}

////////////////////////////////////////
//       getMazzoName
/*!
// \param eTypeMazzo eType :
*/
std::string cTipoDiMazzo::getMazzoName(eTypeMazzo eType)
{
    std::string strName;
    cLanguages* pLan = cLanguages::Instance();

    switch (eType)
    {
    case PIACENTINA:
        strName = pLan->GetCStringId(cLanguages::ID_PIACENTINA);
        break;
    case BERGAMO:
        strName = pLan->GetCStringId(cLanguages::ID_BERGAMO);
        break;
    case BOLOGNA:
        strName = pLan->GetCStringId(cLanguages::ID_BOLOGNA);
        break;
    case GENOVA:
        strName = pLan->GetCStringId(cLanguages::ID_GENOVA);
        break;
    case MILANO:
        strName = pLan->GetCStringId(cLanguages::ID_MILANO);
        break;
    case NAPOLI:
        strName = pLan->GetCStringId(cLanguages::ID_NAPOLI);
        break;
    case PIEMONTE:
        strName = pLan->GetCStringId(cLanguages::ID_PIEMONTE);
        break;
    case ROMAGNA:
        strName = pLan->GetCStringId(cLanguages::ID_ROMAGNA);
        break;
    case SARDEGNA:
        strName = pLan->GetCStringId(cLanguages::ID_SARDEGNA);
        break;
    case SICILIA:
        strName = pLan->GetCStringId(cLanguages::ID_SICILIA);
        break;
    case TOSCANA:
        strName = pLan->GetCStringId(cLanguages::ID_TOSCANA);
        break;
    case TRENTO:
        strName = pLan->GetCStringId(cLanguages::ID_TRENTO);
        break;
    case TREVISO:
        strName = pLan->GetCStringId(cLanguages::ID_TREVISO);
        break;
        /*
        case TRIESTE:
        strName = pLan->GetCStringId(cLanguages::ID_TRIESTE ) ;
        break;
        */
    default:
        assert(0);
    }

    return strName;
}

////////////////////////////////////////
//       SetType
/*! Set type of the new deck
*/
void cTipoDiMazzo::SetType(eTypeMazzo eType)
{
    m_eType = eType;
    switch(eType)
    {
    case PIACENTINA:
        m_strMazzoName = "Piacentine";
        m_strResFileName = "mazzo_piac.pac";
        m_strSymbolName = "symb_336.bmp";
        break;
    case BERGAMO:
        m_strMazzoName = "Bergamasche";
        m_strResFileName = "bergamo_cards.pac";
        m_strSymbolName = "symb_320.bmp";
        break;
    case BOLOGNA:
        m_strMazzoName = "Bolognesi";
        m_strResFileName = "bologna_cards.pac";
        m_strSymbolName = "symb_320.bmp";
        break;
    case GENOVA:
        m_strMazzoName = "Genovesi";
        m_strResFileName = "genova_cards.pac";
        m_strSymbolName = "symb_368.bmp";
        break;
    case MILANO:
        m_strMazzoName = "Milanesi";
        m_strResFileName = "milano_cards.pac";
        m_strSymbolName = "symb_320.bmp";
        break;
    case NAPOLI:
        m_strMazzoName = "Napoletane";
        m_strResFileName = "napoli_cards.pac";
        m_strSymbolName = "symb_368.bmp";
        break;
    case PIEMONTE:
        m_strMazzoName = "Piemontesi";
        m_strResFileName = "piemonte_cards.pac";
        m_strSymbolName = "symb_368.bmp";
        break;
    case ROMAGNA:
        m_strMazzoName = "Romagnole";
        m_strResFileName = "romagna_cards.pac";
        m_strSymbolName = "symb_336.bmp";
        break;
    case SARDEGNA:
        m_strMazzoName = "Sarde";
        m_strResFileName = "sardegna_cards.pac";
        m_strSymbolName = "symb_368.bmp";
        break;
    case SICILIA:
        m_strMazzoName = "Siciliane";
        m_strResFileName = "sicilia_cards.pac";
        m_strSymbolName = "symb_368.bmp";
        break;
    case TOSCANA:
        m_strMazzoName = "Toscane";
        m_strResFileName = "toscana_cards.pac";
        m_strSymbolName = "symb_368.bmp";
        break;
    case TRENTO:
        m_strMazzoName = "Trentine";
        m_strResFileName = "trento_cards.pac";
        m_strSymbolName = "symb_336.bmp";
        break;
    case TREVISO:
        m_strMazzoName = "Trevigiane";
        m_strResFileName = "carte_trevisane.pac";
        m_strSymbolName = "symb_320.bmp";
        break;
    default:
        assert(0);

    }
}


////////////////////////////////////////
//       Clone
/*! 
// \param cTipoDiMazzo &Val : 
*/
void cTipoDiMazzo::Clone(cTipoDiMazzo &Val)
{
    m_eType = Val.GetType();
    m_strMazzoName = Val.GetMazzoName() ;
    m_strResFileName = Val.GetResFileName() ;
    m_strSymbolName = Val.GetSymbolFileName() ;
}


////////////////////////////////////////
//       SetTypeIndex
/*! 
// \param int iVal : 
*/
void cTipoDiMazzo::SetTypeIndex(int iVal)
{
    switch(iVal)
    {
    case 0:
        SetType(PIACENTINA);
        break;
    case 1:
        SetType(BERGAMO);
        break;
    case 2:
        SetType(BOLOGNA);
        break;
    case 3:
        SetType(GENOVA);
        break;
    case 4:
        SetType(MILANO);
        break;
    case 5:
        SetType(NAPOLI);
        break;
    case 6:
        SetType(PIEMONTE);
        break;
    case 7:
        SetType(ROMAGNA);
        break;
    case 8:
        SetType(SARDEGNA);
        break;
    case 9:
        SetType(SICILIA);
        break;
    case 10:
        SetType(TOSCANA);
        break;
    case 11:
        SetType(TRENTO);
        break;
    case 12:
        SetType(TREVISO);
        break;
    default:
        SetType(PIACENTINA);
        break;
    }
}