#include <boost/test/unit_test.hpp>
#include "model/Vehicle.h"
#include "model/Bicycle.h"
#include "typedefs.h"

struct TestSuiteVehicleFixture{
    const std::string plates = "12345";
    const unsigned int nr = 5050;
    const std::string plates2 = "abcdef";
    const unsigned int nr2 = 1;

};


BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicle, TestSuiteVehicleFixture)

    BOOST_AUTO_TEST_CASE(VehicleConstructorTests) {
        VehiclePtr a=std::make_shared<Bicycle> (plates,nr);
        BOOST_TEST(a->get_plateNumber().compare(plates)==0);
        BOOST_TEST(a->get_basePrice()==nr);
//        BOOST_TEST(a->isRented()==false);
        ;
    }
    BOOST_AUTO_TEST_CASE(VehiclePlateNumberSetterTests) {
        VehiclePtr a=std::make_shared<Bicycle>(plates,nr);
        a->set_plateNumber(plates2);
        BOOST_TEST(a->get_plateNumber().compare(plates2)==0);
        a->set_plateNumber("");
        BOOST_TEST(a->get_plateNumber().compare(plates2)==0);
        ;
    }
    BOOST_AUTO_TEST_CASE(VehicleBasePriceSetterTests) {
        VehiclePtr a = std::make_shared<Bicycle>(plates,nr);
        a->set_basePrice(nr2);
        BOOST_TEST(a->get_basePrice()==nr2);
        ;
    }


BOOST_AUTO_TEST_SUITE_END()

