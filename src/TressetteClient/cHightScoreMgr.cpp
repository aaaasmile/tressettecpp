
// cHightScoreMgr.cpp: implementation of the cHightScoreMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "win_type_global.h"
#include "cHightScoreMgr.h"
#include <stdlib.h>
#include <io.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cHightScoreMgr::cHightScoreMgr()
{

}

cHightScoreMgr::~cHightScoreMgr()
{

}



////////////////////////////////////////
//       Save
/*! Save hight score in file
*/
void cHightScoreMgr::Save()
{
    int f;
    char buffer[16];
    unsigned int score,k,nb;
    string name;
    
    f=open("scores.bin",  _O_TRUNC | _O_WRONLY | _O_CREAT, _S_IREAD | _S_IWRITE   );
    
    if (f>0)
    {
        for (k=0;k<10;k++)
        {
            score=HS_Scores[k];
            memset(buffer,0,16);
            memcpy(buffer,HS_Names[k].c_str(),15);
            nb=write(f,&score,4);
            nb=write(f,buffer,15);
            
        }
        close(f);
    }
}


////////////////////////////////////////
//       Load
/*! Load hight scores from file
*/
void cHightScoreMgr::Load()
{	
    int f;
    char buffer[16];
    unsigned int score,k;
    string name;
    
    f=open("scores.bin", O_RDONLY|O_BINARY );
    if (f>0)
    {
        for (k=0;k<10;k++)
        {
            if (read(f,&score,4)==0)
                score=0;
            if (read(f,buffer,15)==0)
                name="";
            else
                name=buffer;
            HS_Scores[k]=score;
            HS_Names[k]=name;
        }
        close(f);
    }
    else
    {
        for (k=0;k<10;k++)
        {
            HS_Scores[k]=(10-k)*1000;
            HS_Names[k]="Re dal sulitari";
        }
    }
}

