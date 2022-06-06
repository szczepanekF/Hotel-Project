#include <boost/test/unit_test.hpp>
#include "model/RoomWithoutTerrace.h"
#include "model/RoomWithTerrace.h"

#include "repositories/RoomRepository.h"
#include "managers/RoomManager.h"

struct RoomManagerFixture {
    RoomPtr testRoom;
    RoomPtr testRoom2;
    
    RoomRepositoryPtr RP;
    RoomManagerFixture() {
        RP =  std::make_shared<RoomRepository>();
//        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
//        testRoom2 = std::make_shared<RoomWithTerrace>(2,500,3,200);
//        testRoom3 = std::make_shared<RoomWithoutTerrace>(3,500,3);

    }

    ~RoomManagerFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRoomManager,RoomManagerFixture)

BOOST_AUTO_TEST_CASE(RegisterTestDefault) {

        RoomManager RM(RP);
        BOOST_TEST(RP->size()== 0);
        testRoom = RM.RegisterRoomWithoutTerrace(1,400,2);
        testRoom2 = RM.RegisterRoomWithTerrace(2,900,2,500);
        BOOST_TEST(RM.getRoom(1) == testRoom);
        BOOST_TEST(RM.getRoom(2) == testRoom2);
        BOOST_TEST(RP->size()== 2);


}

BOOST_AUTO_TEST_CASE(FindTestDefault) {
        RoomManager RM(RP);
        testRoom = RM.RegisterRoomWithoutTerrace(1,400,2);
        testRoom2 = RM.RegisterRoomWithTerrace(2,900,2,500);
        BOOST_TEST(RM.findAllRooms().size()==2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;}).size()==2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[0]==testRoom);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[1]==testRoom2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[0]->getId() == 1);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBedCount()==2;})[1]->getId() == 2);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBasePricePerNight()==900;}).size()==1);
        BOOST_TEST(RM.findRooms([](const RoomPtr ptr)->bool{return ptr->getBasePricePerNight()==900;})[0]->getId() == 2);

}

BOOST_AUTO_TEST_CASE(ExceptionsTestDefault) {
        RoomManager RM(RP);
        BOOST_REQUIRE_THROW(RM.findAllRooms(),RoomError);
        BOOST_CHECK_EXCEPTION(RM.findAllRooms(),RoomError,
                              [] (const RoomError &e){return e.information().compare("ERROR No Objects")==0;});
        testRoom = RM.RegisterRoomWithoutTerrace(1,400,2);
        std::string information = testRoom->getInfo();
        BOOST_CHECK_THROW(RM.RegisterRoomWithoutTerrace(1,100,10),RoomError);
        BOOST_CHECK_EXCEPTION(RM.RegisterRoomWithoutTerrace(1,100,10),RoomError,
        [information] (const RoomError &e){return e.information().compare("ERROR Room already exists: "+information)==0;});
        testRoom2 = RM.RegisterRoomWithTerrace(2,900,2,500);
        information = testRoom2->getInfo();
        BOOST_CHECK_THROW(RM.RegisterRoomWithTerrace(2,100,10,1),RoomError);
        BOOST_CHECK_EXCEPTION(RM.RegisterRoomWithTerrace(2,100,10,1),RoomError,
        [information] (const RoomError &e){return e.information().compare("ERROR Room already exists: "+information)==0;});
        BOOST_CHECK_THROW(RM.getRoom(4),RoomError);
        BOOST_CHECK_EXCEPTION(RM.getRoom(4),RoomError,
                              [] (const RoomError &e){return e.information().compare("ERROR No Object")==0;});





}


BOOST_AUTO_TEST_SUITE_END()