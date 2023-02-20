//
// Created by student on 04.02.2023.
//

#ifndef HOTELPROJECT_SIMPLEROOMVIRTUALLISTCONTROL_H
#define HOTELPROJECT_SIMPLEROOMVIRTUALLISTCONTROL_H

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "RoomItemData.h"
#include <vector>


class SimpleRoomVirtualListControl : public wxListCtrl {
private:
    std::vector<RoomItemData> items;
    std::vector<long> orderedIndices;
public:
    SimpleRoomVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size);
    virtual wxString OnGetItemText(long index, long column) const override;
    void RefreshAfterUpdate();
    long getFirstSelectedIndex();
    void setItems(std::vector<RoomItemData> itemsToSet);

private:
    bool sortAscending = true;
    void sortByColumn(int column);

    long findIndexOfNRindex(long dataIndex);

};

#endif //HOTELPROJECT_SIMPLEROOMVIRTUALLISTCONTROL_H
