//
// Created by student on 20.02.2023.
//

#include "baseLoggedPanel.h"
#include "cMain.h"
#include "model/Client.h"
#include "sstream"

baseLoggedPanel::baseLoggedPanel(cMain *parent) : basePanel(parent) {


}

baseLoggedPanel::~baseLoggedPanel() {

}

void baseLoggedPanel::RefreshAfterLogging() {
    std::string log = parent->getConnection()->getLoggedPid();
    ClientPtr ptr = parent->getCm()->getClient(log);
    std::string Fname = ptr->getFirstName();
    std::string Lname = ptr->getLastName();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << ptr->getBill();

    wxStaticText* helpText = new wxStaticText(this,wxID_ANY,"Your balance: ");

    balanceInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    fname = new wxStaticText(this,wxID_ANY,Fname);
    lname = new wxStaticText(this,wxID_ANY,Lname);
    balance = new wxStaticText(this,wxID_ANY,ss.str());



    horizontalSizer->Add(fname,0,wxALIGN_CENTER|wxALL,2);
    horizontalSizer->Add(lname,0,wxALIGN_CENTER|wxALL,2);
    balanceInfoSizer->Add(helpText,0,wxALIGN_CENTER|wxALL,2);
    balanceInfoSizer->Add(balance,0,wxALIGN_CENTER|wxALL,2);

    verticalSizer->Prepend(balanceInfoSizer,0,wxALIGN_RIGHT|wxRIGHT,10);
    verticalSizer->Prepend(horizontalSizer,0,wxALIGN_RIGHT|wxRIGHT|wxTOP,10);



}
