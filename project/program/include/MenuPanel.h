//
// Created by student on 13.11.2022.
//

#ifndef HOTELPROJECT_MENUPANEL_H
#define HOTELPROJECT_MENUPANEL_H
#include "wx/wx.h"
#include "basePanel.h"


class gMain;
class MenuPanel : public basePanel {
public:
    MenuPanel(gMain* parent);
    virtual ~MenuPanel();

private:

    void SwitchToRes(wxCommandEvent &evt) ;
    void SwitchToRooms(wxCommandEvent &evt) ;
    void SwitchToSetting(wxCommandEvent &evt) ;
    wxButton** buttons;
wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_MENUPANEL_H
