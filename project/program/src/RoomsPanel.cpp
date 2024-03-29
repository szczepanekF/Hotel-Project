//
// Created by student on 01.02.2023.
//
#include "wx/datetime.h"
#include "cMain.h"
#include "RoomsPanel.h"
#include "Lists/SimpleRoomVirtualListControl.h"
#include "model/Client.h"
#include "model/Room.h"
#include "model/RoomWithoutTerrace.h"
#include "model/RoomWithTerrace.h"
#include "managers/ReservationManager.h"
#include "repositories/ReservationRepository.h"
#include <sstream>

wxBEGIN_EVENT_TABLE(RoomsPanel,wxPanel)
                EVT_BUTTON(1001,RoomsPanel::ReturnClicked)
                EVT_BUTTON(1002,RoomsPanel::SearchClicked)
                EVT_BUTTON(1003,RoomsPanel::SubmitReservation)
wxEND_EVENT_TABLE()


RoomsPanel::RoomsPanel(cMain *parent) : baseLoggedPanel(parent) {


    info = new wxStaticText(this,wxID_ANY,"Choose a room and make a reservation");
    wxFont* tekst = new wxFont();
    tekst->SetWeight(wxFONTWEIGHT_BOLD);
    info->SetFont(*tekst);
    info->SetForegroundColour(*wxBLUE);



    wxStaticText* from = new wxStaticText(this,wxID_ANY,"From: ");
    begin = new wxDatePickerCtrl(this,wxID_ANY);
    begin->SetMinSize(wxSize(115,30));
    wxStaticText* to = new wxStaticText(this,wxID_ANY,"To: ");
    end = new wxDatePickerCtrl(this,wxID_ANY,begin->GetValue().SetDay(begin->GetValue().GetDay() + 1));
    end->SetMinSize(wxSize(115,30));

    dateErr = new wxStaticText(this,wxID_ANY,"");
    dateErr->SetForegroundColour(*wxRED);
    dateErr->Hide();

    searchButton = new wxButton(this,1002,"Search");

    basicListView = new SimpleRoomVirtualListControl(this, 1005, wxDefaultPosition, wxSize(550, 200));

    base = new wxCheckBox(this,wxID_ANY,"no maintenance");
    base->SetValue(true);
    base->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        if (!medium->GetValue() && !extra->GetValue()) {
            base->SetValue(true);
            return;
        }
        medium->SetValue(false);
        extra->SetValue(false);
        RefreshPrice();
    });
    base->Hide();
    medium = new wxCheckBox(this,wxID_ANY,"breakfast");
    medium->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        if (!base->GetValue() && !extra->GetValue()) {
            medium->SetValue(true);
            return;
        }
        base->SetValue(false);
        extra->SetValue(false);
        RefreshPrice();
    });
    medium->Hide();
    extra = new wxCheckBox(this,wxID_ANY,"breakfast and dinner");
    extra->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        if (!base->GetValue() && !medium->GetValue()) {
            extra->SetValue(true);
            return;
        }
        base->SetValue(false);
        medium->SetValue(false);
        RefreshPrice();
    });
    extra->Hide();


    submitRes = new wxButton(this,1003,"Pay and submit reservation");
    resPrice = new wxStaticText(this,wxID_ANY,"Reservation price: ");
    price = new wxStaticText(this,wxID_ANY,"");
    wxButton* retButton = new wxButton(this,1001,"<-- MENU");



    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);
    horizontalSizer2->Add(from,0,wxALIGN_CENTER|wxLEFT,5);
    horizontalSizer2->Add(begin,0,wxALIGN_CENTER|wxRIGHT,25);
    horizontalSizer2->Add(to,0,wxALIGN_CENTER|wxLEFT,5);
    horizontalSizer2->Add(end,0,wxALIGN_CENTER,5);

    typeResSizer = new wxBoxSizer(wxHORIZONTAL);
    typeResSizer->Add(base,0,wxRIGHT,10);
    typeResSizer->Add(medium,0,wxRIGHT|wxLEFT,10);
    typeResSizer->Add(extra,0,wxLEFT,10);

    priceSizer = new wxBoxSizer(wxHORIZONTAL);
    priceSizer->Add(resPrice,0,wxALIGN_CENTER|wxRIGHT,7);
    priceSizer->Add(price,0,wxALIGN_CENTER|wxRIGHT,10);
    priceSizer->Add(submitRes,0,wxALIGN_CENTER,0);

    verticalSizer->Add(info,0,wxALIGN_CENTER|wxTOP,5);
    verticalSizer->Add(horizontalSizer2,0,wxALIGN_CENTER|wxTOP,20);
    verticalSizer->Add(dateErr,0,wxALIGN_CENTER_HORIZONTAL|wxTOP,5);
    verticalSizer->Add(searchButton,0,wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxTOP, 15);
    verticalSizer->Add(basicListView,0,wxALIGN_CENTER|wxLEFT|wxTOP,5);
    verticalSizer->Add(typeResSizer,0,wxALIGN_CENTER|wxTOP,15);
    verticalSizer->Add(priceSizer,0,wxALIGN_RIGHT|wxTOP|wxRIGHT,5);
    verticalSizer->Add(retButton,0,wxALIGN_LEFT|wxTOP|wxBOTTOM|wxLEFT,7);
    this->SetSizer(verticalSizer);


    basicListView->Bind(wxEVT_LIST_ITEM_SELECTED,[this](wxListEvent& evt) {
        this->base->Show();
        this->medium->Show();
        this->extra->Show();

        RefreshPrice();
        this->Layout();
    });

    basicListView->Bind(wxEVT_LIST_ITEM_DESELECTED,[this](wxListEvent& evt) {
        HidePrice();
        this->Layout();
    });


    basicListView->Hide();
    HidePrice();
}
void RoomsPanel::ReturnClicked(wxCommandEvent &evt) {
    basicListView->Hide();
    HidePrice();
    evt.Skip();
    parent->changePanels(3);

}

