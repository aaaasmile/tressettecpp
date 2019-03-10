// AlgSupport.h

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

// function support for algorithm calculation

#ifndef _ALGSUPPORT_H____
#define _ALGSUPPORT_H____

#include "InfoComm.h"
#include "CoreEnv.h"
#include "CardSpec.h"

//! namespace AlgSupport
namespace AlgSupport
{
    enum eHandInfoTypeForce
    {
        MOLTOFORTE,
        FORTE,
        ATTACCO,
        DEBOLE,
        NOTDEF
    };
    enum eHandInfoLabel
    {
        _3_3_3_1,
        _3_3_2_2,
        _4_2_2_2,
        _4_3_2_1,
        _4_3_3_0,
        _4_4_1_1,
        _4_4_2_0,
        _5_2_2_1,
        _5_3_1_1,
        _5_3_2_0,
        _5_4_1_0,
        _5_5_0_0,
        _6_2_1_1,
        _6_2_2_0,
        _6_3_1_0,
        _6_4_0_0,
        _7_1_1_1,
        _7_2_1_0,
        _7_3_0_0,
        _8_1_1_0,
        _8_2_0_0,
        _9_1_0_0,
        _10_0_0_0
    };
    enum ePizzicoInSuit
    {
        NAPOLA, // 3 2 1
        VENTICINQUE, // 2 and 3
        VENTINOVE,   // 3 and 1
        VENTOTTO,    // 2 and 1
        TRE,
        DUE,
        ASSO,
        PIZZ_NONE
    };
    enum eHandBalance
    {
        BILANCIATA,
        SEMIBILANCIATA,
        SBILANCIATA,
        MOLTO_SBILANCIATA,
        BALA_NOTDEF
    };


    //! class cHandInfo
    struct HandInfo
    {
        //! label
        eHandInfoLabel       eValLabel;
        //! force
        eHandInfoTypeForce   eForce;
        //! balance
        eHandBalance         eBalance;
        //! number of pizzichi
        int                  iNumOfPizzichi;
        //! number of 3
        int                  iNum3;
        //! number of 2
        int                  iNum2;
        //! number of 1
        int                  iNum1;
        //! pizzichi on bastoni
        ePizzicoInSuit       ePizzOnBastoni;
        //! pizzichi on spade
        ePizzicoInSuit       ePizzOnSpade;
        //! pizzichi on coppe
        ePizzicoInSuit       ePizzOnCoppe;
        //! pizzichi on denari
        ePizzicoInSuit       ePizzOnDenari;
        //! opponent force on bastoni
        eHandInfoTypeForce   eOppForceBastoni;
        //! opponent force on denari
        eHandInfoTypeForce   eOppForceDenari;
        //! opponent force on coppe
        eHandInfoTypeForce   eOppForceCoppe;
        //! opponent force on spade
        eHandInfoTypeForce   eOppForceSpade;
    };

    //! provides a list of all available good games on the hand
    void GetAvailbDeclGoodGames(VCT_CARDINFO& vctCardInHand, VCT_GOODGAMEDETAIL& vctGoodGameRec);
    //! binomial coefficient
    double BinomialCoef(long lN, long lK);
    //! calculate fattorial
    double Fattorial(long lN);
    //! provides partner index
    int  GetPartnerIndex(int iPlayerIndex);

    //! class TrickInfo
    /** hold information abouta trick
    */
    class TrickInfo
    {
    public:
        //! constructor
        TrickInfo(){}

    public:
        //! player index that start the trick
        int           iPlayer_S;
        //! number of player tha have played
        BYTE           byNumPlayerPlayed;
        //! card played in the trick
        VCT_CARDSPEC   vctCardsPlayed;
        //! say player
        VCT_SAYPLAYER  vctSayPlayer;

    public:
        void Reset(){iPlayer_S = 0; byNumPlayerPlayed = 0; vctCardsPlayed.clear(); vctSayPlayer.clear();}
    };
};

#endif

