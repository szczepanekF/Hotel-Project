//
// Created by student on 01.02.2023.
//

#include "ReservationPanel.h"
#include "gMain.h"
wxBEGIN_EVENT_TABLE(ReservationPanel,wxPanel)
                EVT_BUTTON(1001,ReservationPanel::ReturnClicked)

wxEND_EVENT_TABLE()

ReservationPanel::ReservationPanel(gMain *parent) : basePanel(parent) {
    wxStaticText* info = new wxStaticText(this,wxID_ANY,"Your Reservations",wxDefaultPosition,wxSize(175,30));
    wxButton* retButton = new wxButton(this,1001,"MENU",wxDefaultPosition,wxSize(50,30));

    verticalSizer->Add(info,0,wxALIGN_CENTER_HORIZONTAL);
    verticalSizer->Add(retButton,0,wxALIGN_CENTER_HORIZONTAL);
    this->SetSizer(verticalSizer);
}

ReservationPanel::~ReservationPanel() {


}
void ReservationPanel::ReturnClicked(wxCommandEvent &evt) {
    parent->changePanels(3);
    evt.Skip();
}