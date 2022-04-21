#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Default.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"
#include "model/Diamond.h"

struct TestSuiteClientFixture {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    ClientTypePtr pt1;
    ClientTypePtr pt2;
    ClientTypePtr pt3;
    ClientTypePtr pt4;
    ClientTypePtr pt5;
    ClientTypePtr pt6;

    TestSuiteClientFixture() {
        testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testaddress2 = std::make_shared<Address>("London", "Rue Morgue", "13");
        pt1 = std::make_shared<Default>();
        pt2 = std::make_shared<Bronze>();
        pt3 = std::make_shared<Silver>();
        pt4 = std::make_shared<Gold>();
        pt5 = std::make_shared<Platinum>();
        pt6 = std::make_shared<Diamond>();
    }

    ~TestSuiteClientFixture() {
//        delete testaddress1;
//        delete testaddress2;
    }

};



BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ClientConstructorTests) {

        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt1);

            BOOST_TEST(a.getfirstName().compare(testFirstName)==0);
            BOOST_TEST(a.getlastName().compare(testLastName)==0);
            BOOST_TEST(a.getpersonalID().compare(testPersonalID)==0);
            BOOST_TEST(a.get_address()== testaddress1);
            BOOST_TEST(a.isArchive()==false);

    }
    BOOST_AUTO_TEST_CASE(ClientfirstnameSetterTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt1);
        a.setfirstName("");
        BOOST_TEST(a.getfirstName().compare(testFirstName)==0);
        a.setfirstName("x");
        BOOST_TEST(a.getfirstName().compare("x")==0);

    }
    BOOST_AUTO_TEST_CASE(ClientlastnameSetterTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt1);
        a.setlastName("");
        BOOST_TEST(a.getlastName().compare(testLastName)==0);
        a.setlastName("x");
        BOOST_TEST(a.getlastName().compare("x")==0);

    }
    BOOST_AUTO_TEST_CASE(ClientAddressSetterTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt1);
        AddressPtr b = NULL;
        a.set_address(b);
        BOOST_TEST(a.get_address()== testaddress1);
        a.set_address(testaddress2);
        BOOST_TEST(a.get_address()== testaddress2);
    }

    BOOST_AUTO_TEST_CASE(ClientTypeDefaultTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt1);
        BOOST_TEST(a.applyDiscount(100) == 0);
        BOOST_TEST(a.getMaxVehicles()== 1);
    }
    BOOST_AUTO_TEST_CASE(ClientTypeBronzeTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt2);
        BOOST_TEST(a.applyDiscount(100) == 3);
        BOOST_TEST(a.getMaxVehicles()== 2);
    }
    BOOST_AUTO_TEST_CASE(ClientTypeSilverTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt3);
        BOOST_TEST(a.applyDiscount(100) == 6);
        BOOST_TEST(a.getMaxVehicles()== 3);
    }
    BOOST_AUTO_TEST_CASE(ClientTypeGoldTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt4);
        BOOST_TEST(a.applyDiscount(100) == 5);
        BOOST_TEST(a.getMaxVehicles()== 4);
    }
    BOOST_AUTO_TEST_CASE(ClientTypePlatinumTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt5);
        BOOST_TEST(a.applyDiscount(100) == 10);
        BOOST_TEST(a.getMaxVehicles()== 5);
    }
    BOOST_AUTO_TEST_CASE(ClientTypeDiamondTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1,pt6);
        BOOST_TEST(a.applyDiscount(125) == 12.5);
        BOOST_TEST(a.applyDiscount(250) == 50);
        BOOST_TEST(a.applyDiscount(500) == 150);
        BOOST_TEST(a.applyDiscount(1000) == 400);
        BOOST_TEST(a.getMaxVehicles()== 10);
    }


BOOST_AUTO_TEST_SUITE_END()