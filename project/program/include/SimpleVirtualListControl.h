//
// Created by student on 04.02.2023.
//

#ifndef HOTELPROJECT_SIMPLEVIRTUALLISTCONTROL_H
#define HOTELPROJECT_SIMPLEVIRTUALLISTCONTROL_H

#include "wx/wx.h"
#include "wx/listctrl.h"
#include "itemdata.h"
#include <vector>


class SimpleVirtualListControl : public wxListCtrl {
private:
    std::vector<ItemData> items;
    std::vector<long> orderedIndices;
public:
    SimpleVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size);
    virtual wxString OnGetItemText(long index, long column) const override;
    void RefreshAfterUpdate();

    void setItems(std::vector<ItemData> itemsToSet);
private:
    bool sortAscending = true;
    void sortByColumn(int column);
    long getFirstSelectedIndex();
    long findIndexOfNRindex(long dataIndex);

};

#endif //HOTELPROJECT_SIMPLEVIRTUALLISTCONTROL_H
