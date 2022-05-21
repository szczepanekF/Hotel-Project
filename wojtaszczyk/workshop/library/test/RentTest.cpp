#include <boost/test/unit_test.hpp>
#include "model/Rent.h"
#include "model/Bicycle.h"
#include "model/Client.h"
#include "model/Address.h"
#include "repositories/StorageContainer.h"

struct TestSuiteRentFixture {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    boost::uuids::uuid ID={11};
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 50;
    ClientPtr testClient;
    VehiclePtr testVehicle;
    ClientTypePtr testType;
    TestSuiteRentFixture() {
        testType= std::make_shared<Default>();
        testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress1,testType);
        testVehicle= std::make_shared<Bicycle>(testplateNumber,testbasePrice);


    }

    ~TestSuiteRentFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorRentGivenBeginTime) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25));

    Rent r(ID,testClient,testVehicle,then);

//        for(unsigned int i=0;i< r.getRentClient()->getClient_RentNumber(); i++)
//       {
//            BOOST_TEST(r.getRentClient()->getClientRent(i) != nullptr);
//       }
//        BOOST_TEST(r.getRentVehicle()->isRetend() == true);
        BOOST_TEST(r.getRentVehicle() == testVehicle);
        BOOST_TEST(r.getRentClient() == testClient);
        BOOST_TEST(r.getEndTime()==pt::not_a_date_time);
        BOOST_TEST_REQUIRE(!r.getBeginTime().is_not_a_date_time());
        BOOST_TEST(r.getBeginTime()==then);

        BOOST_CHECK_THROW(RentPtr rent=std::make_shared<Rent>(ID,nullptr,testVehicle,then),std::logic_error);
        BOOST_CHECK_THROW(RentPtr rent=std::make_shared<Rent>(ID,testClient,nullptr,then),std::logic_error);

    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {

        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, pt::not_a_date_time);

        pt::ptime now = pt::second_clock::local_time(); //hope this takes no longer than 59 secs...
        BOOST_TEST_REQUIRE(!r->getBeginTime().is_not_a_date_time()); //if this isn't met, the next check doesn't make sense...
        pt::time_period skew = pt::time_period(r->getBeginTime(), now);
        BOOST_TEST((skew.length().hours()==0 && skew.length().minutes()==0));

    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentNotEnded) {

        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, pt::not_a_date_time);
        BOOST_TEST(r->getRentDays()==0);

    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedWithinMinute) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25)+pt::seconds(1));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(26)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==0);


    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter1m) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(25)+pt::seconds(1));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(26)+pt::seconds(1));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==1);


    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter23h59m) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(8)+pt::minutes(59)+pt::seconds(1));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==1);


    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter24h0m) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getRentDays()==2);


    }
    BOOST_AUTO_TEST_CASE(EndRentTestBasic) {

        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, pt::not_a_date_time);

       // unsigned int i= r->getRentClient()->getClient_RentNumber();
        r->endRent(pt::not_a_date_time);
//        BOOST_TEST(r->getRentVehicle()->isRetend() == 0);
      //  BOOST_TEST(i-1== r->getRentClient()->getClient_RentNumber());


    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetCurrentTime) {

        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, pt::not_a_date_time);


        r->endRent(pt::second_clock::local_time());
        BOOST_TEST_REQUIRE(r->getEndTime()!=pt::not_a_date_time);
        BOOST_TEST(r->getEndTime()==pt::second_clock::local_time());



    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeAfterBeginTime) {

        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getEndTime()==end);


    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeEqualsBeginTime) {

        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        r->endRent(then);
        BOOST_TEST(r->getEndTime()==then);


    }
    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeBeforeBeginTime) {

        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, end);
        r->endRent(then);
        BOOST_TEST(r->getEndTime()==end);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIs0) {

        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, pt::not_a_date_time);
        r->endRent(pt::not_a_date_time);
        BOOST_TEST(r->getRentCost()==0);

    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositiveDefault) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        BOOST_TEST(r->getRentCost()==2*testbasePrice);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositiveBronze) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        testType= std::make_shared<Bronze>();
        r->getRentClient()->setClientType(testType);
        r->endRent(end);
        BOOST_TEST(r->getRentCost()==97);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositiveSilver) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        testType= std::make_shared<Silver>();
        r->getRentClient()->setClientType(testType);
        r->endRent(end);
        BOOST_TEST(r->getRentCost()==94);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositiveGold) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        testType= std::make_shared<Gold>();
        r->getRentClient()->setClientType(testType);
        r->endRent(end);
        BOOST_TEST(r->getRentCost()==95);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositivePlatinm) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        testType= std::make_shared<Platinum>();
        r->getRentClient()->setClientType(testType);
        r->endRent(end);
        BOOST_TEST(r->getRentCost()==90);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositiveDiamond) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        testType= std::make_shared<Diamond>();
        r->getRentClient()->setClientType(testType);
        r->endRent(end);
        BOOST_TEST(r->getRentCost()==90);


    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentCostIsPermanentWhenVehiclePriceChanged) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        const unsigned int i=r->getRentCost();
        r->getRentVehicle()->setVehiclebasePrcie(testbasePrice + 5);
        BOOST_TEST(r->getRentCost()==i);


    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentTryEndRentAlreadyEnded) {
        pt::ptime then = pt::ptime(gr::date(2015,5,13),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        RentPtr r = std::make_shared<Rent>(ID,testClient ,testVehicle, then);
        pt::ptime end=pt::ptime(gr::date(2015,5,14),pt::hours(9)+pt::minutes(0)+pt::seconds(0));
        r->endRent(end);
        unsigned int i=r->getRentDays();
        r->endRent(pt::not_a_date_time);
        BOOST_TEST(r->getRentDays()==i);

    }


BOOST_AUTO_TEST_SUITE_END()

