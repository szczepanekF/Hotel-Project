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
    pt::ptime testEndTime = pt::second_clock::local_time()+pt::hours(50);
    ReservationFixture() {
        testClient = std::make_shared<Client>("Jan","Ktos","242544",testType);
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2,A);
    }

     ~ReservationFixture() {

     }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteReservation,ReservationFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefault) {
        Reservation res(testClient,testRoom,testGuestCount,testId,testBeginTime,testEndTime);
        BOOST_TEST(res.getClient()==testClient);
        BOOST_TEST(res.getRoom()==testRoom);
        BOOST_TEST(res.getGuestCount()==testGuestCount);
        BOOST_TEST(res.getId()==testId);
        BOOST_TEST(res.getBeginTime()==testBeginTime);
        BOOST_TEST(res.getEndTime()==testEndTime);
        BOOST_TEST(res.getTotalReservationCost()==testClient->getBill()+testRoom->getFinalPricePerNight()*res.getReservationDays());


    }

    BOOST_AUTO_TEST_CASE(CalculateTotalReservationCostDefault) {
        Reservation res(testClient,testRoom,testGuestCount,testId,testBeginTime,testEndTime);
        double temp =res.getTotalReservationCost();
        BOOST_TEST(res.getTotalReservationCost()==temp);
        testRoom->setExtraBonus(E);
        BOOST_TEST(res.getTotalReservationCost()==temp);
        res.calculateReservationCost();
        BOOST_TEST(res.getTotalReservationCost()!=temp);

}








BOOST_AUTO_TEST_SUITE_END()


