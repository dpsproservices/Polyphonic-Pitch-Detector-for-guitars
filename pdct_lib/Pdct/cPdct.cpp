/* 
 * File:   cPdct.cpp
 * Author: luciamarock
 * 
 * Created on 11 novembre 2016, 22.23
 */

#include "cPdct.h"

cPdct::cPdct() :
    m_resonator(),
    m_output(NULL)
{
//    init();
//    reset();
}

cPdct::~cPdct() 
{
    
}

cFloat cPdct::noteToFrequency(int note) 
{
    return pow(2.0, (note-69)/12.0)*440.0;
}

void cPdct::connectOutput(cPdctOutput* output) 
{
    m_output = output;
}

void cPdct::outputNoteOn(int resonator) 
{
    /* if already on, return */
    if(m_noteMap[resonator] == NOTE_ON_STATE){       
        return;
    }
    
    /* save note map state */
    m_noteMap[resonator] = NOTE_ON_STATE;
    
    /* notify output with note on detection */
    if(m_output != NULL){
        int note = resonator + FIRST_NOTE_NUMBER;
        int velocity = 64;
        m_output->onDetectNoteOn(note, velocity);
    }
    
    /* for debug...*/
    LOG_INFO("NOTE ON: %d", resonator + FIRST_NOTE_NUMBER);
}

void cPdct::outputNoteOff(int resonator) 
{
    /* if already off, return */
    if(m_noteMap[resonator] == NOTE_OFF_STATE){       
        return;
    }
    
    /* save note map state */
    m_noteMap[resonator] = NOTE_OFF_STATE;
    
    /* notify output with note off detection */
    if(m_output != NULL){
        int note = resonator + FIRST_NOTE_NUMBER;
        int velocity = 64;
        m_output->onDetectNoteOff(note, velocity);
    }
    
    /* for debug...*/
    LOG_INFO("NOTE OFF: %d", resonator + FIRST_NOTE_NUMBER);
}

bool cPdct::isOutputNoteOn(int resonator) 
{
    return (m_noteMap[resonator]==NOTE_ON_STATE);
}

void cPdct::init() 
{           
    LOG_INFO("Resonator SETUP:"); 
    
    /* setup complex resonator */
    for(int i=0; i<NUM_OF_RESONATOR; i++){
        /* calc note number and frequency of resonator */
        int note = i + FIRST_NOTE_NUMBER;
        cFloat frequency = noteToFrequency(note);
        
        /* Pitch detect use Constant-Q Time Frequency Analysys */
        /* The bandwidth is fixed to one semitone              */
        cFloat d_value  = pow(2.0, 1.0/(2.0*12.0));
        cFloat c_value  = (2.0 * d_value - 2) / (d_value + 1);
        cFloat omega  = 2.0 * M_PI * frequency;
        cFloat width  = 2.0 * M_PI * frequency * c_value; 
        cFloat r_omega = width/M_PI;
        
        /* calc resonator complex coefficient */
        cComplex a1 = cComplex::exp((-r_omega + cComplex::i * omega) / SAMPLE_RATE);
        cFloat r = exp(-r_omega/SAMPLE_RATE);
        cComplex b0 = (((1.0-r*r)/r)/sqrt(2));
        
        /* init complex resonator */
        m_resonator[i].setCoef_a1(a1);
        m_resonator[i].setCoef_b0(b0);
        
        /* print coefficient value to console */
        LOG_INFO("Resonator %2d [%d,%7.2f Hz]: r=%f, coef=(%f+j%f)",
                i, note, frequency, r, a1.re(), a1.im());
    }   
}

void cPdct::printCoef() 
{
    for(int i=0; i<NUM_OF_RESONATOR; i++){
        /* calc note number and frequency of resonator */
        int note = i + FIRST_NOTE_NUMBER;
        cFloat frequency = noteToFrequency(note);
        
        cComplex a1 = m_resonator[i].getCoef_a1();
//        cComplex b0 = m_resonator[i].getCoef_b0();

        /* print coefficient value to console */
        LOG_INFO("Resonator %2d [%d,%7.2f Hz]: coef=(%f+j%f)",
                i, note, frequency, a1.re(), a1.im());        
    }
}

void cPdct::reset() 
{
    /* reset complex resonator filter */
    for(int i=0; i<NUM_OF_RESONATOR; i++){
        m_resonator[i].reset();
    }
    /* reset energy of resonator */
    for(int i=0; i<NUM_OF_RESONATOR; i++){
        m_energy[i] = 0.0;
        m_wenergy[i] = 0.0;
    }
    /* reset note on map */
    for(int i=0; i<NUM_OF_RESONATOR; i++){
        m_noteMap[i] = 0; //off state
    }    
 
    /* reset timing */
    m_tick = 0;
    m_frame= 0;
    
    m_inputEnergy = 0.0;
}

void cPdct::process(cFloat* in, int frame, int channels) 
{
    cComplex output;
    for(int i=0; i<frame; i++) {
        /* get input signal */
        cFloat signal = *in;

        /* create complex input for resonator */
        cComplex input(signal);
        m_inputEnergy+=input.norm()/WINDOW_SIZE;
        
        /* filter input by resonator */
        for(int r=0; r<NUM_OF_RESONATOR; r++){
            cComplexResonator* resonator = &m_resonator[r];
            resonator->tick(&input,&output);
            m_energy[r]+=output.norm()/WINDOW_SIZE;
        }
        
        /* print frame energy frame */
        if(m_frame==WINDOW_SIZE){
            /* display energy of resonator */
            printEnergy();
            
            /* energy analisys */
            doEnergyAnalysis();           
            
            /* reset energy */
            for(int r=0; r<NUM_OF_RESONATOR; r++){
                m_wenergy[r] = m_energy[r];
                m_energy[r]=0;
            }
            m_inputEnergy=0;
            
            /* reset frame counter */
            m_frame = 0;            
        }
        
        /* increment counter */
        m_tick++;
        m_frame++;
        in+=channels;
    }
}

void cPdct::doEnergyAnalysis() 
{
    for(int r=0; r<NUM_OF_RESONATOR; r++){
        if(m_energy[r]>0.001){
            if(m_noteMap[r]==NOTE_OFF_STATE)
                outputNoteOn(r);
        }else{
            if(m_noteMap[r]==NOTE_ON_STATE)
                outputNoteOff(r);
        }
    }  
}

void cPdct::printEnergy() 
{
    LOG_INFO("TIME = %.3f sec", m_tick/SAMPLE_RATE);
    for(int resonator=0; resonator<NUM_OF_RESONATOR; resonator++){
        int note = resonator+FIRST_NOTE_NUMBER;
        LOG_INFO("RESONATOR[%2d](Note=%d, Freq=%7.2f Hz): E=%6.2f dB, I=%6.2f dB, Time=%.3f sec", 
                    resonator, note, noteToFrequency(note),
                    10*log10(m_energy[resonator]), 
                    10*log10(m_inputEnergy), 
                    m_tick/SAMPLE_RATE);
    }
}

cFloat cPdct::getResonatorEnergy(int resonator) 
{
    if(resonator<0)return 0.0;
    if(resonator>=NUM_OF_RESONATOR)return 0.0;
    
    return 10*log10(m_wenergy[resonator]);
}

int cPdct::getNoteMapState(int resonator) 
{
    if(resonator<0)return NOTE_OFF_STATE;
    if(resonator>=NUM_OF_RESONATOR)return NOTE_OFF_STATE;
    
    return m_noteMap[resonator];
}

cFloat cPdct::getCurrentTime() 
{
    return (((cFloat)m_tick)/SAMPLE_RATE);
}



