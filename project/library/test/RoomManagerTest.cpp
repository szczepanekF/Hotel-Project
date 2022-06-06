#include <boost/test/unit_test.hpp>
#include "model/RoomWithoutTerrace.h"
#include "model/RoomWithTerrace.h"

#include "repositories/RoomRepository.h"
#include "managers/RoomManager.h"

struct RoomManagerFixture {
    RoomPtr testRoom;
    RoomPtr testRoom2;

    RoomManagerFixture() {
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
        testRoom2 = std::make_shared<RoomWithTerrace>(2,500,3,200);
    }

    ~RoomManagerFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRoomManager,RoomManagerFixture)

BOOST_AUTO_TEST_CASE(RegisterTestDefault) {
        RoomManager RM;
        RoomPtr room1 = RM.RegisterRoomWithoutTerrace(1,400,2);
        BOOST_TEST(RM.getRoom(1) == room1);
        RoomPtr room2 = RM.RegisterRoomWithTerrace(2,900,2,500);
        BOOST_TEST(RM.getRoom(2) == room2);


}

BOOST_AUTO_TEST_CASE(FindTestDefault) {
        RoomManager RM;
        RoomPtr room1 = RM.RegisterRoomWithoutTerrace(1,400,2);
        RoomPtr room2 = RM.RegisterRoomWithTerrace(2,900,2,500);
        BOOST_TEST(RM.findAllRooms().size()==2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;}).size()==2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[0]==room1);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[0]->getId() == 1);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[1]->getId() == 2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBasePricePerNight()==900;}).size()==1);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBasePricePerNight()==900;})[0]->getId() == 2);

}

BOOST_AUTO_TEST_CASE(ExceptionsTestDefault) {
        RoomManager RM;
        RoomPtr room1 = RM.RegisterRoomWithoutTerrace(1,400,2);
        BOOST_CHECK_THROW(RM.RegisterRoomWithoutTerrace(1,100,10),RoomError);
        BOOST_CHECK_EXCEPTION(RM.RegisterRoomWithoutTerrace(1,100,10),RoomError,
        [room1] (const RoomError &e){return e.information().compare("ERROR Room already exists: "+room1->getInfo())==0;});
        RoomPtr room2 = RM.RegisterRoomWithTerrace(2,900,2,500);
        BOOST_CHECK_THROW(RM.RegisterRoomWithTerrace(2,100,10,1),RoomError);
        BOOST_CHECK_EXCEPTION(RM.RegisterRoomWithTerrace(2,100,10,1),RoomError,
        [room2] (const RoomError &e){return e.information().compare("ERROR Room already exists: "+room2->getInfo())==0;});





}


BOOST_AUTO_TEST_SUITE_END()