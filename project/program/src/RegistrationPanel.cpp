#include "RegistrationPanel.h"
#include "gMain.h"
#include "exceptions/ClientError.h"
#include "model/ShortTerm.h"

RegistrationPanel::RegistrationPanel(gMain* parent) : baseLogRegistPanel(parent)
{


    this->SetBackgroundColour(wxColour(252, 242, 238));
    info = new wxStaticText(this,wxID_ANY,"",wxDefaultPosition,wxSize(175,30));
    info->SetForegroundColour(*wxRED);
    pid = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);
    pid->SetHint("pid");
    firstName = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);
    firstName->SetHint("firstName");
    lastName = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);
    lastName->SetHint("lastName");
    passwd = new wxTextCtrl(this, 10001,"",wxDefaultPosition,wxSize(175,30),wxTE_PASSWORD|wxTE_CENTRE);
    passwd->SetHint("passwd");


    login = new wxButton(this, 10003,"login",wxDefaultPosition,wxSize(125,30));

    submit = new wxButton(this, 10002 ,"submit",wxDefaultPosition,wxSize(125,30));
    submit->SetFocus();

    verticalSizer = new wxBoxSizer(wxVERTICAL);
    horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);
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
    std::string pidStr = pid->GetValue().ToStdString();
    std::string fnameStr = firstName->GetValue().ToStdString();
    std::string lnameStr = lastName->GetValue().ToStdString();
    std::string passwdStr = passwd->GetValue().ToStdString();
    std::cout<<pidStr<<"\n";
    try {
        parent->getCm()->registerClient(pidStr,fnameStr,lnameStr);
        info->SetForegroundColour(*wxGREEN);
        info->SetLabel("success");
    } catch (const ClientError& err) {
        info->SetForegroundColour(*wxRED);
        info->SetLabel(err.what());
    }
    evt.Skip();
}

void RegistrationPanel::OnRegistClicked(wxCommandEvent &evt) {
    parent->changePanels(1);
    evt.Skip();
}

void RegistrationPanel::OnPasswdWrite(wxCommandEvent &evt) {
    if(passwd->GetWindowStyleFlag()==wxTE_CENTER) {
        passwd->SetWindowStyleFlag(wxTE_PASSWORD | wxTE_CENTER);
    }
    evt.Skip();
}
