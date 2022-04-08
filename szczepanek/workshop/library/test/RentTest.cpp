#include <boost/test/unit_test.hpp>
#include "model/Vehicle.h"
#include "model/Rent.h"
#include "model/Client.h"

namespace pt = boost::posix_time;

struct TestSuiteRentFixture{
    const unsigned int testid = 1;
    Address *testaddress1;
    Client *testclient1;
    Vehicle  *testvehicle1;


    TestSuiteRentFixture(){
        testaddress1=new Address("London", "Accacia Avenue", "22");
        testclient1 = new Client("Jon","Arbuckle","0123456789",testaddress1);
        testvehicle1 = new Vehicle("54321",10);
    }
    ~TestSuiteRentFixture(){
        delete testaddress1;
        delete testclient1;
        delete testvehicle1;

    }
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstructorTestGivenBeginTime) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        BOOST_TEST(a->get_id()==testid);
        BOOST_TEST(a->get_client()==testclient1);
        BOOST_TEST(a->get_vehicle()==testvehicle1);
        BOOST_TEST(a->get_rentCost()==0);
        BOOST_TEST(testclient1->get_rentNumber()==1);
        BOOST_TEST(testclient1->get_currentRent(0)==a);
        BOOST_TEST(testvehicle1->isRented()==true);

        delete a;
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {

        Rent *r = new Rent(testid, testclient1, testvehicle1, pt::not_a_date_time);

        pt::ptime now = pt::second_clock::local_time(); //hope this takes no longer than 59 secs...
        BOOST_TEST_REQUIRE(!r->get_beginTime().is_not_a_date_time()); //if this isn't met, the next check doesn't make sense...
        pt::time_period skew = pt::time_period(r->get_beginTime(), now);
        BOOST_TEST((skew.length().hours()==0 && skew.length().minutes()==0));

        delete r;
    }

    BOOST_AUTO_TEST_CASE(EndTestBasic) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent();
        BOOST_TEST(testvehicle1->isRented()==false);
        BOOST_TEST(testclient1->get_rentNumber()==0);

        delete a;
    }

    BOOST_AUTO_TEST_CASE(EndTestSetCurrentTime) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(pt::not_a_date_time);
        BOOST_TEST(a->get_endTime()==pt::second_clock::local_time());
        a->endRent(pt::second_clock::local_time()+pt::minutes(30));
        BOOST_TEST(a->get_endTime()==pt::second_clock::local_time());
        delete a;
    }

    BOOST_AUTO_TEST_CASE(EndTestSetGivenEndTimeAfterBeginTime) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(pt::second_clock::local_time() + pt::minutes(30));
        BOOST_TEST(a->get_endTime()==pt::second_clock::local_time() + pt::minutes(30));
        delete a;
    }

    BOOST_AUTO_TEST_CASE(EndTestSetGivenEndTimeEqualsBeginTime) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(a->get_beginTime());
        BOOST_TEST(a->get_endTime()==a->get_beginTime());
        delete a;
    }


    BOOST_AUTO_TEST_CASE(EndTestSetGivenEndTimeBeforeBeginTime) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(pt::second_clock::local_time() - pt::minutes(30));
        BOOST_TEST(a->get_endTime()==a->get_beginTime());
        delete a;
    }


    BOOST_AUTO_TEST_CASE(RentDaysTestRentNotEnded) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::not_a_date_time);
        BOOST_TEST(a->get_rentDays()==0);
        delete a;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedWithinMinute) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::seconds(30)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==0);
        delete a;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter1m) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==1);
        delete a;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter23h59m) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(59)-pt::hours(23)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==1);
        delete a;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter24h0m) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==2);
        delete a;
    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentTryEndRentAlreadyEnded) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        a->endRent();
        BOOST_TEST(a->get_rentDays()==2);
        delete a;
    }


    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIs0) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,pt::second_clock::local_time());
        a->endRent();
        BOOST_TEST(a->get_rentCost()==0);
        delete a;
    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositive) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==testvehicle1->get_basePrice()*a->get_rentDays());
        delete a;
    }

    BOOST_AUTO_TEST_CASE(RentCostTestRentCostIsPermanentWhenVehiclePriceChanged) {
        Rent *a = new Rent(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        testvehicle1->set_basePrice(2);
        BOOST_TEST(a->get_rentCost()==20);
        delete a;
    }



BOOST_AUTO_TEST_SUITE_END()

