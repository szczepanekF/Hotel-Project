#include <boost/test/unit_test.hpp>
#include "model/Moped.h"

struct TestSuiteMopedFixture {
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 20;
    const unsigned int engine1=999;
    const unsigned int engine2=1500;
    const unsigned int engine3=2001;

    VehiclePtr testVehicle;
    VehiclePtr testVehicle2;
    VehiclePtr testVehicle3;

    TestSuiteMopedFixture() {

    }

    ~TestSuiteMopedFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteMoped, TestSuiteMopedFixture)


    BOOST_AUTO_TEST_CASE(MopedPriceTests){
        testVehicle= std::make_shared<Moped>(testplateNumber, testbasePrice,engine1);
        BOOST_TEST(testVehicle->getActualRentalPrice()==20);
        testVehicle2= std::make_shared<Moped>(testplateNumber, testbasePrice,engine2);
        BOOST_TEST(testVehicle2->getActualRentalPrice()==25);
        testVehicle3= std::make_shared<Moped>(testplateNumber, testbasePrice,engine3);
        BOOST_TEST(testVehicle3->getActualRentalPrice()==30);

    }



BOOST_AUTO_TEST_SUITE_END()


