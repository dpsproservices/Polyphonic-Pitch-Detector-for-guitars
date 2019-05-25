
/* 
 * File:   cJackdDriver.h
 * Author: xxac
 *
 * Created on 17 dicembre 2016, 18.13
 */

#ifndef CJACKDDRIVER_H
#define CJACKDDRIVER_H

#include "common_type.h"
#include "cJackProcess.h"

class cJackdDriver {
public:
    cJackdDriver();
    virtual ~cJackdDriver();
private:
    cString m_clientName;
    void* m_client;
    void* m_output_port1;
    void* m_output_port2;
    void* m_input_port1;
    void* m_input_port2;
    int m_bufferSize;
    cFloat* m_inputBuffer;
    cFloat* m_outputBuffer;
    cJackProcess* m_process;
public:
    /* jackd callback*/
    int onJackProcess(int frames);
    void onJackShutdown();
public:
    int open(cString name);
    int close();
    void attachProcess(cJackProcess* process);
};

#endif /* CJACKDDRIVER_H */

