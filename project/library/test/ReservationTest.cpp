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
namespace gr = boost::gregorian;

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
        testRoom = std::make_shared<RoomWithoutTerrace>(1,400,2);
    }

     ~ReservationFixture() {

     }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteReservation,ReservationFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefault) {
        Reservation res(testClient, testRoom, testGuestCount, testId, testBeginTime, 1, A);
        BOOST_TEST(res.getClient()==testClient);
        BOOST_TEST(res.getRoom()==testRoom);
        BOOST_TEST(res.getGuestCount()==testGuestCount);
        BOOST_TEST(res.getId()==testId);
        BOOST_TEST(res.getBeginTime()==testBeginTime);
        BOOST_TEST(res.getReservationDays()==1);
        BOOST_TEST(res.getExtraBonus()==A);



    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestExceptions) {

        BOOST_CHECK_THROW(Reservation res(nullptr, testRoom, testGuestCount, testId, testBeginTime, 1, B), ClientError);
        BOOST_CHECK_EXCEPTION(Reservation res(nullptr, testRoom, testGuestCount, testId, testBeginTime, 1, B), ClientError,
                              [](const HotelError &e){return e.information().compare("ERROR Null client")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient, nullptr, testGuestCount, testId, testBeginTime, 1, B), RoomError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient, nullptr, testGuestCount, testId, testBeginTime, 1, B), RoomError,
                              [](const HotelError &e){return e.information().compare("Error Null room")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient, testRoom, 0, testId, testBeginTime, 1, B), ReservationError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient, testRoom, 0, testId, testBeginTime, 1, B), ReservationError,
                              [](const HotelError &e){return e.information().compare("ERROR Wrong guest count")==0;});
        BOOST_CHECK_THROW(Reservation res(testClient, testRoom, testGuestCount, testId, pt::not_a_date_time, 1, B), ReservationError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient, testRoom, testGuestCount, testId, pt::not_a_date_time, 1, B), ReservationError,
                              [](const HotelError &e){return e.information().compare("Error Begin time not given")==0;});

        BOOST_CHECK_THROW(Reservation res(testClient, testRoom, 3, testId, testBeginTime, 0, B), ReservationError);
        BOOST_CHECK_EXCEPTION(Reservation res(testClient, testRoom, 3, testId, testBeginTime, 0, B), ReservationError,
                              [](const HotelError &e){return e.information().compare("Error Wrong reservation days")==0;});

    }

    BOOST_AUTO_TEST_CASE(GetEndTimeTest) {
        pt::ptime testBeginTime1(gr::date(2015,5,13),pt::hours(12)+pt::minutes(0)+pt::seconds(0));
        pt::ptime testBeginTime2(gr::date(2015,5,13),pt::hours(11)+pt::minutes(59)+pt::seconds(59));
        pt::ptime testBeginTime3(gr::date(2015,5,13),pt::hours(12)+pt::minutes(0)+pt::seconds(1));
        pt::ptime ideal1(gr::date(2015,5,17),pt::hours(12));
        pt::ptime ideal2(gr::date(2015,5,16),pt::hours(12));
        Reservation res1(testClient, testRoom, testGuestCount, testId, testBeginTime1, 4, B);
        Reservation res2(testClient, testRoom, testGuestCount, testId, testBeginTime2, 4, B);
        Reservation res3(testClient, testRoom, testGuestCount, testId, testBeginTime3, 4, B);
        BOOST_TEST(res1.getEndTime()==ideal1);
        BOOST_TEST(res2.getEndTime()==ideal2);
        BOOST_TEST(res3.getEndTime()==ideal1);


    }
    BOOST_AUTO_TEST_CASE(GetPricePerNight) {
        Reservation res(testClient, testRoom, testGuestCount, testId, testBeginTime, 1, A);
        BOOST_TEST(res.getPricePerNight() == 400);
        res.setExtraBonus(B);
        BOOST_TEST(res.getPricePerNight() == 500);
        res.setExtraBonus(C);
        BOOST_TEST(res.getPricePerNight() == 650);

}






BOOST_AUTO_TEST_SUITE_END()


