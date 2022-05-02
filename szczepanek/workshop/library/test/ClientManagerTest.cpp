
#include <boost/test/unit_test.hpp>
//#include "model/StorageContainer.h"
#include "typedefs.h"
#include "managers/ClientManager.h"


#include "model/Default.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/Platinum.h"
#include "model/Diamond.h"

struct TestSuiteClientManagerFixture{
    const std::string testFN1 = "Jon";
    const std::string testLN1 = "Arbuckle";
    const std::string testPID1 = "1";
    const std::string testFN2 = "Filip";
    const std::string testLN2 = "Szczepanek";
    const std::string testPID2 = "2";
    AddressPtr testaddress1;
    AddressPtr testaddress2;
    ClientPtr testclient1;
    ClientPtr testclient2;
    ClientPtr testclient3;
    ClientManagerPtr CM;
    ClientTypePtr pt1;
    ClientTypePtr pt2;
//    ClientTypePtr pt3;
//    ClientTypePtr pt4;
//    ClientTypePtr pt5;
//    ClientTypePtr pt6;


    TestSuiteClientManagerFixture(){
        pt1 = std::make_shared<Default>();
        pt2 = std::make_shared<Bronze>();
//        pt3 = std::make_shared<Silver>();
//        pt4 = std::make_shared<Gold>();
//        pt5 = std::make_shared<Platinum>();
//        pt6 = std::make_shared<Diamond>();
        testaddress1 = std::make_shared<Address>("London", "Accacia Avenue", "22");
        testaddress2 = std::make_shared<Address>("Łask", "Rogaczewska", "4");
        testclient1 = std::make_shared<Client>(testFN1,testLN1,testPID1,testaddress1,pt1);
        testclient2 = std::make_shared<Client>(testFN2,testLN2,testPID2,testaddress2,pt1);
        CM = std::make_shared<ClientManager>();
    }
    ~TestSuiteClientManagerFixture(){

    }

};


BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager,TestSuiteClientManagerFixture)
    BOOST_AUTO_TEST_CASE(registertest) {
        CM->registerClient(testFN1,testLN1,testPID1,testaddress1,pt1);
        BOOST_TEST(CM->getClient(testPID2)==nullptr);
        BOOST_TEST(CM->getClient(testPID1)->getfirstName()==testFN1);
        CM->registerClient(testFN2,testLN2,testPID1,testaddress2,pt1);
        BOOST_TEST(CM->getClient(testPID1)->getfirstName()==testFN1);

    }
    BOOST_AUTO_TEST_CASE(unregistertest) {
        CM->registerClient(testFN1,testLN1,testPID1,testaddress1,pt1);
        CM->unregisterClient(CM->getClient(testPID1));
        CM->unregisterClient(CM->getClient(testPID2));
        BOOST_TEST_REQUIRE(CM->getClient(testPID1)!=nullptr);

        BOOST_TEST(CM->getClient(testPID1)->isArchive()==true);

    }
    BOOST_AUTO_TEST_CASE(findclienttest) {
        CM->registerClient(testFN1,testLN1,testPID1,testaddress1,pt2);
        BOOST_TEST(CM->findClients([](const ClientPtr ptr){return ptr->getMaxVehicles()>1;})[0]==CM->getClient(testPID1));
        BOOST_TEST(CM->findClients([](const ClientPtr ptr){return ptr->getMaxVehicles()>1;}).size()==1);

        CM->getClient(testPID1)->setArchive(true);
        BOOST_TEST(CM->findClients([](const ClientPtr ptr){return ptr->getMaxVehicles()>1;}).size()==0);

    }


BOOST_AUTO_TEST_SUITE_END()
