//
// Created by student on 01.02.2023.
//
#include "wx/datetime.h"
#include "cMain.h"
#include "RoomsPanel.h"
#include "SimpleRoomVirtualListControl.h"
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
wxEND_EVENT_TABLE()

RoomsPanel::~RoomsPanel() = default;

RoomsPanel::RoomsPanel(cMain *parent) : baseLoggedPanel(parent) {
    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);
    info = new wxStaticText(this,wxID_ANY,"Choose a room and make a reservation");
    info->SetForegroundColour(*wxBLUE);
    dateErr = new wxStaticText(this,wxID_ANY,"");
    dateErr->SetForegroundColour(*wxRED);
    dateErr->Hide();

    wxButton* retButton = new wxButton(this,1001,"<-- MENU");

    wxStaticText* from = new wxStaticText(this,wxID_ANY,"From: ");
    wxStaticText* to = new wxStaticText(this,wxID_ANY,"To: ");
    basicListView = new SimpleRoomVirtualListControl(this, 1005, wxDefaultPosition, wxSize(550, 200));


    begin = new wxDatePickerCtrl(this,wxID_ANY);
    begin->SetMinSize(wxSize(115,30));
    end = new wxDatePickerCtrl(this,wxID_ANY,begin->GetValue().SetDay(begin->GetValue().GetDay() + 1));
    end->SetMinSize(wxSize(115,30));



    medium = new wxCheckBox(this,wxID_ANY,"breakfast");
    extra = new wxCheckBox(this,wxID_ANY,"breakfast and dinner");
    price = new wxStaticText(this,wxID_ANY,"");
    medium->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        extra->SetValue(false);
    });
    extra->Bind(wxEVT_CHECKBOX,[this](wxCommandEvent& evt){
        medium->SetValue(false);
    });
    medium->Hide();
    extra->Hide();




    typeResSizer = new wxBoxSizer(wxHORIZONTAL);
    typeResSizer->Add(medium,0,wxRIGHT,10);
    typeResSizer->Add(extra,0,wxLEFT,10);


    searchButton = new wxButton(this,1002,"Search");

    horizontalSizer2->Add(from,0,wxALIGN_CENTER|wxLEFT,5);
    horizontalSizer2->Add(begin,0,wxALIGN_CENTER|wxRIGHT,25);
    horizontalSizer2->Add(to,0,wxALIGN_CENTER|wxLEFT,5);
    horizontalSizer2->Add(end,0,wxALIGN_CENTER,5);

    verticalSizer->Add(info,0,wxALIGN_CENTER|wxTOP,5);
    verticalSizer->Add(horizontalSizer2,0,wxALIGN_CENTER|wxTOP,20);
    verticalSizer->Add(dateErr,0,wxALIGN_CENTER_HORIZONTAL|wxTOP,5);
    verticalSizer->Add(searchButton,0,wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxTOP, 15);
    verticalSizer->Add(basicListView,0,wxALIGN_CENTER|wxLEFT|wxTOP,5);
    verticalSizer->Add(typeResSizer,0,wxALIGN_CENTER|wxTOP,10);
    verticalSizer->Add(price,0,wxALIGN_CENTER|wxTOP,5);
    verticalSizer->Add(retButton,0,wxALIGN_LEFT|wxTOP|wxBOTTOM|wxLEFT,7);
    this->SetSizer(verticalSizer);
//    verticalSizer->Add(info,1,wxALIGN_CENTER_HORIZONTAL);
//    verticalSizer->Add(retButton,1,wxALIGN_CENTER_HORIZONTAL);
//    this->SetSizer(verticalSizer);
//

    basicListView->Bind(wxEVT_LIST_ITEM_SELECTED,[this](wxListEvent& evt) {
        this->medium->Show();
        this->extra->Show();
        RefreshPrice();
        this->Layout();
    });
    basicListView->Hide();
}
void RoomsPanel::ReturnClicked(wxCommandEvent &evt) {
    basicListView->Hide();
    medium->Hide();
    extra->Hide();
    price->Hide();
    parent->changePanels(3);
    evt.Skip();
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
        dateErr->SetLabel("'From' date must be before the 'To' date");
        dateErr->Show();
        this->Layout();
        return;
    } else if (PTfrom_time.date() < pt::second_clock::local_time().date()) {
        basicListView->Hide();
        dateErr->SetLabel("Date period can't begin in the past");
        dateErr->Show();
        this->Layout();
        return;
    } else if ( end->GetValue().Subtract(begin->GetValue()).GetDays() > client->getMaxDays())
    {
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
                    if (std::find_if(resvs.begin(),resvs.end(),[a](const ReservationPtr& ptr) {
                        return ptr->getRoom() == a;
                    }) == resvs.end()) {
                        return true;
                    }
                    return !RM->isRoomOccupied(a,PTfrom_time,(PTto_time-PTfrom_time).hours()/24);
                    });
    } catch (std::exception& e) {
        std::cout << e.what();
    }
    long selectedListIndex = basicListView->getFirstSelectedIndex();
    basicListView->SetItemState(selectedListIndex,0,wxLIST_STATE_SELECTED);
    chosenBegin = begin->GetValue();
    chosenEnd = end->GetValue();
    basicListView->Show();
    this->Layout();

    evt.Skip();
}

std::string RoomsPanel::FormatDate(wxDateTime date) {
    return date.FormatISOCombined().ToStdString().replace(10,1," ");
}

void RoomsPanel::RefreshPrice() {
    std::string from_time = FormatDate(begin->GetValue());
    pt::ptime PTfrom_time =  pt::time_from_string(from_time);
    std::string loggedPid = parent->getConnection()->getLoggedPid();

    ReservationRepositoryPtr currRes = std::make_shared<ReservationRepository>();
    ReservationRepositoryPtr archRes = std::make_shared<ReservationRepository>();
    ReservationManager test(currRes,archRes);

    long id = basicListView->getFirstSelectedIndex();
    std::string nr = basicListView->GetItemText(id,0).ToStdString();
    int roomNR = std::stoi(nr);

    ClientPtr client = parent->getCm()->getClient(loggedPid);
    RoomPtr room = parent->getRoomM()->getRoom(roomNR);
    int Days_of_res = chosenEnd.Subtract(chosenBegin).GetDays();

    try {
        test.startReservation(client, room, room->getBedCount(), PTfrom_time, Days_of_res, A);
        double pr = test.findClientReservations(client)[0]->getTotalReservationCost();
        std::stringstream string;
        string << std::fixed << std::setprecision(2) << pr;
        price->SetLabel(string.str());
        price->Show();
    } catch(std::exception &e) {
        std::cout<<e.what();
    }



}
