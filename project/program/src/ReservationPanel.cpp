//
// Created by student on 01.02.2023.
//

#include "ReservationPanel.h"
#include "model/Room.h"
#include "model/Client.h"
#include "cMain.h"
#include "Lists/SimpleReservationVirtualListControl.h"



wxBEGIN_EVENT_TABLE(ReservationPanel,wxPanel)
                EVT_BUTTON(1001,ReservationPanel::ReturnClicked)
                EVT_BUTTON(1002,ReservationPanel::ChangeClicked)
                EVT_BUTTON(1003,ReservationPanel::CancelReservation)
                EVT_BUTTON(1004,ReservationPanel::ChangeType)
                EVT_BUTTON(1005,ReservationPanel::Submit)
                EVT_BUTTON(1006,ReservationPanel::Submit2)
wxEND_EVENT_TABLE()

ReservationPanel::ReservationPanel(cMain *parent) : baseLoggedPanel(parent) {
    manageResSizer = new wxBoxSizer(wxHORIZONTAL);
    changeTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    priceSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* info = new wxStaticText(this,wxID_ANY,"Your Reservations");
    wxFont* tekst = new wxFont();
    tekst->SetWeight(wxFONTWEIGHT_BOLD);
    info->SetFont(*tekst);
    info->SetForegroundColour(*wxBLUE);
    wxButton* retButton = new wxButton(this,1001,"<-- MENU");
    changeBtn = new wxButton(this,1002,"Show upcoming/ongoing");

    cancelResButton = new wxButton(this,1003,"Cancel Reservation");
    cancelResButton->SetForegroundColour(*wxRED);

    changeTypeOfMaintenance = new wxButton(this,1004,"Change Maintenance");

    medium = new wxCheckBox(this,wxID_ANY,"breakfast");
    extra = new wxCheckBox(this,wxID_ANY,"breakfast and dinner");

    
    medium->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        if (!extra->GetValue()) {
            medium->SetValue(true);
            return;
        }

        extra->SetValue(false);
        RefreshPrice();
    });
    extra->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        if (!medium->GetValue()) {
            extra->SetValue(true);
            return;
        }
        medium->SetValue(false);
        RefreshPrice();
    });



    list = new SimpleReservationVirtualListControl(this, wxID_ANY, wxDefaultPosition, wxSize(550, 200));


    list->Bind(wxEVT_LIST_ITEM_SELECTED,[this](wxListEvent &evt){

        ReservationPtr ptr = getSelectedRes();
        if (filter == true) {
            cancelResButton->Show();
        }
        if (ptr->getExtraBonus() != C){
            changeTypeOfMaintenance->Show();
        }

        this->Layout();
        evt.Skip();});
    list->Bind(wxEVT_LIST_ITEM_DESELECTED,[this](wxListEvent &evt){
        HideOptions();
        evt.Skip();});

    list->Hide();

    manageResSizer->Add(cancelResButton,0,wxALIGN_CENTER|wxRIGHT,10);
    manageResSizer->Add(changeTypeOfMaintenance,0,wxALIGN_CENTER|wxLEFT,10);


    changeTypeSizer->Add(medium,0,wxRIGHT,10);
    changeTypeSizer->Add(extra,0,wxLEFT,10);


    priceInfo = new wxStaticText(this,wxID_ANY,"Price: ");
    price = new wxStaticText(this,wxID_ANY,"");
    submit = new wxButton(this,1005,"Pay and submit changes");
    submit2 = new wxButton(this,1006,"Cancel reservation and get refund");
    HideOptions();

    priceSizer->Add(priceInfo,0,wxALIGN_CENTER|wxRIGHT,7);
    priceSizer->Add(price,0,wxALIGN_CENTER|wxRIGHT,10);
    priceSizer->Add(submit,0,wxALIGN_CENTER,0);
    priceSizer->Add(submit2,0,wxALIGN_CENTER,0);


    verticalSizer->Add(info,0,wxALIGN_CENTER|wxTOP,20);
    verticalSizer->Add(changeBtn,0,wxALIGN_CENTRE|wxTOP|wxBOTTOM,10);
    verticalSizer->Add(list,0,wxALIGN_CENTER|wxALL,20);
    verticalSizer->Add(manageResSizer,0,wxALIGN_CENTER|wxALL,20);
    verticalSizer->Add(changeTypeSizer,0,wxALIGN_RIGHT|wxRIGHT,75);
    verticalSizer->Add(priceSizer,0,wxALIGN_RIGHT|wxRIGHT,75);
    verticalSizer->Add(retButton,0,wxALIGN_LEFT|wxALL,10);
    this->SetSizer(verticalSizer);
}






void ReservationPanel::ReturnClicked(wxCommandEvent &evt) {
    changeBtn->SetLabel("Show upcoming/ongoing");
    this->filter = false;
    list->Hide();

    HideOptions();
    evt.Skip();
    parent->changePanels(3);

}


