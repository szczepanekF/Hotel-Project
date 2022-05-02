#include <boost/test/unit_test.hpp>
#include "model/Vehicle.h"
#include "model/Rent.h"
#include "model/Client.h"
#include "model/Bicycle.h"
#include "model/Default.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"
#include "model/Diamond.h"

namespace pt = boost::posix_time;

struct TestSuiteRentFixture{
    const unsigned int testid = 1;
    AddressPtr testaddress1;
    ClientPtr testclient1;
    VehiclePtr testvehicle1;
    ClientTypePtr pt1;
    ClientTypePtr pt2;
    ClientTypePtr pt3;
    ClientTypePtr pt4;
    ClientTypePtr pt5;
    ClientTypePtr pt6;


    TestSuiteRentFixture(){
        pt1 = std::make_shared<Default>();
        pt2 = std::make_shared<Bronze>();
        pt3 = std::make_shared<Silver>();
        pt4 = std::make_shared<Gold>();
        pt5 = std::make_shared<Platinum>();
        pt6 = std::make_shared<Diamond>();
        testaddress1=std::make_shared<Address>("London", "Accacia Avenue", "22");
        testclient1 = std::make_shared<Client>("Jon","Arbuckle","0123456789",testaddress1,pt1);
        testvehicle1 = std::make_shared<Bicycle>("54321",100);
    }
    ~TestSuiteRentFixture(){

    }
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstructorTestGivenBeginTime) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
        BOOST_TEST(a->get_id()==testid);
        BOOST_TEST(a->get_client()==testclient1);
        BOOST_TEST(a->get_vehicle()==testvehicle1);
        BOOST_TEST(a->get_rentCost()==0);
        BOOST_TEST(a->get_beginTime()==pt::second_clock::local_time());

//        BOOST_TEST(testclient1->get_rentNumber()==1);
//        BOOST_TEST(testclient1->get_currentRent(0)==a);
//        BOOST_TEST(testvehicle1->isRented()==true);

        ;
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {

        RentPtr r = std::make_shared<Rent>(testid, testclient1, testvehicle1, pt::not_a_date_time);

        pt::ptime now = pt::second_clock::local_time(); //hope this takes no longer than 59 secs...
        BOOST_TEST_REQUIRE(!r->get_beginTime().is_not_a_date_time()); //if this isn't met, the next check doesn't make sense...
        pt::time_period skew = pt::time_period(r->get_beginTime(), now);
        BOOST_TEST((skew.length().hours()==0 && skew.length().minutes()==0));

//        delete r;
    }
//    BOOST_AUTO_TEST_CASE(EndTestBasic) {
//        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
//        a->endRent();
//        BOOST_TEST(testvehicle1->isRented()==false);
//        BOOST_TEST(testclient1->get_rentNumber()==0);
//
//        ;
//    }

//

    BOOST_AUTO_TEST_CASE(EndTestSetCurrentTime) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(pt::not_a_date_time);
        BOOST_TEST(a->get_endTime()==pt::second_clock::local_time());
        a->endRent(pt::second_clock::local_time()+pt::minutes(30));
        BOOST_TEST(a->get_endTime()==pt::second_clock::local_time());
        ;
    }

    BOOST_AUTO_TEST_CASE(EndTestSetGivenEndTimeAfterBeginTime) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(pt::second_clock::local_time() + pt::minutes(30));
        BOOST_TEST(a->get_endTime()==pt::second_clock::local_time() + pt::minutes(30));
        ;
    }

    BOOST_AUTO_TEST_CASE(EndTestSetGivenEndTimeEqualsBeginTime) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(a->get_beginTime());
        BOOST_TEST(a->get_endTime()==a->get_beginTime());
        ;
    }


    BOOST_AUTO_TEST_CASE(EndTestSetGivenEndTimeBeforeBeginTime) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
        a->endRent(pt::second_clock::local_time() - pt::minutes(30));
        BOOST_TEST(a->get_endTime()==a->get_beginTime());
        ;
    }


    BOOST_AUTO_TEST_CASE(RentDaysTestRentNotEnded) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::not_a_date_time);
        BOOST_TEST(a->get_rentDays()==0);
        ;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedWithinMinute) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::seconds(30)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==0);
        ;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter1m) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==1);
        ;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter23h59m) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(59)-pt::hours(23)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==1);
        ;
    }
    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter24h0m) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        BOOST_TEST(a->get_rentDays()==2);
        ;
    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentTryEndRentAlreadyEnded) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        a->endRent();
        BOOST_TEST(a->get_rentDays()==2);
        ;
    }


    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIs0) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,pt::second_clock::local_time());
        a->endRent();
        BOOST_TEST(a->get_rentCost()==0);
        ;
    }
    BOOST_AUTO_TEST_CASE(RentCostTestRentDaysIsPositive) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==testvehicle1->get_basePrice()*a->get_rentDays());
        ;
    }

    BOOST_AUTO_TEST_CASE(RentCostTestRentCostIsPermanentWhenVehiclePriceChanged) {
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::hours(24)));
        a->endRent();
        testvehicle1->set_basePrice(2);
        BOOST_TEST(a->get_rentCost()==200);
        ;
    }
    BOOST_AUTO_TEST_CASE(RentCostTestDefault) {
        testclient1->set_clientType(pt1);
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==100);
    }
    BOOST_AUTO_TEST_CASE(RentCostTestBronze) {
        testclient1->set_clientType(pt2);
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==97);
    }
    BOOST_AUTO_TEST_CASE(RentCostTestSilver) {
        testclient1->set_clientType(pt3);
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==94);
    }
    BOOST_AUTO_TEST_CASE(RentCostTestGold) {
        testclient1->set_clientType(pt4);
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==95);
    }
    BOOST_AUTO_TEST_CASE(RentCostTestPlatinum) {
        testclient1->set_clientType(pt5);
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==90);
    }
    BOOST_AUTO_TEST_CASE(RentCostTestDiamond) {
        testclient1->set_clientType(pt6);
        RentPtr a = std::make_shared<Rent>(testid,testclient1,testvehicle1,(pt::second_clock::local_time()-pt::minutes(2)));
        a->endRent();
        BOOST_TEST(a->get_rentCost()==90);
    }


BOOST_AUTO_TEST_SUITE_END()

