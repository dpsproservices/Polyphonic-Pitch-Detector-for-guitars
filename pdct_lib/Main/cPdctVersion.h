/* 
 * File:   cPdctVersion.h
 * Author: luciamarock
 *
 * Created on 5 Novembre 2016, 15.00
 */

#ifndef CPDCTVERSION_H
#define	CPDCTVERSION_H

#include "common_type.h"

class cPdctVersion {
public:
    cPdctVersion();
    virtual ~cPdctVersion();
private:
    int m_mayorVersionNumber;
    int m_minorVersionNumber;
    int m_patchVersionNumber;
    int m_buildVersionNumber;
public:
    int getMayorVersionNumber(){
        return m_mayorVersionNumber;
    }
    int getMinorVersionNumber(){
        return m_minorVersionNumber;
    }
    int getPatchVersionNumber(){
        return m_patchVersionNumber;
    }
    int getBuildVersionNumber(){
        return m_buildVersionNumber;
    }
    cString getVersionString();
};

#endif	/* CPDCTVERSION_H */

