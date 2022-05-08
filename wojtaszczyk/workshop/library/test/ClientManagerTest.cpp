#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "managers/ClientManager.h"

struct TestSuiteClientManagerFixture {
    const std::string testFirstName = "Jan";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    StorageContainer S;
    ClientPtr testClient;

    const std::string testFirstNameX = "Jon";
    const std::string testLastNameX = "Arbuckle";
    const std::string testPersonalIDX = "12";
    AddressPtr testaddress1X;
    ClientPtr testClientX;
    ClientPtr testClient2;
    ClientTypePtr testType;
    ClientManager CM;



    TestSuiteClientManagerFixture() {

        testType= std::make_shared<Default>();
        testaddress1X = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testClientX= std::make_shared<Client>(testFirstNameX, testLastNameX, testPersonalIDX, testaddress1X,testType);
       // CM.registerClient(testFirstNameX,testLastNameX,testPersonalIDX,testaddress1X,testType);

    }

    ~TestSuiteClientManagerFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteClientManagerFixture)


    BOOST_AUTO_TEST_CASE(registerTest){
        ClientPtr ptr;
        ptr=CM.registerClient(testFirstNameX,testLastNameX,testPersonalIDX,testaddress1X,testType);
        BOOST_TEST(CM.getClient("12")==ptr);
        BOOST_TEST(CM.getClient("10")==nullptr);
        BOOST_TEST(CM.findAllClients().size()==1);
        ptr=CM.registerClient(testFirstName,testLastName,testPersonalIDX,testaddress1X,testType);
        BOOST_TEST(ptr==CM.findAllClients()[0]);
        ClientPredicate f=[](ClientPtr ptr)->bool{return ptr->getClientPersonalID()=="12";};
        BOOST_TEST(CM.findClients(f).size()==1);
        CM.unregisterClient("12");
        BOOST_TEST(ptr->isArchive()==true);
        BOOST_TEST(CM.findClients(f).size()==0);
        ptr=CM.registerClient(testFirstName,testLastName,"2",testaddress1X,testType);
        BOOST_TEST(CM.findClients(f).size()==0);
        BOOST_TEST(CM.findAllClients().size()==1);
    }


BOOST_AUTO_TEST_SUITE_END()

