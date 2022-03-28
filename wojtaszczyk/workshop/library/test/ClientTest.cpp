#include <boost/test/unit_test.hpp>
#include "model/Client.h"

BOOST_AUTO_TEST_SUITE(TestSuiteClient)

    BOOST_AUTO_TEST_CASE(AssertionsTests) {
        BOOST_TEST(1.0/3.0 == 0.333,  boost::test_tools::tolerance(0.01));
        BOOST_TEST(true);
    }
    BOOST_AUTO_TEST_CASE(ClientConstructorTest){
        Client c1("Milosz","Wojtaszczyk","242567");
        BOOST_TEST(c1.GetClientFirstName().compare("Milosz")==0);
        BOOST_TEST(c1.GetClientLastName().compare("Wojtaszczyk")==0);
        BOOST_TEST(c1.GetClientPersonalID().compare("242567")==0);

    }
    BOOST_AUTO_TEST_CASE(ClientSetterTests){
        Client c1("Milosz","Wojtaszczyk","242567");
        c1.SetClientFirstName("Abraham");
        c1.SetClientLastName("Gold");
        BOOST_TEST(c1.GetClientFirstName().compare("Abraham")==0);
        BOOST_TEST(c1.GetClientLastName().compare("Gold")==0);
        c1.SetClientFirstName(" ");
        c1.SetClientLastName(" ");
        BOOST_TEST(c1.GetClientFirstName().compare("Abraham")==0);
        BOOST_TEST(c1.GetClientLastName().compare("Gold")==0);
    }
BOOST_AUTO_TEST_SUITE_END()