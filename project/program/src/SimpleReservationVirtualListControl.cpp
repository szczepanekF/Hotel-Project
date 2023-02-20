//
// Created by student on 16.02.2023.
//

#include <numeric>
#include "SimpleReservationVirtualListControl.h"

SimpleReservationVirtualListControl::SimpleReservationVirtualListControl(wxWindow *parent, wxWindowID winid,
                                                                         const wxPoint &pos, const wxSize &size)
                                                                         : wxListCtrl(parent, winid, pos, size, wxLC_REPORT | wxLC_VIRTUAL) {
    this->AppendColumn("Room nr",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Begin date",wxLIST_FORMAT_CENTER);
    this->AppendColumn("End date",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Guests",wxLIST_FORMAT_CENTER);
    this->AppendColumn("Reservation Type",wxLIST_FORMAT_CENTER);
    this->SetColumnWidth(0,100);
    this->SetColumnWidth(1,125);
    this->SetColumnWidth(2,100);
    this->SetColumnWidth(3,75);
    this->SetColumnWidth(4,150);

    this->Bind(wxEVT_LIST_COL_CLICK,[this](wxListEvent& evt) {
        auto selectedListIndex = getFirstSelectedIndex();
        long selectedNrIndex;
        if (selectedListIndex != -1) {
            selectedNrIndex = this->orderedIndices[selectedListIndex];
            this->SetItemState(selectedListIndex,0,wxLIST_STATE_SELECTED);
        }

        this->sortByColumn(evt.GetColumn());
        this->RefreshAfterUpdate();

        if (selectedListIndex != -1) {
            auto indexToSelect = findIndexOfNRindex(selectedNrIndex);
            this->SetItemState(indexToSelect,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
            this->EnsureVisible(indexToSelect);
        }


        this->sortAscending = !this->sortAscending;
    });

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
            return std::to_string(item.type_of_res);
        default: return "";


    }
}

void SimpleReservationVirtualListControl::RefreshAfterUpdate() {
    this->SetItemCount(orderedIndices.size());
    this->Refresh();
}

void SimpleReservationVirtualListControl::setItems(std::vector<ReservationItemData> itemsToSet) {
    this->items = itemsToSet;
    this->orderedIndices = std::vector<long>(items.size());
    std::iota(orderedIndices.begin(),orderedIndices.end(),0);
}

void SimpleReservationVirtualListControl::sortByColumn(int column) {
    static auto genericCompare = [](auto i1,auto i2, bool ascending) {
        return ascending ? i1 < i2 : i1 > i2;
    };

    bool ascending = this->sortAscending;

    std::sort(orderedIndices.begin(),orderedIndices.end(),[this,column,ascending](long index1, long index2) {
        auto i1 = this->items[index1];
        auto i2 = this->items[index2];
        switch (column) {
            case 0:
                return genericCompare(i1.roomNr,i2.roomNr,ascending);
            case 1:
                return genericCompare(i1.begin,i2.begin,ascending);
            case 2:
                return genericCompare(i1.end,i2.end,ascending);
            case 3:
                return genericCompare(i1.guests,i2.guests,ascending);
            case 4:
                return genericCompare(i1.type_of_res,i2.type_of_res,ascending);
            default:
                return false;
        }
    });
}

long SimpleReservationVirtualListControl::getFirstSelectedIndex() {
    return GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
}

long SimpleReservationVirtualListControl::findIndexOfNRindex(long dataIndex) {
    return std::find(orderedIndices.begin(),orderedIndices.end(),dataIndex)-orderedIndices.begin();
}
