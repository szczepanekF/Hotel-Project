#include <boost/test/unit_test.hpp>
#include "model/Client.h"

struct TestSuiteClientFixture {
    const std::string testFirstName = "Jon";
    const std::string testLastName = "Arbuckle";
    const std::string testPersonalID = "0123456789";
    Address *testaddress1;
    Address *testaddress2;

    TestSuiteClientFixture() {
        testaddress1 = new Address("London", "Accacia Avenue", "22");
        testaddress2 = new Address("London", "Rue Morgue", "13");
    }

    ~TestSuiteClientFixture() {
        delete testaddress1;
        delete testaddress2;
    }

};



BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ClientConstructorTests) {

        Client a(testFirstName, testLastName, testPersonalID, testaddress1);

            BOOST_TEST(a.getfirstName().compare(testFirstName)==0);
            BOOST_TEST(a.getlastName().compare(testLastName)==0);
            BOOST_TEST(a.getpersonalID().compare(testPersonalID)==0);
            BOOST_TEST(a.get_address()== testaddress1);
            BOOST_TEST(a.get_rentNumber()==0);

    }
    BOOST_AUTO_TEST_CASE(ClientfirstnameSetterTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1);
        a.setfirstName("");
        BOOST_TEST(a.getfirstName().compare(testFirstName)==0);
        a.setfirstName("x");
        BOOST_TEST(a.getfirstName().compare("x")==0);

    }
    BOOST_AUTO_TEST_CASE(ClientlastnameSetterTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1);
        a.setlastName("");
        BOOST_TEST(a.getlastName().compare(testLastName)==0);
        a.setlastName("x");
        BOOST_TEST(a.getlastName().compare("x")==0);

    }
    BOOST_AUTO_TEST_CASE(ClientAddressSetterTests) {
        Client a(testFirstName, testLastName, testPersonalID, testaddress1);
        Address *b = NULL;
        a.set_address(b);
        BOOST_TEST(a.get_address()== testaddress1);
        a.set_address(testaddress2);
        BOOST_TEST(a.get_address()== testaddress2);
    }

BOOST_AUTO_TEST_SUITE_END()