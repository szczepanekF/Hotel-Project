
#ifndef HOTELPROJECT_REGISTRATIONPANEL_H
#define HOTELPROJECT_REGISTRATIONPANEL_H

#include "baseLogRegistPanel.h"

class cMain;
class RegistrationPanel : public baseLogRegistPanel {
private:
    wxTextCtrl* firstName = nullptr;
    wxTextCtrl* lastName = nullptr;
    wxButton* login= nullptr;
public:
    RegistrationPanel(cMain* parent);
    virtual ~RegistrationPanel() = default;
private:
    void OnSubmitClicked(wxCommandEvent &evt) override;
    void OnRegistClicked(wxCommandEvent &evt) override;
    void OnPasswdWrite(wxCommandEvent &evt) override;

    void setHints() override;

};


#endif //HOTELPROJECT_REGISTRATIONFRAME_H
