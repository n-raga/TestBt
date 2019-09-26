#include "StdAfx.h"
#include "FileLog.h"
#include "Shlwapi.h"

CFileLog btLogger;

CFileLog::CFileLog(void)
{
    m_isOpen = false;
}

CFileLog::~CFileLog(void)
{
}

BOOL CFileLog::OpenLog()
{
    if (_T("") == m_lpszFileName)
    {
        m_isOpen = false;
        return (FALSE);
    }

    if(!m_isOpen)
    {
        if ((FALSE) == m_logFile.Open(m_lpszFileName, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText))
        {
            m_isOpen = false;
            return (FALSE);
        }
    }

    m_isOpen = true;
    return (TRUE);
}

void CFileLog::CloseLog()
{
    if(!m_isOpen)
        return;

    m_logFile.Flush();
    m_logFile.Close();
    m_isOpen = false;
}

BOOL CFileLog::CreateNewInstance()
{
    if ((TRUE) == OpenLog())
    {
        m_logFile.SetLength(0);
        CloseLog();
        return (TRUE);
    }
    return (FALSE);
}

BOOL CFileLog::Init(CString lpszFileName)
{
    m_lpszFileName = lpszFileName;

    BOOL result = (TRUE);

    CFileStatus rStatus;
    // Verifica esistenza del file di log
    if (0 == CFile::GetStatus(lpszFileName, rStatus))
    {
        // Il file non esiste: creazione del file di log
        result &= CreateNewInstance();
        result &= CFile::GetStatus(lpszFileName, rStatus);
    }

    // Verifica dimensione del file
    if (rStatus.m_size > 1048576)
    {
        CTime time = CTime::GetCurrentTime();
        CString lpszFileNameWithoutExtension(lpszFileName);
        PathRemoveExtension(lpszFileNameWithoutExtension.GetBuffer());
        lpszFileNameWithoutExtension.ReleaseBuffer();
        CString lpszFileExtension = PathFindExtension(lpszFileName);
        CString lpszNewFileName;
        lpszNewFileName.Format(_T("%s_%04d%02d%02d_%02d%02d%02d%s"), lpszFileNameWithoutExtension,
            time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(),
            lpszFileExtension);
        result &= CopyFile(lpszFileName, lpszNewFileName, FALSE);
        result &= CreateNewInstance();
    }

    btLogger.AppendLog(LOG_START, _T(">>>"));

    return result;
}

void CFileLog::Release()
{
    AppendLog(LOG_STOP, _T("<<<"));
    CloseLog();
}

void CFileLog::AppendLog(LogLevel log_type, PTCHAR lpszFormat, ...)
{
    //// limit the file size to 500KB
    //const DWORD dwFileSize  = 500 * 1024;

    try
    {
        if ((FALSE) == OpenLog())
            return;

        //// check if the file size is greater than limit file size
        //if (logFile.GetLength() > dwFileSize)
        //{
        //// remove all content in the file by reset it size to zero
        //logFile.SetLength(0);
        //}
        m_logFile.SeekToEnd();
        va_list args;
        va_start(args, lpszFormat);
        TCHAR szMsgBuffer[4096] = { 0 };
        _vsntprintf(szMsgBuffer, (sizeof(szMsgBuffer) / sizeof(TCHAR)), lpszFormat, args);
        va_end(args);

        CTime time = CTime::GetCurrentTime();
        CString szLogType = _T("");
        switch(log_type)
        {
            case LOG_START:
                szLogType = _T("Start");
                break;

            case LOG_ERROR:
                szLogType = _T("Error");
                break;

            case LOG_WARNING:
                szLogType = _T("Warning");
                break;

            case LOG_INFO:
                szLogType = _T("Info");
                break;

            case LOG_DEBUG:
                szLogType = _T("Debug");
                break;

            case LOG_ERROR_INFO:
                szLogType = _T("Error Info");
                break;

            case LOG_STOP:
                szLogType = _T("Stop");
                break;

            default:
                break;
        }

        TCHAR szBuffer[9216] = { 0 };
        _sntprintf(szBuffer, (sizeof(szBuffer) / sizeof(TCHAR)), _T("%04d-%02d-%02d %02d:%02d:%02d|%s|%s"),
            time.GetYear(), time.GetMonth(), time.GetDay(),
            time.GetHour(), time.GetMinute(), time.GetSecond(),
            szLogType.MakeUpper(),
            szMsgBuffer);

        m_logFile.WriteString(szBuffer);
        m_logFile.WriteString(_T("\n"));

        CloseLog();
    }
    catch(...)
    {
    }
}
