#include <iostream>

#include "model/Reservation.h"
#include "model/Client.h"
//#include "model/shortTerm.h"
#include "model/Standard.h"
#include "model/longTerm.h"
#include "model/RoomWithoutTerrace.h"
#include "repositories/RoomRepository.h"
#include "repositories/ClientRepository.h"
#include "repositories/ReservationRepository.h"

#include "managers/ClientManager.h"
#include "managers/ReservationManager.h"
#include "exceptions/ReservationError.h"
using namespace std;
namespace gr=boost::gregorian;
int main(){


//    cout<<"DZIALA";
    ClientTypePtr testType=std::make_shared<Standard>();
    ClientPtr testClient;
    RoomPtr testRoom;
    ClientPtr testClient2;
    RoomPtr testRoom2;
    ud::uuid testId = {2};
    ud::uuid testId2 = {1};
    int testGuestCount = 2;
    pt::ptime testBeginTime = pt::second_clock::local_time();
//    pt::ptime testEndTime = pt::second_clock::local_time()+pt::hours(50);
    testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
    testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
    testClient2 = std::make_shared<Client>("ktos","jan","242557",testType);
    testRoom2 = std::make_shared<RoomWithoutTerrace>(2,500,2);
//    Reservation res(testClient,testRoom,testGuestCount,testId,testBeginTime,testEndTime);
//    cout<<res.getInfo();
//    RoomRepository repo;
//    repo.add(testRoom);


//    ClientRepositoryPtr CR= make_shared<ClientRepository>();
//    ClientManager CM(CR);
//    CM.regiterClient("Milo","woj","232",testType);
//    CM.regiterClient("dalo","fds","242",testType);
//    CR->findById("242");
//    CM.unregisterClient("232");
//    cout<<CM.findAllClients().size();



    ReservationRepositoryPtr RR1= make_shared<ReservationRepository>();
    ReservationRepositoryPtr RR2= make_shared<ReservationRepository>();
//    ReservationManager RM;
    ReservationManager *RM=new ReservationManager(RR1,RR2);
    try {
        RM->startReservation(testClient, testRoom, testGuestCount, testId, testBeginTime, 4, A);
        RM->startReservation(testClient2, testRoom2, testGuestCount, testId2, testBeginTime, 6, B);
    }catch(const ReservationError &e){
        cout<<e.information();
    }
    RM->endReservation(testId2);
    delete RM;
    return 0;
};