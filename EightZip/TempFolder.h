// TempFolder.h

#ifndef TEMPFOLDER_H
#define TEMPFOLDER_H

#include <boost/filesystem.hpp>

#include "SevenZipCore/TString.h"

using namespace std;

class TempFolder
{
public:
    TempFolder() {}
    ~TempFolder() {}

    void Create(TString tstrFileName = wxEmptyString);
    void Delete();

    const TString GetFileName() const
    {
        return ConvertWStringToTString(m_pathFile.filename().wstring());
    }
    const TString GetFilePath() const
    {
        return ConvertWStringToTString(m_pathFile.wstring());
    }
    void SetFileName(const TString &value);
    const TString GetFolderPath() const
    {
        return ConvertWStringToTString(m_pathFolder.wstring());
    }

private:
    boost::filesystem::path m_pathFile;
    boost::filesystem::path m_pathFolder;
};

#endif // TEMPFOLDER_H
