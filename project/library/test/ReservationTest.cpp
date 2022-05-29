#include <boost/test/unit_test.hpp>
#include "model/Reservation.h"
#include "model/Client.h"
//#include "model/shortTerm.h"
#include "model/Standard.h"
//#include "model/longTerm.h"
#include "model/RoomWithoutTerrace.h"
#include "exceptions/ReservationError.h"
#include "exceptions/RoomError.h"
#include "exceptions/ClientError.h"
#include "exceptions/HotelError.h"

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
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestExceptions) {

        BOOST_CHECK_THROW(Reservation res(nullptr,testRoom,testGuestCount,testId,testBeginTime,testEndTime),ClientError);
        BOOST_CHECK_EXCEPTION(Reservation res(nullptr,testRoom,testGuestCount,testId,testBeginTime,testEndTime),ClientError,
                              [](const HotelError &e){return e.information().compare("ERROR Null client")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient,nullptr,testGuestCount,testId,testBeginTime,testEndTime),RoomError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient,nullptr,testGuestCount,testId,testBeginTime,testEndTime),RoomError,
                              [](const HotelError &e){return e.information().compare("Error Null room")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient,testRoom,0,testId,testBeginTime,testEndTime),ReservationError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient,testRoom,0,testId,testBeginTime,testEndTime),ReservationError,
                              [](const HotelError &e){return e.information().compare("ERROR Wrong guest count")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient,testRoom,testGuestCount,testId,pt::not_a_date_time,testEndTime),ReservationError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient,testRoom,testGuestCount,testId,pt::not_a_date_time,testEndTime),ReservationError,
                              [](const HotelError &e){return e.information().compare("Error Begin time not given")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient,testRoom,3,testId,testBeginTime,testEndTime),ReservationError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient,testRoom,3,testId,testBeginTime,testEndTime),ReservationError,
                              [](const HotelError &e){return e.information().compare("Error Too many guests")==0;});


    }
    








BOOST_AUTO_TEST_SUITE_END()


