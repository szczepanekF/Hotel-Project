//
// Created by student on 04.02.2023.
//

#include <algorithm>
#include <numeric>
#include "Lists/SimpleRoomVirtualListControl.h"
#include <sstream>
#include <iomanip>

SimpleRoomVirtualListControl::SimpleRoomVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos,
                                                           const wxSize &size) : SimpleVirtualListBase<RoomItemData>(parent, winid, pos, size) {
    this->AppendColumn("Room nr",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Price Per night [eur]",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Bed Amount",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Terrace Surface [m^2]",wxLIST_FORMAT_CENTER);
    this->SetColumnWidth(0,100);
    this->SetColumnWidth(1,175);
    this->SetColumnWidth(2,100);
    this->SetColumnWidth(3,175);
}



wxString SimpleRoomVirtualListControl::OnGetItemText(long index, long column) const  {
    RoomItemData item  = items[orderedIndices[index]];
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) ;
    switch (column) {
        case 0: return std::to_string(item.nr);
        case 1:
            ss<< item.price;
            return ss.str();
        case 2: return std::to_string(item.beds);
        case 3:
            ss<< item.terr;
            return item.terr == 0 ? "X" : ss.str();
        default: return "";
    }
}



void SimpleRoomVirtualListControl::sortByColumn(int column) {
    const static auto genericCompare = [](auto i1,auto i2, bool ascending) {
        return ascending ? i1 < i2 : i1 > i2;
    };

    bool ascending = this->sortAscending;

    std::sort(orderedIndices.begin(),orderedIndices.end(),[this,column,ascending](long index1, long index2) {
        auto i1 = this->items[index1];
        auto i2 = this->items[index2];
        switch (column) {
            case 0:
                return genericCompare(i1.nr,i2.nr,ascending);
            case 1:
                return genericCompare(i1.price,i2.price,ascending);
            case 2:
                return genericCompare(i1.beds,i2.beds,ascending);
            case 3:
                return genericCompare(i1.terr,i2.terr,ascending);
            default:
                return false;
        }
    });
}



