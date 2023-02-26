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

    loginP->Show();
    registerP->Hide();

    middleP->Hide();

    reservationP->Hide();
    roomsP->Hide();
    settingsP->Hide();

    boxsizer = new wxBoxSizer(wxVERTICAL);

    boxsizer->Add(loginP, 1, wxGROW);
    boxsizer->Add(registerP, 1, wxGROW);
    boxsizer->Add(middleP, 1, wxGROW);
    boxsizer->Add(reservationP, 1, wxGROW);
    boxsizer->Add(roomsP, 1, wxGROW);
    boxsizer->Add(settingsP, 1, wxGROW);


    this->SetSizer(boxsizer);
    this->SetMinSize(wxSize(400,300));
    loginP->setSubmitFocus();
}

cMain::~cMain() {
    delete connection;
}

void cMain::changePanels(unsigned int panelnr) {

    switch (panelnr) {
        case 1:
            registerP->Hide();
            loginP->Show();
            middleP->Hide();
            break;
        case 2:
            loginP->Hide();
            registerP->Show();
            middleP->Hide();
            break;
        case 3:
            loginP->Hide();
            registerP->Hide();
            middleP->Show();
            reservationP->Hide();
            roomsP->Hide();
            settingsP->Hide();
            break;
        case 4:
            middleP->Hide();
            reservationP->Show();
            break;
        case 5:
            middleP->Hide();
            roomsP->Show();
            break;
        case 6:
            middleP->Hide();
            settingsP->Show();
            break;
        default:
            break;
    }
    boxsizer->Layout();
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

void cMain::RefreshAllPanelsAfterLogging() {


    middleP->SetOnLogging();
    roomsP->SetOnLogging();
    reservationP->SetOnLogging();
    settingsP->SetOnLogging();
    settingsP->setClient(CM->getClient(connection->getLoggedPid()));
    settingsP->Refresh();
}

void cMain::RefreshAllPanelsBalance() {
    middleP->RefreshBalance();
    roomsP->RefreshBalance();
    reservationP->RefreshBalance();
    settingsP->RefreshBalance();
}
