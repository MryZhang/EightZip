// Archive.h

#ifndef SEVENZIPCORE_ARCHIVE_H
#define SEVENZIPCORE_ARCHIVE_H

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include "Platform.h"
#include "TString.h"

namespace SevenZipCore
{
    class ArchiveEntry;
    class ArchiveFolder;
    class Codecs;
    struct IArchiveOpenCallback;
    struct IInStream;

    // CArchiveLink
    class Archive
        : public std::enable_shared_from_this<Archive>
    {
    public:
        Archive(std::shared_ptr<Codecs> cpCodecs);
        virtual ~Archive();

        void Open(
            TString tstrPath,
            std::shared_ptr<IArchiveOpenCallback> cpCallback);
        void Open(
            TString tstrPath,
            std::shared_ptr<IInStream> cpStream,
            std::shared_ptr<IArchiveOpenCallback> cpCallback);
        void Close();

        TString GetPath() const { return m_tstrPath; }
        std::shared_ptr<ArchiveFolder> GetRootFolder() const
        {
            return m_spRootFolder;
        }

        std::shared_ptr<ArchiveEntry> GetArchiveEntry() const;

        const boost::optional<FILETIME> &GetModifiedTime() const
        {
            return m_oftModified;
        }

    private:
        std::shared_ptr<Codecs> m_cpCodecs;

        TString m_tstrPath;

        std::vector<std::shared_ptr<ArchiveEntry>> m_vspArchiveEntry;
        std::shared_ptr<ArchiveFolder> m_spRootFolder;
        boost::optional<FILETIME> m_oftModified;

    };
}

#endif // SEVENZIPCORE_ARCHIVE_H