//
// Created by student on 01.02.2023.
//

#include "RoomsPanel.h"
#include "gMain.h"
#include "SimpleVirtualListControl.h"
#include "model/Room.h"
#include <sstream>
#include "model/RoomWithoutTerrace.h"
#include "model/RoomWithTerrace.h"
#include "wx/datetime.h"

wxBEGIN_EVENT_TABLE(RoomsPanel,wxPanel)
                EVT_BUTTON(1001,RoomsPanel::ReturnClicked)

wxEND_EVENT_TABLE()

RoomsPanel::~RoomsPanel() {

}

RoomsPanel::RoomsPanel(gMain *parent) : basePanel(parent) {
    wxStaticText* info = new wxStaticText(this,wxID_ANY,"Choose a room and make a reservation");
    wxButton* retButton = new wxButton(this,1001,"<-- MENU");


    basicListView = new SimpleVirtualListControl(this,wxID_ANY,wxDefaultPosition,wxSize(550,200));
    begin = new wxDatePickerCtrl(this,wxID_ANY);
    begin->SetLabel("From:");
    end = new wxDatePickerCtrl(this,wxID_ANY);
    end->SetLabel("To:");
//    wxDateTime CheckIn = begin->GetValue();
//    wxTimeSpan oneMonth(30,0,0,0);
//    end->SetRange(CheckIn,CheckIn.Subtract(oneMonth));

    horizontalSizer->Add(begin,0,wxALIGN_CENTER_HORIZONTAL|wxTOP,5);
    horizontalSizer->Add(end,0,wxALIGN_CENTER_HORIZONTAL|wxLEFT|wxTOP,5);


    verticalSizer->Add(info,0,wxALIGN_CENTER);
    verticalSizer->Add(horizontalSizer,0,wxALIGN_CENTER|wxTOP|wxBottom,20);
    verticalSizer->Add(basicListView,0,wxALIGN_CENTER|wxLEFT|wxTOP,10);

    verticalSizer->Add(retButton,0,wxALIGN_LEFT|wxTOP|wxBOTTOM|wxLEFT,7);
    this->SetSizer(verticalSizer);
//    verticalSizer->Add(info,1,wxALIGN_CENTER_HORIZONTAL);
//    verticalSizer->Add(retButton,1,wxALIGN_CENTER_HORIZONTAL);
//    this->SetSizer(verticalSizer);
    populateListView();
    basicListView->Hide();
}
void RoomsPanel::ReturnClicked(wxCommandEvent &evt) {

//    parent->changePanels(3);
    basicListView->Show();
    this->Layout();
//    verticalSizer->Replace(info,basicListView)
    evt.Skip();
}

void RoomsPanel::populateListView() {
    std::vector<RoomPtr> rooms;
    try {
         rooms = parent->getRoomM()->findAllRooms();
    } catch (std::exception& e) {

    }
    double x;
    std::vector<ItemData> items;

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

