#include "gMain.h"
#include "repositories/ClientRepository.h"
#include "managers/ClientManager.h"
#include "typedefs.h"
#include "exceptions/ClientError.h"
#include "model/Client.h"
#include "RegistrationPanel.h"
#include "LoginPanel.h"
#include "MenuPanel.h"
#include "ReservationPanel.h"
#include "RoomsPanel.h"
#include "SettingsPanel.h"

gMain::gMain(C_client* conn,ClientManagerPtr CM,RoomManagerPtr RoomM,ReservationManagerPtr ResM) :connection(conn),CM(CM),
                RoomM(RoomM),ResM(ResM),wxFrame(nullptr,wxID_ANY,"Hotel Reservation App",wxPoint(30,30),wxSize(800,600))
{
    loginP = new LoginPanel(this);
    registerP = new RegistrationPanel(this);
    middleP = new MenuPanel(this);
    reservationP = new ReservationPanel(this);
    roomsP = new RoomsPanel(this);
    settingsP = new SettingsPanel(this);
//
    loginP->Show();
    registerP->Hide();
    middleP->Hide();
    reservationP->Hide();
    roomsP->Hide();
    settingsP->Hide();
    boxsizer2 = new wxBoxSizer(wxVERTICAL);

    boxsizer2->Add(loginP,1,wxGROW);
    boxsizer2->Add(registerP,1,wxGROW);
    boxsizer2->Add(middleP,1,wxGROW);
    boxsizer2->Add(reservationP,1,wxGROW);
    boxsizer2->Add(roomsP,1,wxGROW);
    boxsizer2->Add(settingsP,1,wxGROW);
    connection->sendMessage("242544");

    this->SetSizer(boxsizer2);
    loginP->getRegist()->SetFocus();
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
            registerP->Hide();
            loginP->Show();

            registerP->Hide();
            middleP->Hide();
            reservationP->Hide();
            roomsP->Hide();
            settingsP->Hide();
            break;
        case 2:
            loginP->Hide();
            registerP->Show();
            middleP->Hide();
            reservationP->Hide();
            roomsP->Hide();
            settingsP->Hide();
            break;
        case 3:
            loginP->Hide();
            registerP->Hide();
            middleP->Show();
            registerP->Hide();
            reservationP->Hide();
            roomsP->Hide();
            settingsP->Hide();
            break;
        case 4:
            middleP->Hide();
            reservationP->Show();
            roomsP->Hide();
            settingsP->Hide();
            break;
        case 5:
            middleP->Hide();
            reservationP->Hide();
            roomsP->Show();
            settingsP->Hide();
            break;
        case 6:
            middleP->Hide();
            reservationP->Hide();
            roomsP->Hide();
            settingsP->Show();
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
