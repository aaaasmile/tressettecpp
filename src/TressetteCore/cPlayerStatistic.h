/*
    Tressette
    Copyright (C) 2005  Igor Sarzi Sartori

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Igor Sarzi Sartori
    www.invido.it
    6colpiunbucosolo@gmx.net
*/



// cPlayerStatistic.h


#ifndef _______PLAYER_STATISTIC_H
#define _______PLAYER_STATISTIC_H

#include "CoreEnv.h"
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
