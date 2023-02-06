//
// Created by student on 08.01.2023.
//

#ifndef HOTELPROJECT_SETTINGSPANEL_H
#define HOTELPROJECT_SETTINGSPANEL_H
#include "wx/wx.h"
#include "basePanel.h"

class SettingsPanel: public basePanel {
public:
    SettingsPanel(gMain *parent);



    virtual ~SettingsPanel();

    void ReturnClicked(wxCommandEvent &evt);
    wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_SETTINGSPANEL_H
