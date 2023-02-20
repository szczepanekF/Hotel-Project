#include "MenuPanel.h"
#include "cMain.h"
wxBEGIN_EVENT_TABLE(MenuPanel,wxPanel)
                EVT_BUTTON(10001,MenuPanel::SwitchToRes)
                EVT_BUTTON(10002,MenuPanel::SwitchToRooms)
                EVT_BUTTON(10003,MenuPanel::SwitchToSetting)

wxEND_EVENT_TABLE()

MenuPanel::MenuPanel(cMain *parent) : baseLoggedPanel(parent){

    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);
    buttons = new wxButton*[4];
    buttons[0] = new wxButton(this, 10001,"Your Reservations",wxDefaultPosition,wxSize(150,50));
    buttons[1] = new wxButton(this, 10002,"Rooms",wxDefaultPosition,wxSize(150,50));
    buttons[2] = new wxButton(this, 10003,"Settings",wxDefaultPosition,wxSize(150,50));
//    wxPanel* test = new wxPanel(this,wxID_ANY);
//    test->SetBackgroundColour(*wxBLUE);


    verticalSizer->Add(buttons[0] ,0,wxALIGN_CENTER|wxTOP,150);
    verticalSizer->Add(buttons[1] ,0,wxALIGN_CENTER|wxTOP, 10);
    verticalSizer->Add(buttons[2] ,0,wxALIGN_CENTER|wxTOP, 10);
//    verticalSizer->Add(test,1,wxEXPAND|wxALL,5);
    horizontalSizer2->Add(verticalSizer,1,wxEXPAND,0);

    this->SetSizer(horizontalSizer2);

}

MenuPanel::~MenuPanel() {

}

void MenuPanel::SwitchToRes(wxCommandEvent &evt) {
    parent->changePanels(4);
    evt.Skip();
}

void MenuPanel::SwitchToRooms(wxCommandEvent &evt) {
    parent->changePanels(5);
    evt.Skip();
}

void MenuPanel::SwitchToSetting(wxCommandEvent &evt) {
    parent->changePanels(6);
    evt.Skip();
}
