#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/ClientType.h"
#include "model/ShortTerm.h"
#include "model/Standard.h"
#include "model/LongTerm.h"
#include "exceptions/ClientError.h"



BOOST_AUTO_TEST_SUITE(TestSuiteClient)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefault) {
        ClientTypePtr T1=std::make_shared<ShortTerm>();

        Client c("Jan","ktos","242567",T1);
        BOOST_TEST(c.getFirstName()=="Jan");
        BOOST_TEST(c.getLastName().compare("ktos")==0);
        BOOST_TEST(c.getId() == "242567");
        BOOST_TEST(c.isArchive()==0);
        BOOST_TEST(c.getBill()==0);
        BOOST_TEST(c.getMaxDays()==2);
        BOOST_TEST(c.acceptDiscount()==0);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestExceptions) {
        ClientTypePtr T1=std::make_shared<ShortTerm>();

        BOOST_REQUIRE_THROW(Client c("","ktos","242567",T1),ClientError);
        BOOST_CHECK_EXCEPTION(Client c("","ktos","242567",T1),ClientError,
                            [] (const ClientError &e){return e.information()=="ERROR Empty first name";});
        BOOST_REQUIRE_THROW(Client c("Jan","","242567",T1),ClientError);
        BOOST_CHECK_EXCEPTION(Client c("Jan","","242567",T1),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Empty last name";});
        BOOST_REQUIRE_THROW(Client c("Jan","ktos","",T1),ClientError);
        BOOST_CHECK_EXCEPTION(Client c("Jan","ktos","",T1),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Empty personalId";});
        BOOST_REQUIRE_THROW(Client c("Jan","ktos","242567",nullptr),ClientError);
        BOOST_CHECK_EXCEPTION(Client c("Jan","ktos","242567",nullptr),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Null client type";});

    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestNotDefaultAndClientTypes) {
        ClientTypePtr T2=std::make_shared<Standard>();
        ClientTypePtr T3=std::make_shared<LongTerm>();
        Client c1("Jan","ktos","242567",T2);
        Client c2("Jan","ktos","242567",T3);
        BOOST_TEST(c1.getBill()==0);
        BOOST_TEST(c1.getMaxDays()==7);
        BOOST_TEST(c1.acceptDiscount()==1);
        BOOST_TEST(c2.getBill()==0);
        BOOST_TEST(c2.getMaxDays()==30);
        BOOST_TEST(c2.acceptDiscount()==1);
    }
    BOOST_AUTO_TEST_CASE(SetterTest) {
        ClientTypePtr T1=std::make_shared<ShortTerm>();
        ClientTypePtr T2=std::make_shared<Standard>();
        ClientTypePtr T3=std::make_shared<LongTerm>();
        Client c("Jan","ktos","242567",T1);
        c.setFirstName("Naj");
        c.setLastName("sotk");
        c.setArchive(true);
        c.setClientType(T2);
        BOOST_TEST(c.getFirstName()=="Naj");
        BOOST_TEST(c.getLastName()=="sotk");
        BOOST_TEST(c.isArchive()==true);
        BOOST_TEST(c.getMaxDays()==7);
        BOOST_TEST(c.acceptDiscount()==1);
        c.setClientType(T3);
        BOOST_TEST(c.getMaxDays()==30);
        BOOST_TEST(c.acceptDiscount()==1);


    }
    BOOST_AUTO_TEST_CASE(SetterTestExceptions) {
        ClientTypePtr T1=std::make_shared<ShortTerm>();
        Client c("Jan","ktos","242567",T1);
        BOOST_REQUIRE_THROW(c.setClientType(nullptr),ClientError);
        BOOST_CHECK_EXCEPTION(c.setClientType(nullptr),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Null client type";});
        BOOST_REQUIRE(c.getClientType()==T1);

        BOOST_REQUIRE_THROW(c.setFirstName(""),ClientError);
        BOOST_CHECK_EXCEPTION(c.setFirstName(""),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Empty first name";});
        BOOST_REQUIRE(c.getFirstName()=="Jan");

        BOOST_REQUIRE_THROW(c.setLastName(""),ClientError);
        BOOST_CHECK_EXCEPTION(c.setLastName(""),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Empty last name";});
        BOOST_REQUIRE(c.getLastName().compare("ktos")==0);

    }





BOOST_AUTO_TEST_SUITE_END()

