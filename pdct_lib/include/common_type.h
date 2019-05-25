/* 
 * File:   common_type.h
 * Author: luciamarock
 * Note: general common type
 * 
 * Created on 5 novembre 2016, 14.00
 */

#ifndef COMMON_TYPE_H
#define	COMMON_TYPE_H

/* sprintf */
#include <cstdio>

/* memset,...*/
#include <cstring>

/* cString */
#include <string>
typedef std::string cString;

/* cMap */
#include <map>
#define cMap    std::map

/* cVector */
#include <vector>
#define cVector   std::vector

/* cList */
#include <list>
#define cList   std::list

/* float type */
typedef double cFloat;

/* sampling frequency */
#ifdef RUN_AT_48KHZ
#define SAMPLE_RATE  48000.0
#define SAMPLE_RATE_INT  48000
#else
#define SAMPLE_RATE  44100.0
#define SAMPLE_RATE_INT  44100
#endif

/* useful math function */
#include <cmath>

/* size of any array */
#define array_sizeof(a) ((int)(sizeof(a)/sizeof(a[0])))

/* enable log function */
#include "log_info.h"

/* make compiler happy for not used variable */
#define UNUSED(x) (void)(x)

#endif	/* COMMON_TYPE_H */

