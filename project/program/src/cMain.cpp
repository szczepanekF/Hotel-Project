#include "cMain.h"
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


cMain::cMain(C_client* conn, ClientManagerPtr& CM, RoomManagerPtr& RoomM, ReservationManagerPtr& ResM) : connection(conn), CM(CM),
                                                                                                         RoomM(RoomM), ResM(ResM), wxFrame(nullptr,wxID_ANY,"Hotel Reservation App",wxPoint(30,30),wxSize(800,600))
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

    this->SetSizer(boxsizer2);
    loginP->getRegist()->SetFocus();
    this->SetMinSize(wxSize(400,300));
}

cMain::~cMain() {
    delete connection;
}

void cMain::changePanels(unsigned int panelnr) {

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
            break;
        default:
            break;
    }
    boxsizer2->Layout();
}

C_client *cMain::getConnection() const {
    return connection;
}

ClientManagerPtr cMain::getCm() const {
    return CM;
}

RoomManagerPtr cMain::getRoomM() const {
    return RoomM;
}

ReservationManagerPtr cMain::getResM() const {
    return ResM;
}

void cMain::RefreshAfterLogging() {



    middleP->RefreshAfterLogging();
    roomsP->RefreshAfterLogging();
    reservationP->RefreshAfterLogging();
    settingsP->RefreshAfterLogging();
    settingsP->setClient(CM->getClient(connection->getLoggedPid()));
    settingsP->Refresh();
}
