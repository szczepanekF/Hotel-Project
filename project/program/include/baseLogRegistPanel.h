//
// Created by student on 07.11.2022.
//

#ifndef HOTELPROJECT_BASELOGREGISTPANEL_H
#define HOTELPROJECT_BASELOGREGISTPANEL_H
#include "wx/wx.h"
#include "basePanel.h"

class cMain;
class baseLogRegistPanel : public basePanel{
protected:
    wxBoxSizer* horizontalSizer2= nullptr;

    wxTextCtrl* pid = nullptr;
    wxTextCtrl* passwd = nullptr;

    wxButton* submit= nullptr;
    wxButton* regist= nullptr;

    wxStaticText* info = nullptr;



public:
    baseLogRegistPanel(cMain* parent);
    virtual ~baseLogRegistPanel() = default;

    void setSubmitFocus() const;
protected:
    virtual void setHints();
    virtual void OnSubmitClicked(wxCommandEvent &evt)=0;
    virtual void OnRegistClicked(wxCommandEvent &evt)=0;
    virtual void OnPasswdWrite(wxCommandEvent &evt)= 0;
    wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_BASELOGREGISTPANEL_H
