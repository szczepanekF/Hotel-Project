#include "LoginPanel.h"
#include "cMain.h"
#include "exceptions/ClientError.h"


LoginPanel::LoginPanel(cMain* parent) : baseLogRegistPanel(parent)
{


    info = new wxStaticText(this,wxID_ANY,"",wxDefaultPosition,wxSize(175,30));
    info->SetForegroundColour(*wxRED);

    pid = new wxTextCtrl(this, wxID_ANY,"",wxDefaultPosition,wxSize(175,30),wxTE_CENTRE);

    passwd = new wxTextCtrl(this, 10001,"",wxDefaultPosition,wxSize(175,30));

    regist = new wxButton(this, 10003,"register",wxDefaultPosition,wxSize(125,30));
    submit = new wxButton(this, 10002,"submit",wxDefaultPosition,wxSize(125,30));


    setHints();
    regist->SetFocus();
    horizontalSizer2->Add(regist,1,wxALIGN_CENTER|wxALL,1);
    horizontalSizer2->Add(submit,1,wxALIGN_CENTER|wxALL,1);
    verticalSizer->Add(info,0,wxALIGN_CENTER);
    verticalSizer->Add(pid,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(passwd,1,wxALIGN_CENTER|wxALL, 5);
    verticalSizer->Add(horizontalSizer2,1,wxALIGN_CENTER|wxALL, 10);
    horizontalSizer->Add(verticalSizer,1,wxALIGN_CENTER|wxALL,25);

    this->SetSizer(horizontalSizer);
}




void LoginPanel::OnPasswdWrite(wxCommandEvent &evt) {
    if(passwd->GetWindowStyleFlag()==wxTE_CENTER) {
        passwd->SetWindowStyleFlag(wxTE_PASSWORD | wxTE_CENTER);
    }

    evt.Skip();

}
void LoginPanel::OnSubmitClicked(wxCommandEvent &evt) {
    std::string pidstr = pid->GetValue().ToStdString();
    std::string password = passwd->GetValue().ToStdString();


    if (parent->getConnection()->getConnSuccess()) {
        info->SetLabel("no connection");
        evt.Skip();
        return;
    }

    if (pidstr.empty()) {
        info->SetLabel("fill login");
        evt.Skip();
        return;
    }

    if (password.empty()) {
        info->SetLabel("fill password");
        evt.Skip();
        return;
    }


    int success = parent->getConnection()->login(pidstr, password);

    if(success == -1) {
        info->SetLabel("no such client");
    } else if (success == 0)
    {
        info->SetLabel("bad password");
    } else {
        parent->RefreshAllPanelsAfterLogging();
        parent->changePanels(3);
    }
    setHints();
    evt.Skip();
}
void LoginPanel::OnRegistClicked(wxCommandEvent &evt) {
    parent->changePanels(2);
    setHints();
    evt.Skip();
}


