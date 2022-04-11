#include <boost/test/unit_test.hpp>
#include "model/Rent.h"
#include "model/Vehicle.h"
#include "model/Client.h"
#include "model/Address.h"

struct TestSuiteRentFixture {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    Address *testaddress1;
    const unsigned int ID=11;
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 21;
    Client *testClient;
    Vehicle *testVehicle;

    TestSuiteRentFixture() {
        testaddress1 = new Address("London", "Accacia Avenue", "22");
        testClient= new Client(testFirstName, testLastName, testPersonalID, testaddress1);
        testVehicle= new Vehicle(testplateNumber,testbasePrice);
    }

    ~TestSuiteRentFixture() {
        delete testaddress1;
        delete testClient;
        delete testVehicle;
    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorRentGivenBeginTime) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25));

    Rent r(ID,testClient,testVehicle,then);

        for(unsigned int i=0;i<r.GetRentClient()->GetClient_RentNumber();i++)
       {
            BOOST_TEST(r.GetRentClient()->GetClientRent(i)!= nullptr);
       }
        BOOST_TEST(r.GetRentVehicle()->isRetend()==true);
        BOOST_TEST(r.GetRentVehicle()==testVehicle);
        BOOST_TEST(r.GetRentClient()==testClient);
        BOOST_TEST(r.getEndTime()==pt::not_a_date_time);
        BOOST_TEST_REQUIRE(!r.getBeginTime().is_not_a_date_time());
        BOOST_TEST(r.getBeginTime()==then);

    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {

        Rent *r = new Rent(ID,testClient ,testVehicle, pt::not_a_date_time);

        pt::ptime now = pt::second_clock::local_time(); //hope this takes no longer than 59 secs...
        BOOST_TEST_REQUIRE(!r->getBeginTime().is_not_a_date_time()); //if this isn't met, the next check doesn't make sense...
        pt::time_period skew = pt::time_period(r->getBeginTime(), now);
        BOOST_TEST((skew.length().hours()==0 && skew.length().minutes()==0));

        delete r;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentNotEnded) {

        Rent *r = new Rent(ID,testClient ,testVehicle, pt::not_a_date_time);
        BOOST_TEST(r->getRentDays()==0);
        delete r;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedWithinMinute) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25)+pt::seconds(1));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(26)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==0);
        delete r;

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter1m) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25)+pt::seconds(1));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(26)+pt::seconds(1));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==1);
        delete r;

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter23h59m) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(8)+pt::minutes(59)+pt::seconds(1));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==1);
        delete r;

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter24h0m) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==2);
        delete r;

    }
    BOOST_AUTO_TEST_CASE(EndRentTestBasic) {

        Rent *r = new Rent(ID,testClient ,testVehicle, pt::not_a_date_time);

        unsigned int i=r->GetRentClient()->GetClient_RentNumber();
        r->endRent(pt::not_a_date_time);
        BOOST_TEST(r->GetRentVehicle()->isRetend()==0);
        BOOST_TEST(i-1==r->GetRentClient()->GetClient_RentNumber());
        delete r;

    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetCurrentTime) {

        Rent *r = new Rent(ID,testClient ,testVehicle, pt::not_a_date_time);


        r->endRent(pt::second_clock::local_time());
        BOOST_TEST_REQUIRE(r->getEndTime()!=pt::not_a_date_time);
        BOOST_TEST(r->getEndTime()==pt::second_clock::local_time());

        delete r;

    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeAfterBeginTime) {

        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getEndTime()==end);
        delete r;

    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeEqualsBeginTime) {

        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        r->endRent(then);
        BOOST_TEST(r->getEndTime()==then);
        delete r;

    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeBeforeBeginTime) {

        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, end);
        r->endRent(then);
        BOOST_TEST(r->getEndTime()==end);
        delete r;

    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIs0) {

        Rent *r = new Rent(ID,testClient ,testVehicle, pt::not_a_date_time);
        r->endRent(pt::not_a_date_time);
        BOOST_TEST(r->getRentCost()==0);
        delete r;
    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositive) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getRentCost()=2*testbasePrice);
        delete r;

    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentCostIsPermanentWhenVehiclePriceChanged) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        unsigned int i=r->getRentCost();
        r->GetRentVehicle()->SetVehiclebasePrcie(testbasePrice+5);
        BOOST_TEST(r->getRentCost()==i);
        delete r;

    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentTryEndRentAlreadyEnded) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        Rent *r = new Rent(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        unsigned int i=r->getRentDays();
        r->endRent(pt::not_a_date_time);
        BOOST_TEST(r->getRentDays()==i);
        delete r;

    }


BOOST_AUTO_TEST_SUITE_END()

