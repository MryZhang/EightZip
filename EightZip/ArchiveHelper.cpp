#include "stdwx.h"
#include "ArchiveHelper.h"

#include <thread>

#include "SevenZipCore/CommonHelper.h"
#include "SevenZipCore/Exception.h"

#include "ExtractIndicator.h"
#include "FileHelper.h"
#include "ProgressDialog.h"

using namespace std;

namespace Helper
{
    static void ExtractThread(TString tstrPath,
        shared_ptr<ArchiveModel> spModel,
        shared_ptr<ProgressDialog> spProgressDialog)
    {
        wxTheApp->CallAfter([spProgressDialog](){
            spProgressDialog->CenterOnParent();
            spProgressDialog->ShowModal();
        });
        ExtractIndicator extractIndicator(spProgressDialog);

        try
        {
            spModel->Extract(tstrPath, &extractIndicator);
        }
        catch (const SevenZipCore::ArchiveException &)
        {
        }
        wxTheApp->CallAfter([spProgressDialog](){
            spProgressDialog->Close();
        });
    }

    bool Extract(TString tstrPath, shared_ptr<ArchiveModel> spModel)
    {
        try
        {
            if (!spModel)
            {
                return false;
            }
            shared_ptr<IModel> spCurrentModel = spModel;
            while (spCurrentModel->IsArchive())
            {
                spCurrentModel = spCurrentModel->GetParent();
            }
            assert(spCurrentModel);
            auto tstrAbsPath = spCurrentModel->GetPath();
            auto path = boost::filesystem::absolute(tstrPath, tstrAbsPath);
            boost::filesystem::create_directories(path);

            auto tstrArchivePath = spModel->GetArchive()->GetPath();
            auto spProgressDialog = make_shared<ProgressDialog>(
                wxTheApp->GetTopWindow(), wxID_ANY,
                wxString::Format(_("Extracting from %s"),
                SevenZipCore::Helper::GetFileName(
                tstrArchivePath)));
            spProgressDialog->SetArchivePath(tstrArchivePath);

            thread extractThread(ExtractThread,
                Helper::GetCanonicalPath(path.wstring()), spModel,
                spProgressDialog);
            extractThread.detach();
        }
        catch (const boost::system::system_error &)
        {
            return false;
        }
        return true;
    }
}
