//
// Created by student on 08.01.2023.
//

#ifndef HOTELPROJECT_SETTINGSPANEL_H
#define HOTELPROJECT_SETTINGSPANEL_H
#include "wx/wx.h"
#include "baseLoggedPanel.h"
#include "typedefs.h"
#include "wx/checkbox.h"
class SettingsPanel: public baseLoggedPanel {
private:

    wxButton* removeMoney = nullptr;
    wxButton* addMoney = nullptr;
    wxBoxSizer* changeMoneyAmountSizer = nullptr;
    wxStaticText* value = nullptr;
    wxButton* standard = nullptr;
    wxButton* longTerm = nullptr;
    wxBoxSizer* clientTypeSizer = nullptr;
    ClientPtr client;



    void add(wxCommandEvent &evt);
    void remove(wxCommandEvent &evt);
    void standardClicked(wxCommandEvent &evt);
    void longClicked(wxCommandEvent &evt);
    void ReturnClicked(wxCommandEvent &evt);
    void RefreshValue();

public:
    SettingsPanel(cMain *parent);

    void setClient(const ClientPtr &client);

    virtual ~SettingsPanel();
    void Refresh();


wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_SETTINGSPANEL_H