void ReservationPanel::ChangeClicked(wxCommandEvent &evt) {
    list->Show();
    std::string pid = parent->getConnection()->getLoggedPid();
    if (!filter) {

        changeBtn->SetLabel("Show ended");
        this->Layout();
    } else {
        changeBtn->SetLabel("Show upcoming/ongoing");
        this->Layout();
    }

    bool filt = this->filter;
    populateListView([pid,filt](const ReservationPtr &ptr){
        if (ptr->getClient()->getId() == pid) {
            return filt == (ptr->getEndTime().date() < pt::second_clock::local_time().date());
        }
        return false;});
    this->filter = !this->filter;
    HideOptions();
    long id = list->getFirstSelectedIndex();
    list->SetItemState(id,0,wxLIST_STATE_SELECTED);
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

void ReservationPanel::RefreshPrice() {
    submit->SetLabel("Pay and submit changes");
    priceInfo->SetLabel("Price: ");
    ReservationPtr ptr = getSelectedRes();
    ReservationManagerPtr resM = parent->getResM();

    extraBonusType addPrice = A;
    if (medium->GetValue()) {
        addPrice = B;

    } else if (extra->GetValue()) {
        addPrice = C;
    }
    double diff = resM->calculatePriceDifferenceAfterChange(ptr->getId(),addPrice);
    if (diff > ptr->getClient()->getBalance()) {
        submit->Disable();
        price->SetForegroundColour(*wxRED);
    } else {
        submit->Enable();
        price->SetForegroundColour(*wxGREEN);
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << diff;
    price->SetLabel(ss.str());
    this->Layout();
}

void ReservationPanel::CancelReservation(wxCommandEvent &evt) {
    medium->Hide();
    extra->Hide();
    medium->SetValue(false);
    extra->SetValue(false);
    submit->Hide();
    submit2->Show();
    price->Show();
    priceInfo->Show();
    RefreshRefund();
    this->Layout();
    evt.Skip();
}

void ReservationPanel::ChangeType(wxCommandEvent &evt) {

    ReservationPtr ptr = getSelectedRes();
    priceInfo->Show();
    price->Show();
    submit->Show();
    submit2->Hide();

    extraBonusType a = ptr->getExtraBonus();

    if (a == A) {
        medium->Show();
        medium->SetValue(true);
        extra->SetValue(false);
    } else {
        extra->SetValue(true);
    }
    extra->Show();



    RefreshPrice();
    evt.Skip();
    this->Layout();
}

void ReservationPanel::HideOptions() {

    cancelResButton->Hide();
    changeTypeOfMaintenance->Hide();
    medium->Hide();
    extra->Hide();
    medium->SetValue(false);
    extra->SetValue(false);
    priceInfo->Hide();
    price->Hide();
    submit->Hide();
    submit2->Hide();
    this->Layout();
}

ReservationPtr ReservationPanel::getSelectedRes() {
    std::vector<ReservationPtr> res = parent->getResM()->findReservations([this](const ReservationPtr &ptr){
        long id = list->getFirstSelectedIndex();
        std::string beginDate = list->GetItemText(id,1).ToStdString();
        std::string roomNR = list->GetItemText(id,0).ToStdString();
        int roomNRint = std::stoi(roomNR);
        if (parent->getConnection()->getLoggedPid() == ptr->getClient()->getId()) {
            if (to_simple_string(ptr->getBeginTime().date()) == beginDate && roomNRint == ptr->getRoom()->getId()) {
                return true;
            }
        }
        return false;
    });
    if (res.size() > 1) {
        return nullptr;
    }
    return res[0];
}

void ReservationPanel::Submit(wxCommandEvent &evt) {
    ReservationPtr ptr = getSelectedRes();
    ClientPtr client = ptr->getClient();

    if (medium->GetValue()) {
        parent->getResM()->changeReservationExtraBonusToB(ptr->getId());
    } else if (extra->GetValue()) {
        parent->getResM()->changeReservationExtraBonusToC(ptr->getId());
    }

    parent->getResM()->updateExtraBonusToDB(parent->getConnection(),ptr);
    parent->RefreshAllPanelsBalance();
    parent->getConnection()->updateBalance(std::to_string(client->getBalance()));
    this->filter = !this->filter;
    wxCommandEvent nullEvt;
    ChangeClicked(nullEvt);
    evt.Skip();
}

void ReservationPanel::RefreshRefund() {
    ReservationPtr ptr = getSelectedRes();
    price->SetForegroundColour(*wxBLACK);
    priceInfo->SetLabel("Refund: ");

    if (ptr->getBeginTime().date() <= pt::second_clock::local_time().date()) {
        submit2->Hide();
        price->Hide();
        priceInfo->SetLabel("Can't cancel ongoing reservations");
        this->Layout();
        return;
    }
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << ptr->getTotalReservationCost()*0.6;
    price->SetLabel(ss.str());
}

void ReservationPanel::Submit2(wxCommandEvent &evt) {
    ReservationPtr ptr = getSelectedRes();
    ClientPtr client = ptr->getClient();
        try {
        parent->getResM()->removeReservation(ptr->getId());
        std::stringstream ss;
        ss <<  ptr->getClient()->getId() << "#" << ptr->getRoom()->getId() << "#" << to_simple_string(ptr->getBeginTime());
        std::string message = ss.str();
        parent->getResM()->removeFromDB(parent->getConnection(),message);
        HideOptions();

        client->setBalance(client->getBalance() + ptr->getTotalReservationCost()*0.6);
        parent->RefreshAllPanelsBalance();
        parent->getConnection()->updateBalance(std::to_string(client->getBalance()));

        this->filter=!this->filter;
        wxCommandEvent nullEvt;
        ChangeClicked(nullEvt);
    } catch (std::exception &e){
    }
    evt.Skip();
}
