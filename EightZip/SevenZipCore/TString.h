// TString.h

#ifndef SEVENZIPCORE_TSTRING_H
#define SEVENZIPCORE_TSTRING_H

#include <locale>
#include <string>
#include <sstream>

#ifdef _UNICODE

typedef std::wstring TString;
typedef std::wstringstream TStringStream;

#define ToTUpper towupper
#define ToTLower towlower

#define ToTString std::to_wstring

#else

typedef std::string TString;
typedef std::stringstream TStringStream;

#define ToTUpper toupper
#define ToTLower tolower

#define ToTString std::to_string

#endif

template<typename T>
std::wstring ConvertTStringToWString(T &&value)
{
#ifdef _UNICODE
    return value;
#else
    return ConvertStringToWString(std::forward<T>(value));
#endif
}

template<typename T>
std::string ConvertTStringToString(T &&value)
{
#ifdef _UNICODE
    return ConvertWStringToString(std::forward<T>(value));
#else
    return value;
#endif
}

template<typename T>
std::wstring ConvertStringToTString(T &&value)
{
#ifdef _UNICODE
    return ConvertStringToWString(std::forward<T>(value));
#else
    return value;
#endif
}

template<typename T>
std::wstring ConvertWStringToTString(T &&value)
{
#ifdef _UNICODE
    return value;
#else
    return ConvertWStringToString(std::forward<T>(value));
#endif
}

class LocaleSwitcher
{
public:
    LocaleSwitcher(const char *locale)
        : m_strOldLocale(setlocale(LC_CTYPE, nullptr))
    {
        setlocale(LC_CTYPE, locale);
    }
    ~LocaleSwitcher()
    {
        setlocale(LC_CTYPE, m_strOldLocale.c_str());
    }

private:
    std::string m_strOldLocale;
};

#endif // SEVENZIPCORE_TSTRING_H
