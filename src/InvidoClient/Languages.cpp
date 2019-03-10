#include "StdAfx.h"
#include "win_type_global.h"
#include "Languages.h"
#include <assert.h>

// NOTA: questo file viene generato e modificato manualmente

static std::string sta_strRet ="Err trans.";

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
	m_matStringsLang[LANG_ITA][ID_EXIT] = "Esci";
	m_matStringsLang[LANG_ITA][ID_CHOOSELEVEL] = "Seleziona il gioco";
	m_matStringsLang[LANG_ITA][ID_BACKMAINMENU] = "Vai al menu principale";
	m_matStringsLang[LANG_ITA][ID_EASY] = "Facile";
	m_matStringsLang[LANG_ITA][ID_HARD] = "Difficile";
	m_matStringsLang[LANG_ITA][ID_HARDER] = "Difficilissimo";
	m_matStringsLang[LANG_ITA][ID_BACK] = "Torna indietro";
	m_matStringsLang[LANG_ITA][ID_SELECTDISPLAYSETTINGS] = "Seleziona il display";
	m_matStringsLang[LANG_ITA][ID_INVIDO] = "Invido";
	m_matStringsLang[LANG_ITA][ID_CHOOSELANGUA] = "Seleziona la lingua";
	m_matStringsLang[LANG_ITA][ID_ENGLISH] = "Inglese";
	m_matStringsLang[LANG_ITA][ID_DIALETMN] = "Dialetto Bredese";
	m_matStringsLang[LANG_ITA][ID_ITALIANO] = "Italiano";
	m_matStringsLang[LANG_ITA][ID_ANONIM] = "Remigiu";
	m_matStringsLang[LANG_ITA][ID_PUSHBUTTON] = "Premi un tasto";
	m_matStringsLang[LANG_ITA][ID_CMD_UNKNOWN] = "Comando non riconosciuto";
	m_matStringsLang[LANG_ITA][ID_CMD_HELP] = "Comandi che puoi usare:";
	m_matStringsLang[LANG_ITA][ID_CMD_CHATWELCOME] = "Bene arrivato nella chat";
	m_matStringsLang[LANG_ITA][ID_CMD_CHATLIST] = "La lista dei presenti nella chat";
	m_matStringsLang[LANG_ITA][ID_MAZZONAME] = "Mazzi di carte";
	m_matStringsLang[LANG_ITA][ID_S_AMONTE] = "A monte";
	m_matStringsLang[LANG_ITA][ID_S_INVIDO] = "Invido";
	m_matStringsLang[LANG_ITA][ID_S_TRASMAS] = "Tras mas";
	m_matStringsLang[LANG_ITA][ID_S_TRASMASNOEF] = "Tras mas noef";
	m_matStringsLang[LANG_ITA][ID_S_FUERAJEUQ] = "Fuori gioco";
	m_matStringsLang[LANG_ITA][ID_S_PARTIDA] = "Partita";
	m_matStringsLang[LANG_ITA][ID_S_VABENE] = "Va bene";
	m_matStringsLang[LANG_ITA][ID_S_VADOVIA] = "Vado via";
	m_matStringsLang[LANG_ITA][ID_S_CHIAMADIPIU] = "Chiama di più";
	m_matStringsLang[LANG_ITA][ID_S_NO] = "No";
	m_matStringsLang[LANG_ITA][ID_S_GIOCA] = "Gioca";
	m_matStringsLang[LANG_ITA][ID_S_BT_AMONTE] = "Monte";
	m_matStringsLang[LANG_ITA][ID_S_BT_INVIDO] = "Invido";
	m_matStringsLang[LANG_ITA][ID_S_BT_TRASMAS] = "Tras mas";
	m_matStringsLang[LANG_ITA][ID_S_BT_TRASMASNOEF] = "Nof";
	m_matStringsLang[LANG_ITA][ID_S_BT_FUERAJEUQ] = "Fuori J.";
	m_matStringsLang[LANG_ITA][ID_S_BT_PARTIDA] = "Partita";
	m_matStringsLang[LANG_ITA][ID_S_BT_VABENE] = "Va bene";
	m_matStringsLang[LANG_ITA][ID_S_BT_VADOVIA] = "Vado via";
	m_matStringsLang[LANG_ITA][ID_S_BT_CHIAMADIPIU] = "Chiama di più";
	m_matStringsLang[LANG_ITA][ID_S_BT_NO] = "No";
	m_matStringsLang[LANG_ITA][ID_S_BT_GIOCA] = "Gioca";
	m_matStringsLang[LANG_ITA][ID_S_CANELA] = "Stanga";
	m_matStringsLang[LANG_ITA][ID_S_PATA] = "Patta";
	m_matStringsLang[LANG_ITA][ID_MEN_OPTIONS] = "Opzioni";
	m_matStringsLang[LANG_ITA][ID_CREDITS] = "Credits";
	m_matStringsLang[LANG_ITA][ID_WELCOMETITLEBAR] = "Benvenuti nel mondo dell'invido!";
	m_matStringsLang[LANG_ITA][ID_STA_PTCURRENT] = "Punteggio attuale";
	m_matStringsLang[LANG_ITA][ID_CHOOSEMAZZO] = "Scegli il mazzo di carte";
	m_matStringsLang[LANG_ITA][ID_PIACENTINA] = "Piacentine";
	m_matStringsLang[LANG_ITA][ID_BERGAMO] = "Bergamesche";
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
	m_matStringsLang[LANG_ITA][ID_CP_PARTITAFIN] = "PARTITA finita";
	m_matStringsLang[LANG_ITA][ID_CP_NOWPOINTS] = "Punteggio della giocata ora è";
	m_matStringsLang[LANG_ITA][ID_CP_BUIADA] = "Quello che hai chiamato non è corretto";
	m_matStringsLang[LANG_ITA][ID_CP_VINCE] = "vince";
	m_matStringsLang[LANG_ITA][ID_MN_HELP] = "Guida";
	m_matStringsLang[LANG_ITA][ID_OK] = "OK";
	m_matStringsLang[LANG_ITA][ID_CANCEL] = "Cancella";
	m_matStringsLang[LANG_ITA][ID_NAME] = "Nome";
	m_matStringsLang[LANG_ITA][ID_OPT_CONTRL_GENERAL] = "Opzioni Generali";
	m_matStringsLang[LANG_ITA][ID_MUSIC] = "Musica";
	m_matStringsLang[LANG_ITA][ID_SOUNDEFFECT] = "Effetti sonori";
	m_matStringsLang[LANG_ITA][ID_LANGUAGE] = "Lingua";
	m_matStringsLang[LANG_ITA][ID_MATCHENDQUESTION] = "Partita in corso, vuoi  uscire?";
	m_matStringsLang[LANG_ITA][ID_YES] = "Si";
	m_matStringsLang[LANG_ITA][ID_NO] = "No";
	m_matStringsLang[LANG_ITA][ID_CHOOSENAME] = "Immetti il tuo nome";
	m_matStringsLang[LANG_ITA][ID_SHOWFOTOBACK] = "Mostra foto sfondo";
    m_matStringsLang[LANG_ITA][ID_S_BT_VADODENTRO] = "Vado dentro";
    m_matStringsLang[LANG_ITA][ID_S_BT_CHIAMA_BORTOLO] = "Dagli del bortolo";
    m_matStringsLang[LANG_ITA][ID_S_VADODENTRO] = "Vado dentro";
	
	// Dialetto bredese
	m_matStringsLang[LANG_DIAL_MN][ID_START] = "Cumincia";
	m_matStringsLang[LANG_DIAL_MN][ID_LANGUAGESEL] = "Lengui furèsti";
	m_matStringsLang[LANG_DIAL_MN][ID_HISCORE] = "I mei di mei";
	m_matStringsLang[LANG_DIAL_MN][ID_VIDEOSET] = "Al schermo";
	m_matStringsLang[LANG_DIAL_MN][ID_MAINMENU] = "Menu principal";
	m_matStringsLang[LANG_DIAL_MN][ID_EXIT] = "Fnomla che";
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSELEVEL] = "Selesiuna al gioc";
	m_matStringsLang[LANG_DIAL_MN][ID_BACKMAINMENU] = "Va al menu principal";
	m_matStringsLang[LANG_DIAL_MN][ID_EASY] = "Facil";
	m_matStringsLang[LANG_DIAL_MN][ID_HARD] = "Dificil";
	m_matStringsLang[LANG_DIAL_MN][ID_HARDER] = "Dificilisim";
	m_matStringsLang[LANG_DIAL_MN][ID_BACK] = "Turna indrè";
	m_matStringsLang[LANG_DIAL_MN][ID_SELECTDISPLAYSETTINGS] = "Selesiuna al schermo";
	m_matStringsLang[LANG_DIAL_MN][ID_INVIDO] = "Invidu";
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSELANGUA] = "Selesiuna la lengua";
	m_matStringsLang[LANG_DIAL_MN][ID_ENGLISH] = "Ingles";
	m_matStringsLang[LANG_DIAL_MN][ID_DIALETMN] = "Dialet";
	m_matStringsLang[LANG_DIAL_MN][ID_ITALIANO] = "Italian";
	m_matStringsLang[LANG_DIAL_MN][ID_ANONIM] = "Anonim";
	m_matStringsLang[LANG_DIAL_MN][ID_PUSHBUTTON] = "Schesa an buton";
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_UNKNOWN] = "Cumand mia cunusi";
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_HELP] = "I cumand cat po drua:";
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_CHATWELCOME] = "Ben arriva indla chat";
	m_matStringsLang[LANG_DIAL_MN][ID_CMD_CHATLIST] = "Chi ghè in dla chat";
	m_matStringsLang[LANG_DIAL_MN][ID_MAZZONAME] = "Mas ad li carti";
	m_matStringsLang[LANG_DIAL_MN][ID_S_AMONTE] = "A munt";
	m_matStringsLang[LANG_DIAL_MN][ID_S_INVIDO] = "Invidu";
	m_matStringsLang[LANG_DIAL_MN][ID_S_TRASMAS] = "Tras mas";
	m_matStringsLang[LANG_DIAL_MN][ID_S_TRASMASNOEF] = "Tras mas nof";
	m_matStringsLang[LANG_DIAL_MN][ID_S_FUERAJEUQ] = "Fora gioc";
	m_matStringsLang[LANG_DIAL_MN][ID_S_PARTIDA] = "Partida";
	m_matStringsLang[LANG_DIAL_MN][ID_S_VABENE] = "Va ben";
	m_matStringsLang[LANG_DIAL_MN][ID_S_VADOVIA] = "Vu via";
	m_matStringsLang[LANG_DIAL_MN][ID_S_CHIAMADIPIU] = "Ciama pusè";
	m_matStringsLang[LANG_DIAL_MN][ID_S_NO] = "In frunt";
	m_matStringsLang[LANG_DIAL_MN][ID_S_GIOCA] = "Gioga";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_AMONTE] = "Munt";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_INVIDO] = "Invidu";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_TRASMAS] = "Tras mas";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_TRASMASNOEF] = "Nof";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_FUERAJEUQ] = "Fora Gi.";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_PARTIDA] = "Partida";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_VABENE] = "Va ben";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_VADOVIA] = "Vu via";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_CHIAMADIPIU] = "Ciama pusè";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_NO] = "No";
	m_matStringsLang[LANG_DIAL_MN][ID_S_BT_GIOCA] = "Gioga";
	m_matStringsLang[LANG_DIAL_MN][ID_S_CANELA] = "Canela";
	m_matStringsLang[LANG_DIAL_MN][ID_S_PATA] = "Pata";
	m_matStringsLang[LANG_DIAL_MN][ID_MEN_OPTIONS] = "Upsion";
	m_matStringsLang[LANG_DIAL_MN][ID_CREDITS] = "Ringrasiament";
	m_matStringsLang[LANG_DIAL_MN][ID_WELCOMETITLEBAR] = "I me cumpliment par sugar a l'Invidu!";
	m_matStringsLang[LANG_DIAL_MN][ID_STA_PTCURRENT] = "I punt d'ades";
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSEMAZZO] = "Cata fora al mas adli carti";
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
	m_matStringsLang[LANG_DIAL_MN][ID_CP_PARTITAFIN] = "PARTIDA fnida";
	m_matStringsLang[LANG_DIAL_MN][ID_CP_NOWPOINTS] = "A gè so ades";
	m_matStringsLang[LANG_DIAL_MN][ID_CP_BUIADA] = "Te det na stupidada, ciama giost";
	m_matStringsLang[LANG_DIAL_MN][ID_CP_VINCE] = "vins";
	m_matStringsLang[LANG_DIAL_MN][ID_MN_HELP] = "Infurmasion";
	m_matStringsLang[LANG_DIAL_MN][ID_OK] = "Sè";
	m_matStringsLang[LANG_DIAL_MN][ID_CANCEL] = "Scàsa";
	m_matStringsLang[LANG_DIAL_MN][ID_NAME] = "Nom";
	m_matStringsLang[LANG_DIAL_MN][ID_OPT_CONTRL_GENERAL] = "Upsion generichi";
	m_matStringsLang[LANG_DIAL_MN][ID_MUSIC] = "La musica";
	m_matStringsLang[LANG_DIAL_MN][ID_SOUNDEFFECT] = "I rumur";
	m_matStringsLang[LANG_DIAL_MN][ID_LANGUAGE] = "Lengui furesti";
	m_matStringsLang[LANG_DIAL_MN][ID_MATCHENDQUESTION] = "Som adre a suga, dabon at vo fni la partita?";
	m_matStringsLang[LANG_DIAL_MN][ID_YES] = "Se";
	m_matStringsLang[LANG_DIAL_MN][ID_NO] = "No";
	m_matStringsLang[LANG_DIAL_MN][ID_CHOOSENAME] = "Scriv al to nom";
	m_matStringsLang[LANG_DIAL_MN][ID_SHOWFOTOBACK] = "La foto in dal sfont";
    m_matStringsLang[LANG_DIAL_MN][ID_S_BT_VADODENTRO] = "A vu dentar";
    m_matStringsLang[LANG_DIAL_MN][ID_S_BT_CHIAMA_BORTOLO] = "Dag dal burtul";
    m_matStringsLang[LANG_DIAL_MN][ID_S_VADODENTRO] = "Vu dentar";

	// English language
	m_matStringsLang[LANG_ENG][ID_START] = "Start";
	m_matStringsLang[LANG_ENG][ID_LANGUAGESEL] = "Language";
	m_matStringsLang[LANG_ENG][ID_HISCORE] = "Hight Score";
	m_matStringsLang[LANG_ENG][ID_VIDEOSET] = "";
	m_matStringsLang[LANG_ENG][ID_MAINMENU] = "";
	m_matStringsLang[LANG_ENG][ID_EXIT] = "Exit";
	m_matStringsLang[LANG_ENG][ID_CHOOSELEVEL] = "Select a game level";
	m_matStringsLang[LANG_ENG][ID_BACKMAINMENU] = "Go to main menu";
	m_matStringsLang[LANG_ENG][ID_EASY] = "Easy";
	m_matStringsLang[LANG_ENG][ID_HARD] = "Hard";
	m_matStringsLang[LANG_ENG][ID_HARDER] = "Very Hard";
	m_matStringsLang[LANG_ENG][ID_BACK] = "Back";
	m_matStringsLang[LANG_ENG][ID_SELECTDISPLAYSETTINGS] = "Display select";
	m_matStringsLang[LANG_ENG][ID_INVIDO] = "Invido";
	m_matStringsLang[LANG_ENG][ID_CHOOSELANGUA] = "Select language";
	m_matStringsLang[LANG_ENG][ID_ENGLISH] = "English";
	m_matStringsLang[LANG_ENG][ID_DIALETMN] = "Bredas dialect";
	m_matStringsLang[LANG_ENG][ID_ITALIANO] = "Italian";
	m_matStringsLang[LANG_ENG][ID_ANONIM] = "Anonimous";
	m_matStringsLang[LANG_ENG][ID_PUSHBUTTON] = "Push button";
	m_matStringsLang[LANG_ENG][ID_CMD_UNKNOWN] = "Unknown command";
	m_matStringsLang[LANG_ENG][ID_CMD_HELP] = "Commands available:";
	m_matStringsLang[LANG_ENG][ID_CMD_CHATWELCOME] = "Welcome in the chaatroom";
	m_matStringsLang[LANG_ENG][ID_CMD_CHATLIST] = "Chat list";
	m_matStringsLang[LANG_ENG][ID_MAZZONAME] = "Decks card";
	m_matStringsLang[LANG_ENG][ID_S_AMONTE] = "Monte";
	m_matStringsLang[LANG_ENG][ID_S_INVIDO] = "Invido";
	m_matStringsLang[LANG_ENG][ID_S_TRASMAS] = "Tras mas";
	m_matStringsLang[LANG_ENG][ID_S_TRASMASNOEF] = "Tras mas nof";
	m_matStringsLang[LANG_ENG][ID_S_FUERAJEUQ] = "Fora gioc";
	m_matStringsLang[LANG_ENG][ID_S_PARTIDA] = "Partida";
	m_matStringsLang[LANG_ENG][ID_S_VABENE] = "Ok";
	m_matStringsLang[LANG_ENG][ID_S_VADOVIA] = "Go away";
	m_matStringsLang[LANG_ENG][ID_S_CHIAMADIPIU] = "Call more";
	m_matStringsLang[LANG_ENG][ID_S_NO] = "No";
	m_matStringsLang[LANG_ENG][ID_S_GIOCA] = "Play";
	m_matStringsLang[LANG_ENG][ID_S_BT_AMONTE] = "Mountain";
	m_matStringsLang[LANG_ENG][ID_S_BT_INVIDO] = "Invidu";
	m_matStringsLang[LANG_ENG][ID_S_BT_TRASMAS] = "Tras mas";
	m_matStringsLang[LANG_ENG][ID_S_BT_TRASMASNOEF] = "Nof";
	m_matStringsLang[LANG_ENG][ID_S_BT_FUERAJEUQ] = "Fuori J.";
	m_matStringsLang[LANG_ENG][ID_S_BT_PARTIDA] = "Partida";
	m_matStringsLang[LANG_ENG][ID_S_BT_VABENE] = "Ok";
	m_matStringsLang[LANG_ENG][ID_S_BT_VADOVIA] = "Go away";
	m_matStringsLang[LANG_ENG][ID_S_BT_CHIAMADIPIU] = "Call more";
	m_matStringsLang[LANG_ENG][ID_S_BT_NO] = "No";
	m_matStringsLang[LANG_ENG][ID_S_BT_GIOCA] = "Play";
	m_matStringsLang[LANG_ENG][ID_S_CANELA] = "Line";
	m_matStringsLang[LANG_ENG][ID_S_PATA] = "Drawn";
	m_matStringsLang[LANG_ENG][ID_MEN_OPTIONS] = "Options";
	m_matStringsLang[LANG_ENG][ID_CREDITS] = "Credits";
	m_matStringsLang[LANG_ENG][ID_WELCOMETITLEBAR] = "Welcome into the Invido's world";
	m_matStringsLang[LANG_ENG][ID_STA_PTCURRENT] = "Current points";
	m_matStringsLang[LANG_ENG][ID_CHOOSEMAZZO] = "Choose a deck";
	m_matStringsLang[LANG_ENG][ID_PIACENTINA] = "Piacentinas";
	m_matStringsLang[LANG_ENG][ID_BERGAMO] = "Bergamos";
	m_matStringsLang[LANG_ENG][ID_BOLOGNA] = "Bolognas";
	m_matStringsLang[LANG_ENG][ID_GENOVA] = "Genovas";
	m_matStringsLang[LANG_ENG][ID_MILANO] = "Milans";
	m_matStringsLang[LANG_ENG][ID_NAPOLI] = "Napolis";
	m_matStringsLang[LANG_ENG][ID_PIEMONTE] = "Piemontes";
	m_matStringsLang[LANG_ENG][ID_ROMAGNA] = "Romagnas";
	m_matStringsLang[LANG_ENG][ID_SARDEGNA] = "Sardegnas";
	m_matStringsLang[LANG_ENG][ID_TOSCANA] = "Toscanas";
	m_matStringsLang[LANG_ENG][ID_TRENTO] = "Trentos";
	m_matStringsLang[LANG_ENG][ID_TREVISO] = "Trevisos";
	m_matStringsLang[LANG_ENG][ID_TRIESTE] = "Triestes";
	m_matStringsLang[LANG_ENG][ID_SICILIA] = "Sicilias";
	m_matStringsLang[LANG_ENG][ID_CP_RISP1] = "Now you must responce";
	m_matStringsLang[LANG_ENG][ID_CP_PLAYER] = "Player";
	m_matStringsLang[LANG_ENG][ID_CP_DICE] = "said";
	m_matStringsLang[LANG_ENG][ID_CP_MANOPATA] = "Hand draw, player on turn";
	m_matStringsLang[LANG_ENG][ID_CP_MANOVINTA] = "Hand wons by";
	m_matStringsLang[LANG_ENG][ID_CP_GIOCATAPATA] = "Trick drawn";
	m_matStringsLang[LANG_ENG][ID_CP_GIOCATAMONTE] = "Trick invalid";
	m_matStringsLang[LANG_ENG][ID_CP_GIOCATAVINTA] = "Trink won by";
	m_matStringsLang[LANG_ENG][ID_CP_PUNTI] = "points";
	m_matStringsLang[LANG_ENG][ID_CP_PARTITAFIN] = "Match terminated";
	m_matStringsLang[LANG_ENG][ID_CP_NOWPOINTS] = "Current points";
	m_matStringsLang[LANG_ENG][ID_CP_BUIADA] = "You said something incorrect";
	m_matStringsLang[LANG_ENG][ID_CP_VINCE] = "win";
	m_matStringsLang[LANG_ENG][ID_MN_HELP] = "Help";
	m_matStringsLang[LANG_ENG][ID_OK] = "OK";
	m_matStringsLang[LANG_ENG][ID_CANCEL] = "Cancel";
	m_matStringsLang[LANG_ENG][ID_NAME] = "Name";
	m_matStringsLang[LANG_ENG][ID_OPT_CONTRL_GENERAL] = "General Options";
	m_matStringsLang[LANG_ENG][ID_MUSIC] = "Music";
	m_matStringsLang[LANG_ENG][ID_SOUNDEFFECT] = "Sound effects";
	m_matStringsLang[LANG_ENG][ID_LANGUAGE] = "Language";
	m_matStringsLang[LANG_ENG][ID_MATCHENDQUESTION] = "Do you want exit the game?";
	m_matStringsLang[LANG_ENG][ID_YES] = "Yes";
	m_matStringsLang[LANG_ENG][ID_NO] = "No";
	m_matStringsLang[LANG_ENG][ID_CHOOSENAME] = "Insert your name";
	m_matStringsLang[LANG_ENG][ID_SHOWFOTOBACK] = "Show foto in background";
    m_matStringsLang[LANG_ENG][ID_S_BT_VADODENTRO] = "I go inside";
    m_matStringsLang[LANG_ENG][ID_S_BT_CHIAMA_BORTOLO] = "Call bortolo";
    m_matStringsLang[LANG_ENG][ID_S_VADODENTRO] = "Go inside";
}


std::string cLanguages::GetStringId(eStringID eId)
{
	ASSERT(eId < TOT_STRINGS);
    if (eId < TOT_STRINGS)
    {
        sta_strRet = m_matStringsLang[m_eLangid][eId];
    }
    return sta_strRet;
}

char*  cLanguages::GetCStringId(eStringID eId)
{
    ASSERT(eId < TOT_STRINGS);
    if (eId < TOT_STRINGS)
    {
        sta_strRet = m_matStringsLang[m_eLangid][eId];
    }
    return const_cast<char*>(sta_strRet.c_str()) ;
}


