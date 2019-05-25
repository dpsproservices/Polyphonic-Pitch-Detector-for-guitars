
/* 
 * File:   cSineSource.cpp
 * Author: xxac
 * 
 * Created on 5 dicembre 2016, 18.14
 */

#include "cSineSource.h"

cSineSource::cSineSource() :
    m_frame(0),
    m_time(SAMPLE_RATE_INT)
{
    
}

cSineSource::~cSineSource() 
{
    
}

void cSineSource::addSineWave(cSineWave sine) 
{
    m_sineWave.push_back(sine);
}

void cSineSource::clearSineWave() 
{
    m_sineWave.clear();
}

int cSineSource::open() 
{
    m_frame = 0;
    
    int numOfSineWave = m_sineWave.size();
    for(int w=0; w<numOfSineWave; w++){
        m_sineWave[w].reset();
    }
    
    return 0;
}

int cSineSource::close() 
{
    return 0;
}

int cSineSource::read(cFloat* buffer, int frame) 
{
    /* run pitch detect process (1 second) */
    int numOfSineWave = m_sineWave.size();
    int read = 0;
    
    if(m_frame >= m_time){
        return read;
    }
    
    for(int i=0; i<frame; i++){
        cFloat signal = 0.0;
        for(int w=0; w<numOfSineWave; w++){
            cFloat sine;
            m_sineWave[w].tick(&sine);
            signal+=sine;           
        }
        
        *buffer++ = signal;
        read++;
        m_frame++;
        if(m_frame >= m_time){
            break;
        }
    }
    
    return read;
}

int cSineSource::getNumOfChannel() 
{
    return 1;
}


void cSineSource::setDuration(cFloat time) 
{
    m_time = time * SAMPLE_RATE;
}

