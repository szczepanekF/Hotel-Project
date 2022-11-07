#include "LoginPanel.h"
#include "gMain.h"



LoginPanel::LoginPanel(gMain* parent) : baseLogRegistPanel(parent)
{
    this->SetBackgroundColour(wxColour(222,244,222));
    info = new wxStaticText(this,wxID_ANY,"",wxDefaultPosition,wxSize(175,30));
    info->SetForegroundColour(*wxRED);

    pid = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);
    pid->SetHint("pid");

    passwd = new wxTextCtrl(this, 10001,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTER);
    passwd->SetHint("passwd");

    regist = new wxButton(this, 10003,"register",wxDefaultPosition,wxSize(125,30));
    submit = new wxButton(this, 10002,"submit",wxDefaultPosition,wxSize(125,30));
    submit->SetFocus();

    verticalSizer = new wxBoxSizer(wxVERTICAL);
    horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);

    horizontalSizer2->Add(regist,1,wxALIGN_CENTER|wxALL,1);
    horizontalSizer2->Add(submit,1,wxALIGN_CENTER|wxALL,1);
    verticalSizer->Add(info,0,wxALIGN_CENTER);
    verticalSizer->Add(pid,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(passwd,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(horizontalSizer2,1,wxALIGN_CENTER|wxALL, 10);
    horizontalSizer->Add(verticalSizer,1,wxALIGN_CENTER|wxALL,25);

    this->SetSizer(horizontalSizer);
}

LoginPanel::~LoginPanel()  {}



void LoginPanel::OnPasswdWrite(wxCommandEvent &evt) {
    if(passwd->GetWindowStyleFlag()==wxTE_CENTER) {
        passwd->SetWindowStyleFlag(wxTE_PASSWORD | wxTE_CENTER);
    }

    evt.Skip();

}
void LoginPanel::OnSubmitClicked(wxCommandEvent &evt) {
    std::string pidstr = pid->GetValue().ToStdString();
    std::string password = passwd->GetValue().ToStdString();

    int success = parent->getConnection()->login(pidstr,password);

    if (success == -2) {
        info->SetLabel("no connection");
    }
    else if(success == -1) {
        info->SetLabel("no such client");
    } else if (success == 0)
    {
        info->SetLabel("bad password");
    }
    else {
        info->SetForegroundColour(*wxGREEN);
        info->SetLabel("success");
    }

    evt.Skip();
}
void LoginPanel::OnRegistClicked(wxCommandEvent &evt) {
    parent->changePanels(2);
    evt.Skip();
}


