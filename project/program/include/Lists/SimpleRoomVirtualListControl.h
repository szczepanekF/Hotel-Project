//
// Created by student on 04.02.2023.
//

#ifndef HOTELPROJECT_SIMPLEROOMVIRTUALLISTCONTROL_H
#define HOTELPROJECT_SIMPLEROOMVIRTUALLISTCONTROL_H

#include "SimpleVirtualListBase.h"
#include "RoomItemData.h"



class SimpleRoomVirtualListControl : public SimpleVirtualListBase<RoomItemData> {

public:
    SimpleRoomVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size);
    wxString OnGetItemText(long index, long column) const override;
private:
    void sortByColumn(int column);



};

#endif //HOTELPROJECT_SIMPLEROOMVIRTUALLISTCONTROL_H
