#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"

struct TestSuiteClientRepositoryFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    StorageContainer S;
    ClientPtr testClient;

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



    TestSuiteClientRepositoryFixture() {
       // testaddress1 = new Address("London", "Accacia Avenue", "22");
        //testaddress2 = new Address("London", "Rue Morgue", "13");
        testaddress1X = new Address("London", "Accacia Avenue", "22");
        testClientX= new Client(testFirstNameX, testLastNameX, testPersonalIDX, testaddress1X);
        testVehicleX= new Bicycle(testplateNumberX,testbasePriceX);
        testRentX=new Rent(1,testClientX,testVehicleX,pt::not_a_date_time);
    }

    ~TestSuiteClientRepositoryFixture() {
        delete testaddress1X;
        delete testClientX;
        delete testVehicleX;
        delete testRentX;

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientRepository, TestSuiteClientRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {

        BOOST_TEST(S.getClientRepository().size() == 1);
    }

    BOOST_AUTO_TEST_CASE(GetTest){

        BOOST_TEST(S.getClientRepository().get(0)->getFullClientInfo()==testClientX->getFullClientInfo());
        BOOST_TEST(S.getClientRepository().get(1)== nullptr);
        BOOST_TEST(S.getClientRepository().get(-1)==nullptr);
}
    BOOST_AUTO_TEST_CASE(AddTest){
        testaddress2 = new Address("London", "Rue Morgue", "13");
        testClient= new Client(testFirstName, testLastName, testPersonalID, testaddress2);
        S.getClientRepository().add(testClient);
        BOOST_TEST(S.getClientRepository().size() == 2);
        BOOST_TEST(S.getClientRepository().get(1)->getClientInfo()==testClient->getClientInfo());
        S.getClientRepository().add(nullptr);
        BOOST_TEST(S.getClientRepository().size() == 2);
        delete testaddress2;
}
    BOOST_AUTO_TEST_CASE(RemoveTest){
        testaddress2 = new Address("London", "Rue Morgue", "13");
        testClient= new Client(testFirstName, testLastName, testPersonalID, testaddress2);
        testClient2= new Client("Miłosz", "Wojtaszczyk", "242567", testaddress2);
        S.getClientRepository().add(testClient);
        S.getClientRepository().add(testClient2);
        S.getClientRepository().remove(testClient);
        BOOST_TEST(S.getClientRepository().size() == 2);
        BOOST_TEST(S.getClientRepository().get(1)->getClientInfo()==testClient2->getClientInfo());
        S.getClientRepository().remove(nullptr);
        BOOST_TEST(S.getClientRepository().size() == 2);

        delete testaddress2;


}
    BOOST_AUTO_TEST_CASE(findALLTest){
        testaddress2 = new Address("London", "Rue Morgue", "13");
        testClient= new Client(testFirstName, testLastName, testPersonalID, testaddress2);
        S.getClientRepository().add(testClient);

        BOOST_TEST(S.getClientRepository().findAll().size()==2);
        BOOST_TEST(S.getClientRepository().findAll()[1]->getClientInfo()==testClient->getClientInfo());

        delete testaddress2;

}
    BOOST_AUTO_TEST_CASE(findByTest){
        testaddress2 = new Address("London", "Rue Morgue", "13");
        testClient= new Client(testFirstName, testLastName, "1", testaddress2);
        S.getClientRepository().add(testClient);

        BOOST_TEST(S.getClientRepository().findBy(clientID1).size()==1);
        BOOST_TEST(S.getClientRepository().findBy(clientID1)[0]->getClientInfo()==testClient->getClientInfo());

        delete testaddress2;

    }


BOOST_AUTO_TEST_SUITE_END()


