//
// Created by student on 01.02.2023.
//

#ifndef HOTELPROJECT_ROOMSPANEL_H
#define HOTELPROJECT_ROOMSPANEL_H


#include "basePanel.h"

#include "wx/wx.h"
#include "wx/datectrl.h"
#include "wx/generic/datectrl.h"

#include "itemdata.h"
class SimpleVirtualListControl;
class RoomsPanel: public basePanel{
private:
    SimpleVirtualListControl* basicListView =nullptr;
    wxDatePickerCtrlBase* begin = nullptr;
    wxDatePickerCtrlBase* end = nullptr;




    void ReturnClicked(wxCommandEvent &evt);
    void populateListView();





public:
    RoomsPanel(gMain *parent);

    virtual ~RoomsPanel();


    wxDECLARE_EVENT_TABLE();

};


#endif //HOTELPROJECT_ROOMSPANEL_H
