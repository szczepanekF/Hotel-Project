//
// Created by student on 16.02.2023.
//

#ifndef HOTELPROJECT_SIMPLERESERVATIONVIRTUALLISTCONTROL_H
#define HOTELPROJECT_SIMPLERESERVATIONVIRTUALLISTCONTROL_H


#include "wx/wx.h"
#include "wx/listctrl.h"
#include "ReservationItemData.h"
#include <vector>
#include "SimpleVirtualListBase.h"


class SimpleReservationVirtualListControl : public SimpleVirtualListBase<ReservationItemData> {
public:
    SimpleReservationVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size);
    wxString OnGetItemText(long index, long column) const override;
private:
    void sortByColumn(int column);


};
#endif //HOTELPROJECT_SIMPLERESERVATIONVIRTUALLISTCONTROL_H
