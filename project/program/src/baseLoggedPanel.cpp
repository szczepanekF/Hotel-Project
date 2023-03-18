//
// Created by student on 20.02.2023.
//

#include "baseLoggedPanel.h"
#include "cMain.h"
#include "model/Client.h"
#include "sstream"

baseLoggedPanel::baseLoggedPanel(cMain *parent) : basePanel(parent) {
    balanceInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    verticalSizer->Add(horizontalSizer,0,wxALIGN_RIGHT|wxRIGHT|wxTOP,10);
    verticalSizer->Add(balanceInfoSizer,0,wxALIGN_RIGHT|wxRIGHT,10);
}


void baseLoggedPanel::SetOnLogging() {
    horizontalSizer->Clear(true);
    balanceInfoSizer->Clear(true);
    std::string log = parent->getConnection()->getLoggedPid();
    ClientPtr ptr = parent->getCm()->getClient(log);
    std::string Fname = ptr->getFirstName();
    std::string ClientType = ptr->getClientType()->getClientTypeInfo();
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << ptr->getBalance();

    wxStaticText* helpText = new wxStaticText(this,wxID_ANY,"Your balance: ");


    fname = new wxStaticText(this,wxID_ANY,Fname);
    cType = new wxStaticText(this,wxID_ANY,ClientType);
    wxFont* tekst = new wxFont();
    tekst->SetWeight(wxFONTWEIGHT_HEAVY);

    cType->SetFont(*tekst);
    cType->SetForegroundColour(*wxRED);
    balance = new wxStaticText(this,wxID_ANY,ss.str());


    horizontalSizer->Add(cType,0,wxALIGN_CENTER|wxALL,2);
    horizontalSizer->Add(fname,0,wxALIGN_CENTER|wxALL,2);

    balanceInfoSizer->Add(helpText,0,wxALIGN_CENTER|wxALL,2);
    balanceInfoSizer->Add(balance,0,wxALIGN_CENTER|wxALL,2);
}

void baseLoggedPanel::RefreshBalance() {
    std::string log = parent->getConnection()->getLoggedPid();
    ClientPtr ptr = parent->getCm()->getClient(log);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << ptr->getBalance();
    std::string ClientType = ptr->getClientType()->getClientTypeInfo();
    balance->SetLabel(ss.str());
    cType->SetLabel(ClientType);

    this->Layout();
}
