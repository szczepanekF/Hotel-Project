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
#include "RoomItemData.h"
class SimpleRoomVirtualListControl;
class RoomsPanel: public baseLoggedPanel{
private:
    wxBoxSizer* horizontalSizer2 = nullptr;
    SimpleRoomVirtualListControl* basicListView =nullptr;
    wxDatePickerCtrlBase* begin = nullptr;
    wxDatePickerCtrlBase* end = nullptr;
    wxButton* searchButton = nullptr;
    wxStaticText* dateErr = nullptr;
    wxStaticText* info = nullptr;
    wxStaticText* price = nullptr;
    wxButton* submitRes = nullptr;
    wxCheckBox* medium = nullptr;
    wxCheckBox* extra = nullptr;
    wxBoxSizer* typeResSizer = nullptr;
    wxDateTime chosenBegin;
    wxDateTime chosenEnd;
    void ReturnClicked(wxCommandEvent &evt);
    void populateListView(RoomPredicate predicate);
    void SearchClicked(wxCommandEvent &evt);
    static std::string FormatDate(wxDateTime date);
    void RefreshPrice();



public:
    RoomsPanel(cMain *parent);

    virtual ~RoomsPanel();


    wxDECLARE_EVENT_TABLE();

};


#endif //HOTELPROJECT_ROOMSPANEL_H
