
#ifndef HOTELPROJECT_REGISTRATIONPANEL_H
#define HOTELPROJECT_REGISTRATIONPANEL_H

#include "baseLogRegistPanel.h"

class gMain;
class RegistrationPanel : public baseLogRegistPanel {
public:
    RegistrationPanel(gMain* parent);;
    virtual ~RegistrationPanel();
private:
    wxTextCtrl* firstName = nullptr;
    wxTextCtrl* lastName = nullptr;
    wxButton* login= nullptr;

    void OnSubmitClicked(wxCommandEvent &evt) override;
    void OnRegistClicked(wxCommandEvent &evt) override;
    void OnPasswdWrite(wxCommandEvent &evt) override;
    void setHints() override;
//wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_REGISTRATIONFRAME_H
