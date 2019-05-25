/* 
 * File:   cPdctVersion.cpp
 * Author: luciamarock
 * 
 * Created on 5 Novembre 2016, 15.00
 */

#include "cPdctVersion.h"
#include "pdct_config.h"

cPdctVersion::cPdctVersion():
    m_mayorVersionNumber(pdct_VERSION_MAJOR),
    m_minorVersionNumber(pdct_VERSION_MINOR),
    m_patchVersionNumber(pdct_VERSION_PATCH),
    m_buildVersionNumber(pdct_VERSION_BUILD)
{
    
}

cPdctVersion::~cPdctVersion() 
{
    
}

cString cPdctVersion::getVersionString() {
  char buff[50];
  sprintf(buff, "%d.%02d.%02d (build %03d)", 
          m_mayorVersionNumber, m_minorVersionNumber, 
          m_patchVersionNumber, m_buildVersionNumber); 
  
  return cString(buff);
}