void RoomsPanel::populateListView(RoomPredicate predicate) {
    std::vector<RoomPtr> rooms;
    try {
         rooms = parent->getRoomM()->findRooms(predicate);
    } catch (std::exception& e) {

    }
    double x;
    std::vector<RoomItemData> items;

    for (int i = 0; i < rooms.size(); i++) {
       x=0;
       std::shared_ptr<RoomWithTerrace> temp = std::dynamic_pointer_cast<RoomWithTerrace>(rooms[i]);
       if (temp != nullptr) {
           x = temp->getTerraceSurface();
       }

       items.push_back({rooms[i]->getId(),rooms[i]->getFinalPricePerNight(),rooms[i]->getBedCount(),x});
    }
    basicListView->setItems(items);
    basicListView->RefreshAfterUpdate();

}


void RoomsPanel::SearchClicked(wxCommandEvent &evt) {
    std::string from_time = FormatDate(begin->GetValue());
    std::string to_time = FormatDate(end->GetValue());
    pt::ptime PTfrom_time =  pt::time_from_string(from_time);
    pt::ptime PTto_time=  pt::time_from_string(to_time);
    ClientPtr client = parent->getCm()->getClient(parent->getConnection()->getLoggedPid());
    if (PTto_time <= PTfrom_time) {
        basicListView->Hide();
        HidePrice();
        dateErr->SetLabel("'From' date must be before the 'To' date");
        dateErr->Show();
        this->Layout();
        return;
    } else if (PTfrom_time.date() < pt::second_clock::local_time().date()) {
        basicListView->Hide();
        HidePrice();
        dateErr->SetLabel("Date period can't begin in the past");
        dateErr->Show();
        this->Layout();
        return;
    } else if ( end->GetValue().Subtract(begin->GetValue()).GetDays() > client->getMaxDays()) {
        HidePrice();
        std::stringstream ss;
        ss << "Upgrade your account to make reservation for more than " << client->getMaxDays() << " days";
        basicListView->Hide();
        dateErr->SetLabel(ss.str());
        dateErr->Show();
        this->Layout();
        return;
    } else {
        dateErr->SetLabel("");
        dateErr->Hide();
    }


    ReservationManagerPtr RM = parent->getResM();
    std::vector<ReservationPtr> resvs = RM->findAllReservations();
    try {
        populateListView([RM,resvs,PTfrom_time,PTto_time](RoomPtr a) {
                        /// znajdź jeśli nie ma żadnej rezerwacji tego pokoju, lub nie jest zajęty w tymczasie
                    if (std::find_if(resvs.begin(),resvs.end(),[a](const ReservationPtr& ptr) {
                        return ptr->getRoom() == a;
                    }) == resvs.end()) {
                        return true;
                    }
                    return !RM->isRoomOccupied(a,PTfrom_time,(PTto_time-PTfrom_time).hours()/24);
                    });
    } catch (std::exception& e) {
    }
    long selectedListIndex = basicListView->getFirstSelectedIndex();
    basicListView->SetItemState(selectedListIndex,0,wxLIST_STATE_SELECTED);
    chosenBegin = begin->GetValue();
    chosenEnd = end->GetValue();
    basicListView->Show();
    HidePrice();
    this->Layout();
    evt.Skip();
}

