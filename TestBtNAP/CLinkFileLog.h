#pragma once
#include "FileLog.h"


#define LOG_EXPORTS


#ifdef LOG_EXPORTS
    #define LOG_EXT_API __declspec(dllexport)
#else
    #define LOG_EXT_API __declspec(dllimport)
#endif


extern "C" LOG_EXT_API void AppendLogEx(LogLevel, PTCHAR, ...);

