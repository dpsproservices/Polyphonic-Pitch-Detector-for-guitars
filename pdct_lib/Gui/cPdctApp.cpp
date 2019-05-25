/* 
 * File:   cPdctApp.cpp
 * Author: xxac
 * 
 * Created on 27 novembre 2016, 16.56
 */

#include "cPdctApp.h"
#include "cPdtcFrame.h"

////---------------------------------------------------------------------------
//class Button : public wxFrame
//{
//public:
//    Button(const wxString& title);
//
//    void OnQuit(wxCommandEvent & event);
//};
//
//Button::Button(const wxString& title)
//       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
//{
//  wxPanel *panel = new wxPanel(this, wxID_ANY);
//
//  wxButton *button = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint(20, 20));
//  Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Button::OnQuit));
//  button->SetFocus();
//  Centre();
//}
//
//void Button::OnQuit(wxCommandEvent & WXUNUSED(event))
//{
//    Close(true);
//}
////---------------------------------------------------------------------------


cPdctApp::cPdctApp() 
{
    
}

cPdctApp::~cPdctApp() 
{
    
}

bool cPdctApp::OnInit() 
{
    cPdtcFrame* pdctframe = new cPdtcFrame(wxT("Pitch Detect App"));
    pdctframe->Show(true);
    
    return true;
}

/* start gui application */
IMPLEMENT_APP_NO_MAIN(cPdctApp)

int cPdctApp::run() 
{
    char* argv[] = { (char*)"PdctGuiApp", NULL };
    int   argc = sizeof(argv)/sizeof(argv[0]) - 1;

    return wxEntry(argc, argv); 
}

