#include <boost/test/unit_test.hpp>
#include "model/Client.h"

BOOST_AUTO_TEST_SUITE(TestSuiteClient)

    BOOST_AUTO_TEST_CASE(ClientConstructorTests) {
        Client a("1","2","3");

            BOOST_TEST(a.getfirstName().compare("1")==0);
            BOOST_TEST(a.getlastName().compare("2")==0);
            BOOST_TEST(a.getpersonalID().compare("3")==0);

    }
    BOOST_AUTO_TEST_CASE(ClientfirstnameSetterTests) {
        Client a("a","b","c");
        a.setfirstName("x");
        BOOST_TEST(a.getfirstName().compare("x")==0);
        a.setfirstName("");
        BOOST_TEST(a.getfirstName().compare("x")==0);



    }
    BOOST_AUTO_TEST_CASE(ClientlastnameSetterTests) {
        Client a("a","b","c");
        a.setlastName("x");
        BOOST_TEST(a.getlastName().compare("x")==0);
        a.setlastName("");
        BOOST_TEST(a.getlastName().compare("x")==0);



    }


BOOST_AUTO_TEST_SUITE_END()