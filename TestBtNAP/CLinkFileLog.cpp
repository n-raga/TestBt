#include "StdAfx.h"
#include "CLinkFileLog.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AppendLogEx
//-------------------------------------------------------------------------
void AppendLogEx(LogLevel log_type, PTCHAR lpszFormat, ...)
{
    va_list args;
    va_start(args, lpszFormat);
    TCHAR szBuffer[4096] = { 0 };
    _vsntprintf(szBuffer, (sizeof(szBuffer) / sizeof(TCHAR)), lpszFormat, args);
    va_end(args);
    btLogger.AppendLog(log_type, szBuffer);
}
