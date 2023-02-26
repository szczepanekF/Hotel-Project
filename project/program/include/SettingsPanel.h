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
    wxButton* standard = nullptr;
    wxButton* longTerm = nullptr;

    wxBoxSizer* changeMoneyAmountSizer = nullptr;
    wxBoxSizer* clientTypeInfoSizer = nullptr;

    wxBoxSizer* clientTypeSizer = nullptr;

    wxStaticText* errInfoMsg = nullptr;
    ClientPtr client;


public:
    SettingsPanel(cMain *parent);
    virtual ~SettingsPanel() = default;

    void setClient(const ClientPtr &client);
    void Refresh();
private:
    void add(wxCommandEvent &evt);
    void remove(wxCommandEvent &evt);
    void standardClicked(wxCommandEvent &evt);
    void longClicked(wxCommandEvent &evt);
    void ReturnClicked(wxCommandEvent &evt);
    void accountTypeInfo(wxCommandEvent &evt);
    void RefreshValue();


wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_SETTINGSPANEL_H
