/* 
 * File:   cLog.cpp
 * Author: luciamarock
 * 
 * Created on 5 novembre 2016, 14.00
 */

#include "common_type.h"
#include "cLog.h"
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <cstdio>
#include <cstdarg>
#include <sys/time.h>


cLog::cLog() 
{
    disableAllLogLevel();
}

cLog::~cLog() 
{
    
}

void cLog::enableAllLogLevel() 
{
    for(int i=0; i<NUM_LEVEL; i++) {
        m_loglevelEnable[i] = true;
    }
}

void cLog::disableAllLogLevel() 
{
    for(int i=0; i<NUM_LEVEL; i++) {
        m_loglevelEnable[i] = false;
    }
}

void cLog::setLogLevelEnable(cLog::eLogLevel level, bool on) {
    if(level>=NUM_LEVEL){
        return;
    }
    m_loglevelEnable[level]=on;
}

void cLog::setLogLevel(cLog::eLogLevel level) 
{
    for(int i=0; i<NUM_LEVEL; i++) {
        if(i<=level){
            m_loglevelEnable[i] = true;
        }else{
            m_loglevelEnable[i] = false;
        }
    }    
}

bool cLog::isLogLevelEnable(cLog::eLogLevel level) 
{
    if(level>=NUM_LEVEL){
        return false;
    }
    
    return m_loglevelEnable[level];
}

void cLog::log(cLog::eLogLevel level, const char* format, ...) 
{
    if(!isLogLevelEnable(level)){
        return;
    }
    
    /* build message */
    char sMessage[512];
    va_list args;
    va_start (args, format);
    vsnprintf (sMessage,sizeof(sMessage),format, args); 
    va_end (args);
    
    /* check for time */
    char sTime[32];
    if(sMessage[0]=='@'){
        sprintf(sTime, "[%06d]", getCurrentTime());
    }else{
        sTime[0]=0;
    }
    
    /* print */
    switch(level){
        case OUT:
            fprintf(stderr, "%s\n", sMessage);
            break;
        case INFO:
            fprintf(stderr, "pdct: [%s]%s %s\n", "INFO", sTime, sMessage);
            break;
        case WARNING:
            fprintf(stderr, "pdct: [%s]%s %s\n", "WARNING", sTime, sMessage);
            break;
        case ERROR:
            fprintf(stderr, "pdct: [%s]%s %s\n", "ERROR", sTime, sMessage);
            break;
        default:
            break;
    }
    fflush(stderr);
}

unsigned int cLog::getCurrentTime() 
{
    static unsigned int initialize_time = 0;
    static struct timeval initial_tv;
    
    if(initialize_time==0){
        gettimeofday(&initial_tv, NULL);
        initialize_time = 1;
        return 0;
    }
    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned int elapsed = (tv.tv_sec-initial_tv.tv_sec)*1000 + 
                           (tv.tv_usec-initial_tv.tv_usec)/1000;
    
    return elapsed;
}


