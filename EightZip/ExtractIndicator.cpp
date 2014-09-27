#include "stdwx.h"
#include "ExtractIndicator.h"

#include <functional>

#include "SevenZipCore/CommonHelper.h"

#include "ProgressDialog.h"

using namespace std;

ExtractIndicator::ExtractIndicator(shared_ptr<ProgressDialog> spProgressDialog)
    : m_spProcessDialog(spProgressDialog)
{
}

void ExtractIndicator::SetTotal(UINT64 un64Total)
{
    m_un64Total = un64Total;
    m_spProcessDialog->SetCurrentPercent(0);
}

void ExtractIndicator::SetCompleted(boost::optional<UINT64> oun64Value)
{
    m_spProcessDialog->SetCurrentPercent(oun64Value && m_un64Total
        ? static_cast<double>(*oun64Value) / m_un64Total * m_spProcessDialog->PROGRESS_MAX
        : 0);
}

SevenZipCore::OverwriteAnswer ExtractIndicator::AskOverwrite(
    TString tstrExistPath,
    boost::optional<FILETIME> oftExistModified,
    boost::optional<UINT64> un64ExistSize,
    TString tstrNewPath,
    boost::optional<FILETIME> oftNewModified,
    boost::optional<UINT64> un64NewSize)
{
    return SevenZipCore::OverwriteAnswer::Yes;
}

void ExtractIndicator::AddError(TString tstrMessage)
{
    //wxMessageBox(wxString::Format("AddError: %s", tstrMessage));
}

void ExtractIndicator::AddError(TString tstrMessage, TString tstrParameter)
{
    //wxMessageBox(wxString::Format("AddError: %s %s", tstrMessage, tstrParameter));
}

void ExtractIndicator::Prepare(TString tstrPath,
    bool isFolder,
    SevenZipCore::ExtractAskMode askMode,
    boost::optional<UINT64> oun64Position)
{
    m_spProcessDialog->SetCurrentFile(
        SevenZipCore::Helper::GetFileName(tstrPath));
}

void ExtractIndicator::SetOperationResult(
    SevenZipCore::ExtractResult extractResult)
{
    //wxMessageBox(wxString::Format("SetOperationResult: %d", extractResult));
}