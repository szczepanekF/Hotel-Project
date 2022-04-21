#include <boost/test/unit_test.hpp>
#include "model/Car.h"
#include "typedefs.h"

struct TestSuiteCarFixture{
    std::string testplates = "car";
    const unsigned int testprice = 1;
    const unsigned int testEngineDisplacement1 = 1;
//    const unsigned int testEngineDisplacement2 = 1000;
//    const unsigned int testEngineDisplacement3 = 1500;
//    const unsigned int testEngineDisplacement4 = 1999;
//    const unsigned int testEngineDisplacement5 = 2000;
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteCar,TestSuiteCarFixture)

    BOOST_AUTO_TEST_CASE(CarRentCostTest1A) {
        VehiclePtr car = std::make_shared<Car>(testplates,testprice,testEngineDisplacement1,A);
        BOOST_TEST(car->get_ActualRentalPrice()==testprice);
        //delete car;
    }
    BOOST_AUTO_TEST_CASE(CarRentCostTest1B) {
        VehiclePtr car = std::make_shared<Car>(testplates,testprice,testEngineDisplacement1,B);
        BOOST_TEST(car->get_ActualRentalPrice()==1.1);
        //delete car;
    }
    BOOST_AUTO_TEST_CASE(CarRentCostTest1C) {
        VehiclePtr car = std::make_shared<Car>(testplates,testprice,testEngineDisplacement1,C);
        BOOST_TEST(car->get_ActualRentalPrice()==1.2);
        //delete car;
    }
    BOOST_AUTO_TEST_CASE(CarRentCostTest1D) {
        VehiclePtr car = std::make_shared<Car>(testplates,testprice,testEngineDisplacement1,D);
        BOOST_TEST(car->get_ActualRentalPrice()==1.3);
        //delete car;
    }
    BOOST_AUTO_TEST_CASE(CarRentCostTest1E) {
        VehiclePtr car = std::make_shared<Car>(testplates,testprice,testEngineDisplacement1,E);
        BOOST_TEST(car->get_ActualRentalPrice()==1.5);
        //delete car;
    }
BOOST_AUTO_TEST_SUITE_END()