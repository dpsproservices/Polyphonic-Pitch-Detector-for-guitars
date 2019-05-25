/* 
 * File:   cPdctOptions.cpp
 * Author: luciamarock
 * 
 * Created on 5 Novembre 2016, 15.00
 */

#include "cPdctOptions.h"
#include "cPdctVersion.h"
#include <stdlib.h>
#include <getopt.h>

cPdctOptions::cPdctOptions() 
{
    initOptionList();
}

cPdctOptions::~cPdctOptions() 
{
    
}

void cPdctOptions::initOptionList() 
{
    m_optionList["log-level"] = Logger.ERROR;
    m_optionList["exec-test"] = 0;
}

void cPdctOptions::printUsage() 
{
    LOG_OUTP("Usage:");
    LOG_OUTP("       --log-level=0..4  (log output level)");
    LOG_OUTP("       --exec-test=0..1  (execute test at startup)");
    LOG_OUTP("       --version         (show version information)");
    LOG_OUTP("       --help            (show this help message)");
}

void cPdctOptions::printVersion() 
{
    cPdctVersion aVersion;   
    LOG_OUTP("pdct version: %s", aVersion.getVersionString().data());
}

int cPdctOptions::getOptionValue(cString optionKey)
{
    cMap<cString, int>::const_iterator it;
    it = m_optionList.find(optionKey);
    if(it!=m_optionList.end()){
        return it->second;
    }else{
        LOG_ERRO("getOptionValue invalid option key");
        return 0;
    }
}

bool cPdctOptions::parseCommandLine(int argc, char** argv) 
{
    Logger.setLogLevel(cLog::ALL);
    
    while (1) {
        static struct option long_options[] ={
            {"log-level",       required_argument, 0, 'l'},
            {"exec-test",       required_argument, 0, 'e'},
            {"version",         no_argument,       0, 'v'},
            {"help",            no_argument,       0, 'h'},
            {0, 0, 0, 0}
        };
        
        /* getopt_long stores the option index here. */
        int option_index = 0;
        int c = getopt_long(argc, argv, "l:e:",
                long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;
        
        /* Detect the help message. */
        if (c == 'h'){
            printUsage();
            return false;
        }
        
        /* Detect the version message. */
        if (c == 'v'){
            printVersion();
            return false;
        }
        
        /* get option */
        bool foundOption = false;
        for(int i=0; i<(int)array_sizeof(long_options); i++){
            if(long_options[i].val == c){
                LOG_INFO("Found Option \"--%s\",\"-%c\" = %s", 
                        long_options[i].name, long_options[i].val, optarg);
                m_optionList[long_options[i].name] = atoi(optarg);
                foundOption = true;
                break;
            }
        }
        
        if(!foundOption){
            LOG_ERRO("Invalid Options");
            return false;
        }
    }
    
    /* all options specified are OK */
    return true;
}



