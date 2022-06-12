//
// Created by student on 11.06.2022.
//

#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/shortTerm.h"
#include "model/RoomWithoutTerrace.h"
#include "repositories/ClientRepository.h"
#include "managers/ClientManager.h"
#include "exceptions/ClientError.h"
#include "model/Predicates.h"
#include "model/Standard.h"
#include "repositories/RoomRepository.h"
#include "managers/RoomManager.h"
#include "managers/ReservationManager.h"
#include "repositories/ReservationRepository.h"
#include "exceptions/RoomError.h"
#include "exceptions/ReservationError.h"


namespace pt = boost::posix_time;
namespace ud = boost::uuids;
namespace gr = boost::gregorian;


struct PredicateFixture {

    ClientRepositoryPtr CR;
    RoomRepositoryPtr RP;
    ReservationRepositoryPtr currentRR;
    ReservationRepositoryPtr archiveRR;
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
    pt::ptime testBeginTime=pt::ptime(gr::date(2015,5,17),pt::hours(12));
    pt::ptime testBeginTime2=pt::ptime(gr::date(2015,5,20),pt::hours(12));



    PredicateFixture() {
        RP =  std::make_shared<RoomRepository>();
        CR = std::make_shared<ClientRepository>();
        currentRR = std::make_shared<ReservationRepository>();
        archiveRR = std::make_shared<ReservationRepository>();
        testType=std::make_shared<Standard>();
        testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
        testRes = std::make_shared<Reservation>(testClient,testRoom,testGuestCount,testId,testBeginTime,4,A);
        testClient2= std::make_shared<Client>("Stanislaw","Kowalski","242567",testType);
        testRoom2 = std::make_shared<RoomWithoutTerrace>(2,500,3);
        testRes2= std::make_shared<Reservation>(testClient2,testRoom2,testGuestCount2,testId2,testBeginTime2,4,A);




    }

    ~PredicateFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePredicate,PredicateFixture)

    BOOST_AUTO_TEST_CASE(ClientLastNamePredicateTest){

        ClientManager CM(CR);
        ClientPtr testClient = CM.regiterClient("Jan", "Wojtaszczyk", "242544", testType);
        ClientPtr testClient2 = CM.regiterClient("NieJan", "Wojtasik", "242567", testType);
        ClientPtr testClient3 = CM.regiterClient("Jan", "Walaszek", "444091", testType);

        BOOST_TEST(CM.findClients(ClientLastNamePredicate("Woj")).size() == 2);
        BOOST_TEST(CM.findClients(ClientLastNamePredicate("woj")).size() == 2);
        BOOST_TEST(CM.findClients(ClientLastNamePredicate("w")).size() == 3);

        BOOST_REQUIRE_THROW(CM.findClients(ClientLastNamePredicate("wojte")), ClientError);
        BOOST_CHECK_EXCEPTION(CM.findClients(ClientLastNamePredicate("wojte")), ClientError,
                                  [](const ClientError &e) { return e.information() == "ERROR No Objects"; });

        BOOST_REQUIRE_THROW(CM.findClients(ClientLastNamePredicate("")), ClientError);
        BOOST_CHECK_EXCEPTION(CM.findClients(ClientLastNamePredicate("")), ClientError,
                                  [](const ClientError &e) { return e.information() == "ERROR Empty pattern"; });


    }
    BOOST_AUTO_TEST_CASE(RoomBasePricePredicateTest){
        RoomManager RM(RP);
        RoomPtr testRoom = RM.registerRoomWithoutTerrace(1, 400, 2);
        RoomPtr testRoom2 = RM.registerRoomWithTerrace(2, 900, 2, 500);
        RoomPtr testRoom3=RM.registerRoomWithoutTerrace(3,300,3);

        BOOST_TEST(RM.findRooms(RoomBasePricePredicate(300)).size()==3);
        BOOST_TEST(RM.findRooms(RoomBasePricePredicate(400)).size()==2);

        std::vector<RoomPtr> testRooms;
        BOOST_REQUIRE_THROW(testRooms=RM.findRooms(RoomBasePricePredicate(1000)),RoomError);
        BOOST_CHECK_EXCEPTION(testRooms=RM.findRooms(RoomBasePricePredicate(1000)),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testRooms.size()==0);

        BOOST_REQUIRE_THROW(testRooms=RM.findRooms(RoomBasePricePredicate(0)),RoomError);
        BOOST_CHECK_EXCEPTION(testRooms=RM.findRooms(RoomBasePricePredicate(0)),RoomError,
                              [] (const RoomError &e){return e.information()=="ERROR Wrong pattern price";});
        BOOST_TEST(testRooms.size()==0);

}
BOOST_AUTO_TEST_CASE(ReservationBeginTimePredicateTest){
        ReservationManager RM(currentRR,archiveRR);
        currentRR->add(testRes);
        currentRR->add(testRes2);
        BOOST_TEST(RM.findReservations(ReservationBeginTimePredicate(pt::ptime(gr::date(2015,5,17),pt::hours(12)))).size()==2);
        BOOST_TEST(RM.findReservations(ReservationBeginTimePredicate(pt::ptime(gr::date(2015,5,20),pt::hours(12)))).size()==1);

        std::vector<ReservationPtr> testReservations;
        BOOST_REQUIRE_THROW(testReservations=RM.findReservations(ReservationBeginTimePredicate(pt::not_a_date_time)),ReservationError);
        BOOST_CHECK_EXCEPTION(testReservations=RM.findReservations(ReservationBeginTimePredicate(pt::not_a_date_time)),ReservationError,
                            [] (const ReservationError &e){return e.information()=="Error Begin time not given";});
        BOOST_TEST(testReservations.size()==0);

        BOOST_REQUIRE_THROW(testReservations=RM.findReservations(ReservationBeginTimePredicate(pt::ptime(gr::date(2015,5,21),pt::hours(12)))),ReservationError);
        BOOST_CHECK_EXCEPTION(testReservations=RM.findReservations(ReservationBeginTimePredicate(pt::ptime(gr::date(2015,5,21),pt::hours(12)))),ReservationError,
                              [] (const ReservationError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testReservations.size()==0);

}


BOOST_AUTO_TEST_SUITE_END()