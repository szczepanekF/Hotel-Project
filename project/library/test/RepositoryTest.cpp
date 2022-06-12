#include <boost/test/unit_test.hpp>
#include "model/Reservation.h"
#include "model/Client.h"
#include "model/Standard.h"
#include "model/RoomWithoutTerrace.h"
#include "repositories/ClientRepository.h"
#include "repositories/RoomRepository.h"
#include "repositories/ReservationRepository.h"
#include <vector>
#include "exceptions/RoomError.h"
#include "exceptions/ReservationError.h"
#include "exceptions/ClientError.h"

struct RepositoryFixture {
    ClientTypePtr testType;
    ClientPtr testClient;
    RoomPtr testRoom;
    ReservationPtr testRes;
    ClientPtr testClient2;
    RoomPtr testRoom2;
    ReservationPtr testRes2;
    ud::uuid testId = {1};
    ud::uuid testId2 = {2};
    int testGuestCount = 2;
    int testGuestCount2 = 3;
    pt::ptime testBeginTime = pt::second_clock::local_time();


    RepositoryFixture() {
        testType=std::make_shared<Standard>();
        testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
        testRes = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId,testBeginTime,4,A);
        testClient2= std::make_shared<Client>("Stanislaw","Kowalski","242567",testType);
        testRoom2 = std::make_shared<RoomWithoutTerrace>(2,500,3);
        testRes2= std::make_shared<Reservation>(testClient2,testRoom2,testGuestCount2,testId2,testBeginTime,4,A);


    }

    ~RepositoryFixture() = default;

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepository,RepositoryFixture)

    BOOST_AUTO_TEST_CASE(AddTestDefault) {
        ClientRepository CR;
        BOOST_TEST(CR.size() == 0);
        CR.add(testClient);
        CR.add(testClient2);
        BOOST_TEST(CR.size() == 2);
        RoomRepository RoomR;
        BOOST_TEST(RoomR.size() == 0);
        RoomR.add(testRoom);
        RoomR.add(testRoom2);
        BOOST_TEST(RoomR.size() == 2);
        ReservationRepository ResR;
        BOOST_TEST(ResR.size() == 0);
        ResR.add(testRes);
        ResR.add(testRes2);
        BOOST_TEST(ResR.size() == 2);
    }
    BOOST_AUTO_TEST_CASE(GetTestDefault) {
        ClientRepository CR;
        CR.add(testClient);
        BOOST_TEST(CR.get(0) == testClient);
        RoomRepository RoomR;
        RoomR.add(testRoom);
        BOOST_TEST(RoomR.get(0) == testRoom);
        ReservationRepository ResR;
        ResR.add(testRes);
        BOOST_TEST(ResR.get(0) == testRes);
    }

    BOOST_AUTO_TEST_CASE(RemoveTestDefault) {
        ClientRepository CR;
        CR.add(testClient);
        CR.add(testClient2);
        BOOST_TEST(CR.size() == 2);
        CR.remove(testClient);
        BOOST_TEST(CR.size() == 1);


        RoomRepository RoomR;
        RoomR.add(testRoom);
        RoomR.add(testRoom2);
        BOOST_TEST(RoomR.size() == 2);
        RoomR.remove(testRoom);
        BOOST_TEST(RoomR.size() == 1);


        ReservationRepository ResR;
        ResR.add(testRes);
        ResR.add(testRes2);
        BOOST_TEST(ResR.size() == 2);
        ResR.remove(testRes);
        BOOST_TEST(ResR.size() == 1);
    }
    BOOST_AUTO_TEST_CASE(FindByTestDefault) {
        ClientRepository CR;

        CR.add(testClient);
        CR.add(testClient2);
        BOOST_TEST(CR.findAll().size() == 2);
        BOOST_TEST(CR.findAll()[0] == testClient);
        BOOST_TEST(CR.findAll()[1] == testClient2);
        BOOST_TEST(CR.findBy([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";}).size() == 1);
        BOOST_TEST(CR.findBy([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";})[0] == testClient);
        BOOST_TEST(CR.findById("242567") == testClient2);


        RoomRepository RoomR;
        RoomR.add(testRoom);
        RoomR.add(testRoom2);
        BOOST_TEST(RoomR.findAll().size() == 2);
        BOOST_TEST(RoomR.findAll()[0] == testRoom);
        BOOST_TEST(RoomR.findAll()[1] == testRoom2);
        BOOST_TEST(RoomR.findBy([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;}).size() == 1);
        BOOST_TEST(RoomR.findBy([](const RoomPtr &ptr)->bool{return ptr->getBedCount()==2;})[0] == testRoom);
        BOOST_TEST(RoomR.findById(2) == testRoom2);

        ReservationRepository ResR;
        ResR.add(testRes);
        ResR.add(testRes2);
        BOOST_TEST(ResR.findAll().size() == 2);
        BOOST_TEST(ResR.findAll()[0] == testRes);
        BOOST_TEST(ResR.findAll()[1] == testRes2);
        BOOST_TEST(ResR.findBy([](const ReservationPtr &ptr)->bool{return ptr->getGuestCount()==2;}).size() == 1);
        BOOST_TEST(ResR.findBy([](const ReservationPtr &ptr)->bool{return ptr->getGuestCount()==2;})[0] == testRes);
        BOOST_TEST(ResR.findById(testId2) == testRes2);
    }
    BOOST_AUTO_TEST_CASE(ExceptionsTest) {
        ClientRepository CR;
        CR.add(testClient2);

        BOOST_REQUIRE_THROW(CR.add(nullptr),ClientError);
        BOOST_CHECK_EXCEPTION(CR.add(nullptr),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Null pointer";});
        BOOST_TEST(CR.size()==1);

        ClientPtr testClient3=nullptr;
        BOOST_REQUIRE_THROW(testClient3=CR.get(1),ClientError);
        BOOST_CHECK_EXCEPTION(CR.get(1),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Invalid index";});
        BOOST_TEST(testClient3==nullptr);

        BOOST_REQUIRE_THROW(testClient3=CR.get(-1),ClientError);
        BOOST_CHECK_EXCEPTION(CR.get(-1),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Invalid index";});
        BOOST_TEST(testClient3==nullptr);

        BOOST_REQUIRE_THROW(CR.remove(nullptr),ClientError);
        BOOST_CHECK_EXCEPTION(CR.remove(nullptr),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Null pointer";});
        BOOST_TEST(CR.size()==1);

        BOOST_REQUIRE_THROW(testClient3=CR.findById("432"),ClientError);
        BOOST_CHECK_EXCEPTION(CR.findById("432"),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR No Object";});
        BOOST_TEST(testClient3==nullptr);

        std::vector<ClientPtr> testClients;
        BOOST_REQUIRE_THROW(testClients=CR.findBy([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";}),ClientError);
        BOOST_CHECK_EXCEPTION(CR.findBy([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";}),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testClients.size()==0);

    }

BOOST_AUTO_TEST_SUITE_END()