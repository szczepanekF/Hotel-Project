#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Address.h"
#include "repositories/StorageContainer.h"

struct TestSuiteClientFixture {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    ClientTypePtr testType;


    TestSuiteClientFixture() {
        testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        testType= std::make_shared<Default>();
    }

    ~TestSuiteClientFixture() {

    }

};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefault) {

        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        BOOST_TEST(c.getClientFirstName().compare(testFirstName ) == 0);
        BOOST_TEST(c.getClientLastName().compare(testLastName) == 0);
        BOOST_TEST(c.getClientPersonalID().compare(testPersonalID) == 0);
        BOOST_TEST(testaddress1 == c.getClientAddress());
        BOOST_TEST(c.isArchive() == 0);
        BOOST_TEST(c.getMaxVehicles()==1);
        BOOST_TEST(c.applyDiscount(1000)==0);
    }
    BOOST_AUTO_TEST_CASE(ClientSetterTests){
        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        AddressPtr pusty=NULL;
        c.setClientFirstName("Abraham");
        c.setClientLastName("Gold");
        c.setClientAddress(testaddress2);
        BOOST_TEST(c.getClientFirstName().compare("Abraham") == 0);
        BOOST_TEST(c.getClientLastName().compare("Gold") == 0);
        BOOST_TEST(testaddress2== c.getClientAddress());
        BOOST_CHECK_THROW(ClientPtr client= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, nullptr, testType),std::logic_error);
        BOOST_CHECK_THROW(ClientPtr client= std::make_shared<Client>("", testLastName, testPersonalID, testaddress1, testType),std::logic_error);
        BOOST_CHECK_THROW(ClientPtr client= std::make_shared<Client>(testFirstName, "", testPersonalID, testaddress1, testType),std::logic_error);
        BOOST_CHECK_THROW(ClientPtr client= std::make_shared<Client>(testFirstName, testLastName, "", testaddress1, testType),std::logic_error);
        BOOST_CHECK_THROW(ClientPtr client= std::make_shared<Client>(testFirstName, testLastName, testPersonalID, testaddress1, nullptr),std::logic_error);
        BOOST_CHECK_THROW(c.setClientFirstName(""),std::logic_error);
        BOOST_CHECK_THROW(c.setClientLastName(""),std::logic_error);
        BOOST_CHECK_THROW(c.setClientAddress(pusty),std::logic_error);
        c.setArchive(true);
        BOOST_TEST(c.isArchive() == 1);
        BOOST_TEST(c.getClientFirstName().compare("Abraham") == 0);
        BOOST_TEST(c.getClientLastName().compare("Gold") == 0);
        BOOST_TEST(testaddress2 == c.getClientAddress());
        BOOST_CHECK_THROW(c.setClientType(nullptr),std::logic_error);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestBronze){

        testType= std::make_shared<Bronze>();
        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        BOOST_TEST(c.getMaxVehicles()==2);
        BOOST_TEST(c.applyDiscount(1000)==3);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestSilver){

        testType= std::make_shared<Silver>();
        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        BOOST_TEST(c.getMaxVehicles()==3);
        BOOST_TEST(c.applyDiscount(1000)==6);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestGold){

        testType= std::make_shared<Gold>();
        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        BOOST_TEST(c.getMaxVehicles()==4);
        BOOST_TEST(c.applyDiscount(100)==5);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestPlatinum){

        testType= std::make_shared<Platinum>();
        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        BOOST_TEST(c.getMaxVehicles()==5);
        BOOST_TEST(c.applyDiscount(100)==10);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDiamond){

        testType= std::make_shared<Diamond>();
        Client c(testFirstName, testLastName, testPersonalID, testaddress1, testType);
        BOOST_TEST(c.getMaxVehicles()==10);
        BOOST_TEST(c.applyDiscount(125)==12.5);
        BOOST_TEST(c.applyDiscount(126)==25.2, boost::test_tools::tolerance(0.1));
        BOOST_TEST(c.applyDiscount(250)==50);
        BOOST_TEST(c.applyDiscount(251)==75.3);
        BOOST_TEST(c.applyDiscount(500)==150);
        BOOST_TEST(c.applyDiscount(1000)==400);
    }


BOOST_AUTO_TEST_SUITE_END()


























