// ExtractDialog.h

#ifndef EXTRACTDIALOG_H
#define EXTRACTDIALOG_H

#include "SevenZipCore/TString.h"

#include "WindowStateManager.h"

class ExtractDialog
    : public wxDialog
{
public:
    ExtractDialog(
        wxWindow *parent,
        wxWindowID id,
        const wxString &title,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER,
        const wxString&name = wxDialogNameStr);

    virtual ~ExtractDialog() {}

    void SetPath(const TString &tstrPath)
    {
        m_pComboBoxPath->SetValue(tstrPath);
    }

    TString GetPath() const
    {
        return m_pComboBoxPath->GetValue().ToStdWstring();
    }

    bool IsLaunchFolder() const { return m_pCheckBoxLaunchFolder->IsChecked(); }

private:
    WindowStateManager m_windowStateManager;

    wxComboBox *m_pComboBoxPath = nullptr;
    wxCheckBox *m_pCheckBoxLaunchFolder = nullptr;
    wxButton *m_pButtonOK = nullptr;

    TString m_tstrPath;

    void __Create();

    void __OnBrowseClick(wxCommandEvent &WXUNUSED(event));
    void __OnOKClick(wxCommandEvent &WXUNUSED(event));
    void __OnPathChange(wxCommandEvent &event);
};

#endif // EXTRACTDIALOG_H
