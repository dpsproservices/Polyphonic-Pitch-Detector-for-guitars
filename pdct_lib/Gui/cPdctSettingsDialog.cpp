
/* 
 * File:   cPdctSettingsDialog.cpp
 * Author: xxac
 * 
 * Created on 10 dicembre 2016, 16.17
 */

#include "cPdctSettingsDialog.h"
#include "cPdtcFrame.h"
#include "wx/radiobox.h"

cPdctSettingsDialog::cPdctSettingsDialog( wxWindow * parent, wxWindowID id, const wxString& title) : 
    wxDialog(parent, id, title, wxDefaultPosition, wxSize(250, 290)) {
    cPdtcFrame *frame = (cPdtcFrame *) parent;
    m_settings = frame->getSettings();

    wxPanel *panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

    wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Simulation"), wxPoint(5, 5), wxSize(240, 125));
    wxStaticText* speed = new wxStaticText(panel, -1, wxT("Speed [x]:"), wxPoint(15, 35));
    m_speedCtrl = new wxSpinCtrlDouble(panel, wxID_SIMULATION_SPEED, wxT(""), wxPoint(110, 30));
    m_speedCtrl->SetDigits(1);
    m_speedCtrl->SetRange(0.1, 2.0);
    m_speedCtrl->SetValue(m_settings->getSimulationSpeed());
    m_speedCtrl->SetIncrement(0.1);
    UNUSED(st);
    UNUSED(speed);

    wxStaticText* dbIn = new wxStaticText(panel, -1, wxT("Input [dB]:"), wxPoint(15, 70));
    m_dbInCtrl = new wxSpinCtrlDouble(panel, wxID_SIMULATION_DBINP, wxT(""), wxPoint(110, 65));
    m_dbInCtrl->SetDigits(1);
    m_dbInCtrl->SetRange(-24, +24);
    m_dbInCtrl->SetValue(m_settings->getAudioInputVolumedB());
    m_dbInCtrl->SetIncrement(0.5);
    UNUSED(dbIn);

    wxStaticText* dbOut = new wxStaticText(panel, -1, wxT("Output [dB]:"), wxPoint(15, 105));
    m_dbOutCtrl = new wxSpinCtrlDouble(panel, wxID_SIMULATION_DBOUT, wxT(""), wxPoint(110, 100));
    m_dbOutCtrl->SetDigits(1);
    m_dbOutCtrl->SetRange(-96, +0);
    m_dbOutCtrl->SetValue(m_settings->getAudioOutputVolumedB());
    m_dbOutCtrl->SetIncrement(0.5);
    UNUSED(dbOut);

    wxPanel *panel2 = new wxPanel(this, -1);
    wxArrayString strings;
    strings.Add(wxT("&C, D, E, F, G, A, B"));
    strings.Add(wxT("&Do, Re, Mi, Fa, Sol, La, Si"));
    m_noteName = new wxRadioBox(panel2, wxID_NOTE_NAME, wxT("Note Name"),
            wxDefaultPosition, wxDefaultSize, strings, 1, wxRA_SPECIFY_COLS);
    m_noteName->SetSelection(m_settings->getNoteNameMode());

    wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
    wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxSize(70, 30));
    wxButton *resetButton = new wxButton(this, wxID_RESET_SETTINGS, wxT("Reset"), wxDefaultPosition, wxSize(70, 30));

    hbox->Add(okButton, 1);
    hbox->Add(closeButton, 1, wxLEFT, 5);
    hbox->Add(resetButton, 1, wxLEFT, 10);  

    vbox->Add(panel, 1);
    vbox->Add(panel2, 1, wxALL, 5);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    Connect(wxID_RESET_SETTINGS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cPdctSettingsDialog::OnResetSettings));
    Connect(wxID_SIMULATION_SPEED, wxEVT_SPINCTRLDOUBLE, wxSpinDoubleEventHandler(cPdctSettingsDialog::onSpeedChange));
    Connect(wxID_SIMULATION_DBINP, wxEVT_SPINCTRLDOUBLE, wxSpinDoubleEventHandler(cPdctSettingsDialog::onInputChange));
    Connect(wxID_SIMULATION_DBOUT, wxEVT_SPINCTRLDOUBLE, wxSpinDoubleEventHandler(cPdctSettingsDialog::onOutputChange));
    Connect(wxID_NOTE_NAME, wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(cPdctSettingsDialog::OnRadioBoxNoteName));

    SetSizer(vbox);

    Centre();
}


cPdctSettingsDialog::~cPdctSettingsDialog() 
{
    
}

void cPdctSettingsDialog::onSpeedChange(wxSpinDoubleEvent& event)
{
    m_settings->setSimulationSpeed(event.GetValue());
}

void cPdctSettingsDialog::onInputChange(wxSpinDoubleEvent& event)
{
    m_settings->setAudioInputVolumedB(event.GetValue());
}

void cPdctSettingsDialog::onOutputChange(wxSpinDoubleEvent& event) 
{
    m_settings->setAudioOutputVolumedB(event.GetValue());
}

void cPdctSettingsDialog::OnRadioBoxNoteName(wxCommandEvent& event) 
{
    m_settings->SetNoteNameMode(event.GetSelection());
}

void cPdctSettingsDialog::OnResetSettings(wxCommandEvent& /*event*/) 
{
    m_settings->setDefault(); 
    
    m_speedCtrl->SetValue(m_settings->getSimulationSpeed());
    m_dbInCtrl->SetValue(m_settings->getAudioInputVolumedB());
    m_dbOutCtrl->SetValue(m_settings->getAudioOutputVolumedB());
    m_noteName->SetSelection(m_settings->getNoteNameMode());
}


