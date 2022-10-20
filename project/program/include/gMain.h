//
// Created by student on 06.09.2022.
//
#include "wx/wx.h"
#include "../../library/include/socket/c_client.h"
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
    c_client* connection = nullptr;
    wxStaticText* text = nullptr;
    wxBoxSizer* boxsizer = nullptr;
    int nFieldWidth = 1;
    int nFieldHeight = 1;
   //wxButton **btn;


    void OnButtonClicked(wxCommandEvent &evt);
    void OnTextboxWritten(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_GMAIN_H
