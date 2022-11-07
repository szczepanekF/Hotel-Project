#include "gMain.h"
#include "repositories/ClientRepository.h"
#include "managers/ClientManager.h"
#include "typedefs.h"
#include "exceptions/ClientError.h"
#include "model/Client.h"
#include "RegistrationPanel.h"
#include "LoginPanel.h"

gMain::gMain(C_client* conn,ClientManagerPtr CM,RoomManagerPtr RoomM,ReservationManagerPtr ResM) :connection(conn),CM(CM),
                RoomM(RoomM),ResM(ResM),wxFrame(nullptr,wxID_ANY,"Hotel Reservation App",wxPoint(30,30),wxSize(800,600))
{

    connection->createConnection();
    panel2 = new RegistrationPanel(this);
    panel = new LoginPanel(this);
    panel2->Hide();

    boxsizer2 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxsizer2);
    boxsizer2->Add(panel,1,wxGROW);
    boxsizer2->Add(panel2,1,wxGROW);
//    connection->sendMessage("242544");
}

gMain::~gMain() {
    delete connection;
}
/*
void gMain::errorMessage(std::string message) {


    this->SetBackgroundColour(wxColour(252, 242, 238));
    text = new wxStaticText(this,wxID_ANY,message+"\nNO CONNECTION",wxDefaultPosition,wxDefaultSize,wxALIGN_CENTRE_HORIZONTAL);
    boxsizer = new wxBoxSizer(wxVERTICAL);
    boxsizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxFont font (16,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);
    text->SetFont(font);
    text->SetForegroundColour(*wxRED);
    boxsizer->Add(text,0,wxALIGN_CENTER);
    boxsizer2->Add(boxsizer,1,wxALIGN_CENTER|wxALL,200);

    this->SetSizer(boxsizer2);

}*/

void gMain::changePanels(unsigned int panelnr) {

    switch (panelnr) {
        case 1:
            panel2->Hide();
            panel->Show();
            break;
        case 2:
            panel->Hide();
            panel2->Show();
            break;
        default:
            break;
    }
    boxsizer2->Layout();
}

C_client *gMain::getConnection() const {
    return connection;
}

ClientManagerPtr gMain::getCm() const {
    return CM;
}

RoomManagerPtr gMain::getRoomM() const {
    return RoomM;
}

ReservationManagerPtr gMain::getResM() const {
    return ResM;
}
