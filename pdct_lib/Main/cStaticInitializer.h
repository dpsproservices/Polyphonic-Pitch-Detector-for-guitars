/* 
 * File:   cStaticInitializer.h
 * Author: luciamarock
 *
 * Created on 5 novembre 2016, 14.00
 */

#ifndef CSTATICINITIALIZER_H
#define	CSTATICINITIALIZER_H

#include "common_type.h"

typedef  void(*func_exec)(void);

class cStaticInitializer {
public:
    static cStaticInitializer& getInstance();
private:
    cStaticInitializer();
    cStaticInitializer(const cStaticInitializer& orig);// Don't Implement
    virtual ~cStaticInitializer();
    void operator=(cStaticInitializer const&);// Don't Implement
private:
    cMap <func_exec, func_exec> m_funcMap;
public:
    void registerStaticInitializer(func_exec init, func_exec exit);
    void clean();
};

#define SystemInitializer cStaticInitializer::getInstance()

#endif	/* CSTATICINITIALIZER_H */

