// stdafx.cpp : source file that includes just the standard includes
//	TestEngine.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "StdAfx.h"
#include "win_type_global.h"
#include <iostream>
#include <fstream>
#include "TraceService.h"
#include "InvidoInfoComm.h"

void TraceInLogFile(char* myBuff)
{
    TraceService* pTracer = TraceService::Instance();
    pTracer->AddSimpleTrace(TR_CORE_CH, myBuff);
}
