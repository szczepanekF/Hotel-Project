//
// Created by student on 13.11.2022.
//

#ifndef HOTELPROJECT_MENUPANEL_H
#define HOTELPROJECT_MENUPANEL_H
#include "wx/wx.h"
#include "baseLoggedPanel.h"


class cMain;
class MenuPanel : public baseLoggedPanel {
private:
    wxButton** buttons;
    wxBoxSizer* horizontalSizer2;
public:
    MenuPanel(cMain* parent);
    virtual ~MenuPanel() = default;
private:
    void SwitchToRes(wxCommandEvent &evt) ;
    void SwitchToRooms(wxCommandEvent &evt) ;
    void SwitchToSetting(wxCommandEvent &evt) ;
    void Logout(wxCommandEvent &evt) ;



wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_MENUPANEL_H
