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
// fuzzy.h


///////////// fuzzy header
#ifndef  __FUZZY_COLLECTION_H__
#define  __FUZZY_COLLECTION_H__

#include <stdlib.h>

class FuzzyCollection
{
private:
   int fuzzyFALSE;
   int fuzzyTRUE;
   int fuzzyUNDEF;

public:
   FuzzyCollection(): fuzzyFALSE(0), fuzzyTRUE(100), fuzzyUNDEF(fuzzyTRUE >> 1)  {}
   FuzzyCollection(int a, int b, int c){fuzzyFALSE = a; fuzzyTRUE = b; fuzzyUNDEF = c;}

   int Fuzzy(int lValue, int lStart, int lEnd);
   int FuzzyAND(int nFirst, int nSecond){return nFirst < nSecond ? nFirst : nSecond;}
   int FuzzyOR(int nFirst, int nSecond){ return nFirst > nSecond ? nFirst : nSecond;}
   int FuzzyHYPEROR(int nFirst, int nSecond) {return ( (nFirst + nSecond) >= fuzzyTRUE ) ? fuzzyTRUE : ( nFirst + nSecond);}
   int FuzzyNOT(int nFuzzy){ return nFuzzy < fuzzyTRUE ? (fuzzyTRUE - nFuzzy) : fuzzyFALSE;}
};

////////////////////
// Fuzzy :
//                 --------------------
//               /
//             /
// -----------
/*! Normalized a value between 0 and 100. Linear norm into the rage is used.
// Values that <= lStart are 0; values that are >= lEnd are 100
// \param lValue : value to be normalized
// \param lStart : start range
// \param lEnd   : end range
*/
inline int FuzzyCollection::Fuzzy(int lValue, int lStart, int lEnd)
{
   if(lValue <= lStart)
   {
      return(fuzzyFALSE);
   }
   else if(lValue >= lEnd)
   {
      return(fuzzyTRUE);
   }
   else if(lEnd == lStart)
   {
      return(fuzzyTRUE);
   }
   else
   {
      return((short)(((lValue - lStart) * fuzzyTRUE) / (lEnd - lStart)));
   }
}

#endif
//////// end fuzzy header

