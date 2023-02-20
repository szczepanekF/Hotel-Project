#include "RegistrationPanel.h"
#include "cMain.h"
#include "exceptions/ClientError.h"
#include "model/ShortTerm.h"
#include "model/Client.h"

RegistrationPanel::RegistrationPanel(cMain* parent) : baseLogRegistPanel(parent)
{
    this->SetBackgroundColour(wxColour(252, 242, 238));
    info = new wxStaticText(this,wxID_ANY,"",wxDefaultPosition,wxSize(175,30));
    info->SetForegroundColour(*wxRED);
    pid = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);
    firstName = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);

    lastName = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);


    passwd = new wxTextCtrl(this, 10001,"",wxDefaultPosition,wxSize(175,30));
    setHints();

    login = new wxButton(this, 10003,"login",wxDefaultPosition,wxSize(125,30));

    submit = new wxButton(this, 10002 ,"submit",wxDefaultPosition,wxSize(125,30));
    submit->SetFocus();



    horizontalSizer2->Add(login,1,wxALIGN_CENTER|wxALL,1);
    horizontalSizer2->Add(submit,1,wxALIGN_CENTER|wxALL,1);
    verticalSizer->Add(info,0,wxALIGN_CENTER);
    verticalSizer->Add(pid,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(firstName,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(lastName,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(passwd,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(horizontalSizer2,1,wxALIGN_CENTER|wxALL, 10);
    horizontalSizer->Add(verticalSizer,1,wxALIGN_CENTER|wxALL,25);

    this->SetSizer(horizontalSizer);
}
RegistrationPanel::~RegistrationPanel() {}

void RegistrationPanel::OnSubmitClicked(wxCommandEvent &evt) {

    if(parent->getConnection()->getConnSuccess()<0) {
        info->SetForegroundColour(*wxRED);
        info->SetLabel("no connection");
        return;
    }
    std::string pidStr = pid->GetValue().ToStdString();
    std::string fnameStr = firstName->GetValue().ToStdString();
    std::string lnameStr = lastName->GetValue().ToStdString();
    std::string passwdStr = passwd->GetValue().ToStdString();


    if (pidStr.find("#") != std::string::npos || passwdStr.find("#") !=std::string::npos ||
    fnameStr.find("#") != std::string::npos || lnameStr.find("#") != std::string::npos) {
        info->SetLabel("'#' sign is not allowed");
        evt.Skip();
        return;
    }

    if (pidStr.length() == 0 || fnameStr.length() == 0 || lnameStr.length() == 0 || passwdStr.length() ==0) {
        info->SetLabel("fill all info");
        evt.Skip();
        return;
    }

    if (passwdStr.length() <3) {
        info->SetLabel("Password is too short (min. 3 characters)");
        evt.Skip();
        return;
    }

    try {
        parent->getCm()->registerClient(fnameStr,lnameStr,pidStr);

        std::string combined = parent->getCm()->getClient(pidStr)->toDBInfo()+"#"+passwdStr;
        parent->getCm()->addClientToDB(parent->getConnection(),combined);
        parent->getConnection()->setLoggedPid(pidStr);
        info->SetForegroundColour(*wxGREEN);
        info->SetLabel("success");
        parent->RefreshAfterLogging();
        parent->changePanels(3);
    } catch (const ClientError& err) {
        std::string errors = err.what();
//        errors[20] = '\0';
        info->SetLabel(errors);
    }

    parent->Layout();

    evt.Skip();
}

void RegistrationPanel::OnRegistClicked(wxCommandEvent &evt) {
    parent->changePanels(1);
    setHints();
    evt.Skip();
}

void RegistrationPanel::OnPasswdWrite(wxCommandEvent &evt) {
    if(passwd->GetWindowStyleFlag()==wxTE_CENTER) {
        passwd->SetWindowStyleFlag(wxTE_PASSWORD | wxTE_CENTER);
    }
    evt.Skip();
}

void RegistrationPanel::setHints() {
    baseLogRegistPanel::setHints();
    firstName->Clear();
    firstName->SetHint("firstName");

    lastName->Clear();
    lastName->SetHint("lastName");
}
