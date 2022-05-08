#include <boost/test/unit_test.hpp>
#include "model/Car.h"

struct TestSuiteCarFixture {
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 20;
    const unsigned int engine1=1000;

    VehiclePtr testVehicle;
    VehiclePtr testVehicle2;
    VehiclePtr testVehicle3;
    VehiclePtr testVehicle4;
    VehiclePtr testVehicle5;

    TestSuiteCarFixture() {

    }

    ~TestSuiteCarFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCar, TestSuiteCarFixture)


    BOOST_AUTO_TEST_CASE(CarPriceTests){
        testVehicle= std::make_shared<Car>(testplateNumber, testbasePrice,engine1,A);
        BOOST_TEST(testVehicle->getActualRentalPrice()==20);
        testVehicle2= std::make_shared<Car>(testplateNumber, testbasePrice,engine1,B);
        BOOST_TEST(testVehicle2->getActualRentalPrice()==22);
        testVehicle3= std::make_shared<Car>(testplateNumber, testbasePrice,engine1,C);
        BOOST_TEST(testVehicle3->getActualRentalPrice()==24);
        testVehicle4= std::make_shared<Car>(testplateNumber, testbasePrice,engine1,D);
        BOOST_TEST(testVehicle4->getActualRentalPrice()==26);
        testVehicle5= std::make_shared<Car>(testplateNumber, testbasePrice,engine1,E);
        BOOST_TEST(testVehicle5->getActualRentalPrice()==30);

    }



BOOST_AUTO_TEST_SUITE_END()
