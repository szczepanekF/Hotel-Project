//
// Created by student on 25.02.2023.
//

#ifndef HOTELPROJECT_SIMPLEVIRTUALLISTBASE_H
#define HOTELPROJECT_SIMPLEVIRTUALLISTBASE_H


#include "wx/wx.h"
#include "wx/listctrl.h"
#include <vector>
#include <numeric>

template<class T> class SimpleVirtualListBase : public wxListCtrl{
protected:
    std::vector<T> items;
    std::vector<long> orderedIndices;
    bool sortAscending = true;
public:
    SimpleVirtualListBase(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size)
    : wxListCtrl(parent, winid, pos, size, wxLC_REPORT | wxLC_VIRTUAL){

        this->Bind(wxEVT_LIST_ITEM_SELECTED,[this](wxListEvent &evt){
            auto selectedListIndex = 0;
            if (GetSelectedItemCount() > 1) {
                while (selectedListIndex != -1) {
                    selectedListIndex = getFirstSelectedIndex();
                    this->SetItemState(selectedListIndex, 0, wxLIST_STATE_SELECTED);
                }
            }
        });

        this->Bind(wxEVT_LIST_COL_CLICK,[this](wxListEvent& evt) {
            auto selectedListIndex = getFirstSelectedIndex();
            long selectedNrIndex;
            if (selectedListIndex!= -1) {
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
    };
    virtual wxString OnGetItemText(long index, long column) const override = 0;;
    virtual void RefreshAfterUpdate(){
        this->SetItemCount(orderedIndices.size());
        this->Refresh();
    };
    virtual long getFirstSelectedIndex() {
        return GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED);
    };
    virtual void setItems(std::vector<T> itemsToSet) {
        this->items = itemsToSet;
        this->orderedIndices = std::vector<long>(items.size());
        std::iota(orderedIndices.begin(),orderedIndices.end(),0);
    };

private:

    virtual void sortByColumn(int column) = 0;

    virtual long findIndexOfNRindex(long dataIndex) {
        return std::find(orderedIndices.begin(),orderedIndices.end(),dataIndex)-orderedIndices.begin();};
};


#endif //HOTELPROJECT_SIMPLEVIRTUALLISTBASE_H
