#include <boost/test/unit_test.hpp>
#include "model/RoomWithoutTerrace.h"
#include "model/RoomWithTerrace.h"

#include "repositories/RoomRepository.h"
#include "managers/RoomManager.h"

struct RoomManagerFixture {
    RoomPtr testRoom;
    RoomPtr testRoom2;
    RoomPtr testRoom3;

    RoomRepositoryPtr RP;
    RoomManagerFixture() {
        RP =  std::make_shared<RoomRepository>();
//        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
//        testRoom2 = std::make_shared<RoomWithTerrace>(2,500,3,200);
//        testRoom3 = std::make_shared<RoomWithoutTerrace>(3,500,3);

    }

    ~RoomManagerFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRoomManager,RoomManagerFixture)

BOOST_AUTO_TEST_CASE(RegisterAndGetRoomTest) {

        RoomManager RM(RP);
        BOOST_TEST(RP->size()== 0);
        testRoom = RM.registerRoomWithoutTerrace(1, 400, 2);
        testRoom2 = RM.registerRoomWithTerrace(2, 900, 2, 500);
        testRoom3=RM.registerRoomWithoutTerrace(3,300,3);
        BOOST_TEST(RM.getRoom(1) == testRoom);
        BOOST_TEST(RM.getRoom(2) == testRoom2);
        BOOST_TEST(RM.getRoom(3) == testRoom3);
        BOOST_TEST(RP->size()== 3);


}

BOOST_AUTO_TEST_CASE(FindRoomsAndFindAllRoomsTest) {
        RoomManager RM(RP);
        testRoom = RM.registerRoomWithoutTerrace(1, 400, 2);
        testRoom2 = RM.registerRoomWithTerrace(2, 900, 2, 500);
        testRoom3=RM.registerRoomWithoutTerrace(3,300,3);
        BOOST_TEST(RM.findAllRooms().size()==3);
        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;}).size()==2);
        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;})[0]==testRoom);
        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;})[1]==testRoom2);
//        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;})[0]->getId() == 1);
//        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;})[1]->getId() == 2);
        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBasePricePerNight()==900;}).size()==1);
        BOOST_TEST(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBasePricePerNight()==900;})[0] == testRoom2);

}

BOOST_AUTO_TEST_CASE(ExceptionsTest) {
        RoomManager RM(RP);
        std::vector<RoomPtr> testRooms;
        BOOST_REQUIRE_THROW(testRooms=RM.findAllRooms(),RoomError);
        BOOST_CHECK_EXCEPTION(RM.findAllRooms(),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testRooms.size()==0);

        BOOST_REQUIRE_THROW(testRooms=RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;}),RoomError);
        BOOST_CHECK_EXCEPTION(RM.findRooms([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;}),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testRooms.size()==0);

        testRoom3=nullptr;
        testRoom = RM.registerRoomWithoutTerrace(1, 400, 2);
        std::string information = testRoom->getInfo();

        BOOST_REQUIRE_THROW(RM.registerRoomWithoutTerrace(1, 100, 10), RoomError);
        BOOST_CHECK_EXCEPTION(RM.registerRoomWithoutTerrace(1, 100, 10), RoomError,
                              [information] (const RoomError &e){return e.information()=="ERROR already exists: "+information;});
        BOOST_TEST(RP->size()==1);

        testRoom2 = RM.registerRoomWithTerrace(2, 900, 2, 500);
        information = testRoom2->getInfo();
        BOOST_REQUIRE_THROW(RM.registerRoomWithTerrace(2, 100, 10, 1), RoomError);
        BOOST_CHECK_EXCEPTION(RM.registerRoomWithTerrace(2, 100, 10, 1), RoomError,
                              [information] (const RoomError &e){return e.information()=="ERROR already exists: "+information;});
        BOOST_TEST(RP->size()==2);

        BOOST_REQUIRE_THROW(testRoom3=RM.getRoom(4),RoomError);

        BOOST_CHECK_EXCEPTION(RM.getRoom(4),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR No Object";});
        BOOST_TEST(testRoom3==nullptr);





}


BOOST_AUTO_TEST_SUITE_END()