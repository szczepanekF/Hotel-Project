//
// Created by student on 16.02.2023.
//

#ifndef HOTELPROJECT_SIMPLERESERVATIONVIRTUALLISTCONTROL_H
#define HOTELPROJECT_SIMPLERESERVATIONVIRTUALLISTCONTROL_H


#include "wx/wx.h"
#include "wx/listctrl.h"
#include "ReservationItemData.h"
#include <vector>


class SimpleReservationVirtualListControl : public wxListCtrl {
private:
    std::vector<ReservationItemData> items;
    std::vector<long> orderedIndices;
public:
    SimpleReservationVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size);
    virtual wxString OnGetItemText(long index, long column) const override;
    void RefreshAfterUpdate();

    void setItems(std::vector<ReservationItemData> itemsToSet);
private:
    bool sortAscending = true;
    void sortByColumn(int column);
    long getFirstSelectedIndex();
    long findIndexOfNRindex(long dataIndex);

};
#endif //HOTELPROJECT_SIMPLERESERVATIONVIRTUALLISTCONTROL_H
