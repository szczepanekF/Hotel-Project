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


wxIMPLEMENT_APP(cApp);


cApp::cApp() {
    clients = std::make_shared<ClientRepository>();
    rooms = std::make_shared<RoomRepository>();
    archRes = std::make_shared<ReservationRepository>();
    currRes = std::make_shared<ReservationRepository>();


}

cApp::~cApp() {

}
bool cApp::OnInit() {
    ClientManager cManager(clients);
    RoomManager roomManager(rooms);
    ReservationManager resManager(currRes,archRes);


    m_frame1 = new gMain();
    m_frame1->Show();


    return true;
}