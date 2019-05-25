
/* 
 * File:   cWavSource.cpp
 * Author: xxac
 * 
 * Created on 4 dicembre 2016, 18.26
 */

#include "cWavSource.h"
#include "log_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

cWavSource::cWavSource():
    m_filename(""),
    m_sndFile(NULL)
{
    
}


cWavSource::~cWavSource() 
{
    close();
}

void cWavSource::setFilename(cString filename) 
{
    m_filename = filename;
}


int cWavSource::open() 
{
    SNDFILE *sf;
    SF_INFO info;

    m_sndFile = sf = sf_open(m_filename.c_str(), SFM_READ, &info);
    
    /* check for error */
    if (m_sndFile == NULL) {
        LOG_ERRO("sf_open error");
        return -1;
    }
    
    /* success */
    m_samplerate = info.samplerate;
    m_channels = info.channels;
    return 0;
}

int cWavSource::close() 
{
    if(m_sndFile != NULL){
        int ret = sf_close((SNDFILE *)m_sndFile);
        m_sndFile = NULL;
        if(ret!=0){
            LOG_ERRO("sf_close error");
            return -1;
        }      
    }
    return 0;
}

int cWavSource::read(cFloat* buffer, int frame) 
{
    int read = 0;
    if(sizeof(cFloat)==sizeof(float)){
        read = sf_readf_float((SNDFILE *)m_sndFile, (float*)buffer, frame);
    }else{
        read = sf_readf_double((SNDFILE *)m_sndFile, (double*)buffer, frame);
    }
    return read;
}

int cWavSource::getNumOfChannel() 
{
    return m_channels;
}

