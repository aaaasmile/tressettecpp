#include "StdAfx.h"
#include "win_type_global.h"
#include "lang_gen.h"
#include <assert.h>

static std::string sta_strRet ="Err trans.";

 
 cLanguages* cLanguages::pinstance = 0;// initialize pointer
  cLanguages* cLanguages::Instance () 
  {
    if (pinstance == 0)  // is it the first call?
    {  
      pinstance = new cLanguages; // create sole instance
    }
    return pinstance; // address of sole instance
  }

//! constructor
cLanguages::cLanguages()
{
	for (int i = 0; i< TOT_STRINGS; i++)
    {
        for (int j = 0; j < TOT_LANG; j++)
        {
            m_matStringsLang[j][i] = "No Translation!";
        }
    }
    m_eLangid = LANG_ITA;

	m_matStringsLang[LANG_ITA][ID_START] = "Inizia";
		
	m_matStringsLang[LANG_ITA][ID_LANGUAGESEL] = "Lingua";
		
	m_matStringsLang[LANG_ITA][ID_HISCORE] = "Hight Score";
		
	m_matStringsLang[LANG_ITA][ID_VIDEOSET] = "Settings Display";
		
	m_matStringsLang[LANG_ITA][ID_MAINMENU] = "Menu principale";
		
	m_matStringsLang[LANG_ITA][ID_OK] = "OK";
		
	m_matStringsLang[LANG_ITA][ID_CANCEL] = "Cancella";
		
	m_matStringsLang[LANG_ITA][ID_NAME] = "Nome";
		
	m_matStringsLang[LANG_ITA][ID_EXIT] = "Esci";
		
	m_matStringsLang[LANG_ITA][ID_MUSIC] = "Musica";
		
	m_matStringsLang[LANG_ITA][ID_SOUNDEFFECT] = "Effetti sonori";
		
	m_matStringsLang[LANG_ITA][ID_CHOOSELEVEL] = "Seleziona il gioco";
		
	m_matStringsLang[LANG_ITA][ID_MANAGEPLAYER] = "Controllo giocatore";
		
	m_matStringsLang[LANG_ITA][ID_BACKMAINMENU] = "Vai al menu principale";
		
	m_matStringsLang[LANG_ITA][ID_EASY] = "Facile";
		
	m_matStringsLang[LANG_ITA][ID_HARD] = "Difficile";
		
	m_matStringsLang[LANG_ITA][ID_HARDER] = "Difficilissimo";
		
	m_matStringsLang[LANG_ITA][ID_BACK] = "Torna indietro";
		
	m_matStringsLang[LANG_ITA][ID_SELECTDISPLAYSETTINGS] = "Seleziona il display";
		
	m_matStringsLang[LANG_ITA][ID_GAMENAME] = "Tressette";
		
	m_matStringsLang[LANG_ITA][ID_CHOOSELANGUA] = "Seleziona la lingua";
		
	m_matStringsLang[LANG_ITA][ID_LANGUAGE] = "Lingua";
		
	m_matStringsLang[LANG_ITA][ID_ENGLISH] = "Inglese";
		
	m_matStringsLang[LANG_ITA][ID_DIALETMN] = "Dialetto Bredese";
		
	m_matStringsLang[LANG_ITA][ID_ITALIANO] = "Italiano";
		
	m_matStringsLang[LANG_ITA][ID_ANONIM] = "Anonimo";
		
	m_matStringsLang[LANG_ITA][ID_PUSHBUTTON] = "Premi un tasto";
		
	m_matStringsLang[LANG_ITA][ID_CMD_UNKNOWN] = "Comando non riconosciuto";
		
	m_matStringsLang[LANG_ITA][ID_CMD_HELP] = "Comandi che puoi usare:";
		
	m_matStringsLang[LANG_ITA][ID_CMD_CHATWELCOME] = "Bene arrivato nella chat";
		
	m_matStringsLang[LANG_ITA][ID_CMD_CHATLIST] = "La lista dei presenti nella chat";
		
	m_matStringsLang[LANG_ITA][ID_SOLITARIO] = "Solitario";
		
	m_matStringsLang[LANG_ITA][ID_MAZZONAME] = "Mazzi di carte";
		
	m_matStringsLang[LANG_ITA][ID_C_NOTHING] = "Nulla";
		
	m_matStringsLang[LANG_ITA][ID_C_VOLO] = "Volo";
		
	m_matStringsLang[LANG_ITA][ID_C_PIOMBO] = "Piombo";
		
	m_matStringsLang[LANG_ITA][ID_C_BUSSO_LAMIGLIORE] = "Busso";
		
	m_matStringsLang[LANG_ITA][ID_C_BUSSO] = "Busso";
		
	m_matStringsLang[LANG_ITA][ID_C_LAMIGLIORE] = "La migliore";
		
	m_matStringsLang[LANG_ITA][ID_C_STRISCIO_NEHOTANTE] = "Striscio lungo";
		
	m_matStringsLang[LANG_ITA][ID_C_STRISCIO_COMELISCIO] = "Striscio";
		
	m_matStringsLang[LANG_ITA][ID_C_PUNTO_ANCORAUNA] = "Punto";
		
	m_matStringsLang[LANG_ITA][ID_C_VIA_DAQUESTOGIOCO] = "Via";
		
	m_matStringsLang[LANG_ITA][ID_C_HO_ILTRE] = "Ho il tre";
		
	m_matStringsLang[LANG_ITA][ID_C_HO_ILDUE] = "Ho il due";
		
	m_matStringsLang[LANG_ITA][ID_C_RIBUSSO] = "Ribusso";
		
	m_matStringsLang[LANG_ITA][ID_C_VOGLIOIL25] = "Voglio il 25";
		
	m_matStringsLang[LANG_ITA][ID_C_ALTRECARTE] = "Altre carte";
		
	m_matStringsLang[LANG_ITA][ID_C_HOIL25] = "Ho il 25";
		
	m_matStringsLang[LANG_ITA][ID_C_HO_ASSO] = "Ho l'Asso";
		
	m_matStringsLang[LANG_ITA][ID_C_LISCIO_NEHOANCORAPIUBASSE] = "Liscio";
		
	m_matStringsLang[LANG_ITA][ID_C_PIOMBOAUNPALO] = "Piombo a un palo";
		
	m_matStringsLang[LANG_ITA][ID_MEN_OPTIONS] = "Opzioni";
		
	m_matStringsLang[LANG_ITA][ID_OPT_GENERAL] = "Generali";
		
	m_matStringsLang[LANG_ITA][ID_OPT_CONTRL_GENERAL] = "Opzioni Generali";
		
	m_matStringsLang[LANG_ITA][ID_OPT_CONTRL_GAME] = "Opzioni Gioco";
		
	m_matStringsLang[LANG_ITA][ID_OPT_CONTRL_DECK] = "Opzioni mazzi di carte";
		
	m_matStringsLang[LANG_ITA][ID_OPT_GAME] = "Gioco";
		
	m_matStringsLang[LANG_ITA][ID_CREDITS] = "Credits";
		
	m_matStringsLang[LANG_ITA][ID_WELCOMETITLEBAR] = "Benvenuti nel mondo del Tressette!";
		
	m_matStringsLang[LANG_ITA][ID_STA_PTCURRENT] = "Punteggio attuale";
		
	m_matStringsLang[LANG_ITA][ID_CHOOSEMAZZO] = "Scegli il mazzo di carte";
		
	m_matStringsLang[LANG_ITA][ID_CHOOSELOCALGAME] = "Scegli la localizzazione";
		
	m_matStringsLang[LANG_ITA][ID_LOCAL_BREDACISONI] = "Breda Cisoni";
		
	m_matStringsLang[LANG_ITA][ID_LOCAL_NEUTRAL] = "Neutrale";
		
	m_matStringsLang[LANG_ITA][ID_LOCAL_CHITARELLA] = "Chitarrella";
		
	m_matStringsLang[LANG_ITA][ID_LOCAL_ROMANA] = "Romana";
		
	m_matStringsLang[LANG_ITA][ID_LOCAL_CLASSIC] = "Classico";
		
	m_matStringsLang[LANG_ITA][ID_CHOOSENAME] = "Immetti il tuo nome";
		
	m_matStringsLang[LANG_ITA][ID_SHOWALGCONTROL] = "Mostra algoritmi";
		
	m_matStringsLang[LANG_ITA][ID_SHOWCARDANIMATION] = "Mostra animazioni carte";
		
	m_matStringsLang[LANG_ITA][ID_ENABLEDECLARGG] = "Accusi buoni giochi";
		
	m_matStringsLang[LANG_ITA][ID_MATCHENDQUESTION] = "Partita in corso, vuoi  uscire?";
		
	m_matStringsLang[LANG_ITA][ID_YES] = "Si";
		
	m_matStringsLang[LANG_ITA][ID_NO] = "No";
		
	m_matStringsLang[LANG_ITA][ID_PIACENTINA] = "Piacentine";
		
	m_matStringsLang[LANG_ITA][ID_BERGAMO] = "Bergamasche";
		
	m_matStringsLang[LANG_ITA][ID_BOLOGNA] = "Bolognesi";
		
	m_matStringsLang[LANG_ITA][ID_GENOVA] = "Genovesi";
		
	m_matStringsLang[LANG_ITA][ID_MILANO] = "Milanesi";
		
	m_matStringsLang[LANG_ITA][ID_NAPOLI] = "Napoletane";
		
	m_matStringsLang[LANG_ITA][ID_PIEMONTE] = "Piemontesi";
		
	m_matStringsLang[LANG_ITA][ID_ROMAGNA] = "Romagnole";
		
	m_matStringsLang[LANG_ITA][ID_SARDEGNA] = "Sarde";
		
	m_matStringsLang[LANG_ITA][ID_TOSCANA] = "Toscane";
		
	m_matStringsLang[LANG_ITA][ID_TRENTO] = "Trentine";
		
	m_matStringsLang[LANG_ITA][ID_TREVISO] = "Trevigiane";
		
	m_matStringsLang[LANG_ITA][ID_TRIESTE] = "Triestine";
		
	m_matStringsLang[LANG_ITA][ID_SICILIA] = "Siciliane";
		
	m_matStringsLang[LANG_ITA][ID_CP_RISP1] = "Ora devi rispondere...";
		
	m_matStringsLang[LANG_ITA][ID_CP_PLAYER] = "Giocatore";
		
	m_matStringsLang[LANG_ITA][ID_CP_DICE] = "dice";
		
	m_matStringsLang[LANG_ITA][ID_CP_MANOPATA] = "Mano patada, tocca a";
		
	m_matStringsLang[LANG_ITA][ID_CP_MANOVINTA] = "Mano vinta da";
		
	m_matStringsLang[LANG_ITA][ID_CP_GIOCATAPATA] = "Giocata patta";
		
	m_matStringsLang[LANG_ITA][ID_CP_GIOCATAMONTE] = "Giocata a monte";
		
	m_matStringsLang[LANG_ITA][ID_CP_GIOCATAVINTA] = "Giocata vinta da";
		
	m_matStringsLang[LANG_ITA][ID_CP_PUNTI] = "punti";
		
	m_matStringsLang[LANG_ITA][ID_CP_PUNTITOT] = "Punteggio totale:";
		
	m_matStringsLang[LANG_ITA][ID_CP_PUNTIGIOCATA] = "Punti in questa smazzata:";
		
	m_matStringsLang[LANG_ITA][ID_SCOREGOAL] = "Punteggio vittoria";
		
	m_matStringsLang[LANG_ITA][ID_CP_PUNTIACCUSE] = "Punti in accuse:";
		
	m_matStringsLang[LANG_ITA][ID_PUNTIMATCH_GOAL] = "La partita finisce ai punti:";
		
	m_matStringsLang[LANG_ITA][ID_CP_PARTITAFIN] = "PARTITA finita";
		
	m_matStringsLang[LANG_ITA][ID_CP_NOWPOINTS] = "Punteggio della giocata ora è";
		
	m_matStringsLang[LANG_ITA][ID_CP_BUIADA] = "Quello che hai chiamato non è corretto";
		
	m_matStringsLang[LANG_ITA][ID_CP_VINCE] = "vince";
		
	m_matStringsLang[LANG_ITA][ID_CP_PERDE] = "perde";
		
	m_matStringsLang[LANG_ITA][ID_MN_HELP] = "Guida";
		
	m_matStringsLang[LANG_ITA][ID_A_ACCUSA] = "ha accusato";
		
	m_matStringsLang[LANG_ITA][ID_A_NAPOLA] = "Napoletana a";
		
	m_matStringsLang[LANG_ITA][ID_A_SBAGLIA] = "sbaglia";
		
	m_matStringsLang[LANG_ITA][ID_A_SENZA] = "senza";
		
	m_matStringsLang[LANG_ITA][ID_A_TRETRE] = "tre 3 ";
		
	m_matStringsLang[LANG_ITA][ID_A_TREDUE] = "tre due ";
		
	m_matStringsLang[LANG_ITA][ID_A_TREASSI] = "tre assi ";
		
	m_matStringsLang[LANG_ITA][ID_A_4ASSI] = "quattro assi";
		
	m_matStringsLang[LANG_ITA][ID_A_4DUE] = "quattro due";
		
	m_matStringsLang[LANG_ITA][ID_A_4TRE] = "quattro tre";
		
	m_matStringsLang[LANG_ITA][ID_A_BASTONI] = "Bastoni";
		
	m_matStringsLang[LANG_ITA][ID_A_COPPE] = "Coppe";
		
	m_matStringsLang[LANG_ITA][ID_A_DENARI] = "Denari";
		
	m_matStringsLang[LANG_ITA][ID_A_SPADE] = "Spade";
		
	m_matStringsLang[LANG_ITA][ID_SPEED_SLOW] = "lenta";
		
	m_matStringsLang[LANG_ITA][ID_SPEED_FAST] = "veloce";
		
	m_matStringsLang[LANG_ITA][ID_BLOCKONMANOEND] = "Pausa al termine della mano";
		
	m_matStringsLang[LANG_ITA][ID_SIGNARMOUSEBT] = "Segnali col tasto destro mouse";
		
	m_matStringsLang[LANG_DIAL_MN][ID_START] = "Cumincia";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LANGUAGESEL] = "Lengui furèsti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_HISCORE] = "";
		
	m_matStringsLang[LANG_DIAL_MN][ID_VIDEOSET] = "Al schermo";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MAINMENU] = "Menu principal";
		
	m_matStringsLang[LANG_DIAL_MN][ID_OK] = "Sè";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CANCEL] = "Scàsa";
		
	m_matStringsLang[LANG_DIAL_MN][ID_NAME] = "Nom";
		
	m_matStringsLang[LANG_DIAL_MN][ID_EXIT] = "Fnomla che";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MUSIC] = "La musica";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SOUNDEFFECT] = "I rumur";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSELEVEL] = "Selesiuna al gioc";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MANAGEPLAYER] = "I cumpurtament di sugadur";
		
	m_matStringsLang[LANG_DIAL_MN][ID_BACKMAINMENU] = "Va al menu principal";
		
	m_matStringsLang[LANG_DIAL_MN][ID_EASY] = "Facil";
		
	m_matStringsLang[LANG_DIAL_MN][ID_HARD] = "Dificil";
		
	m_matStringsLang[LANG_DIAL_MN][ID_HARDER] = "Dificilisim";
		
	m_matStringsLang[LANG_DIAL_MN][ID_BACK] = "Turna indrè";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SELECTDISPLAYSETTINGS] = "Selesiuna al schermo";
		
	m_matStringsLang[LANG_DIAL_MN][ID_GAMENAME] = "Triset";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSELANGUA] = "Selesiuna la lengua";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LANGUAGE] = "Lengui furesti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_ENGLISH] = "Ingles";
		
	m_matStringsLang[LANG_DIAL_MN][ID_DIALETMN] = "Dialet";
		
	m_matStringsLang[LANG_DIAL_MN][ID_ITALIANO] = "Italian";
		
	m_matStringsLang[LANG_DIAL_MN][ID_ANONIM] = "Anonim";
		
	m_matStringsLang[LANG_DIAL_MN][ID_PUSHBUTTON] = "Schesa an buton";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_UNKNOWN] = "Cumand mia cunusi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_HELP] = "I cumand cat po drua:";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_CHATWELCOME] = "Ben arriva indla chat";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_CHATLIST] = "Chi ghè in dla chat";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SOLITARIO] = "Sulitari";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MAZZONAME] = "Mas ad li carti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_NOTHING] = "Gnint";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_VOLO] = "Volo";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_PIOMBO] = "Piombo";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_BUSSO_LAMIGLIORE] = "Cioca";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_BUSSO] = "Cioca";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_LAMIGLIORE] = "Cioca";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_STRISCIO_NEHOTANTE] = "Stresa tant";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_STRISCIO_COMELISCIO] = "Stresa";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_PUNTO_ANCORAUNA] = "A la Punti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_VIA_DAQUESTOGIOCO] = "Via";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_HO_ILTRE] = "Cioca al tri";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_HO_ILDUE] = "Cioca al du";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_RIBUSSO] = "Cioca al du";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_VOGLIOIL25] = "Voi al 25";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_ALTRECARTE] = "Atri carti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_HOIL25] = "A gu al 25";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_HO_ASSO] = "Punta l'Ass";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_LISCIO_NEHOANCORAPIUBASSE] = "Stresa";
		
	m_matStringsLang[LANG_DIAL_MN][ID_C_PIOMBOAUNPALO] = "Pimbà in dan pal";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MEN_OPTIONS] = "Upsion";
		
	m_matStringsLang[LANG_DIAL_MN][ID_OPT_GENERAL] = "In general";
		
	m_matStringsLang[LANG_DIAL_MN][ID_OPT_CONTRL_GENERAL] = "Upsion generichi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_OPT_CONTRL_GAME] = "Upsion dal seuc";
		
	m_matStringsLang[LANG_DIAL_MN][ID_OPT_CONTRL_DECK] = "Upsion mas ad li carti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_OPT_GAME] = "Seug";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CREDITS] = "Ringrasiament";
		
	m_matStringsLang[LANG_DIAL_MN][ID_WELCOMETITLEBAR] = "I me cumpliment par sugar an Trisetas!";
		
	m_matStringsLang[LANG_DIAL_MN][ID_STA_PTCURRENT] = "I punt d'ades";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSEMAZZO] = "Cata fora al mas adli carti";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSELOCALGAME] = "Cata fora al post";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LOCAL_BREDACISONI] = "A la Breda";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LOCAL_NEUTRAL] = "Neutral";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LOCAL_CHITARELLA] = "Dal Chitarela";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LOCAL_ROMANA] = "Rumana";
		
	m_matStringsLang[LANG_DIAL_MN][ID_LOCAL_CLASSIC] = "Classic";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSENAME] = "Scriv al to nom";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SHOWALGCONTROL] = "Fam veder in cuntroi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SHOWCARDANIMATION] = "Fam veder li carti movas";
		
	m_matStringsLang[LANG_DIAL_MN][ID_ENABLEDECLARGG] = "Con la cusa";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MATCHENDQUESTION] = "Som adre a suga, dabon at vo fni la partita?";
		
	m_matStringsLang[LANG_DIAL_MN][ID_YES] = "Se";
		
	m_matStringsLang[LANG_DIAL_MN][ID_NO] = "No";
		
	m_matStringsLang[LANG_DIAL_MN][ID_PIACENTINA] = "Piacentini";
		
	m_matStringsLang[LANG_DIAL_MN][ID_BERGAMO] = "Bergamaschi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_BOLOGNA] = "Bulugnesi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_GENOVA] = "Genuvesi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MILANO] = "Milanes";
		
	m_matStringsLang[LANG_DIAL_MN][ID_NAPOLI] = "Napulitani";
		
	m_matStringsLang[LANG_DIAL_MN][ID_PIEMONTE] = "Piemuntesi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_ROMAGNA] = "Rumangnoli";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SARDEGNA] = "Sardagnoli";
		
	m_matStringsLang[LANG_DIAL_MN][ID_TOSCANA] = "Tuscani";
		
	m_matStringsLang[LANG_DIAL_MN][ID_TRENTO] = "Trentini";
		
	m_matStringsLang[LANG_DIAL_MN][ID_TREVISO] = "Trevigiani";
		
	m_matStringsLang[LANG_DIAL_MN][ID_TRIESTE] = "Triestini";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SICILIA] = "Siciliani";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_RISP1] = "Ades at ghé da rispondar...";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PLAYER] = "Sugadur";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_DICE] = "dis";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_MANOPATA] = "Man patada, a toca a";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_MANOVINTA] = "Man vinsida da";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_GIOCATAPATA] = "Sugada patada";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_GIOCATAMONTE] = "Sugada  a munt";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_GIOCATAVINTA] = "Sugada vinsida da";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PUNTI] = "punt";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PUNTITOT] = "La soma di punt lè:";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PUNTIGIOCATA] = "I punt ad la man:";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SCOREGOAL] = "I punt da fa";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PUNTIACCUSE] = "I punt cusà:";
		
	m_matStringsLang[LANG_DIAL_MN][ID_PUNTIMATCH_GOAL] = "La partida la fnes ai punt:";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PARTITAFIN] = "PARTIDA fnida";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_NOWPOINTS] = "A gè so ades";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_BUIADA] = "Te det na stupidada, ciama giost";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_VINCE] = "vins";
		
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PERDE] = "pert";
		
	m_matStringsLang[LANG_DIAL_MN][ID_MN_HELP] = "Infurmasion";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_ACCUSA] = "l'ha cusà";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_NAPOLA] = "Napula a";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_SBAGLIA] = "sbaglia";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_SENZA] = "sensa";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_TRETRE] = "tri tri ";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_TREDUE] = "tri du ";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_TREASSI] = "tri ass ";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_4ASSI] = "quatr ass";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_4DUE] = "quatr du";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_4TRE] = "quatr tri";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_BASTONI] = "Baston";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_COPPE] = "Copi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_DENARI] = "Diner";
		
	m_matStringsLang[LANG_DIAL_MN][ID_A_SPADE] = "Spadi";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SPEED_SLOW] = "lent";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SPEED_FAST] = "veloce";
		
	m_matStringsLang[LANG_DIAL_MN][ID_BLOCKONMANOEND] = "Fermat a la fin ad la man";
		
	m_matStringsLang[LANG_DIAL_MN][ID_SIGNARMOUSEBT] = "Segna col tast dester dal maus";
		
	m_matStringsLang[LANG_ENG][ID_START] = "Start";
		
	m_matStringsLang[LANG_ENG][ID_LANGUAGESEL] = "Language";
		
	m_matStringsLang[LANG_ENG][ID_HISCORE] = "";
		
	m_matStringsLang[LANG_ENG][ID_VIDEOSET] = "";
		
	m_matStringsLang[LANG_ENG][ID_MAINMENU] = "Main Menu";
		
	m_matStringsLang[LANG_ENG][ID_OK] = "OK";
		
	m_matStringsLang[LANG_ENG][ID_CANCEL] = "Cancel";
		
	m_matStringsLang[LANG_ENG][ID_NAME] = "Name";
		
	m_matStringsLang[LANG_ENG][ID_EXIT] = "Exit";
		
	m_matStringsLang[LANG_ENG][ID_MUSIC] = "Music";
		
	m_matStringsLang[LANG_ENG][ID_SOUNDEFFECT] = "Sound effects";
		
	m_matStringsLang[LANG_ENG][ID_CHOOSELEVEL] = "";
		
	m_matStringsLang[LANG_ENG][ID_MANAGEPLAYER] = "Player control";
		
	m_matStringsLang[LANG_ENG][ID_BACKMAINMENU] = "Go to main menu";
		
	m_matStringsLang[LANG_ENG][ID_EASY] = "Easy";
		
	m_matStringsLang[LANG_ENG][ID_HARD] = "";
		
	m_matStringsLang[LANG_ENG][ID_HARDER] = "Very hard";
		
	m_matStringsLang[LANG_ENG][ID_BACK] = "Back";
		
	m_matStringsLang[LANG_ENG][ID_SELECTDISPLAYSETTINGS] = "Display select";
		
	m_matStringsLang[LANG_ENG][ID_GAMENAME] = "Tressette";
		
	m_matStringsLang[LANG_ENG][ID_CHOOSELANGUA] = "Select language";
		
	m_matStringsLang[LANG_ENG][ID_LANGUAGE] = "Language";
		
	m_matStringsLang[LANG_ENG][ID_ENGLISH] = "English";
		
	m_matStringsLang[LANG_ENG][ID_DIALETMN] = "Bredas dialect";
		
	m_matStringsLang[LANG_ENG][ID_ITALIANO] = "Italian";
		
	m_matStringsLang[LANG_ENG][ID_ANONIM] = "Anonimous";
		
	m_matStringsLang[LANG_ENG][ID_PUSHBUTTON] = "Push button";
		
	m_matStringsLang[LANG_ENG][ID_CMD_UNKNOWN] = "Unknown command";
		
	m_matStringsLang[LANG_ENG][ID_CMD_HELP] = "Commands available:";
		
	m_matStringsLang[LANG_ENG][ID_CMD_CHATWELCOME] = "";
		
	m_matStringsLang[LANG_ENG][ID_CMD_CHATLIST] = "";
		
	m_matStringsLang[LANG_ENG][ID_SOLITARIO] = "";
		
	m_matStringsLang[LANG_ENG][ID_MAZZONAME] = "Decks card";
		
	m_matStringsLang[LANG_ENG][ID_C_NOTHING] = "Nothing";
		
	m_matStringsLang[LANG_ENG][ID_C_VOLO] = "Volo";
		
	m_matStringsLang[LANG_ENG][ID_C_PIOMBO] = "Piombo";
		
	m_matStringsLang[LANG_ENG][ID_C_BUSSO_LAMIGLIORE] = "Busso";
		
	m_matStringsLang[LANG_ENG][ID_C_BUSSO] = "Busso";
		
	m_matStringsLang[LANG_ENG][ID_C_LAMIGLIORE] = "The best";
		
	m_matStringsLang[LANG_ENG][ID_C_STRISCIO_NEHOTANTE] = "Striscio";
		
	m_matStringsLang[LANG_ENG][ID_C_STRISCIO_COMELISCIO] = "Striscio";
		
	m_matStringsLang[LANG_ENG][ID_C_PUNTO_ANCORAUNA] = "Punto";
		
	m_matStringsLang[LANG_ENG][ID_C_VIA_DAQUESTOGIOCO] = "Via";
		
	m_matStringsLang[LANG_ENG][ID_C_HO_ILTRE] = "Ho il tre";
		
	m_matStringsLang[LANG_ENG][ID_C_HO_ILDUE] = "Ho il due";
		
	m_matStringsLang[LANG_ENG][ID_C_RIBUSSO] = "Ribusso";
		
	m_matStringsLang[LANG_ENG][ID_C_VOGLIOIL25] = "Voglio il 25";
		
	m_matStringsLang[LANG_ENG][ID_C_ALTRECARTE] = "Other cards";
		
	m_matStringsLang[LANG_ENG][ID_C_HOIL25] = "Ho il 25";
		
	m_matStringsLang[LANG_ENG][ID_C_HO_ASSO] = "Ho l'Asso";
		
	m_matStringsLang[LANG_ENG][ID_C_LISCIO_NEHOANCORAPIUBASSE] = "Liscio";
		
	m_matStringsLang[LANG_ENG][ID_C_PIOMBOAUNPALO] = "Piombo a un palo";
		
	m_matStringsLang[LANG_ENG][ID_MEN_OPTIONS] = "Options";
		
	m_matStringsLang[LANG_ENG][ID_OPT_GENERAL] = "General";
		
	m_matStringsLang[LANG_ENG][ID_OPT_CONTRL_GENERAL] = "General Options";
		
	m_matStringsLang[LANG_ENG][ID_OPT_CONTRL_GAME] = "Game Options";
		
	m_matStringsLang[LANG_ENG][ID_OPT_CONTRL_DECK] = "Deck Options";
		
	m_matStringsLang[LANG_ENG][ID_OPT_GAME] = "Game";
		
	m_matStringsLang[LANG_ENG][ID_CREDITS] = "Credits";
		
	m_matStringsLang[LANG_ENG][ID_WELCOMETITLEBAR] = "Welcome to the Tressette suite";
		
	m_matStringsLang[LANG_ENG][ID_STA_PTCURRENT] = "Current points";
		
	m_matStringsLang[LANG_ENG][ID_CHOOSEMAZZO] = "Choose a deck";
		
	m_matStringsLang[LANG_ENG][ID_CHOOSELOCALGAME] = "Local";
		
	m_matStringsLang[LANG_ENG][ID_LOCAL_BREDACISONI] = "Breda Cisoni";
		
	m_matStringsLang[LANG_ENG][ID_LOCAL_NEUTRAL] = "Neutral";
		
	m_matStringsLang[LANG_ENG][ID_LOCAL_CHITARELLA] = "Chitarrella";
		
	m_matStringsLang[LANG_ENG][ID_LOCAL_ROMANA] = "Roman";
		
	m_matStringsLang[LANG_ENG][ID_LOCAL_CLASSIC] = "Classic";
		
	m_matStringsLang[LANG_ENG][ID_CHOOSENAME] = "Insert your name";
		
	m_matStringsLang[LANG_ENG][ID_SHOWALGCONTROL] = "Show algorithm controls";
		
	m_matStringsLang[LANG_ENG][ID_SHOWCARDANIMATION] = "Show card animations";
		
	m_matStringsLang[LANG_ENG][ID_ENABLEDECLARGG] = "Call good game";
		
	m_matStringsLang[LANG_ENG][ID_MATCHENDQUESTION] = "Do you want exit the game?";
		
	m_matStringsLang[LANG_ENG][ID_YES] = "Yes";
		
	m_matStringsLang[LANG_ENG][ID_NO] = "No";
		
	m_matStringsLang[LANG_ENG][ID_PIACENTINA] = "Piacenza";
		
	m_matStringsLang[LANG_ENG][ID_BERGAMO] = "Bergamo";
		
	m_matStringsLang[LANG_ENG][ID_BOLOGNA] = "Bologna";
		
	m_matStringsLang[LANG_ENG][ID_GENOVA] = "Genova";
		
	m_matStringsLang[LANG_ENG][ID_MILANO] = "Milan";
		
	m_matStringsLang[LANG_ENG][ID_NAPOLI] = "Napoli";
		
	m_matStringsLang[LANG_ENG][ID_PIEMONTE] = "Piemonte";
		
	m_matStringsLang[LANG_ENG][ID_ROMAGNA] = "Romagna";
		
	m_matStringsLang[LANG_ENG][ID_SARDEGNA] = "Sardegna";
		
	m_matStringsLang[LANG_ENG][ID_TOSCANA] = "Toscana";
		
	m_matStringsLang[LANG_ENG][ID_TRENTO] = "Trento";
		
	m_matStringsLang[LANG_ENG][ID_TREVISO] = "Treviso";
		
	m_matStringsLang[LANG_ENG][ID_TRIESTE] = "Trieste";
		
	m_matStringsLang[LANG_ENG][ID_SICILIA] = "Sicilia";
		
	m_matStringsLang[LANG_ENG][ID_CP_RISP1] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_PLAYER] = "Player";
		
	m_matStringsLang[LANG_ENG][ID_CP_DICE] = "said";
		
	m_matStringsLang[LANG_ENG][ID_CP_MANOPATA] = "Hand draw, player on turn";
		
	m_matStringsLang[LANG_ENG][ID_CP_MANOVINTA] = "Hand wons by";
		
	m_matStringsLang[LANG_ENG][ID_CP_GIOCATAPATA] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_GIOCATAMONTE] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_GIOCATAVINTA] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_PUNTI] = "points";
		
	m_matStringsLang[LANG_ENG][ID_CP_PUNTITOT] = "Total points:";
		
	m_matStringsLang[LANG_ENG][ID_CP_PUNTIGIOCATA] = "Points on this trick:";
		
	m_matStringsLang[LANG_ENG][ID_SCOREGOAL] = "Points to win the match";
		
	m_matStringsLang[LANG_ENG][ID_CP_PUNTIACCUSE] = "Points on declarations:";
		
	m_matStringsLang[LANG_ENG][ID_PUNTIMATCH_GOAL] = "Match end on points:";
		
	m_matStringsLang[LANG_ENG][ID_CP_PARTITAFIN] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_NOWPOINTS] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_BUIADA] = "";
		
	m_matStringsLang[LANG_ENG][ID_CP_VINCE] = "win";
		
	m_matStringsLang[LANG_ENG][ID_CP_PERDE] = "lose";
		
	m_matStringsLang[LANG_ENG][ID_MN_HELP] = "Help";
		
	m_matStringsLang[LANG_ENG][ID_A_ACCUSA] = "has declared";
		
	m_matStringsLang[LANG_ENG][ID_A_NAPOLA] = "Napoletana on";
		
	m_matStringsLang[LANG_ENG][ID_A_SBAGLIA] = "without";
		
	m_matStringsLang[LANG_ENG][ID_A_SENZA] = "without";
		
	m_matStringsLang[LANG_ENG][ID_A_TRETRE] = "three three ";
		
	m_matStringsLang[LANG_ENG][ID_A_TREDUE] = "three two ";
		
	m_matStringsLang[LANG_ENG][ID_A_TREASSI] = "three ass ";
		
	m_matStringsLang[LANG_ENG][ID_A_4ASSI] = "four ass";
		
	m_matStringsLang[LANG_ENG][ID_A_4DUE] = "four two";
		
	m_matStringsLang[LANG_ENG][ID_A_4TRE] = "four three";
		
	m_matStringsLang[LANG_ENG][ID_A_BASTONI] = "Bastoni";
		
	m_matStringsLang[LANG_ENG][ID_A_COPPE] = "Coppe";
		
	m_matStringsLang[LANG_ENG][ID_A_DENARI] = "Denari";
		
	m_matStringsLang[LANG_ENG][ID_A_SPADE] = "Spade";
		
	m_matStringsLang[LANG_ENG][ID_SPEED_SLOW] = "slow";
		
	m_matStringsLang[LANG_ENG][ID_SPEED_FAST] = "fast";
		
	m_matStringsLang[LANG_ENG][ID_BLOCKONMANOEND] = "Pause on trick end";
		
	m_matStringsLang[LANG_ENG][ID_SIGNARMOUSEBT] = "Signal mouse right button";
		
}


std::string cLanguages::GetStringId(eStringID eId)
{
    
    assert(eId < TOT_STRINGS);

    if (eId < TOT_STRINGS)
    {
        sta_strRet = m_matStringsLang[m_eLangid][eId];
    }

    return sta_strRet;
}

char*  cLanguages::GetCStringId(eStringID eId)
{
    

    assert(eId < TOT_STRINGS);

    if (eId < TOT_STRINGS)
    {
        sta_strRet = m_matStringsLang[m_eLangid][eId];
    }

    return const_cast<char*>(sta_strRet.c_str()) ;
}