std::string RoomsPanel::FormatDate(wxDateTime date) {
    return date.FormatISOCombined().ToStdString().replace(10,1," ");
}

void RoomsPanel::RefreshPrice() {
    ReservationRepositoryPtr currRes = std::make_shared<ReservationRepository>();
    ReservationRepositoryPtr archRes = std::make_shared<ReservationRepository>();
    ReservationManager test(currRes,archRes);

    std::string from_time = FormatDate(begin->GetValue());
    pt::ptime PTfrom_time =  pt::time_from_string(from_time);
    std::string loggedPid = parent->getConnection()->getLoggedPid();
    ClientPtr client = parent->getCm()->getClient(loggedPid);

    long id = basicListView->getFirstSelectedIndex();
    std::string nr = basicListView->GetItemText(id,0).ToStdString();
    int roomNR = std::stoi(nr);
    RoomPtr room = parent->getRoomM()->getRoom(roomNR);

    int Days_of_res = chosenEnd.Subtract(chosenBegin).GetDays();

    extraBonusType x;
    if (!medium->GetValue() && !extra->GetValue()) {
        x = A;
    } else if (!extra->GetValue()) {
        x = B;
    } else {
        x = C;
    }

    ReservationManagerPtr resM = parent->getResM();
    try {
        ReservationPtr res = resM->readReservation(client, room, room->getBedCount(), PTfrom_time, Days_of_res, x);
        resM->removeReservation(res->getId());
        double pr = res->getTotalReservationCost();
        std::stringstream string;
        string << std::fixed << std::setprecision(2) << pr;
        price->SetLabel(string.str());
        price->Show();
        submitRes->Show();
        resPrice->Show();
        if (pr > client->getBalance()) {
            submitRes->Disable();
            price->SetForegroundColour(*wxRED);
        } else {
            submitRes->Enable();
            price->SetForegroundColour(*wxGREEN);
        }
        this->Layout();
    } catch(std::exception &e) {
    }



}

void RoomsPanel::HidePrice() {

    submitRes->Hide();
    resPrice->Hide();
    base->Hide();
    base->SetValue(true);
    medium->Hide();
    medium->SetValue(false);
    extra->Hide();
    extra->SetValue(false);
    price->Hide();
    this->Layout();
}

void RoomsPanel::SubmitReservation(wxCommandEvent &evt) {
    std::string loggedPid = parent->getConnection()->getLoggedPid();
    ClientPtr client = parent->getCm()->getClient(loggedPid);

    long id = basicListView->getFirstSelectedIndex();
    std::string nr = basicListView->GetItemText(id,0).ToStdString();
    int roomNR = std::stoi(nr);
    RoomPtr room = parent->getRoomM()->getRoom(roomNR);

    int Days_of_res = chosenEnd.Subtract(chosenBegin).GetDays();

    std::string from_time = FormatDate(begin->GetValue());
    pt::ptime PTfrom_time =  pt::time_from_string(from_time);

    extraBonusType x;
    if (!medium->GetValue() && !extra->GetValue()) {
        x = A;
    } else if (!extra->GetValue()) {
        x = B;
    } else {
        x = C;
    }

    try {
        ReservationPtr res = parent->getResM()->startReservation(client, room, room->getBedCount(), PTfrom_time, Days_of_res, x);
        parent->getConnection()->updateBalance(std::to_string(client->getBalance()));
        std::string info = res->toDBInfo();
        parent->getResM()->addReservationToDB(parent->getConnection(),info);
        basicListView->Hide();
        HidePrice();
        parent->RefreshAllPanelsBalance();
        basicListView->SetItemState(id,0,wxLIST_STATE_SELECTED);
        this->Layout();
    } catch(std::exception &e) {
    }

    evt.Skip();
}
