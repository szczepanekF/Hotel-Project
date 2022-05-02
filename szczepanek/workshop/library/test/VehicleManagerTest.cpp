
#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "managers/VehicleManager.h"
#include "model/Car.h"
#include "model/Bicycle.h"
#include "model/Moped.h"



struct TestSuiteVehicleManagerFixture{
    std::string testplates1 = "car";
    const unsigned int testprice1 = 5000;
    std::string testplates3 = "bike";
    const unsigned int testprice3 = 1;
    std::string testplates2 = "moped";
    const unsigned int testprice2 = 1000;
    const unsigned int testEngineDisplacement2 = 500;
    const unsigned int testEngineDisplacement1 = 1000;
    SegmentType testsegment = A;

    VehiclePtr testvehicle1;
    VehiclePtr testvehicle2;
    VehiclePtr testvehicle3;

    VehicleManagerPtr VM;



    TestSuiteVehicleManagerFixture(){
//        testvehicle1 = std::make_shared<Car>(testplates1,testprice1,testEngineDisplacement1,testsegment);
//        testvehicle1 = std::make_shared<Moped>(testplates2,testprice2,testEngineDisplacement2);
//        testvehicle1 = std::make_shared<Bicycle>(testplates3,testprice3);


        VM = std::make_shared<VehicleManager>();
    }
    ~TestSuiteVehicleManagerFixture(){

    }

};


BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleManager,TestSuiteVehicleManagerFixture)
    BOOST_AUTO_TEST_CASE(registertest) {
        VM->registerBicycle(testplates3,testprice3);
        BOOST_TEST(VM->getVehicle(testplates1)==nullptr);
        BOOST_TEST(VM->getVehicle(testplates3)->get_basePrice()==testprice3);
        VM->registerBicycle(testplates3,testprice2);
        BOOST_TEST(VM->getVehicle(testplates3)->get_basePrice()==testprice3);



        VM->registerMoped(testplates2,testprice2,testEngineDisplacement2);
        BOOST_TEST(VM->getVehicle(testplates1)==nullptr);
        BOOST_TEST(VM->getVehicle(testplates2)->get_basePrice()==testprice2);
        VM->registerMoped(testplates2,testprice1,testEngineDisplacement1);
        BOOST_TEST(VM->getVehicle(testplates2)->get_basePrice()==testprice2);

        VM->registerCar(testplates1,testprice1,testEngineDisplacement1,testsegment);
        BOOST_TEST(VM->getVehicle("")==nullptr);
        BOOST_TEST(VM->getVehicle(testplates1)->get_basePrice()==testprice1);
        VM->registerCar(testplates1,testprice2,testEngineDisplacement1,testsegment);
        BOOST_TEST(VM->getVehicle(testplates1)->get_basePrice()==testprice1);

    }
    BOOST_AUTO_TEST_CASE(unregistertest) {
        VM->registerBicycle(testplates3,testprice3);
        VM->unregisterVehicle(VM->getVehicle(testplates3));
        BOOST_TEST_REQUIRE(VM->getVehicle(testplates3)!=nullptr);
        BOOST_TEST(VM->getVehicle(testplates3)->isArchive()==true);
    }
    BOOST_AUTO_TEST_CASE(findvehicletest) {
        VM->registerBicycle(testplates1,testprice2);
        BOOST_TEST(VM->findVehicles([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;})[0]==VM->getVehicle(testplates1));
        BOOST_TEST(VM->findVehicles([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;}).size()==1);
        VM->registerBicycle(testplates2,testprice2);
        BOOST_TEST(VM->findVehicles([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;})[0]==VM->getVehicle(testplates1));
        BOOST_TEST(VM->findVehicles([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;})[1]==VM->getVehicle(testplates2));
        BOOST_TEST(VM->findVehicles([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;}).size()==2);
        VM->unregisterVehicle(VM->getVehicle(testplates1));
        VM->unregisterVehicle(VM->getVehicle(testplates2));

        BOOST_TEST(VM->findVehicles([](const VehiclePtr ptr){return ptr->get_basePrice()==1000;}).size()==0);

    }


BOOST_AUTO_TEST_SUITE_END()
