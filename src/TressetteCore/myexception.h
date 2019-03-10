//myexception.h

#ifndef _MY_EXCEPTION_H__
#define _MY_EXCEPTION_H__

//! namespace Error
namespace Error
{
    enum
    {
        BUFDIM = 512
    };
    struct Init
    {
        STRING strErrMsg;
        //! constructor
        Init(LPCSTR lpsMsg){strErrMsg = lpsMsg;}
    };
    struct Generic
    {
        STRING strErrMsg;
        //! constructor
        Generic(LPCSTR lpsMsg){strErrMsg = lpsMsg;}
    };
};


#endif