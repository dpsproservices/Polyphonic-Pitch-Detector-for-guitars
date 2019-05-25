
/* 
 * File:   cDisplayWidget.h
 * Author: xxac
 *
 * Created on 28 novembre 2016, 22.22
 */

#ifndef CDISPLAYWIDGET_H
#define CDISPLAYWIDGET_H

#include <wx/wx.h>

class cDisplayWidget: public wxPanel {
public:
    cDisplayWidget(wxPanel *parent, 
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize);
    virtual ~cDisplayWidget();
private:
    wxPanel *m_parent;
public:
    void OnSize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);
};

#endif /* CDISPLAYWIDGET_H */

