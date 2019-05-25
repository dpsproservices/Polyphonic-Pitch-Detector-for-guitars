
/* 
 * File:   cBuffSource.h
 * Author: xxac
 *
 * Created on 27 dicembre 2016, 10.05
 */

#ifndef CBUFFSOURCE_H
#define CBUFFSOURCE_H

#include "cAudioSource.h"
#include "cSineWave.h"

class cBuffSource: public cAudioSource  {
public:
    cBuffSource();
    virtual ~cBuffSource();
public:
    virtual int open();
    virtual int close();
    virtual int read(cFloat* buffer, int frame); 
    virtual int getNumOfChannel();
private:
    cFloat* m_buffer;  
    int m_frame;
    int m_channel;
    cFloat m_volume;
public:
    void putBuffer(cFloat* buff, int frame, int channel);
    void setVolume(cFloat volume);
};

#endif /* CBUFFSOURCE_H */

