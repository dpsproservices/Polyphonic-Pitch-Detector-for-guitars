
/* 
 * File:   cJackProcess.h
 * Author: xxac
 *
 * Created on 18 dicembre 2016, 18.48
 */

#ifndef CJACKPROCESS_H
#define CJACKPROCESS_H

#include "common_type.h"

class cJackProcess {
public:
    cJackProcess(){};
    virtual ~cJackProcess(){};
public:
    virtual int process(cFloat* in, cFloat* out, int nframe, int nchannel) = 0;
//    {
//        /* thru copy */
//        for(int frame=0; frame<nframe; frame++){
//            for(int channel=0; channel<nchannel; channel++){
//                *out++ = (*in++);
//            }
//        }
//        return nframe;
//    }
};

#endif /* CJACKPROCESS_H */

