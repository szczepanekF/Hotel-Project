//
// Created by student on 01.02.2023.
//

#ifndef HOTELPROJECT_RESERVATIONPANEL_H
#define HOTELPROJECT_RESERVATIONPANEL_H

#include "baseLoggedPanel.h"
#include "wx/wx.h"
#include "typedefs.h"

class SimpleReservationVirtualListControl;
class ReservationPanel: public baseLoggedPanel {
    bool filter = true;
    SimpleReservationVirtualListControl* list = nullptr;
    wxButton* changeBtn = nullptr;
    void ReturnClicked(wxCommandEvent &evt);
    void ChangeClicked(wxCommandEvent &evt);
    void populateListView(ReservationPredicate predicate);
public:
    ReservationPanel(cMain *parent);

    virtual ~ReservationPanel();

wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_RESERVATIONPANEL_H
