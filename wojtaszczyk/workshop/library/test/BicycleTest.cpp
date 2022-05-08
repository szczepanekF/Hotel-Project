#include <boost/test/unit_test.hpp>
#include "model/Bicycle.h"

struct TestSuiteBicycleFixture {
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 21;

    const std::string testplateNumber1= "Jan";
    const unsigned int  testbasePrice1 = 41;
    VehiclePtr testVehicle;


    TestSuiteBicycleFixture() {

    }

    ~TestSuiteBicycleFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteBicycle, TestSuiteBicycleFixture)


    BOOST_AUTO_TEST_CASE(BicyclePriceTests){
       testVehicle= std::make_shared<Bicycle>(testplateNumber, testbasePrice);

        BOOST_TEST(testVehicle->getActualRentalPrice()==21);

    }



BOOST_AUTO_TEST_SUITE_END()

