/* 
 * File:   cPdctApp.h
 * Author: xxac
 *
 * Created on 27 novembre 2016, 16.56
 */

#ifndef CPDCTAPP_H
#define CPDCTAPP_H

#include <wx/wx.h>

class cPdctApp: public wxApp {
public:
    cPdctApp();
    virtual ~cPdctApp();
private:
    virtual bool OnInit();
public:
    static int run();
};

#endif /* CPDCTAPP_H */

