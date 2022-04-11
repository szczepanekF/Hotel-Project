#include <boost/test/unit_test.hpp>
#include "model/Vehicle.h"

struct TestSuiteVehicleFixture {
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 21;

    const std::string testplateNumber1= "Jan";
    const unsigned int  testbasePrice1 = 41;


    TestSuiteVehicleFixture() {

    }

    ~TestSuiteVehicleFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicle, TestSuiteVehicleFixture)

    BOOST_AUTO_TEST_CASE(VehicleConstructorTest){
      Vehicle v1(testplateNumber, testbasePrice);
        BOOST_TEST(v1.GetVehicleplateNumber().compare(testplateNumber)==0);
        BOOST_TEST(v1.GetVehiclebasePrice()==testbasePrice);
        BOOST_TEST(v1.isRetend()==0);
    }
    BOOST_AUTO_TEST_CASE(VehicleSetterTests){
        Vehicle v1(testplateNumber, testbasePrice);
        v1.SetVehiclebasePrcie(testbasePrice1);
        v1.SetVehicleplateNumber(testplateNumber1);

        BOOST_TEST(v1.GetVehicleplateNumber().compare(testplateNumber1)==0);
        BOOST_TEST(v1.GetVehiclebasePrice()==testbasePrice1);
        v1.SetVehicleplateNumber("");
        BOOST_TEST(v1.GetVehicleplateNumber().compare(testplateNumber1)==0);
    }



BOOST_AUTO_TEST_SUITE_END()