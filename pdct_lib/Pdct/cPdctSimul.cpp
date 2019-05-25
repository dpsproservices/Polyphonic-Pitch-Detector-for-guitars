/* 
 * File:   cPdctSimul.cpp
 * Author: luciamarock
 * 
 * Created on 5 novembre 2016, 16.22
 */

#include "cPdctSimul.h"

cPdctSimul::cPdctSimul() :
    m_source(NULL)
{
    m_buffer = new cFloat[SAMPLE_RATE_INT];
}


cPdctSimul::~cPdctSimul() 
{
    if(m_buffer!=NULL){
        delete [] m_buffer;
        m_buffer = NULL;
    }
    if(m_source!=NULL){
        m_source->close();
        m_source = NULL;
    }
}

void cPdctSimul::setSource(cAudioSource* source) 
{
    if(m_source!=NULL){
        m_source->close();
    }
    m_source = source;
    if(m_source!=NULL){
        m_source->open();
        m_pdct.init();
        m_pdct.reset();
    } 
}

int cPdctSimul::start() 
{
    if(m_source!=NULL){
        m_source->close();
    }
    if(m_source!=NULL){
        m_source->open();
        m_pdct.init();
        m_pdct.reset();
    } 
    
    return 0;
}


int cPdctSimul::stop() 
{
    return 0;
}

int cPdctSimul::pause() 
{
    return 0;
}

int cPdctSimul::play(int frame) 
{
    if(m_source==NULL) return 0;
    
    LOG_INFO("Resonator Run:");
    
    /* get signal from source */
    int read = m_source->read(m_buffer,frame);
       
    /* run pitch detect process */
    m_pdct.process(m_buffer, read, m_source->getNumOfChannel());
    
    return read;
}

cFloat cPdctSimul::getResonatorEnergy(int resonator)
{
    return m_pdct.getResonatorEnergy(resonator);
}

cFloat cPdctSimul::getSimulationTime() 
{
    return m_pdct.getCurrentTime();
}

void cPdctSimul::connectOutput(cPdctOutput* output) 
{
    m_pdct.connectOutput(output);
}

int cPdctSimul::getNoteMap(int resonator) 
{
    return m_pdct.getNoteMapState(resonator);
}

