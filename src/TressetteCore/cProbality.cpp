

//cProbality.cpp

#include "StdAfx.h"
#include "cProbality.h"


////////////////////////////////////////////////////////////////
//   *******************      cProbality CLASS ******************
////////////////////////////////////////////////////////////////



////////////////////////////////////////
//       SvilCombiHands
/*! Develop all possible hands with input deck 
// \param VCT_MAZZO &vct_Mazzo : input deck
*/
void cProbality::SvilCombiHands(VCT_MAZZO &vct_Mazzo, MTX_HANDCOMBI &mtx_Result)
{
	long lNumCard = (long)vct_Mazzo.size();
    mtx_Result.clear();

	size_t lNumCombi =  (size_t)BinomialCoef(lNumCard, m_iCardOnHand);

                       
    if (m_bIndexNotInit)
    {
        m_vctCounter.clear();
                           // inizializza counter
        for (long i = 0; i < m_iCardOnHand; i++)
        {
            m_vctCounter.push_back(i);
        }
    }

    m_bIndexNotInit = false;

                           // riserva spazio per lo sviluppo integrale
    mtx_Result.reserve(lNumCombi);

    VCT_SINGLECARD vct_tmpRow(m_iCardOnHand);
                           // sviluppo delle colonne
    for (long lCurrRow = 0; lCurrRow < lNumCombi; lCurrRow ++)
    {
        for (long j = 0; j < m_iCardOnHand; j ++ )
        {
             long lIndex = m_vctCounter[j];
             ASSERT(lIndex < lNumCard && lIndex >= 0);
             vct_tmpRow[j] = vct_Mazzo[lIndex]; 
        }

        mtx_Result.push_back(vct_tmpRow);

        if (lCurrRow == lNumCombi - 1)
        {
                           // ultima colonna, non c'è bisogno di calcolare gli indici
            break;
        }

        long i = 0,j = 0;
        long lChangeSubIndex = 0;
                           // incrementa gli indici
        for (j = m_iCardOnHand - 1; j >= 0; j-- )
        {
             m_vctCounter[j] ++;
             if (m_vctCounter[j] == lNumCard - i)
             {
                           // indice a fine corsa
                lChangeSubIndex = i + 1;
             }
             else
             {
                break;
             }
             i ++;
        }
                           // aggiorna tutti gli indici
        for (; lChangeSubIndex > 0; lChangeSubIndex --)
        {
             j = m_iCardOnHand - lChangeSubIndex;
             ASSERT( j - 1 >= 0);
             ASSERT(m_vctCounter[j - 1] + 1 < lNumCard);
             m_vctCounter[j] = m_vctCounter[j - 1] + 1;
        }
    }

    //Utility::SaveItemToFile(mtx_Result, DEF_path_s, "allhands.txt"); 

    
}


////////////////////////////////////////
//       BinomialCoef
/*! Coefficiente binomiale
// \param long lN : numero di elementi
// \param long lK : classe
*/
double cProbality::BinomialCoef(long lN, long lK)
{
   double dResult = 0.0;
   double dNum, dDen;

   dNum = Fattorial(lN);
   dDen = Fattorial(lN - lK) * Fattorial(lK);

   dResult = dNum / dDen;

   return dResult;
}

////////////////////////////////////////
//       Fattorial
/*! Fattoriale di n elementi 
// \param long lN : numero degli elementi
*/
double cProbality::Fattorial(long lN)
{
   double dResult = 1.0;

   for (long i = 0; i < lN - 1; i++)
   {
      dResult *= lN - i;
   }
   
   return dResult;
}

////////////////////////////////////////
//       << 
/*! Dump dello sviluppo in stream
// \param std::ostream &stream : output stream
// \param const MTX_HANDCOMBI &o : 
*/
std::ostream &operator << (std::ostream &stream, const MTX_HANDCOMBI &o)
{
   long lCount = 0;
   size_t iNumEle = o.size();
   for (long i = 0; i < iNumEle; i++)
   {
      lCount ++;
      VCT_SINGLECARD vct_tmpRow;
      vct_tmpRow = o[i];

      if (lCount < 10)
	  {
         stream <<  " [" << lCount << "] ";
	  }
      else
	  {
         stream <<  "[" << lCount << "] ";
	  }
      
	  size_t iNumRow = vct_tmpRow.size();
      for (long j = 0; j < iNumRow; j++)
      {
         if (vct_tmpRow[j] < 10)
         {
            stream << " " << ((int) vct_tmpRow[j]) << " ";
         }
         else
         {
            stream << ((int) vct_tmpRow[j]) << " ";
         }
      }
      stream << std::endl;
   }
   return stream;
}
