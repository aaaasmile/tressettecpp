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


//save_utility.h

#ifndef _SAVE_UTILITY__H
#define _SAVE_UTILITY__H
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#ifndef VOID
   #define VOID void
#endif

namespace Utility
{
#ifdef _DEBUG

////////////////////////////////////
// SaveContainerToFile
/*! save  container  in a file
*/
template <class T> inline 
VOID SaveContainerToFile(T &myContainer, char *fname)
{
   std::ofstream out(fname);
   T::const_iterator Icontainer;
   
   Icontainer = myContainer.begin();
   while (Icontainer != myContainer.end())
   {
      out << *Icontainer << endl;
      Icontainer++;
   }

   out.close();
}//end SaveContainerToFile

// Save iterators in a file
template <class T> inline 
VOID SaveIteratorsToFile(T &myContainer, char *fname)
{
   std::ofstream out(fname);
   T::const_iterator Icontainer;
   
   Icontainer = myContainer.begin();
   while (Icontainer != myContainer.end())
   {
      out << **Icontainer << endl;
      Icontainer++;
   }

   out.close();
}

//////////////////////////////// PATH + FILENAME //////////////////////

template <class T> inline 
VOID SaveContainerToFile(T &myContainer, const std::string &pathfname, const std::string &fname )
{
   std::string FileName = pathfname;

   FileName += fname;

   std::ofstream out(FileName.c_str());
   T::const_iterator Icontainer;
   
   Icontainer = myContainer.begin();
   while (Icontainer != myContainer.end())
   {
      out << *Icontainer << std::endl;
      Icontainer++;
   }

   out.close();
}//end SaveContainerToFile

// Save iterators in a file
template <class T> inline 
VOID SaveIteratorsToFile(T &myContainer, const std::string &pathfname, const std::string &fname )
{
   std::string FileName = pathfname;

   FileName += fname;

   std::ofstream out(FileName.c_str());
   T::const_iterator Icontainer;
   
   Icontainer = myContainer.begin();
   while (Icontainer != myContainer.end())
   {
      out << **Icontainer << endl;
      Icontainer++;
   }

   out.close();
}

//SaveItemToFile
template <class T> inline 
VOID SaveItemToFile(T &myContainer, const std::string &pathfname, const std::string &fname )
{
   
   std::string FileName = pathfname;

   FileName += fname;
   
   std::ofstream out(FileName.c_str());

   
   out << myContainer << std::endl;
   
   out.close();
}

// trace the container in the debug window
template <class T> inline
VOID TraceContainer( T &myContainer, const std::string &strComment )
{
    T::const_iterator Icontainer;
   
    std::ostringstream out;
    std::string w;

    out << strComment << std::endl;

    Icontainer = myContainer.begin();
    while (Icontainer != myContainer.end())
    {
        out << *Icontainer << " ";
        Icontainer++;
    }
    out <<  std::endl;
    w = out.str();
    //::OutputDebugString(w.c_str());
    TRACE(w.c_str());
}//end TraceContainer

// trace an object in the debug window
template <class T> inline
VOID TraceItem( T &myContainer, const std::string &strComment )
{
    
    std::ostringstream out;
    std::string w;

    out << strComment << std::endl;

    out << myContainer << std::endl;
    
    w = out.str();
    //::OutputDebugString(w.c_str());
    TRACE(w.c_str());
}//end TraceItem
#else

template <class T> inline 
VOID SaveContainerToFile(T &myContainer, char *fname)
{
}//end SaveContainerToFile

// Save iterators in a file
template <class T> inline 
VOID SaveIteratorsToFile(T &myContainer, char *fname)
{
}

template <class T> inline 
VOID SaveContainerToFile(T &myContainer, const std::string &pathfname, const std::string &fname )
{
}//end SaveContainerToFile

// Save iterators in a file
template <class T> inline 
VOID SaveIteratorsToFile(T &myContainer, const std::string &pathfname, const std::string &fname )
{
}

//SaveItemToFile
template <class T> inline 
VOID SaveItemToFile(T &myContainer, const std::string &pathfname, const std::string &fname )
{
}

// trace the container in the debug window
template <class T> inline
VOID TraceContainer( T &myContainer, const std::string &strComment )
{
}//end TraceContainer

template <class T> inline
VOID TraceItem( T &myContainer, const std::string &strComment )
{
}//end TraceItem


#endif


}//end namespace Utility


#endif
