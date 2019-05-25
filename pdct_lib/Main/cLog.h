/* 
 * File:   cLog.h
 * Author: luciamarock
 *
 * Created on 5 novembre 2016, 14.00
 */

#ifndef CLOG_H
#define	CLOG_H

class cLog {
public:
    static cLog& getInstance()
    {
       static cLog  instance;
       return instance;
    }
public:
    enum eLogLevel {
        OUT,
        INFO,
        WARNING,
        ERROR,
        NUM_LEVEL,
        /*-------*/
        ALL = ERROR,
        NONE= NUM_LEVEL,
    };
    bool m_loglevelEnable[NUM_LEVEL];
    void enableAllLogLevel();
    void disableAllLogLevel();
    void setLogLevelEnable(cLog::eLogLevel level, bool on);
    void setLogLevel(cLog::eLogLevel level);
    bool isLogLevelEnable(cLog::eLogLevel level);
    
    void log(cLog::eLogLevel level, const char * format, ... );
private:
    cLog();
    cLog(const cLog&);          // Don't Implement
    virtual ~cLog();
    void operator=(cLog const&);// Don't Implement
private:
    unsigned int getCurrentTime();
};

#define Logger cLog::getInstance()

#endif	/* CLOG_H */

