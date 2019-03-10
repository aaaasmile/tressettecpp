// InvidoInfoComm.h

#ifndef __INVIDOINFO_COMM_H
#define __INVIDOINFO_COMM_H

#include <vector>

enum
{
    // trace channels
    TR_CORE_CH = 0,
};

#ifndef BOOL 
    typedef int BOOL;
#endif

#ifndef BYTE
    typedef unsigned char BYTE;
#endif

//! suit of cards
enum eSUIT
{
    BASTONI = 0,
    COPPE = 1,
    DENARI = 2,
    SPADE = 3,
    UNDEF = 4
};

//! what the player can say
enum eSayPlayer
{
    AMONTE = 0,
    INVIDO = 1,
    TRASMAS = 2,
    TRASMASNOEF = 3,
    FUERAJEUQ = 4,
    PARTIDA = 5,
    VABENE = 6,
    VADOVIA = 7,
    CHIAMADIPIU = 8,
    NO = 9,
    VADODENTRO = 10,
    GIOCA = 11,
    CHIAMA_BORTOLO = 12,
    NOTHING = 13
};

//! giocata score state
enum eGiocataScoreState
{
    SC_AMONTE = 0,
    SC_PATTA = 0,
    SC_CANELA = 1,
    SC_INVIDO = 3,
    SC_TRASMAS = 6,
    SC_TRASMASNOEF = 9,
    SC_FUERAJEUQ = 12,
    SC_PARTIDA = 24,
};

#define NUM_BYTE_NAME 32

//! information about card
typedef struct _CardInfo
{
    //! index of the card
   BYTE   byIndex;
   //! seed of the card
   eSUIT  eSuit;
   //! name of the card
   char   CardName[NUM_BYTE_NAME];
}CARDINFO;

typedef std::vector<eSayPlayer>               VCT_COMMANDS;


#endif