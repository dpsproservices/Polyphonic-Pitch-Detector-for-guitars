/* 
 * File:   cStaticInitializer.cpp
 * Author: luciamarock
 * 
 * Created on 5 novembre 2016, 14.00
 */

#include "cStaticInitializer.h"

cStaticInitializer::cStaticInitializer() 
{
    
}


cStaticInitializer::~cStaticInitializer() 
{
    clean();
}

void cStaticInitializer::clean() 
{
    cMap<func_exec, func_exec>::const_iterator it;
    for (it = m_funcMap.begin(); it != m_funcMap.end(); ++it){
        func_exec exitCall = it->second;
        exitCall();
    }
    m_funcMap.clear();
}

void cStaticInitializer::registerStaticInitializer(func_exec init, func_exec exit) 
{
    m_funcMap[init] = exit;
    init();
}

cStaticInitializer& cStaticInitializer::getInstance() {
    static cStaticInitializer  instance;
    return instance;
}



