//
// Created by student on 08.01.2023.
//

#include "SettingsPanel.h"
#include "gMain.h"
wxBEGIN_EVENT_TABLE(SettingsPanel,wxPanel)
                EVT_BUTTON(1001,SettingsPanel::ReturnClicked)

wxEND_EVENT_TABLE()
SettingsPanel::SettingsPanel(gMain *parent) : basePanel(parent) {
    wxStaticText* info = new wxStaticText(this,wxID_ANY,"Settings",wxDefaultPosition,wxSize(175,30));
    wxButton* retButton = new wxButton(this,1001,"MENU",wxDefaultPosition,wxSize(150,30));


    verticalSizer->Add(info,1,wxALIGN_CENTER|wxALL,5);
    verticalSizer->Add(retButton,1, wxALIGN_CENTER|wxALL,5);
    horizontalSizer->Add(verticalSizer,1,wxALIGN_CENTER|wxALL,25);
//    horizontalSizer->Add(retButton,1, wxALL,5);

    this->SetSizer(horizontalSizer);

}

SettingsPanel::~SettingsPanel() {

}

void SettingsPanel::ReturnClicked(wxCommandEvent &evt) {
    parent->changePanels(3);
    evt.Skip();
}
