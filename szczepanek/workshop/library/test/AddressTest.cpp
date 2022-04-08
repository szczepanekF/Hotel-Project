#include <boost/test/unit_test.hpp>
#include "model/Address.h"

BOOST_AUTO_TEST_SUITE(TestSuiteAddress)

    BOOST_AUTO_TEST_CASE(AddressConstructorTests) {
        Address a("1","2","3");

        BOOST_TEST(a.get_city().compare("1")==0);
        BOOST_TEST(a.get_street().compare("2")==0);
        BOOST_TEST(a.get_number().compare("3")==0);
    }


   /* BOOST_AUTO_TEST_CASE(AddressCitySetterTests) {
        Address a("a","b","c");
        a.set_city("x");
        BOOST_TEST(a.get_city().compare("x")==0);
    }
    BOOST_AUTO_TEST_CASE(AddressStreetSetterTests) {
        Address a("a","b","c");
        a.set_street("x");
        BOOST_TEST(a.get_street().compare("x")==0);
    }
    BOOST_AUTO_TEST_CASE(AddressNumberSetterTests) {
        Address a("a","b","c");
        a.set_number("x");
        BOOST_TEST(a.get_number().compare("x")==0);
    }
    */


BOOST_AUTO_TEST_SUITE_END()