/* 
 * File:   log_function.h
 * Author: luciamarock
 * Note: general log function call
 * 
 * Created on 19 Novembre 2016, 15.00
 */

#ifndef LOG_INFO_H
#define	LOG_INFO_H

#include "log_config.h"
#include "cLog.h"

#ifdef ENABLE_LOG
#define LOG_OUTP(...) Logger.log(cLog::OUT,__VA_ARGS__)
#define LOG_INFO(...) Logger.log(cLog::INFO,__VA_ARGS__)
#define LOG_WARN(...) Logger.log(cLog::WARNING,__VA_ARGS__)
#define LOG_ERRO(...) Logger.log(cLog::ERROR,__VA_ARGS__)
#else
#define LOG_OUTP(...) Logger.log(cLog::OUT,__VA_ARGS__)
#define LOG_INFO(...) 
#define LOG_WARN(...) 
#define LOG_ERRO(...) 
#endif

#endif	/* LOG_INFO_H */

