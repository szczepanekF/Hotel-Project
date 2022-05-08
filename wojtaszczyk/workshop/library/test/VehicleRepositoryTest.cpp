#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"

struct TestSuiteVehicleRepositoryFixture {

    StorageContainer S;

    const std::string testplateNumberX= "Jon";
    const unsigned int  testbasePriceX = 21;
    VehiclePtr testVehicleX;
    VehiclePtr testVehicle;



    TestSuiteVehicleRepositoryFixture() {


        testVehicleX= std::make_shared<Bicycle>(testplateNumberX,testbasePriceX);

    }

    ~TestSuiteVehicleRepositoryFixture() {




    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleRepository, TestSuiteVehicleRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {

        BOOST_TEST(S.getVehicleRepository().size() == 1);
    }

    BOOST_AUTO_TEST_CASE(GetTest){

        BOOST_TEST(S.getVehicleRepository().get(0)->getVehicleInfo()==testVehicleX->getVehicleInfo());
        BOOST_TEST(S.getVehicleRepository().get(1)== nullptr);
        BOOST_TEST(S.getVehicleRepository().get(-1)==nullptr);
    }
    BOOST_AUTO_TEST_CASE(AddTest){
        testVehicle = std::make_shared<Bicycle>(testplateNumberX, testbasePriceX);
        S.getVehicleRepository().add(testVehicle);
        BOOST_TEST(S.getVehicleRepository().size() == 2);
        BOOST_TEST(S.getVehicleRepository().get(1)->getVehicleInfo()==testVehicle->getVehicleInfo());
        S.getClientRepository().add(nullptr);
        BOOST_TEST(S.getClientRepository().size() == 1);

    }
    BOOST_AUTO_TEST_CASE(RemoveTest){
        testVehicle = std::make_shared<Bicycle>(testplateNumberX, testbasePriceX);
        S.getVehicleRepository().add(testVehicle);
        S.getVehicleRepository().remove(testVehicle);
        BOOST_TEST(S.getVehicleRepository().size() == 1);
        BOOST_TEST(S.getVehicleRepository().get(0)->getVehicleInfo()==testVehicleX->getVehicleInfo());
        S.getVehicleRepository().remove(nullptr);
        BOOST_TEST(S.getVehicleRepository().size() == 1);




    }
    BOOST_AUTO_TEST_CASE(findALLTest){
        testVehicle = std::make_shared<Bicycle>(testplateNumberX, testbasePriceX);
        S.getVehicleRepository().add(testVehicle);
        BOOST_TEST(S.getVehicleRepository().findAll().size()==2);
        BOOST_TEST(S.getVehicleRepository().findAll()[1]->getVehicleInfo()==testVehicle->getVehicleInfo());


    }
    BOOST_AUTO_TEST_CASE(findByTest){
        testVehicle = std::make_shared<Bicycle>(testplateNumberX, 25);
        S.getVehicleRepository().add(testVehicle);
        BOOST_TEST(S.getVehicleRepository().findBy(vehiclebaseprice25).size()==1);
        BOOST_TEST(S.getVehicleRepository().findBy(vehiclebaseprice25)[0]->getVehicleInfo()==testVehicle->getVehicleInfo());

    }


BOOST_AUTO_TEST_SUITE_END()


