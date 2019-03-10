

//cInvidoCoreEnv.h

// c enum, struct for invido core


#ifndef _C_COREINVIDOENV_H_
#define _C_COREINVIDOENV_H_

#include <win_type_global.h>

#include "fuzzy.h"
#include "save_utility.h"

#include <algorithm>
#include <vector>
#include <iostream>

#define TRACE_BRISC_LEVEL 5 // trace level 

const std::string DEF_path_s = ".\\"; // path dove vengono memorizzati i dati


// points table. This table is to retrieve points for each cards in the pool
const int g_PointsTable[] = 
{ 
  /*Asso*/11, /*Due*/12, /*Tre*/13, /*Quattro*/4, /*cinque*/5, /*Sei*/6, /*Sette*/7, /*Fante*/8, /*Cavallo*/9, /*Re*/10,
  /*Asso*/11, /*Due*/12, /*Tre*/13, /*Quattro*/4, /*cinque*/5, /*Sei*/6, /*Sette*/7, /*Fante*/8, /*Cavallo*/9, /*Re*/10,
  /*Asso*/11, /*Due*/12, /*Tre*/13, /*Quattro*/4, /*cinque*/5, /*Sei*/6, /*Sette*/7, /*Fante*/8, /*Cavallo*/9, /*Re*/10,
  /*Asso*/11, /*Due*/12, /*Tre*/13, /*Quattro*/4, /*cinque*/5, /*Sei*/6, /*Sette*/7, /*Fante*/8, /*Cavallo*/9, /*Re*/10
}; 

const std::string g_CardsNameX[]=
{
  "Asso di bastoni", "Due di bastoni", "Tre di bastoni", "Quattro di bastoni", "Cinque di bastoni","Sei di bastoni", "Sette di bastoni", "Fante di bastoni", "Cavallo di bastoni", " Re di bastoni",
  "Asso di  coppe", "Due di  coppe", "Tre di  coppe", "Quattro di  coppe", "Cinque di  coppe", "Sei di  coppe", "Sette di  coppe", "Fante di  coppe", "Cavallo di  coppe", " Re di  coppe",
  "Asso di  denari", "Due di  denari", "Tre di  denari", "Quattro di  denari", "Cinque di  denari", "Sei di  denari", "Sette di  denari", "Fante di  denari", "Cavallo di  denari", " Re di  denari",
  "Asso di  spade", "Due di  spade", "Tre di  spade", "Quattro di  spade", "Cinque di  spade", "Sei di  spade", "Sette di  spade", "Fante di  spade", "Cavallo di  spade", " Re di  spade"
};


typedef std::vector<long> VCT_LONG;
typedef VCT_LONG::iterator IT_VCTLONG;


//! useful constants
enum
{
    //! index of me
    PLAYER_ME         = 0,
    //! index of opponent
    PLAYER_OPPONENT   = 1,
    //! number of cards on game invido
    NUM_CARDS         = 32,
    //! number of cards on briscola mazzo
    NUM_CARDS_MAZZBRI = 40,
    //! cards on hand of the player
    NUM_CARDS_HAND    = 3,
    NUM_HANDS         = 3,
    //! num of cards played on the table
    NUM_CARDS_PLAYED  = 2,
    //! total points to win a match
    SCORE_GOAL        = 24,
    //! special score 
    SPECIAL_SCORE     = 23,
    //! special score goal
    SPECIAL_SCORE_GOAL = 8,
    //! special score seven
    SCORE_SEVEN       = 7,
    NOT_VALID_INDEX   = -1,
    NUM_SEEDS         = 5,
    BUFF_NAME         = 64,
    //! players index
    PLAYER1           = 0,
    PLAYER2           = 1,
    PLAYER3           = 2,
    PLAYER4           = 3,
    MAX_NUM_PLAYER    = 4,
    NUM_PLAY_INVIDO_2 = 2
};

//! type of game
enum eGameType
{
    LOCAL_TYPE      = 0,
    NET_CLIENT_TYPE = 1,
    NET_SERVER_TYPE = 2
};


//! Partita state
enum ePartitaStatus
{
    WAIT_NEW_PARTITA = 0,
    PARTITA_ONGOING  = 1,
    PARTITA_END      = 2
};

//! Giocata state
enum eGiocataStatus
{
    WAIT_NEW_GIOCATA = 0,
    GIOCATA_ONGOING  = 1
};

//! Mano state
enum eManoStatus
{
    MNST_WAIT_NEW_MANO      = 0,
    MNST_WAIT_PLAY_PLAYER_1 = 1,
    MNST_WAIT_PLAY_PLAYER_2 = 2,
    MNST_WAIT_PLAY_PLAYER_3 = 3,
    MNST_WAIT_PLAY_PLAYER_4 = 4,
    MNST_MANO_END   = 5,    
    MNST_WAIT_RESP_PLAYER_1 = 6,
    MNST_WAIT_RESP_PLAYER_2 = 7,
    MNST_WAIT_RESP_PLAYER_3 = 8,
    MNST_WAIT_RESP_PLAYER_4 = 9,
};



//! game level
enum eGameLevel
{
    //! level dummy
    DUMMY = 0,
    //! level beginner
    BEGINNER = 1,
    //! level advanced
    ADVANCED = 2,
    //! level nightmare
    NIGHTMARE = 3,
    //! use hmi to play
    HMI       = 4,
    //! tester python
    TEST_PYTHON,
    //! server level
    SERVER_LEVEL
};




//! nature of the player
enum eTypeOfPLayer
{
    //! local player
    PT_LOCAL,
    //! machine player
    PT_MACHINE,
    //!remote player
    PT_REMOTE,
    //! server player handler
    PT_SERVER
};

//! type of notification for the script
enum eScriptNotification
{
    //! deck was shuffled
    SCR_NFY_SHUFFLEDECK = 0,
    //! have to say something
    SCR_NFY_HAVETO_SAY  = 1,
    //! have to play something
    SCR_NFY_HAVETO_PLAY = 2,
    //! new giocata notification
    SCR_NFY_NEWGIOCATA  = 3,
    SCR_NFY_ALGMANOEND  = 4,
    SCR_NFY_ALGGIOCATAEND = 5,
    SCR_NFY_ALGMATCHEND   = 6,
    SCR_NFY_NEWMATCH = 7 
};


#endif