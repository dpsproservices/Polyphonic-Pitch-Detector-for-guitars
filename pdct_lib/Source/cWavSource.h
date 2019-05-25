
/* 
 * File:   cWavSource.h
 * Author: xxac
 *
 * Created on 4 dicembre 2016, 18.26
 */

#ifndef CWAVSOURCE_H
#define CWAVSOURCE_H

#include "cAudioSource.h"

class cWavSource: public cAudioSource {
public:
    cWavSource();
    virtual ~cWavSource();
private:
    cString m_filename;
    void* m_sndFile;
    int m_samplerate;
    int m_channels;
public:
    void setFilename(cString filename);
    virtual int open();
    virtual int close();
    virtual int read(cFloat* buffer, int frame);  
    virtual int getNumOfChannel();
};

#endif /* CWAVSOURCE_H */

