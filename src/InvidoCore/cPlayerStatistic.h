

// cPlayerStatistic.h


#ifndef _______PLAYER_STATISTIC_H
#define _______PLAYER_STATISTIC_H

#include "cInvidoCoreEnv.h"
#include "AlgPlayerInterface.h"

//! class for player statistic
class cPlayerStatistic
{
public:
    cPlayerStatistic();
    //! clone statistic element
    void Clone(cPlayerStatistic* pNew);
    //! rest statistic
    void Reset();

public:
    //! actual score
    long    lScore;
    //! actual number of hand old
    long    lNumHand;
    //! actual number of briscole taken
    long    lNumBrisc;
    //! actual number of carac taken
    long    lNumCarac;
    //! number of strozzi remained
    long    bynStroz[NUM_SEEDS];
    //! number of Re remained
    long    bynRe[NUM_SEEDS];
    //! number of horse remained
    long    bynHorse[NUM_SEEDS];
    //! number of Fanti remained
    long    bynFanti[NUM_SEEDS];
    //! number of briscole remained
    long    lRemNumBrisc;
    //! number of points remained
    long    lRemNumPoints;
    //! last played seed first
    eSUIT   eLastPlayed;
    //! number of briscole played
    long    bynBriscHad;
    //! points played
    long    bynPointsHad;
    //! points of briscole played
    long    bynBriscPointsHad;
    //! number of briscole on the first hand
    long    bynBriscFirstHad;
    //! number of carac played
    long    lCaracHad;
    //! number of briscole in hand
    long    lInHand_nBris;
    //! number of carac in hand
    long    lInHand_nCarac;
    //! number of lisci in hand
    long    lInHand_nLisc;
    //! number of segni wons
    long    lSegniWons;

    friend std::ostream &operator << (std::ostream &stream, const struct tag_cPlayerStatistic &o);

};

inline std::ostream &operator << (std::ostream &stream, const cPlayerStatistic &o)
{ 
    stream << "---------------- new stat ------------------" << std::endl;
    stream << " punti totali = " << o.lScore << std::endl;
    stream << " num mani vinte = " << o.lNumHand << std::endl;
    stream << " num briscole prese = " << o.lNumBrisc << std::endl;
    stream << " num carichi presi = " << o.lNumCarac << std::endl;
    stream << " num briscole avute = " << o.bynBriscHad << std::endl;
    stream << " punti in briscole avuti = " << o.bynBriscPointsHad << std::endl;
    stream << " punti avuti = " << o.bynPointsHad << std::endl;
    stream << " num carichi giocati = " << o.lCaracHad << std::endl ;
    stream << " briscole in prima mano = " << o.bynBriscFirstHad << std::endl ;
    stream << std::endl;
   
    return stream;
}


//! structure for match statistic
typedef struct tag_MATCH_STATISTIC
{
    //! total segni wons
    long   lTotMatchWons;
    //! total segni losed
    long   lTotMatchLose;
    //! total points
    long   lTotPoints;
   friend std::ostream &operator << (std::ostream &stream, const struct tag_MATCH_STATISTIC &o);
}MATCH_STATISTIC;

inline std::ostream &operator << (std::ostream &stream, const tag_MATCH_STATISTIC &o)
{ 
    stream << "---------------- new stat ------------------" << std::endl;
    stream << " partite vinte = " << o.lTotMatchWons << std::endl;
    stream << " partite perse = " << o.lTotMatchLose << std::endl;
    stream << " punti fatti = " << o.lTotPoints << std::endl;
    stream << std::endl;
   
    return stream;
}

#endif
