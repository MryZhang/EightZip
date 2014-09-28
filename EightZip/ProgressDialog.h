// ProgressDialog.h

#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <chrono>
#include <mutex>

#include "SevenZipCore/TString.h"

class ProgressDialog
    : public wxDialog
{
public:
    static const int PROGRESS_MAX = 1000;
    static const int UPDATE_INTERVAL = 100;

    ProgressDialog(
        wxWindow *parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER,
        const wxString& name = wxDialogNameStr);

    ~ProgressDialog() {}

    void SetArchivePath(const TString &tstrPath);
    void SetCurrentFile(const TString &tstrFileName);
    void SetTotal(UINT64 un64Total);
    void SetCompleted(UINT64 un64Completed);

private:
    std::mutex m_mutex;

    wxTimer m_timer;

    std::chrono::milliseconds m_msElasped;
    std::chrono::system_clock::time_point m_tpStart;

    TString m_tstrArchiveFileName;
    TString m_tstrArchivePath;
    TString m_tstrCurrentFile;
    UINT64 m_un64Total = 0;
    UINT64 m_un64Completed = 0;

    wxStaticText *m_pLabelElaspedTime = nullptr;
    wxStaticText *m_pLabelTimeLeft = nullptr;
    wxStaticText *m_pLabelArchivePath = nullptr;
    wxStaticText *m_pLabelCurrentFile = nullptr;
    wxStaticText *m_pLabelPercent = nullptr;

    wxGauge *m_pGaugeProcessed = nullptr;

    void __Create();
    void __StartTimer();
    void __Update(wxTimerEvent &WXUNUSED(event));
};

#endif // PROGRESSDIALOG_H
