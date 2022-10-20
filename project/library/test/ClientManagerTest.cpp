//
// Created by student on 06.06.2022.
//

#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Standard.h"
#include "model/ShortTerm.h"
#include "model/LongTerm.h"
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
        testType=std::make_shared<ShortTerm>();
        testType3=std::make_shared<LongTerm>();

    }

    ~ClientManagerFixture() = default;

};
BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager,ClientManagerFixture)

    BOOST_AUTO_TEST_CASE(RegisterAndGetClientTest) {
    ClientManager CM(CR);
    BOOST_TEST(CR->size()==0);
    testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
    testClient2= CM.registerClient("Stanislaw", "Kowalski", "242567", testType2);
    testClient3= CM.registerClient("Ktos", "Ziemowit", "444091", testType3);
    BOOST_TEST(CR->size()==3);
    BOOST_TEST(CM.getClient("242567")==testClient2);
    BOOST_TEST(CM.getClient("444091")==testClient3);
    BOOST_TEST(CM.getClient("242544")==testClient);
    BOOST_TEST(testClient->getBill()==0);
    BOOST_TEST(testClient2->getBill()==100);
    BOOST_TEST(testClient3->getBill()==300);
}
    BOOST_AUTO_TEST_CASE(ExcpetionsRegisterAndExceptionsGetClientTest) {
        ClientManager CM(CR);
        testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
        testClient2= CM.registerClient("Stanislaw", "Kowalski", "242567", testType);
        testClient3= CM.registerClient("Ktos", "Ziemowit", "444091", testType);
        std::string information=testClient->getInfo();
        ClientPtr testClient4 =nullptr;

        BOOST_REQUIRE_THROW(CM.registerClient("Jan", "Ktos", "242544", testType), ClientError);
        BOOST_CHECK_EXCEPTION(CM.registerClient("Jan", "Ktos", "242544", testType), ClientError,
                              [information] (const ClientError &e){return e.information()=="ERROR already exists: "+information;});
        BOOST_TEST(CR->size()==3);

        BOOST_REQUIRE_THROW(CM.registerClient("Jan", "Ktos", "242544", nullptr), ClientError);
        BOOST_CHECK_EXCEPTION(CM.registerClient("Jan", "Ktos", "242549", nullptr), ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR Null c_client type";});
        BOOST_TEST(CR->size()==3);

        BOOST_REQUIRE_THROW(testClient4=CM.getClient("1"),ClientError);
        BOOST_CHECK_EXCEPTION(CM.getClient("1"),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR No Object";});
        BOOST_TEST(testClient4==nullptr);

    }
    BOOST_AUTO_TEST_CASE(UnregisterTest) {
        ClientManager CM(CR);
        testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
        testClient2= CM.registerClient("Stanislaw", "Kowalski", "242567", testType);
        testClient3= CM.registerClient("Ktos", "Ziemowit", "444091", testType);
        BOOST_REQUIRE(!testClient->isArchive());
        BOOST_REQUIRE(!testClient2->isArchive());
        BOOST_REQUIRE(!testClient3->isArchive());
        CM.unregisterClient("242567");
        BOOST_TEST(!testClient->isArchive());
        BOOST_TEST(testClient2->isArchive());
        BOOST_TEST(!testClient3->isArchive());
    }
    BOOST_AUTO_TEST_CASE(ErrorUnregisterTest) {
        ClientManager CM(CR);
        testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
        testClient2= CM.registerClient("Stanislaw", "Kowalski", "242567", testType);
        testClient3= CM.registerClient("Ktos", "Ziemowit", "444091", testType);

        BOOST_REQUIRE_THROW(CM.unregisterClient("1"),ClientError);
        BOOST_CHECK_EXCEPTION(CM.unregisterClient("1"),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR No Object";});
        BOOST_TEST(!testClient->isArchive());
        BOOST_TEST(!testClient2->isArchive());
        BOOST_TEST(!testClient3->isArchive());

    }

    BOOST_AUTO_TEST_CASE(FindClientsAndFindAllClientsTest){
        ClientManager CM(CR);
        testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
        testClient2= CM.registerClient("NieJan", "Kowalski", "242567", testType);
        testClient3= CM.registerClient("Jan", "Ziemowit", "444091", testType);
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";}).size()==2);
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";})[0]==testClient);
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan";})[1]==testClient3);
        BOOST_TEST(CM.findAllClients().size()=3);
        CM.unregisterClient("242544");
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan" && !ptr->isArchive();}).size()==1);
        BOOST_TEST(CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Jan" && !ptr->isArchive();})[0]==testClient3);
        BOOST_TEST(CM.findAllClients().size()=2);
}
    BOOST_AUTO_TEST_CASE(ExceptionsFindClientsAndFindAllClientsTest){
        ClientManager CM(CR);
        testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
        testClient2= CM.registerClient("Jan", "Kowalski", "242567", testType);
        testClient3= CM.registerClient("Jan", "Ziemowit", "444091", testType);

        std::vector<ClientPtr> testClients;
        BOOST_REQUIRE_THROW(testClients=CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Janek";}),ClientError);
        BOOST_CHECK_EXCEPTION(CM.findClients([](const ClientPtr &ptr)->bool{return ptr->getFirstName()=="Janek";}),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testClients.size()==0);

        CM.unregisterClient("242567");
        CM.unregisterClient("242544");
        CM.unregisterClient("444091");
        BOOST_REQUIRE_THROW(testClients=CM.findAllClients(),ClientError);
        BOOST_CHECK_EXCEPTION(CM.findAllClients(),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR No Objects";});
        BOOST_TEST(testClients.size()==0);
    }
    BOOST_AUTO_TEST_CASE(ChangeTypeTest){
        ClientManager CM(CR);
        testClient= CM.registerClient("Jan", "Ktos", "242544", testType);
        CM.changeClientTypetoStandard("242544");
        BOOST_CHECK(testClient->getBill()==100);
        CM.changeClientTypetoLongTerm("242544");
        BOOST_CHECK(testClient->getBill()==400);
        testClient2= CM.registerClient("Jan", "Kowalski", "242567", testType);
        CM.changeClientTypetoLongTerm("242567");
        BOOST_CHECK(testClient2->getBill()==300);
}
    BOOST_AUTO_TEST_CASE(ErrorChangeTypeTest) {
        ClientManager CM(CR);
        testClient = CM.registerClient("Jan", "Ktos", "242544", testType3);
        BOOST_REQUIRE_THROW(CM.changeClientTypetoStandard("242544"), ClientError);
        BOOST_CHECK_EXCEPTION(CM.changeClientTypetoStandard("242544"),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR cant change to lower type";});
        BOOST_TEST(testClient->getClientType()==testType3);

        BOOST_REQUIRE_THROW(CM.changeClientTypetoLongTerm("242544"), ClientError);
        BOOST_CHECK_EXCEPTION(CM.changeClientTypetoLongTerm("242544"),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR cant change to equal type";});
        BOOST_TEST(testClient->getClientType()==testType3);

        testClient2 = CM.registerClient("Jan", "Kowalski", "242567", testType2);
        BOOST_REQUIRE_THROW(CM.changeClientTypetoStandard("242567"), ClientError);
        BOOST_CHECK_EXCEPTION(CM.changeClientTypetoStandard("242567"),ClientError,
                              [] (const ClientError &e){return e.information()=="ERROR cant change to equal type";});
        BOOST_TEST(testClient2->getClientType()==testType2);
    }

BOOST_AUTO_TEST_SUITE_END()