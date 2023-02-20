#include "cApp.h"
#include "managers/ClientManager.h"
#include "managers/RoomManager.h"
#include "managers/ReservationManager.h"
#include "repositories/ClientRepository.h"
#include "repositories/RoomRepository.h"
#include "repositories/ReservationRepository.h"
#include "exceptions/ClientError.h"
#include "exceptions/ReservationError.h"
#include "exceptions/RoomError.h"


#include "model/Room.h"

namespace gr = boost::gregorian;
wxIMPLEMENT_APP(cApp);


cApp::cApp() {
    clients = std::make_shared<ClientRepository>();
    rooms = std::make_shared<RoomRepository>();
    archRes = std::make_shared<ReservationRepository>();
    currRes = std::make_shared<ReservationRepository>();
    connection = new C_client();

}

cApp::~cApp() {

}
bool cApp::OnInit() {

    ClientManagerPtr cManager = std::make_shared<ClientManager>(clients);
    RoomManagerPtr roomManager = std::make_shared<RoomManager>(rooms);
    ReservationManagerPtr resManager = std::make_shared<ReservationManager>(currRes,archRes);


    connection->createConnection();
    if(connection->getConnSuccess()>=0) {
        cManager->readClientsFromServer(connection);
        roomManager->readRoomsFromServer(connection);
        resManager->readReservationsFromServer(connection,cManager,roomManager);
    }
    

    m_Frame = new cMain(connection, cManager, roomManager, resManager);
    m_Frame->Show();



    return true;
}