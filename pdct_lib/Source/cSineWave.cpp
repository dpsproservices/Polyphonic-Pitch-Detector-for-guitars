/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cSineWave.cpp
 * Author: xxac
 * 
 * Created on 26 novembre 2016, 18.26
 */

#include "cSineWave.h"

cSineWave::cSineWave():
    m_phase(0.0),
    m_frequency(0.0),
    m_stepPhase(0.0),
    m_gain(1.0)
{
    
}

cSineWave::cSineWave(int note, cFloat gain):
    m_phase(0.0),
    m_frequency(0.0),
    m_stepPhase(0.0),
    m_gain(1.0) 
{
    setFrequencyNote(note);
    setGain(gain);
}


cSineWave::cSineWave(const cSineWave& orig):
    m_phase(orig.m_phase),
    m_frequency(orig.m_frequency),
    m_stepPhase(orig.m_stepPhase),
    m_gain(orig.m_gain)
{
    
}

cSineWave::~cSineWave() 
{
    
}

