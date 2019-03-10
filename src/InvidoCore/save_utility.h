

//save_utility.h

#ifndef _SAVE_UTILITY__H
#define _SAVE_UTILITY__H
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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
    TRACE("\n");
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
    TRACE("\n");
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