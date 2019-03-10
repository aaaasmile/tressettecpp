//cTipoDiMazzo.h

#ifndef __CTIPODIMAZZO__H_
#define __CTIPODIMAZZO__H_

#include <string>
#include "Languages.h"


//! class cTipoDiMazzo 
/* Collect all info about deck
*/
class cTipoDiMazzo
{
public:
	enum eTypeMazzo
	{
		PIACENTINA = 0,
		BERGAMO,
		BOLOGNA,
		GENOVA,
		MILANO,
		NAPOLI,
		PIEMONTE,
		ROMAGNA,
		SARDEGNA,
		SICILIA,
		TOSCANA,
		TRENTO,
		TREVISO,
		TRIESTE,
	};
public:
	cTipoDiMazzo(){}

public:
	void          SetType(eTypeMazzo eType);
	std::string   GetResFileName() { return m_strResFileName; }
	std::string   GetMazzoName() { return m_strMazzoName; }
	std::string   GetSymbolFileName() { return m_strSymbolName; }
	eTypeMazzo    GetType() { return m_eType; }
	void          Clone(cTipoDiMazzo &Val);
	void          SetTypeIndex(int iVal);
	int           GetTypeIndex() { return (int)m_eType; }

private:
	//! id mazzo
	eTypeMazzo   m_eType;
	//! name
	std::string  m_strMazzoName;
	//! resource file name
	std::string  m_strResFileName;
	//! symbol file name
	std::string  m_strSymbolName;
};



#endif