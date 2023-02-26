
#ifndef HOTELPROJECT_LOGINPANEL_H
#define HOTELPROJECT_LOGINPANEL_H
#include "baseLogRegistPanel.h"
class cMain;
class LoginPanel : public baseLogRegistPanel{
public:
    LoginPanel(cMain* parent);
    ~LoginPanel() = default;
private:
    void OnSubmitClicked(wxCommandEvent &evt) override;
    void OnRegistClicked(wxCommandEvent &evt) override;
    void OnPasswdWrite(wxCommandEvent &evt) override;

};


#endif //HOTELPROJECT_LOGINPANEL_H
