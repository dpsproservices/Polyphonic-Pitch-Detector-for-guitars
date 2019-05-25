
/* 
 * File:   cAudioSource.h
 * Author: xxac
 *
 * Created on 4 dicembre 2016, 18.23
 */

#ifndef CAUDIOSOURCE_H
#define CAUDIOSOURCE_H

#include "common_type.h"

class cAudioSource {
public:
    cAudioSource();
    virtual ~cAudioSource();
public:
    virtual int open() = 0;
    virtual int close() = 0;
    virtual int read(cFloat* buffer, int frame) = 0;
    virtual int getNumOfChannel() = 0;
};

#endif /* CAUDIOSOURCE_H */

