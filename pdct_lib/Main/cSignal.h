/* 
 * File:   cSignal.h
 * Author: luciamarock
 *
 * Created on 5 novembre 2016, 14.00
 */

#ifndef CSIGNAL_H
#define	CSIGNAL_H

#include <signal.h>

/* forward declaration */
class cSignalHandler;

/* signal class*/
class cSignal {
public:
    static cSignal& getInstance()
    {
       static cSignal  instance;
       return instance;
    }
private:
    cSignal();
    cSignal(const cSignal& orig);// Don't Implement
    virtual ~cSignal();
    void operator=(cSignal const&);// Don't Implement
private:
    enum {
        MAX_HANDLER = 10
    };
    cSignalHandler* m_handler[MAX_HANDLER];
    static void signal_handler(int signal);
    void sendSignalToRegisterHandler(int signal);
public:
    void registerSignalHandler(cSignalHandler* handler);
    void unregisterSignalHandler(cSignalHandler* handler);
};

#define SystemSignal cSignal::getInstance()

#endif	/* CSIGNAL_H */

