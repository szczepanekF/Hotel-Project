#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"

struct TestSuiteRentRepositoryFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    StorageContainer S;
    ClientPtr testClient;
    VehiclePtr testVehicle;
    RentPtr testRent;
    const std::string testplateNumber= "Jon";
    const unsigned int  testbasePrice = 21;

    const std::string testFirstNameX = "Jon";
    const std::string testLastNameX = "Arbuckle";
    const std::string testPersonalIDX = "0123456789";
    AddressPtr testaddress1X;
    const unsigned int IDX=11;
    const std::string testplateNumberX= "Jon";
    const unsigned int  testbasePriceX = 21;
    ClientPtr testClientX;
    VehiclePtr testVehicleX;
    RentPtr testRentX;
    ClientPtr testClient2;
    ClientTypePtr testType;




    TestSuiteRentRepositoryFixture() {
        testType= std::make_shared<Default>();
        testaddress1X = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testClientX= std::make_shared<Client>(testFirstNameX, testLastNameX, testPersonalIDX, testaddress1X,testType);
        testVehicleX= std::make_shared<Bicycle>(testplateNumberX,testbasePriceX);
        testRentX=std::make_shared<Rent>(1,testClientX,testVehicleX,pt::not_a_date_time);
    }

    ~TestSuiteRentRepositoryFixture() {


    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRentRepository, TestSuiteRentRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {

        BOOST_TEST(S.getRentRepository().size() == 1);
    }

    BOOST_AUTO_TEST_CASE(GetTest){

        BOOST_TEST(S.getRentRepository().get(0)->getRentInfo()==testRentX->getRentInfo());
        BOOST_TEST(S.getRentRepository().get(2)== nullptr);
        BOOST_TEST(S.getRentRepository().get(-1)==nullptr);
}
    BOOST_AUTO_TEST_CASE(AddTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        testVehicle= std::make_shared<Bicycle>(testplateNumber, testbasePrice);
        testRent= std::make_shared<Rent>(2,testClient,testVehicle,pt::not_a_date_time);

        S.getRentRepository().add(testRent);
        BOOST_TEST(S.getRentRepository().size() == 2);
        BOOST_TEST(S.getRentRepository().get(1)->getRentInfo()==testRent->getRentInfo());
        S.getRentRepository().add(nullptr);
        BOOST_TEST(S.getRentRepository().size() == 2);

}
    BOOST_AUTO_TEST_CASE(RemoveTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        testVehicle= std::make_shared<Bicycle>(testplateNumber, testbasePrice);
        testRent= std::make_shared<Rent>(2,testClient,testVehicle,pt::not_a_date_time);
        S.getRentRepository().add(testRent);
        S.getRentRepository().remove(nullptr);
        BOOST_TEST(S.getRentRepository().size() == 2);
        S.getRentRepository().remove(testRent);
        BOOST_TEST(S.getRentRepository().size() == 1);
        BOOST_TEST(S.getRentRepository().get(0)->getRentInfo()==testRentX->getRentInfo());



}
    BOOST_AUTO_TEST_CASE(findALLTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        testVehicle= std::make_shared<Bicycle>(testplateNumber, testbasePrice);
        testRent= std::make_shared<Rent>(2,testClient,testVehicle,pt::not_a_date_time);
        S.getRentRepository().add(testRent);

        BOOST_TEST(S.getRentRepository().findAll().size()==2);
        BOOST_TEST(S.getRentRepository().findAll()[1]->getRentInfo()==testRent->getRentInfo());

     ;

    }
    BOOST_AUTO_TEST_CASE(findByTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        testVehicle= std::make_shared<Bicycle>(testplateNumber, testbasePrice);
        testRent= std::make_shared<Rent>(2,testClient,testVehicle,pt::not_a_date_time);
        S.getRentRepository().add(testRent);

        BOOST_TEST(S.getRentRepository().findBy(rentID1).size()==1);
        BOOST_TEST(S.getRentRepository().findBy(rentID1)[0]->getRentInfo()==testRent->getRentInfo());



    }


BOOST_AUTO_TEST_SUITE_END()


