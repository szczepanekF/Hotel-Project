//
// Created by student on 04.02.2023.
//

#include <algorithm>
#include <numeric>
#include "SimpleRoomVirtualListControl.h"
#include <sstream>
#include <iomanip>

SimpleRoomVirtualListControl::SimpleRoomVirtualListControl(wxWindow *parent, wxWindowID winid, const wxPoint &pos,
                                                           const wxSize &size) : wxListCtrl(parent, winid, pos, size, wxLC_REPORT | wxLC_VIRTUAL) {
    this->AppendColumn("Room nr",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Price Per night [eur]",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Bed Amount",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Terrace Surface [m^2]",wxLIST_FORMAT_CENTER);
    this->SetColumnWidth(0,100);
    this->SetColumnWidth(1,175);
    this->SetColumnWidth(2,100);
    this->SetColumnWidth(3,175);


    this->Bind(wxEVT_LIST_COL_CLICK,[this](wxListEvent& evt) {
        auto selectedListIndex = getFirstSelectedIndex();
        long selectedNrIndex;
        if (selectedListIndex!= -1) {
            selectedNrIndex = this->orderedIndices[selectedListIndex];
            this->SetItemState(selectedListIndex,0,wxLIST_STATE_SELECTED);
        }

        this->sortByColumn(evt.GetColumn());
        this->RefreshAfterUpdate();

        if (selectedListIndex!= -1) {
            auto indexToSelect = findIndexOfNRindex(selectedNrIndex);
            this->SetItemState(indexToSelect,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
            this->EnsureVisible(indexToSelect);
        }


        this->sortAscending = !this->sortAscending;
    });

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

void SimpleRoomVirtualListControl::RefreshAfterUpdate() {
    this->SetItemCount(orderedIndices.size());
    this->Refresh();

}


void SimpleRoomVirtualListControl::sortByColumn(int column) {
    static auto genericCompare = [](auto i1,auto i2, bool ascending) {
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

long SimpleRoomVirtualListControl::getFirstSelectedIndex() {
    return GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
}

long SimpleRoomVirtualListControl::findIndexOfNRindex(long dataIndex) {
    return std::find(orderedIndices.begin(),orderedIndices.end(),dataIndex)-orderedIndices.begin();
}

void SimpleRoomVirtualListControl::setItems(std::vector<RoomItemData> itemsToSet) {
    this->items = itemsToSet;
    this->orderedIndices = std::vector<long>(items.size());
    std::iota(orderedIndices.begin(),orderedIndices.end(),0);
}
