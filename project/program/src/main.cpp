#include <iostream>

#include "model/Reservation.h"
#include "model/Client.h"
//#include "model/shortTerm.h"
#include "model/Standard.h"
#include "model/longTerm.h"
#include "model/RoomWithoutTerrace.h"
#include "repositories/RoomRepository.h"
#include "repositories/ClientRepository.h"
#include "managers/ClientManager.h"
using namespace std;
int main(){


//    cout<<"DZIALA";
//    ClientTypePtr testType=std::make_shared<Standard>();
//    ClientPtr testClient;
//    RoomPtr testRoom;
//    ud::uuid testId = {12,50,255,255,255,255,255,255,255,255,255};
//    int testGuestCount = 2;
//    pt::ptime testBeginTime = pt::second_clock::local_time();
//    pt::ptime testEndTime = pt::second_clock::local_time()+pt::hours(50);
//    testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
//    testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2,A);
//    Reservation res(testClient,testRoom,testGuestCount,testId,testBeginTime,testEndTime);
//    cout<<res.getInfo();
//    RoomRepository repo;
//    repo.add(testRoom);

//    ClientTypePtr typ= make_shared<longTerm>();
//    ClientRepositoryPtr CR= make_shared<ClientRepository>();
//    ClientManager CM(CR);
//    CM.regiterClient("Milo","woj","232",typ);
//    CM.regiterClient("dalo","fds","242",typ);
    //CR->findById("432");
    //CM.unregisterClient("282");
    //cout<<CM.findAllClients().size();

    return 0;
};