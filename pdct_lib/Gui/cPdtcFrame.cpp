
/* 
 * File:   cPdtcFrame.cpp
 * Author: xxac
 * 
 * Created on 27 novembre 2016, 17.32
 */

#include "cPdtcFrame.h"
#include "cPdctSettingsDialog.h"
#include <wx/filename.h>


#define TIMER_TIME_MS 100.0
#define X_RUN         0.5

cPdtcFrame::cPdtcFrame(const wxString& title): 
    wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 660)) 
{
    m_mode = MODE_NONE;
    
    /* load settings */
    m_settings.load();
    
    /* create menu bar */
    m_menuBar = new wxMenuBar;

    /* crete "File" menu */
    m_menuFile = new wxMenu;
    m_menuFile->Append(wxID_EXIT, wxT("&Quit"));
    m_menuBar->Append(m_menuFile, wxT("&File"));
    
    /* create "Edit" menu */
    m_menuEdit = new wxMenu;
    m_menuEdit->Append(wxID_PROPERTIES, wxT("&Settings"));
    m_menuBar->Append(m_menuEdit, wxT("&Edit"));  
    
    /* create "Source" menu */
    m_menuSource = new wxMenu;
    m_menuSource->Append(wxID_SOURCE_SINE, wxT("&Sine")); 
    m_menuSource->Append(wxID_SOURCE_FILE, wxT("&File"));
    m_menuSource->Append(wxID_SOURCE_AUDIO, wxT("&Audio"));
    m_menuBar->Append(m_menuSource, wxT("&Source"));

    /* create "Help" menu */
    m_menuHelp = new wxMenu;
    m_menuHelp->Append(wxID_ABOUT, wxT("&About"));
    m_menuBar->Append(m_menuHelp, wxT("&Help"));
    
    /* set menu to the current frame */
    SetMenuBar(m_menuBar);
    
    /* add dsisplay */
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    m_display = new cDisplayWidget(panel, wxID_ANY, wxDefaultPosition, wxSize(300, 600));
    hbox->Add(m_display, 1, wxEXPAND);
    vbox->Add(hbox, 0, wxEXPAND);
    panel->SetSizer(vbox);
    
    /* add start/stop button */
    wxButton *button = new wxButton(panel, wxID_TEST, wxT("Start/Stop Simulation"), wxPoint(20, 20));
    vbox->Add(button, 0, wxEXPAND);
    Connect(wxID_TEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cPdtcFrame::OnStartStopSimulation));
    button->SetFocus();

    /* signal connect */
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cPdtcFrame::OnQuit));
    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cPdtcFrame::OnAbout));
    Connect(wxID_PROPERTIES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cPdtcFrame::OnSettings));

    
    Connect(wxID_SOURCE_SINE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cPdtcFrame::OnSourceSine));
    Connect(wxID_SOURCE_FILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cPdtcFrame::OnSourceFile));
    Connect(wxID_SOURCE_AUDIO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cPdtcFrame::OnSourceAudio));
    
    
    m_pTimer = new wxTimer(this,wxID_TIMER);
    Connect(wxID_TIMER, wxEVT_TIMER, wxTimerEventHandler(cPdtcFrame::OnTimerEvent));
    
    Centre();  
    
    m_runSimulation = false;
    
    /* setup sine source */
    m_sineSource.setDuration(3.0);
    m_sineSource.clearSineWave();
    m_sineSource.addSineWave(cSineWave(40,0.5));
    m_sineSource.addSineWave(cSineWave(53,0.5));
    m_sineSource.addSineWave(cSineWave(69,0.5));
    m_sineSource.addSineWave(cSineWave(81,0.5));    
    setSimulationMode(MODE_SINE);
    
    m_jackdDriver.attachProcess(this);
    m_jackdDriver.open("PdctApp");
}


cPdtcFrame::~cPdtcFrame() 
{
    /* save settings */
    m_settings.save();
}

void cPdtcFrame::OnQuit(wxCommandEvent& /*event*/) 
{
    Close(true);
}

float cPdtcFrame::getDisplayValue(int resonator) 
{
    return 0.0 - m_pdctSimul.getResonatorEnergy(resonator);
}

float cPdtcFrame::getDisplayTime() 
{
    return m_pdctSimul.getSimulationTime();
}

int cPdtcFrame::getDisplayNoteState(int resonator) 
{
    return m_pdctSimul.getNoteMap(resonator);
}

cPdctSettings* cPdtcFrame::getSettings() 
{
    return &m_settings;
}

