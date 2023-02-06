//
// Created by student on 01.02.2023.
//

#ifndef HOTELPROJECT_RESERVATIONPANEL_H
#define HOTELPROJECT_RESERVATIONPANEL_H

#include "basePanel.h"
#include "wx/wx.h"

class ReservationPanel: public basePanel {
public:
    ReservationPanel(gMain *parent);

    virtual ~ReservationPanel();
    void ReturnClicked(wxCommandEvent &evt);
wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_RESERVATIONPANEL_H
