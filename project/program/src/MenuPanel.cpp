#include "MenuPanel.h"
#include "gMain.h"
wxBEGIN_EVENT_TABLE(MenuPanel,wxPanel)
                EVT_BUTTON(10001,MenuPanel::SwitchToRes)
                EVT_BUTTON(10002,MenuPanel::SwitchToRooms)
                EVT_BUTTON(10003,MenuPanel::SwitchToSetting)

wxEND_EVENT_TABLE()

MenuPanel::MenuPanel(gMain *parent) : basePanel(parent){

    buttons = new wxButton*[4];
    buttons[0] = new wxButton(this, 10001,"Your Reservations",wxDefaultPosition,wxSize(150,50));
    buttons[1] = new wxButton(this, 10002,"Rooms",wxDefaultPosition,wxSize(150,50));
    buttons[2] = new wxButton(this, 10003,"Settings",wxDefaultPosition,wxSize(150,50));

    verticalSizer->Add(buttons[0] ,1,wxALIGN_CENTER|wxALL,5);
    verticalSizer->Add(buttons[1] ,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(buttons[2] ,1,wxALIGN_CENTER|wxALL, 5);
    horizontalSizer->Add(verticalSizer,1,wxALIGN_CENTER|wxALL,25);

    this->SetSizer(horizontalSizer);

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
