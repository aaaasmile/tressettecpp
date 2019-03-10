
// Lang_Gen.h 
// used to handle languages resource 
// Automatic generated header file by xml->xslt = header

#ifndef   __LANGUAG_GEN_HEAD_H_
#define   __LANGUAG_GEN_HEAD_H_  
 



#include <string>


//! class cLanguages
class cLanguages
{
protected:
	
    cLanguages();
   
public:
	static  cLanguages* Instance();
	
private:
    static cLanguages* pinstance;
   
public:
    
    enum eLangId
    {
    
    		LANG_ITA=0,
        		LANG_DIAL_MN,
        		LANG_ENG,
        
    	TOT_LANG // it mus be  always on the last place
    };
    enum eStringID
    {
        	ID_START=0,
        		ID_LANGUAGESEL,
        		ID_HISCORE,
        		ID_VIDEOSET,
        		ID_MAINMENU,
        		ID_OK,
        		ID_CANCEL,
        		ID_NAME,
        		ID_EXIT,
        		ID_MUSIC,
        		ID_SOUNDEFFECT,
        		ID_CHOOSELEVEL,
        		ID_MANAGEPLAYER,
        		ID_BACKMAINMENU,
        		ID_EASY,
        		ID_HARD,
        		ID_HARDER,
        		ID_BACK,
        		ID_SELECTDISPLAYSETTINGS,
        		ID_GAMENAME,
        		ID_CHOOSELANGUA,
        		ID_LANGUAGE,
        		ID_ENGLISH,
        		ID_DIALETMN,
        		ID_ITALIANO,
        		ID_ANONIM,
        		ID_PUSHBUTTON,
        		ID_CMD_UNKNOWN,
        		ID_CMD_HELP,
        		ID_CMD_CHATWELCOME,
        		ID_CMD_CHATLIST,
        		ID_SOLITARIO,
        		ID_MAZZONAME,
        		ID_C_NOTHING,
        		ID_C_VOLO,
        		ID_C_PIOMBO,
        		ID_C_BUSSO_LAMIGLIORE,
        		ID_C_BUSSO,
        		ID_C_LAMIGLIORE,
        		ID_C_STRISCIO_NEHOTANTE,
        		ID_C_STRISCIO_COMELISCIO,
        		ID_C_PUNTO_ANCORAUNA,
        		ID_C_VIA_DAQUESTOGIOCO,
        		ID_C_HO_ILTRE,
        		ID_C_HO_ILDUE,
        		ID_C_RIBUSSO,
        		ID_C_VOGLIOIL25,
        		ID_C_ALTRECARTE,
        		ID_C_HOIL25,
        		ID_C_HO_ASSO,
        		ID_C_LISCIO_NEHOANCORAPIUBASSE,
        		ID_C_PIOMBOAUNPALO,
        		ID_MEN_OPTIONS,
        		ID_OPT_GENERAL,
        		ID_OPT_CONTRL_GENERAL,
        		ID_OPT_CONTRL_GAME,
        		ID_OPT_CONTRL_DECK,
        		ID_OPT_GAME,
        		ID_CREDITS,
        		ID_WELCOMETITLEBAR,
        		ID_STA_PTCURRENT,
        		ID_CHOOSEMAZZO,
        		ID_CHOOSELOCALGAME,
        		ID_LOCAL_BREDACISONI,
        		ID_LOCAL_NEUTRAL,
        		ID_LOCAL_CHITARELLA,
        		ID_LOCAL_ROMANA,
        		ID_LOCAL_CLASSIC,
        		ID_CHOOSENAME,
        		ID_SHOWALGCONTROL,
        		ID_SHOWCARDANIMATION,
        		ID_ENABLEDECLARGG,
        		ID_MATCHENDQUESTION,
        		ID_YES,
        		ID_NO,
        		ID_PIACENTINA,
        		ID_BERGAMO,
        		ID_BOLOGNA,
        		ID_GENOVA,
        		ID_MILANO,
        		ID_NAPOLI,
        		ID_PIEMONTE,
        		ID_ROMAGNA,
        		ID_SARDEGNA,
        		ID_TOSCANA,
        		ID_TRENTO,
        		ID_TREVISO,
        		ID_TRIESTE,
        		ID_SICILIA,
        		ID_CP_RISP1,
        		ID_CP_PLAYER,
        		ID_CP_DICE,
        		ID_CP_MANOPATA,
        		ID_CP_MANOVINTA,
        		ID_CP_GIOCATAPATA,
        		ID_CP_GIOCATAMONTE,
        		ID_CP_GIOCATAVINTA,
        		ID_CP_PUNTI,
        		ID_CP_PUNTITOT,
        		ID_CP_PUNTIGIOCATA,
        		ID_SCOREGOAL,
        		ID_CP_PUNTIACCUSE,
        		ID_PUNTIMATCH_GOAL,
        		ID_CP_PARTITAFIN,
        		ID_CP_NOWPOINTS,
        		ID_CP_BUIADA,
        		ID_CP_VINCE,
        		ID_CP_PERDE,
        		ID_MN_HELP,
        		ID_A_ACCUSA,
        		ID_A_NAPOLA,
        		ID_A_SBAGLIA,
        		ID_A_SENZA,
        		ID_A_TRETRE,
        		ID_A_TREDUE,
        		ID_A_TREASSI,
        		ID_A_4ASSI,
        		ID_A_4DUE,
        		ID_A_4TRE,
        		ID_A_BASTONI,
        		ID_A_COPPE,
        		ID_A_DENARI,
        		ID_A_SPADE,
        		ID_SPEED_SLOW,
        		ID_SPEED_FAST,
        		ID_BLOCKONMANOEND,
        		ID_SIGNARMOUSEBT,
        
        TOT_STRINGS // it mus be always on the last place
    };
    
public:
    void  SetLang(eLangId eVal){m_eLangid = eVal;}
    eLangId  GetLang(){return m_eLangid ;}
    std::string  GetStringId(eStringID eId);
    char*        GetCStringId(eStringID eId);

private:
    eLangId      m_eLangid;
    std::string  m_matStringsLang[TOT_LANG][TOT_STRINGS];

};

#endif

