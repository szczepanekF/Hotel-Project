//
// Created by student on 06.06.2022.
//

#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Standard.h"
#include "model/shortTerm.h"
#include "model/longTerm.h"
#include "model/RoomWithoutTerrace.h"
#include "repositories/ClientRepository.h"
#include "managers/ClientManager.h"
#include "exceptions/ClientError.h"


struct ClientManagerFixture {
    ClientTypePtr testType;
    ClientTypePtr testType2;
    ClientTypePtr testType3;
    ClientPtr testClient;
    ClientPtr testClient2;
    ClientPtr testClient3;
    ClientRepositoryPtr CR;


    ClientManagerFixture() {
        CR= std::make_shared<ClientRepository>();
        testType2=std::make_shared<Standard>();
        testType=std::make_shared<shortTerm>();
        testType3=std::make_shared<longTerm>();

    }

    ~ClientManagerFixture() {

    }

};
BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager,ClientManagerFixture)

    BOOST_AUTO_TEST_CASE(TestRegisterAndGetClient) {
    ClientManager CM(CR);
    BOOST_TEST(CR->size()==0);
    testClient=CM.regiterClient("Jan","Ktos","242544",testType);
    testClient2=CM.regiterClient("Stanislaw","Kowalski","242567",testType2);
    testClient3=CM.regiterClient("Ktos","Ziemowit","444091",testType3);
    BOOST_TEST(CR->size()==3);
    BOOST_TEST(CM.getClient("242567")==testClient2);
    BOOST_TEST(CM.getClient("444091")==testClient3);
    BOOST_TEST(CM.getClient("242544")==testClient);
    BOOST_TEST(testClient->getBill()==0);
    BOOST_TEST(testClient2->getBill()==100);
    BOOST_TEST(testClient3->getBill()==300);
}
    BOOST_AUTO_TEST_CASE(TestErrorRegisterAndErrorGetClient) {
        ClientManager CM(CR);
        testClient=CM.regiterClient("Jan","Ktos","242544",testType);
        testClient2=CM.regiterClient("Stanislaw","Kowalski","242567",testType);
        testClient3=CM.regiterClient("Ktos","Ziemowit","444091",testType);
        std::string information=testClient->getInfo();
        BOOST_CHECK_THROW(CM.regiterClient("Jan","Ktos","242544",testType),ClientError);
        BOOST_CHECK_EXCEPTION(CM.regiterClient("Jan","Ktos","242544",testType),ClientError,
                              [information] (const ClientError &e){return e.information()=="ERROR already exists: "+information;});
        BOOST_CHECK_THROW(CM.regiterClient("Jan","Ktos","242544",nullptr),ClientError);
        BOOST_CHECK_EXCEPTION(CM.regiterClient("Jan","Ktos","242549",nullptr),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR Null client type")==0;});
        BOOST_TEST(CR->size()==3);
        BOOST_CHECK_THROW(CM.getClient("1"),ClientError);
        BOOST_CHECK_EXCEPTION(CM.getClient("1"),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR No Object")==0;});

    }
    BOOST_AUTO_TEST_CASE(TestUnregister) {
        ClientManager CM(CR);
        testClient=CM.regiterClient("Jan","Ktos","242544",testType);
        testClient2=CM.regiterClient("Stanislaw","Kowalski","242567",testType);
        testClient3=CM.regiterClient("Ktos","Ziemowit","444091",testType);
        BOOST_REQUIRE(!testClient->isArchive());
        BOOST_REQUIRE(!testClient2->isArchive());
        BOOST_REQUIRE(!testClient3->isArchive());
        CM.unregisterClient("242567");
        BOOST_TEST(!testClient->isArchive());
        BOOST_TEST(testClient2->isArchive());
        BOOST_TEST(!testClient3->isArchive());
    }
    BOOST_AUTO_TEST_CASE(TestErrorUnregister) {
        ClientManager CM(CR);
        testClient=CM.regiterClient("Jan","Ktos","242544",testType);
        testClient2=CM.regiterClient("Stanislaw","Kowalski","242567",testType);
        testClient3=CM.regiterClient("Ktos","Ziemowit","444091",testType);
        BOOST_CHECK_THROW(CM.unregisterClient("1"),ClientError);
        BOOST_CHECK_EXCEPTION(CM.unregisterClient("1"),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR No Object")==0;});

    }

    BOOST_AUTO_TEST_CASE(TestFindClientsAndFindAllClients){
        ClientManager CM(CR);
        testClient=CM.regiterClient("Jan","Ktos","242544",testType);
        testClient2=CM.regiterClient("Jan","Kowalski","242567",testType);
        testClient3=CM.regiterClient("Jan","Ziemowit","444091",testType);
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return !ptr->getFirstName().compare("Jan");}).size()==3);
        BOOST_TEST(CM.findAllClients().size()=3);
        CM.unregisterClient("242567");
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return !ptr->getFirstName().compare("Jan")&& !ptr->isArchive();}).size()==2);
        BOOST_TEST(CM.findAllClients().size()=2);
}
    BOOST_AUTO_TEST_CASE(TestErrorFindClientsAndFindAllClients){
        ClientManager CM(CR);
        testClient=CM.regiterClient("Jan","Ktos","242544",testType);
        testClient2=CM.regiterClient("Jan","Kowalski","242567",testType);
        testClient3=CM.regiterClient("Jan","Ziemowit","444091",testType);
        BOOST_REQUIRE_THROW(CM.findClients([](const ClientPtr &ptr)->bool{return !ptr->getFirstName().compare("Janek");}),ClientError);
        BOOST_CHECK_EXCEPTION(CM.findClients([](const ClientPtr &ptr)->bool{return !ptr->getFirstName().compare("Janek");}),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR No Objects")==0;});
        CM.unregisterClient("242567");
        CM.unregisterClient("242544");
        CM.unregisterClient("444091");
        BOOST_REQUIRE_THROW(CM.findAllClients(),ClientError);
        BOOST_CHECK_EXCEPTION(CM.findAllClients(),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR No Objects")==0;});
    }
    BOOST_AUTO_TEST_CASE(TestChangeType){
        ClientManager CM(CR);
        testClient=CM.regiterClient("Jan","Ktos","242544",testType);
        CM.changeClientTypetoStandard("242544");
        BOOST_CHECK(testClient->getBill()==100);
        CM.changeClientTypetoLongTerm("242544");
        BOOST_CHECK(testClient->getBill()==400);
        testClient2=CM.regiterClient("Jan","Kowalski","242567",testType);
        CM.changeClientTypetoLongTerm("242567");
        BOOST_CHECK(testClient2->getBill()==300);
}
    BOOST_AUTO_TEST_CASE(TestErrorChangeType) {
        ClientManager CM(CR);
        testClient = CM.regiterClient("Jan", "Ktos", "242544", testType3);
        BOOST_REQUIRE_THROW(CM.changeClientTypetoStandard("242544"), ClientError);
        BOOST_CHECK_EXCEPTION(CM.changeClientTypetoStandard("242544"),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR cant change to lower type")==0;});
        BOOST_REQUIRE_THROW(CM.changeClientTypetoLongTerm("242544"), ClientError);
        BOOST_CHECK_EXCEPTION(CM.changeClientTypetoLongTerm("242544"),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR cant change to equal type")==0;});
        testClient2 = CM.regiterClient("Jan", "Kowalski", "242567", testType2);
        BOOST_REQUIRE_THROW(CM.changeClientTypetoStandard("242567"), ClientError);
        BOOST_CHECK_EXCEPTION(CM.changeClientTypetoStandard("242567"),ClientError,
                              [] (const ClientError &e){return e.information().compare("ERROR cant change to equal type")==0;});
    }

BOOST_AUTO_TEST_SUITE_END()