#include <boost/test/unit_test.hpp>
#include "model/Bicycle.h"
#include "typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteBicycle)

    BOOST_AUTO_TEST_CASE(BicycleRentCostTest) {
        VehiclePtr bike = std::make_shared<Bicycle>("bike",2);
        BOOST_TEST(bike->get_ActualRentalPrice()==2);
//        delete bike;
    }
BOOST_AUTO_TEST_SUITE_END()
