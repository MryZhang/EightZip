// ProgressDialog.h

#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <mutex>

#include "SevenZipCore/TString.h"

class ProgressDialog
    : public wxDialog
{
public:
    ProgressDialog(
        wxWindow *parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE,
        const wxString& name = wxDialogNameStr);

    ~ProgressDialog() {}

    void SetArchivePath(const TString &tstrPath);
    void SetCurrentFile(const TString &tstrFileName);

private:
    std::mutex m_mutex;

    wxTimer m_timer;

    TString m_tstrArchivePath;
    TString m_tstrCurrentFile;

    wxStaticText *m_pLabelArchivePath = nullptr;
    wxStaticText *m_pLabelCurrentFile = nullptr;

    wxGauge *m_pGaugeCurrentFile = nullptr;
    wxGauge *m_pGaugeProcessed = nullptr;

    void __Create();
    void __StartTimer();
    void __Update(wxTimerEvent &WXUNUSED(event));
};

#endif // PROGRESSDIALOG_H
