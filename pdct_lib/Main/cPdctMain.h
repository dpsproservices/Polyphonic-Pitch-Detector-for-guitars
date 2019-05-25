/* 
 * File:   cPdctMain.h
 * Author: luciamarock
 *
 * Created on 5 Novembre 2016, 15.00
 */

#ifndef CPDCTMAIN_H
#define	CPDCTMAIN_H

#include "cPdctOptions.h"
#include "cSignalHandler.h"

class cPdctMain: public cSignalHandler {
public:
    cPdctMain();
    virtual ~cPdctMain();
private:
     volatile bool m_running;   
public:
    void run(cPdctOptions& opt);
    void stop();
    virtual void handleSignal(int signal);
};

#endif	/* CPDCTMAIN_H */

