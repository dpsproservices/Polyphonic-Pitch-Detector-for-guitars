
/* 
 * File:   cPdtcFrame.h
 * Author: xxac
 *
 * Created on 27 novembre 2016, 17.32
 */

#ifndef CPDTCFRAME_H
#define CPDTCFRAME_H

#include <wx/wx.h>
#include "cDisplayWidget.h"
#include "cPdctSimul.h"
#include "cAudioSource.h"
#include "cSineSource.h"
#include "cWavSource.h"
#include "cBuffSource.h"
#include "cPdctSettings.h"
#include "cJackdDriver.h"
#include "cPdctOutput.h"

class cPdtcFrame: public wxFrame, 
                  public cJackProcess, 
                  public cPdctOutput {
public:
    cPdtcFrame(const wxString& title);
    virtual ~cPdtcFrame();
private:
    wxMenuBar* m_menuBar;
    wxMenu* m_menuFile;
    wxMenu* m_menuEdit;
    wxMenu* m_menuSource;
    wxMenu* m_menuHelp;
    cDisplayWidget* m_display;
    enum {
        wxID_TEST,
        wxID_TIMER,
        wxID_SOURCE_SINE,
        wxID_SOURCE_FILE,
        wxID_SOURCE_AUDIO,
    };
    wxTimer* m_pTimer;
    wxString m_lastPath;
    cPdctSettings m_settings;
    
    void OnStartStopSimulation(wxCommandEvent& event);
    void OnTimerEvent(wxTimerEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSettings(wxCommandEvent& event);
    
    void OnSourceSine(wxCommandEvent& event);
    void OnSourceFile(wxCommandEvent& event);
    void OnSourceAudio(wxCommandEvent& event);
private:
    enum {
        MODE_SINE,
        MODE_FILE,
        MODE_AUDIO,
        
        MODE_NONE,
    };
    int m_mode;
    bool m_runSimulation;
    cSineSource m_sineSource;
    cWavSource m_waveSource;
    cBuffSource m_buffSource;
    cPdctSimul m_pdctSimul;
    cJackdDriver m_jackdDriver;
private:
    void setSimulationMode(int mode);
    void startSimulation();
    void stopSimulation();
private:
    virtual int process(cFloat* in, cFloat* out, int nframe, int nchannel);
private:
    virtual void onDetectNoteOn(int note, int velocity);
    virtual void onDetectNoteOff(int note, int velocity);
public:
    float getDisplayValue(int resonator);
    float getDisplayTime();
    int   getDisplayNoteState(int resonator);
    cPdctSettings* getSettings();
};

#endif /* CPDTCFRAME_H */

