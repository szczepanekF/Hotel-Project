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
    ClientPtr testClientX;
    ClientPtr testClient2;
    ClientTypePtr testType;



    TestSuiteClientRepositoryFixture() {

        testType= std::make_shared<Default>();
        testaddress1X = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testClientX= std::make_shared<Client>(testFirstNameX, testLastNameX, testPersonalIDX, testaddress1X,testType);

    }

    ~TestSuiteClientRepositoryFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientRepository, TestSuiteClientRepositoryFixture)

    BOOST_AUTO_TEST_CASE(SizeTest) {

        BOOST_TEST(S.getClientRepository().size() == 1);
    }

    BOOST_AUTO_TEST_CASE(GetTest){

        BOOST_TEST(S.getClientRepository().get(0)->getClientInfo()==testClientX->getClientInfo());
        BOOST_TEST(S.getClientRepository().get(1)== nullptr);
        BOOST_TEST(S.getClientRepository().get(-1)==nullptr);
}
    BOOST_AUTO_TEST_CASE(AddTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        S.getClientRepository().add(testClient);
        BOOST_TEST(S.getClientRepository().size() == 2);
        BOOST_TEST(S.getClientRepository().get(1)->getClientInfo()==testClient->getClientInfo());
        S.getClientRepository().add(nullptr);
        BOOST_TEST(S.getClientRepository().size() == 2);

}
    BOOST_AUTO_TEST_CASE(RemoveTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        testClient2= std::make_shared<Client>("Miłosz", "Wojtaszczyk", "242567", testaddress2,testType);
        S.getClientRepository().add(testClient);
        S.getClientRepository().add(testClient2);
        S.getClientRepository().remove(testClient);
        BOOST_TEST(S.getClientRepository().size() == 2);
        BOOST_TEST(S.getClientRepository().get(1)->getClientInfo()==testClient2->getClientInfo());
        S.getClientRepository().remove(nullptr);
        BOOST_TEST(S.getClientRepository().size() == 2);


}
    BOOST_AUTO_TEST_CASE(findALLTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress2,testType);
        S.getClientRepository().add(testClient);

        BOOST_TEST(S.getClientRepository().findAll().size()==2);
        BOOST_TEST(S.getClientRepository().findAll()[1]->getClientInfo()==testClient->getClientInfo());

}
    BOOST_AUTO_TEST_CASE(findByTest){
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient= std::make_shared<Client>(testFirstName, testLastName, "1", testaddress2,testType);
        S.getClientRepository().add(testClient);

        BOOST_TEST(S.getClientRepository().findBy(clientID1).size()==1);
        BOOST_TEST(S.getClientRepository().findBy(clientID1)[0]->getClientInfo()==testClient->getClientInfo());


    }
    BOOST_AUTO_TEST_CASE(findByPersonalIDTest) {
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testClient = std::make_shared<Client>(testFirstName, testLastName, "1", testaddress2, testType);
        S.getClientRepository().add(testClient);

        BOOST_TEST(S.getClientRepository().findByPersonalID("1") == testClient);
        BOOST_TEST(S.getClientRepository().findByPersonalID("51") == nullptr);
    }




    BOOST_AUTO_TEST_SUITE_END()