void cPdtcFrame::setSimulationMode(int mode) 
{
    if(m_mode == mode) return;
    m_mode = mode;
    
    switch(m_mode){
        case MODE_SINE:
            m_pdctSimul.setSource(&m_sineSource);
            break;
        case MODE_FILE:
            m_pdctSimul.setSource(&m_waveSource);
            break;
        case MODE_AUDIO:
            m_pdctSimul.setSource(&m_buffSource);
            break;               
    }
    
    m_pdctSimul.connectOutput(this);
}

void cPdtcFrame::startSimulation() 
{
    m_pdctSimul.start();
    
//    if(m_mode == MODE_FILE  ||  m_mode == MODE_SINE){
        m_pTimer->Stop();
        m_pTimer->Start(TIMER_TIME_MS);
//    }

    m_runSimulation = true;
}

void cPdtcFrame::stopSimulation() 
{
    m_pdctSimul.stop();
    m_pTimer->Stop();
    
    m_runSimulation = false;
}


void cPdtcFrame::OnStartStopSimulation(wxCommandEvent& /*event*/) 
{  
    if(m_runSimulation==false){
        startSimulation();
    }else{
        stopSimulation();
    }
}

void cPdtcFrame::OnTimerEvent(wxTimerEvent& /*event*/) 
{
    if(m_mode == MODE_FILE  ||  m_mode == MODE_SINE){
        int frame = m_settings.getSimulationSpeed()*TIMER_TIME_MS*SAMPLE_RATE/1000.0;
        int read = m_pdctSimul.play(frame);
        
        m_display->Refresh();

        if(read == 0){
           stopSimulation(); 
        }
    }else{
        m_display->Refresh();
    }
}

void cPdtcFrame::OnAbout(wxCommandEvent& /*event*/) 
{
    wxMessageBox( wxT("Pitch Dectect App.\nVersion 0.02.\nWith Audio Input Support.") );
}

void cPdtcFrame::OnSettings(wxCommandEvent& /*event*/) 
{     
    cPdctSettingsDialog settingsDialog (this,-1,"Settings");
    if ( settingsDialog.ShowModal() == wxID_OK ){
//        wxMessageBox( wxT("OK!!!!!!") );
    } else {
//        wxMessageBox( wxT("Cancel!!!!!!") );
    }
}

void cPdtcFrame::OnSourceSine(wxCommandEvent& /*event*/) 
{
    stopSimulation();
    setSimulationMode(MODE_SINE);
    startSimulation();
}

void cPdtcFrame::OnSourceFile(wxCommandEvent& /*event*/) 
{
//    setSimulationMode(MODE_FILE);
    wxFileDialog* OpenDialog = new wxFileDialog(
            this, _("Choose a wave file to open"), m_lastPath, wxEmptyString, 
            _("Wav files (*.wav)|*.wav"), wxFD_OPEN, wxDefaultPosition);

    if (OpenDialog->ShowModal() == wxID_OK)
    {
            wxString pathname = OpenDialog->GetPath();           
            wxFileName name = pathname;
            m_lastPath = name.GetPath();
            
            m_waveSource.setFilename(cString(pathname.mb_str()));
            
            stopSimulation();
            setSimulationMode(MODE_FILE);
            startSimulation();
    }

    OpenDialog->Destroy();
}

void cPdtcFrame::OnSourceAudio(wxCommandEvent& /*event*/) 
{
    stopSimulation();
    setSimulationMode(MODE_AUDIO);
    startSimulation();
}

int cPdtcFrame::process(cFloat* in, cFloat* out, int nframe, int nchannel) 
{
    if(m_mode == MODE_AUDIO){
        m_buffSource.putBuffer(in, nframe, nchannel);
        m_buffSource.setVolume(pow(10,m_settings.getAudioInputVolumedB()/20.0));
        m_pdctSimul.play(nframe);
    }
 
    /* thru copy (volume adjust) */
    cFloat volume = pow(10,m_settings.getAudioOutputVolumedB()/20.0);
    for(int frame=0; frame<nframe; frame++){
        for(int channel=0; channel<nchannel; channel++){
            *out++ = volume*(*in++);
        }
    }
    
    return nframe;
}

void cPdtcFrame::onDetectNoteOn(int note, int velocity) 
{
    LOG_INFO("onDetectNoteOn: %d, %d",note,velocity);
}

void cPdtcFrame::onDetectNoteOff(int note, int velocity) 
{
    LOG_INFO("onDetectNoteOff: %d, %d",note,velocity);
}

