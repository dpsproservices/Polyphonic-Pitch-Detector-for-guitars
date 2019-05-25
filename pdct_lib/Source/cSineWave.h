/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cSineWave.h
 * Author: xxac
 *
 * Created on 26 novembre 2016, 18.26
 */

#ifndef CSINEWAVE_H
#define CSINEWAVE_H

#include "common_type.h"

class cSineWave {
public:
    cSineWave();
    cSineWave(int note, cFloat gain);
    cSineWave(const cSineWave& orig);
    virtual ~cSineWave();
private:
    cFloat m_phase;
    cFloat m_frequency;
    cFloat m_stepPhase;
    cFloat m_gain;
public:
    void setFrequencyHz(cFloat frequency){
        m_frequency = frequency;
        m_stepPhase = (2*M_PI*m_frequency/SAMPLE_RATE);
    }
    void setFrequencyNote(int note){
        m_frequency = pow(2.0, (note-69)/12.0)*440.0;
        m_stepPhase = (2*M_PI*m_frequency/SAMPLE_RATE);
    }
    void setGain(cFloat gain){
        m_gain = gain;
    }
public:
    void reset()
    {
        m_phase = 0.0;
    }
    void tick(cFloat* out)
    {
        *out = m_gain*sin(m_phase);
        m_phase+=m_stepPhase;
        if(m_phase>(2*M_PI))m_phase-=2*M_PI;
    }
};

#endif /* CSINEWAVE_H */

