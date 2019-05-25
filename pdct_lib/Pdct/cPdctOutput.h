
/* 
 * File:   cPdctOutput.h
 * Author: xxac
 *
 * Created on 7 gennaio 2017, 9.53
 */

#ifndef CPDCTOUTPUT_H
#define CPDCTOUTPUT_H

class cPdctOutput {
public:
    cPdctOutput();
    virtual ~cPdctOutput();
public:
    virtual void onDetectNoteOn(int note, int velocity) = 0;
    virtual void onDetectNoteOff(int note, int velocity) = 0;
};

#endif /* CPDCTOUTPUT_H */

