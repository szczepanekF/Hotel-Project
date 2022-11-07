#include "baseLogRegistPanel.h"
#include "gMain.h"
wxBEGIN_EVENT_TABLE(baseLogRegistPanel,wxPanel)
                EVT_TEXT(10001,baseLogRegistPanel::OnPasswdWrite)
                EVT_BUTTON(10002,baseLogRegistPanel::OnSubmitClicked)
                EVT_BUTTON(10003,baseLogRegistPanel::OnRegistClicked)

wxEND_EVENT_TABLE()

baseLogRegistPanel::baseLogRegistPanel(gMain* parent) : parent(parent),wxPanel(parent)
{

}
baseLogRegistPanel::~baseLogRegistPanel() {

}