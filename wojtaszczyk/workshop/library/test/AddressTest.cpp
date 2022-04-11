
#include <boost/test/unit_test.hpp>
#include "model/Address.h"

BOOST_AUTO_TEST_SUITE(TestSuiteAddress)

    BOOST_AUTO_TEST_CASE(AddressConstructorTest){
    Address a1("Pabianice","Dobra","25");
    BOOST_TEST(a1.GetAddresscity().compare("Pabianice")==0);
    BOOST_TEST(a1.GetAddressstreet().compare("Dobra")==0);
    BOOST_TEST(a1.GetAddressnumber().compare("25")==0);
}




BOOST_AUTO_TEST_SUITE_END()