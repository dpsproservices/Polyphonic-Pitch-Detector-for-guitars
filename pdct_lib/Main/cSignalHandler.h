/* 
 * File:   cSignalHandler.h
 * Author: luciamarock
 *
 * Created on 5 novembre 2016, 14.00
 */

#ifndef CSIGNALHANDLER_H
#define	CSIGNALHANDLER_H

#include <signal.h>

class cSignalHandler {
public:
    cSignalHandler();
    virtual ~cSignalHandler();
public:
    virtual void handleSignal(int signal)=0;
};

#endif	/* CSIGNALHANDLER_H */

