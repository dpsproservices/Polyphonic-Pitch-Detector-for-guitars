
/* 
 * File:   cBuffSource.cpp
 * Author: xxac
 * 
 * Created on 27 dicembre 2016, 10.05
 */

#include "cBuffSource.h"

cBuffSource::cBuffSource() :
    m_buffer(NULL),  
    m_frame(0),
    m_channel(0),
    m_volume(1.0)
{
    
}

cBuffSource::~cBuffSource() 
{
    
}

int cBuffSource::open() 
{
    return 0;
}

int cBuffSource::close() 
{
    return 0;
}

int cBuffSource::read(cFloat* buffer, int frame) 
{
    int counter = 0;
    while(m_frame>0 && frame>0){
        for(int i=0; i<m_channel; i++){
            *buffer++ = (*m_buffer++) * m_volume;
        }
        m_frame--;
        frame--;
        counter++;
    }
    return counter;
}

int cBuffSource::getNumOfChannel() 
{
    return m_channel;
}

void cBuffSource::putBuffer(cFloat* buff, int frame, int channel) 
{
    m_buffer = buff;
    m_frame = frame;
    m_channel = channel;
}

void cBuffSource::setVolume(cFloat volume) 
{
    m_volume = volume;
}

