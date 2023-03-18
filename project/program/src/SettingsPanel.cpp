//
// Created by student on 08.01.2023.
//

#include <wx/popupwin.h>
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
                EVT_BUTTON(1006,SettingsPanel::accountTypeInfo)
wxEND_EVENT_TABLE()
SettingsPanel::SettingsPanel(cMain *parent) : baseLoggedPanel(parent) {
    wxStaticText* info = new wxStaticText(this,wxID_ANY,"SETTINGS");
    info->SetForegroundColour(*wxBLUE);
    wxFont* tekst = new wxFont();
    tekst->SetWeight(wxFONTWEIGHT_BOLD);
    info->SetFont(*tekst);
    wxStaticText* moneyChangeInfo = new wxStaticText(this,wxID_ANY,"Set payment amount");
    removeMoney = new wxButton(this, 1003,"-500");
    addMoney = new wxButton(this, 1002,"+500");
    errInfoMsg = new wxStaticText(this,wxID_ANY,"Not enough money");
    errInfoMsg->SetForegroundColour(*wxRED);
    errInfoMsg->Hide();

    standard = new wxButton(this, 1004,"-Gold-\n(-300)");
    longTerm = new wxButton(this, 1005,"-Diamond-\n(-500)");
    wxStaticText* changeType = new wxStaticText(this,wxID_ANY,"Upgrade account");

    wxButton* infoButton = new wxButton(this,1006,"i");

    infoButton->SetMaxSize(wxSize(25,25));


    wxButton* retButton = new wxButton(this,1001,"<-- MENU");

    changeMoneyAmountSizer = new wxBoxSizer(wxHORIZONTAL);
    changeMoneyAmountSizer->Add(removeMoney,0,wxRIGHT,10);
    changeMoneyAmountSizer->Add(addMoney,0,wxLEFT,10);

    clientTypeInfoSizer = new wxBoxSizer(wxHORIZONTAL);
    clientTypeInfoSizer->Add(changeType,0,wxALIGN_CENTER|wxRIGHT,5);
    clientTypeInfoSizer->Add(infoButton,0,wxALIGN_CENTER|wxLEFT,5);

    clientTypeSizer = new wxBoxSizer(wxHORIZONTAL);
    clientTypeSizer->Add(standard,0,wxALIGN_CENTER|wxRIGHT,10);
    clientTypeSizer->Add(longTerm,0,wxALIGN_CENTER|wxLEFT,10);


    verticalSizer->Add(info,0,wxALIGN_CENTER,50);
    verticalSizer->Add(moneyChangeInfo,0,wxALIGN_CENTER|wxTOP,50);
    verticalSizer->Add(changeMoneyAmountSizer,0,wxALIGN_CENTER|wxTOP|wxBOTTOM,20);

    verticalSizer->Add(clientTypeInfoSizer,0,wxALIGN_CENTER|wxTOP,30);
    verticalSizer->Add(clientTypeSizer,0,wxALIGN_CENTER|wxTOP,15);
    verticalSizer->Add(errInfoMsg,0,wxALIGN_CENTER|wxTOP|wxBOTTOM,10);

    verticalSizer->Add(retButton,0, wxLEFT|wxTOP,40);

    this->SetSizer(verticalSizer);
}




void SettingsPanel::ReturnClicked(wxCommandEvent &evt) {
    errInfoMsg->Hide();
    evt.Skip();
    parent->changePanels(3);
}

void SettingsPanel::standardClicked(wxCommandEvent &evt) {
    try {
        parent->getCm()->changeClientTypetoStandard(client->getId());
    } catch (std::exception &e) {
        errInfoMsg->Show();
        this->Layout();
        return;
    }
    parent->getConnection()->updateType("1");
    errInfoMsg->Hide();
    Refresh();
    parent->getConnection()->updateBalance(std::to_string(client->getBalance()));
    evt.Skip();
}

void SettingsPanel::longClicked(wxCommandEvent &evt) {
    try {
        parent->getCm()->changeClientTypetoLongTerm(client->getId());
    } catch (std::exception &e) {
        errInfoMsg->Show();
        this->Layout();
        return;
    }
    parent->getConnection()->updateType("2");
    errInfoMsg->Hide();
    Refresh();
    parent->getConnection()->updateBalance(std::to_string(client->getBalance()));

    evt.Skip();
}

void SettingsPanel::setClient(const ClientPtr &client) {
    SettingsPanel::client = client;
}

void SettingsPanel::RefreshValue() {
    parent->RefreshAllPanelsBalance();
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

    client->setBalance(client->getBalance() + 500);
    RefreshValue();
    parent->getConnection()->updateBalance(std::to_string(client->getBalance()));
    evt.Skip();
}

void SettingsPanel::remove(wxCommandEvent &evt) {
    if (client->getBalance() - 500 < 0) {
        client->setBalance(0);
    } else {
        client->setBalance(client->getBalance() - 500);
    }
    RefreshValue();
    parent->getConnection()->updateBalance(std::to_string(client->getBalance()));
    evt.Skip();
}

void SettingsPanel::accountTypeInfo(wxCommandEvent &evt) {
    evt.Skip();


    wxDialog* dlg = new wxDialog(this,wxID_ANY,"INFORMATION");
    dlg->SetSize(wxSize(300,200));
    dlg->SetBackgroundColour(*wxWHITE);
    wxStaticText* dialogInfo = new wxStaticText(dlg,wxID_ANY,"Base account - reservations up to 2 days; discounts are not applied\n\n"
                                                             "Gold account - reservations up to 14 days; discounts are applied\n\n"
                                                             "Diamon account - reservations up to 30 days; discounts are applied");
    dialogInfo ->Show();
    dlg->ShowModal();
}


