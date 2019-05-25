
/* 
 * File:   cPdctSettingsDialog.h
 * Author: xxac
 *
 * Created on 10 dicembre 2016, 16.17
 */

#ifndef CPDCTSETTINGSFRAME_H
#define CPDCTSETTINGSFRAME_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "cPdctSettings.h"

class cPdctSettingsDialog: public wxDialog  {
public:
    cPdctSettingsDialog( wxWindow * parent, wxWindowID id, const wxString& title);
    virtual ~cPdctSettingsDialog();
private:
    enum {
        wxID_SIMULATION_SPEED,
        wxID_SIMULATION_DBINP,
        wxID_SIMULATION_DBOUT,
        wxID_NOTE_NAME,
        wxID_RESET_SETTINGS
    };
    cPdctSettings* m_settings;
    wxSpinCtrlDouble* m_speedCtrl;
    wxSpinCtrlDouble* m_dbInCtrl;
    wxSpinCtrlDouble* m_dbOutCtrl;
    wxRadioBox* m_noteName;
private:
    void OnResetSettings(wxCommandEvent& event);
    void onSpeedChange(wxSpinDoubleEvent& event);
    void onInputChange(wxSpinDoubleEvent& event);
    void onOutputChange(wxSpinDoubleEvent& event);
    void OnRadioBoxNoteName(wxCommandEvent& event);
};

#endif /* CPDCTSETTINGSFRAME_H */

