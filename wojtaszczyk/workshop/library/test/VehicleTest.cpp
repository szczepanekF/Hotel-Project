#include <boost/test/unit_test.hpp>
#include "model/Bicycle.h"

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
      Bicycle v1(testplateNumber, testbasePrice);
        BOOST_TEST(v1.getVehicleplateNumber().compare(testplateNumber) == 0);
        BOOST_TEST(v1.getVehiclebasePrice() == testbasePrice);
      //  BOOST_TEST(v1.isRetend()==0);
    }
    BOOST_AUTO_TEST_CASE(VehicleSetterTests){
        Bicycle v1(testplateNumber, testbasePrice);
        v1.setVehiclebasePrcie(testbasePrice1);
        v1.setVehicleplateNumber(testplateNumber1);

        BOOST_TEST(v1.getVehicleplateNumber().compare(testplateNumber1) == 0);
        BOOST_TEST(v1.getVehiclebasePrice() == testbasePrice1);
        v1.setVehicleplateNumber("");
        BOOST_TEST(v1.getVehicleplateNumber().compare(testplateNumber1) == 0);
    }



BOOST_AUTO_TEST_SUITE_END()