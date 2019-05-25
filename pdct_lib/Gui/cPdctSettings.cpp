
/* 
 * File:   cPdctSettings.cpp
 * Author: xxac
 * 
 * Created on 11 dicembre 2016, 16.31
 */

#include "cPdctSettings.h"
#include <wx/wx.h>
#include <wx/config.h>

cPdctSettings::cPdctSettings() :
    m_simulationSpeed(1.0),
    m_noteNameMode(0),
    m_audioOutputVolumedB(-30.0),
    m_audioInputVolumedB(0.0)
{
   
}

cPdctSettings::~cPdctSettings() 
{
    
}

void cPdctSettings::setDefault() 
{
    m_simulationSpeed = 1.0;
    m_noteNameMode = 0;
    m_audioOutputVolumedB = -30.0;
    m_audioInputVolumedB = 0.0;
}

void cPdctSettings::load() 
{
    wxConfig *config = new wxConfig("PdctApp");
    
    config->Read(wxT("/Simulation/Speed"), &m_simulationSpeed, 1.0);
    config->Read(wxT("/Display/NoteName"), &m_noteNameMode, 0);
    config->Read(wxT("/Audio/OuputVolumedB"), &m_audioOutputVolumedB, -30.0);
    config->Read(wxT("/Audio/InputVolumedB"), &m_audioInputVolumedB, 0.0);
    
    delete config;
}

void cPdctSettings::save() 
{
    wxConfig *config = new wxConfig("PdctApp");
    
    config->Write(wxT("/Simulation/Speed"), m_simulationSpeed);
    config->Write(wxT("/Display/NoteName"), m_noteNameMode);
    config->Write(wxT("/Audio/OuputVolumedB"), m_audioOutputVolumedB);
    config->Write(wxT("/Audio/InputVolumedB"), m_audioInputVolumedB);
    
    delete config;
}

