//
// Created by student on 07.11.2022.
//

#ifndef HOTELPROJECT_BASELOGREGISTPANEL_H
#define HOTELPROJECT_BASELOGREGISTPANEL_H
#include "wx/wx.h"

class gMain;
class baseLogRegistPanel : public wxPanel{
public:
    baseLogRegistPanel(gMain* parent);
    virtual ~baseLogRegistPanel();
protected:
    gMain* parent;
    wxBoxSizer* verticalSizer = nullptr;
    wxBoxSizer* horizontalSizer= nullptr;
    wxBoxSizer* horizontalSizer2= nullptr;
    wxTextCtrl* pid = nullptr;
    wxTextCtrl* passwd = nullptr;
    wxButton* submit= nullptr;
    wxButton* regist= nullptr;
    wxStaticText* info = nullptr;




    virtual void OnSubmitClicked(wxCommandEvent &evt)=0;
    virtual void OnRegistClicked(wxCommandEvent &evt)=0;
    virtual void OnPasswdWrite(wxCommandEvent &evt)= 0;
    wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_BASELOGREGISTPANEL_H
