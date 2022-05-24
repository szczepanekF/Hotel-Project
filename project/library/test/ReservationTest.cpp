#include <boost/test/unit_test.hpp>
#include "model/Reservation.h"
#include "model/Client.h"
//#include "model/shortTerm.h"
#include "model/Standard.h"
//#include "model/longTerm.h"
#include "model/RoomWithoutTerrace.h"
struct ReservationFixture {
    ClientTypePtr testType=std::make_shared<Standard>();
    ClientPtr testClient;
    RoomPtr testRoom;
    ud::uuid testId = {1};
    int testGuestCount = 2;
    pt::ptime testBeginTime = pt::second_clock::local_time();
//    pt::ptime testEndTime = pt::second_clock::local_time();
    ReservationFixture() {
        testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2,A);
    }

     ~ReservationFixture() {

     }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteReservation,ReservationFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefault) {
        Reservation res(testClient,testRoom,testGuestCount,testId,testBeginTime,testBeginTime);


    }






BOOST_AUTO_TEST_SUITE_END()


