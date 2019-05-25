
/* 
 * File:   cDisplayWidget.cpp
 * Author: xxac
 * 
 * Created on 28 novembre 2016, 22.22
 */

#include "cDisplayWidget.h"
#include "cPdtcFrame.h"
//#define NUM_OF_RESONATOR 51

static float noteToFrequency(int note) 
{
    return pow(2.0, (note-69)/12.0)*440.0;
}

static int indexToNote(int id)
{
    return FIRST_NOTE_NUMBER+id;
}

static void noteToName(int note, char* buff, int code)
{
    int octave = note/12 - 1;
    int root = note%12;
    
    static const char* name_tbl_0[12]={
        "C%d","C#%d","D%d","D#%d","E%d","F%d","F#%d","G%d","G#%d","A%d","A#%d","B%d",
    };
    static const char* name_tbl_1[12]={
        "DO%d","DO#%d","RE%d","RE#%d","MI%d","FA%d","FA#%d","SOL%d","SOL#%d","LA%d","LA#%d","SI%d",
    };
    if(code==0)
        sprintf(buff, name_tbl_0[root], octave);
    else
       sprintf(buff, name_tbl_1[root], octave); 
}

cDisplayWidget::cDisplayWidget(
            wxPanel *parent, 
            wxWindowID winid,
            const wxPoint& pos,
            const wxSize& size):
    wxPanel(parent, winid, pos, size, wxSUNKEN_BORDER)
{
  m_parent = parent;

  Connect(wxEVT_PAINT, wxPaintEventHandler(cDisplayWidget::OnPaint));
  Connect(wxEVT_SIZE, wxSizeEventHandler(cDisplayWidget::OnSize));    
}

cDisplayWidget::~cDisplayWidget() 
{
    
}

void cDisplayWidget::OnPaint(wxPaintEvent& /*event*/) 
{
    wxFont font(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));

    wxPaintDC dc(this);
    dc.SetFont(font);
    wxSize size = GetSize();
    int xborder = 40;
    int yborder = 40;
    int width = size.GetWidth()-2*xborder;
    int height= size.GetHeight()-2*yborder;

    /* draw x-axis */
    float xstep = (float) (width / 51.0);
    dc.SetPen(wxPen(wxColour(90, 80, 60)));
    for (int i = 0; i < 51; i++) {
        int ypos = yborder + height;
        int xpos = xborder + i*xstep;
        dc.DrawLine(xpos, ypos, xpos, ypos+6);
        wxSize size = dc.GetTextExtent(wxString::Format(wxT("%d"), i));
        if(i%2==0)
            dc.DrawText(wxString::Format(wxT("%d"), i), xpos - size.GetWidth() / 2, ypos+8);
        else
            dc.DrawText(wxString::Format(wxT("%d"), i), xpos - size.GetWidth() / 2, ypos+18);
    }
    
    /* draw y-axis */
    int yrange = 50;
    float ystep = ((float)height/(float)yrange);
    dc.SetPen(wxPen(wxColour(90, 80, 60)));
    for (int i = 0; i < yrange; i++) {
        int ypos = yborder+ystep*i;
        int xpos = xborder;
        dc.DrawLine(xpos-6, ypos, xpos, ypos);
        wxSize size = dc.GetTextExtent(wxString::Format(wxT("%d"), -2*i));
        if(i%2==0)
            dc.DrawText(wxString::Format(wxT("%d"), -2*i), xpos - 10 - size.GetWidth(), ypos-ystep/2);
        else
            dc.DrawText(wxString::Format(wxT("%d"), -2*i), xpos - 10 - size.GetWidth(), ypos-ystep/2);
    }
    
    /* draw background area */
    dc.SetPen(wxPen(wxColour(90, 80, 60)));
    dc.SetBrush(wxBrush(wxColour(255, 255, 184)));
    dc.DrawRectangle(xborder, yborder, width+1, height+1);
    
    /* draw x-grid */
    dc.SetPen(wxPen(wxColour(90, 80, 60),1,wxPENSTYLE_DOT));
    for (int i = 0; i < 51; i++) {
        int xpos = xborder + i*xstep;
        dc.DrawLine(xpos, yborder, xpos, yborder + height);
    }
    
    /* draw y-grid */
    dc.SetPen(wxPen(wxColour(90, 80, 60),1,wxPENSTYLE_DOT));
    for (int i = 0; i < 51; i++) {
        int ypos = yborder+ystep*i;
        dc.DrawLine(xborder, ypos, xborder+width, ypos);
    }
    
    /* draw diagram */
    cPdtcFrame *frame = (cPdtcFrame *) m_parent->GetParent();
    dc.SetPen(wxPen(wxColour(255, 0, 0)));
    dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
    int last_xpos;
    int last_ypos;
    for (int i = 0; i < 51; i++) {
        float y = frame->getDisplayValue(i)/2;
        int state = frame->getDisplayNoteState(i);
        if(y<0)y=0;
        if(y>yrange)y=yrange;
        int ypos = yborder+ystep*y;
        int xpos = xborder + i*xstep;
        if(state == 1){
            dc.SetBrush(wxBrush(wxColour(0, 0, 255)));
            dc.DrawCircle(xpos, ypos, 6);
        }
        
        dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
        dc.DrawCircle(xpos, ypos, 2);
        if(i>0){
            dc.DrawLine(last_xpos, last_ypos, xpos, ypos);
        }
        if(i>0 && i<50){
            if(frame->getDisplayValue(i)<96 && 
               (frame->getDisplayValue(i)<(frame->getDisplayValue(i-1)-3)) &&
               (frame->getDisplayValue(i)<(frame->getDisplayValue(i+1)-3)) ){
                int mode = frame->getSettings()->getNoteNameMode();
                int note = indexToNote(i);
                float frequency = noteToFrequency(note);
                char name[16];
                noteToName(note, name, mode);
                //dc.SetTextForeground(wxColour(0, 0, 0));
                dc.DrawText(wxString::Format(wxT("%s"), name), xpos+2, ypos-36);
                dc.DrawText(wxString::Format(wxT("%d"), note), xpos+2, ypos-27);
                dc.DrawText(wxString::Format(wxT("%.0fHz"), frequency), xpos+2, ypos-18);
                dc.DrawText(wxString::Format(wxT("%d"), i), xpos+2, ypos-9);
            }
        }
        last_xpos = xpos;
        last_ypos = ypos;
    }
    
    /* draw time */
    float time = frame->getDisplayTime();
    dc.SetPen(wxPen(wxColour(255, 0, 0)));
    dc.DrawText(wxString::Format(wxT("Time [sec]: %.3f"), time), xborder, yborder-16);
}

void cDisplayWidget::OnSize(wxSizeEvent& /*event*/)
{
    Refresh();
}
