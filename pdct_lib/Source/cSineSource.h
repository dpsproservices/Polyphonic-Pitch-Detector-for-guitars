
/* 
 * File:   cSineSource.h
 * Author: xxac
 *
 * Created on 5 dicembre 2016, 18.14
 */

#ifndef CSINESOURCE_H
#define CSINESOURCE_H

#include "cAudioSource.h"
#include "cSineWave.h"

class cSineSource: public cAudioSource {
public:
    cSineSource();
    virtual ~cSineSource();
private:
    cVector<cSineWave> m_sineWave;
    int m_frame;
    int m_time;
public:
    virtual int open();
    virtual int close();
    virtual int read(cFloat* buffer, int frame); 
    virtual int getNumOfChannel();
public:
    void addSineWave(cSineWave sine);
    void clearSineWave();
    void setDuration(cFloat time);
};

#endif /* CSINESOURCE_H */

