
/* 
 * File:   cPdctSettings.h
 * Author: xxac
 *
 * Created on 11 dicembre 2016, 16.31
 */

#ifndef CPDCTSETTINGS_H
#define CPDCTSETTINGS_H


class cPdctSettings {
public:
    cPdctSettings();
    virtual ~cPdctSettings();
private:
    float m_simulationSpeed;
    int m_noteNameMode;
    float m_audioOutputVolumedB;
    float m_audioInputVolumedB;
public:
    void load();
    void save();
public:
    float getSimulationSpeed(){
        return m_simulationSpeed;
    }
    void setSimulationSpeed(float value){
        m_simulationSpeed = value;
    }
    enum {
        NOTE_NAME_CDE,
        NOTE_NAME_DOREMI
    };
    int getNoteNameMode(){
        return m_noteNameMode;
    } 
    void SetNoteNameMode(int mode){
        m_noteNameMode = mode;
    }
    float getAudioOutputVolumedB(){
        return m_audioOutputVolumedB;
    }
    void setAudioOutputVolumedB(float value){
        m_audioOutputVolumedB = value;
    }
    float getAudioInputVolumedB(){
        return m_audioInputVolumedB;
    }
    void setAudioInputVolumedB(float value){
        m_audioInputVolumedB = value;
    }
    void setDefault();
};

#endif /* CPDCTSETTINGS_H */

