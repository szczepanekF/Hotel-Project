#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "managers/RentManager.h"

struct TestSuiteRentManagerFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    StorageContainer S;
    ClientPtr testClient;
    const std::string testplateNumberX= "JJ";
    const unsigned int  testbasePriceX = 50;

    VehiclePtr testVehicleX;
    VehiclePtr testVehicle2;
    VehiclePtr testVehicle3;
    const std::string testFirstNameX = "Jon";
    const std::string testLastNameX = "Arbuckle";
    const std::string testPersonalIDX = "0123456789";
    AddressPtr testaddress1X;
    ClientPtr testClientX;
    ClientPtr testClient2;
    ClientTypePtr testType;
    RentManager RM;



    TestSuiteRentManagerFixture() {

        testType= std::make_shared<Default>();
        testaddress1X = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testClientX= std::make_shared<Client>(testFirstNameX, testLastNameX, testPersonalIDX, testaddress1X,testType);
        //CM.registerClient(testFirstNameX,testLastNameX,testPersonalIDX,testaddress1X,testType);
        testVehicleX= std::make_shared<Bicycle>(testplateNumberX,testbasePriceX);
        testVehicle2= std::make_shared<Bicycle>("AA",200);
        testVehicle3= std::make_shared<Bicycle>("BB",1000);
        testClient2= std::make_shared<Client>("Milosz","Wojtaszczyk","242",testaddress1X,testType);

    }

    ~TestSuiteRentManagerFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRentManager, TestSuiteRentManagerFixture)

    BOOST_AUTO_TEST_CASE(rentTest){
    RentPtr ptr;
    ptr=RM.rentVehicle(1,testClientX,testVehicleX,pt::not_a_date_time);
    BOOST_TEST(RM.findAllRents().size()==1);
    BOOST_TEST(RM.findVehicleRent(testVehicleX)==ptr);
    ptr=RM.rentVehicle(1,testClientX,testVehicle2,pt::not_a_date_time);
    BOOST_TEST(RM.findAllRents().size()==1);
    BOOST_TEST(ptr==nullptr);
    BOOST_TEST(RM.findAllClientRents(testClientX).size()==1);
    ptr=RM.rentVehicle(2,testClientX,testVehicle2,pt::not_a_date_time);
    BOOST_TEST(ptr==nullptr);
    BOOST_TEST(RM.findAllRents().size()==1);
    testType= std::make_shared<Gold>();
    testClientX->setClientType(testType);
    ptr=RM.rentVehicle(2,testClientX,testVehicle2,pt::not_a_date_time);
    BOOST_TEST(RM.findAllRents().size()==2);
    BOOST_TEST(RM.findVehicleRent(testVehicle2)==ptr);
    BOOST_TEST(RM.findAllClientRents(testClientX).size()==2);
    RentPredicate f =[](RentPtr ptr)->bool{return ptr->getRentID()==5; };
    BOOST_TEST(RM.findRents(f).size()==0);
    RentPredicate f2 =[](RentPtr ptr)->bool{return ptr->getRentID()==2; };
    BOOST_TEST(RM.findRents(f2).size()==1);
    BOOST_TEST(RM.findRents(f2)[0]->getRentInfo()==ptr->getRentInfo());
    ptr=RM.rentVehicle(3,testClientX,testVehicle2,pt::not_a_date_time);
    BOOST_TEST(ptr==nullptr);
    BOOST_TEST(RM.findAllRents().size()==2);
    testClientX->setArchive(true);
    ptr=RM.rentVehicle(3,testClientX,testVehicle3,pt::not_a_date_time);
    BOOST_TEST(ptr==nullptr);
    BOOST_TEST(RM.findAllRents().size()==2);
    testClientX->setArchive(false);
    RM.returnVehicle(testVehicleX);
    BOOST_TEST(RM.findAllRents().size()==1);





}

BOOST_AUTO_TEST_SUITE_END()