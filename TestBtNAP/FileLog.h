#pragma once

enum LogLevel
{
    LOG_START = 0,
    LOG_STOP,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_ERROR_INFO
};

class CFileLog
{
public:
    CFileLog(void);
    virtual ~CFileLog(void);
    void SetLogFile(CString fileName) { m_lpszFileName = fileName; };
    BOOL OpenLog(void);
    void CloseLog(void);
    BOOL CreateNewInstance(void);
    void AppendLog(LogLevel, PTCHAR, ...);
    BOOL Init(CString);
    void Release(void);

protected:
    bool m_isOpen;
    CString m_lpszFileName;
    CStdioFile m_logFile;
};

extern CFileLog btLogger;
