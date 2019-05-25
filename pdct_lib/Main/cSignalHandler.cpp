/* 
 * File:   cSignalHandler.cpp
 * Author: luciamarock
 * 
 * Created on 5 novembre 2016, 14.00
 */

#include "cSignalHandler.h"
#include "cSignal.h"

cSignalHandler::cSignalHandler() 
{
    SystemSignal.registerSignalHandler(this);
}

cSignalHandler::~cSignalHandler() 
{
    SystemSignal.unregisterSignalHandler(this);
}

