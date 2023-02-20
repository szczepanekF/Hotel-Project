//
// Created by student on 01.02.2023.
//

#include "ReservationPanel.h"
#include "model/Room.h"
#include "model/Client.h"
#include "cMain.h"
#include "SimpleReservationVirtualListControl.h"
wxBEGIN_EVENT_TABLE(ReservationPanel,wxPanel)
                EVT_BUTTON(1001,ReservationPanel::ReturnClicked)
                EVT_BUTTON(1002,ReservationPanel::ChangeClicked)
wxEND_EVENT_TABLE()

ReservationPanel::ReservationPanel(cMain *parent) : baseLoggedPanel(parent) {
    wxStaticText* info = new wxStaticText(this,wxID_ANY,"Your Reservations");
    wxButton* retButton = new wxButton(this,1001,"<-- MENU");
    changeBtn = new wxButton(this,1002,"Show ended reservations");

    list = new SimpleReservationVirtualListControl(this, wxID_ANY, wxDefaultPosition, wxSize(550, 200));
    verticalSizer->Add(info,0,wxALIGN_CENTER|wxTOP,20);
    verticalSizer->Add(changeBtn,0,wxALIGN_CENTRE|wxTOP|wxBOTTOM,10);
    verticalSizer->Add(list,0,wxALIGN_CENTER|wxALL,20);
    verticalSizer->Add(retButton,0,wxALIGN_LEFT|wxALL,10);
    this->SetSizer(verticalSizer);
}

ReservationPanel::~ReservationPanel() {


}
void ReservationPanel::ReturnClicked(wxCommandEvent &evt) {
    parent->changePanels(3);
    evt.Skip();
}


void ReservationPanel::ChangeClicked(wxCommandEvent &evt) {
    std::string pid = parent->getConnection()->getLoggedPid();
    if (!filter) {
        changeBtn->SetLabel("Show ended reservations");
        this->Layout();
    } else {
        changeBtn->SetLabel("Show upcoming reservations");
        this->Layout();
    }

    bool filt = this->filter;
    populateListView([pid,filt](const ReservationPtr &ptr){
        if (ptr->getClient()->getId() == pid) {
            return filt == (ptr->getEndTime().date() < pt::second_clock::local_time().date());
        }
        return false;});
    this->filter = !this->filter;
    evt.Skip();
}

void ReservationPanel::populateListView(ReservationPredicate predicate) {
    std::vector<ReservationPtr> resvs;
    try {
        resvs = parent->getResM()->findReservations(predicate);
    } catch (std::exception& e) {

    }
    std::vector<ReservationItemData> items;

    for (int i = 0; i < resvs.size(); i++) {
        items.push_back({resvs[i]->getRoom()->getId(),resvs[i]->getBeginTime(),resvs[i]->getEndTime(),
                         resvs[i]->getGuestCount(),resvs[i]->getExtraBonus()});
    }
    list->setItems(items);
    list->RefreshAfterUpdate();
}
