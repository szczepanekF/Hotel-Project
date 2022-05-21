#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/ClientType.h"
#include "model/shortTerm.h"
#include "model/Standard.h"
#include "model/longTerm.h"


BOOST_AUTO_TEST_SUITE(TestSuiteClient)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefault) {
        ClientTypePtr T1=std::make_shared<shortTerm>();

        Client c("Jan","ktos","242567",T1);
        BOOST_TEST(c.getFirstName()=="Jan");
        BOOST_TEST(c.getLastName()=="ktos");
        BOOST_TEST(c.getPersonalId()=="242567");
        BOOST_TEST(c.isArchive()==0);
        BOOST_TEST(c.getBill()==0);
        BOOST_TEST(c.getMaxDays()==2);
        BOOST_TEST(c.acceptDiscount()==0);
    }
    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestNotDefaultAndClientTypes) {
        ClientTypePtr T2=std::make_shared<Standard>();
        ClientTypePtr T3=std::make_shared<longTerm>();
        Client c1("Jan","ktos","242567",T2);
        Client c2("Jan","ktos","242567",T3);
        BOOST_TEST(c1.getBill()==100);
        BOOST_TEST(c1.getMaxDays()==7);
        BOOST_TEST(c1.acceptDiscount()==1);
        BOOST_TEST(c2.getBill()==300);
        BOOST_TEST(c2.getMaxDays()==30);
        BOOST_TEST(c2.acceptDiscount()==1);
    }
    BOOST_AUTO_TEST_CASE(SetterTest) {
        ClientTypePtr T1=std::make_shared<shortTerm>();
        ClientTypePtr T2=std::make_shared<Standard>();
        ClientTypePtr T3=std::make_shared<longTerm>();
        Client c("Jan","ktos","242567",T1);
        c.setFirstName("Naj");
        c.setLastName("sotk");
        c.setArchive(true);
        c.setClientType(T2);
        BOOST_TEST(c.getFirstName()=="Naj");
        BOOST_TEST(c.getLastName()=="sotk");
        BOOST_TEST(c.isArchive()==true);
        BOOST_TEST(c.getBill()==100);
        BOOST_TEST(c.getMaxDays()==7);
        BOOST_TEST(c.acceptDiscount()==1);
        c.setClientType(T1);
        BOOST_TEST(c.getClientType()->getClientTypeInfo()==T2->getClientTypeInfo());
        c.setClientType(T3);
        BOOST_TEST(c.getBill()==400);
        BOOST_TEST(c.getMaxDays()==30);
        BOOST_TEST(c.acceptDiscount()==1);
        c.setClientType(T1);
        BOOST_TEST(c.getClientType()->getClientTypeInfo()==T3->getClientTypeInfo());
        c.setClientType(T2);
        BOOST_TEST(c.getClientType()->getClientTypeInfo()==T3->getClientTypeInfo());
        BOOST_TEST(c.getBill()==400);

    }





BOOST_AUTO_TEST_SUITE_END()

