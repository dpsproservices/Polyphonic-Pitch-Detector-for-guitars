/* 
 * File:   cPdctMain.cpp
 * Author: luciamarock
 * 
 * Created on 5 Novembre 2016, 15.00
 */
#include "unistd.h"
#include "common_type.h"
#include "pdct_config.h"
#include "cPdctVersion.h"
#include "cPdctMain.h"
#include "cStaticInitializer.h"
#include "cPdctSimul.h"

#define USE_WXWODGETS_GUI_APP

#ifdef USE_WXWODGETS_GUI_APP
#include "cPdctApp.h"
#endif /* USE_WXWODGETS_GUI_APP */

cPdctMain::cPdctMain() : m_running(false)
{
    
}

cPdctMain::~cPdctMain()
{
    
}

void cPdctMain::run(cPdctOptions& opt)
{
    m_running = true;
    
    Logger.setLogLevel((cLog::eLogLevel)opt.getOptionValue("log-level"));
    
    /* print version information */
    cPdctVersion aVersion;
    LOG_OUTP("PDCT: START.");
    LOG_OUTP("PDCT: Version: %s", aVersion.getVersionString().data()); 
    
    /* run simulation of pitch detect */
//    cPdctSimul aTest;
//    aTest.addSineWave(cSineWave(40,1.0));
//    aTest.addSineWave(cSineWave(53,1.0));
//    aTest.addSineWave(cSineWave(69,1.0));
//    aTest.addSineWave(cSineWave(81,1.0));
//    aTest.run();
    
    /* keep running until the Ctrl+C (or signal) */
#ifdef USE_WXWODGETS_GUI_APP
    while (m_running) {
        cPdctApp::run();
        m_running = false;
    }
#else
    while (m_running) {
        sleep(1);
    }
#endif
    
    /* clear all objects */
    SystemInitializer.clean();
    
    LOG_OUTP("PDCT: End.");
}

void cPdctMain::stop()
{
    m_running = false;
}

void cPdctMain::handleSignal(int signal) {
    switch(signal){
        case SIGQUIT:
            LOG_INFO("signal SIGQUIT received, exiting ...");
            break;
        case SIGTERM:
            LOG_INFO("signal SIGTERM received, exiting ...");
            break;
        case SIGHUP:
            LOG_INFO("signal SIGHUP received, exiting ...");
            break;
        case SIGINT:
            LOG_INFO("signal SIGINT received, exiting ...");
            break;
    }
    
    stop();
}
