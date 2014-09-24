#include "stdwx.h"
#include "FileInfo.h"

#include "FileHelper.h"

using namespace std;

std::map<TString, TString> FileInfo::m_mTypeCache;

FileInfo::FileInfo(TString tstrPath)
    : m_tstrPath(move(tstrPath))
{
#ifdef __WXMSW__
    m_isOK = (FALSE != ::GetFileAttributesEx(
        m_tstrPath.c_str(), GetFileExInfoStandard, &m_fileAttributeData));
#endif
}

TString FileInfo::GetCanonicalPath() const
{
    if (!IsOK())
    {
        return wxEmptyString;
    }
    if (m_tstrCanonicalPath.empty())
    {
        m_tstrCanonicalPath = Helper::GetCanonicalPath(m_tstrPath);
    }
    return m_tstrCanonicalPath;
}

TString FileInfo::GetType(
    TString tstrFileName,
    bool isDirectory /*= false*/,
    bool isVirtual /*= true*/)
{
#ifdef __WXMSW__
    TString tstrFakeName;
    if (isVirtual)
    {
        if (isDirectory)
        {
            tstrFakeName = wxT("fakedir");
        }
        else
        {
            auto szPointPosition = tstrFileName.rfind(wxFILE_SEP_EXT);
            tstrFakeName = TString(wxT("fake."))
                + tstrFileName.substr(szPointPosition + 1);
        }
        auto iter = m_mTypeCache.find(tstrFakeName);
        if (iter != m_mTypeCache.end())
        {
            return iter->second;
        }
    }

    SHFILEINFO info;
    if (SUCCEEDED(SHGetFileInfo(tstrFileName.c_str(),
        isDirectory ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL,
        &info,
        sizeof(SHFILEINFO),
        SHGFI_TYPENAME | (isVirtual ? SHGFI_USEFILEATTRIBUTES : 0))))
    {
        TString result(info.szTypeName);
        if (isVirtual)
        {
            m_mTypeCache[tstrFakeName] = result;
        }
        return result;
    }
#endif
    return wxEmptyString;
}

int FileInfo::GetIconIndex(
    TString tstrFileName,
    bool isDirectory /*= false*/,
    bool isVirtual /*= true*/)
{
#ifdef __WXMSW__
    SHFILEINFO info;
    if (SUCCEEDED(SHGetFileInfo(tstrFileName.c_str(),
        isDirectory ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL,
        &info,
        sizeof(SHFILEINFO),
        SHGFI_SMALLICON | SHGFI_SYSICONINDEX | (
        isVirtual ? SHGFI_USEFILEATTRIBUTES : 0))))
    {
        return info.iIcon;
    }
#endif
    return -1;
}

#ifdef __WXMSW__
wxDateTime GetTimeFromFileTime(_In_ CONST FILETIME *lpFileTime)
{
    SYSTEMTIME systemTime;
    FileTimeToSystemTime(lpFileTime, &systemTime);
    return wxDateTime(systemTime);
}
#endif