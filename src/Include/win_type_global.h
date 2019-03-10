
//win_type_global.h


#ifndef _AIGLOBAL_TYPE_H
#define _AIGLOBAL_TYPE_H

#if _MSC_VER > 1000
    #include <StdAfx.h>
#endif

#ifdef USEDIALOGTRACE
    #include <iostream>
#endif

#if _MSC_VER > 1000
    #pragma warning(disable:4786)
	#pragma warning(disable:4996)
    #include <vector> 
    #include <deque>
    #include <windows.h>
    #include <string>
#else
    #include <deque>
    #include <string>
#endif

#ifndef BOOL 
    typedef int BOOL;
#endif

#ifndef BYTE
    typedef unsigned char BYTE;
#endif

#ifndef TRUE 
    #define TRUE 1==1
#endif

#ifndef FALSE 
    #define FALSE 0==1
#endif

#ifndef CHAR 
    #define CHAR char
#endif

#ifndef STRING 
	typedef std::string STRING;
#endif

#ifndef ASSERT
    #include <assert.h>
    #define ASSERT(f) \
	assert(f);
#endif

#ifndef LPCSTR
    typedef CONST CHAR *LPCSTR, *PCSTR;
#endif

#ifndef LP_FNTHREAD
    //! function pointer for thread proxy casting
    typedef int (*LP_FNTHREAD)(void*);
#endif

#ifndef TRACE
    #include <stdio.h>
    extern void TraceInLogFile(char* myBuff);
    #ifdef WIN32
        
        inline void TRACE(const char* fmt, ...)
        {
            char myBuff[512];
            va_list args;

            va_start( args, fmt );     /* Initialize variable arguments. */

            int result = vsprintf(myBuff, fmt, args); 
        #ifdef USEDIALOGTRACE
            std::cout << "[TR] " <<myBuff;
        #else
            ::OutputDebugString(myBuff);
            TraceInLogFile(myBuff);
        #endif
        }
    #else
        // non windows
	    inline void TRACE(const char* fmt, ...)
        {
     	    // todo: implement trace for anjuta
        }
    #endif
#endif


//random value between [0,x)
#define CASO(x) (x * rand()) / RAND_MAX

typedef std::vector<STRING> VCT_STRING;

#endif