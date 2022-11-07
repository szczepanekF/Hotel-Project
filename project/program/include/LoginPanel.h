
#ifndef HOTELPROJECT_LOGINPANEL_H
#define HOTELPROJECT_LOGINPANEL_H
#include "wx/wx.h"
#include "baseLogRegistPanel.h"
class gMain;
class LoginPanel : public baseLogRegistPanel{
public:
    LoginPanel(gMain* parent);
    ~LoginPanel();
private:
    void OnSubmitClicked(wxCommandEvent &evt) override;
    void OnRegistClicked(wxCommandEvent &evt) override;
    void OnPasswdWrite(wxCommandEvent &evt) override;
//    wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_LOGINPANEL_H
