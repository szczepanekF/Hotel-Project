#include "baseLogRegistPanel.h"
#include "cMain.h"
wxBEGIN_EVENT_TABLE(baseLogRegistPanel,wxPanel)
                EVT_TEXT(10001,baseLogRegistPanel::OnPasswdWrite)
                EVT_BUTTON(10002,baseLogRegistPanel::OnSubmitClicked)
                EVT_BUTTON(10003,baseLogRegistPanel::OnRegistClicked)

wxEND_EVENT_TABLE()

baseLogRegistPanel::baseLogRegistPanel(cMain* parent) : basePanel(parent)
{
    horizontalSizer2 = new wxBoxSizer(wxHORIZONTAL);
}
baseLogRegistPanel::~baseLogRegistPanel() {

}

void baseLogRegistPanel::setHints() {
    info->SetLabel("");
    pid->Clear();
    pid->SetHint("login");
    passwd->Clear();
    passwd->SetWindowStyleFlag(wxTE_CENTER);
    passwd->SetHint("password");

}

wxButton *baseLogRegistPanel::getRegist() const {
    return regist;
}
