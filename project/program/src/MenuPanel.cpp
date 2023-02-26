#include "MenuPanel.h"
#include "cMain.h"
wxBEGIN_EVENT_TABLE(MenuPanel,wxPanel)
                EVT_BUTTON(10001,MenuPanel::SwitchToRes)
                EVT_BUTTON(10002,MenuPanel::SwitchToRooms)
                EVT_BUTTON(10003,MenuPanel::SwitchToSetting)
                EVT_BUTTON(10004,MenuPanel::Logout)
wxEND_EVENT_TABLE()

MenuPanel::MenuPanel(cMain *parent) : baseLoggedPanel(parent){

    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);
    buttons = new wxButton*[4];
    buttons[0] = new wxButton(this, 10001,"Your Reservations",wxDefaultPosition,wxSize(150,50));
    buttons[1] = new wxButton(this, 10002,"Rooms",wxDefaultPosition,wxSize(150,50));
    buttons[2] = new wxButton(this, 10003,"Settings",wxDefaultPosition,wxSize(150,50));
    buttons[3] = new wxButton(this,10004,"Log out");

    verticalSizer->Add(buttons[0] ,0,wxALIGN_CENTER|wxTOP,150);
    verticalSizer->Add(buttons[1] ,0,wxALIGN_CENTER|wxTOP|wxBOTTOM, 10);
    verticalSizer->Add(buttons[2] ,0,wxALIGN_CENTER|wxBOTTOM, 100);
    verticalSizer->Add(buttons[3] ,0,wxALIGN_LEFT|wxLEFT|wxBOTTOM, 10);
    horizontalSizer2->Add(verticalSizer,1,wxEXPAND,0);

    this->SetSizer(horizontalSizer2);

}



void MenuPanel::SwitchToRes(wxCommandEvent &evt) {
    evt.Skip();
    parent->changePanels(4);
}

void MenuPanel::SwitchToRooms(wxCommandEvent &evt) {
    evt.Skip();
    parent->changePanels(5);
}

void MenuPanel::SwitchToSetting(wxCommandEvent &evt) {
    evt.Skip();
    parent->changePanels(6);
}

void MenuPanel::Logout(wxCommandEvent &evt) {
    parent->getConnection()->setLoggedPid("");
    evt.Skip();
    parent->changePanels(1);
}
