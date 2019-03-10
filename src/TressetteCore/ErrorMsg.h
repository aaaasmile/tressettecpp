
// ErrorMsg.h

#ifndef ERROR_MSG__H_____
#define ERROR_MSG__H_____

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
