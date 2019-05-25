/* 
 * File:   cPdctOptions.h
 * Author: luciamarock
 *
 * Created on 5 Novembre 2016, 15.00
 */

#ifndef CPDCTOPTIONS_H
#define	CPDCTOPTIONS_H

#include "common_type.h"

class cPdctOptions {
public:
    cPdctOptions();
    virtual ~cPdctOptions();
private:
    cMap<cString, int> m_optionList;
private:
    void initOptionList();
    void printUsage();
    void printVersion();
public:
    bool parseCommandLine(int argc, char** argv);
    int getOptionValue(cString optionKey);
};

#endif	/* CPDCTOPTIONS_H */

