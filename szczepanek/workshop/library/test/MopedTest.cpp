#include <boost/test/unit_test.hpp>
#include "model/Moped.h"
#include "typedefs.h"

struct TestSuiteMopedFixture{
    std::string testplates = "moped";
    const unsigned int testprice = 1;
    const unsigned int testEngineDisplacement1 = 999;
    const unsigned int testEngineDisplacement2 = 1000;
    const unsigned int testEngineDisplacement3 = 1500;
    const unsigned int testEngineDisplacement4 = 1999;
    const unsigned int testEngineDisplacement5 = 2000;
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteMoped,TestSuiteMopedFixture)

    BOOST_AUTO_TEST_CASE(MopedRentCostTest1) {
        VehiclePtr moped = std::make_shared<Moped>(testplates,testprice,testEngineDisplacement1);
        BOOST_TEST(moped->get_ActualRentalPrice()==testprice);
        //delete moped;
    }
    BOOST_AUTO_TEST_CASE(MopedRentCostTest2) {
        VehiclePtr moped = std::make_shared<Moped>(testplates,testprice,testEngineDisplacement2);
        BOOST_TEST(moped->get_ActualRentalPrice()==testprice);
        //delete moped;
    }
    BOOST_AUTO_TEST_CASE(MopedRentCostTest3) {
        VehiclePtr moped = std::make_shared<Moped>(testplates,testprice,testEngineDisplacement3);
        BOOST_TEST(moped->get_ActualRentalPrice()==1.25);
        //delete moped;
    }
    BOOST_AUTO_TEST_CASE(MopedRentCostTest4) {
        VehiclePtr moped = std::make_shared<Moped>(testplates,testprice,testEngineDisplacement4);
        BOOST_TEST(moped->get_ActualRentalPrice()==1.4995);
        //delete moped;
    }
    BOOST_AUTO_TEST_CASE(MopedRentCostTest5) {
        VehiclePtr moped = std::make_shared<Moped>(testplates,testprice,testEngineDisplacement5);
        BOOST_TEST(moped->get_ActualRentalPrice()==1.5);
        //delete moped;
    }
BOOST_AUTO_TEST_SUITE_END()
