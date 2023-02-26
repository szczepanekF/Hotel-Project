//
// Created by student on 01.02.2023.
//

#ifndef HOTELPROJECT_ROOMSPANEL_H
#define HOTELPROJECT_ROOMSPANEL_H


#include "baseLoggedPanel.h"

#include "wx/wx.h"
#include "wx/datectrl.h"
#include "wx/generic/datectrl.h"
#include "typedefs.h"
#include "Lists/RoomItemData.h"
class SimpleRoomVirtualListControl;
class RoomsPanel: public baseLoggedPanel{
private:

    SimpleRoomVirtualListControl* basicListView =nullptr;

    wxDatePickerCtrlBase* begin = nullptr;
    wxDatePickerCtrlBase* end = nullptr;

    wxButton* searchButton = nullptr;
    wxButton* submitRes = nullptr;

    wxStaticText* dateErr = nullptr;
    wxStaticText* info = nullptr;
    wxStaticText* price = nullptr;
    wxStaticText* resPrice = nullptr;

    wxCheckBox* base = nullptr;
    wxCheckBox* medium = nullptr;
    wxCheckBox* extra = nullptr;

    wxBoxSizer* horizontalSizer2 = nullptr;
    wxBoxSizer* typeResSizer = nullptr;
    wxBoxSizer* priceSizer = nullptr;

    wxDateTime chosenBegin;
    wxDateTime chosenEnd;



public:
    RoomsPanel(cMain *parent);
    virtual ~RoomsPanel() = default;

private:
    void ReturnClicked(wxCommandEvent &evt);
    void SearchClicked(wxCommandEvent &evt);
    void SubmitReservation(wxCommandEvent &evt);

    void populateListView(RoomPredicate predicate);
    static std::string FormatDate(wxDateTime date);

    void RefreshPrice();
    void HidePrice();

    wxDECLARE_EVENT_TABLE();

};


#endif //HOTELPROJECT_ROOMSPANEL_H
