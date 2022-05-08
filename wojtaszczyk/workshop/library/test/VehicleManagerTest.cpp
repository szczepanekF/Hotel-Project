#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "managers/VehicleManager.h"

struct TestSuiteVehicleManagerFixture {

    const unsigned int  testbasePriceX = 100;


    VehicleManager VM;



    TestSuiteVehicleManagerFixture() {



    }

    ~TestSuiteVehicleManagerFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleManager, TestSuiteVehicleManagerFixture)


    BOOST_AUTO_TEST_CASE(registerTest){
        VehiclePtr ptr;
        ptr=VM.registerBicycle("JJ",testbasePriceX);
        BOOST_TEST(VM.getVehicle("JJ")==ptr);
        BOOST_TEST(VM.getVehicle("10")==nullptr);
        ptr=VM.registerMoped("JJ",200,2000);
        BOOST_TEST(VM.findAllVehicles().size()==1);
        BOOST_TEST(VM.findAllVehicles()[0]==ptr);
        ptr=VM.registerMoped("AA",200,2000);
        BOOST_TEST(VM.getVehicle("AA")==ptr);
        ptr=VM.registerCar("BB",300,4000,A);
        BOOST_TEST(VM.getVehicle("BB")==ptr);
        BOOST_TEST(VM.findAllVehicles().size()==3);
        VehiclePredicate f=[](VehiclePtr ptr)->bool{return ptr->getVehicleplateNumber()=="AA";};
        BOOST_TEST(VM.findVehicles(f).size()==1);

    }


BOOST_AUTO_TEST_SUITE_END()



