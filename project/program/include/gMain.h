#include "wx/wx.h"
#include "socket/C_client.h"
#ifndef HOTELPROJECT_GMAIN_H
#define HOTELPROJECT_GMAIN_H


class gMain : public wxFrame{
public:
    gMain();
    virtual ~gMain();
public:
   wxButton* m_btn1 = nullptr;
    wxTextCtrl* m_txt1 = nullptr;
    wxListBox* m_list1= nullptr;
    C_client* connection = nullptr;
    wxStaticText* text = nullptr;
    wxBoxSizer* boxsizer = nullptr;
    wxBoxSizer* boxsizer2 = nullptr;

    void errorMessage(std::string message);
    void OnButtonClicked(wxCommandEvent &evt);
    void OnTextboxWritten(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_GMAIN_H
