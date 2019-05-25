
/* 
 * File:   cPdctSimul.h
 * Author: luciamarock
 *
 * Created on 5 novembre 2016, 16.22
 */

#ifndef CPDCTSIMUL_H
#define CPDCTSIMUL_H

#include "common_type.h"
#include "cAudioSource.h"
#include "cPdct.h"
#include "cPdctOutput.h"

class cPdctSimul {
public:
    cPdctSimul();
    virtual ~cPdctSimul();
private:
    cPdct m_pdct;
    cAudioSource* m_source;
    cFloat* m_buffer;
public:
    int play(int frame);
    int start();
    int stop();
    int pause();
    void setSource(cAudioSource* source);
    cFloat getResonatorEnergy(int resonator);
    cFloat getSimulationTime();
    int getNoteMap(int resonator);
    void connectOutput(cPdctOutput* output);
};

#endif /* CPDCTSIMUL_H */

