/* 
 * File:   cSignal.cpp
 * Author: luciamarock
 * 
 * Created on 5 novembre 2016, 14.00
 */

#include "cSignal.h"
#include "common_type.h"
#include "cSignalHandler.h"

void cSignal::signal_handler(int signal) 
{
    SystemSignal.sendSignalToRegisterHandler(signal);
}

cSignal::cSignal()
{
    for(int i=0; i<MAX_HANDLER; i++){
        m_handler[i]=NULL;
    }
    
    signal(SIGQUIT, cSignal::signal_handler);
    signal(SIGTERM, cSignal::signal_handler);
    signal(SIGHUP, cSignal::signal_handler);
    signal(SIGINT, cSignal::signal_handler);
}

cSignal::~cSignal() 
{
    
}

void cSignal::registerSignalHandler(cSignalHandler* handler) 
{
    for(int i=0; i<MAX_HANDLER; i++){
        if(m_handler[i]==NULL){
            m_handler[i]=handler;
            return;
        }
    }    

    /* not enough handler space*/
    LOG_ERRO("Not enough space to regsiter a new signal handler");
}

void cSignal::unregisterSignalHandler(cSignalHandler* handler) 
{
    for(int i=0; i<MAX_HANDLER; i++){
        if(m_handler[i]==handler){
            m_handler[i]=NULL;
            return;
        }
    }    

    /* the handler was not resister before*/
    LOG_ERRO("No handler has been registered before");
}


void cSignal::sendSignalToRegisterHandler(int signal) 
{
    for(int i=0; i<MAX_HANDLER; i++){
        if(m_handler[i]!=NULL){
            m_handler[i]->handleSignal(signal);
        }
    }  
}
