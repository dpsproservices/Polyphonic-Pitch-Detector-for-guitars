
/* 
 * File:   cPdct.h
 * Author: luciamarock
 *
 * Created on 11 novembre 2016, 22.23
 */

#ifndef CPDCT_H
#define CPDCT_H

#include "cComplex.h"
#include "cComplexResonator.h"
#include "cPdctOutput.h"

/* pitch detect configuration define */
#define FIRST_GUITAR_NOTE  40  //  82.407 Hz
#define LAST_GUITAR_NOTE   88  //1318.510 Hz
#define FIRST_NOTE_NUMBER  (FIRST_GUITAR_NOTE-1)
#define LAST_NOTE_NUMBER   (LAST_GUITAR_NOTE +1)
#define NUM_OF_RESONATOR   (LAST_NOTE_NUMBER - FIRST_NOTE_NUMBER + 1)
#define WINDOW_SIZE        960 //20 ms 
#define NOTE_ON_STATE      1
#define NOTE_OFF_STATE     0


class cPdct {
public:
    cPdct();
    virtual ~cPdct();
private:
    cComplexResonator m_resonator[NUM_OF_RESONATOR];
    cFloat m_energy[NUM_OF_RESONATOR];
    cFloat m_wenergy[NUM_OF_RESONATOR];
    char m_noteMap[NUM_OF_RESONATOR];
    cFloat m_inputEnergy;
    long int m_tick;
    int m_frame;
    cPdctOutput* m_output;
private:
    cFloat noteToFrequency(int note);
    void outputNoteOn(int resonator);
    void outputNoteOff(int resonator);
    bool isOutputNoteOn(int resonator);
public:
    void init();
    void reset();
    void process(cFloat* in, int frame, int channels);
    void printEnergy();
    void printCoef();
    void doEnergyAnalysis();
    void connectOutput(cPdctOutput* output);
public:
    cFloat getResonatorEnergy(int resonator);
    int getNoteMapState(int resonator);
    cFloat getCurrentTime();
};

#endif /* CPDCT_H */

