//
// Created by student on 16.02.2023.
//

#include <numeric>
#include "Lists/SimpleReservationVirtualListControl.h"

SimpleReservationVirtualListControl::SimpleReservationVirtualListControl(wxWindow *parent, wxWindowID winid,
                                                                         const wxPoint &pos, const wxSize &size)
                                                                         : SimpleVirtualListBase(parent, winid, pos, size) {
    this->AppendColumn("Room nr",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Begin date",wxLIST_FORMAT_CENTER);
    this->AppendColumn("End date",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Beds",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Maintenance",wxLIST_FORMAT_CENTER);
    this->SetColumnWidth(0,100);
    this->SetColumnWidth(1,125);
    this->SetColumnWidth(2,100);
    this->SetColumnWidth(3,75);
    this->SetColumnWidth(4,150);
}

wxString SimpleReservationVirtualListControl::OnGetItemText(long index, long column) const {
    ReservationItemData item  = items[orderedIndices[index]];
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) ;
    switch (column) {
        case 0: return std::to_string(item.roomNr);
        case 1:
            return to_simple_string(item.begin.date());
        case 2:
            return to_simple_string(item.end.date());
        case 3:
            return std::to_string(item.guests);
        case 4:
            if (item.type_of_res == A) {
                return "No maintenance";
            } else if (item.type_of_res == B) {
                return "Breakfast";
            } else if (item.type_of_res = C) {
                ss << "Breakfast and dinner";
                return ss.str();
            }

        default: return "";


    }
}


void SimpleReservationVirtualListControl::sortByColumn(int column) {
    static auto genericCompare = [](auto i1, auto i2, bool ascending) {
        return ascending ? i1 < i2 : i1 > i2;
    };

    bool ascending = this->sortAscending;

    std::sort(orderedIndices.begin(), orderedIndices.end(), [this, column, ascending](long index1, long index2) {
        auto i1 = this->items[index1];
        auto i2 = this->items[index2];
        switch (column) {
            case 0:
                return genericCompare(i1.roomNr, i2.roomNr, ascending);
            case 1:
                return genericCompare(i1.begin, i2.begin, ascending);
            case 2:
                return genericCompare(i1.end, i2.end, ascending);
            case 3:
                return genericCompare(i1.guests, i2.guests, ascending);
            case 4:
                return genericCompare(i1.type_of_res, i2.type_of_res, ascending);
            default:
                return false;
        }
    });
}
