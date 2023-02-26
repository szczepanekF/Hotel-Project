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
    bool filter = false;
    SimpleReservationVirtualListControl* list = nullptr;
    wxButton* changeBtn = nullptr;
    wxButton* cancelResButton = nullptr;
    wxButton* changeTypeOfMaintenance = nullptr;
    wxButton* submit = nullptr;
    wxButton* submit2 = nullptr;

    wxBoxSizer* manageResSizer = nullptr;
    wxBoxSizer* changeTypeSizer = nullptr;
    wxBoxSizer* priceSizer = nullptr;
    wxCheckBox* medium = nullptr;
    wxCheckBox* extra = nullptr;
    wxStaticText* priceInfo = nullptr;
    wxStaticText* price = nullptr;

public:
    ReservationPanel(cMain *parent);
    virtual ~ReservationPanel() = default;
private:
    void ReturnClicked(wxCommandEvent &evt);
    void ChangeClicked(wxCommandEvent &evt);
    void ChangeType(wxCommandEvent &evt);
    void CancelReservation(wxCommandEvent &evt);
    void Submit(wxCommandEvent &evt);
    void Submit2(wxCommandEvent &evt);

    void populateListView(ReservationPredicate predicate);

    void RefreshPrice();
    void RefreshRefund();
    void HideOptions();
    ReservationPtr getSelectedRes();

wxDECLARE_EVENT_TABLE();
};


#endif //HOTELPROJECT_RESERVATIONPANEL_H
