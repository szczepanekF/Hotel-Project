#include <boost/test/unit_test.hpp>
#include "model/Vehicle.h"

struct TestSuiteVehicleFixture{
    std::string plates = "12345";
    const unsigned int nr = 5050;
    std::string plates2 = "abcdef";
    const unsigned int nr2 = 1;

};


BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicle, TestSuiteVehicleFixture)

    BOOST_AUTO_TEST_CASE(VehicleConstructorTests) {
        Vehicle a(plates,nr);
        BOOST_TEST(a.get_plateNumber().compare(plates)==0);
        BOOST_TEST(a.get_basePrice()==nr);
        BOOST_TEST(a.isRented()==false);

    }
    BOOST_AUTO_TEST_CASE(VehiclePlateNumberSetterTests) {
        Vehicle a(plates,nr);
        a.set_plateNumber(plates2);
        BOOST_TEST(a.get_plateNumber().compare(plates2)==0);
        a.set_plateNumber("");
        BOOST_TEST(a.get_plateNumber().compare(plates2)==0);
    }
    BOOST_AUTO_TEST_CASE(VehicleBasePriceSetterTests) {
        Vehicle a(plates,nr);
        a.set_basePrice(nr2);
        BOOST_TEST(a.get_basePrice()==nr2);

    }





BOOST_AUTO_TEST_SUITE_END()
