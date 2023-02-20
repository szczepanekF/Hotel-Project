//
// Created by student on 08.01.2023.
//

#include "SettingsPanel.h"
#include "cMain.h"
#include "model/Client.h"
#include "model/Standard.h"
#include "model/LongTerm.h"

wxBEGIN_EVENT_TABLE(SettingsPanel,wxPanel)
                EVT_BUTTON(1001,SettingsPanel::ReturnClicked)
                EVT_BUTTON(1002,SettingsPanel::add)
                EVT_BUTTON(1003,SettingsPanel::remove)
                EVT_BUTTON(1004,SettingsPanel::standardClicked)
                EVT_BUTTON(1005,SettingsPanel::longClicked)

wxEND_EVENT_TABLE()
SettingsPanel::SettingsPanel(cMain *parent) : baseLoggedPanel(parent) {
    wxStaticText* info = new wxStaticText(this,wxID_ANY,"SETTINGS");
    info->SetForegroundColour(*wxBLUE);

    wxStaticText* moneyChangeInfo = new wxStaticText(this,wxID_ANY,"Set payment amount");
    removeMoney = new wxButton(this, 1003,"-500");
    addMoney = new wxButton(this, 1002,"+500");
    value = new wxStaticText(this,wxID_ANY,"");
    value->SetForegroundColour(*wxGREEN);
    standard = new wxButton(this, 1004,"Standard\n(-300)");
    longTerm = new wxButton(this, 1005,"Long term\n(-500)");
    changeMoneyAmountSizer = new wxBoxSizer(wxHORIZONTAL);
    changeMoneyAmountSizer->Add(removeMoney,0,wxRIGHT,10);
    changeMoneyAmountSizer->Add(value,0,wxTOP,7);
    changeMoneyAmountSizer->Add(addMoney,0,wxLEFT,10);

    wxStaticText* changeType = new wxStaticText(this,wxID_ANY,"Change client Type");




    clientTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    clientTypeSizer->Add(standard,0,wxRIGHT,10);
    clientTypeSizer->Add(longTerm,0,wxLEFT,10);




    wxButton* retButton = new wxButton(this,1001,"<-- MENU");

    verticalSizer->Add(info,0,wxALIGN_CENTER|wxTOP,20);
    verticalSizer->Add(moneyChangeInfo,0,wxALIGN_CENTER|wxTOP,50);
    verticalSizer->Add(changeMoneyAmountSizer,0,wxALIGN_CENTER|wxTOP|wxBOTTOM,20);
    verticalSizer->Add(changeType,0,wxALIGN_CENTER|wxTOP,30);
    verticalSizer->Add(clientTypeSizer,0,wxALIGN_CENTER|wxTOP,15);

    verticalSizer->Add(retButton,0, wxLEFT|wxTOP,40);


//    horizontalSizer->Add(retButton,1, wxALL,5);

    this->SetSizer(verticalSizer);

}



SettingsPanel::~SettingsPanel() {

}

void SettingsPanel::ReturnClicked(wxCommandEvent &evt) {
    parent->changePanels(3);
    evt.Skip();
}

void SettingsPanel::standardClicked(wxCommandEvent &evt) {
    try {
        parent->getCm()->changeClientTypetoStandard(client->getId());
        parent->getConnection()->updateType("1");
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
    Refresh();
    parent->getConnection()->updateBill(value->GetLabel().ToStdString());
    evt.Skip();
}

void SettingsPanel::longClicked(wxCommandEvent &evt) {
    try {
        parent->getCm()->changeClientTypetoLongTerm(client->getId());
        parent->getConnection()->updateType("2");
    } catch (std::exception &e) {
        std::cout<<e.what();
    }
    Refresh();
    parent->getConnection()->updateBill(value->GetLabel().ToStdString());
    evt.Skip();
}

void SettingsPanel::setClient(const ClientPtr &client) {
    SettingsPanel::client = client;
}

void SettingsPanel::RefreshValue() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << client->getBill();
    value->SetLabel(ss.str());
    this->Layout();

}

void SettingsPanel::Refresh() {
    RefreshValue();
    std::shared_ptr<LongTerm> temp2 = std::dynamic_pointer_cast<LongTerm>(client->getClientType());
    if (temp2 != nullptr) {
        standard->Disable();
        longTerm->Disable();
        return;
    }
    std::shared_ptr<Standard> temp = std::dynamic_pointer_cast<Standard>(client->getClientType());
    if (temp != nullptr) {
        standard->Disable();


    }
}

void SettingsPanel::add(wxCommandEvent &evt) {
    client->setBill(client->getBill()+500);
    RefreshValue();
    parent->getConnection()->updateBill(value->GetLabel().ToStdString());
    evt.Skip();
}

void SettingsPanel::remove(wxCommandEvent &evt) {
    if (client->getBill()-500 < 0) {
        client->setBill(0);
    } else {
        client->setBill(client->getBill() - 500);
    }
    RefreshValue();
    parent->getConnection()->updateBill(value->GetLabel().ToStdString());
    evt.Skip();
}


